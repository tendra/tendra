# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmScaleWidgetClass;

+TYPE (struct) _XmScaleClassRec;
+TYPE (struct) _XmScaleRec;
+TYPEDEF _XmScaleClassRec * XmScaleWidgetClass;
+TYPEDEF _XmScaleRec      * XmScaleWidget;


+FUNC void XmScaleSetValue (Widget w, int value);
+FUNC void XmScaleGetValue (Widget w, int *value);
+FUNC Widget XmCreateScale (Widget parent, String name, ArgList arglist, Cardinal argcount);

