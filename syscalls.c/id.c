#include <sys/types.h>
#include <errno.h>

uid_t getuid()
{
		return 0;
}

uid_t geteuid()
{
		return 0;
}

gid_t getgid()
{
		return 0;
}

gid_t getegid()
{
		return 0;
}

int getgroups(int size, gid_t list[])
{
		return 0;
}

int setuid(uid_t uid)
{
	errno = EPERM;
	return -1;
}

int setgid(gid_t gid)
{
	errno = EPERM;
	return -1;
}

int setreuid(uid_t ruid, uid_t euid)
{
	errno = EPERM;
	return -1;
}

int setregid(gid_t rgid, gid_t egid)
{
	errno = EPERM;
	return -1;
}

