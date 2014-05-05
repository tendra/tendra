# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "xpg4", "signal.h.ts" ;
+IMPLEMENT "unix95", "ucontext.h.ts", "sig" ;

+CONST void ( *SIG_HOLD ) ( int ) ;

+CONST int SIGTRAP, SIGBUS, SIGSYS, SIGPOLL, SIGPROF, SIGXCPU ;
+CONST int SIGXFSZ, SIGURG, SIGVTALRM ;

+CONST int SA_ONSTACK, SA_RESETHAND, SA_RESTART, SA_SIGINFO, SA_NOCLDWAIT ;
+CONST int SA_NODEFER ;

+CONST int MINSIGSTKSZ, SIGSTKSZ ;

+CONST int SS_ONSTACK, SS_DISABLE ;

+FIELD struct sigstack | sigstack_struct {
    int ss_onstack ;
    void *ss_sp ;
} ;

+SUBSET "siginfo_t" := {
    +USE "posix", "sys/types.h.ts" ;			# for uid_t
    +IMPLEMENT "posix", "sys/types.h.ts", "pid_t" ;

    +FIELD ( struct ) siginfo_t {
	int si_signo ;
	int si_errno ;
	int si_code ;
	pid_t si_pid ;
	uid_t si_uid ;
	void *si_addr ;
	int si_status ;
	long si_band ;
    } ;
} ;

+FIELD struct sigaction | struct_sigaction {
    void ( *sa_sigaction ) ( int, siginfo_t *, void * ) ;
} ;

+CONST int ILL_ILLOPC, ILL_ILLOPN, ILL_ILLADR, ILL_ILLTRP ;
+CONST int ILL_PRVOPC, ILL_PRVREG, ILL_COPROC, ILL_BADSTK ;

+CONST int FPE_INTDIV, FPE_INTOVF, FPE_FLTDIV, FPE_FLTOVF ;
+CONST int FPE_FLTUND, FPE_FLTRES, FPE_FLTINV, FPE_FLTSUB ;

+CONST int SEGV_MAPERR, SEGV_ACCERR ;

+CONST int BUS_ADRALN, BUS_ADRERR, BUS_OBJERR ;

+CONST int TRAP_BRKPT, TRAP_TRACE ;

+CONST int CLD_EXITED, CLD_KILLED, CLD_DUMPED, CLD_TRAPPED ;
+CONST int CLD_STOPPED, CLD_CONTINUED ;

+CONST int POLL_IN, POLL_OUT, POLL_MSG ;
+CONST int POLL_ERR, POLL_PRI, POLL_HUP ;

+FUNC void ( * bsd_signal ( int, void ( * ) ( int ) ) ) ( int ) ;
+FUNC int killpg ( pid_t, int ) ;
+FUNC int sigaltstack ( const stack_t *, stack_t * ) ;
+FUNC int sigignore ( int ) ;
+FUNC int sighold ( int ) ;
+FUNC int siginterrupt ( int, int ) ;
+FUNC int sigpause ( int ) ;
+FUNC void ( *sigset ( int, void (*) ( int ) ) ) ( int ) ;
+FUNC int sigrelse ( int ) ;
+FUNC int sigstack ( struct sigstack *, struct sigstack * ) ;

/* +MACRO int sigmask ( int ) ;		Corrigenda U013 1170/37: remove */
