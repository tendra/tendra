# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts" ;

+EXP lvalue WidgetClass xmScrollBarWidgetClass;

+TYPE (struct) _XmScrollBarClassRec;
+TYPE (struct) _XmScrollBarRec;
+TYPEDEF _XmScrollBarClassRec * XmScrollBarWidgetClass;
+TYPEDEF _XmScrollBarRec * XmScrollBarWidget;

+FUNC Widget XmCreateScrollBar (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC void XmScrollBarGetValues (Widget w, int *value, int *slider_size, int *increment, int *page_increment);
+FUNC void XmScrollBarSetValues (Widget w, int value, int slider_size, int increment, int page_increment,Boolean notify);


