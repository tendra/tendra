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

+IMPLEMENT "ansi", "stddef.h", "size_t";
+IMPLEMENT "ansi", "stdio.h", "file";
+IMPLEMENT "ansi", "stdio.h", "eof";
+IMPLEMENT "ansi", "stdio.h", "seek_consts";
+IMPLEMENT "ansi", "stdio.h", "tmp_max";

# 7.19.1

+TYPE fpos_t;
+CONST int _IOFBF, _IOLBF, _IONBF;
+CONST int BUFSIZ;
+CONST int FOPEN_MAX, FILENAME_MAX, L_tmpnam;
+EXP FILE *stdin, *stdout, *stderr;

# 7.19.4.1

+FUNC int remove(const char *);

# 7.19.4.2

+FUNC int rename(const char *, const char *);

# 7.19.4.3

+FUNC FILE *tmpfile(void);

# 7.19.4.4

+FUNC char *tmpnam(char *);

# 7.19.5.1

+FUNC int fclose(FILE *);

# 7.19.5.2

+FUNC int fflush(FILE *);

# 7.19.5.3

+FUNC FILE *fopen(const char * restrict, const char * restrict);

# 7.19.5.4

+FUNC FILE *freopen(const char * restrict, const char * restrict,
		    FILE * restrict);

# 7.19.5.5

+FUNC void setbuf(FILE * restrict, char * restrict);

# 7.19.5.6

+FUNC int setvbuf(FILE * restrict, char * restrict, int, size_t);

# 7.19.6.1

+FUNC int fprintf(FILE * restrict, const char * restrict, ...);

# 7.19.6.2

+FUNC int fscanf(FILE * restrict, const char * restrict, ...);

# 7.19.6.3

+FUNC int printf(const char * restrict, ...);

# 7.19.6.4

+FUNC int scanf(const char * restrict, ...);

# 7.19.6.5

+FUNC int snprintf(char * restrict, size_t, const char * restrict, ...);

# 7.19.6.6

+FUNC int sprintf(char * restrict, const char * restrict, ...);

# 7.19.6.7

+FUNC int sscanf(const char * restrict, const char * restrict, ...);

# 7.19.6.8

+FUNC int vfprintf(FILE * restrict, const char * restrict, ~va_list);

# 7.19.6.9

+FUNC int vfscanf(FILE * restrict, const char * restrict, ~va_list);

# 7.19.6.10

+FUNC int vprintf(const char * restrict, ~va_list);

# 7.19.6.11

+FUNC int vscanf(const char * restrict, ~va_list);

# 7.19.6.12

+FUNC int vsnprintf(char * restrict, size_t, const char * restrict, ~va_list);

# 7.19.6.13

+FUNC int vsprintf(char * restrict, const char * restrict, ~va_list);

# 7.19.6.14

+FUNC int vsscanf(const char * restrict, const char * restrict, ~va_list);

# 7.19.7.1

+FUNC int fgetc(FILE *);

# 7.19.7.2

+FUNC char *fgets(char * restrict, int, FILE * restrict);

# 7.19.7.3

+FUNC int fputc(int, FILE *);

# 7.19.7.4

+FUNC int fputs(const char * restrict, FILE * restrict);

# 7.19.7.5

+FUNC int getc(FILE *);

# 7.19.7.6

+FUNC int getchar(void);

# 7.19.7.7

+FUNC char *gets(char *);

# 7.19.7.8

+FUNC int putc(int, FILE *);

# 7.19.7.9

+FUNC int putchar(int);

# 7.19.7.10

+FUNC int puts(const char *);

# 7.19.7.11

+FUNC int ungetc(int, FILE *);

# 7.19.8.1

+FUNC size_t fread(void * restrict, size_t, size_t, FILE * restrict);

# 7.19.8.2

+FUNC size_t fwrite(const void * restrict, size_t, size_t, FILE * restrict);

# 7.19.9.1

+FUNC int fgetpos(FILE * restrict, fpos_t * restrict);

# 7.19.9.2

+FUNC int fseek(FILE *, long int, int);

# 7.19.9.3

+FUNC int fsetpos(FILE *, const fpos_t *);

# 7.19.9.4

+FUNC long int ftell(FILE *);

# 7.19.9.5

+FUNC void rewind(FILE *);

# 7.19.10.1

+FUNC void clearerr(FILE *);

# 7.19.10.2

+FUNC int feof(FILE *);

# 7.19.10.3

+FUNC int ferror(FILE *);

# 7.19.10.4

+FUNC void perror(const char *);
