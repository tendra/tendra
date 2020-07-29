# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix/posix", "sys/types.h.ts" ;
+USE "posix/posix", "sys/stat.h.ts" ;
+USE "posix/posix", "unistd.h.ts", "u_proto" ;

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
