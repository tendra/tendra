/* $Id$ */

#ifndef __HACKED_TERMIOS_H
#define __HACKED_TERMIOS_H

#ifdef _OPENBSD4
#ifndef _BSD_SOURCE
#define _BSD_SOURCE	/* for XCASE */
#endif
#endif


#include_next <termios.h>

#endif

