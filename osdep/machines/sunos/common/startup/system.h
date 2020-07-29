/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR sunos/680x0
    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA set size_t : unsigned int	/* Thanks, Sun */
#pragma TenDRA set wchar_t : unsigned short
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed

#define unix		1
#define sun		1
#define mc68000         1
#define mc68020         1

#endif
