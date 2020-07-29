# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmPushButtonGadgetClass;

+TYPE (struct) _XmPushButtonGadgetClassRec;
+TYPE (struct) _XmPushButtonGadgetRec;
+TYPE (struct) _XmPushButtonGCacheObjRec;
+TYPEDEF _XmPushButtonGadgetClassRec   *XmPushButtonGadgetClass;
+TYPEDEF _XmPushButtonGadgetRec        *XmPushButtonGadget;
+TYPEDEF _XmPushButtonGCacheObjRec     *XmPushButtonGCacheObject;


+FUNC Widget XmCreatePushButtonGadget(Widget parent, String name, ArgList arglist, Cardinal argcount);

