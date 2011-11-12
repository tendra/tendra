/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
