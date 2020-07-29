# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# Panner Widget (3.5)

+TYPE ( struct ) PannerClassRec ;
+TYPEDEF PannerClassRec *PannerWidgetClass ;

+EXP lvalue WidgetClass pannerWidgetClass ;

+TYPE ( struct ) PannerRec ;
+TYPEDEF PannerRec *PannerWidget ;
