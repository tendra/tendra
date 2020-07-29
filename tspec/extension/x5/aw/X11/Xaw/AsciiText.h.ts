# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Text.h.ts" ;

# AsciiText Widget (5.5)

+TYPE ( struct ) AsciiTextClassRec ;
+TYPEDEF AsciiTextClassRec *AsciiTextWidgetClass ;

+EXP lvalue WidgetClass asciiTextWidgetClass ;

+TYPE ( struct ) AsciiTextRec ;
+TYPEDEF AsciiTextRec *AsciiTextWidget ;
