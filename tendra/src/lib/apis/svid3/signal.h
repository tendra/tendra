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
+IMPLEMENT "posix", "signal.h" ;

+CONST int SIGBUS, SIGEMT, SIGPOLL, SIGPWR, SIGSYS, SIGTRAP, SIGWINCH ;
+CONST int SIGXCPU, SIGXFSZ ;

+CONST int SA_NOCLDWAIT, SA_ONSTACK, SA_RESETHAND, SA_RESTART, SA_SIGINFO ;

/* See errata */
+FIELD ( struct ) stack_t {
    char *ss_sp ;
    int ss_size ;
    int ss_flags ;
} ;

+CONST int SS_ONSTACK, SS_DISABLE, SIGSTKSZ ;
/* Typo in book */
+CONST int MINSIGSTKSZ ;

+FUNC int sigaltstack ( const stack_t *, stack_t * ) ;
+FUNC void ( *sigset ( int, void (*) ( int ) ) ) ( int ) ;
+FUNC int sighold ( int ) ;
+FUNC int sigrelse ( int ) ;
+FUNC int sigignore ( int ) ;
+FUNC int sigpause ( int ) ;
