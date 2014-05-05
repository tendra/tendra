# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "xpg3", "sys/types.h.ts" ;
+USE "xpg3", "sys/ipc.h.ts" ;

+SUBSET "sem_proto" := {
    +USE "xpg3", "sys/types.h.ts" ;
    +USE "xpg3", "sys/ipc.h.ts" ;

    +CONST short SEM_UNDO ;
    +CONST int GETNCNT, GETPID, GETVAL, GETALL, GETZCNT, SETVAL, SETALL ;

    +FIELD struct semid_ds {
	struct ipc_perm sem_perm ;
	unsigned short sem_nsems ;
	time_t sem_otime ;
	time_t sem_ctime ;
    } ;

    +IF 0
    +FIELD struct ~unnamed {
	unsigned short semval ;
	pid_t sempid ;
	unsigned short semncnt ;
	unsigned short semzcnt ;
    } ;
    +ENDIF

    +FIELD struct sembuf {
	unsigned short sem_num ;
	short sem_op ;
	short sem_flg ;
    } ;

    +FUNC int semget ( key_t, int, int ) ;
} ;

+FIELD union semun {
    int val ;
    struct semid_ds *buf ;
    unsigned short *array ;
} ;

+IFNDEF ~building_libs
+FUNC int semctl ( int, int, int, union semun ) ;
+ELSE
+IFNDEF __semun_defined
+FUNC int __old_semctl | semctl.1 ( int, int, int, union semun ) ;
+ELSE
+FUNC int semctl.2 ( int, int, int, union semun ) ;
+ENDIF
+ENDIF

%%%
#ifndef __semun_defined
union semun {
    int val ;
    struct semid_ds *buf ;
    unsigned short *array ;
} ;

#define __old_semctl( A, B, C, D )	semctl ( A, B, C, D )
#endif
%%%

+FUNC int semop ( int, struct sembuf *, unsigned ) ;
