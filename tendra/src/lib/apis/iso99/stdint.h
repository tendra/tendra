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
+USE "iso99", "stddef.h", "_ptrdiff_t";
+USE "iso99", "stddef.h", "_size_t";
+USE "iso99", "signal.h", "_sig_atomic_t";
+USE "iso99", "wchar.h", "_wint_t";

# 7.18.1.1

+IFNDEF __NO_INT8_T
+TYPE (signed) int8_t;
+TYPE (unsigned) uint8_t;
+ENDIF
+IFNDEF __NO_INT16_T
+TYPE (signed) int16_t;
+TYPE (unsigned) uint16_t;
+ENDIF
+IFNDEF __NO_INT32_T
+TYPE (signed) int32_t;
+TYPE (unsigned) uint32_t;
+ENDIF
+IFNDEF __NO_INT64_T
+TYPE (signed) int64_t;
+TYPE (unsigned) uint64_t;
+ENDIF

# 7.18.1.2

+TYPE (signed) int_least8_t;
+TYPE (signed) int_least16_t;
+TYPE (signed) int_least32_t;
+TYPE (signed) int_least64_t;
+TYPE (unsigned) uint_least8_t;
+TYPE (unsigned) uint_least16_t;
+TYPE (unsigned) uint_least32_t;
+TYPE (unsigned) uint_least64_t;

# 7.18.1.3

+TYPE (signed) int_fast8_t;
+TYPE (signed) int_fast16_t;
+TYPE (signed) int_fast32_t;
+TYPE (signed) int_fast64_t;
+TYPE (unsigned) uint_fast8_t;
+TYPE (unsigned) uint_fast16_t;
+TYPE (unsigned) uint_fast32_t;
+TYPE (unsigned) uint_fast64_t;

# 7.18.1.4

+IFNDEF __NO_INTPTR_T
+TYPE (signed) intptr_t;
+TYPE (unsigned) uintptr_t;
+ENDIF

# 7.18.1.5

+TYPE (signed) intmax_t;
+TYPE (unsigned) uintmax_t;

# 7.18.2.1

+IFNDEF __NO_INT8_T
+CONST int INT8_MIN, INT8_MAX;
+CONST int UINT8_MAX;
+ENDIF
+IFNDEF __NO_INT16_T
+CONST int INT16_MIN, INT16_MAX;
+CONST int UINT16_MAX;
+ENDIF
+IFNDEF __NO_INT32_t
+TYPEDEF ~promote(int32_t) ~int32_t;
+TYPEDEF ~promote(uint32_t) ~uint32_t;
+CONST ~int32_t INT32_MIN, INT32_MAX;
+CONST ~uint32_t UINT32_MAX;
+ENDIF
+IFNDEF __NO_INT64_t
+TYPEDEF ~promote(int64_t) ~int64_t;
+TYPEDEF ~promote(uint64_t) ~uint64_t;
+CONST ~int64_t INT64_MIN, INT64_MAX;
+CONST ~uint64_t UINT64_MAX;
+ENDIF

# 7.18.2.2

+TYPEDEF ~promote(int_least8_t) ~int_least8_t;
+TYPEDEF ~promote(uint_least8_t) ~uint_least8_t;
+CONST ~int_least8_t INT_LEAST8_MIN, INT_LEAST8_MAX;
+CONST ~uint_least8_t UINT_LEAST8_MAX;
+TYPEDEF ~promote(int_least16_t) ~int_least16_t;
+TYPEDEF ~promote(uint_least16_t) ~uint_least16_t;
+CONST ~int_least16_t INT_LEAST16_MIN, INT_LEAST16_MAX;
+CONST ~uint_least16_t UINT_LEAST16_MAX;
+TYPEDEF ~promote(int_least32_t) ~int_least32_t;
+TYPEDEF ~promote(uint_least32_t) ~uint_least32_t;
+CONST ~int_least32_t INT_LEAST32_MIN, INT_LEAST32_MAX;
+CONST ~uint32_t UINT_LEAST32_MAX;
+TYPEDEF ~promote(int_least64_t) ~int_least64_t;
+TYPEDEF ~promote(uint_least64_t) ~uint_least64_t;
+CONST ~int_least64_t INT_LEAST64_MIN, INT_LEAST64_MAX;
+CONST ~uint_least64_t UINT_LEAST64_MAX;

# 7.18.2.3

+CONST int INT_FAST8_MIN, INT_FAST8_MAX;
+CONST int UINT_FAST8_MAX;
+CONST int INT_FAST16_MIN, INT_FAST16_MAX;
+CONST int UINT_FAST16_MAX;
+TYPEDEF ~promote(int_fast32_t) ~int_fast32_t;
+TYPEDEF ~promote(uint_fast32_t) ~uint_fast32_t;
+CONST ~int_fast32_t INT_FAST32_MIN, INT_FAST32_MAX;
+CONST ~uint_fast32_t UINT_FAST32_MAX;
+TYPEDEF ~promote(int_fast64_t) ~int_fast64_t;
+TYPEDEF ~promote(uint_fast64_t) ~uint_fast64_t;
+CONST ~int_fast64_t INT_FAST64_MIN, INT_FAST64_MAX;
+CONST ~uint_fast64_t UINT_FAST64_MAX;

# 7.18.2.4

+IFNDEF __NO_INTPTR_T
+TYPEDEF ~promote(intptr_t) ~intptr_t;
+TYPEDEF ~promote(uintptr_t) ~uintptr_t;
+CONST ~intptr_t INTPTR_MIN, INTPTR_MAX;
+CONST ~uintptr_t UINTPTR_MAX;
+ENDIF

# 7.18.2.5

+CONST intmax_t INTMAX_MIN, INTMAX_MAX;
+CONST uintmax_t UINTMAX_MAX;

# 7.18.3

+CONST __promoted_ptrdiff_t PTRDIFF_MIN, PTRDIFF_MAX;
+CONST __promoted_sig_atomic_t SIG_ATOMIC_MIN, SIG_ATOMIC_MAX;
+CONST __promoted_size_t SIZE_MAX;
+SUBSET "wchar_max" := {
    +USE "iso99", "stddef.h", "_wchar_t";
    +CONST __promoted_wchar_t WCHAR_MIN, WCHAR_MAX;
};
+CONST ~wint_t WINT_MIN, WINT_MAX;

# 7.18.4.1

%% #undef INT8_C %%
%% #undef UINT8_C %%
%% #undef INT16_C %%
%% #undef UINT16_C %%
%% #undef INT32_C %%
%% #undef UINT32_C %%
%% #undef INT64_C %%
%% #undef UINT64_C %%

+DEFINE INT8_C(c) %% ((int_least8_t)+(c)) %%;
+DEFINE UINT8_C(c) %% ((uint_least8_t)+(c)) %%;
+DEFINE INT16_C(c) %% ((int_least16_t)+(c)) %%;
+DEFINE UINT16_C(c) %% ((uint_least16_t)+(c)) %%;
+DEFINE INT32_C(c) %% ((int_least32_t)+(c)) %%;
+DEFINE UINT32_C(c) %% ((uint_least32_t)+(c)) %%;
+DEFINE INT64_C(c) %% ((int_least64_t)+(c)) %%;
+DEFINE UINT64_C(c) %% ((uint_least64_t)+(c)) %%;

# 7.18.4.2

%% #undef INTMAX_C %%
%% #undef UINTMAX_C %%

+DEFINE INTMAX_C(c) %% ((intmax_t)+(c)) %%;
+DEFINE UINTMAX_C(c) %% ((uintmax_t)+(c)) %%;
