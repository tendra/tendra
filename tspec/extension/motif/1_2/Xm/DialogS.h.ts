# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts"; 
+USE "x5/t","X11/Shell.h.ts";


+EXP lvalue WidgetClass xmDialogShellWidgetClass;

+TYPE (struct) _XmDialogShellClassRec;
+TYPE (struct) _XmDialogShellRec;
+TYPEDEF _XmDialogShellClassRec * XmDialogShellWidgetClass;
+TYPEDEF _XmDialogShellRec * XmDialogShellWidget;

+FUNC Widget XmCreateDialogShell(Widget, String, ArgList, Cardinal);

