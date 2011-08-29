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


/*
 * XXX: this ought to be done properly, but I can't quite find a way to get it
 * to work using the hacked includes mechanism.
 * The problem is machine/_types.h:45 typedef __signed char __int8_t;
 * Where __signed is not defined. This happens just because <math.h> includes
 * <sys/_types.h> before <sys/cdefs.h>. So, instead of having a hacked include
 * for math.h to do that, we do it here.
 */
#if defined(_OPENBSD4) || defined(_OPENBSD5)
#include <sys/cdefs.h>
#endif

#ifdef _OPENBSD5
#define __WRONG_ANSI_STDARG_H_VA_ARGS	/* parse error in va_arg, to investigate later */
#endif

