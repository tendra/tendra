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
%%
#ifndef __X11_P_HEADERS
#error Unauthorized access to X11 P headers
#endif
%%

+USE "x5/t", "X11/RectObj.h" ;
+USE "x5/t", "X11/IntrinsicP.h", "intrinsix" ;
+USE "x5/t", "X11/ObjectP.h" (!?) ;


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
