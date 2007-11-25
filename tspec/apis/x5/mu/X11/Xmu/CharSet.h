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
+USE "x5/t", "X11/Intrinsic.h" ;

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
