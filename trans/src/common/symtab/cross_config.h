/*
 * Copyright 2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __CROSS_CONFIG_INCLUDED
#define __CROSS_CONFIG_INCLUDED

#ifdef __ultrix
#ifndef __ANSI_COMPAT
#define __ANSI_COMPAT
#ifndef CROSS_INCLUDE
#include <ansi_compat.h>
#else
#include CROSS_INCLUDE/ansi_compat.h>
#endif
#endif
#endif

#ifndef __LANGUAGE_C__
#define __LANGUAGE_C__	1
#endif

#endif
