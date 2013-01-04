#include <time.h>
#include <unistd.h>

/* nano * 1000 == usecs
 * usecs * 1000 == msecs
 * msecs * 1000 = secs */
int usleep(unsigned long usecs) {
	int fd;
	int t;
	t = usecs/10000;
	fd = open("/dev/timer/0", 0);
	write(fd, &t, sizeof(t));
	read(fd, &t, sizeof(t));
	close(fd);
	return 0;
}
