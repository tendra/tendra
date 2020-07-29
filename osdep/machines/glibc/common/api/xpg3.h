/*
 * Copyright 2011-2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifdef _GLIBC2_14
#define __WRONG_XPG3_SYS_SHM_H_SHM_PROTO /* incompatible shm.shmid_ds.shm_segsz */
#define __WRONG_XPG3_SYS_SEM_H_SEM_PROTO /* incompatible sem.semid_ds.sem_nsems */
#define __WRONG_XPG3_SYS_SEM_H /* incompatible sem.semid_ds.sem_nsems */
#endif

