#include <sys/types.h>
#include <errno.h>

int __syscall_getcwd(char *buf, size_t size)
{
	if(buf && size) {
		buf[0] = '/';
		buf[1] = 0;
		return 1;
	}
	return -EINVAL;
}

