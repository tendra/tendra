# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "xpg4", "sys/types.h.ts" ;
+USE "xpg4", "sys/ipc.h.ts" ;
+IMPLEMENT "xpg3", "sys/sem.h.ts", "sem_proto" ;

# These are different from xpg3
+FUNC int semctl ( int, int, int, ... ) ;
+FUNC int semop ( int, struct sembuf *, size_t ) ;
