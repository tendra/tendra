/* $Id$ */

#include "ansi.h"

#define _XOPEN_SOURCE

#ifdef _OPENBSD4
#ifndef __semun_defined
#define __semun_defined	/* for *.api/sem.c */
#endif
#endif


#ifdef _OPENBSD4
#define __WRONG_XPG3_SEARCH_H_SRCH_PROTO	/* incompatible (TODO: just lsearch; move to subset) */
#define __WRONG_XPG3_SEARCH_H	/* incompatible (TODO: just lsearch; move to subset) */
#define __WRONG_XPG3_SYS_SEM_H	/* incompatible (elipsis) */
#define __WRONG_XPG3_TERMIOS_H	/* partial (TODO: move to subset) */
#define __WRONG_XPG3_UNISTD_H_U_PLUS	/* partial */
#endif

