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
+USE "ansi", "stddef.h", "size_t" (!?) ;

+CONST int REG_EXTENDED, REG_ICASE, REG_NOSUB, REG_NEWLINE, REG_NOTBOL ;
+CONST int REG_NOTEOL, REG_NOMATCH, REG_BADPAT, REG_ECOLLATE, REG_ECTYPE ;
+CONST int REG_EESCAPE, REG_ESUBREG, REG_EBRACK, REG_EPAREN, REG_EBRACE ;
+CONST int REG_BADBR, REG_ERANGE, REG_ESPACE, REG_BADRPT, REG_ENOSYS ;

+FIELD ( struct ) regex_t {
    size_t re_nsub ;
} ;

+TYPE ( int ) regoff_t ;

+FIELD ( struct ) regmatch_t {
    regoff_t rm_so ;
    regoff_t rm_eo ;
} ;

+FUNC int regcomp ( regex_t *, const char *, int ) ;
+FUNC int regexec ( const regex_t *, const char *, size_t, regmatch_t *, int ) ;
+FUNC size_t regerror ( int, const regex_t *, char *, size_t ) ;
+FUNC void regfree ( regex_t * ) ;
