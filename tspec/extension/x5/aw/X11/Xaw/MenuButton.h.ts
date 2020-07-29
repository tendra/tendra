# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# MenuButton Widget (4.6)

+TYPE ( struct ) MenuButtonClassRec ;
+TYPEDEF MenuButtonClassRec *MenuButtonWidgetClass ;

+EXP lvalue WidgetClass menuButtonWidgetClass ;

+TYPE ( struct ) MenuButtonRec ;
+TYPEDEF MenuButtonRec *MenuButtonWidget ;
