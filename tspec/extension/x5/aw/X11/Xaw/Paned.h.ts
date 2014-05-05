# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# Paned Widget (6.4)

+TYPE ( struct ) PanedClassRec ;
+TYPEDEF PanedClassRec *PanedWidgetClass ;

+EXP lvalue WidgetClass panedWidgetClass ;

+TYPE ( struct ) PanedRec ;
+TYPEDEF PanedRec *PanedWidget ;


+FUNC void XawPanedAllowResize ( Widget, Boolean ) ;
+FUNC void XawPanedSetMinMax ( Widget, int, int ) ;
+FUNC void XawPanedGetMinMax ( Widget, int *, int * ) ;
+FUNC void XawPanedSetRefigureMode ( Widget, Boolean ) ;
+FUNC int XawPanedGetNumSub ( Widget ) ;
