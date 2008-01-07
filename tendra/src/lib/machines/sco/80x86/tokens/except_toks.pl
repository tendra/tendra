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
	/* **************************************************** */
	/*							*/
	/*	Spec Token Definitions for trans386		*/
	/*	Needs to be linked with posix library		*/
	/*	specific to each platform.			*/
	/*							*/
	/* **************************************************** */


Tokdec ~Throw : [NAT] EXP;

Tokdec ansi.stdlib.abort : [] EXP;
Tokdec ansi.signal.SIGFPE : [] EXP;
Tokdec ansi.signal.SIGSEGV : [] EXP;
Tokdec posix.signal.SIG_SETMASK : [] EXP;
Tokdec posix.signal.sigaction : [EXP, EXP, EXP] EXP;
Tokdec posix.signal.sigemptyset : [EXP] EXP;
Tokdec posix.signal.sigset_t : [] SHAPE;
Tokdec posix.signal.struct_sigaction : [] SHAPE;
Tokdec posix.signal.sigaction.sa_handler : [] EXP;
Tokdec posix.signal.sigaction.sa_mask : [] EXP;
Tokdec posix.signal.sigaction.sa_flags : [] EXP;
Tokdec posix.signal.sigprocmask : [EXP, EXP, EXP] EXP;


Iddec __trans386_special : proc;	/* special interface to trans386 */

Common __trans386_stack_limit : pointer (locals_alignment)
		= make_null_ptr (locals_alignment);


Common __trans386_errhandler : proc;
	/* Initialised by ~Set_signal_handler */
	/* called from numerical exception interrupt or from translated code */

Var allsigs : posix.signal.sigset_t;


Tokdef ~Set_signal_handler = [] EXP
	/* must be called before any possible exceptions */

Let ovhandler = Proc bottom (sig : Int)
  {
    __trans386_special [top](2(Int));	/* fclex to clear interrupt */
    posix.signal.sigprocmask [posix.signal.SIG_SETMASK, allsigs,
		make_null_ptr (alignment (posix.signal.sigset_t)) ];
    (* __trans386_errhandler) [bottom] (+ error_val(overflow)(Int));
  }

Let nilaccess_handler = Proc bottom (sig : Int)
  {
    posix.signal.sigprocmask [posix.signal.SIG_SETMASK, allsigs,
		make_null_ptr (alignment (posix.signal.sigset_t)) ];
    (* __trans386_errhandler) [bottom] (+ error_val(nil_access)(Int));
  }

Let errhandler = Proc bottom (err : Int)
{	/* called from numerical or nilaccess exception interrupt,
	   or from translated code */
  __trans386_special [top](1(Int));	/* finit for known state before ~Throw */
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

{		/* main body of ~Set_signal_handler */
  __trans386_errhandler = errhandler;
  posix.signal.sigemptyset [allsigs];
  posix.signal.sigemptyset [sigact *+. posix.signal.sigaction.sa_mask];
  (sigact *+. posix.signal.sigaction.sa_flags) = 0(Int);
  (sigact *+. posix.signal.sigaction.sa_handler) = ovhandler;
  posix.signal.sigaction [ ansi.signal.SIGFPE, sigact, 
		make_null_ptr (alignment (posix.signal.struct_sigaction)) ];
  (sigact *+. posix.signal.sigaction.sa_handler) = nilaccess_handler;
  posix.signal.sigaction [ ansi.signal.SIGSEGV, sigact, 
		make_null_ptr (alignment (posix.signal.struct_sigaction)) ];
  env_size (errhandler)
};


Tokdef ~Sync_handler = [] EXP
	/* must be called prior to any action that modifies ~Trap handling */
{
  __trans386_special [top](0(Int));	/* fwait */
};


Keep (~Set_signal_handler, ~Sync_handler, 
	__trans386_errhandler, __trans386_stack_limit)
