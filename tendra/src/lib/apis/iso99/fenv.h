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

# 7.6

+TYPE fenv_t;
+TYPE fexcept_t;

+IFNDEF __NO_FP_EXCEPTIONS
+CONST int FE_DIVBYZERO;
+CONST int FE_INEXACT;
+CONST int FE_INVALID;
+CONST int FE_OVERFLOW;
+CONST int FE_UNDERFLOW;
+CONST int FE_ALL_EXCEPT;
+ENDIF

+IFNDEF __NO_FP_ROUND_DIRECTIONS
+CONST int FE_DOWNWARD;
+CONST int FE_TONEAREST;
+CONST int FE_TOWARDZERO;
+CONST int FE_UPWARD;
+ENDIF

+EXP const fenv_t *FE_DFL_ENV;

# 7.6.2.1

+FUNC int feclearexcept(int);

# 7.6.2.2

+FUNC int fegetexceptflag(fexcept_t *, int);

# 7.6.2.3

+FUNC int feraiseexcept(int);

# 7.6.2.4

+FUNC int fesetexceptflag(const fexcept_t *, int);

# 7.6.2.5

+FUNC int fetestexcept(int);

# 7.6.3.1

+FUNC int fegetround(void);

# 7.6.3.2

+FUNC int fesetround(int);

# 7.6.4.1

+FUNC int fegetenv(fenv_t *);

# 7.6.4.2

+FUNC int feholdexcept(fenv_t *);

# 7.6.4.3

+FUNC int fesetenv(const fenv_t *);

# 7.6.4.4

+FUNC int feupdateenv(const fenv_t *);
