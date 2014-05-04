/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    Exception tokens for sparctrans
*/

Common __sparc_stack_limit : pointer (locals_alignment) = 
                            make_null_ptr(locals_alignment);

Common __sparc_errhandler : proc; /* initialised by ~Set_signal_handler */

Tokdec ~Throw: [NAT] EXP;
Tokdec c89.stdlib.abort : [] EXP;
Tokdec c89.signal.SIGFPE : [] EXP;
Tokdec c89.signal.SIGSEGV : [] EXP;
Tokdec posix.signal.SIGUSR1 : [] EXP;
Tokdec posix.signal.SIG_SETMASK : [] EXP;
Tokdec posix.signal.sigaction : [EXP, EXP, EXP] EXP;
Tokdec posix.signal.sigemptyset : [EXP] EXP;
Tokdec posix.signal.sigset_t : [] SHAPE;
Tokdec posix.signal.struct_sigaction : [] SHAPE;
Tokdec posix.signal.sigaction.sa_handler : [] EXP;
Tokdec posix.signal.sigaction.sa_mask : [] EXP;
Tokdec posix.signal.sigaction.sa_flags : [] EXP;
Tokdec posix.signal.sigprocmask : [EXP, EXP, EXP] EXP;

/*
    Sync handler delays subsequent processing until any pending
    exceptions have been raised
*/
Tokdec ~Sync_handler : [] EXP;

Var allsigs : posix.signal.sigset_t;

/*
  Called before any use of error treatment

  Sets up each of the signal handlers
*/
Tokdef ~Set_signal_handler = [] EXP 

Let ovhandler = Proc bottom (sig : Int)
  {
    posix.signal.sigprocmask [posix.signal.SIG_SETMASK, allsigs,
                make_null_ptr (alignment (posix.signal.sigset_t)) ];
    (* __sparc_errhandler) [bottom] (+ error_val(overflow)(Int));
  }


Let nil_access_handler = Proc bottom (sig : Int){
      posix.signal.sigprocmask [posix.signal.SIG_SETMASK, allsigs,
                make_null_ptr (alignment (posix.signal.sigset_t)) ];
      (* __sparc_errhandler) [bottom] (+ error_val(nil_access)(Int));
}



Let errhandler = Proc bottom (err : Int)
{	/* called from numerical exception interrupt or from translated code */
  ?{	? (* err == + error_val(overflow)(Int));
	~Throw[error_val(overflow)];
	c89.stdlib.abort ;
  | ?{	? (* err == + error_val(stack_overflow)(Int));
	~Throw[error_val(stack_overflow)];
	c89.stdlib.abort ;
    |	~Throw[error_val(nil_access)];
	c89.stdlib.abort ;
  } }
}


Var sigact : posix.signal.struct_sigaction
{
  __sparc_errhandler = errhandler;
  posix.signal.sigemptyset [allsigs];
  (sigact *+. posix.signal.sigaction.sa_handler) = ovhandler;
  posix.signal.sigemptyset [sigact *+. posix.signal.sigaction.sa_mask];
  (sigact *+. posix.signal.sigaction.sa_flags) = 0(Int);
  posix.signal.sigaction [ c89.signal.SIGFPE, sigact, 
		make_null_ptr (alignment (posix.signal.struct_sigaction)) ];
  (sigact *+. posix.signal.sigaction.sa_handler) = nil_access_handler;
  posix.signal.sigaction [c89.signal.SIGSEGV,sigact,
		 make_null_ptr(alignment(posix.signal.struct_sigaction)) ];
  env_size (errhandler)
};


Keep (~Set_signal_handler, ~Sync_handler, __sparc_errhandler, 
      __sparc_stack_limit)


