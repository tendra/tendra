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



/* SCO CID (IXI) DialogSEP.h,v 1.1 1996/08/08 14:12:30 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/VendorSEP.h";

+EXP lvalue WidgetClass xmDialogShellExtObjectClass;

+FIELD (struct) _XmDialogShellExtClassPart := {

	XtPointer	extension;
};

+TYPEDEF _XmDialogShellExtClassPart XmDialogShellExtClassPart;
+TYPEDEF _XmDialogShellExtClassPart *XmDialogShellExtClassPartPtr;


+FIELD (struct) _XmDialogShellExtClassRec := {

	ObjectClassPart			object_class;
	XmExtClassPart			ext_class;
	XmDesktopClassPart		desktop_class;
	XmShellExtClassPart		shell_class;
	XmVendorShellExtClassPart	vendor_class;
	XmDialogShellExtClassPart	dialog_class;
};

+TYPEDEF _XmDialogShellExtClassRec XmDialogShellExtClassRec;
+TYPEDEF _XmDialogShellExtClassRec *XmDialogShellExtObjectClass;

+FIELD (struct) _XmDialogShellExtPart := { 

	int		empty;
};

+TYPEDEF _XmDialogShellExtPart XmDialogShellExtPart;

+EXP lvalue XmDialogShellExtClassRec xmDialogShellExtClassRec;

+FIELD (struct) _XmDialogShellExtRec := { 

	ObjectPart			object;
	XmExtPart			ext;
	XmDesktopPart			desktop;
	XmShellExtPart			shell;
	XmVendorShellExtPart		vendor;
	XmDialogShellExtPart		dialog;
};

+TYPEDEF _XmDialogShellExtRec XmDialogShellExtRec;
+TYPEDEF _XmDialogShellExtRec *XmDialogShellExtObject;

