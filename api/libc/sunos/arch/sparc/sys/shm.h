/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_SYS_SHM_INCLUDED
#define __HACKED_SYS_SHM_INCLUDED

#ifdef __BUILDING_LIBS
#define uint	int
#endif

#include_next <sys/shm.h>

extern char *shmat () ;

#ifdef __BUILDING_LIBS
#undef uint
#endif

#endif
