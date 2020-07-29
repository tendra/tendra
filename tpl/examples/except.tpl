/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* This module gives the MIPS specific error handling, using C signals
   where possible. Particular language implementations must provide
   definitions of the tokens Throw and Convert_stndard_error as well as
   ensuring that SET_SIGNAL_HANDLER is called before any possible
   exceptions. MAKE_STACK_LIMIT[n] makes a limit of the stack.
*/

Iddec signal:proc;
Iddec exit:proc;
Iddec __mipshandler:proc;

Tokdec Throw:[EXP]EXP;
	/* This token must be defined to throw the language specific error
	value
	*/
Tokdec Convert_standard_error: [NAT]EXP;
	/* This token must be defined to convert TDF ERROR_CODEs to their
	   language specific error values */
	   
Var __TDFstacklim:pointer(alignment(Char));
	/* will contain the stack limit set up by set_stack_limit */
		
Tokdec SIGFPE:[]SIGNED_NAT;
Tokdec SIGBUS:[]SIGNED_NAT;
Tokdec SIGSEGV:[]SIGNED_NAT;
Tokdec SIGUSR1:[]SIGNED_NAT;
	/* Standard C signal numbers - SIGUSR1 is used for stack overflow
	*/
	

Proc __TDFhandler = top( sig:Int, code:Int)
{
/* This procedure may either be called via __mipshandler or else as a
   result of an explicit error test in the user program. It's action is to
   throw the language specific error coding. 
   NB. there always must be enough space to run it on the stack - the offset
   of this space can be found by env_size(__TDFhandler)
*/
   
   Labelled {
	Case * sig (SIGFPE -> overf, SIGBUS -> nilref1, SIGSEGV -> nilref2,	
			SIGUSR1 -> stackov)
	| :overf: 
		signal[top](SIGFPE(Int), __mipshandler);
		Throw[Convert_standard_error[error_val(overflow)]]
	| :nilref1:
		signal[top](SIGBUS(Int), __mipshandler); 
		Throw[Convert_standard_error[error_val(nil_access)]]
	| :nilref2:
		signal[top](SIGSEGV(Int), __mipshandler); 
		Throw[Convert_standard_error[error_val(nil_access)]]
	| :stackov:
		signal[top](SIGUSR1(Int), __mipshandler); 
		Throw[Convert_standard_error[error_val(stack_overflow)]]
	/* other C signals can be treated similarly */
   };
   exit[bottom](* sig)
};


		

Tokdef MAKE_STACK_LIMIT = [s:EXP]EXP
	/* sets the stack limit to be s bytes on top of current stack */
	make_stack_limit(current_env,
	         env_size(__TDFhandler) .+. s, 
		offset_zero(alloca_alignment));
	  	

Tokdef SET_SIGNAL_HANDLER = [] EXP 
{
/* This token must be called before any possible exceptions */
	signal[top](SIGFPE(Int), __mipshandler);
	signal[top](SIGBUS(Int), __mipshandler);
	signal[top](SIGSEGV(Int), __mipshandler);
	signal[top](SIGUSR1(Int), __mipshandler);
};

Keep(__TDFhandler, SET_SIGNAL_HANDLER, __TDFstacklim, MAKE_STACK_LIMIT  )
