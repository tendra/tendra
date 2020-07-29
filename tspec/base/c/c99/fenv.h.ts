# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c99", "math.h.ts", "errhandling";

# 7.6 p3, p4
+TYPE fenv_t;
+TYPE fexcept_t;

# 7.6 p5
+IFNDEF ~have_fenv_exceptions
+CONST int FE_INEXACT;
+CONST int FE_UNDERFLOW;
+ENDIF

# 7.12 p9
+IF %% math_errhandling & MATH_ERREXCEPT %%
+CONST int FE_INVALID;
+CONST int FE_DIVBYZERO;
+CONST int FE_OVERFLOW;
+ENDIF

# 7.6 p6
+CONST int FE_ALL_EXCEPT;

# 7.6 p7
+IFNDEF ~have_fenv_rounding
+CONST int FE_DOWNWARD;
+CONST int FE_TONEAREST;
+CONST int FE_TOWARDZERO;
+CONST int FE_UPWARD;
+ENDIF

# 7.6 p8
+EXP const fenv_t *FE_DFL_ENV;

# 7.6.2.n
+FUNC int feclearexcept(int);
+FUNC int fegetexceptflag(fexcept_t *, int);
+FUNC int feraiseexcept(int);
+FUNC int fesetexceptflag(const fexcept_t *, int);
+FUNC int fetestexcept(int);
+FUNC int fegetround(void);
+FUNC int fesetround(int);
+FUNC int fegetenv(fenv_t *);
+FUNC int feholdexcept(fenv_t *);
+FUNC int fesetenv(const fenv_t *);
+FUNC int feupdateenv(const fenv_t *);

