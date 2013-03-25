/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR osf1/alpha
    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA set size_t : unsigned long
#pragma TenDRA set wchar_t : unsigned int
#pragma TenDRA set ptrdiff_t : long
#pragma TenDRA character signed

#define __alpha         1
#define alpha           1
#define LANGUAGE_C      1
#define __LANGUAGE_C    1
#define __LANGUAGE_C__  1
#define __osf__         1
#define unix            1
#define __unix__        1
#define _SYSTYPE_BSD    1
#define _CFE            1

#endif
