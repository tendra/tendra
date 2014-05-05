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

+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/t", "X11/Composite.h.ts" ;
+USE "x5/t", "X11/IntrinsicP.h.ts", "intrinsix" ;
+USE "x5/t", "X11/CoreP.h.ts" ;


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
