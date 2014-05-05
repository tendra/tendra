# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# List Widget (3.4)

+TYPE ( struct ) ListClassRec ;
+TYPEDEF ListClassRec *ListWidgetClass ;

+EXP lvalue WidgetClass listWidgetClass ;

+TYPE ( struct ) ListRec ;
+TYPEDEF ListRec *ListWidget ;


# List Callbacks (3.4.3)

+FIELD ( struct ) XawListReturnStruct {
    String string ;
    int list_index ;
} ;


# List functions (3.4.4-7) - all Widgets are ListWidgets

+FUNC void XawListChange ( Widget, String *, int, int, Boolean ) ;
+FUNC void XawListHighlight ( Widget, int ) ;
+FUNC void XawListUnhighlight ( Widget ) ;
+FUNC XawListReturnStruct *XawListShowCurrent ( Widget ) ;
+CONST int XAW_LIST_NONE ;
