/ crti.s version 1.0 for tcc/trans386_Solaris

.file "crti.s"
.text

.section .init
.type _init,@function
.globl _init
.align 16
_init:

.section .fini
.type _fini,@function
.globl _fini
.align 16
_fini:
