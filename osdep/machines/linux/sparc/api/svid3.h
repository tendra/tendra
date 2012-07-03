/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifdef _GLIBC2_14
#define __WRONG_SVID3_RPC_XDR_H /* incompatible x_inline */
#define __WRONG_SVID3_SYS_SWAP_H /* missing SC_REMOVE */
#define __WRONG_SVID3_SYS_MOUNT_H /* incompatible mount */
#define __WRONG_SVID3_SYS_ACCT_H /* incompatible acct.acct.ac_uid */
#define __WRONG_SVID3_SYS_TIME_H /* incompatible settimeofday */
#define __WRONG_SVID3_RPC_RPC_H /* incompatible xdr_ops.x_inline */
#define __WRONG_SVID3_WAIT_H /* incompatible siginfo_t.si_addr */
#define __WRONG_SVID3_TERMIOS_H /* missing VSWTCH */
#define __WRONG_SVID3_SYS_TYPES_H /* missing __local_addr_t */
#define __WRONG_SVID3_UNISTD_H /* missing readlink */
#define __WRONG_SVID3_SYS_UIO_H /* incompatible iovec.iov_base */
#define __WRONG_SVID3_SYS_MMAN_H /* incompatible mmap */
#define __WRONG_SVID3_TIUSER_H /* missing tiuser.h */
#define __WRONG_SVID3_SYS_STATVFS_H /* missing FSTYPSZ */
#define __WRONG_SVID3_SIGNAL_H /* incompatible stack_t.ss_sp */
#define __WRONG_SVID3_SYS_SHM_H /* incompatible shmid_ds.shm_segsz */
#define __WRONG_SVID3_TERMIO_H /* incompatible termio.c_line */
#define __WRONG_SVID3_UCONTEXT_H /* incompatible stack_t.ss_sp */
#endif

