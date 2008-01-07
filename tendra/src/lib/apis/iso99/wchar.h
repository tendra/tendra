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
+USE "ansi", "stdarg.h", "va_list";
+USE "iso99", "stdio.h", "_file";

+IMPLEMENT "iso99", "stddef.h", "null";
+IMPLEMENT "iso99", "stddef.h", "size_t";
+IMPLEMENT "iso99", "stddef.h", "wchar_t";
+IMPLEMENT "iso99", "stdint.h", "wchar_max";

# 7.24.1

+TYPE mbstate_t;

+SUBSET "_wint_t" := {
    +IFNDEF ~building_libs
    +TYPE (int) ~wint_t.1 | wint_t.1;
    +ELSE
    +TYPE (int) wint_t.2 | wint_t.2;
    +TYPEDEF wint_t ~wint_t.2;
    +ENDIF
};

+SUBSET "wint" := {
    +USE "iso99", "wchar.h", "_wint_t";
    +IFNDEF ~building_libs
    +TYPEDEF ~wint_t wint_t;
    +ENDIF
    +CONST wint_t WEOF;
};

# 7.24.2.1

+FUNC int fwprintf(~FILE * restrict, const wchar_t * restrict, ...);

# 7.24.2.2

+FUNC int fwscanf(~FILE * restrict, const wchar_t * restrict, ...);

# 7.24.2.3

+FUNC int swprintf(wchar_t * restrict, size_t, const wchar_t * restrict, ...);

# 7.24.2.4

+FUNC int swscanf(const wchar_t * restrict, const wchar_t * restrict, ...);

# 7.24.2.5

+FUNC int vfwprintf(~FILE * restrict, const wchar_t * restrict, ~va_list);

# 7.24.2.6

+FUNC int vfwscanf(~FILE * restrict, const wchar_t * restrict, ~va_list);

# 7.24.2.7

+FUNC int vswprintf(wchar_t * restrict, size_t, const wchar_t * restrict,
		    ~va_list);

# 7.24.2.8

+FUNC int vswscanf(const wchar_t * restrict, const wchar_t * restrict,
		   ~va_list);

# 7.24.2.9

+FUNC int vwprintf(const wchar_t * restrict, ~va_list);

# 7.24.2.10

+FUNC int vwscanf(const wchar_t * restrict, ~va_list);

# 7.24.2.11

+FUNC int wprintf(const wchar_t * restrict, ...);

# 7.24.2.12

+FUNC int wscanf(const wchar_t * restrict, ...);

# 7.24.3.1

+FUNC wint_t fgetwc(~FILE *);

# 7.24.3.2

+FUNC wchar_t *fgetws(wchar_t * restrict, int, ~FILE * restrict);

# 7.24.3.3

+FUNC wint_t fputwc(wchar_t, ~FILE *);

# 7.24.3.4

+FUNC int fputws(const wchar_t * restrict, ~FILE * restrict);

# 7.24.3.5

+FUNC int fwide(~FILE *, int);

# 7.24.3.6

+FUNC wint_t getwc(~FILE *);

# 7.24.3.7

+FUNC wint_t getwchar(void);

# 7.24.3.8

+FUNC wint_t putwc(wchar_t, ~FILE *);

# 7.24.3.9

+FUNC wint_t putwchar(wchar_t);

# 7.24.3.10

+FUNC wint_t ungetwc(wint_t, ~FILE *);

# 7.24.4.1.1

+FUNC double wcstod(const wchar_t * restrict, wchar_t ** restrict);
+FUNC float wcstof(const wchar_t * restrict, wchar_t ** restrict);
+FUNC long double wcstold(const wchar_t * restrict, wchar_t ** restrict);

# 7.24.4.1.2

+FUNC long int wcstol(const wchar_t * restrict, wchar_t ** restrict, int);
+FUNC long long int wcstoll(const wchar_t * restrict, wchar_t ** restrict, int);
+FUNC unsigned long int wcstoul(const wchar_t * restrict, wchar_t ** restrict,
				int);
+FUNC unsigned long long int wcstoull(const wchar_t * restrict,
				      wchar_t ** restrict, int);

# 7.24.4.2.1

+FUNC wchar_t *wcscpy(wchar_t * restrict, const wchar_t * restrict);

# 7.24.4.2.2

+FUNC wchar_t *wcsncpy(wchar_t * restrict, const wchar_t * restrict, size_t);

# 7.24.4.2.3

+FUNC wchar_t *wmemcopy(wchar_t * restrict, const wchar_t * restrict, size_t);

# 7.24.4.2.4

+FUNC wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t);

# 7.24.4.3.1

+FUNC wchar_t *wcscat(wchar_t * restrict, const wchar_t * restrict);

# 7.24.4.3.2

+FUNC wchar_t *wcsncat(wchar_t * restrict, const wchar_t * restrict, size_t);

# 7.24.4.4.1

+FUNC int wcscmp(const wchar_t *, const wchar_t *);

# 7.24.4.4.2

+FUNC int wcscoll(const wchar_t *, const wchar_t *);

# 7.24.4.4.3

+FUNC int wcsncmp(const wchar_t *, const wchar_t *, size_t);

# 7.24.4.4.4

+FUNC size_t wcsxfrm(wchar_t * restrict, const wchar_t * restrict, size_t);

# 7.24.4.4.5

+FUNC int wmemcmp(const wchar_t *, const wchar_t *, size_t);

# 7.24.4.5.1

+FUNC wchar_t *wcschr(const wchar_t *, wchar_t);

# 7.24.4.5.2

+FUNC size_t wcscspn(const wchar_t *, const wchar_t *);

# 7.24.4.5.3

+FUNC wchar_t *wcspbrk(const wchar_t *, const wchar_t *);

# 7.24.4.5.4

+FUNC wchar_t *wcsrchr(const wchar_t *, wchar_t);

# 7.24.4.5.5

+FUNC size_t wcsspn(const wchar_t *, const wchar_t *);

# 7.24.4.5.6

+FUNC wchar_t *wcsstr(const wchar_t *, const wchar_t *);

# 7.24.4.5.7

+FUNC wchar_t *wcstok(wchar_t * restrict, const wchar_t * restrict,
		      wchar_t ** restrict);

# 7.24.4.5.8

+FUNC wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);

# 7.24.4.6.1

+FUNC size_t wcslen(const wchar_t *);

# 7.24.4.6.2

+FUNC wchar_t *wmemset(wchar_t *, wchar_t, size_t);

# 7.24.5.1

+FUNC size_t wcsftime(wchar_t * restrict, size_t, const wchar_t * restrict,
		      const struct tm * restrict);

# 7.24.6.1.1

+FUNC wint_t btowc(int);

# 7.24.6.1.2

+FUNC int wctob(wint_t);

# 7.24.6.2.1

+FUNC int mbsinit(const mbstate_t *);

# 7.24.6.3.1

+FUNC size_t mbrlen(const char * restrict, size_t, mbstate_t * restrict);

# 7.24.6.3.2

+FUNC size_t mbrtowc(wchar_t * restrict, const char * restrict, size_t,
		     mbstate_t * restrict);

# 7.24.6.3.3

+FUNC size_t wcrtomb(char * restrict, wchar_t, mbstate_t * restrict);

# 7.24.6.4.1

+FUNC size_t mbsrtowcs(wchar_t * restrict, const char ** restrict, size_t,
		       mbstate_t * restrict);

# 7.24.6.4.2

+FUNC size_t wcsrtombs(char * restrict, const wchar_t ** restrict, size_t,
		       mbstate_t * restrict);
