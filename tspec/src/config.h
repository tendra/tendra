/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_H
#define CONFIG_H

/*
 * ANSI API SPECIFICATION
 *
 * The API for this program is ANSI.  This defines the basic interface,
 * and utility.c includes stdarg.h (or varargs.h).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * HACKS FOR BAD API IMPLEMENTATIONS
 *
 * These values are meant to be in the headers above, but sometimes
 * they are omitted.
 */

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#ifdef __MSDOS__
#define FS_NO_MODE_T 1
#endif

/*
 * COMPILER DEPENDENT MACROS
 */

#include "ossg.h"

/*
 * BASIC TYPES
 *
 * These types are so ubiquitous that this is the only suitable place
 * for them.
 */

typedef char boolean;

#endif

