# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# Text Widget (5.9)

+TYPE ( struct ) TextClassRec ;
+TYPEDEF TextClassRec *TextWidgetClass ;

+EXP lvalue WidgetClass textWidgetClass ;

+TYPE ( struct ) TextRec ;
+TYPEDEF TextRec *TextWidget ;


# Text Routines

+TYPE ( int ) XawTextSelectType ;

+CONST XawTextSelectType XawselectNull, XawselectAll, XawselectChar ;
+CONST XawTextSelectType XawselectLine, XawselectParagraph, XawselectWord ;


+TYPEDEF long XawTextPosition ;

+FIELD ( struct ) XawTextBlock := {
    int firstPos ;
    int length ;
    char *ptr ;
    unsigned long format ;
} ;

+TYPEDEF XawTextBlock *XawTextBlockPtr ;

+FUNC void XawTextSetSelection ( Widget, XawTextPosition, XawTextPosition ) ;
+FUNC void XawTextUnsetSelection ( Widget ) ;
+FUNC void XawTextGetSelectionPos ( Widget, XawTextPosition *,
    XawTextPosition * ) ;

+CONST int XawEditDone, XawPositionError, XawEditError ;
+FUNC int XawTextReplace ( Widget, XawTextPosition, XawTextPosition,
    XawTextBlock * ) ;

+TYPE ( int ) XawTextScanDirection ;
+CONST XawTextScanDirection XawsdLeft, XawsdRight ;
+CONST XawTextPosition XawTextSearchError ;
+FUNC XawTextPosition XawTextSearch ( Widget, XawTextScanDirection,
    XawTextBlock * ) ;

+FUNC void XawTextInvalidate ( Widget, XawTextPosition, XawTextPosition ) ;
+FUNC void XawTextEnableRedisplay ( Widget ) ;
+FUNC void XawTextDisableRedisplay ( Widget ) ;
+FUNC void XawTextDisplay ( Widget ) ;

+FUNC XawTextPosition XawTextTopPosition ( Widget ) ;
+FUNC void XawTextSetSelectionArray ( Widget, XawTextSelectType * ) ;
+FUNC void XawTextSetInsertionPoint ( Widget, XawTextPosition ) ;
+FUNC XawTextPosition XawTextGetInsertionPoint ( Widget ) ;
+FUNC void XawTextSetSource ( Widget, Widget, XawTextPosition ) ;
+FUNC Widget XawTextGetSource ( Widget ) ;
+FUNC void XawTextDisplayCaret ( Widget, Boolean ) ;

+CONST int XawtextRead, XawtextEdit, XawtextAppend ;
+CONST int XawtextResizeNever,  XawtextResizeWidth, XawtextResizeHeight ;
+CONST int XawtextResizeBoth ;
+CONST int XawtextScrollAlways, XawtextScrollWhenNeeded, XawtextScrollNever ;
+CONST int XawAsciiString, XawAsciiFile ;
+CONST int XawtextWrapNever, XawtextWrapLine, XawtextWrapWord ;
