#pragma TenDRA begin
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow
#pragma TenDRA longlong type allow
#pragma TenDRA extra type definition allow
#pragma TenDRA no external declaration allow
#pragma TenDRA incompatible type qualifier allow

/* Put target-dependent macro definitions here */

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(winnt)
#unassert lint
#endif

#define i386		1
#define __i386		1
#define __i386__	1
#define _X86_		1
#define _WIN32		1
#define __CYGWIN32__	1
#define __WINNT		1

/* macros to match GNU C extensions used in headers */

#ifndef __inline__
#pragma TenDRA keyword __inline__ for inline
#endif

#ifndef __signed__
#define __signed__	signed
#endif

#ifndef __attribute__
#define __attribute__(p)
#endif

/* gcc has alloca builtin */
#include <alloca.h>
