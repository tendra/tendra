# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Form.h.ts" ;

# Dialog Widget (6.2)

+TYPE ( struct ) DialogClassRec ;
+TYPEDEF DialogClassRec *DialogWidgetClass ;

+EXP lvalue WidgetClass dialogWidgetClass ;

+TYPE ( struct ) DialogRec ;
+TYPEDEF DialogRec *DialogWidget ;

+FUNC String XawDialogGetValueString ( Widget ) ;
+FUNC void XawDialogAddButton ( Widget, String, XtCallbackProc, XtPointer ) ;
