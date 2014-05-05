/* $Id: c89.h 2473 2010-12-24 22:32:39Z kate $ */

#pragma TenDRA begin
#pragma TenDRA directive include_next allow
#pragma TenDRA longlong type allow
#pragma TenDRA no external declaration allow
#pragma TenDRA directive warning allow

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(Haiku)
#unassert lint
#endif

#define __unix		1
#define __i386		1
#define __unix__	1
#define __i386__	1
#define __HAIKU__	1



/*
 * Provided for headers/config/HaikuConfig.h to pick up.
 */
#define __INTEL__ 1


/*
 * Provided to keep headers/os/BeBuild.h quiet; it wants to know this in order
 * to determine which GCC ABI to specify.
 *
 * Instead of this, we should pretend to be __GNUC__ 4; that would remove the
 * problem with HUGE_VALF and friends in headers/posix/math.h. Then we would be
 * expected to provide token definitions for (say) __builtin_huge_valf; that
 * would live alongside the other machine-dependent .tpl in tokens/.
 */
#define __GNUC__ 2


#ifdef _HAIKU1
typedef long ssize_t;	/* see headers/posix/size_t.h */
#endif


/* TODO: this should be in the include/ hacks; see stdio_pre.h */
#ifdef _HAIKU1
#define _STDIO_PRE_H_
#include <libio.h>

typedef struct _IO_FILE FILE;

#define __PRINTFLIKE(format, varargs)
#define __SCANFLIKE(format, varargs)
#endif

