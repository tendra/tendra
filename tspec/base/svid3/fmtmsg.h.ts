# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


/* Also see pfmt.h - the MM values are not necessarily the same! */

+CONST long MM_HARD, MM_SOFT, MM_FIRM, MM_APPL, MM_UTIL, MM_OPSYS, MM_PRINT ;
+CONST int MM_CONSOLE, MM_RECOVER, MM_NRECOV ;

+CONST long MM_HALT, MM_ERROR, MM_WARNING, MM_INFO, MM_NOSEV ;

+IFNDEF MM_NULLLBL
+DEFINE MM_NULLLBL	%% ( ( char * ) NULL ) %% ;
+DEFINE MM_NULLSEV	%% 0 %% ;
+DEFINE MM_NULLMC	%% 0L %% ;
+DEFINE MM_NULLTXT	%% ( ( char * ) NULL ) %% ;
+DEFINE MM_NULLACT	%% ( ( char * ) NULL ) %% ;
+DEFINE MM_NULLTAG	%% ( ( char * ) NULL ) %% ;
+ENDIF

+CONST int MM_OK, MM_NOTOK, MM_NOMSG, MM_NOCON ;

+FUNC int fmtmsg ( long, const char *, int, const char *,
		   const char *, const char * ) ;
