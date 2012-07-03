/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __TDF_SYS_INCLUDED
#define __TDF_SYS_INCLUDED

#include <Xsystem>

#pragma TenDRA begin
#pragma TenDRA set size_t : unsigned int
#pragma TenDRA set wchar_t : int
#pragma TenDRA set ptrdiff_t : int
#pragma TenDRA character signed
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA longlong type allow
#pragma TenDRA directive warning allow

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(OpenBSD)
#unassert lint
#endif

#define __unix		1
#define __i386		1
#define __unix__	1
#define __i386__	1
#define __OpenBSD__	2

#endif

