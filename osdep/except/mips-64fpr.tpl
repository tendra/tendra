/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This is intended for SGI IRIX 32-bit
 */

Common __TDFhandler:proc;
Common __mipshandler:proc;
Common __TDFstacklim:pointer(locals_alignment);

Tokdec c89.signal.signal: [EXP, EXP]EXP;
Tokdec c89.stdlib.exit: [EXP]EXP;

/* signal numbers - SIGUSR1 is used for stack overflow */
Tokdec c89.signal.SIGFPE         : [] EXP;
Tokdec c89.signal.SIGSEGV        : [] EXP;
Tokdec xsh4v2_unix.signal.SIGBUS : [] EXP;
Tokdec posix.signal.SIGUSR1      : [] EXP;

Tokdef SIGFPE  = [] SIGNED_NAT snat_from_nat(false, computed_nat(c89.signal.SIGFPE));
Tokdef SIGSEGV = [] SIGNED_NAT snat_from_nat(false, computed_nat(c89.signal.SIGSEGV));
Tokdef SIGBUS  = [] SIGNED_NAT snat_from_nat(false, computed_nat(xsh4v2_unix.signal.SIGBUS));
Tokdef SIGUSR1 = [] SIGNED_NAT snat_from_nat(false, computed_nat(posix.signal.SIGUSR1));

/* This token must be defined to throw the language specific error value */
Tokdec ~Throw:[NAT]EXP;

/*
 * This PL_TDF was written to target IRIX on 32-bit MIPS. The floating point
 * registers for this are 32-bit wide. The corresponding PL_TDF for Ultrix
 * also targets 32-bit MIPS, and so both systems use ieee754-double.tpl
 * for their floating point representations.
 *
 * However, Struct sigcontext defined here (and for the corresponding PL_TDF
 * for Ultrix) must match the OS's standard C library's datastructure ABI,
 * which is not neccessarily the same as the processor's layout.
 *
 * The reason the PL_TDF differs between Ultrix and IRIX is because their
 * C datastructures differ. That's because IRIX's headers also provide for
 * 64-bit MIPS, whereas Ultrix's do not. IRIX caters for this by defining
 * sigcontext using 64-bit types (on both 64-bit and 32-bit systems).
 *
 * As far as I understand, for IRIX on 32-bit MIPS, half the width is unused
 * space and is 0-padded. I imagine which half depends on the endianness.
 * So, that's why Struct longptr here has two fields; the .hi field is the
 * high bits (as TenDRA's IRIX target is for big-endian MIPS) are padding.
 */

Struct longptr (
	hi:Int,
	lo:Ptr proc
);

Struct sigcontext (
	sc_onstack:Int,
	sc_mask:Int,
	sc_pc:longptr,
	sc_regs:nof(32,longptr),
	sc_fpregs:nof(32,longptr),
	sc_ownedfp:Int,
	sc_fpc_csr:Int,
	sc_fpc_eir:Int,
	sc_ssflags:Int,
	sc_mdhi:longptr,
	sc_mdlo:longptr,
	sc_cause:longptr,
	sc_badvaddr:longptr
);

Tokdef SETREG = [scp:EXP, r:NAT, val:EXP]EXP
{
	((scp *+. .sc_regs) *+. (.lo .+. (Sizeof(longptr) .* (+ r(Int))))) = val
};

Tokdef CAUSE_BD = []SIGNED_NAT 16r80000000;

/* This token must be called before any possible exceptions */
Tokdef ~Set_signal_handler = [] EXP
{
	/*
	 * This procedure is obeyed at an automatic error trap, using signal.
	 * It's action calls __TDFhandler on top of the user stack by overwriting
	 * the relevant registers of the failing process and simply returning.
	 * Could have written this in C.
	 */
	Let mh = Proc top(sig:Int, code:Int, scp:Ptr sigcontext) {
		((* scp *+. .sc_pc) *+. .lo) = * __TDFhandler; /* the pc of the failing process */

		SETREG[* scp, 4, * sig];  /* the first parameter */
		SETREG[* scp, 5, * code]; /* the second parameter */
		SETREG[* scp, 25, * __TDFhandler]; /* required for PIC code  */

		Let x = *(Int)(* scp *+. (.lo .+. .sc_cause))
		{
			/*
			 * the exception could have occurred in a delay slot
			 * - make sure the return does not treat it as one.
			 */
			(* scp *+. (.lo .+. .sc_cause)) = (x And not(CAUSE_BD(Int)))
		};

		/* reinstates the failing process ie does a call of __TDFhandler */
		return(make_top)
    }

	{
		__mipshandler = mh;
		__TDFhandler = Proc top( sig:Int, code:Int)

		/*
		 * This procedure may either be called via __mipshandler or else as a
		 * result of an explicit error test in the user program. It's action is to
		 * throw the language specific error coding.
		 */
		{
			Labelled {
			Case * sig (
				SIGFPE  -> overf,
				SIGBUS  -> nilref1,
				SIGSEGV -> nilref2,
				SIGUSR1 -> stackov)
			| :overf:
				c89.signal.signal[SIGFPE(Int),  * __mipshandler];
				~Throw[error_val(overflow)]
			| :nilref1:
				c89.signal.signal[SIGBUS(Int),  * __mipshandler];
				~Throw[error_val(nil_access)]
			| :nilref2:
				c89.signal.signal[SIGSEGV(Int), * __mipshandler];
				~Throw[error_val(nil_access)]
			| :stackov:
				c89.signal.signal[SIGUSR1(Int), * __mipshandler];
				~Throw[error_val(stack_overflow)]
			/* other C signals can be treated similarly */
			};

			c89.stdlib.exit[* sig];
			return(make_top);
		};

		c89.signal.signal[SIGFPE(Int),  * __mipshandler];
		c89.signal.signal[SIGBUS(Int),  * __mipshandler];
		c89.signal.signal[SIGSEGV(Int), * __mipshandler];
		c89.signal.signal[SIGUSR1(Int), * __mipshandler];

		env_size(mh) .+. (Sizeof(Char) .* 1000(Int))
	}
};

Tokdef ~Sync_handler = [] EXP make_top;

Keep (
	~Set_signal_handler,
	__TDFhandler, ~Sync_handler, __TDFstacklim
)

