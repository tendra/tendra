/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
