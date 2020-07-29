# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

# Sme Object (4.5)

+TYPE ( struct ) SmeClassRec ;
+TYPEDEF SmeClassRec *SmeObjectClass ;

+EXP lvalue WidgetClass smeObjectClass ;

+TYPE ( struct ) SmeRec ;
+TYPEDEF SmeRec *SmeObject ;
