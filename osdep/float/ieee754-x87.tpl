/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Floating variety representations
 * Sequence: 1=single, 2=double, 3=extended
 *
 * IEEE 754 Double-Extended Format (x87)
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

Tokdef .~rep_fv = [n:NAT] FLOATING_VARIETY
FLOATING_VARIETY ? ( NATTEST [n, ==, 1],
	flvar_parms (2, 24, 126, 127),
	FLOATING_VARIETY ? ( NATTEST [n, ==, 2],
		flvar_parms (2, 53, 1022, 1023),
		flvar_parms (2, 64, 16382, 16383) /* n must be in range */
	)
);

Tokdef .~rep_fv_width = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	32,
	NAT ? ( NATTEST [n, ==, 2],
		64,
		NAT ? ( NATTEST [n, ==, 3],
			80,	/* 80 bits memory, increased to 96 by ABI */
			0   /* provides test for end of range */
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
		64 /* n must be in range */
	)
);

Tokdef .~rep_fv_min_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	149,
	NAT ? ( NATTEST [n, ==, 2],
		1074,
		16445 /* n must be in range */
	)
);

Tokdef .~rep_fv_max_exp = [n:NAT] NAT
NAT ? ( NATTEST [n, ==, 1],
	127,
	NAT ? ( NATTEST [n, ==, 2],
		1023,
		16383 /* n must be in range */
	)
);

Tokdef .~rep_fv_epsilon = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
	(2r1.0 E -23 (.~rep_fv[n])),
	EXP ? ( NATTEST [n, ==, 2],
		(2r1.0 E -52 (.~rep_fv[n])),
		(2r1.0 E -63 (.~rep_fv[n])) /* n must be in range */
	)
);

Tokdef .~rep_fv_min_val = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
	(2r1.0 E -149 (.~rep_fv[n])),
	EXP ? ( NATTEST [n, ==, 2],
		(2r1.0 E -1074 (.~rep_fv[n])),
		(2r1.0 E -16445 (.~rep_fv[n])) /* n must be in range */
	)
);

Tokdef .~rep_fv_max_val = [n:NAT] EXP
EXP ? ( NATTEST [n, ==, 1],
	(8r3.77777774 E 42 (.~rep_fv[n])),
	EXP ? ( NATTEST [n, ==, 2],
		(8r1.777777777777777774 E 341 (.~rep_fv[n])),
		(8r1.777777777777777777777 E 5461 (.~rep_fv[n])) /* n must be in range */
	)
);

Keep (
	.~rep_fv, .~rep_fv_width, .~rep_fv_radix, .~rep_fv_mantissa, .~rep_fv_min_exp,
	.~rep_fv_max_exp, .~rep_fv_epsilon, .~rep_fv_min_val, .~rep_fv_max_val
)

