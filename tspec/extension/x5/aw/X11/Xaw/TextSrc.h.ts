# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Text.h.ts" ;

# TextSrc Object (5.10)

+TYPE ( struct ) TextSrcClassRec ;
+TYPEDEF TextSrcClassRec *TextSrcObjectClass ;

+EXP lvalue WidgetClass textSrcObjectClass ;

+TYPE ( struct ) TextSrcRec ;
+TYPEDEF TextSrcRec *TextSrcObject ;

