# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;
+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "pid_t" ;
+IMPLEMENT "cae/xpg3", "sys/types.h.ts", "key_t" ;

+IMPLEMENT "cae/xsh4-base", "sys/ipc.h.ts" ;

+IMPLEMENT "cae/xpg3", "sys/shm.h.ts", "shm_proto" ;

# These are different from xpg3
+FUNC void *shmat ( int, const void *, int ) ;
+FUNC int shmdt ( const void * ) ;
+FUNC int shmget ( key_t, size_t, int ) ;

/* Define XPG4 hack in terms of my hack */
+TYPEDEF ~shm_nattch_t shmatt_t ;

