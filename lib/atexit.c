#include <stdlib.h>
#include <unistd.h>

int __cxa_atexit(void (*f)(void *), void *p, void *d);
void __cxa_finalize(void *d);

struct object
{
	void (*f)(void*);
	void *p;
	void *d;
} object[64];
unsigned int __cxa_atexit_count = 0;

int __cxa_atexit(void (*f)(void *), void *p, void *d)
{
	if (__cxa_atexit_count >= 64) return -1;
	object[__cxa_atexit_count].f = f;
	object[__cxa_atexit_count].p = p;
	object[__cxa_atexit_count].d = d;
	++__cxa_atexit_count;
	return 0;
}

/* This currently destroys all objects */
void __cxa_finalize(void *d)
{
	unsigned int i = __cxa_atexit_count;
	if(d)
	{
		return;
	}
	for (; i > 0; --i)
	{
		--__cxa_atexit_count;
		object[__cxa_atexit_count].f(object[__cxa_atexit_count].p);
        }
}

int atexit(void (*t)()) {
  return __cxa_atexit(t, NULL, NULL);
}

extern void __thread_doexit(int doexit);

void __libc_exit(int code);
void __libc_exit(int code) {
  __thread_doexit(code);
  __cxa_finalize(NULL);
  _exit(code);
}
void exit(int code) __attribute__((alias("__libc_exit")));
