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
+IMPLEMENT "xpg4", "signal.h" ;
+IMPLEMENT "unix95", "ucontext.h", "sig" ;

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
    +USE "posix", "sys/types.h" ;			# for uid_t
    +IMPLEMENT "posix", "sys/types.h", "pid_t" ;

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
