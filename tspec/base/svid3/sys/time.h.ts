# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$SOURCENAME = "sys/sys_time.h.ts" ;

+USE "svid3", "", "config" ;
+IF %% __SYSV_REAL_TIME %%

+SUBSET "timeval" := {
    # Duplicated in a number of places
    $PROTECT = "__TDF_STRUCT_TIMEVAL" ;

    +FIELD struct timeval | timeval_sysv {
        long tv_sec ;
        long tv_usec ;
    } ;
} ;

+FIELD struct itimerval {
    struct timeval it_interval ;
    struct timeval it_value ;
} ;

+CONST int DST_GB, DST_WET, DST_MET, DST_EET, DST_RUM, DST_TUR ;
+CONST int DST_AUST, DST_AUSTALT, DST_CAN, DST_USA, DST_NONE ;
+CONST int ITIMER_REAL, ITIMER_VIRTUAL, ITIMER_PROF ;

+FUNC int adjtime ( struct timeval *, struct timeval * ) ;
+FUNC int gettimeofday ( struct timeval * ) ;
+FUNC int settimeofday ( struct timeval * ) ;
+FUNC int getitimer ( int, struct itimerval * ) ;
+FUNC int setitimer ( int, struct itimerval *, struct itimerval * ) ;

+ENDIF
