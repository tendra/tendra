/*
 * Copyright 2011-2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#if defined(_GLIBC2_14) || defined(_GLIBC2_31) \
	|| defined(_GLIBC2_32)
#define __WRONG_C89_FLOAT_H_XPG4_RANGES /* provided by gcc; we need to provide our own */
#endif

