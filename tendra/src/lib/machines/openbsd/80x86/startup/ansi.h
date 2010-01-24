/* $Id$ */

#pragma TenDRA begin
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow
#pragma TenDRA longlong type allow
#pragma TenDRA no external declaration allow
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

