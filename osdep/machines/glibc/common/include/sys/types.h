#ifndef __HACKED_LIBC_SYS_TYPES_H
#define __HACKED_LIBC_SYS_TYPES_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_UNIX95_SIGNAL_H_SIGINFO_T
#define _POSIX_C_SOURCE 199309L /* for siginfo_t in signal.h */
#endif
#endif

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_SVID3_TERMIOS_H
#include <sys/ioctl.h>
#endif
#endif

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_SVID3_SYS_IPC_H
#pragma TenDRA extra type definition allow /* for caddr_t in sys/ipc.h */
#endif
#endif

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_SVID3_UNISTD_H_U_OLD
#pragma TenDRA extra type definition allow /* for caddr_t in sys/ipc.h */
#endif
#endif

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_SVID3_UTMP_H
#pragma TenDRA extra type definition allow /* for caddr_t in sys/ipc.h */
#endif
#endif

#include_next <sys/types.h>

#endif

