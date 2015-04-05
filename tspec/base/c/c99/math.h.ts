# $Id$

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "math.h.ts", "func";

+TYPE (float) ~real;

# 7.12 p2
+IF %% FLT_EVAL_METHOD == 0 %%
+TYPEDEF float float_t.0;
+TYPEDEF float double_t.0;
+ELSE +IF %% FLT_EVAL_METHOD == 1 %%
+TYPEDEF double float_t.1;
+TYPEDEF double double_t.1;
+ELSE +IF %% FLT_EVAL_METHOD == 2 %%
+TYPEDEF long double float_t.2;
+TYPEDEF long double double_t.2;
+ELSE
+TYPE (float) float_t.3;
+TYPE (float) double_t.3;
+ENDIF
+ENDIF
+ENDIF

# 7.12 p3
+CONST double HUGE_VAL; # HUGE_VAL was +EXP (not +CONST) for C89
+CONST float HUGE_VALF;
+CONST long double HUGE_VALL;

# 7.12 p4
+CONST float INFINITY;

# 7.12 p5
+IFDEF ~have_nan
+CONST float NAN;
+ENDIF

# 7.12 p6
+CONST int FP_INFINITE;
+CONST int FP_NAN;
+CONST int FP_NORMAL;
+CONST int FP_SUBNORMAL;
+CONST int FP_ZERO;

# 7.12 p7
+IFDEF ~have_fast_fma
+DEFINE FP_FAST_FMA 1;
+ENDIF
+IFDEF ~have_fast_fmaf
+DEFINE FP_FAST_FMAF 1;
+ENDIF
+IFDEF ~have_fast_fmal
+DEFINE FP_FAST_FMAFL 1;
+ENDIF

# 7.12 p8
+CONST int FP_ILOGB0;
+CONST int FP_ILOGBNAN;

# 7.12 p9
+DEFINE MATH_ERRNO     1;
+SUBSET "errhandling" := {
	+DEFINE MATH_ERREXCEPT 2;
	+EXP int math_errhandling;
};

# 7.12.3.n
+MACRO int fpclassify(~real type);
+MACRO int isfinite(~real type);
+MACRO int isinf(~real type);
+MACRO int isnan(~real type);
+MACRO int isnormal(~real type);
+MACRO int issignbit(~real type);

# 7.12.4.n
+FUNC float acosf(float);
+FUNC long double acosl(long double);
+FUNC float asinf(float);
+FUNC long double asinl(long double);
+FUNC float atanf(float);
+FUNC long double atanl(long double);
+FUNC float atan2f(float, float);
+FUNC long double atan2l(long double, long double);
+FUNC float cosf(float);
+FUNC long double cosl(long double);
+FUNC float sinf(float);
+FUNC long double sinl(long double);
+FUNC float tanf(float);
+FUNC long double tanl(long double);

# 7.12.5.n
+FUNC double acosh(double);
+FUNC float acoshf(float);
+FUNC long double acoshl(long double);
+FUNC double asinh(double);
+FUNC float asinhf(float);
+FUNC long double asinhl(long double);
+FUNC double atanh(double);
+FUNC float atanhf(float);
+FUNC long double atanhl(long double);
+FUNC float coshf(float);
+FUNC long double coshl(long double);
+FUNC float sinhf(float);
+FUNC long double sinhl(long double);
+FUNC float tanhf(float);
+FUNC long double tanhl(long double);

# 7.12.6.n
+FUNC float expf(float);
+FUNC long double expl(long double);
+FUNC double exp2(double);
+FUNC float exp2f(float);
+FUNC long double exp2l(long double);
+FUNC double expm1(double);
+FUNC float expm1f(float);
+FUNC long double expm1l(long double);
+FUNC float frexpf(float, int *);
+FUNC long double frexp1(long double, int *);
+FUNC int ilogb(double);
+FUNC int ilogbf(float);
+FUNC int ilogbl(long double);
+FUNC float ldexpf(float, int);
+FUNC long double ldexpl(long double, int);
+FUNC float logf(float);
+FUNC long double logl(long double);
+FUNC float log10f(float);
+FUNC long double log10l(long double);
+FUNC double log1p(double);
+FUNC float log1pf(float);
+FUNC long double log1pl(long double);
+FUNC double log2(double);
+FUNC float log2f(float);
+FUNC long double log2l(long double);
+FUNC double logb(double);
+FUNC float logbf(float);
+FUNC long double logbl(long double);
+FUNC float modff(float, float *);
+FUNC long double modfl(long double, long double *);
+FUNC double scalbn(double, int);
+FUNC float scalbnf(float, int);
+FUNC long double scalbnl(long double, int);
+FUNC double scalbln(double, long int);
+FUNC float scalblnf(float, long int);
+FUNC long double scalblnl(long double, long int);

