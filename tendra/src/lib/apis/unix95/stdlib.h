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
+IMPLEMENT "xpg4", "stdlib.h" ;

+FUNC long a64l ( const char * ) ;
+FUNC char *l64a ( long ) ;
+FUNC char *ecvt ( double, int, int *, int * ) ;
+FUNC char *fcvt ( double, int, int *, int * ) ;
+FUNC char *gcvt ( double, int, char * ) ;
+FUNC int getsubopt ( char **, char * const *, char ** ) ;
+FUNC int grantpt ( int ) ;
+FUNC char *initstate ( unsigned, char *, int ) ;
+FUNC char *mktemp ( char * ) ;
+FUNC int mkstemp ( char * ) ;
+FUNC char *ptsname ( int ) ;
+FUNC long random ( void ) ;
+FUNC char *setstate ( char * ) ;
+FUNC void srandom ( unsigned ) ;
+FUNC char *realpath ( const char *, char * ) ;
+FUNC int ttyslot ( void ) ;
+FUNC int unlockpt ( int ) ;
+FUNC void *valloc ( size_t ) ;
