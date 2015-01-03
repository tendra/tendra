/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

	/* **************************************************** */
	/*							*/
	/* Target Dependency Token Definitions for lin_i386	*/
	/*							*/
	/* **************************************************** */




	/* LOCAL TOKENS */


Tokdef REP_V = [] VARIETY
	/* variety for integer widths and float_sequence */
var_width (false, 16);


Tokdef NATTEST = [a:NAT, comp:NTEST, b:NAT] EXP
	/* comparison of nats, for static conditionals */
? { ?(snat_from_nat(false,a)(REP_V) comp snat_from_nat(false,b)(REP_V));
    1(REP_V)
  | 0(REP_V)
};




	/* INTEGER VARIETY REPRESENTATIONS */


Tokdef .~rep_var_width = [w:NAT] NAT
NAT ? ( NATTEST [w, <=, 8],
  8,
  NAT ? ( NATTEST [w, <=, 16],
    16,
    NAT ? ( NATTEST [w, <=, 32],
      32,
      NAT ? ( NATTEST [w, <=, 64],
	64,
	0
      )
    )
  )
);


Tokdef .~rep_atomic_width = [] NAT
32;




	/* NON-NUMERIC REPRESENTATIONS */


Tokdef .~best_div = [] NAT
2;


Tokdef .~little_endian = [] BOOL
true;




Keep (
.~rep_var_width, .~rep_atomic_width,
.~best_div, .~little_endian
)
