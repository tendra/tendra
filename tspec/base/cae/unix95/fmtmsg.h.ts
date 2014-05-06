# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+CONST long MM_HARD, MM_SOFT, MM_FIRM, MM_APPL, MM_UTIL, MM_OPSYS ;
+CONST long MM_RECOVER, MM_NRECOV ;
+CONST int MM_HALT, MM_ERROR, MM_WARNING, MM_INFO, MM_NOSEV ;

+CONST long MM_PRINT, MM_CONSOLE ;

+IFNDEF MM_NULLLBL
+DEFINE MM_NULLLBL	%% ( ( char * ) NULL ) %% ;
+DEFINE MM_NULLSEV	%% 0 %% ;
+DEFINE MM_NULLMC	%% 0L %% ;
+DEFINE MM_NULLTXT	%% ( ( char * ) NULL ) %% ;
+DEFINE MM_NULLACT	%% ( ( char * ) NULL ) %% ;
+DEFINE MM_NULLTAG	%% ( ( char * ) NULL ) %% ;
+ENDIF

+CONST int MM_OK, MM_NOTOK, MM_NOMSG, MM_NOCON ;

+FUNC int fmtmsg ( long, const char *, int, const char *, const char *,
    const char * ) ;
