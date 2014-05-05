# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/BulletinB.h.ts";

+EXP lvalue WidgetClass xmFormWidgetClass;

+TYPE (struct) _XmFormClassRec;
+TYPE (struct) _XmFormRec;
+TYPEDEF _XmFormClassRec * XmFormWidgetClass;
+TYPEDEF _XmFormRec * XmFormWidget;


+FUNC Widget XmCreateForm (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateFormDialog (Widget parent, String name, ArgList arglist, Cardinal argcount);
