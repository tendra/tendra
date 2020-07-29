# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Command.h.ts" ;

# Toggle Widget (3.10)

+TYPE ( struct ) ToggleClassRec ;
+TYPEDEF ToggleClassRec *ToggleWidgetClass ;

+EXP lvalue WidgetClass toggleWidgetClass ;

+TYPE ( struct ) ToggleRec ;
+TYPEDEF ToggleRec *ToggleWidget ;


# Convenience Routines (3.10.5)

+FUNC void XawToggleChangeRadioGroup ( Widget, Widget ) ;
+FUNC XtPointer XawToggleGetCurrent ( Widget ) ;
+FUNC void XawToggleSetCurrent ( Widget, XtPointer ) ;
+FUNC void XawToggleUnsetCurrent ( Widget ) ;
