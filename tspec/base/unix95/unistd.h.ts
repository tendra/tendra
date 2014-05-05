# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "xpg4", "unistd.h.ts" ;
+IMPLEMENT "c/c89", "stddef.h.ts", "null" ;
+IMPLEMENT "c/c89", "stdio.h.ts", "seek_consts" ;

+CONST int _SC_ATEXIT_MAX ;
+CONST int _SC_PAGESIZE, _SC_PAGE_SIZE ;
+CONST int _SC_IOV_MAX ;
+CONST int _SC_XOPEN_UNIX ;

+CONST int F_ULOCK, F_LOCK, F_TLOCK, F_TEST ;

+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;
+IMPLEMENT "posix1", "sys/types.h.ts", "ssize_t" ;
+IMPLEMENT "posix", "sys/types.h.ts", "guid" ;
+IMPLEMENT "posix", "sys/types.h.ts", "off_t" ;
+IMPLEMENT "posix", "sys/types.h.ts", "pid_t" ;
+IMPLEMENT "unix95", "sys/types.h.ts", "useconds_t" ;
+IMPLEMENT "xpg4", "stdio.h.ts", "optopt" ;

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
