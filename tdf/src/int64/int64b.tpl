/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file contains the PL_TDF definitions of functions which
 * perform floating-point to 64-bit integer conversions.
 *
 * Since there is a separate function for each rounding mode,
 * code is going to be duplicated; for this reason, TDF tokens
 * have been used:
 *
 *   round_to_smaller: converts assuming 'towards_smaller'
 *   fixup_difference: makes any necessary correction
 *
 * The general format is as follows:
 *
 *   1. Do error checking
 *   2. Call 'round_to_smaller'
 *   3. Make correction with 'fixup_difference
 *
 * (For the functions with rounding mode 'towards_smaller',
 * there is no need to make a correction.)
 */

#include "abstract.tph"

Iddec printf : proc; /* definition provided by ANSI library */
Iddec print_bignum : proc;
Iddec print_sbignum : proc;

/*
 * TDFUshl is a C macro which is defined in the C file which implements
 * the remaining functions in the 64-bit arithmetic library. tdfc2 then
 * outputs it as a TDF token, which is used in this file.
 */

Tokdec TDFUshl : [EXP, EXP, EXP] EXP;

/*
 * Tokens for handling Error Treatments
 */

/*
 * DIV_ZERO_ERROR if distinct from OVERFLOW_ERROR, but the installers
 * don't distinguish, so reflect this here.
 */

Vardec __TDFerror : Int;

Tokdef OVERFLOW_ERROR = [] EXP  __TDFerror = -1(Int);
Tokdef DIV_ZERO_ERROR = [] EXP  OVERFLOW_ERROR;
/* Tokdef DIV_ZERO_ERROR = [] EXP  __TDFerror =  0(Int); */
Tokdef CLEAR_ERRORS   = [] EXP  __TDFerror =  1(Int);

/*
 * Tokens for rounding floating-point number to TDF_INT64
 *
 * (Some of these error treatments must be 'continue',
 *  and some of them may be 'impossible'.)
 */

Tokdef Sround_to_smaller = [new_int:EXP, x:EXP] EXP
{
	(new_int *+. .hi_32) = round_with_mode(continue, toward_smaller, ~INT32,
		floating_div(impossible,
			(* (BigFloat) x),
			4294967296.0(~BigFloat)));

	(new_int *+. .lo_32) = round_with_mode(continue, toward_smaller, ~UINT32,
		floating_minus(impossible,
			(* (BigFloat) x),
			floating_mult(impossible,
				float_int(impossible, ~BigFloat,
					hi_32[* (TDF_INT64) new_int]),
				4294967296.0(~BigFloat))))
};

Tokdef Uround_to_smaller = [new_int:EXP, x:EXP] EXP
{
	(new_int *+. .hi_u32) = round_with_mode(continue, toward_smaller, ~UINT32,
		floating_div(impossible,
			(* (BigFloat) x),
			4294967296.0(~BigFloat)));

	(new_int *+. .lo_u32) = round_with_mode(continue, toward_smaller, ~UINT32,
		floating_minus(impossible,
			(* (BigFloat) x),
			floating_mult(impossible,
				float_int(impossible, ~BigFloat,
					hi_u32[* (TDF_INT64) new_int]),
				4294967296.0(~BigFloat))))
};

/*
 * Tokens for making the correction
 */

Tokdef Sfixup_difference = [new_int:EXP, x:EXP, MODE:ROUNDING_MODE] EXP
	Var new_float  : BigFloat
	Var difference : BigFloat
{
	/* Construct the approximation */
	new_float = floating_plus(impossible,
		float_int(impossible, ~BigFloat, lo_32[* (TDF_INT64) new_int]),
		floating_mult(impossible,
			float_int(impossible, ~BigFloat, hi_32[* (TDF_INT64) new_int]),
			4294967296.0(~BigFloat)));
	difference = floating_minus(impossible,
		(* (BigFloat) x),
		(* new_float));

	? { ? { F? ((* (BigFloat) x) >= 0.0(~BigFloat));
		? (1(~INT32) == round_with_mode(continue, MODE, ~INT32,
			(* difference)) | L)
		|
			? (0(~INT32) == round_with_mode(continue, MODE, ~INT32,
				floating_minus(impossible, (* difference), 1.0(~BigFloat))) | L)
			};

			(new_int *+. .lo_32) = (lo_32[* (TDF_INT64) new_int] + 1(~UINT32));

			? (lo_32[*(TDF_INT64) new_int] == 0(~UINT32) | L);
			(new_int *+. .hi_32) = (hi_32[* (TDF_INT64) new_int] + 1(~INT32))
		| :L: /* answer is correct - do nothing */
			make_top
	};
};

