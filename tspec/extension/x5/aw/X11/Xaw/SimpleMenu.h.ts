# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/t", "X11/Shell.h.ts" ;

# SimpleMenu Widget (4.2)

+TYPE ( struct ) SimpleMenuClassRec ;
+TYPEDEF SimpleMenuClassRec *SimpleMenuWidgetClass ;

+EXP lvalue WidgetClass simpleMenuWidgetClass ;

+TYPE ( struct ) SimpleMenuRec ;
+TYPEDEF SimpleMenuRec *SimpleMenuWidget ;


# Convenience Routines (4.2.4)

+FUNC void XawSimpleMenuAddGlobalActions ( XtAppContext ) ;
+FUNC Widget XawSimpleMenuGetActiveEntry ( Widget ) ;
+FUNC void XawSimpleMenuClearActiveEntry ( Widget ) ;
