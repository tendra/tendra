# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IF %% __SYSV_KERNEL_EXTENSION %%
+USE "svid3", "sys/types.h.ts" ;

+CONST int PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE ;
+CONST int MAP_SHARED, MAP_PRIVATE, MAP_FIXED ;
+CONST int MS_ASYNC, MS_SYNC, MS_INVALIDATE ;

+FUNC caddr_t mmap ( caddr_t, size_t, int, int, int, off_t ) ;
+FUNC int mprotect ( caddr_t, size_t, int ) ;
+FUNC int msync ( caddr_t, size_t, int ) ;
+FUNC int munmap ( caddr_t, size_t ) ;

+IF %% __SYSV_REAL_TIME %%

+CONST int SHARED, PRIVATE, PROC_TEXT, PROC_DATA, MC_LOCK, MC_LOCKAS ;
+CONST int MC_SYNC, MC_UNLOCK, MC_UNLOCKAS, MCL_CURRENT, MCL_FUTURE ;

/* Error in book? */
+FUNC int memcntl ( caddr_t, size_t, caddr_t, int, int, int ) ;
+FUNC int mlock ( caddr_t, size_t ) ;
+FUNC int munlock ( caddr_t, size_t ) ;
+FUNC int mlockall ( int ) ;
+FUNC int munlockall ( void ) ;

+ENDIF
+ENDIF
