# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# SmeBSB Object (4.3)

+TYPE ( struct ) SmeBSBClassRec ;
+TYPEDEF SmeBSBClassRec *SmeBSBObjectClass ;

+EXP lvalue WidgetClass smeBSBObjectClass ;

+TYPE ( struct ) SmeBSBRec ;
+TYPEDEF SmeBSBRec *SmeBSBObject ;
