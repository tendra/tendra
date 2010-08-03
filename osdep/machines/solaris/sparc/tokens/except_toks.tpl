/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/
/*
    Exception tokens for sparctrans
*/

Common __sparc_stack_limit : pointer (locals_alignment) = 
                            make_null_ptr(locals_alignment);

Common __sparc_errhandler : proc; /* initialised by ~Set_signal_handler */

Tokdec ~Throw: [NAT] EXP;
Tokdec ansi.stdlib.abort : [] EXP;
Tokdec ansi.signal.SIGFPE : [] EXP;
Tokdec ansi.signal.SIGSEGV : [] EXP;
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
	ansi.stdlib.abort ;
  | ?{	? (* err == + error_val(stack_overflow)(Int));
	~Throw[error_val(stack_overflow)];
	ansi.stdlib.abort ;
    |	~Throw[error_val(nil_access)];
	ansi.stdlib.abort ;
  } }
}


Var sigact : posix.signal.struct_sigaction
{
  __sparc_errhandler = errhandler;
  posix.signal.sigemptyset [allsigs];
  (sigact *+. posix.signal.sigaction.sa_handler) = ovhandler;
  posix.signal.sigemptyset [sigact *+. posix.signal.sigaction.sa_mask];
  (sigact *+. posix.signal.sigaction.sa_flags) = 0(Int);
  posix.signal.sigaction [ ansi.signal.SIGFPE, sigact, 
		make_null_ptr (alignment (posix.signal.struct_sigaction)) ];
  (sigact *+. posix.signal.sigaction.sa_handler) = nil_access_handler;
  posix.signal.sigaction [ansi.signal.SIGSEGV,sigact,
		 make_null_ptr(alignment(posix.signal.struct_sigaction)) ];
  env_size (errhandler)
};


Keep (~Set_signal_handler, ~Sync_handler, __sparc_errhandler, 
      __sparc_stack_limit)



