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
+USE "posix", "sys/types.h" ;
+USE "posix", "sys/stat.h" ;
+USE "posix", "unistd.h", "u_proto" ;

+CONST int F_DUPFD, F_GETFD, F_SETFD, F_GETFL, F_SETFL, F_GETLK ;
+CONST int F_SETLK, F_SETLKW ;
+CONST int FD_CLOEXEC ;
+CONST int F_RDLCK, F_UNLCK, F_WRLCK ;
+CONST int O_CREAT, O_EXCL, O_NOCTTY, O_TRUNC ;
+CONST int O_APPEND, O_NONBLOCK ;
+CONST int O_ACCMODE ;
+CONST int O_RDONLY, O_RDWR, O_WRONLY ;

/* This type is abstracted */
+IF %% __STRICT_POSIX %%
+TYPEDEF pid_t ~fcntl_pid_t ;
+ELSE
+TYPE ( int ) ~fcntl_pid_t.1 ;
+MACRO pid_t __fcntl_pid2pid ( ~fcntl_pid_t ) ;
+MACRO ~fcntl_pid_t __pid2fcntl_pid ( pid_t ) ;
+IFNDEF ~building_libs
%%
#pragma accept conversion __fcntl_pid2pid
#pragma accept conversion __pid2fcntl_pid
%%
%%%
#include <fcntl.h>
#define __fcntl_pid2pid( X )	( pid_t ) ( X )
#define __pid2fcntl_pid( X )	( __local_fcntl_pid_t ) ( X )
%%%
+ENDIF
+ENDIF

+FIELD struct flock {
    short l_type ;
    short l_whence ;
    off_t l_start ;
    off_t l_len ;
    ~fcntl_pid_t l_pid ;
} ;

+FUNC int open ( const char *, int, ... ) ;
+FUNC int fcntl ( int, int, ... ) ;
+FUNC int creat ( const char *, mode_t ) ;
