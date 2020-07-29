# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stddef.h.ts", "null"    (!?);
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t"  (!?);
+IMPLEMENT "c/c89", "stddef.h.ts", "wchar_t" (!?);

+SUBSET "bottom" := {
	+TYPEDEF ~special("bottom") ~bottom;
};

# 4.10 GENERAL UTILITIES <stdlib.h>
+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+FIELD (struct) div_t  { int  quot, rem; };
+FIELD (struct) ldiv_t { long quot, rem; };
+EXP int MB_CUR_MAX;
+ENDIF
+ENDIF
+CONST int EXIT_FAILURE, EXIT_SUCCESS;
+CONST int RAND_MAX;

# 4.10.1.n String conversion functions
+FUNC double atof(const char *);
+FUNC int atoi(const char *);
+FUNC long atol(const char *);
+IFNDEF __JUST_POSIX
+FUNC double strtod(const char * ~restrict, char ** ~restrict);
+FUNC long strtol(const char * ~restrict, char ** ~restrict, int);
+IFNDEF __JUST_XPG3
+FUNC unsigned long strtoul(const char * ~restrict, char ** ~restrict, int);
+ENDIF
+ENDIF

# 4.10.2.n Pseudo-random sequence generation functions
+FUNC int rand(void);
+FUNC void srand(unsigned int);

# 4.10.3.n Memory management functions
+SUBSET "free" := {
	+FUNC void free(void *);
};
+SUBSET "alloc" := {
	+USE "c/c89", "stddef.h.ts", "size_t" (!?);
	+FUNC void *calloc(size_t, size_t);
	+FUNC void *malloc(size_t);
	+FUNC void *realloc(void *, size_t);
};

# 4.10.4.n Communication with the environment
+FUNC ~bottom abort(void);
+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+FUNC int atexit(void (*) (void));
+ENDIF
+ENDIF
+FUNC ~bottom exit(int);
+FUNC char *getenv(const char *);
+IFNDEF __JUST_POSIX
+SUBSET "system" := {
	+FUNC int system(const char *);
};
+ENDIF

# 4.10.5.n Searching and sorting utilities
+FUNC void *bsearch(const void *, const void *, size_t, size_t,
	int (*) (const void *, const void *));
+FUNC void qsort(void *, size_t, size_t,
	int (*) (const void *, const void *));

# 4.10.6.n Integer arithmetic functions
+FUNC int abs(int);
+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+FUNC div_t div(int, int);
+FUNC long labs(long);
+FUNC ldiv_t ldiv(long, long);
+ENDIF
+ENDIF

# 4.10.7.n Multibyte character functions
+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+FUNC int mblen(const char *, size_t);
+FUNC int mbtowc(wchar_t * ~restrict, const char * ~restrict, size_t);
+FUNC int wctomb(char *, wchar_t);
+ENDIF
+ENDIF

# 4.10.8.n Multibyte string functions
+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+FUNC size_t mbstowcs(wchar_t * ~restrict, const char * ~restrict, size_t);
+FUNC size_t wcstombs(char * ~restrict, const wchar_t * ~restrict, size_t);
+ENDIF
+ENDIF

