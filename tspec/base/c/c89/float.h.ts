# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# 4.1.4 Limits <float.h> and <limits.h>

+SUBSET "xpg3_ranges" := {
	+SUBSET "xpg4_ranges" := {
		+EXP int DBL_DIG;
		+EXP double DBL_MAX;
		+EXP int FLT_DIG;
		+EXP float FLT_MAX;
	};
	+EXP double DBL_MIN;
	+EXP float FLT_MIN;
};

+EXP double DBL_EPSILON;
+EXP int DBL_MANT_DIG, DBL_MAX_10_EXP, DBL_MAX_EXP;
+EXP int DBL_MIN_10_EXP, DBL_MIN_EXP;

+EXP float FLT_EPSILON;
+EXP int FLT_MANT_DIG, FLT_MAX_10_EXP, FLT_MAX_EXP;
+EXP int FLT_MIN_10_EXP, FLT_MIN_EXP;
+CONST int FLT_RADIX;
+EXP int FLT_ROUNDS;

+EXP int LDBL_DIG;
+EXP long double LDBL_EPSILON;
+EXP int LDBL_MANT_DIG;
+EXP long double LDBL_MAX;
+EXP int LDBL_MAX_10_EXP, LDBL_MAX_EXP;
+EXP long double LDBL_MIN;
+EXP int LDBL_MIN_10_EXP, LDBL_MIN_EXP;

