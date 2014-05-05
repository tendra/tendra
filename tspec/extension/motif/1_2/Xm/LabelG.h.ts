# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmLabelGadgetClass;

+TYPE (struct) _XmLabelGadgetClassRec;
+TYPE (struct) _XmLabelGadgetRec;
+TYPE (struct) _XmLabelGCacheObjRec;
+TYPEDEF _XmLabelGadgetClassRec * XmLabelGadgetClass;
+TYPEDEF _XmLabelGadgetRec      * XmLabelGadget;
+TYPEDEF _XmLabelGCacheObjRec   * XmLabelGCacheObject;


+FUNC Widget XmCreateLabelGadget (Widget parent, String name, ArgList arglist, Cardinal argCount);

