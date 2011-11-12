/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR ultrix/mips
    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : unsigned int
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed

#define __mips		1
#define mips		1
#define LANGUAGE_C	1
#define __LANGUAGE_C	1
#define MIPSEL		1
#define __MIPSEL	1
#define unix		1
#define __unix		1
#define ultrix		1
#define __ultrix	1

#endif
