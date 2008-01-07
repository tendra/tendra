/* $TenDRA$ */

#ifndef __HACKED_MATH_INCLUDED
#define __HACKED_MATH_INCLUDED

#pragma TenDRA begin
#pragma TenDRA error "cpp_replace_arg_empty" off
#define __NO_MATH_INLINES
#include_next <math.h>
#pragma TenDRA end

#ifndef MAXFLOAT
#include <float.h>
#define MAXFLOAT	FLT_MAX
#endif

#endif
