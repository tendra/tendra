# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmSeparatorGadgetClass;

+TYPE (struct) _XmSeparatorGadgetClassRec;
+TYPE (struct) _XmSeparatorGadgetRec;
+TYPE (struct) _XmSeparatorGCacheObjRec;
+TYPEDEF _XmSeparatorGadgetClassRec * XmSeparatorGadgetClass;
+TYPEDEF _XmSeparatorGadgetRec * XmSeparatorGadget;
+TYPEDEF _XmSeparatorGCacheObjRec * XmSeparatorGCacheObject;



+FUNC Widget XmCreateSeparatorGadget (Widget parent, char *name, ArgList arglist, Cardinal argcount);

