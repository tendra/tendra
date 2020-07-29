# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# Tree Widget (6.6)

+TYPE ( struct ) TreeClassRec ;
+TYPEDEF TreeClassRec *TreeWidgetClass ;

+EXP lvalue WidgetClass treeWidgetClass ;

+TYPE ( struct ) TreeRec ;
+TYPEDEF TreeRec *TreeWidget ;


+FUNC void XawTreeForceLayout ( Widget ) ;
