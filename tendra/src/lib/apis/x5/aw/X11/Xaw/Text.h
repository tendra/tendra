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
+USE "x5/aw", "X11/Xaw/Simple.h" ;

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
