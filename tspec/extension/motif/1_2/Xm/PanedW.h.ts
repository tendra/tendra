# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmPanedWindowWidgetClass;

+TYPE (struct) _XmPanedWindowClassRec;
+TYPE (struct) _XmPanedWindowRec;
+TYPEDEF _XmPanedWindowClassRec *XmPanedWindowWidgetClass;
+TYPEDEF _XmPanedWindowRec *XmPanedWindowWidget;


+FUNC Widget XmCreatePanedWindow (Widget parent, String name, ArgList arglist, Cardinal argCount);

