#ifndef __HACKED_STRING_INCLUDED
#define __HACKED_STRING_INCLUDED

/* Suppress __std_hdr_* definitions */
#define strlen		strlen
#define strcpy		strcpy
#define strncpy		strncpy

#include_next <string.h>


#endif
