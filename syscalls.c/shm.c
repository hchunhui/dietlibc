#include <errno.h>
#include <os/unistd.h>
#include <os/shm.h>

int shm_at(int key, unsigned long base_addr, unsigned int flag)
{
	return usr_sys_call3(__NR_shm_at, key, base_addr, flag);
}

int shm_dt(int key, unsigned long base_addr)
{
	return usr_sys_call2(__NR_shm_dt, key, base_addr);
}

int shm_get(int key, unsigned long size)
{
	return usr_sys_call2(__NR_shm_get, key, size);
}

int shm_free(int key)
{
	return usr_sys_call1(__NR_shm_free, key);
}

