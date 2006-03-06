#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow

/* tcc is supposed to define this, but we do it just in case ...
   (this is important to enable ansi features, see /usr/include/ansi.h) */

#define __STDC__	1

/* the following definitions are inspired by what ACK does (_EM_*SIZE macros
   are used by many ansi and posix headers) */

#define __minix		1
#define __i386		1

#define _EM_WSIZE	4
#define _EM_PSIZE	4
#define _EM_SSIZE	2
#define _EM_LSIZE	4
#define _EM_FSIZE	4
#define _EM_DSIZE	8

/* this is needed at some places, but it's done only if __ACK__ is defined
   (see minix/(sys_)config.h), so we must do it explicitly */

#define _WORD_SIZE	_EM_WSIZE
#define _PTR_SIZE	_EM_PSIZE

/* finally, standard definitions for all Unix-like systems */

#define unix		1
#define __unix		1
