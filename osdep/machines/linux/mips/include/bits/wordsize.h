/* $Id$ */

#ifndef __HACKED_BITS_WORDSIZE_H
#define __HACKED_BITS_WORDSIZE_H

/* for __WORDSIZE */
#if defined(_EGLIBC2_11)
#define _MIPS_SZPTR 32
#endif

#include_next <bits/wordsize.h>

#endif

