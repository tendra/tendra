# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/VendorSEP.h.ts";

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

