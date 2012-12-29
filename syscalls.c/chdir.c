#include <unistd.h>
#include <errno.h>

int chdir(const char *path)
{
	errno = EACCES;
	return -1;
}

