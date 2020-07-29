# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE ( "c/c89" ), "stdio.h.ts" (!?) ;
+USE "x5/t", "X11/Intrinsic.h.ts" ;

+FUNC int XmuPrintDefaultErrorMessage ( Display *, XErrorEvent *, FILE * ) ;
+FUNC int XmuSimpleErrorHandler ( Display *, XErrorEvent * ) ;
