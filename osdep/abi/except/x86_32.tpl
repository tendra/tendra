/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Spec Token Definitions for trans.x86_32
 */

Tokdec ~Throw : [NAT] EXP;

Tokdec c89.stdlib.abort : [] EXP;
Tokdec posix.signal.SIG_SETMASK : [] EXP;
Tokdec posix.signal.sigaction : [EXP, EXP, EXP] EXP;
Tokdec posix.signal.sigemptyset : [EXP] EXP;
Tokdec posix.signal.sigset_t : [] SHAPE;
Tokdec posix.signal.struct_sigaction : [] SHAPE;
Tokdec posix.signal.sigaction.sa_handler : [] EXP;
Tokdec posix.signal.sigaction.sa_mask : [] EXP;
Tokdec posix.signal.sigaction.sa_flags : [] EXP;
Tokdec posix.signal.sigprocmask : [EXP, EXP, EXP] EXP;

Tokdec c89.signal.SIGFPE  : [] EXP;
Tokdec c89.signal.SIGSEGV : [] EXP;

Tokdef SIGFPE  = [] SIGNED_NAT snat_from_nat(false, computed_nat(c89.signal.SIGFPE));
Tokdef SIGSEGV = [] SIGNED_NAT snat_from_nat(false, computed_nat(c89.signal.SIGSEGV));

Iddec __trans386_special : proc; /* special interface to trans386 */

Common __trans386_stack_limit : pointer (locals_alignment)
	= make_null_ptr (locals_alignment);

/* Initialised by .~abi_Set_signal_handler */
/* called from numerical exception interrupt or from translated code */
Common __trans386_errhandler : proc;

Var allsigs : posix.signal.sigset_t;

/* must be called before any possible exceptions */
Tokdef .~abi_Set_signal_handler = [] EXP

Let ovhandler = Proc bottom (sig : Int)
{
	__trans386_special [top](2(Int)); /* fclex to clear interrupt */
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

/* called from numerical or nilaccess exception interrupt, or from translated code */
Let errhandler = Proc bottom (err : Int)
{
	__trans386_special [top](1(Int));	/* finit for known state before ~Throw */
	?{ ? (* err == + error_val(overflow)(Int));
		~Throw[error_val(overflow)];
		c89.stdlib.abort ;
	| ?{ ? (* err == + error_val(stack_overflow)(Int));
		  ~Throw[error_val(stack_overflow)];
		  c89.stdlib.abort ;
		| ~Throw[error_val(nil_access)];
		  c89.stdlib.abort ;
		}
	}
}

/* main body of .~abi_Set_signal_handler */
Var sigact : posix.signal.struct_sigaction
{
	__trans386_errhandler = errhandler;

	posix.signal.sigemptyset [allsigs];
	posix.signal.sigemptyset [sigact *+. posix.signal.sigaction.sa_mask];
	(sigact *+. posix.signal.sigaction.sa_flags) = 0(Int);
	(sigact *+. posix.signal.sigaction.sa_handler) = ovhandler;
	posix.signal.sigaction [ SIGFPE(Int), sigact,
		make_null_ptr(alignment(posix.signal.struct_sigaction)) ];
	(sigact *+. posix.signal.sigaction.sa_handler) = nilaccess_handler;
	posix.signal.sigaction [ SIGSEGV(Int), sigact,
		make_null_ptr(alignment(posix.signal.struct_sigaction)) ];

	env_size (errhandler)
};

/* must be called prior to any action that modifies ~Trap handling */
Tokdef .~abi_Sync_handler = [] EXP
{
	__trans386_special [top](0(Int)); /* fwait */
};

Keep (
	.~abi_Set_signal_handler, .~abi_Sync_handler,
	__trans386_errhandler, __trans386_stack_limit
)