Tokdef Ufixup_difference = [new_int:EXP, x:EXP, MODE:ROUNDING_MODE] EXP
	Var new_float  : BigFloat
	Var difference : BigFloat
{
	/* Construct the approximation */
	new_float = floating_plus(impossible,
		float_int(impossible, ~BigFloat, lo_u32[* (TDF_INT64) new_int]),
		floating_mult(impossible,
			float_int(impossible, ~BigFloat, hi_u32[* (TDF_INT64) new_int]),
			4294967296.0(~BigFloat)));

	difference = floating_minus(impossible,
		(* (BigFloat) x),
		(* new_float));

	? { ? (1(~UINT32) == round_with_mode(continue, MODE, ~UINT32,
		* difference));

		(new_int *+. .lo_u32) = (lo_u32[* (TDF_INT64) new_int] + 1(~UINT32));
		? (lo_u32[* (TDF_INT64) new_int] == 0(~UINT32));
		(new_int *+. .hi_u32) = (hi_u32[* (TDF_INT64) new_int] + 1(~UINT32));
	|
		make_top /* result is correct - do nothing */
	};
};

/*
 * Procedures for SIGNED conversions
 */

/* SIGNED round_towards_negative_infinity */
Proc __TDFUs_R2NINF = INT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x <   9223372036854775808.0(~BigFloat));
	    F? (* x >= -9223372036854775808.0(~BigFloat));
	|
		OVERFLOW_ERROR
	};

	Sround_to_smaller [new_int, x];
	return (PARAM [* new_int])
};

/* SIGNED round_towards_positive_infinity */
Proc __TDFUs_R2PINF = INT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x <=  9223372036854775807.0(~BigFloat));
	    F? (* x >  -9223372036854775809.0(~BigFloat));
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < -9223372036854775808.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_32) = 0(~UINT32);
		(new_int *+. .hi_32) = -2147483648(~INT32);
	|
		Sround_to_smaller [new_int, x];
		Sfixup_difference [new_int, x, toward_larger];
	};

	return (PARAM [* new_int])
};

/* SIGNED round_to_nearest */
Proc __TDFUs_R2NEAR = INT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	/* Use a strict test here else result is undefined */
	? { F? (* x <  9223372036854775807.5(~BigFloat));
	    F? (* x > -9223372036854775807.5(~BigFloat));
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < -9223372036854775808.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_32) = 0(~UINT32);
		(new_int *+. .hi_32) = -2147483648(~INT32);
	|
		Sround_to_smaller [new_int, x];
		Sfixup_difference [new_int, x, to_nearest];
	};

	return (PARAM[* new_int])
};

/* SIGNED round_to_zero */
Proc __TDFUs_R2ZERO = INT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x <  9223372036854775808.0(~BigFloat));
	    F? (* x > -9223372036854775809.0(~BigFloat));
	|
	    OVERFLOW_ERROR
	};

	? { F? (* x < -9223372036854775808.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_32) = 0(~UINT32);
		(new_int *+. .hi_32) = -2147483648(~INT32);
	|
		Sround_to_smaller [new_int, x];
		Sfixup_difference [new_int, x, toward_zero];
	};

	return (PARAM[* new_int])
};

/* SIGNED round_as_state */
Proc __TDFUs_ASSTATE = INT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x <  9223372036854775808.0(~BigFloat));
	    F? (* x > -9223372036854775809.0(~BigFloat));
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < -9223372036854775808.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_32) = 0(~UINT32);
		(new_int *+. .hi_32) = -2147483648(~INT32);
	|
		Sround_to_smaller [new_int, x];
		Sfixup_difference [new_int, x, round_as_state];
	};

	return (PARAM[* new_int])
};

