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
+IMPLEMENT "iso99", "wchar.h", "wint";

# 7.25.1

+TYPE (int) wctrans_t;
+TYPE (int) wctype_t;

# 7.25.2.1.1

+FUNC int iswalnum(wint_t);

# 7.25.2.1.2

+FUNC int iswalpha(wint_t);

# 7.25.2.1.3

+FUNC int iswblank(wint_t);

# 7.25.2.1.4

+FUNC int iswcntrl(wint_t);

# 7.25.2.1.5

+FUNC int iswdigit(wint_t);

# 7.25.2.1.6

+FUNC int iswgraph(wint_t);

# 7.25.2.1.7

+FUNC int iswlower(wint_t);

# 7.25.2.1.8

+FUNC int iswprint(wint_t);

# 7.25.2.1.9

+FUNC int iswpunct(wint_t);

# 7.25.2.1.10

+FUNC int iswspace(wint_t);

# 7.25.2.1.11

+FUNC int iswupper(wint_t);

# 7.25.2.1.12

+FUNC int iswxdigit(wint_t);

# 7.25.2.2.1

+FUNC wctype_t wctype(const char *);

# 7.25.2.2.2

+FUNC int iswctype(wint_t, wctype_t);

# 7.25.3.1.1

+FUNC wint_t towlower(wint_t);

# 7.25.3.1.2

+FUNC wint_t towupper(wint_t);

# 7.25.3.2.1

+FUNC wctrans_t wctrans(const char *);

# 7.25.3.2.2

+FUNC wint_t towctrans(wint_t, wctrans_t);
