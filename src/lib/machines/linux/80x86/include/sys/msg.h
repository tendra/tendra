#ifndef __HACKED_LINUX_SYS_MSG_INCLUDED
#define __HACKED_LINUX_SYS_MSG_INCLUDED

#ifdef __BUILDING_LIBS
#define msgsnd	__msgsnd_wrong
#define msgrcv	__msgrcv_wrong
#endif

#include_next <sys/msg.h>

#ifdef __BUILDING_LIBS
#undef msgsnd
#undef msgrcv
#endif

#endif
