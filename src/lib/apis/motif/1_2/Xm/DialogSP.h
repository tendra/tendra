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



/* SCO CID (IXI) DialogSP.h,v 1.1 1996/08/08 14:12:30 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";
+USE "motif/1_2", "Xm/DialogS.h";
+USE "x5/t", "X11/ShellP.h";


+FIELD (struct) XmDialogShellPart := { 

	XtGrabKind	grab_kind;
	Position	old_x;
	Position	old_y;
};


+FIELD (struct) _XmDialogShellRec := { 

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	WMShellPart		wm;
	VendorShellPart		vendor;
	TransientShellPart	transient;
	XmDialogShellPart	dialog;
};

+TYPEDEF _XmDialogShellRec XmDialogShellRec;

/* OBSOLETE (for compatibility only */
+TYPEDEF _XmDialogShellRec _XmDialogShellWidgetRec;


+FIELD (struct) XmDialogShellClassPart := { 

	XtPointer		extension;
};


+FIELD (struct) _XmDialogShellClassRec := { 

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ShellClassPart		shell_class;
	WMShellClassPart	wm_shell_class;
	VendorShellClassPart	vendor_shell_class;
	TransientShellClassPart	transient_shell_class;
	XmDialogShellClassPart	dialog_shell_part;
};

+TYPEDEF _XmDialogShellClassRec XmDialogShellClassRec;

+EXP lvalue XmDialogShellClassRec xmDialogShellClassRec;



