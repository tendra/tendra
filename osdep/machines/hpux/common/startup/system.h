/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR hpux/hppa
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

#define __hp9000s700	1
#define __hp9000s800	1
#define _HPUX_SOURCE	1
#define __hpux		1

#endif
