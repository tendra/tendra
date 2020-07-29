# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# 4.5 MATHEMATICS <math.h>
+EXP double HUGE_VAL;

+SUBSET "func" := {
	# 4.5.2.n Trigonometric functions
	+FUNC double acos(double);
	+FUNC double asin(double);
	+FUNC double atan(double);
	+FUNC double atan2(double, double);
	+FUNC double cos(double);
	+FUNC double sin(double);
	+FUNC double tan(double);

	# 4.5.3.n Hyperbolic functions
	+FUNC double cosh(double);
	+FUNC double sinh(double);
	+FUNC double tanh(double);

	# 4.5.4.n Exponential and logarithmic functions
	+FUNC double exp(double);
	+FUNC double frexp(double, int *);
	+FUNC double ldexp(double, int);
	+FUNC double log(double);
	+FUNC double log10(double);
	+FUNC double modf(double, double *);

	# 4.5.5.n Power functions
	+FUNC double pow(double, double);
	+FUNC double sqrt(double);

	# 4.5.6.n Nearest integer, absolute value, and remainder functions
	+FUNC double ceil(double);
	+FUNC double fabs(double);
	+FUNC double floor(double);
	+FUNC double fmod(double, double);
};

