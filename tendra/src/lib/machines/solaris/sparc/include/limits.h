#ifndef _HACKED_LIMITS_H
#define _HACKED_LIMITS_H

#include_next <limits.h>

/* This isn't defined, so give it it's minimum value */
#ifndef CHARCLASS_NAME_MAX
#define CHARCLASS_NAME_MAX	14
#endif

#endif
