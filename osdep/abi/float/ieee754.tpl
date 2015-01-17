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

Tokdef .~rep_fv_radix = [n:NAT] NAT
	2;

Tokdef .~rep_fv_width = [n:NAT] NAT
	computed_nat(
		Var r:Int = snat_from_nat(false, n)(Int)
		Labelled {
			Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4);
			       0   (Int) /* provides test for end of range */
			| :l1: 32  (Int)
			| :l2: 64  (Int)
			| :l3: 80  (Int)
			| :l4: 128 (Int)
		}
	);

/* n must be in range */
Tokdef .~rep_fv_mantissa = [n:NAT] NAT
	computed_nat(
		Var r:Int = snat_from_nat(false, n)(Int)
		Labelled {
			Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
			| :l1: 24  (Int)
			| :l2: 53  (Int)
			| :l3: 64  (Int)
			| :l4: 113 (Int)
		}
	);

/* n must be in range */
Tokdef .~rep_fv_min_exp = [n:NAT] NAT
	computed_nat(
		Var r:Int = snat_from_nat(false, n)(Int)
		Labelled {
			Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
			| :l1: 149   (Int)
			| :l2: 1074  (Int)
			| :l3: 16445 (Int)
			| :l4: 16494 (Int)
		}
	);

/* n must be in range */
Tokdef .~rep_fv_max_exp = [n:NAT] NAT
	computed_nat(
		Var r:Int = snat_from_nat(false, n)(Int)
		Labelled {
			Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
			| :l1: 127   (Int)
			| :l2: 1023  (Int)
			| :l3: 16383 (Int)
			| :l4: 16383 (Int)
		}
	);

/* n must be in range */
Tokdef .~rep_fv = [n:NAT] FLOATING_VARIETY
	flvar_parms(
		.~rep_fv_radix[n],
		.~rep_fv_mantissa[n],
		computed_nat(snat_from_nat(false, .~rep_fv_max_exp[n])(Int) - 1(Int)),
		.~rep_fv_max_exp[n]
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

/* These are minimum normalised values per the float.h *_MIN macros */
/* n must be in range */
Tokdef ieee754_min_val = [n:NAT] EXP
	Var r:Int = snat_from_nat(false, n)(Int)
	Labelled {
		Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
		| :l1: 2r1.0 E -126   (.~rep_fv[n]) /* 1.17549435E-38F */
		| :l2: 2r1.0 E -1022  (.~rep_fv[n]) /* 2.2250738585072014E-308 */
		| :l3: 2r1.0 E -16382 (.~rep_fv[n]) /* 3.36210314311209350626e-4932L */
		| :l4: 2r1.0 E -16382 (.~rep_fv[n]) /* 3.362103143112093506262677817321752603E-4932L */
	};

/* n must be in range */
Tokdef ieee754_max_10_exp = [n:NAT] NAT
	computed_nat(
		Var r:Int = snat_from_nat(false, n)(Int)
		Labelled {
			Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
			| :l1: 38   (Int)
			| :l2: 1024 (Int)
			| :l3: 4932 (Int)
			| :l4: 4932 (Int)
		}
	);

/* n must be in range */
Tokdef ieee754_dig = [n:NAT] NAT
	computed_nat(
		Var r:Int = snat_from_nat(false, n)(Int)
		Labelled {
			Case * r (1 -> l1, 2 -> l2, 3 -> l3, 4 -> l4)
			| :l1:  6 (Int)
			| :l2: 15 (Int)
			| :l3: 18 (Int)
			| :l4: 33 (Int)
		}
	);

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

