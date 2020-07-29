/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR solaris/sparc
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
#assert machine(sparc)
#assert cpu(sparc)
#assert system(unix)
#unassert lint
#endif

#ifndef __ANSI__
#undef __STDC__
#define __STDC__	0
#define sparc		1
#define sun		1
#define unix		1
#define __sparc		1
#define __sun		1
#define __svr4		1
#define __unix		1
#define __sparc__	1
#define __sun__		1
#define __svr4__	1
#define __unix__	1
#define _NO_LONGLONG	1
#endif

#endif
