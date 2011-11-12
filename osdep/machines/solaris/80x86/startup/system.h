/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR solaris/80x86
    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA begin
#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : long
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#unassert lint
#endif

#ifndef __ANSI__
#undef __STDC__
#define __STDC__	0
#define i386		1
#define __i386		1
#define unix		1
#define __unix		1
#define _NO_LONGLONG	1
#endif

#endif
