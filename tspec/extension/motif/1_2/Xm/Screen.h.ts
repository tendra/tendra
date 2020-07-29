# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+TYPE (struct) _XmScreenRec;
+TYPE (struct) _XmScreenClassRec;
+TYPEDEF _XmScreenRec *XmScreen;
+TYPEDEF _XmScreenRec *XmScreenObject;
+TYPEDEF _XmScreenClassRec *XmScreenClass;

+EXP lvalue WidgetClass xmScreenClass;

+FUNC Widget XmGetXmScreen(Screen *screen);

