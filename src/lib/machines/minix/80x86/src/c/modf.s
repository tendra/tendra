.sect .text; .sect .rom; .sect .data; .sect .bss
.extern _modf
.sect .text
_modf:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	12(ebp)
	push	8(ebp)
	push	1
	push	4
	call	.cif8
	mov	eax, esp
	push	eax
	call	.fif8
	pop	ecx
	mov	edx, 16(ebp)
	pop	ecx
	pop	ebx
	mov	0(edx), ecx
	mov	4(edx), ebx
	fldd	(esp)
	pop	eax
	pop	edx
	pop	ebx
	leave
	ret
.cif8:
	mov	bx,sp
	fildl	8(bx)
	fstpd	4(bx)
	wait
	ret
.fif8:
	mov	bx,sp
	fldd	8(bx)
	fmuld	16(bx)		! multiply
	fld	st		! and copy result
	ftst			! test sign; handle negative separately
	fstsw	ax
	wait
	sahf			! result of test in condition codes
	jb	1f
	frndint			! this one rounds (?)
	fcom	st(1)		! compare with original; if <=, then OK
	fstsw	ax
	wait
	sahf
	jbe	2f
	fisubs	(one)		! else subtract 1
	jmp	2f
1:				! here, negative case
	frndint			! this one rounds (?)
	fcom	st(1)		! compare with original; if >=, then OK
	fstsw	ax
	wait
	sahf
	jae	2f
	fiadds	(one)		! else add 1
2:
	fsub	st(1),st	! subtract integer part
	mov	bx,4(bx)
	fstpd	(bx)
	fstpd	8(bx)
	wait
	ret
