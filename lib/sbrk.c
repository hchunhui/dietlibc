#include <unistd.h>
#include <errno.h>

void* __curbrk=0;

int __libc_brk(void *end_data_segment);
void* __libc_sbrk(ptrdiff_t increment);

void* __libc_sbrk(ptrdiff_t increment) {
	if((__curbrk = __diet_sbrk(increment))==(void *)-1)
		errno = ENOMEM;
	return __curbrk;
}

int __libc_brk(void *end_data_segment) {
	return __libc_sbrk(end_data_segment-__curbrk);
}

void* sbrk (ptrdiff_t increment) __attribute__((weak,alias("__libc_sbrk")));
int brk(void *end_data_segment) __attribute__((weak,alias("__libc_brk")));
