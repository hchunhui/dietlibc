#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <utime.h>
#include <sys/utsname.h>

int dup(int old)
{
	return dup2(old, -1);
}

int access(const char *path, int mode)
{
	return 0;
}

int mkdir(const char *path, mode_t mode)
{
	return 0;
}

int rmdir(const char *path)
{
	return 0;
}

int chmod(const char *path, mode_t mode)
{
	return 0;
}

int fchmod(int fd, mode_t mode)
{
	return 0;
}

int chown(const char *path, uid_t owner, gid_t grp)
{
	return 0;
}


int link(const char *old, const char *new)
{
	errno = EMLINK;
	return -1;
}

int unlink(const char *name)
{
	errno = ENOENT;
	return -1;
}

int rename(const char *old, const char *new)
{
	errno = ENOENT;
	return -1;
}

int symlink(const char *a, const char *b)
{
	errno = ENOENT;
	return -1;
}

int mknod(const char *pathname, mode_t mode, dev_t dev)
{
	errno = ENOENT;
	return -1;
}

int mkfifo(const char *pathname, mode_t mode)
{
        errno = ENOENT;
        return -1;
}

int ftruncate(int fd, off_t length)
{
	errno = ENOENT;
	return -1;
}

int readlink(const char *pathname, char *buf, size_t bufsiz)
{
	errno = ENOENT;
	return -1;
}

int utime(const char *file, const struct utimbuf *times)
{
	return 0;
}

int uname(struct utsname *buf)
{
	strcpy(buf->sysname, "myos");
	strcpy(buf->nodename, "local");
	strcpy(buf->release, "2");
	strcpy(buf->version, "2");
	strcpy(buf->machine, "i386");
	strcpy(buf->domainname, "local");
	return 0;
}

char *ttyname(int fd)
{
	errno = ENOTTY;
	return "";
}

unsigned int alarm(unsigned int seconds)
{
	return seconds;
}

