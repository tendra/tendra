# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "bsd_extn", "sys/time.h.ts" ;

+IFDEF ~protect ( "svid/svid3", "sys/types.h.ts" )

+USE ( "svid/svid3" ), "sys/resource.h.ts" ;

+ELSE

+TYPE ( int ) rlimit_t.1 ;

+TYPE struct rlimit.1 ;
+FIELD struct rlimit.1 {
    rlimit_t rlim_cur.1 ;
    rlimit_t rlim_max.1 ;
} ;

+CONST rlimit_t RLIM_INFINITY.1 ;

+CONST int RLIMIT_CORE.1 ;
+CONST int RLIMIT_CPU.1 ;
+CONST int RLIMIT_DATA.1 ;
+CONST int RLIMIT_FSIZE.1 ;
+CONST int RLIMIT_STACK.1 ;

+FUNC int getrlimit.1 ( int, struct rlimit * ) ;
+FUNC int setrlimit.1 ( int, const struct rlimit * ) ;

+ENDIF
