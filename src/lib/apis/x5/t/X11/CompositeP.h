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
+USE "x5/t", "X11/Composite.h" ;
+USE "x5/t", "X11/IntrinsicP.h", "intrinsix" ;
+USE "x5/t", "X11/CoreP.h" ;


# CompositeClassPart Structure (1.4.2.1)

+FIELD ( struct ) CompositeClassPart := {
    XtGeometryHandler geometry_manager ;
    XtWidgetProc change_managed ;
    XtWidgetProc insert_child ;
    XtWidgetProc delete_child ;
    XtPointer extension ;
} ;

+FIELD ( struct ) CompositeClassExtensionRec := {
    XtPointer next_extension ;
    XrmQuark record_type ;
    long version ;
    Cardinal record_size ;
    Boolean accepts_objects ;
} ;

+TYPEDEF CompositeClassExtensionRec *CompositeClassExtension ;
+CONST long XtCompositeExtensionVersion ;

+FIELD CompositeClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
} ;

+EXP lvalue CompositeClassRec compositeClassRec ;


# CompositePart Structure (1.4.2.2)

+FIELD ( struct ) CompositePart {
    WidgetList children ;
    Cardinal num_children ;
    Cardinal num_slots ;
    XtOrderProc insert_position ;
} ;

+FIELD CompositeRec := {
    CorePart core ;
    CompositePart composite ;
} ;


# Inheritance of Superclass Operations (1.6.10)

+EXP XtGeometryHandler XtInheritGeometryManager ;
+EXP XtWidgetProc XtInheritChangeManaged ;
+EXP XtWidgetProc XtInheritInsertChild ;
+EXP XtWidgetProc XtInheritDeleteChild ;
