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

+USE "x5/t", "X11/Object.h.ts" ;
+USE "x5/t", "X11/IntrinsicP.h.ts", "intrinsix" ;


# ObjectClassPart Definition (12.2.1)

+FIELD ( struct ) ObjectClassPart := {
    WidgetClass superclass ;
    String class_name ;
    Cardinal widget_size ;
    XtProc class_initialize ;
    XtWidgetClassProc class_part_initialize ;
    XtEnum class_inited ;
    XtInitProc initialize ;
    XtArgsProc initialize_hook ;
    XtProc obj1 ;
    XtPointer obj2 ;
    Cardinal obj3 ;
    XtResourceList resources ;
    Cardinal num_resources ;
    XrmClass xrm_class ;
    Boolean obj4 ;
    XtEnum obj5 ;
    Boolean obj6 ;
    Boolean obj7 ;
    XtWidgetProc destroy ;
    XtProc obj8 ;
    XtProc obj9 ;
    XtSetValuesFunc set_values ;
    XtArgsFunc set_values_hook ;
    XtProc obj10 ;
    XtArgsProc get_values_hook ;
    XtProc obj11 ;
    XtVersionType version ;
    XtPointer callback_private ;
    String obj12 ;
    XtProc obj13 ;
    XtProc obj14 ;
    XtPointer extension ;
} ;

+FIELD (struct) ObjectClassRec := {
    ObjectClassPart object_class ;
} ;

+EXP lvalue ObjectClassRec objectClassRec ;


# ObjectPart Definition (12.2.2)

+FIELD ( struct ) ObjectPart {
    Widget self ;
    WidgetClass widget_class ;
    Widget parent ;
    Boolean being_destroyed ;
    XtCallbackList destroy_callbacks ;
    XtPointer constraints ;
} ;

+FIELD ObjectRec := {
    ObjectPart object ;
} ;
