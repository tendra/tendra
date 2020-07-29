# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "signal.h.ts" ;
+USE "posix/posix", "sys/types.h.ts" ;

+SUBSET "sigset_t" := { +TYPE sigset_t ; } ;

+FIELD struct sigaction | struct_sigaction {
    void ( *sa_handler ) ( int ) ;
    sigset_t sa_mask ;
    int sa_flags ;
} ;

+CONST int SIGALRM, SIGCHLD, SIGCONT, SIGHUP, SIGKILL, SIGPIPE, SIGQUIT ;
+CONST int SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU, SIGUSR1, SIGUSR2 ;
+CONST int SIG_BLOCK, SIG_SETMASK, SIG_UNBLOCK ;
+CONST int SA_NOCLDSTOP ;

+FUNC int kill ( pid_t, int ) ;
+FUNC int sigaction ( int, const struct sigaction *, struct sigaction * ) ;
+FUNC int sigaddset ( sigset_t *, int ) ;
+FUNC int sigdelset ( sigset_t *, int ) ;
+FUNC int sigemptyset ( sigset_t * ) ;
+FUNC int sigfillset ( sigset_t * ) ;
+FUNC int sigismember ( const sigset_t *, int ) ;
+FUNC int sigpending ( sigset_t * ) ;
+FUNC int sigprocmask ( int, const sigset_t *, sigset_t * ) ;
+FUNC int sigsuspend ( const sigset_t * ) ;
