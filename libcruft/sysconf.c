#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/resource.h>
#include <fcntl.h>
#define _GNU_SOURCE
#include <sched.h>

long sysconf(int name)
{
  switch(name)
  {
  case _SC_OPEN_MAX:
    return 64;

  case _SC_CLK_TCK:
    return 100;

  case _SC_PAGESIZE:
#if ( defined(__alpha__) || defined(__sparc__) )
    return 8192;
#else
    return 4096;
#endif

  case _SC_ARG_MAX:
    return ARG_MAX;

  case _SC_NGROUPS_MAX:
    return NGROUPS_MAX;

  case _SC_NPROCESSORS_ONLN:
    return 1;
  }
  errno=ENOSYS;
  return -1;
}
