
#include <dietfeatures.h>
#include <syscalls.h>
.text
.global __unified_syscall_256
.type __unified_syscall_256,@function
__unified_syscall_256:
	movzwl %ax,%eax
	jmp .L1
.L2:
.size __unified_syscall_256,.L2-__unified_syscall_256
.weak exit
exit:
.global _exit
.type	_exit,@function
_exit:
	movb	$__NR_exit,%al
.global __unified_syscall
.type	__unified_syscall,@function
__unified_syscall:
.size _exit,__unified_syscall-_exit
	movzbl	%al, %eax
.L1:
	push	%ebx
	movl	2*4(%esp),%ebx
	movl	3*4(%esp),%ecx
	movl	4*4(%esp),%edx
	int	$0x80
	pop	%ebx
	cmp	$-132,%eax
	jb	.Lnoerror
	neg	%eax
.global __error_unified_syscall
.type	__error_unified_syscall,@function
__error_unified_syscall:
#ifdef WANT_THREAD_SAFE
	push	%eax
	call	__errno_location
	pop	(%eax)
	orl	$-1,%eax
#else
	mov	%eax,errno
	sbb	%eax,%eax               # eax = eax - eax - CY = -1
#endif
.Lnoerror:

/* here we go and "reuse" the return for weak-void functions */
#include "dietuglyweaks.h"

	ret
