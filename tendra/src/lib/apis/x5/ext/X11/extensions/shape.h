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
# From "X11 Nonrectangular Window Shape Extension"

+USE "x5/lib", "X11/Xlib.h" ;

+CONST int X_ShapeQueryVersion ;
+CONST int X_ShapeRectangles ;
+CONST int X_ShapeMask ;
+CONST int X_ShapeCombine ;
+CONST int X_ShapeOffset ;
+CONST int X_ShapeQueryExtents ;
+CONST int X_ShapeSelectInput ;
+CONST int X_ShapeInputSelected ;
+CONST int X_ShapeGetRectangles ;

+CONST int ShapeNotify ;

+CONST int ShapeBounding, ShapeClip ;
+CONST int ShapeSet, ShapeUnion, ShapeIntersect, ShapeSubtract, ShapeInvert ;

+FUNC Bool XShapeQueryExtension ( Display *, int *, int * ) ;
+FUNC Status XShapeQueryVersion ( Display *, int *, int * ) ;
+FUNC void XShapeCombineRegion ( Display *, Window, int, int, int,
    Region, int ) ;
+FUNC void XShapeCombineRectangles ( Display *, Window, int, int, int,
    XRectangle *, int, int, int ) ;
+FUNC void XShapeCombineMask ( Display *, Window, int, int, int,
    Pixmap, int ) ;
+FUNC void XShapeCombineShape ( Display *, Window, int, int, int,
    Window, int, int ) ;
+FUNC void XShapeOffsetShape ( Display *, Window, int, int, int ) ;
+FUNC Status XShapeQueryExtents ( Display *, Window, Bool *,  int *,
    int *, unsigned int *, unsigned int *, Bool *, int *, int *,
    unsigned int *, unsigned int * ) ;
+FUNC void XShapeSelectInput ( Display *, Window, unsigned long ) ;
+FUNC unsigned long XShapeInputSelected ( Display *, Window ) ;
+FUNC XRectangle *XShapeGetRectangles ( Display *, Window, int,
    int *, int * ) ;

+CONST unsigned long ShapeNotifyMask ;

+FIELD ( struct ) XShapeEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    int kind ;
    int x, y ;
    unsigned int width, height ;
    Time time ;
    Bool shaped ;
} ;
