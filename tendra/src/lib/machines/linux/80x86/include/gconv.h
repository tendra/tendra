/* $TenDRA$ */

#ifndef __HACKED_GCONV_H_INCLUDE
#define __HACKED_GCONV_H_INCLUDE

/* _G_config.h puts a flexible-array-member struct in another struct,
 * work around */
#undef __flexarr
#define __flexarr [1]

#include_next <gconv.h>

/* Redefine to old value */
#undef __flexarr
#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#define __flexarr []
#else
#define __flexarr [1]
#endif

#endif
