# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

+TYPEDEF unsigned char *XctString ;
+TYPE ( int ) XctFlags ;

+CONST XctFlags XctSingleSetSegments ;
+CONST XctFlags XctProvideExtensions ;
+CONST XctFlags XctAcceptC0Extensions ;
+CONST XctFlags XctAcceptC1Extensions ;
+CONST XctFlags XctHideDirection ;
+CONST XctFlags XctFreeString ;
+CONST XctFlags XctShiftMultiGRToGL ;

+ENUM XctResult := {
    XctSegment,
    XctC0Segment,
    XctGLSegment,
    XctC1Segment,
    XctGRSegment,
    XctExtendedSegment,
    XctExtension,
    XctHorizontal,
    XctEndOfText,
    XctError
} ;

+ENUM XctHDirection := {
    XctUnspecified,
    XctLeftToRight,
    XctRightToLeft
} ;

# RCA : follow implementation

/* The Spec implies that XctData is a struct, not a ptr struct */

+FIELD struct _XctRec {
    XctString item ;
    int item_length ;
    int char_size ;
    char *encoding ;
    XctHDirection horizontal ;
    int horz_depth ;
    char *GL ;
    char *GL_encoding ;
    int GL_set_size ;
    int GL_char_size ;
    char *GR ;
    char *GR_encoding ;
    int GR_set_size ;
    int GR_char_size ;
    char *GLGR_encoding ;
} ;

+TYPEDEF struct _XctRec *XctData ;

+FUNC XctData XctCreate ( XctString, int, XctFlags ) ;
+FUNC void XctReset ( XctData ) ;
+FUNC XctResult XctNextItem ( XctData ) ;
+FUNC void XctFree ( XctData ) ;
