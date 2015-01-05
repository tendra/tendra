/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * IEEE 754 Format floating variety representations
 *
 * Sequence:
 *   1 = Single
 *   2 = Double
 *   3 = Double-Extended 80 bit (as used by the x87)
 *   4 = Quad
 */

/* variety for integer widths and float_sequence */
Tokdef REP_V = [] VARIETY
var_width (false, 16);

/* comparison of nats, for static conditionals */
Tokdef NATTEST = [a:NAT, comp:NTEST, b:NAT] EXP
? { ?(snat_from_nat(false,a)(REP_V) comp snat_from_nat(false,b)(REP_V));
	  1(REP_V)
	| 0(REP_V)
};

/* n must be in range */
Tokdef .~rep_fv = [n:NAT] FLOATING_VARIETY
FLOATING_VARIETY ? ( NATTEST [n, ==, 1],
	flvar_parms (2, 24, 126, 127),
	FLOATING_VARIETY ? ( NATTEST [n, ==, 2],
		flvar_parms (2, 53, 1022, 1023),
		FLOATING_VARIETY ? ( NATTEST [n, ==, 3],
			flvar_parms (2, 64, 16382, 16383),
			flvar_parms (2, 113, 16382, 16383)
		)
	)
);

Tokdef .~rep_fv_width = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	32,
	NAT ? ( NATTEST [n, ==, 2],
		64,
		NAT ? ( NATTEST [n, ==, 3],
			80, /* 80 bits memory, increased to 96 by x87 ABI */
			NAT ? ( NATTEST [n, ==, 4],
				128,
				0 /* provides test for end of range */
			)
		)
	)
);

Tokdef .~rep_fv_radix = [n:NAT] NAT
2;

/* n must be in range */
Tokdef .~rep_fv_mantissa = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	24,
	NAT ? ( NATTEST [n, ==, 2],
		53,
		NAT ? ( NATTEST [n, ==, 3],
			64,
			113
		)
	)
);

/* n must be in range */
Tokdef .~rep_fv_min_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	149,
	NAT ? ( NATTEST [n, ==, 2],
		1074,
		NAT ? ( NATTEST [n, ==, 3],
			16445,
			16494
		)
	)
);

/* n must be in range */
Tokdef .~rep_fv_max_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	127,
	NAT ? ( NATTEST [n, ==, 2],
		1023,
		NAT ? ( NATTEST [n, ==, 3],
			16383,
			16383
		)
	)
);

/* n must be in range */
Tokdef .~rep_fv_epsilon = [n:NAT] EXP
	Var r:Int = snat_from_nat(false, n)(Int)
	Labelled {
		Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
		| :l1: 2r1.0 E -23  (.~rep_fv[n])
		| :l2: 2r1.0 E -52  (.~rep_fv[n])
		| :l3: 2r1.0 E -63  (.~rep_fv[n])
		| :l4: 2r1.0 E -112 (.~rep_fv[n])
	};

/* n must be in range */
Tokdef .~rep_fv_min_val = [n:NAT] EXP
	Var r:Int = snat_from_nat(false, n)(Int)
	Labelled {
		Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
		| :l1: 2r1.0 E -149   (.~rep_fv[n])
		| :l2: 2r1.0 E -1074  (.~rep_fv[n])
		| :l3: 2r1.0 E -16445 (.~rep_fv[n])
		| :l4: 2r1.0 E -16494 (.~rep_fv[n])
	};

/* n must be in range */
Tokdef .~rep_fv_max_val = [n:NAT] EXP
	Var r:Int = snat_from_nat(false, n)(Int)
	Labelled {
		Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
		| :l1: 8r3.77777774 E 42                                 (.~rep_fv[n])
		| :l2: 8r1.777777777777777774 E 341                      (.~rep_fv[n])
		| :l3: 8r1.777777777777777777777 E 5461                  (.~rep_fv[n])
		| :l4: 8r1.77777777777777777777777777777777777774 E 5461 (.~rep_fv[n])
	};

/*
 * Here we map IEEE 754 names to the sequence numbers used by ieee754.tpl
 * to index its various TDF tokens. Each index represents a particular width.
 *
 * These sequence numbers are monotonic with respect to the width. So for
 * example, if IEEE 754 half precision representations are ever implemented,
 * the sequence number for iee754_half_rep would need to be 1, and everything
 * else would increment to make space for it.
 *
 * Note these token names are not exposed to TDF at large; they are private
 * to the ieee754-*.tpl files which include this file. In other words, these
 * form an internal abstraction which serves to keep knowledge of the sequence
 * numbers contained within this file only.
 */

Tokdec iee754_half_rep   : [] NAT;   /* not implemented */
Tokdef iee754_float_rep  = [] NAT 1; /* 32 bit */
Tokdef iee754_double_rep = [] NAT 2; /* 64 bit */
Tokdef iee754_ext80_rep  = [] NAT 3; /* 80 bit */
Tokdef iee754_quad_rep   = [] NAT 4; /* 128 bit */

