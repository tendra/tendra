# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmCommandWidgetClass;

+TYPE (struct) _XmCommandClassRec;
+TYPE (struct) _XmCommandRec;
+TYPEDEF _XmCommandClassRec * XmCommandWidgetClass;
+TYPEDEF _XmCommandRec * XmCommandWidget;

+FUNC Widget XmCreateCommand( Widget parent, String name, ArgList arglist,
                              Cardinal argcount) ;
+FUNC Widget XmCommandGetChild( Widget widget,unsigned char child) ;
+FUNC void XmCommandSetValue( Widget widget, XmString command) ;
+FUNC void XmCommandAppendValue( Widget widget, XmString command) ;
+FUNC void XmCommandError( Widget widget, XmString error) ;
+FUNC Widget XmCreateCommandDialog(Widget, String, ArgList, Cardinal);

