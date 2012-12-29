
#define __NR_sbrk		7
#define __NR_fork		8
#define __NR_exit		9
#define __NR_get_ticks		10
#define __NR_get_utime		11
#define __NR_get_stime		12
#define __NR_waitpid		13
#define __NR_execve		14
#define __NR_gettime		17
#define __NR_pause		19
#define __NR_getpid		22
#define __NR_getppid		23
#define __NR_shm_get		24
#define __NR_shm_at		25
#define __NR_shm_dt		26
#define __NR_shm_free		27
#define __NR_open		28
#define __NR_read		29
#define __NR_write		30
#define __NR_close		31
#define __NR_nice               32
#define __NR_vfork              33
#define __NR_ioctl              34
#define __NR_dup2               35
#define __NR_mknod              36
#define __NR_readdir		37
#define __NR_fstat		38
#define __NR_lseek		39

#define syscall_weak(name,wsym,sym) \
.text; \
.type wsym,@function; \
.weak wsym; \
wsym: ; \
.type sym,@function; \
.global sym; \
sym: \
	movb $__NR_##name,%al; \
	jmp __unified_syscall; \
.Lend##sym: ; \
.size sym,.Lend##sym-sym

#define syscall(name,sym) \
.text; \
.type sym,@function; \
.global sym; \
sym: \
.ifle __NR_##name-255; \
	movb $__NR_##name,%al; \
	jmp __unified_syscall; \
.else; \
	movw $__NR_##name,%ax; \
	jmp __unified_syscall_256; \
.endif; \
.Lend##sym: ; \
.size sym,.Lend##sym-sym

