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
+SUBSET "u_proto" := {
    +USE "posix", "sys/types.h" ;
    +USE "posix", "sys/stat.h" ;
    +IMPLEMENT "ansi", "stddef.h", "null" (!?) ;
    +IMPLEMENT "ansi", "stdlib.h", "bottom" (!?) ;
    +IMPLEMENT "ansi", "stdio.h", "rename" (!?) ;
    +IMPLEMENT "ansi", "stdio.h", "seek_consts" (!?) ;

    +IFNDEF _POSIX_VERSION
    +DEFINE _POSIX_VERSION %% 198808L %% ;
    +ENDIF

    +CONST int R_OK, W_OK, X_OK, F_OK ;

    #+CONST int _POSIX_JOB_CONTROL, _POSIX_SAVED_IDS ;

    +CONST int _SC_ARG_MAX, _SC_CHILD_MAX, _SC_CLK_TCK, _SC_JOB_CONTROL ;
    +CONST int _SC_NGROUPS_MAX, _SC_OPEN_MAX, _SC_SAVED_IDS, _SC_VERSION ;

    +CONST int _PC_CHOWN_RESTRICTED, _PC_LINK_MAX, _PC_MAX_CANON ;
    +CONST int _PC_MAX_INPUT, _PC_NAME_MAX, _PC_NO_TRUNC, _PC_PATH_MAX ;
    +CONST int _PC_PIPE_BUF, _PC_VDISABLE ;

    +DEFINE STDIN_FILENO 0 ;
    +DEFINE STDOUT_FILENO 1 ;
    +DEFINE STDERR_FILENO 2 ;

    +EXP (extern) char **environ ;

    +FUNC ~bottom _exit ( int ) ;
    +FUNC int access ( const char *, int ) ;
    +FUNC unsigned int alarm ( unsigned int ) ;
    +FUNC int chdir ( const char * ) ;
    +FUNC int close ( int ) ;
    +FUNC int dup ( int ) ;
    +FUNC int dup2 ( int, int ) ;
    +FUNC int execl ( const char *, const char *, ... ) ;
    +FUNC int execle ( const char *, const char *, ... ) ;
    +FUNC int execlp ( const char *, const char *, ... ) ;
    +FUNC int execv ( const char *, char * const [] ) ;
    +FUNC int execve ( const char *, char * const [], char * const [] ) ;
    +FUNC int execvp ( const char *, char * const [] ) ;
    +FUNC pid_t fork ( void ) ;
    +FUNC long fpathconf ( int, int ) ;
    +FUNC gid_t getegid ( void ) ;
    +FUNC uid_t geteuid ( void ) ;
    +FUNC gid_t getgid ( void ) ;
    +FUNC int getgroups ( int, gid_t [] ) ;
    +FUNC char *getlogin ( void ) ;
    +FUNC pid_t getpgrp ( void ) ;
    +FUNC pid_t getpid ( void ) ;
    +FUNC pid_t getppid ( void ) ;
    +FUNC uid_t getuid ( void ) ;
    +FUNC int isatty ( int ) ;
    +FUNC int link ( const char *, const char * ) ;
    +FUNC off_t lseek ( int, off_t, int ) ;
    +FUNC long pathconf ( const char *, int ) ;
    +FUNC int pause ( void ) ;
    +FUNC int pipe ( int [2] ) ;
    +FUNC int rmdir ( const char * ) ;
    +FUNC pid_t setsid ( void ) ;
    +FUNC unsigned int sleep ( unsigned int ) ;
    +FUNC long sysconf ( int ) ;
    +FUNC char *ttyname ( int ) ;
    +FUNC int unlink ( const char * ) ;

    +FUNC int chown ( const char *, int, int ) ;
    +FUNC int setgid ( int ) ;
    +FUNC int setpgid ( pid_t, pid_t ) ;
    +FUNC int setuid ( int ) ;
} ;

+SUBSET "tcpgrp" := {
    +USE "posix", "sys/types.h" ;
    +FUNC pid_t tcgetpgrp ( int ) ;
    +FUNC int tcsetpgrp ( int, pid_t ) ;
} ;

+IF 0
+SUBSET "getopt" := {
    +FUNC int getopt ( int, char * const [], const char * ) ;
    +EXP (extern) char *optarg ;
    +EXP (extern) int optind, opterr ;
} ;
+ENDIF

+SUBSET "u_old" := {
+IFNDEF ~building_libs
    +FUNC char *getcwd ( char *, int ) ;
    +FUNC int read ( int, char *, unsigned ) ;
    +FUNC int write ( int, char *, unsigned ) ;
+ELSE
    +FUNC char *__old_getcwd | getcwd.1 ( char *, int ) ;
    +FUNC int __old_read | read.1 ( int, char *, unsigned ) ;
    +FUNC int __old_write | write.1 ( int, char *, unsigned ) ;
%%%
#define __old_getcwd( A, B )		getcwd ( A, B )
#define __old_read( A, B, C )		read ( A, B, C )
#define __old_write( A, B, C )		write ( A, B, C )
%%%
+ENDIF
} ;
