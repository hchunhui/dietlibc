#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <endian.h>
#include <os/stat.h>

__BEGIN_DECLS

#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

extern int stat(const char *__file, struct stat *__buf) __THROW;
extern int fstat(int __fd, struct stat *__buf) __THROW;
extern int lstat(const char *__file, struct stat *__buf) __THROW;

#define __NO_STAT64

#define major(dev) ({ unsigned long long l=(dev); ((l>>8) & 0xfff) | (l >> 32) & 0xfffff000; })
#define minor(dev) ({ unsigned long long l=(dev); (l & 0xff) | ((l>>12)&0xffffff00); })
#define makedev(maj,min) ({ unsigned long long a=(maj), i=(min); ((a&0xfff)<<8) | (i&0xff) | ((a&~0xfff)<<32) | ((i&0xfffff00)<<12); })

extern int chmod (const char *__file, mode_t __mode) __THROW;
extern int fchmod (int __fd, mode_t __mode) __THROW;
extern mode_t umask (mode_t __mask) __THROW;
extern int mkdir (const char *__path, mode_t __mode) __THROW;
extern int mknod (const char *__path, mode_t __mode, dev_t __dev) __THROW;
extern int mkfifo (const char *__path, mode_t __mode) __THROW;

#if defined(_ATFILE_SOURCE) || ((_XOPEN_SOURCE + 0) >= 700) || ((_POSIX_C_SOURCE + 0) >= 200809L)
/* also include fcntl.h for the AT_* constants */

int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags) __THROW;
int fstatat(int dirfd, const char *pathname, struct stat *buf, int flags) __THROW;
int mkdirat(int dirfd, const char *pathname, mode_t mode) __THROW;
int mknodat(int dirfd, const char *pathname, mode_t mode, dev_t dev) __THROW;
int mkfifoat(int dirfd, const char *pathname, mode_t mode) __THROW;
int utimensat(int dirfd, const char *pathname, struct timespec* t,int flags) __THROW;
#endif

__END_DECLS

#endif
