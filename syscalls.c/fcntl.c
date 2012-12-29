#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>

int fcntl(int fd, int cmd, ...)
{
	va_list ap;
	va_start(ap, cmd);
	int fd2;
	int ret;
	switch(cmd)
	{
	case F_DUPFD:
		fd2 = va_arg(ap, int);
		ret = dup2(fd, fd2);
		break;
	default:
		errno = ENOSYS;
		ret = -1;
		break;
	}
	va_end(ap);
	return ret;
}

