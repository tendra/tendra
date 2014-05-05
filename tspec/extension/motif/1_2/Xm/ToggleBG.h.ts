# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmToggleButtonGadgetClass;

+TYPE (struct) _XmToggleButtonGadgetClassRec;
+TYPE (struct) _XmToggleButtonGadgetRec;
+TYPE (struct) _XmToggleButtonGCacheObjRec;
+TYPEDEF _XmToggleButtonGadgetClassRec *XmToggleButtonGadgetClass;
+TYPEDEF _XmToggleButtonGadgetRec *XmToggleButtonGadget;
+TYPEDEF _XmToggleButtonGCacheObjRec *XmToggleButtonGCacheObject;


+FUNC Boolean XmToggleButtonGadgetGetState (Widget w);
+FUNC void XmToggleButtonGadgetSetState (Widget w, Boolean newstate,Boolean notify);
+FUNC Widget XmCreateToggleButtonGadget (Widget parent, String name, ArgList arglist, Cardinal argCount);

