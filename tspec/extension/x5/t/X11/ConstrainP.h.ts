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
+USE "x5/t", "X11/Constraint.h.ts" ;
+USE "x5/t", "X11/IntrinsicP.h.ts", "intrinsix" ;
+USE "x5/t", "X11/CoreP.h.ts" ;
+USE "x5/t", "X11/CompositeP.h.ts" ;


# ConstraintClassPart Structure (1.4.3.1)

+FIELD ( struct ) ConstraintClassPart := {
    XtResourceList resources ;
    Cardinal num_resources ;
    Cardinal constraint_size ;
    XtInitProc initialize ;
    XtWidgetProc destroy ;
    XtSetValuesFunc set_values ;
    XtPointer extension ;
} ;

+FIELD ( struct ) ConstraintClassExtensionRec := {
    XtPointer next_extension ;
    XrmQuark record_type ;
    long version ;
    Cardinal record_size ;
    XtArgsProc get_values_hook ;
} ;

+TYPEDEF ConstraintClassExtensionRec *ConstraintClassExtension ;
+CONST long XtConstraintExtensionVersion ;

+FIELD ConstraintClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ConstraintClassPart constraint_class ;
} ;

+EXP lvalue ConstraintClassRec constraintClassRec ;


# ConstraintPart Structure (1.4.2.2)

+TYPE ( struct ) ConstraintPart ;
+IF 0
+FIELD ConstraintPart {
    int empty ;
} ;
+ENDIF

+FIELD ConstraintRec := {
    CorePart core ;
    CompositePart composite ;
    ConstraintPart constraint ;
} ;
