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


Tokdef PUN = [from_sh:SHAPE, to_sh:SHAPE, val:EXP] EXP
	/* representation preserving conversion */
component (to_sh,
  Cons [ shape_offset(from_sh) .max. shape_offset(to_sh) ] (
    offset_zero(alignment(from_sh)) : val
  ),
  offset_zero(alignment(to_sh))
);




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


Tokdef .~best_div = [] NAT
2;


Tokdef .~little_endian = [] BOOL
true;




Keep (
.~rep_var_width, .~rep_atomic_width,
.~rep_fv, .~rep_fv_width, .~rep_fv_radix, .~rep_fv_mantissa, .~rep_fv_min_exp, 
.~rep_fv_max_exp, .~rep_fv_epsilon, .~rep_fv_min_val, .~rep_fv_max_val,
.~best_div, .~little_endian
)
