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
#assert machine(alpha)
#assert cpu(alpha)
#assert system(unix)
#assert system(FreeBSD)
#unassert lint
#endif

#define unix		1
#define alpha		1
#define __unix		1
#define __alpha		1
#define __unix__	1
#define __alpha__	1
#define __FreeBSD__	%%__FreeBSD__%%

#ifndef __inline
#pragma TenDRA keyword __inline for inline
#endif

#ifndef __signed
#define __signed	signed
#endif
