#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "xpg3", "sys/types.h" ;
+USE "xpg3", "sys/ipc.h" ;

+SUBSET "sem_proto" := {
    +USE "xpg3", "sys/types.h" ;
    +USE "xpg3", "sys/ipc.h" ;

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
