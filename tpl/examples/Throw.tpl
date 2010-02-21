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


/* This module gives possible definitions for Throw for single process
   error handling. In addition it gives a definition of the token TRY where:
   TRY(body, ev, handler) delivers the result of body if no exceptions occur;
   delivers the result of handler if the first exception in body has
   error_code ev; otherwise Throws ev to an outer context.
*/

Var handler_place:pointer(code_alignment);
	/* The label of the highest exception handler */
Var handler_env: pointer(unite_alignments(locals_alignment,
			callers_alignment(true)));
	/* the environment of the highest exception handler */
Var except_val: Int;
	/* The thrown exception value - just take it be an int */



Tokdef Throw = [err_val:NAT]EXP
{	
	except_val = + err_val(Int);
	long_jump( * handler_env, * handler_place)
};

Tokdef TRY = [body:EXP, err_val:NAT, handler:EXP]EXP
Let ohp = * handler_place
Let ohe = * handler_env
	/* stack old exception handler */
Labelled {
	handler_place = make_local_lv(place);
	handler_env = current_env;
	Let x = body
	{ handler_place = ohp;  handler_env = ohe;
	  	/* reinstate old exception handler on successful body */	
	  x
	 }
       | :place:
        ?{ handler_place = ohp;  handler_env = ohe;
        	/* reinstate old exception handler on exceptional body */	
           ?(* except_val == + err_val(Int));
           	/* is it the right exception? ... */
           handler
           	/* ... then do handler */
         | long_jump(ohp, ohe)
         	/* otherwise re-throw the exception */
         }
};

Keep ( handler_place, handler_env, Throw, TRY, except_val )
