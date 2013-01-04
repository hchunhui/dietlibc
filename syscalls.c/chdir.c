#include <unistd.h>
#include <errno.h>

int chdir(const char *path)
{
	errno = EACCES;
	return -1;
}

int fchdir(int fd)
{
	errno = EACCES;
	return -1;
}

