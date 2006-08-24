#ifndef __HACKED_SYS_DIRENT_INCLUDED
#define __HACKED_SYS_DIRENT_INCLUDED

typedef unsigned long long __ino64_t;
#define __invalid_d_ino d_ino
#include_next <sys/dirent.h>

#endif
