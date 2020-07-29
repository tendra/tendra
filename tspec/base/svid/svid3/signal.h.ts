# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "signal.h.ts" ;

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
