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
# Main body from posix
+IMPLEMENT "posix", "unistd.h", "u_proto" ;

+SUBSET "u_old" := {
    # Different from posix
    +USE "svid3", "sys/types.h" ;
    +FUNC char *getcwd ( char *, size_t ) ;
    +FUNC ssize_t read ( int, void *, size_t ) ;
    +FUNC ssize_t write ( int, const void *, size_t ) ;
} ;

# Added in xpg3
+IMPLEMENT "xpg3", "unistd.h", "u_plus" ;
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
