# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Corrigenda U013 1170/02: define timeval and pid_t
+IMPLEMENT "cae/xsh4v2-unix", "sys/time.h.ts", "timeval" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "pid_t" ;

+NAT ~ut_user_size, ~ut_id_size, ~ut_line_size ;

+FIELD struct utmpx {
    char ut_user [ ~ut_user_size ] ;
    char ut_id [ ~ut_id_size ] ;
    char ut_line [ ~ut_line_size ] ;
    pid_t ut_pid ;
    short ut_type ;
    struct timeval ut_tv ;
} ;

+CONST short EMPTY ;
+CONST short BOOT_TIME, OLD_TIME, NEW_TIME, INIT_PROCESS ;
+CONST short LOGIN_PROCESS, USER_PROCESS, DEAD_PROCESS ;

+FUNC void endutxent ( void ) ;
+FUNC struct utmpx *getutxent ( void ) ;
+FUNC struct utmpx *getutxid ( const struct utmpx * ) ;
+FUNC struct utmpx *getutxline ( const struct utmpx * ) ;
+FUNC struct utmpx *pututxline ( const struct utmpx * ) ;
+FUNC void setutxent ( void ) ;

