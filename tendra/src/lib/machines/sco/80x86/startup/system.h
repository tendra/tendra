/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/
/*
    SYSTEM START-UP FILE FOR sco/80x86

    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : int
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed

#define M_I86		1
#define M_I86SM		1
#define M_SDATA		1
#define M_STEXT		1
#define M_I386		1
#define M_XENIX		1
#define M_BITFIELDS	1
#define M_INTERNAT	1
#define M_UNIX		1
#define M_COFF		1
#define M_SYS5		1
#define M_SYSV		1
#define M_SYS3		1
#define M_SYSIII	1
#define M_WORDSWAP	1

#define _M_I86		1
#define _M_I86SM	1
#define _M_SDATA	1
#define _M_STEXT	1
#define _M_I386		1
#define _M_XENIX	1
#define _M_BITFIELDS	1
#define _M_INTERNAT	1
#define _M_UNIX		1
#define _M_COFF		1
#define _M_SYS5		1
#define _M_SYSV		1
#define _M_SYS3		1
#define _M_SYSIII	1
#define _M_WORDSWAP	1

#define i386		1
#define __i386		1
#define unix		1
#define __unix		1

#undef __STDC__
#define __STDC__	0

#endif
