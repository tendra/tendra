# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c89", "stddef.h.ts", "size_t" ;

+USE "posix/posix", "sys/types.h.ts", "guid" ;
+USE "posix/posix", "sys/types.h.ts", "off_t" ;
+USE "posix/posix", "sys/types.h.ts", "pid_t" ;

+IMPLEMENT "cae/xsh4v2-unix", "sys/types.h.ts", "useconds_t" ;

+DEFINE _XOPEN_UNIX %% %% ; # XXX: how to require just that something is defined, with no value?

+CONST int _SC_ATEXIT_MAX ;
+CONST int _SC_IOV_MAX ;
+CONST int _SC_PAGESIZE, _SC_PAGE_SIZE ;
+CONST int _SC_XOPEN_UNIX ;

+CONST int F_ULOCK, F_LOCK, F_TLOCK, F_TEST ;

+FUNC int brk ( void * ) ;
+FUNC void *sbrk ( int ) ;

+FUNC int fchdir ( int ) ;
+FUNC int fchown ( int, uid_t, gid_t ) ;

+FUNC int ftruncate ( int, off_t ) ;
+FUNC int truncate ( const char *, off_t ) ;

+FUNC int getdtablesize ( void ) ;
+FUNC int getpagesize ( void ) ;

+FUNC long gethostid ( void ) ;

+FUNC pid_t getpgid ( pid_t ) ;
+FUNC pid_t getsid ( pid_t ) ;
+FUNC pid_t setpgrp ( void ) ;
+FUNC int setregid ( gid_t, gid_t ) ;
+FUNC int setreuid ( uid_t, uid_t ) ;

+FUNC char *getwd ( char * ) ;

+FUNC int lchown ( const char *, uid_t, gid_t ) ;
+FUNC int lockf ( int, int, off_t ) ;

+FUNC int readlink ( const char *, char *, size_t ) ;
+FUNC int symlink ( const char *, const char * ) ;

+FUNC void sync ( void ) ;

+FUNC useconds_t ualarm ( useconds_t, useconds_t ) ;
+FUNC int usleep ( useconds_t ) ;

+FUNC pid_t vfork ( void ) ;