/* Procedures for UNSIGNED conversions */

/* UNSIGNED round_towards_negative_infinity */
Proc __TDFUu_R2NINF = UINT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x < 18446744073709551616.0(~BigFloat));
	    F? (* x >= 0.0(~BigFloat))
	|
		OVERFLOW_ERROR
	};

	Uround_to_smaller [new_int, x];
	return (UPARAM[* new_int])
};

/* UNSIGNED round_towards_positive_infinity */
Proc __TDFUu_R2PINF = UINT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x <= 18446744073709551615.0(~BigFloat));
	    F? (* x > -1.0(~BigFloat))
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < 0.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_u32) = 0(~UINT32);
		(new_int *+. .hi_u32) = 0(~UINT32);
	|
		Uround_to_smaller [new_int, x];
		Ufixup_difference [new_int, x, toward_larger];
	};

	return (UPARAM[* new_int])
};

/* UNSIGNED round_to_nearest */
Proc __TDFUu_R2NEAR = UINT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	/* Use a strict test here else result is undefined */
	? { F? (* x < 18446744073709551615.5(~BigFloat));
	    F? (* x > -0.5(~BigFloat))
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < 0.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_u32) = 0(~UINT32);
		(new_int *+. .hi_u32) = 0(~UINT32);
	|
		Uround_to_smaller [new_int, x];
		Ufixup_difference [new_int, x, to_nearest];
	};

	return (UPARAM[* new_int])
};

/* UNSIGNED round_to_zero */
Proc __TDFUu_R2ZERO = UINT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x < 18446744073709551616.0(~BigFloat));
	    F? (* x > -1.0(~BigFloat))
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < 0.0(~BigFloat)); /* cannot round down */
	    (new_int *+. .lo_u32) = 0(~UINT32);
	    (new_int *+. .hi_u32) = 0(~UINT32);
	|
		Uround_to_smaller [new_int, x];
		Ufixup_difference [new_int, x, toward_zero];
	};

	return (UPARAM[* new_int])
};

/* UNSIGNED round_as_state */
Proc __TDFUu_ASSTATE = UINT64 (x:BigFloat)
	Var new_int : TDF_INT64
{
	CLEAR_ERRORS;

	? { F? (* x < 18446744073709551616.0(~BigFloat));
	    F? (* x > -1.0(~BigFloat))
	|
		OVERFLOW_ERROR
	};

	? { F? (* x < 0.0(~BigFloat)); /* cannot round down */
		(new_int *+. .lo_u32) = 0(~UINT32);
		(new_int *+. .hi_u32) = 0(~UINT32);
	|
		Uround_to_smaller [new_int, x];
		Ufixup_difference [new_int, x, round_as_state];
	};

	return (UPARAM[* new_int])
};

/*
 * Ian Currie suggested this, and I think it works; The identity:
 *
 *   a = 2^32 * lo(a) + lo(a)
 *
 * holds for all a.
 *
 * When a is negative, there is no loss of accuracy due to loss of
 * relative accuracy since both numbers are stored exactly and as
 * long as truncation doesn't occur, the result will be exact.
 * Truncation itself might theoretically be a problem: consider
 *
 * 	 (0xf8000000, n)  	(where n!=0)
 *
 * Here, the significant word is: -0x8000000, so the calculation:
 *
 *   -0x8000000 * 2^32 + n
 *
 * discards a certain number of bits when n is denormalised before
 * the addition. On the other hand, by converting the number to a
 * positive value before doing the conversion, it becomes:
 *
 *   0x7ffffff * 2^32 + (2^32-n)
 *
 * The number of bits discarded from (2^32-n) is one less than the
 * number discarded above from n, and so this appears to give more
 * accuracy in the result. However, this does not seem to occur in
 * practice.
 */

/* None of the floating-point operations here will overflow */

