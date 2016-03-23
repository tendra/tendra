/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * tdf.h - Miscellaneous TDF routines.
 *
 * See the file "tdf.c" for more information.
 */

#ifndef H_TDF
#define H_TDF

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>

#define U_USED			((unsigned)(0x01))
#define U_DECD			((unsigned)(0x02))
#define U_DEFD			((unsigned)(0x04))
#define U_MULT			((unsigned)(0x08))
#define U_HIDE			((unsigned)(0x10))

extern size_t			tdf_int_size
(unsigned);
extern void			write_usage
(OStreamT *, unsigned);

#endif /* !defined (H_TDF) */
