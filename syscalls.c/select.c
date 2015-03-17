#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <drv/poll.h>
#include <errno.h>
#include <sys/param.h>

static void poll_set_event(int pollfd, int fd, int type)
{
	struct s_poll_event event;
	event.fd = fd;
	event.type = type;
	ioctl(pollfd, POLL_CMD_SET, &event);
}

static void poll_unset_event(int pollfd, int fd)
{
	struct s_poll_event event;
	event.fd = fd;
	event.type = 0;
	ioctl(pollfd, POLL_CMD_UNSET, &event);
}

int select(int nfds,
	   fd_set *rfds, fd_set *wfds, fd_set *efds,
	   struct timeval *timeout)
{
	int poll_fd = open("/dev/poll/0", 0);
	int timer_fd = -1;
	int fd;
	int i, tick, ret, n;

	n = 0;
	for(fd = 0; fd < nfds; fd++) {
		if(FD_ISSET(fd, rfds)) {
			n++;
			poll_set_event(poll_fd, fd, POLL_TYPE_READ);
		}
		if(FD_ISSET(fd, wfds)) {
			n++;
			poll_set_event(poll_fd, fd, POLL_TYPE_WRITE);
		}
		if(FD_ISSET(fd, efds)) {
			n++;
			poll_set_event(poll_fd, fd, POLL_TYPE_EXCEPT);
		}
	}

	if(timeout) {
		tick = timeout->tv_sec * HZ + timeout->tv_usec * HZ / 1000000;
		timer_fd = open("/dev/timer/0", 0);
		n++;
		poll_set_event(poll_fd, timer_fd, POLL_TYPE_READ);
		write(timer_fd, &tick, sizeof(tick));
	}

	struct s_poll_event evs[n];
	if(read(poll_fd, evs, n*sizeof(struct s_poll_event)) == -1) {
		errno = EINVAL;
		ret = -1;
		goto clean;
	}

	ret = n / sizeof(struct s_poll_event);
	FD_ZERO(rfds);
	FD_ZERO(wfds);
	FD_ZERO(efds);

	for(i = 0; i < n; i++) {
		fd = evs[i].fd;
		if(fd == timer_fd) {
			n--;
			continue;
		}
		if(evs[i].type & POLL_TYPE_READ)
			FD_SET(fd, rfds);
		if(evs[i].type & POLL_TYPE_WRITE)
			FD_SET(fd, wfds);
		if(evs[i].type & POLL_TYPE_EXCEPT)
			FD_SET(fd, efds);
	}

clean:
	close(poll_fd);
	if(timer_fd != -1)
		close(timer_fd);
	return ret;
}
