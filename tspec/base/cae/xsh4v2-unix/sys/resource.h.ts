# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# Corrigenda U013 1170/02: define id_t
+IMPLEMENT "cae/xsh4v2-unix", "sys/types.h.ts", "id_t" ;

+CONST int PRIO_PROCESS, PRIO_PGRP, PRIO_USER ;

+FUNC int getpriority ( int, id_t ) ;
+FUNC int setpriority ( int, id_t, int ) ;

+TYPE ( unsigned ) rlim_t ;

+CONST rlim_t RLIM_INFINITY ;

+FIELD struct rlimit {
	rlim_t rlim_cur ;
	rlim_t rlim_max ;
} ;

+CONST int RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA, RLIMIT_FSIZE ;
+CONST int RLIMIT_NOFILE, RLIMIT_STACK, RLIMIT_AS ;

+FUNC int getrlimit ( int, struct rlimit * ) ;
+FUNC int setrlimit ( int, const struct rlimit * ) ;

+SUBSET "rusage" := {
	+IMPLEMENT "cae/xsh4v2-unix", "sys/time.h.ts", "timeval" ;

	+FIELD struct rusage {
		struct timeval ru_utime ;
		struct timeval ru_stime ;
	} ;
} ;

+CONST int RUSAGE_SELF, RUSAGE_CHILDREN ;

+FUNC int getrusage ( int, struct rusage * ) ;

