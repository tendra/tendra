# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# SmeLine Object (4.4)

+TYPE ( struct ) SmeLineClassRec ;
+TYPEDEF SmeLineClassRec *SmeLineObjectClass ;

+EXP lvalue WidgetClass smeLineObjectClass ;

+TYPE ( struct ) SmeLineRec ;
+TYPEDEF SmeLineRec *SmeLineObject ;
