# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# Label Widget (3.3)

+TYPE ( struct ) LabelClassRec ;
+TYPEDEF LabelClassRec *LabelWidgetClass ;

+EXP lvalue WidgetClass labelWidgetClass ;

+TYPE ( struct ) LabelRec ;
+TYPEDEF LabelRec *LabelWidget ;


# Resources (3.3.1)

+CONST int XawTextEncoding8bit, XawTextEncodingChar2b ;
