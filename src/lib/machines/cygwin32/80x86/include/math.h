#ifndef __HACKED_MATH_INCLUDED
#define __HACKED_MATH_INCLUDED

#include_next <math.h>

#ifndef MAXFLOAT
#include <float.h>
#define MAXFLOAT	FLT_MAX
#endif

#endif
