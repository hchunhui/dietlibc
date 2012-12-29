#ifndef _FCNTL_H
#define _FCNTL_H

#include <sys/cdefs.h>

#include <endian.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <os/fcntl.h>
__BEGIN_DECLS

#define F_LINUX_SPECIFIC_BASE	1024

extern int fcntl (int __fd, int __cmd, ...) __THROW;
#ifndef __NO_STAT64
extern int fcntl64 (int __fd, int __cmd, ...) __THROW;
#if defined _FILE_OFFSET_BITS && _FILE_OFFSET_BITS == 64
#define fcntl fcntl64
#endif
#endif

#if !defined(O_ASYNC) && defined(FASYNC)
#define O_ASYNC FASYNC
#endif

#if defined(_LINUX_SOURCE) || defined(_GNU_SOURCE)
ssize_t readahead(int fd, off64_t *offset, size_t count) __THROW;
#endif

#ifdef _GNU_SOURCE
#define SPLICE_F_MOVE	(0x01)	/* move pages instead of copying */
#define SPLICE_F_NONBLOCK (0x02) /* don't block on the pipe splicing (but */
				 /* we may still block on the fd we splice */
				 /* from/to, of course */
#define SPLICE_F_MORE	(0x04)	/* expect more data */
#define SPLICE_F_GIFT	(0x08)	/* pages passed in are a gift */

long tee(int fd_in, int fd_out, size_t len, unsigned int flags) __THROW;

#include <sys/uio.h>

long vmsplice(int fd, const struct iovec *iov, unsigned long nr_segs, unsigned int flags) __THROW;
long splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags) __THROW;

int sync_file_range(int fd, off64_t offset, off64_t nbytes, unsigned int flags) __THROW;

#define FALLOC_FL_KEEP_SIZE 1

int fallocate(int fd, int mode, loff_t offset, loff_t len) __THROW;
#endif

#if defined(_ATFILE_SOURCE) || ((_XOPEN_SOURCE + 0) >= 700) || ((_POSIX_C_SOURCE + 0) >= 200809L)
#define AT_FDCWD		-100    /* Special value used to indicate openat should use the current working directory. */
#define AT_SYMLINK_NOFOLLOW	0x100   /* Do not follow symbolic links.  */
#define AT_REMOVEDIR		0x200   /* Remove directory instead of unlinking file.  */
#define AT_SYMLINK_FOLLOW	0x400   /* Follow symbolic links.  */

int openat(int dirfd, const char *pathname, int flags, ...) __THROW;
int futimesat(int dirfd, const char *pathname, const struct timeval times[2]) __THROW;
int unlinkat(int dirfd, const char *pathname, int flags) __THROW;
#endif

#if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE - 0) >= 600
//#include "linux/fadvise.h"
int posix_fallocate(int fd, off64_t offset, off64_t len) __THROW;
int posix_fadvise(int fd, off64_t offset, off64_t len, int advice) __THROW;
#endif

__END_DECLS

#endif
