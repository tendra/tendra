# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1995, Open Software Foundation, Inc.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2", "Xm/Xm.h.ts";
+USE "x5/t", "X11/Shell.h.ts";
+USE "motif/1_2", "Xm/DragC.h.ts";
+USE "motif/1_2", "Xm/DropSMgr.h.ts";


+CONST int XmDRAG_NONE;
+CONST int XmDRAG_DROP_ONLY;
+CONST int XmDRAG_PREFER_PREREGISTER;
+CONST int XmDRAG_PREREGISTER;
+CONST int XmDRAG_PREFER_DYNAMIC;
+CONST int XmDRAG_DYNAMIC;
+CONST int XmDRAG_PREFER_RECEIVER;

+TYPE (struct) _XmDisplayRec;
+TYPE (struct) _XmDisplayClassRec;
+TYPEDEF _XmDisplayRec *XmDisplay;
+TYPEDEF _XmDisplayRec *XmDisplayObject;
+TYPEDEF _XmDisplayClassRec *XmDisplayClass;

+EXP lvalue WidgetClass xmDisplayClass;

+MACRO Widget XmGetDisplay(Widget);

+FUNC Widget XmGetDragContext(Widget, Time);

+FUNC Widget XmGetXmDisplay(Display *);


