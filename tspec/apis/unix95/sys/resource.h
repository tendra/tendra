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

# Corrigenda U013 1170/02: define id_t
+IMPLEMENT "unix95", "sys/types.h", "id_t" ;

+TYPE ( unsigned ) rlim_t ;

+CONST int PRIO_PROCESS, PRIO_PGRP, PRIO_USER ;

+CONST rlim_t RLIM_INFINITY ;

+FIELD struct rlimit {
    rlim_t rlim_cur ;
    rlim_t rlim_max ;
} ;

+SUBSET "rusage" := {
    +IMPLEMENT "unix95", "sys/time.h", "timeval" ;

    +FIELD struct rusage {
	struct timeval ru_utime ;
	struct timeval ru_stime ;
    } ;
} ;

+CONST int RLIMIT_CORE, RLIMIT_CPU, RLIMIT_DATA, RLIMIT_FSIZE ;
+CONST int RLIMIT_NOFILE, RLIMIT_STACK, RLIMIT_AS ;

+CONST int RUSAGE_SELF, RUSAGE_CHILDREN ;

+FUNC int getpriority ( int, id_t ) ;
+FUNC int getrlimit ( int, struct rlimit * ) ;
+FUNC int getrusage ( int, struct rusage * ) ;
+FUNC int setpriority ( int, id_t, int ) ;
+FUNC int setrlimit ( int, const struct rlimit * ) ;
