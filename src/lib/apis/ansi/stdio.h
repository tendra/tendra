#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "ansi", "stdarg.h", "va_list" ;

+IMPLEMENT "ansi", "stddef.h", "size_t" (!?) ;
+IMPLEMENT "ansi", "stddef.h", "null" (!?) ;

+SUBSET "file" := { +TYPE FILE ; } ;

+EXP FILE *stdin, *stdout, *stderr ;
+SUBSET "eof" := { +CONST int EOF ; } ;
+CONST int BUFSIZ, FILENAME_MAX, FOPEN_MAX ;
+CONST int _IOFBF, _IOLBF, _IONBF, L_tmpnam ;
+SUBSET "seek_consts" := { +CONST int SEEK_CUR, SEEK_END, SEEK_SET ; } ;
+SUBSET "tmp_max" := { +CONST int TMP_MAX ; } ;

+IFNDEF __NO_PRINTF_CHECKS
+TYPEDEF ~special ( "printf" ) ~printf_string ;
+TYPEDEF ~special ( "scanf" ) ~scanf_string ;
+ELSE
+TYPEDEF const char * ~printf_string.1 ;
+TYPEDEF const char * ~scanf_string.1 ;
+ENDIF

+FUNC void clearerr ( FILE * ) ;
+FUNC int fclose ( FILE * ) ;
+FUNC int feof ( FILE * ) ;
+FUNC int ferror ( FILE * ) ;
+FUNC int fflush ( FILE * ) ;
+FUNC int fgetc ( FILE * ) ;
+FUNC char *fgets ( char *, int, FILE * ) ;
+FUNC FILE *fopen ( const char *, const char * ) ;
+FUNC int fputc ( int, FILE * ) ;
+FUNC int fputs ( const char *, FILE * ) ;
+FUNC size_t fread ( void *, size_t, size_t, FILE * ) ;
+FUNC FILE *freopen ( const char *, const char *, FILE * ) ;
+FUNC int fseek ( FILE *, long, int ) ;
+FUNC long ftell ( FILE * ) ;
+FUNC size_t fwrite ( const void *, size_t, size_t, FILE * ) ;
+FUNC int getc ( FILE * ) ;
+FUNC int getchar ( void ) ;
+FUNC char *gets ( char * ) ;
+FUNC void perror ( const char * ) ;
+FUNC int putc ( int, FILE * ) ;
+FUNC int putchar ( int ) ;
+FUNC int puts ( const char * ) ;
+FUNC int remove ( const char * ) ;
+SUBSET "rename" := { +FUNC int rename ( const char *, const char * ) ; } ;
+FUNC void rewind ( FILE * ) ;
+FUNC void setbuf ( FILE *, char * ) ;
+FUNC FILE *tmpfile ( void ) ;
+FUNC char *tmpnam ( char * ) ;
+FUNC int ungetc ( int, FILE * ) ;
+FUNC int printf ( ~printf_string, ... ) ;
+FUNC int fprintf ( FILE *, ~printf_string, ... ) ;
+FUNC int sprintf ( char *, ~printf_string, ... ) ;
+FUNC int scanf ( ~scanf_string, ... ) ;
+FUNC int fscanf ( FILE *, ~scanf_string, ... ) ;
+FUNC int sscanf ( const char *, ~scanf_string, ... ) ;

+IFNDEF __JUST_POSIX
+IFNDEF __JUST_XPG3
+TYPE fpos_t ;
+FUNC int fgetpos ( FILE *, fpos_t * ) ;
+FUNC int fsetpos ( FILE *, fpos_t * ) ;
+ENDIF
+FUNC int setvbuf ( FILE *, char *, int, size_t ) ;
+FUNC int vfprintf ( FILE *, const char *, ~va_list ) ;
+FUNC int vprintf ( const char *, ~va_list ) ;
+FUNC int vsprintf ( char *, const char *, ~va_list ) ;
+ENDIF
