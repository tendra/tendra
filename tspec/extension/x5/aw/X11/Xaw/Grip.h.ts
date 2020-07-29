# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# Grip Widget (3.2)

+TYPE ( struct ) GripClassRec ;
+TYPEDEF GripClassRec *GripWidgetClass ;

+EXP lvalue WidgetClass gripWidgetClass ;

+TYPE ( struct ) GripRec ;
+TYPEDEF GripRec *GripWidget ;


# Grip Actions (3.2.2)

+FIELD ( struct ) XawGripCallDataRec := {
    XEvent *event ;
    String *params ;
    Cardinal num_params ;
} ;

+TYPEDEF XawGripCallDataRec *XawGripCallData ;
+TYPEDEF XawGripCallDataRec GripCallDataRec ;
+TYPEDEF XawGripCallDataRec *GripCallData ;
