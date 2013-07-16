#include "syscalls.h"
.text
.global vfork
.type	vfork,@function
vfork:
	popl %edx
	xorl %eax,%eax
	movb $__NR_vfork, %al
	int $0x80
	jmpl *%edx
.size vfork, . - vfork
