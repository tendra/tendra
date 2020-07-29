# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c99", "math.h.ts";
+IMPLEMENT "c/c99", "complex.h.ts";

# union of double, long double, float and complex
+TYPE ~type;

# XXX: how to specify that these type generic macros exist, when they
# have the same names as the underlying functions which take concrete types?
# For now I have specified these as ".2". I think the underlying functions
# ought to be declared +FUNC (extern) instead.

# 7.22 p4
+MACRO ~type acos.2(~type);
+MACRO ~type asin.2(~type);
+MACRO ~type atan.2(~type);
+MACRO ~type acosh.2(~type);
+MACRO ~type asinh.2(~type);
+MACRO ~type atanh.2(~type);
+MACRO ~type cos.2(~type);
+MACRO ~type sin.2(~type);
+MACRO ~type tan.2(~type);
+MACRO ~type cosh.2(~type);
+MACRO ~type sinh.2(~type);
+MACRO ~type tanh.2(~type);
+MACRO ~type exp.2(~type);
+MACRO ~type log.2(~type);
+MACRO ~type pow.2(~type);
+MACRO ~type sqrt.2(~type);
+MACRO ~type fabs.2(~type);

# 7.22 p5
+MACRO ~type atan2.2(~type);
+MACRO ~type fma.2(~type);
+MACRO ~type llround.2(~type);
+MACRO ~type remainder.2(~type);
+MACRO ~type cbrt.2(~type);
+MACRO ~type fmax.2(~type);
+MACRO ~type log10.2(~type);
+MACRO ~type remquo.2(~type);
+MACRO ~type ceil.2(~type);
+MACRO ~type fmin.2(~type);
+MACRO ~type log1p.2(~type);
+MACRO ~type rint.2(~type);
+MACRO ~type copysign.2(~type);
+MACRO ~type fmod.2(~type);
+MACRO ~type log2.2(~type);
+MACRO ~type round.2(~type);
+MACRO ~type erf.2(~type);
+MACRO ~type frexp.2(~type);
+MACRO ~type logb.2(~type);
+MACRO ~type scalbn.2(~type);
+MACRO ~type erfc.2(~type);
+MACRO ~type hypot.2(~type);
+MACRO ~type lrint.2(~type);
+MACRO ~type scalbln.2(~type);
+MACRO ~type exp2.2(~type);
+MACRO ~type ilogb.2(~type);
+MACRO ~type lround.2(~type);
+MACRO ~type tgamma.2(~type);
+MACRO ~type expm1.2(~type);
+MACRO ~type ldexp.2(~type);
+MACRO ~type nearbyint.2(~type);
+MACRO ~type trunc.2(~type);
+MACRO ~type fdim.2(~type);
+MACRO ~type lgamma.2(~type);
+MACRO ~type nextafter.2(~type);
+MACRO ~type floor.2(~type);
+MACRO ~type llrint.2(~type);
+MACRO ~type nexttoward.2(~type);

