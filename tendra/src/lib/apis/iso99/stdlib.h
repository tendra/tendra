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
+IMPLEMENT "ansi", "stddef.h", "null";
+IMPLEMENT "ansi", "stddef.h", "size_t";
+IMPLEMENT "ansi", "stddef.h", "wchar_t";

# 7.20

+FIELD (struct) div_t { int quot, rem; };
+FIELD (struct) ldiv_t { long int quot, rem; };
+FIELD (struct) lldiv_t { long long int quot, rem; };
+CONST int EXIT_FAILURE, EXIT_SUCCESS;
+CONST int RAND_MAX;
+EXP size_t MB_CUR_MAX;

# 7.20.1.1

+FUNC double atof(const char *);

# 7.20.1.2

+FUNC int atoi(const char *);
+FUNC long int atol(const char *);
+FUNC long long int atoll(const char *);

# 7.20.1.3

+FUNC double strtod(const char * restrict, char ** restrict);
+FUNC float strtof(const char * restrict, char ** restrict);
+FUNC long double strtold(const char * restrict, char ** restrict);

# 7.20.1.4

+FUNC long int strtol(const char * restrict, char ** restrict, int);
+FUNC long long int strtoll(const char * restrict, char ** restrict, int);
+FUNC unsigned long int strtoul(const char * restrict, char ** restrict, int);
+FUNC unsigned long long int strtoull(const char * restrict, char ** restrict,
				      int);

# 7.20.2.1

+FUNC int rand(void);

# 7.20.2.2

+FUNC void srand(unsigned int);

# 7.20.3.1

+FUNC void *calloc(size_t, size_t);

# 7.20.3.2

+FUNC void free(void *);

# 7.20.3.3

+FUNC void *malloc(size_t);

# 7.20.3.4

+FUNC void *realloc(void *, size_t);

# 7.20.4.1

+FUNC void abort(void);

# 7.20.4.2

+FUNC int atexit(void (*)(void));

# 7.20.4.3

+FUNC void exit(int);

# 7.20.4.4

+FUNC void _Exit(int);

# 7.20.4.5

+FUNC char *getenv(const char *);

# 7.20.4.6

+FUNC int system(const char *);

# 7.20.5.1

+FUNC void *bsearch(const void *, const void *, size_t, size_t,
		    int (*)(const void *, const void *));

# 7.20.5.2

+FUNC void qsort(void *, size_t, size_t, int (*)(const void *, const void *));

# 7.20.6.1

+FUNC int abs(int);
+FUNC long int labs(long int);
+FUNC long long int llabs(long long int);

# 7.20.6.2

+FUNC div_t div(int, int);
+FUNC ldiv_t ldiv(long int, long int);
+FUNC lldiv_t lldiv(long long int, long long int);

# 7.20.7.1

+FUNC int mblen(const char *, size_t);

# 7.20.7.2

+FUNC int mbtowc(wchar_t * restrict, const char * restrict, size_t);

# 7.20.7.3

+FUNC int wctomb(char *, wchar_t);

# 7.20.8.1

+FUNC size_t mbstowcs(wchar_t * restrict, const char * restrict, size_t);

# 7.20.8.2

+FUNC size_t wcstombs(char * restrict, const wchar_t * restrict, size_t);
