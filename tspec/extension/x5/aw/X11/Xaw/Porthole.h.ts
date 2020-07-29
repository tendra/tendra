# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# Porthole Widget (6.5)

+TYPE ( struct ) PortholeClassRec ;
+TYPEDEF PortholeClassRec *PortholeWidgetClass ;

+EXP lvalue WidgetClass portholeWidgetClass ;

+TYPE ( struct ) PortholeRec ;
+TYPEDEF PortholeRec *PortholeWidget ;
