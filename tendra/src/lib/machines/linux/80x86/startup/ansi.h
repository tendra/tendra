#pragma TenDRA begin
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow
#pragma TenDRA longlong type allow
#pragma TenDRA extra type definition allow
#pragma TenDRA no external declaration allow
#pragma TenDRA incompatible type qualifier allow
#pragma TenDRA unknown directive allow

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
#define _EXTERN_INLINE extern __inline__

#ifndef __signed__
#define __signed__	signed
#endif

#ifndef __attribute__
#define __attribute__(xyz)
#endif

/* gcc has alloca builtin */
#include <alloca.h>
