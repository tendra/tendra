# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Main body from posix
+IMPLEMENT "posix/posix", "unistd.h.ts", "u_proto" ;

+SUBSET "u_old" := {
    # Different from posix
    +USE "svid/svid3", "sys/types.h.ts" ;
    +FUNC char *getcwd ( char *, size_t ) ;
    +FUNC ssize_t read ( int, void *, size_t ) ;
    +FUNC ssize_t write ( int, const void *, size_t ) ;
} ;

# Added in xpg3
+IMPLEMENT "cae/xpg3", "unistd.h.ts", "u_plus" ;
+IMPLEMENT "cae/xpg3", "unistd.h.ts", "u_plus-crypt" ;
+FUNC void swab ( char *, char *, int ) ;

+IF 0
+CONST int _POSIX_CHOWN_RESTRICTED, _POSIX_NO_TRUNC, _POSIX_VDISABLE ;
+ENDIF

+CONST int _SC_PAGESIZE ;

/* I had missed these */
+FUNC int lockf ( int, int, long ) ;
+CONST int F_ULOCK, F_LOCK, F_TLOCK, F_TEST ;

/* These don't really belong anywhere */
+FUNC int fattach ( int, const char * ) ;
+FUNC int fchdir ( int ) ;
+FUNC int fchown ( int, uid_t, gid_t ) ;
+FUNC int fdetach ( const char * ) ;
+FUNC pid_t getpgid ( pid_t ) ;
+FUNC pid_t getsid ( pid_t ) ;
+FUNC char *gettxt ( char *, char * ) ;
+FUNC int lchown ( const char *, uid_t, gid_t ) ;
+FUNC int ptrace ( int, pid_t, int, int ) ;
+FUNC int readlink ( const char *, char *, int ) ;
+FUNC int stime ( const time_t * ) ;
+FUNC int symlink ( const char *, const char * ) ;
+FUNC void sync ( void ) ;
 
# setgroups needs privileged user status
+FUNC int setgroups ( int, const gid_t * ) ;
