# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __X11_P_HEADERS
#error Unauthorized access to X11 P headers
#endif
%%

+USE "x5/t", "X11/RectObj.h.ts" ;
+USE "x5/t", "X11/IntrinsicP.h.ts", "intrinsix" ;
+USE "x5/t", "X11/ObjectP.h.ts" (!?) ;


# RectObjClassPart Definition (12.3.1)

+FIELD ( struct ) RectObjClassPart := {
    WidgetClass superclass ;
    String class_name ;
    Cardinal widget_size ;
    XtProc class_initialize ;
    XtWidgetClassProc class_part_initialize ;
    XtEnum class_inited ;
    XtInitProc initialize ;
    XtArgsProc initialize_hook ;
    XtProc rect1 ;
    XtPointer rect2 ;
    Cardinal rect3 ;
    XtResourceList resources ;
    Cardinal num_resources ;
    XrmClass xrm_class ;
    Boolean rect4 ;
    XtEnum rect5 ;
    Boolean rect6 ;
    Boolean rect7 ;
    XtWidgetProc destroy ;
    XtWidgetProc resize ;
    XtExposeProc expose ;
    XtSetValuesFunc set_values ;
    XtArgsFunc set_values_hook ;
    XtAlmostProc set_values_almost ;
    XtArgsProc get_values_hook ;
    XtProc rect9 ;
    XtVersionType version ;
    XtPointer callback_private ;
    String rect10 ;
    XtGeometryHandler query_geometry ;
    XtProc rect11 ;
    XtPointer extension ;
} ;

+FIELD RectObjClassRec := {
    RectObjClassPart rect_class ;
} ;

+EXP lvalue RectObjClassRec rectObjClassRec ;


# RectObjPart Definition (12.3.2)

+FIELD ( struct ) RectObjPart {
    Position x, y ;
    Dimension width, height ;
    Dimension border_width ;
    Boolean managed ;
    Boolean sensitive ;
    Boolean ancestor_sensitive ;
} ;

+FIELD RectObjRec := {
    ObjectPart object ;
    RectObjPart rectangle ;
} ;
