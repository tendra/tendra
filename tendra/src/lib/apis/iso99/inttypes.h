# Copyright (c) 2005, The TenDRA Project
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

+IMPLEMENT "iso99", "stdint.h";

+USE "iso99", "stddef.h", "_wchar_t";

# 7.8

+TYPE (struct) imaxdiv_t;

# 7.8.1

# NOT YET IMPLEMENTED
#
# PRI* and SCN* must be macros expanding to character string literals.

# 7.8.2.1

+FUNC intmax_t imaxabs(intmax_t);

# 7.8.2.2

+FUNC imaxdiv_t imaxdiv(intmax_t, intmax_t);

# 7.8.2.3

+FUNC intmax_t strtoimax(const char * restrict, char ** restrict, int);
+FUNC uintmax_t strtoumax(const char * restrict, char ** restrict, int);

# 7.8.2.4

+FUNC intmax_t wcstoimax(const ~wchar_t * restrict, ~wchar_t ** restrict, int);
+FUNC uintmax_t wcstoumax(const ~wchar_t * restrict, ~wchar_t ** restrict, int);
