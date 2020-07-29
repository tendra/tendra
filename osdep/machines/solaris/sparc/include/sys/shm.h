/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _HACKED_SYS_SHM_H
#define _HACKED_SYS_SHM_H

#include <sys/param.h>

#ifdef __BUILDING_LIBS
#define shmctl	shmctl_wrong
#define uint_t	int
#endif

#include_next <sys/shm.h>

#ifdef __BUILDING_LIBS
#undef shmctl
#undef uint_t
extern int shmctl ( int, int, struct shmid_ds * ) ;
#endif

#endif
