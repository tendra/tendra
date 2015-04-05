# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+SUBSET "wint_t" := {
	# 7.16.1
	+TYPE (int) wint_t;
	+TYPEDEF ~promote(wint_t) __wint_t | "__wint_t";
	+CONST wint_t WEOF;
};

+SUBSET "mse" := {
	+USE "c/c89", "stdio.h.ts" (!?);
	+USE "c/c89", "time.h.ts"  (!?);

	# 7.16.1
	+IMPLEMENT "c/c89", "stddef.h.ts", "size_t"  (!?);
	+IMPLEMENT "c/c89", "stddef.h.ts", "wchar_t" (!?);
	+IMPLEMENT "c/c89", "stddef.h.ts", "null"    (!?);

	# 7.16.3.n
	+FUNC wint_t fgetwc(FILE *);
	+FUNC wchar_t *fgetws(wchar_t * ~restrict, int, FILE * ~restrict);
	+FUNC int fputws(const wchar_t * ~restrict, FILE * ~restrict);
	+FUNC wint_t getwc(FILE *);
	+FUNC wint_t getwchar(void);
	+FUNC wint_t ungetwc(wint_t, FILE *);

	# 7.16.4.1.n
	+FUNC double wcstod(const wchar_t * ~restrict, wchar_t ** ~restrict);
	+FUNC long wcstol(const wchar_t * ~restrict, wchar_t ** ~restrict, int);
	+FUNC unsigned long wcstoul(const wchar_t * ~restrict, wchar_t ** ~restrict, int);

	# 7.16.4.2.n
	+FUNC wchar_t *wcscpy(wchar_t * ~restrict, const wchar_t * ~restrict);
	+FUNC wchar_t *wcsncpy(wchar_t * ~restrict, const wchar_t * ~restrict, size_t);

	# 7.16.4.3.n
	+FUNC wchar_t *wcscat(wchar_t * ~restrict, const wchar_t * ~restrict);
	+FUNC wchar_t *wcsncat(wchar_t * ~restrict, const wchar_t * ~restrict, size_t);

	# 7.16.4.4.n
	+FUNC int wcscmp(const wchar_t *, const wchar_t *);
	+FUNC int wcsncmp(const wchar_t *, const wchar_t *, size_t);

	# 7.16.4.5.n
	+FUNC size_t wcscspn(const wchar_t *, const wchar_t *);
	+FUNC size_t wcsspn(const wchar_t *, const wchar_t *);
	+FUNC size_t wcslen(const wchar_t *);
	+IFNDEF ~protect("cpp", "cwchar")
	# These are overloaded in C++
	+FUNC wchar_t *wcschr(const wchar_t *, wchar_t);
	+FUNC wchar_t *wcsrchr(const wchar_t *, wchar_t);
	+FUNC wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
	+ENDIF
};

+SUBSET "mse-i18n" := {
	# 7.16.4.4.n
	+FUNC int wcscoll(const wchar_t *, const wchar_t *);
	+FUNC size_t wcsxfrm(wchar_t * ~restrict, const wchar_t * ~restrict, size_t);
};

# 7.16.1
+TYPE mbstate_t;
+SUBSET "ranges" := {
	+CONST wchar_t WCHAR_MAX, WCHAR_MIN; # XXX: should be __wchar_t for promoted type
};

# 7.16.2.n
+FUNC int fwprintf(FILE * ~restrict, const wchar_t * ~restrict, ...);
+FUNC int fwscanf(FILE * ~restrict, const wchar_t * ~restrict, ...);
+FUNC int wprintf(const wchar_t * ~restrict, ...);
+FUNC int wscanf(const wchar_t * ~restrict, ...);
+FUNC int swprintf(wchar_t * ~restrict, size_t, const wchar_t * ~restrict, ...);
+FUNC int swscanf(const wchar_t * ~restrict, const wchar_t * ~restrict, ...);
+FUNC int vfwprintf(FILE * ~restrict, const wchar_t * ~restrict, ~va_list);
+FUNC int vwprintf(const wchar_t * ~restrict, ~va_list);
+FUNC int vswprintf(wchar_t * ~restrict, size_t, const wchar_t * ~restrict, ~va_list);

# 7.16.3.n
+FUNC wint_t fputwc(wchar_t, FILE *);
+FUNC wint_t putwc(wchar_t, FILE *);
+FUNC wint_t putwchar(wchar_t);
+FUNC int fwide(FILE *, int);

# 7.16.4.5.n
+FUNC wchar_t *wcstok(wchar_t * ~restrict, const wchar_t * ~restrict, wchar_t ** ~restrict);
+IFNDEF ~protect("cpp", "cwchar")
# overloaded in C++
+FUNC wchar_t *wcsstr(const wchar_t *, const wchar_t *);
+ENDIF

# 7.16.4.6.n
+IFNDEF ~protect("cpp", "cwchar")
# overloaded in C++
+FUNC wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
+ENDIF
+FUNC int wmemcmp(const wchar_t *, const wchar_t *, size_t);
+FUNC wchar_t *wmemcpy(wchar_t * ~restrict, const wchar_t * ~restrict, size_t);
+FUNC wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t);
+FUNC wchar_t *wmemset(wchar_t *, wchar_t, size_t);

# 7.16.5
+SUBSET "wcsftime" := {
	+FUNC size_t wcsftime(wchar_t * ~restrict, size_t, const wchar_t * ~restrict,
		const struct tm * ~restrict);
};

# 7.16.6.1.n
+FUNC wint_t btowc(int);
+FUNC int wctob(wint_t);

# 7.16.6.2
+FUNC int mbsinit(const mbstate_t *);

# 7.16.6.3.n
+FUNC size_t mbrlen(const char * ~restrict, size_t, mbstate_t * ~restrict);
+FUNC size_t mbrtowc(wchar_t * ~restrict, const char * ~restrict, size_t, mbstate_t * ~restrict);
+FUNC size_t wcrtomb(char * ~restrict, wchar_t, mbstate_t * ~restrict);

# 7.16.6.4.n
+FUNC size_t mbsrtowcs(wchar_t * ~restrict, const char ** ~restrict, size_t, mbstate_t * ~restrict);
+FUNC size_t wcsrtombs(char * ~restrict, const wchar_t ** ~restrict, size_t, mbstate_t * ~restrict);

