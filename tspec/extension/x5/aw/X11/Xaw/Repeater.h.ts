# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Command.h.ts" ;

# Repeater Widget (3.6)

+TYPE ( struct ) RepeaterClassRec ;
+TYPEDEF RepeaterClassRec *RepeaterWidgetClass ;

+EXP lvalue WidgetClass repeaterWidgetClass ;

+TYPE ( struct ) RepeaterRec ;
+TYPEDEF RepeaterRec *RepeaterWidget ;
