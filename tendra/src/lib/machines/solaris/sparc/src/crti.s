! crti.s version 1.0

	.file		"crti.s"
	.section	".init"
	.proc	022
	.global	_init
	.type	_init,#function
	.align	4
_init:
	save	%sp, -0x60, %sp

	.section	".fini"
	.proc	022
	.global	_fini
	.type	_fini,#function
	.align	4
_fini:
	save	%sp, -0x60, %sp
