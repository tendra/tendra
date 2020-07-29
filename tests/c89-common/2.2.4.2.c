#include <assert.h>

#include <limits.h>
#include <float.h>

int main(void) {
	/*
	 * S2.2.4.2p1 "A conforming implementation shall document all the limits
	 * specified in this section, which shall be specified in the headers
	 * <limits.h> and <float.h>."
	 */
	{
		assert(CHAR_BIT >= 8);
		assert(SCHAR_MIN <= -127);
		assert(SCHAR_MAX >=  127);
		assert(UCHAR_MAX >=  255);
		assert(CHAR_MIN  <= 0); /* see S2.2.4.2p3 */
		assert(CHAR_MAX  >  0); /* see S2.2.4.2p3 */

		assert(MB_LEN_MAX >= 1);

		assert(SHRT_MIN  <= -32767);
		assert(SHRT_MAX  >=  32767);
		assert(USHRT_MAX >=  65535);

		assert(INT_MIN  <= -32767);
		assert(INT_MAX  >=  32767);
		assert(UINT_MAX >= 65535);

		assert(LONG_MIN  <= -2147483647);
		assert(LONG_MAX  >=  2147483647);
		assert(ULONG_MAX >= 4294967295);
	}

	/*
	 * S2.2.4.2p2 "The values given below shall be replaced by constant
	 * expressions suitable for use in #if preprocessing directives."
	 */
	{
#if CHAR_BIT > 0
#endif
#if SCHAR_MIN > 0
#endif
#if SCHAR_MAX > 0
#endif
#if UCHAR_MAX > 0
#endif
#if CHAR_MIN > 0
#endif
#if CHAR_MAX > 0
#endif
#if MB_LEN_MAX > 0
#endif
#if SHRT_MIN > 0
#endif
#if SHRT_MAX > 0
#endif
#if USHRT_MAX > 0
#endif
#if INT_MIN > 0
#endif
#if INT_MAX > 0
#endif
#if UINT_MAX > 0
#endif
#if LONG_MIN > 0
#endif
#if LONG_MAX > 0
#endif
#if ULONG_MAX > 0
#endif
	}

	/*
	 * S2.2.4.2p3 "If the value of an object of type char sign-extends
	 * when used in an expression, ..."
	 */
	if ((char) -1 == -1) {
		/*
		 * "... the value of CHAR_MIN shall be the same as that of SCHAR_MIN ..."
		 */
		assert(CHAR_MIN == SCHAR_MIN);

		/*
		 * "... and the value of CHAR_MAX shall be the same as that of SCHAR_MAX.
		 */
		assert(CHAR_MAX == SCHAR_MAX);
	}

	/*
	 * S2.2.4.2p3 "... If the value of an object of type char does not
	 * sign-extend when used in an expression, ..."
	 */
	if ((char) -1 != -1) {
		/*
		 * "... the value of CHAR_MIN shall be 0 ..."
		 */
		assert(CHAR_MIN == 0);

		/*
		 * "... and the value of CHAR_MAX shall be the same as that of UCHAR_MAX"
		 */
		assert(CHAR_MAX == UCHAR_MAX);
	}

	/*
	 * S2.2.4.2p6 "FLT_RADIX shall be a constant expression suitable for use
	 * in #if preprocessing directives;"
	 */
	{
#if FLT_RADIX > 0
#endif
	}

	/*
	 * S2.2.4.2p7 "The rounding mode for floating-point addition is
	 * characterized by the value of FLT_ROUNDS: -1 indeterminable,
	 * 0 toward zero, 1 to nearest, 2 toward positive infinity,
	 * 3 toward negative infinity.
	 * All other values for FLT_ROUNDS characterize implementation-defined
	 * rounding behavior.
	 */
	switch (FLT_ROUNDS) {
	case -1: /* UNTESTED: indeterminable */ break;
	case  0: /* UNTESTED: towards zero */   break;
	case  1: /* UNTESTED: nearest */        break;
	case  2: /* UNTESTED: towards +inf */   break;
	case  3: /* UNTESTED: towards -inf */   break;
	default: /* UNTESTED: imp. def */       break;
	}
 
	/*
	 * S2.2.4.2p8 "The values given in the following list shall be replaced by
	 * implementation-defined expressions that shall be equal or greater in
	 * magnitude (absolute value) to those shown, with the same sign."
	 */
	{
		assert(FLT_RADIX >= 2);

		/* UNTESTED: FLT_MANT_DIG */
		/* UNTESTED: DBL_MANT_DIG */
		/* UNTESTED: LDBL_MANT_DIG */

		assert(FLT_DIG  >=  6);
		assert(DBL_DIG  >= 10);
		assert(LDBL_DIG >= 10);

		/* UNTESTED: FLT_MIN_EXP */
		/* UNTESTED: DBL_MIN_EXP */
		/* UNTESTED: LDBL_MIN_EXP */

		assert(FLT_MIN_10_EXP  <= -37);
		assert(DBL_MIN_10_EXP  <= -37);
		assert(LDBL_MIN_10_EXP <= -37);

		/* UNTESTED: FLT_MAX_EXP */
		/* UNTESTED: DBL_MAX_EXP */
		/* UNTESTED: LDBL_MAX_EXP */

		assert(FLT_MAX_10_EXP  >= 37);
		assert(DBL_MAX_10_EXP  >= 37);
		assert(LDBL_MAX_10_EXP >= 37);
	}

	/*
	 * S2.2.4.2p9 "The values given in the following list shall be
	 * replaced by implementation-defined expressions with values
	 * that shall be equal to or greater than those shown."
	 */
	{
		assert(FLT_MAX  >= 1E+37);
		assert(DBL_MAX  >= 1E+37);
		assert(LDBL_MAX >= 1E+37);
	}

	/*
	 * S2.2.4.2p10 "The values given in the following list shall be
	 * replaced by implementation-defined expressions with values
	 * that shall be equal to or smaller than those shown."
	 */
	{
		assert(FLT_EPSILON  <= 1E-5);
		assert(DBL_EPSILON  <= 1E-9);
		assert(LDBL_EPSILON <= 1E-9);

		assert(FLT_MIN  <= 1E-37);
		assert(DBL_MIN  <= 1E-37);
		assert(LDBL_MIN <= 1E-37);
	}

	return 0;
}


