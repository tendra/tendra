/ crt1.s version 1.0 for tcc/trans386_Solaris

.file "crt1.s"
.text

.type _start,@function
.globl _start
_start:
 pushl $0		/ null return address
 pushl $0		/ null return frame pointer
 movl %esp,%ebp		/ initial frame pointer

 pushl %edx
 call atexit		/ see System V ABI, p3-32
 popl %eax

 pushl $_fini
 call atexit		/ to call _fini at any sort of exit
 popl %eax

 call __fpstart		/ initialise FPU

 movl 8(%ebp),%eax	/ argc
 leal 16(%ebp,%eax,4),%edx	/ Environment pointers
 movl %edx,_environ	/ preserve for getenv etc
 pushl %edx		/ and 3rd main argument
 leal 12(%ebp),%edx
 pushl %edx		/ argv
 pushl %eax		/ argc
 call _init		/ preserve 3 arguments through _init
 call main
 addl $12,%esp

 pushl %eax
 call exit		/ program exit

 movl $1,%eax
 lcall $7,$0		/ catch-all, see System V ABI, p3-25

.size _start, .-_start
