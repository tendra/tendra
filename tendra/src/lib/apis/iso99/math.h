# Copyright (c) 2002, The TenDRA Project
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
# $TenDRA$
#

# 7.12

+EXP double HUGE_VAL;
+EXP float HUGE_VALF;
+EXP long double HUGE_VALL;

+EXP float INFINITY;

+EXP float NAN;

# 7.12.3.1

# XXX: +MACRO int fpclassify(real-floating type);

# 7.12.3.2

# XXX: +MACRO int isfinite(real-floating type);

# 7.12.3.3

# XXX: +MACRO int isinf(real-floating type);

# 7.12.3.4

# XXX: +MACRO int isnan(real-floating type);

# 7.12.3.5

# XXX: +MACRO int isnormal(real-floating type);

# 7.12.3.6

# XXX: +MACRO int signbit(real-floating type);

# 7.12.4.1

+FUNC double acos(double);
+FUNC float acosf(float);
+FUNC long double acosl(long double);

# 7.12.4.2

+FUNC double asin(double);
+FUNC float asinf(float);
+FUNC long double asinl(long double);

# 7.12.4.3

+FUNC double atan(double);
+FUNC float atanf(float);
+FUNC long double atanl(long double);

# 7.12.4.4

+FUNC double atan2(double, double);
+FUNC float atan2f(float, float);
+FUNC long double atan2l(long double, long double);

# 7.12.4.5

+FUNC double cos(double);
+FUNC float cosf(float);
+FUNC long double cosl(long double);

# 7.12.4.6

+FUNC double sin(double);
+FUNC float sinf(float);
+FUNC long double sinl(long double);

# 7.12.4.7

+FUNC double tan(double);
+FUNC float tanf(float);
+FUNC long double tanl(long double);

# 7.12.5.1

+FUNC double acosh(double);
+FUNC float acoshf(float);
+FUNC long double acoshl(long double);

# 7.12.5.2

+FUNC double asinh(double);
+FUNC float asinhf(float);
+FUNC long double asinhl(long double);

# 7.12.5.3

+FUNC double atanh(double);
+FUNC float atanhf(float);
+FUNC long double atanhl(long double);

# 7.12.5.4

+FUNC double cosh(double);
+FUNC float coshf(float);
+FUNC long double coshl(long double);

# 7.12.5.5

+FUNC double sinh(double);
+FUNC float sinhf(float);
+FUNC long double sinhl(long double);

# 7.12.5.6

+FUNC double tanh(double);
+FUNC float tanhf(float);
+FUNC long double tanhl(long double);

# 7.12.6.1

+FUNC double exp(double);
+FUNC float expf(float);
+FUNC long double expl(long double);

# 7.12.6.2

+FUNC double exp2(double);
+FUNC float exp2f(float);
+FUNC long double exp2l(long double);

# 7.12.6.3

+FUNC double expm1(double);
+FUNC float expm1f(float);
+FUNC long double expm1l(long double);

# 7.12.6.4

+FUNC double frexp(double, int *);
+FUNC float frexpf(float, int *);
+FUNC long double frexp1(long double, int *);

# 7.12.6.5

+FUNC int ilogb(double);
+FUNC int ilogbf(float);
+FUNC int ilogbl(long double);

# 7.12.6.6

+FUNC double ldexp(double, int);
+FUNC float ldexpf(float, int);
+FUNC long double ldexpl(long double, int);

# 7.12.6.7

+FUNC double log(double);
+FUNC float logf(float);
+FUNC long double logl(long double);

# 7.12.6.8

+FUNC double log10(double);
+FUNC float log10f(float);
+FUNC long double log10l(long double);

# 7.12.6.9

+FUNC double log1p(double); 
+FUNC float log1pf(float);
+FUNC long double log1pl(long double);

# 7.12.6.10

+FUNC double log2(double);
+FUNC float log2f(float);
+FUNC long double log2l(long double);

# 7.12.6.11

+FUNC double logb(double);
+FUNC float logbf(float);
+FUNC long double logbl(long double);

# 7.12.6.12

+FUNC double modf(double, double *);
+FUNC float modff(float, float *);
+FUNC long double modfl(long double, long double *);

# 7.12.6.13

+FUNC double scalbn(double, int);
+FUNC float scalbnf(float, int);
+FUNC long double scalbnl(long double, int);
+FUNC double scalbln(double, long int);
+FUNC float scalblnf(float, long int);
+FUNC long double scalblnl(long double, long int);

# 7.12.7.1

+FUNC double cbrt(double);
+FUNC float cbrtf(float);
+FUNC long double cbrtl(long double);

# 7.12.7.2

+FUNC double fabs(double);
+FUNC float fabsf(float);
+FUNC long double fabsl(long double);

# 7.12.7.3

+FUNC double hypot(double, double);
+FUNC float hypotf(float, float);
+FUNC long double hypotl(long double, long double);

# 7.12.7.4

+FUNC double pow(double, double);
+FUNC float powf(float, float);
+FUNC long double powl(long double, long double);

# 7.12.7.5

+FUNC double sqrt(double);
+FUNC float sqrtf(float);
+FUNC long double sqrtl(long double);
