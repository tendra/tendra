# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c89", "stdarg.h.ts", "va_list";

+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" (!?);
+IMPLEMENT "c/c89", "stddef.h.ts", "null"   (!?);

# 4.9 INPUT/OUTPUT <stdio.h>

+SUBSET "file" := {
	+TYPE FILE;
};

+EXP FILE *stdin, *stdout, *stderr;
+SUBSET "eof" := {
	+CONST int EOF;
};
+CONST int BUFSIZ, FILENAME_MAX, FOPEN_MAX;
+CONST int _IOFBF, _IOLBF, _IONBF, L_tmpnam;
+SUBSET "seek_consts" := {
	+CONST int SEEK_CUR, SEEK_END, SEEK_SET;
};
+SUBSET "tmp_max" := {
	+CONST int TMP_MAX;
};

+IFNDEF __NO_PRINTF_CHECKS
+TYPEDEF ~special("printf") ~printf_string;
+TYPEDEF ~special("scanf")  ~scanf_string;
+ELSE
+TYPEDEF const char * ~printf_string.1;
+TYPEDEF const char * ~scanf_string.1;
+ENDIF

# 4.9.4.n Operations on files
+FUNC int remove (const char *);
+SUBSET "rename" := {
	+FUNC int rename(const char *, const char *);
};
+FUNC FILE *tmpfile(void);
+FUNC char *tmpnam(char *);

# 4.9.5.n File access functions
+FUNC int fclose(FILE *);
+FUNC int fflush(FILE *);
+FUNC FILE *fopen(const char * ~restrict, const char * ~restrict);
+FUNC FILE *freopen(const char * ~restrict, const char * ~restrict,
	FILE * ~restrict);
+FUNC void setbuf(FILE * ~restrict, char * ~restrict);
+IFNDEF __JUST_POSIX
+FUNC int setvbuf(FILE * ~restrict, char * ~restrict, int, size_t);
+ENDIF

# 4.9.6.n Formatted input/output functions
+FUNC int fprintf(FILE * ~restrict, ~printf_string ~restrict, ...);
+FUNC int fscanf(FILE * ~restrict, ~scanf_string ~restrict, ...);
+FUNC int printf(~printf_string ~restrict, ...);
+FUNC int scanf(~scanf_string ~restrict, ...);
+FUNC int sprintf(char * ~restrict, ~printf_string ~restrict, ...);
+FUNC int sscanf(const char * ~restrict, ~scanf_string ~restrict, ...);
+IFNDEF __JUST_POSIX
+FUNC int vprintf(const char * ~restrict, ~va_list);
+FUNC int vfprintf(FILE * ~restrict, const char * ~restrict, ~va_list);
+FUNC int vsprintf(char * ~restrict, const char * ~restrict, ~va_list);
+ENDIF

# 4.9.7.n Character input/output functions
+FUNC int fgetc(FILE *);
+FUNC char *fgets(char * ~restrict, int, FILE * ~restrict);
+FUNC int fputc(int, FILE *);
+FUNC int fputs(const char * ~restrict, FILE * ~restrict);
+FUNC int getc(FILE *);
+FUNC int getchar(void);
+FUNC char *gets(char *);
+FUNC int putc(int, FILE *);
+FUNC int putchar(int);
+FUNC int puts(const char *);
+FUNC int ungetc(int, FILE *);
+FUNC size_t fread(void * ~restrict, size_t, size_t, FILE * ~restrict);
+FUNC size_t fwrite(const void * ~restrict, size_t, size_t, FILE * ~restrict);

# 4.9.9.n File positioning functions
+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+TYPE fpos_t;
+FUNC int fgetpos(FILE * ~restrict, fpos_t * ~restrict);
+FUNC int fsetpos(FILE *, const fpos_t *);
+ENDIF
+ENDIF
+FUNC int fseek(FILE *, long, int);
+FUNC long ftell(FILE *);
+FUNC void rewind(FILE *);

# 4.9.10.n Error-handling functions
+FUNC void clearerr(FILE *);
+FUNC int feof(FILE *);
+FUNC int ferror(FILE *);
+FUNC void perror(const char *);

