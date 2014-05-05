# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# Scrollbar Widget (3.7)

+TYPE ( struct ) ScrollbarClassRec ;
+TYPEDEF ScrollbarClassRec *ScrollbarWidgetClass ;

+EXP lvalue WidgetClass scrollbarWidgetClass ;

+TYPE ( struct ) ScrollbarRec ;
+TYPEDEF ScrollbarRec *ScrollbarWidget ;


# Convenience Routine (3.7.4)

+FUNC void XawScrollbarSetThumb ( Widget, float, float ) ;
