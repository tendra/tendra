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
