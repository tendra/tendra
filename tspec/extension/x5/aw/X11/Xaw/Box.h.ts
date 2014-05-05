# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# Box Widget (6.1)

+TYPE ( struct ) BoxClassRec ;
+TYPEDEF BoxClassRec *BoxWidgetClass ;

+EXP lvalue WidgetClass boxWidgetClass ;

+TYPE ( struct ) BoxRec ;
+TYPEDEF BoxRec *BoxWidget ;
