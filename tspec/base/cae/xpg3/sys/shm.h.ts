# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/types.h.ts" ;
+USE "cae/xpg3", "sys/ipc.h.ts" ;

+SUBSET "shm_proto" := {
    +USE "cae/xpg3", "sys/types.h.ts" ;
    +USE "cae/xpg3", "sys/ipc.h.ts" ;

    +EXP int SHMLBA ;
    +CONST int SHM_RDONLY, SHM_RND ;

    /* This is unsigned short in xpg3, unsigned long in sysv */
    +IF %% __STRICT_SYSV %%
    +TYPEDEF unsigned long ~shm_nattch_t ;
    +ELSE
    +IF %% __STRICT_XPG3 %%
    +TYPEDEF unsigned short ~shm_nattch_t.1 ;
    +ELSE
    +TYPE ( int ) ~shm_nattch_t.2 ;
    +ENDIF
    +ENDIF

    /* This type has been abstracted */
    +IF %% __STRICT_XPG3 %%
    +TYPEDEF pid_t ~shm_pid_t ;
    +ELSE
    +TYPE ( int ) ~shm_pid_t.1 ;
    +ENDIF

    +TYPE struct shmid_ds ;
    +FIELD struct shmid_ds {
	struct ipc_perm shm_perm ;
	int shm_segsz ;
	~shm_pid_t shm_lpid ;
	~shm_pid_t shm_cpid ;
	~shm_nattch_t shm_nattch ;
	time_t shm_atime ;
	time_t shm_dtime ;
	time_t shm_ctime ;
    } ;

    +IFNDEF ~building_libs
    +FUNC int shmctl ( int, int, struct shmid_ds * ) ;
    +ELSE
    +FUNC int __old_shmctl | shmctl.1 ( int, int, struct shmid_ds * ) ;
%%%
#define __old_shmctl( A, B, C )		shmctl ( A, B, C )
%%%
    +ENDIF
} ;

+IFNDEF ~building_libs
+FUNC char *shmat ( int, char *, int ) ;
+FUNC int shmdt ( char * ) ;
+FUNC int shmget ( key_t, int, int ) ;
+ELSE
+FUNC char *__old_shmat | shmat.1 ( int, char *, int ) ;
+FUNC int __old_shmdt | shmdt.1 ( char * ) ;
+FUNC int __old_shmget | shmget.1 ( key_t, int, int ) ;
%%%
#define __old_shmat( A, B, C )		shmat ( A, B, C )
#define __old_shmdt( A )		shmdt ( A )
#define __old_shmget( A, B, C )		shmget ( A, B, C )
%%%
+ENDIF
