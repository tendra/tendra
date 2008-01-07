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
	/*	Spec Token Definitions for HP PA-RISC		*/
	/*	Needs to be linked with posix library		*/
	/*	specific to each platform.			*/
	/*							*/
	/* **************************************************** */


Tokdec ~Throw : [NAT] EXP;

Tokdec ansi.stdlib.abort : [] EXP;
Tokdec ansi.signal.SIGFPE : [] EXP;
Tokdec posix.signal.SIG_SETMASK : [] EXP;
Tokdec posix.signal.sigaction : [EXP, EXP, EXP] EXP;
Tokdec posix.signal.sigemptyset : [EXP] EXP;
Tokdec posix.signal.sigset_t : [] SHAPE;
Tokdec posix.signal.struct_sigaction : [] SHAPE;
Tokdec posix.signal.sigaction.sa_handler : [] EXP;
Tokdec posix.signal.sigaction.sa_mask : [] EXP;
Tokdec posix.signal.sigaction.sa_flags : [] EXP;
Tokdec posix.signal.sigprocmask : [EXP, EXP, EXP] EXP;


Common __TDFstacklim : pointer (locals_alignment)
		= make_null_ptr (locals_alignment);

Common __hppahandler : proc;
	/* Initialised by ~Set_signal_handler */
	/* called from numerical exception interrupt or from translated code */

Tokdef SIGFPE = []SIGNED_NAT 8;
Tokdef SIGBUS = []SIGNED_NAT 10;
Tokdef SIGSEGV = []SIGNED_NAT 11;
Tokdef SIGUSR1 = []SIGNED_NAT 16;
	/* signal numbers - SIGUSR1 is used for stack overflow
	*/

Var allsigs : posix.signal.sigset_t;



Tokdef ~Set_signal_handler = [] EXP
	/* must be called before any possible exceptions */

Let ovhandler = Proc bottom (sig : Int)
  {
    posix.signal.sigprocmask [posix.signal.SIG_SETMASK, allsigs,
		make_null_ptr (alignment (posix.signal.sigset_t)) ];
    (* __hppahandler) [bottom] (SIGFPE(Int));
  }

Let nil_access_handler = Proc bottom (sig : Int)
  {
      posix.signal.sigprocmask [posix.signal.SIG_SETMASK, allsigs,
                make_null_ptr (alignment (posix.signal.sigset_t)) ];
      (* __hppahandler) [bottom] (SIGSEGV(Int));
  }

Let __TDFhandler = Proc bottom (err : Int)
{
  Labelled {
	Case * err (SIGFPE -> overf, 
		    SIGBUS -> nilref1,
		    SIGSEGV -> nilref2,	
		    SIGUSR1 -> stackov)
	| :overf: 
		~Throw[error_val(overflow)] ;
                ansi.stdlib.abort;
	| :nilref1:
		~Throw[error_val(nil_access)] ;
                ansi.stdlib.abort;
	| :nilref2:
		~Throw[error_val(nil_access)] ;
                ansi.stdlib.abort;
	| :stackov:
		~Throw[error_val(stack_overflow)] ;
                ansi.stdlib.abort;
	/* other C signals can be treated similarly */
 };
 return(make_top);
}




Var sigact : posix.signal.struct_sigaction

{
  __hppahandler = __TDFhandler;

  posix.signal.sigemptyset [allsigs]; 
  posix.signal.sigemptyset [sigact *+. posix.signal.sigaction.sa_mask];
  (sigact *+. posix.signal.sigaction.sa_flags) = 0(Int);

  (sigact *+. posix.signal.sigaction.sa_handler) = ovhandler;
  posix.signal.sigaction [ SIGFPE(Int), sigact, 
		make_null_ptr (alignment (posix.signal.struct_sigaction)) ];

  (sigact *+. posix.signal.sigaction.sa_handler) = nil_access_handler;
  posix.signal.sigaction [SIGSEGV(Int),sigact,
                 make_null_ptr(alignment(posix.signal.struct_sigaction)) ];

  posix.signal.sigaction [SIGBUS(Int),sigact,
                 make_null_ptr(alignment(posix.signal.struct_sigaction)) ];

  env_size (__TDFhandler)
};


Tokdef ~Sync_handler = [] EXP make_top;


Keep (~Set_signal_handler, ~Sync_handler, 
	__hppahandler, __TDFstacklim)

