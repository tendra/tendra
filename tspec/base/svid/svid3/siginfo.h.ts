# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "sys/types.h.ts" ;

+FIELD ( struct ) siginfo_t {
    int si_signo ;
    int si_errno ;
    int si_code ;
    pid_t si_pid ;
    uid_t si_uid ;
    caddr_t si_addr ;
    int si_status ;
    long si_band ;
} ;

+CONST int ILL_ILLOPC, ILL_ILLOPN, ILL_ILLADR, ILL_ILLTRP, ILL_PRVOPC ;
+CONST int ILL_PRVREG, ILL_COPROC, ILL_BADSTK ;
+CONST int FPE_INTDIV, FPE_INTOVF, FPE_FLTDIV, FPE_FLTOVF, FPE_FLTUND ;
+CONST int FPE_FLTRES, FPE_FLTINV, FPE_FLTSUB ;
+CONST int SEGV_MAPERR, SEGV_ACCERR ;
+CONST int BUS_ADRALN, BUS_ADRERR, BUS_OBJERR ;
+CONST int TRAP_BRKPT, TRAP_TRACE ;
+CONST int CLD_EXITED, CLD_KILLED, CLD_DUMPED, CLD_TRAPPED, CLD_STOPPED ;
+CONST int CLD_CONTINUED ;
+CONST int POLL_IN, POLL_OUT, POLL_MSG, POLL_ERR, POLL_PRI ;
