# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/mu", "X11/StringDefs.h.ts" ;

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
