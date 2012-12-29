#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage)
{
	return waitpid(pid, status, options);
}

