# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IF %% __SYSV_SOFTWARE_DEVELOPMENT %%
+USE "svid3", "sys/types.h.ts" ;

+NAT ~utmp_user_size, ~utmp_id_size, ~utmp_line_size ;

/* This type is abstracted */
+IF %% __STRICT_SYSV %%
+TYPEDEF pid_t ~utmp_pid_t ;
+ELSE
+TYPE ( int ) ~utmp_pid_t.1 ;
+MACRO pid_t __utmp_pid2pid ( ~utmp_pid_t ) ;
+MACRO ~utmp_pid_t __pid2utmp_pid ( pid_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __utmp_pid2pid
#pragma accept conversion __pid2utmp_pid
%%
%%%
#include <utmp.h>
#define __utmp_pid2pid( X )	( pid_t ) ( X )
#define __pid2utmp_pid( X )	( __local_utmp_pid_t ) ( X )
%%%
+ENDIF
+ENDIF

+TYPE struct utmp ;
+FIELD struct utmp {
    char ut_user [ ~utmp_user_size ] ;
    char ut_id [ ~utmp_id_size ] ;
    char ut_line [ ~utmp_line_size ] ;
    ~utmp_pid_t ut_pid ;
    short ut_type ;
} ;

+CONST int EMPTY, RUN_LVL, BOOT_TIME, OLD_TIME, NEW_TIME, INIT_PROCESS ;
+CONST int LOGIN_PROCESS, USER_PROCESS, DEAD_PROCESS, ACCOUNTING ;

+FUNC struct utmp *getutent ( void ) ;
+FUNC struct utmp *getutid ( const struct utmp * ) ;
+FUNC struct utmp *getutline ( const struct utmp * ) ;
+FUNC void setutent ( void ) ;
+FUNC void endutent ( void ) ;
/* Errors in book? */
+FUNC struct utmp *pututline ( const struct utmp * ) ;
+FUNC int utmpname ( const char * ) ;

+ENDIF