# 7.12.7.n
+FUNC double cbrt(double);
+FUNC float cbrtf(float);
+FUNC long double cbrtl(long double);
+FUNC float fabsf(float);
+FUNC long double fabsl(long double);
+FUNC double hypot(double, double);
+FUNC float hypotf(float, float);
+FUNC long double hypotl(long double, long double);
+FUNC float powf(float, float);
+FUNC long double powl(long double, long double);
+FUNC float sqrtf(float);
+FUNC long double sqrtl(long double);

# 7.12.8.n
+FUNC double erf(double);
+FUNC float erff(float);
+FUNC long double erfl(long double);
+FUNC double erfc(double);
+FUNC float erfcf(float);
+FUNC long double erfcl(long double);
+FUNC double lgamma(double);
+FUNC float lgammaf(float);
+FUNC long double lgammal(long double);
+FUNC double tgamma(double);
+FUNC float tgammaf(float);
+FUNC long double tgammal(long double);

# 7.12.9.n
+FUNC float ceilf(float);
+FUNC long double ceill(long double);
+FUNC float floorf(float);
+FUNC long double floorl(long double);
+FUNC double nearbyint(double);
+FUNC float nearbyintf(float);
+FUNC long double nearbyintl(long double);
+FUNC double rint(double);
+FUNC float rintf(float);
+FUNC long double rintl(long double);
+FUNC long int lrint(double);
+FUNC long int lrintf(float);
+FUNC long int lrintl(long double);
+FUNC long long int llrint(double);
+FUNC long long int llrintf(float);
+FUNC long long int llrintl(long double);
+FUNC double round(double);
+FUNC float roundf(float);
+FUNC long double roundl(long double);
+FUNC long int lround(double);
+FUNC long int lroundf(float);
+FUNC long int lroundl(long double);
+FUNC long long int llround(double);
+FUNC long long int llroundf(float);
+FUNC long long int llroundl(long double);
+FUNC double trunc(double);
+FUNC float truncf(float);
+FUNC long double truncl(long double);

# 7.12.10.n
+FUNC float fmodf(float, float);
+FUNC long double fmodl(long double, long double);
+FUNC double remainder(double, double);
+FUNC float remainderf(float, float);
+FUNC long double remainderl(long double, long double);
+FUNC double remquo(double, double, int *);
+FUNC float remquof(float, float, int *);
+FUNC long double remquol(long double, long double, int *);

# 7.12.11.n
+FUNC double copysign(double, double);
+FUNC float copysignf(float, float);
+FUNC long double copysignl(long double, long double);
+FUNC double nan(const char *);
+FUNC float nanf(const char *);
+FUNC long double nanl(const char *);
+FUNC double nextafter(double, double);
+FUNC float nextafterf(float, float);
+FUNC long double nextafterl(long double, long double);
+FUNC double nexttoward(double, long double);
+FUNC float nexttowardf(float, long double);
+FUNC long double nexttowardl(long double, long double);

# 7.12.12.n
+FUNC double fdim(double, double);
+FUNC float fdimf(float, float);
+FUNC long double fdiml(long double, long double);
+FUNC double fmax(double, double);
+FUNC float fmaxf(float, float);
+FUNC long double fmaxl(long double, long double);
+FUNC double fmin(double, double);
+FUNC float fminf(float, float);
+FUNC long double fminl(long double, long double);

# 7.12.13.n
+FUNC double fma(double, double, double);
+FUNC float fmaf(float, float, float);
+FUNC long double fmal(long double, long double, long double);

# 7.12.14.n
+MACRO int isgreater(~real type, ~real type);
+MACRO int isgreaterequal(~real type, ~real type);
+MACRO int isless(~real type, ~real type);
+MACRO int islessequal(~real type, ~real type);
+MACRO int islessgreater(~real type, ~real type);
+MACRO int isunordered(~real type, ~real type);

