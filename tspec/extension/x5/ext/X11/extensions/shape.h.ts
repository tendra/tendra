# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# From "X11 Nonrectangular Window Shape Extension"

+USE "x5/lib", "X11/Xlib.h.ts" ;

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
