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
+IMPLEMENT "xpg4", "unistd.h" ;
+IMPLEMENT "ansi", "stddef.h", "null" ;
+IMPLEMENT "ansi", "stdio.h", "seek_consts" ;

+CONST int _SC_ATEXIT_MAX ;
+CONST int _SC_PAGESIZE, _SC_PAGE_SIZE ;
+CONST int _SC_IOV_MAX ;
+CONST int _SC_XOPEN_UNIX ;

+CONST int F_ULOCK, F_LOCK, F_TLOCK, F_TEST ;

+IMPLEMENT "ansi", "stddef.h", "size_t" ;
+IMPLEMENT "posix1", "sys/types.h", "ssize_t" ;
+IMPLEMENT "posix", "sys/types.h", "guid" ;
+IMPLEMENT "posix", "sys/types.h", "off_t" ;
+IMPLEMENT "posix", "sys/types.h", "pid_t" ;
+IMPLEMENT "unix95", "sys/types.h", "useconds_t" ;
+IMPLEMENT "xpg4", "stdio.h", "optopt" ;

+FUNC int brk ( void * ) ;
+FUNC int fchown ( int, uid_t, gid_t ) ;
+FUNC int fchdir ( int ) ;
+FUNC int ftruncate ( int, off_t ) ;
+FUNC int getdtablesize ( void ) ;
+FUNC long gethostid ( void ) ;
+FUNC int getpagesize ( void ) ;
+FUNC pid_t getpgid ( pid_t ) ;
+FUNC pid_t getsid ( pid_t ) ;
+FUNC char *getwd ( char * ) ;
+FUNC int lchown ( const char *, uid_t, gid_t ) ;
+FUNC int lockf ( int, int, off_t ) ;
+FUNC int readlink ( const char *, char *, size_t ) ;
+FUNC void *sbrk ( int ) ;
+FUNC pid_t setpgrp ( void ) ;
+FUNC int setregid ( gid_t, gid_t ) ;
+FUNC int setreuid ( uid_t, uid_t ) ;
+FUNC int symlink ( const char *, const char * ) ;
+FUNC void sync ( void ) ;
+FUNC int truncate ( const char *, off_t ) ;
+FUNC useconds_t ualarm ( useconds_t, useconds_t ) ;
+FUNC int usleep ( useconds_t ) ;
+FUNC pid_t vfork ( void ) ;

# CAE, Networking Services, Issue 4
+FUNC int gethostname ( char *, size_t ) ;
