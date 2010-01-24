/* $Id$ */

#ifndef __HACKED_CTYPE_H
#define __HACKED_CTYPE_H

#include_next <ctype.h>


#ifdef _OPENBSD4
#ifdef __BUILDING_TDF_XPG3_CTYPE_H
#ifdef _toupper
#undef _toupper
#endif
#define _toupper(c)	__toupper((c))	/* missing */
#endif
#endif

#ifdef _OPENBSD4
#ifdef __BUILDING_TDF_XPG3_CTYPE_H
#ifdef _tolower
#undef _tolower
#endif
#define _tolower(c)	__tolower((c))	/* missing */
#endif
#endif

#endif

