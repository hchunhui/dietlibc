#include "dietfeatures.h"
#include "PIC.h"

.text
.global _start
_start:
	jmp 1f
	.byte 'X','B','I','N'
1:
	movl $__bss_start, %edi
	movl $_end, %ecx
	subl $__bss_start, %ecx
	movl $0, %eax
	cld
	rep stosb
	
#ifdef WANT_DYNAMIC
/* in %edx we have the ld.so dynamic _fini ( register this if non null ) */
	push	%edx
#endif

	movl (%esp), %ecx
	movl 4(%esp), %eax
	movl 8(%esp), %esi
	PIC_INIT			/* non-PIC: this is an empty line */
	PUT_VAR %esi, environ, %ecx	/* non-PIC: movl %esi,environ */

#ifdef PROFILING
	pushl	$_etext
	pushl	$.text
	call	monitor
	addl	$0x8, %esp
#endif

#ifdef WANT_DYNAMIC
	call	_dyn_start
#else
	call	CALL_IN_STARTCODE
#endif

#ifdef PROFILING
	pushl	%eax
	call	_stop_monitor
	popl	%eax
#endif
	pushl	%eax
	call	exit
	hlt	/* die now ! will ya ... */
.Lstart:
	.size	 _start,.Lstart-_start

