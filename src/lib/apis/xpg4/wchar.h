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
+IMPLEMENT "iso", "wchar.h", "wint" ;
+IMPLEMENT "iso", "wchar.h", "mse" ;
+IMPLEMENT "iso", "wctype.h", "mse2" (!?) ;

+FUNC wint_t fputwc ( wint_t, FILE * ) ;
+FUNC wint_t putwc ( wint_t, FILE * ) ;
+FUNC wint_t putwchar ( wint_t ) ;

+FUNC wchar_t *getws ( wchar_t * ) ;
+FUNC int putws ( const wchar_t * ) ;

+FUNC wchar_t *wcstok ( wchar_t *, const wchar_t * ) ;
+FUNC wchar_t *wcswcs ( const wchar_t *, const wchar_t * ) ;
+FUNC size_t wcsftime ( wchar_t *, size_t, const char *, const struct tm * ) ;
+FUNC int wcswidth ( const wchar_t *, size_t ) ;
+FUNC int wcwidth ( wchar_t ) ;
