/*
 * $TenDRA$
 */

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
#assert system(FreeBSD)
#unassert lint
#endif

#define unix		1
#define i386		1
#define __unix		1
#define __i386		1
#define __unix__	1
#define __i386__	1
#define __FreeBSD__	%%__FreeBSD__%%

#ifndef __inline
#pragma TenDRA keyword __inline for inline
#endif

#ifndef __signed
#define __signed	signed
#endif

/* Work around __aligned() and __attribute__()*/
#ifndef	__aligned
#define	__aligned(x)	/* nothing */
#endif
#ifndef	__attribute__
#define	__attribute__(x)	/* nothing */
#endif
