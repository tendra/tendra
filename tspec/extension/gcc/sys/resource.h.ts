# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "gcc", "sys/time.h.ts" ;

+TYPE ( int ) rlimit_t ;
+FIELD struct rlimit {
    rlimit_t rlim_cur ;
    rlimit_t rlim_max ;
} ;

+CONST rlimit_t RLIM_INFINITY ;

+CONST int RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA ;
+CONST int RLIMIT_FSIZE, RLIMIT_STACK ;

+FUNC int getrlimit ( int, struct rlimit * ) ;
+FUNC int setrlimit ( int, const struct rlimit * ) ;
