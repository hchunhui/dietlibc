#ifndef _ERRNO_H
#define _ERRNO_H

#include <os/errno.h>

#ifndef __ASSEMBLER__

#include <sys/cdefs.h>

__BEGIN_DECLS

#ifndef _REENTRANT
extern int errno;
#else
#define errno (*__errno_location())
#endif

extern int *__errno_location(void);

#define __set_errno(x) errno=(x)

#ifdef _BSD_SOURCE
/* don't use, use strerror() instead! */
extern const char *const sys_errlist[] __attribute_dontuse__;
extern int sys_nerr __attribute_dontuse__;
#endif

#ifdef _GNU_SOURCE
extern char* program_invocation_name __attribute_dontuse__;
extern char* program_invocation_short_name __attribute_dontuse__;
#endif

__END_DECLS

#endif

#endif
