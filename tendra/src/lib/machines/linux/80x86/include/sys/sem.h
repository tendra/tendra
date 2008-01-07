#ifndef __HACKED_SYS_SEM_INCLUDED
#define __HACKED_SYS_SEM_INCLUDED

#ifdef __BUILDING_LIBS
struct sembuf {
    unsigned short sem_num ;
    short sem_op ;
    short sem_flg ;
} ;
extern int semop ( int, struct sembuf *, unsigned ) ;
#define sembuf	sembuf_wrong
#define semop	semop_wrong
#endif

#include_next <sys/sem.h>

#ifdef __BUILDING_LIBS
#undef sembuf
#undef semop
#endif

#endif
