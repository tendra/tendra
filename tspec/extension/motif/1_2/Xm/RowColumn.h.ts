# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmRowColumnWidgetClass;

+TYPE (struct) _XmRowColumnClassRec;
+TYPE (struct) _XmRowColumnWidgetRec;
+TYPEDEF _XmRowColumnClassRec * XmRowColumnWidgetClass;
+TYPEDEF _XmRowColumnWidgetRec * XmRowColumnWidget;


+FUNC Widget XmCreateRadioBox (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateRowColumn (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateWorkArea (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreatePopupMenu (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreatePulldownMenu (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateOptionMenu (Widget parent, String name, ArgList arglist,Cardinal argcount);
+FUNC Widget XmCreateMenuBar (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC void XmMenuPosition (Widget parent, XButtonPressedEvent *event);
+FUNC Widget XmOptionLabelGadget (Widget m);
+FUNC Widget XmOptionButtonGadget (Widget m);
+FUNC Widget XmGetPostedFromWidget (Widget menu);
+FUNC Widget XmGetTearOffControl(Widget menu);
+FUNC void XmAddToPostFromList(Widget, Widget);
+FUNC void XmRemoveFromPostFromList(Widget, Widget);

