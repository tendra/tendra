# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Label.h.ts" ;

# Command Widget (3.1)

+TYPE ( struct ) CommandClassRec ;
+TYPEDEF CommandClassRec *CommandWidgetClass ;

+EXP lvalue WidgetClass commandWidgetClass ;

+TYPE ( struct ) CommandRec ;
+TYPEDEF CommandRec *CommandWidget ;
