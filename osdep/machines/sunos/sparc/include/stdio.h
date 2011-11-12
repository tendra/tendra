/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_STDIO_INCLUDED
#define __HACKED_STDIO_INCLUDED

#ifdef __BUILDING_LIBS
#define sprintf		__sprintf_wrong
#endif

#include_next <stdio.h>

#ifdef __BUILDING_LIBS
#undef sprintf
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

typedef long fpos_t ;

#ifndef FILENAME_MAX
#define FILENAME_MAX 255
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX 60
#endif

#ifndef TMP_MAX
#define TMP_MAX 10000
#endif

#endif
