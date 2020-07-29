# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h.ts";
+USE "motif/1_2", "Xm/VendorS.h.ts";
+USE "x5/t", "X11/ShellP.h.ts";
+USE "motif/1_2", "Xm/DesktopP.h.ts";
+USE "motif/1_2", "Xm/ExtObjectP.h.ts";



+FUNC Cardinal _XmFilterResources(XtResource *, Cardinal, WidgetClass, XtResource **);
+FUNC void _XmAddGrab(Widget, Boolean, Boolean);
+FUNC void _XmRemoveGrab(Widget);
+FUNC XtGeometryResult _XmRootGeometryManager(Widget, XtWidgetGeometry *, XtWidgetGeometry *);
+FUNC void _XmVendorExtRealize(Widget, XtPointer, XtPointer );

+FUNC Display * _XmGetDefaultDisplay(void);


