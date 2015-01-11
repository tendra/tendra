/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_SYS_SHM_INCLUDED
#define __HACKED_SYS_SHM_INCLUDED

#ifdef __BUILDING_LIBS
#define smem		shmid_ds
#define sminfo		shminfo
#define smmax		shmmax
#define smmin		shmmin
#define smmni		shmmni
#define smseg		shmseg
#define smbrk		shmbrk
#include <machine/pte.h>
#include <sys/param.h>
#endif

#include_next <sys/shm.h>

#ifdef __BUILDING_LIBS
#undef shmid_ds
#undef shminfo
#undef shmmax
#undef shmmin
#undef shmmni
#undef shmseg
#undef shmbrk
#endif

#endif
