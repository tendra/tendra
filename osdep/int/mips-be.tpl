/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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

Tokdef .~rep_atomic_width = [] NAT 32;
Tokdef .~best_div         = [] NAT 2;
Tokdef .~little_endian    = [] BOOL false;

Keep (
	.~rep_var_width,
	.~rep_atomic_width, .~best_div, .~little_endian
)

