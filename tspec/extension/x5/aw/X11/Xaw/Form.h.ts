# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# Form Widget (6.3)

+TYPE ( struct ) FormClassRec ;
+TYPEDEF FormClassRec *FormWidgetClass ;

+EXP lvalue WidgetClass formWidgetClass ;

+TYPE ( struct ) FormRec ;
+TYPEDEF FormRec *FormWidget ;


+TYPE ( int ) XawEdgeType ;
+CONST XawEdgeType XawChainBottom, XawChainLeft, XawChainRight ;
+CONST XawEdgeType XawChainTop, XawRubber ;

+FUNC void XawFormDoLayout ( Widget, Boolean ) ;
