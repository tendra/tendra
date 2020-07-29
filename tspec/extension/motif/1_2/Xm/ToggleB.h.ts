# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmToggleButtonWidgetClass;

+TYPE (struct) _XmToggleButtonClassRec;
+TYPE (struct) _XmToggleButtonRec;
+TYPEDEF _XmToggleButtonClassRec *XmToggleButtonWidgetClass;
+TYPEDEF _XmToggleButtonRec *XmToggleButtonWidget;

+FUNC Boolean XmToggleButtonGetState (Widget w);
+FUNC void XmToggleButtonSetState (Widget w,Boolean newstate,Boolean notify);
+FUNC Widget XmCreateToggleButton (Widget parent, String name, ArgList arglist, Cardinal argCount);

