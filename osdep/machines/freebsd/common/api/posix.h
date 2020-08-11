/*
 * Copyright 2012, 2013, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */
 
#if defined(_FREEBSD8_3) \
	|| defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) \
	|| defined(_FREEBSD10_1) || defined(_FREEBSD10_2) || defined(_FREEBSD10_3) \
	|| defined(_FREEBSD10_4) \
	|| defined(_FREEBSD11_0) || defined(_FREEBSD11_1) || defined(_FREEBSD11_2) \
	|| defined(_FREEBSD11_3)
#define __WRONG_POSIX_UNISTD_H_SAVED_IDS /* not implemented */
#endif

