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
    SYSTEM START-UP FILE FOR irix/mips

    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : long
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed

#define __mips		1
#define mips		1
#define __sgi		1
#define sgi		1
#define LANGUAGE_C	1
#define _LANGUAGE_C	1
#define MIPSEB		1
#define _MIPSEB		1
#define IRIX		1
#define _IRIX		1
#define _MIPS_SZINT	32
#define _MIPS_SZLONG	32
#define _MIPS_SZPTR	32
#define _MIPS_ISA	_MIPS_ISA_MIPS1
#define _SVR4_SOURCE	1

#endif
