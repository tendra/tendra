# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Form.h.ts" ;

# Viewport Widget (6.7)

+TYPE ( struct ) ViewportClassRec ;
+TYPEDEF ViewportClassRec *ViewportWidgetClass ;

+EXP lvalue WidgetClass viewportWidgetClass ;

+TYPE ( struct ) ViewportRec ;
+TYPEDEF ViewportRec *ViewportWidget ;
