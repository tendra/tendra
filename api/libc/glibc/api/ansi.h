/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifdef _GLIBC2_12
#define __WRONG_ANSI_STDIO_H	/* i don't know what to do about va_list */
#define __WRONG_ANSI_STDARG_H_VA_ARGS	/* i don't know what to do about va_list */
#endif

#ifdef _GLIBC2_14
#define __WRONG_ANSI_FLOAT_H_XPG4_RANGES /* provided by gcc; we need to provide our own */
#endif

