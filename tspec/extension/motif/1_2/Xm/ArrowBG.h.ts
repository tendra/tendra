# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1995, Open Software Foundation, Inc.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts" ;

+EXP lvalue WidgetClass xmArrowButtonGadgetClass;

#+TYPEDEF struct _XmArrowButtonGadgetClassRec * XmArrowButtonGadgetClass;
#+TYPEDEF struct _XmArrowButtonGadgetRec * XmArrowButtonGadget;

+FUNC Widget XmCreateArrowButtonGadget (Widget parent, String name, ArgList arglist, Cardinal argcount);
