# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "xpg4", "sys/types.h.ts" ;
+USE "xpg4", "sys/ipc.h.ts" ;
+IMPLEMENT "xpg3", "sys/shm.h.ts", "shm_proto" ;

# These are different from xpg3
+FUNC void *shmat ( int, const void *, int ) ;
+FUNC int shmdt ( const void * ) ;
+FUNC int shmget ( key_t, size_t, int ) ;

/* Define XPG4 hack in terms of my hack */
+TYPEDEF ~shm_nattch_t shmatt_t ;
