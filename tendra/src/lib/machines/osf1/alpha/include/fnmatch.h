#ifndef __HACKED_FNMATCH_INCLUDED
#define __HACKED_FNMATCH_INCLUDED

#include_next <fnmatch.h>

#ifdef FNM_NOSYS
#undef FNM_NOSYS
#define FNM_NOSYS	4
#endif

#endif
