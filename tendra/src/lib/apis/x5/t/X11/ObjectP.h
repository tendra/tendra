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

+USE "x5/t", "X11/Object.h" ;
+USE "x5/t", "X11/IntrinsicP.h", "intrinsix" ;


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
