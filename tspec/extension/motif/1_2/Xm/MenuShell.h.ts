# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmMenuShellWidgetClass;

+TYPE (struct) _XmMenuShellClassRec;
+TYPE (struct) _XmMenuShellWidgetRec;
+TYPEDEF _XmMenuShellClassRec * XmMenuShellWidgetClass;
+TYPEDEF _XmMenuShellWidgetRec * XmMenuShellWidget;

+FUNC Widget XmCreateMenuShell (Widget parent, String name, ArgList arglist, Cardinal argcount);

