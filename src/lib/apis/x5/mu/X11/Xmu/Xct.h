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
