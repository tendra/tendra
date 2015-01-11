/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
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

/*
 * Under "Representing integers", the TDF spec says:
 *
 *   Installers may limit the size of VARIETY that they implement.
 *   A statement of such limits shall be part of the specification
 *   of the installer.
 *   In no case may such limits be less than 64 bits, signed or unsigned.
 */

Tokdef .~abi_rep_var_width = [w:NAT] NAT
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

