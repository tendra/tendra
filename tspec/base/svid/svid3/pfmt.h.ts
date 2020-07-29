# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_UPDATE %%

/* Also see fmtmsg.h - the MM values are not necessarily the same! */
+USE "svid/svid3", "stdio.h.ts" ;
+USE "c/c89", "stdarg.h.ts", "va_args" ;

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
