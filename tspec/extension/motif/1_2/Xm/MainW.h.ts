# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmMainWindowWidgetClass;

+FUNC Widget XmMainWindowSep1 (Widget widget);
+FUNC Widget XmMainWindowSep2 (Widget widget);
+FUNC Widget XmMainWindowSep3 (Widget widget);
+FUNC void XmMainWindowSetAreas (Widget widget, Widget menu, Widget command, Widget hscroll, Widget vscroll, Widget work_region);
+FUNC Widget XmCreateMainWindow (Widget parent, String name, ArgList arglist, Cardinal argcount);


