#ifndef __HACKED_TIME_INCLUDED
#define __HACKED_TIME_INCLUDED

#include_next <time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC	1000000
#endif

#ifndef CLK_TCK
#define CLK_TCK		60
#endif

#endif
