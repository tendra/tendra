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
+USE "svid3", "", "config" ;
+IF %% __SYSV_SOFTWARE_DEVELOPMENT %%
+USE "svid3", "sys/types.h" ;

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
