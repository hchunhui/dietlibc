#include <sys/time.h>

long __myos_gettime();
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	tv->tv_sec = __myos_gettime();
	tv->tv_usec = 0;
	return 0;
}
