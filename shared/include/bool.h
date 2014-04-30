/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SHARED_BOOL_H
#define SHARED_BOOL_H

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L
typedef _Bool bool;
#else
typedef int bool;
#endif

#endif

