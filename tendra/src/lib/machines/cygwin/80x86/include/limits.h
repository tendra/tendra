#ifndef __HACKED_LIMITS_INCLUDED
#define __HACKED_LIMITS_INCLUDED

#include_next <limits.h>

#ifndef NGROUPS_MAX
#define NGROUPS_MAX		8
#endif

#ifndef NL_ARGMAX
#define NL_ARGMAX		9
#endif

#ifndef NL_LANGMAX
#define NL_LANGMAX		14
#endif

#ifndef NL_MSGMAX
#define NL_MSGMAX		32767
#endif

#ifndef NL_NMAX
#define NL_NMAX			1
#endif

#ifndef NL_SETMAX
#define NL_SETMAX		255
#endif

#ifndef NL_TEXTMAX
#define NL_TEXTMAX		255
#endif

#ifndef NZERO
#define NZERO			20
#endif

#ifndef WORD_BIT
#define WORD_BIT		32
#endif

#ifndef LONG_BIT
#define LONG_BIT		32
#endif

#ifndef _POSIX_SSIZE_MAX
#define _POSIX_SSIZE_MAX	LONG_MAX
#endif

#ifndef _POSIX_STREAM_MAX
#define _POSIX_STREAM_MAX	32
#endif

#ifndef _POSIX_TZNAME_MAX
#define _POSIX_TZNAME_MAX	32
#endif

#endif
