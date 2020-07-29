# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Text.h.ts" ;

# AsciiSrc Object (5.6)

+TYPE ( struct ) AsciiSrcClassRec ;
+TYPEDEF AsciiSrcClassRec *AsciiSrcObjectClass ;

+EXP lvalue WidgetClass asciiSrcObjectClass ;

+TYPE ( struct ) AsciiSrcRec ;
+TYPEDEF AsciiSrcRec *AsciiSrcObject ;


# Convenience Routines (5.6.2)

+FUNC void XawAsciiSourceFreeString ( Widget ) ;
+FUNC Boolean XawAsciiSave ( Widget ) ;
+FUNC Boolean XawAsciiSaveAsFile ( Widget, String ) ;
+FUNC Boolean XawAsciiSourceChanged ( Widget ) ;
