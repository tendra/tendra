# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1995, Open Software Foundation, Inc.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts" ;


+EXP lvalue WidgetClass xmArrowButtonWidgetClass;

+TYPE (struct) _XmArrowButtonClassRec;
+TYPE (struct) _XmArrowButtonRec;

+TYPEDEF _XmArrowButtonClassRec *XmArrowButtonWidgetClass;
+TYPEDEF _XmArrowButtonRec *XmArrowButtonWidget;


+FUNC Widget XmCreateArrowButton (Widget parent, String name, ArgList arglist, Cardinal argcount);

