/* $Id$ */

#include "ansi.h"

#define _XOPEN_SOURCE
#define _XOPEN_VERSION	4


#ifdef _OPENBSD4
#define __WRONG_XPG4_LANGINFO_H	/* partial (TODO: move to subset?) */
#define __WRONG_XPG4_LIMITS_H	/* partial (TODO: just CHARCLASS_NAME_MAX missing; move to subset) */
#define __WRONG_XPG4_SEARCH_H_SRCH_PROTO	/* incompatible (TODO: just lsearch; move to subset) */
#define __WRONG_XPG4_SEARCH_H	/* incompatible (TODO: just lsearch; move to subset) */
#define __WRONG_XPG4_UNISTD_H	/* incompatible (TODO: just swab; move to subset) */
#define __WRONG_XPG4_WCHAR_H	/* incompatible (TODO: just wcstok; move to subset) */
#endif

