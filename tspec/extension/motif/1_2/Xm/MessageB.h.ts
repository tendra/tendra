# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmMessageBoxWidgetClass;

+TYPE (struct) _XmMessageBoxClassRec;
+TYPE (struct) _XmMessageBoxRec;
+TYPEDEF _XmMessageBoxClassRec * XmMessageBoxWidgetClass;
+TYPEDEF _XmMessageBoxRec * XmMessageBoxWidget;


+FUNC Widget XmCreateMessageBox( Widget parent, String name, ArgList arglist,
                                                Cardinal argcount) ;
+FUNC Widget XmCreateMessageDialog( Widget parent, String name, ArgList arglist,                                               Cardinal argcount) ;
+FUNC Widget XmCreateErrorDialog( Widget parent, String name, ArgList arglist,
                                                          Cardinal argcount) ;
+FUNC Widget XmCreateInformationDialog( Widget parent, String name, ArgList arglist, Cardinal argcount) ;
+FUNC Widget XmCreateQuestionDialog( Widget parent, String name, ArgList arglist, Cardinal argcount) ;
+FUNC Widget XmCreateWarningDialog( Widget parent, String name, ArgList arglist, Cardinal argcount) ;
+FUNC Widget XmCreateWorkingDialog( Widget parent, String name, ArgList arglist, Cardinal argcount) ;
+FUNC Widget XmCreateTemplateDialog(Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmMessageBoxGetChild( Widget widget, unsigned char child) ;

