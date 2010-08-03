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
	/* Target Dependency Token Definitions for sol_i386	*/
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


Tokdef PUN = [from_sh:SHAPE, to_sh:SHAPE, val:EXP] EXP
	/* representation preserving conversion */
component (to_sh,
  Cons [ shape_offset(from_sh) .max. shape_offset(to_sh) ] (
    offset_zero(alignment(from_sh)) : val
  ),
  offset_zero(alignment(to_sh))
);


Tokdef PTR_V = [] VARIETY
	/* variety for converted pointers */
var_width (true, 32);




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




	/* FLOATING VARIETY REPRESENTATIONS */

/* sequence: 1=single, 2=double, 3=extended */


Tokdef .~rep_fv = [n:NAT] FLOATING_VARIETY
FLOATING_VARIETY ? ( NATTEST [n, ==, 1],
  flvar_parms (2, 24, 126, 127),
  FLOATING_VARIETY ? ( NATTEST [n, ==, 2],
    flvar_parms (2, 53, 1022, 1023),
    flvar_parms (2, 64, 16382, 16383)	/* n must be in range */
  )
);


Tokdef .~rep_fv_width = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  32,
  NAT ? ( NATTEST [n, ==, 2],
    64,
    NAT ? ( NATTEST [n, ==, 3],
      80,	/* 80 bits memory, increased to 96 by ABI */
      0		/* provides test for end of range */
    )
  )
);


Tokdef .~rep_fv_radix = [n:NAT] NAT
2;


Tokdef .~rep_fv_mantissa = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  24,
  NAT ? ( NATTEST [n, ==, 2],
    53,
    64	/* n must be in range */
  )
);


Tokdef .~rep_fv_min_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  149,
  NAT ? ( NATTEST [n, ==, 2],
    1074,
    16445	/* n must be in range */
  )
);


Tokdef .~rep_fv_max_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
  127,
  NAT ? ( NATTEST [n, ==, 2],
    1023,
    16383	/* n must be in range */
  )
);


Tokdef .~rep_fv_epsilon = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
  (2r1.0 E -23 (.~rep_fv[n])),
  EXP ? ( NATTEST [n, ==, 2],
    (2r1.0 E -52 (.~rep_fv[n])),
    (2r1.0 E -63 (.~rep_fv[n]))	/* n must be in range */
  )
);


Tokdef .~rep_fv_min_val = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
  (2r1.0 E -149 (.~rep_fv[n])),
  EXP ? ( NATTEST [n, ==, 2],
    (2r1.0 E -1074 (.~rep_fv[n])),
    (2r1.0 E -16445 (.~rep_fv[n]))	/* n must be in range */
  )
);


Tokdef .~rep_fv_max_val = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
  (8r3.77777774 E 42
    (.~rep_fv[n])),
  EXP ? ( NATTEST [n, ==, 2],
    (8r1.777777777777777774 E 341
      (.~rep_fv[n])),
    (8r1.777777777777777777777 E 5461
      (.~rep_fv[n]))		/* n must be in range */
  )
);




	/* NON-NUMERIC REPRESENTATIONS */


Tokdef .~ptr_width = [] NAT
32;


Tokdef .~best_div = [] NAT
2;


Tokdef .~little_endian = [] BOOL
true;




	/* COMMON CONVERSION ROUTINES */


Tokdef .~ptr_to_ptr = [a1:ALIGNMENT, a2:ALIGNMENT, p:EXP] EXP
PUN [ pointer(a1), pointer(a2), p ];


Tokdef .~ptr_to_int = [a:ALIGNMENT, v:VARIETY, p:EXP] EXP
([v] PUN [ pointer(a), integer(PTR_V), p ]);


Tokdef .~int_to_ptr = [v:VARIETY, a:ALIGNMENT, i:EXP] EXP
PUN [ integer(PTR_V), pointer(a), [PTR_V] i ];


Tokdef .~f_to_ptr = [a:ALIGNMENT, fn:EXP] EXP
PUN [ proc, pointer(a), fn ];


Tokdef .~ptr_to_f = [a:ALIGNMENT, p:EXP] EXP
PUN [ pointer(a), proc, p ];




Keep (
.~rep_var_width, .~rep_atomic_width,
.~rep_fv, .~rep_fv_width, .~rep_fv_radix, .~rep_fv_mantissa, .~rep_fv_min_exp, 
.~rep_fv_max_exp, .~rep_fv_epsilon, .~rep_fv_min_val, .~rep_fv_max_val,
.~ptr_width, .~best_div, .~little_endian,
.~ptr_to_ptr, .~ptr_to_int, .~int_to_ptr, .~f_to_ptr, .~ptr_to_f
)
