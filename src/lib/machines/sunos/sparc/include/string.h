#ifndef __HACKED_STRING_INCLUDED
#define __HACKED_STRING_INCLUDED

#include_next <string.h>

#ifndef strerror
extern char *sys_errlist [] ;
#define strerror( N )   sys_errlist [ ( N ) ]
#endif

#endif