Proc __TDFUs_float = BigFloat (param_a:INT64)
	Var a : TDF_INT64
{
	(a *+. .PARAM) = (* param_a);

	CLEAR_ERRORS;

	Let lo_float = float_int(impossible, ~BigFloat, lo_32[* a])
	Let hi_float = float_int(impossible, ~BigFloat, hi_32[* a])

	{
		return (floating_plus(impossible,
			lo_float,
			floating_mult(impossible,
				hi_float,
				4294967296.0(~BigFloat))));
	}
};

/*
 * No errors here since each 64-bit integer is
 * representable by a 'BIG_FLOAT'.
 */
Proc __TDFUu_float = BigFloat (param_a:UINT64)
	Var a : TDF_INT64
{
	(a *+. .UPARAM) = (* param_a);

	CLEAR_ERRORS;

	Let lo_float = float_int (impossible, ~BigFloat, lo_u32[* a])
	Let hi_float = float_int (impossible, ~BigFloat, hi_u32[* a])

	{
		return (floating_plus(impossible,
			lo_float,
			floating_mult(impossible,
				hi_float,
				4294967296.0(~BigFloat))));
	}
};

/*
 * If n=64, the result overflows unless a=0.
 * Otherwise, checks that the top (n+1) bits
 * are identical - necessary to avoid overflow.
 * Implements an unsigned shift.
 */
Proc __TDFUs_shl = INT64 (param_a:INT64, n:UINT32)
	Var a : TDF_INT64
{
	(a *+. .PARAM) = (* param_a);

	CLEAR_ERRORS;

	? { ? ((* n) == 0(~UINT32));
		return (* param_a)
	|
		make_top
	};

	? { ? ((* n) > 63(~UINT32)); /* This is undefined */
	    ? { ? (lo_32[* a] == 0(~UINT32)); /* unless a = 0 */
		? (hi_32[* a] == 0(~INT32));
		|
			OVERFLOW_ERROR
	    };

	    return (PARAM[const_0])
	|
		make_top /*  0 <= n < 64  */
	};

	Labelled {
		? ((* n) !< 32(~UINT32)		| L_small_shift);
		? (hi_32[* a] !>  0(~INT32)	| L_overflow);
		? (hi_32[* a] !< -1(~INT32)	| L_overflow);
		? (shift_right (change_variety (continue, ~INT32, lo_32[* a]),
				63(~UINT32) - (* n)) == hi_32[* a] | L_overflow)

	| :L_small_shift:
		? (hi_32[* a] == shift_right (shift_left (continue,
			hi_32[* a], (* n)), (* n)) | L_overflow)

	| :L_overflow:
		OVERFLOW_ERROR
	};

	TDFUshl [a, (* a), (* n)];
	return (PARAM[* a])
};

Proc __TDFUs_shr = INT64 (param_a:INT64, n:UINT32)
	Var a : TDF_INT64
	Var new_int : TDF_INT64
{
	(a *+. .PARAM) = (* param_a);

	CLEAR_ERRORS;

	? { ? (* n >= 32(~UINT32));
	    (new_int *+. .lo_32) = change_variety (impossible, ~UINT32,
				 shift_right (hi_32[* a], (* n) - 32(~UINT32)));
	    ? { ? (hi_32[* a] < 0(~INT32));
			(new_int *+. .hi_32) = -1(~INT32)
		|
			(new_int *+. .hi_32) = 0(~INT32)
	    }
	|
	    (new_int *+. .lo_32) = or
			(shift_right(lo_32[* a], (* n)),
			change_variety(impossible, ~UINT32,
			shift_left(continue, hi_32[* a], 32(~UINT32) - (* n))));
		(new_int *+. .hi_32) = shift_right (hi_32[* a], (* n))
	};

	return (PARAM[* new_int])
};

Keep (
	__TDFUs_R2PINF, __TDFUs_R2NINF, __TDFUs_R2NEAR, __TDFUs_R2ZERO, __TDFUs_ASSTATE,
	__TDFUu_R2PINF, __TDFUu_R2NINF, __TDFUu_R2NEAR, __TDFUu_R2ZERO, __TDFUu_ASSTATE,
	__TDFUs_float,  __TDFUu_float,
	__TDFUs_shl,    __TDFUs_shr
)

