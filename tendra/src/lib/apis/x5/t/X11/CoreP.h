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

+USE "x5/t", "X11/Intrinsic.h" ;
+USE "x5/t", "X11/IntrinsicP.h", "intrinsix" ;
+USE "x5/t", "X11/Core.h" ;

# Definition of CoreClassPart (1.4.1.1)

+FIELD ( struct ) CoreClassPart := {
    WidgetClass superclass ;
    String class_name ;
    Cardinal widget_size ;
    XtProc class_initialize ;
    XtWidgetClassProc class_part_initialize ;
    XtEnum class_inited ;
    XtInitProc initialize ;
    XtArgsProc initialize_hook ;
    XtRealizeProc realize ;
    XtActionList actions ;
    Cardinal num_actions ;
    XtResourceList resources ;
    Cardinal num_resources ;
    XrmClass xrm_class ;
    Boolean compress_motion ;
    XtEnum compress_exposure ;
    Boolean compress_enterleave ;
    Boolean visible_interest ;
    XtWidgetProc destroy ;
    XtWidgetProc resize ;
    XtExposeProc expose ;
    XtSetValuesFunc set_values ;
    XtArgsFunc set_values_hook ;
    XtAlmostProc set_values_almost ;
    XtArgsProc get_values_hook ;
    XtAcceptFocusProc accept_focus ;
    XtVersionType version ;
    XtPointer callback_private ;
    String tm_table ;
    XtGeometryHandler query_geometry ;
    XtStringProc display_accelerator ;
    XtPointer extension ;
} ;

+FIELD CoreClassRec := {
    CoreClassPart core_class ;
} ;

+EXP lvalue CoreClassRec coreClassRec ;


# Definition of CorePart Structure (1.4.1.2)

+FIELD ( struct ) CorePart {
    Widget self ;
    WidgetClass widget_class ;
    Widget parent ;
    Boolean being_destroyed ;
    XtCallbackList destroy_callbacks ;
    XtPointer constraints ;
    Position x, y ;
    Dimension width, height ;
    Dimension border_width ;
    Boolean managed ;
    Boolean sensitive ;
    Boolean ancestor_sensitive ;
    XtTranslations accelerators ;
    Pixel border_pixel ;
    Pixmap border_pixmap ;
    WidgetList popup_list ;
    Cardinal num_popups ;
    String name ;
    Screen *screen ;
    Colormap colormap ;
    Window window ;
    Cardinal depth ;
    Pixel background_pixel ;
    Pixmap background_pixmap ;
    Boolean visible ;
    Boolean mapped_when_managed ;
} ;

+FIELD CoreRec := {
    CorePart core ;
} ;


# Inheritance of Superclass Operations (1.6.10)

+EXP String XtInheritTranslations ;
+EXP XtRealizeProc XtInheritRealize ;
+EXP XtWidgetProc XtInheritResize ;
+EXP XtExposeProc XtInheritExpose ;
+EXP XtAlmostProc XtInheritSetValuesAlmost ;
+EXP XtAcceptFocusProc XtInheritAcceptFocus ;
+EXP XtGeometryHandler XtInheritQueryGeometry ;
+EXP XtStringProc XtInheritDisplayAccelerator ;
