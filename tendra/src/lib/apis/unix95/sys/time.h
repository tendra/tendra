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
$SOURCENAME = "sys/sys_time.h" ;


+SUBSET "timeval" := {
    # Duplicated in a number of places
    $PROTECT = "__TDF_STRUCT_TIMEVAL" ;

    +IMPLEMENT "ansi", "time.h", "time_t" ;

    +FIELD struct timeval {
	time_t tv_sec ;
	long tv_usec ;
    } ;
} ;

+FIELD struct itimerval {
    struct timeval it_interval ;
    struct timeval it_value ;
} ;

+NAT ~fds_bits_size ;

+FIELD (struct) fd_set {
    long fds_bits [ ~fds_bits_size ] ;
} ;

+CONST int ITIMER_REAL, ITIMER_VIRTUAL, ITIMER_PROF ;

+FUNC int getitimer ( int, struct itimerval * ) ;
+FUNC int setitimer ( int, const struct itimerval *, struct itimerval * ) ;
+FUNC int gettimeofday ( struct timeval *, void * ) ;


+CONST int FD_SETSIZE ;
+MACRO void FD_SET ( int, fd_set * ) ;
+MACRO void FD_CLR ( int, fd_set * ) ;
+MACRO int FD_ISSET ( int, fd_set * ) ;
+MACRO void FD_ZERO ( fd_set * ) ;


+FUNC int select ( int, fd_set *, fd_set *, fd_set *, struct timeval * ) ;
+FUNC int utimes ( const char *, const struct timeval [2] ) ;
