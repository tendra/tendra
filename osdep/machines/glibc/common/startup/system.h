/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    SYSTEM START-UP FILE FOR linux/80x86
    This file defines any built-in macros etc. necessary to traverse the
    system headers correctly.
*/

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA begin
#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : long int
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA longlong type allow
#pragma TenDRA anonymous union allow

/* Put target-dependent macro definitions here */

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(posix)
#unassert lint
#endif

#define unix		1
#define i386		1
#define linux		1
#define __unix		1
#define __i386		1
#define __linux		1
#define __unix__	1
#define __i386__	1
#define __linux__	1
#define __i486__	1

#ifdef __LINUX_USE_ELF
#define __ELF__		1
#define _I386_BYTEORDER_H
#endif

/* macros to match GNU C extensions used in headers */
#ifndef __inline__
#pragma TenDRA keyword __inline__ for inline
#endif

#ifndef __signed__
#define __signed__	signed
#endif

#ifndef __attribute__
#define __attribute__(xyz)
#endif

#ifndef __extension__
#define __extension__
#endif

#endif
