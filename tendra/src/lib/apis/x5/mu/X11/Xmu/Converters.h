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
+USE "x5/mu", "X11/StringDefs.h" ;

/* A couple of prototype in the spec are wrong */
+FUNC void XmuCvtFunctionToCallback ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XmuCvtStringToBackingStore ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XmuCvtStringToBitmap ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC Boolean XmuCvtStringToColorCursor ( Display *, XrmValuePtr,
    Cardinal *, XrmValuePtr, XrmValuePtr, XtPointer * ) ;
+FUNC void XmuCvtStringToCursor ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XmuCvtStringToGravity ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XmuCvtStringToJustify ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XmuCvtStringToLong ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XmuCvtStringToOrientation ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC Boolean XmuCvtStringToShapeStyle ( Display *, XrmValue *,
    Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XmuReshapeWidget ( Widget, int, int, int ) ;
+FUNC void XmuCvtStringToWidget ( XrmValue *, Cardinal *,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC Boolean XmuNewCvtStringToWidget ( Display *, XrmValue *,
    Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;

+ENUM XtJustify := {
    XtJustifyLeft,
    XtJustifyCenter,
    XtJustifyRight
} ;

+ENUM XtOrientation := {
    XtorientHorizontal,
    XtorientVertical
} ;

+CONST int XmuShapeRectangle, XmuShapeOval, XmuShapeEllipse ;
+CONST int XmuShapeRoundedRectangle ;
