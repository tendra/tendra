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
+USE "motif/1_2", "Xm/DialogS.h.ts";
+USE "x5/t", "X11/ShellP.h.ts";


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



