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
+USE "svid3", "sys/types.h" ;

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
