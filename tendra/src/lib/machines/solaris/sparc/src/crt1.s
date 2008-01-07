! crt1.s version 1.0

	.section	".text"
	.proc		022
	.global	_start
_start:
	mov	0, %fp		
	ld	[%sp + 0x40], %l0	
	add	%sp, 0x44, %l1	
	sub	%sp, 0x20, %sp
	orcc	%g0, %g1, %g0
	be	.no_exit_fn
	mov	%g1, %o0
	call	atexit
	nop   
.no_exit_fn:
	set	_fini, %o0
	call	atexit, 1
	nop
	call	_init, 0
	nop
	mov	%l0, %o0	
	mov	%l1, %o1	
	add	%l0, 1, %o2
	sll	%o2, 2, %o2
	add	%l1, %o2, %o2	
	set	_environ, %o3
	st	%o2, [%o3]	
	call	main, 4
	nop   
	call	exit, 0
	nop   
	call	_exit, 0
	nop   
	.type	_start,#function
	.size	_start,.-_start
