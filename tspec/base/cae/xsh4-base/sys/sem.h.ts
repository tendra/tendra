# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;
+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "pid_t" ;
+IMPLEMENT "cae/xpg3", "sys/types.h.ts", "key_t" ;

+IMPLEMENT "cae/xpg3", "sys/sem.h.ts", "sem_proto" ;
+IMPLEMENT "cae/xsh4-base", "sys/ipc.h.ts" ;

# These are different from xpg3
+FUNC int semctl ( int, int, int, ... ) ;
+FUNC int semop ( int, struct sembuf *, size_t ) ;

