/* $Id$ */

#define _ANSI_SOURCE   1

#pragma TenDRA begin
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow
#pragma TenDRA longlong type allow
#pragma TenDRA no external declaration allow

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(NetBSD)
#unassert lint
#endif

/* TODO: could move these out to their own API; they don't really belong here */
#define __unix		1
#define __i386		1
#define __unix__	1
#define __i386__	1
#define __NetBSD__	2

