/*
    COPYRIGHT NOTICE

    This program is the proprietary property of IXI Ltd, a subsidiary
    of the Santa Cruz Operation (SCO). Use, reproduction, production
    of amended versions and/or transfer of this program is permitted
    PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996

*/



/* SCO CID (IXI) VendorSP.h,v 1.1 1996/08/08 14:13:54 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";
+USE "motif/1_2", "Xm/VendorS.h";
+USE "x5/t", "X11/ShellP.h";
+USE "motif/1_2", "Xm/DesktopP.h";
+USE "motif/1_2", "Xm/ExtObjectP.h";



+FUNC Cardinal _XmFilterResources(XtResource *, Cardinal, WidgetClass, XtResource **);
+FUNC void _XmAddGrab(Widget, Boolean, Boolean);
+FUNC void _XmRemoveGrab(Widget);
+FUNC XtGeometryResult _XmRootGeometryManager(Widget, XtWidgetGeometry *, XtWidgetGeometry *);
+FUNC void _XmVendorExtRealize(Widget, XtPointer, XtPointer );

+FUNC Display * _XmGetDefaultDisplay(void);


