/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAXMINMACS_H
#define MAXMINMACS_H

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define max(a,b)	(((a)>=(b)) ? (a) : (b))
#define min(a,b)	(((a)<=(b)) ? (a) : (b))
#define absval(a)	(((a)<0) ? -(a) : (a))

#endif /* maxminmacs.h */
