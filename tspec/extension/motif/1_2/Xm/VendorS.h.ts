# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2", "Xm/Xm.h.ts";

+TYPE (struct) _XmVendorShellRec;
+TYPE (struct) _XmVendorShellClassRec;
+TYPEDEF _XmVendorShellRec *XmVendorShellWidget;
+TYPEDEF _XmVendorShellClassRec *XmVendorShellWidgetClass;

+FUNC Boolean XmIsMotifWMRunning(Widget);

