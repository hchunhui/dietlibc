#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int pipe(int pipefd[2])
{
	int fd1 = open("/dev/pipe/0", O_RDWR);
	int fd2 = -1;
	int saveerr;
	fd2 = dup2(fd1, -1);
	if(fd2 == -1)
	{
		saveerr = errno;
		close(fd1);
		errno = saveerr;
		return -1;
	}
	pipefd[0] = fd1;
	pipefd[1] = fd2;
	return 0;
}

