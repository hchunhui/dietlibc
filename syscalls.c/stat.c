#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *path, struct stat *buf)
{
	int fd;
	int ret;
	int saveerr;
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return fd;
	ret = fstat(fd, buf);
	saveerr = errno;
	close(fd);
	errno = saveerr;
	return ret;
}

int lstat(const char *path, struct stat *buf) __attribute__((alias("stat")));
