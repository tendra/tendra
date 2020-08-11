#ifndef __HACKED_SYS_SIGNAL_H
#define __HACKED_SYS_SIGNAL_H

/* for SIG_IGN and SIG_ERR */
#if defined(_FREEBSD8_3) \
	|| defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) \
	|| defined(_FREEBSD10_1) || defined(_FREEBSD10_2) || defined(_FREEBSD10_3) \
	|| defined(_FREEBSD10_4) \
	|| defined(_FREEBSD11_0) || defined(_FREEBSD11_1) || defined(_FREEBSD11_2) \
	|| defined(_FREEBSD11_3)
#pragma TenDRA begin
#pragma TenDRA conversion analysis ( int-pointer explicit ) off
#endif

#include_next <sys/signal.h>

#if defined(_FREEBSD8_3) \
	|| defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) \
	|| defined(_FREEBSD10_1) || defined(_FREEBSD10_2) || defined(_FREEBSD10_3) \
	|| defined(_FREEBSD10_4) \
	|| defined(_FREEBSD11_0) || defined(_FREEBSD11_1) || defined(_FREEBSD11_2) \
	|| defined(_FREEBSD11_3)
#pragma TenDRA end
#endif

#endif

