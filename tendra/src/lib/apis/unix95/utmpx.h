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
# Corrigenda U013 1170/02: define timeval and pid_t
+IMPLEMENT "unix95", "sys/time.h", "timeval" ;
+IMPLEMENT "posix", "sys/types.h", "pid_t" ;

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
