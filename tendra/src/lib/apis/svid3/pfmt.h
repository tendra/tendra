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
+USE "svid3", "", "config" ;

+IF %% __SYSV_UPDATE %%

/* Also see fmtmsg.h - the MM values are not necessarily the same! */
+USE "svid3", "stdio.h" ;
+USE "ansi", "stdarg.h", "va_args" ;

+CONST int MM_NOSTD.1 | MM_NOSTD_pfmt ;
+CONST int MM_STD.1 | MM_STD_pfmt ;
+CONST int MM_NOGET.1 | MM_NOGET_pfmt ;
+CONST int MM_GET.1 | MM_GET_pfmt ;
+CONST int MM_HALT.1 | MM_HALT_pfmt ;
+CONST int MM_ERROR.1 | MM_ERROR_pfmt ;
+CONST int MM_WARNING.1 | MM_WARNING_pfmt ;
+CONST int MM_INFO.1 | MM_INFO_pfmt ;
+CONST int MM_ACTION.1 | MM_ACTION_pfmt ;
+CONST int MM_CONSOLE.1 | MM_CONSOLE_pfmt ;
+CONST int MM_NOCONSOLE.1 | MM_NOCONSOLE_pfmt ;
+CONST int MM_HARD.1 | MM_HARD_pfmt ;
+CONST int MM_SOFT.1 | MM_SOFT_pfmt ;
+CONST int MM_FIRM.1 | MM_FIRM_pfmt ;
+CONST int MM_APPL.1 | MM_APPL_pfmt ;
+CONST int MM_UTIL.1 | MM_UTIL_pfmt ;
+CONST int MM_OPSYS.1 | MM_OPSYS_pfmt ;

+FUNC int pfmt ( FILE *, long, char *, ... ) ;
+FUNC int lfmt ( FILE *, long, char *, ... ) ;
+FUNC int vpfmt ( FILE *, long, char *, va_list ) ;
+FUNC int vlfmt ( FILE *, long, char *, va_list ) ;
+FUNC char *setcat ( const char * ) ;
+FUNC int setlabel ( const char * ) ;

+ENDIF
