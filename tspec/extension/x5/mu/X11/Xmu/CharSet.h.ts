# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

+FUNC void XmuCopyISOLatin1Lowered ( char *, char * ) ;
+FUNC void XmuCopyISOLatin1Uppered ( char *, char * ) ;
+FUNC int XmuCompareISOLatin1 ( char *, char * ) ;
+FUNC int XmuLookupLatin1 ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupLatin2 ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupLatin3 ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupLatin4 ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupKana ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupJISX0201 ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupArabic ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupCyrillic ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupGreek ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupHebrew ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC int XmuLookupAPL ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
