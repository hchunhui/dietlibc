#include <sys/types.h>

char *__syscall_getcwd(char *buf, size_t size)
{
	buf[0] = '/';
	buf[1] = 0;
	return buf;
}

