# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$SOURCENAME = "sys/sys_time.h.ts" ;

+SUBSET "timeval" := {
	# Duplicated in a number of places
	$PROTECT = "__TDF_STRUCT_TIMEVAL" ;

	+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;

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

+CONST int FD_SETSIZE ;
+MACRO void FD_SET ( int, fd_set * ) ;
+MACRO void FD_CLR ( int, fd_set * ) ;
+MACRO int FD_ISSET ( int, fd_set * ) ;
+MACRO void FD_ZERO ( fd_set * ) ;

+FUNC int select ( int, fd_set *, fd_set *, fd_set *, struct timeval * ) ;

+CONST int ITIMER_REAL, ITIMER_VIRTUAL, ITIMER_PROF ;

+FUNC int getitimer ( int, struct itimerval * ) ;
+FUNC int setitimer ( int, const struct itimerval *, struct itimerval * ) ;

+FUNC int gettimeofday ( struct timeval *, void * ) ;
+FUNC int utimes ( const char *, const struct timeval [2] ) ;

