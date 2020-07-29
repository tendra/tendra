# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/MainW.h.ts";
+USE "motif/1_2", "Xm/ScrolledWP.h.ts";
+USE "motif/1_2", "Xm/SeparatoG.h.ts";

+FIELD (struct) _XmMainWindowConstraintPart := {

	char		unused;
};

+TYPEDEF _XmMainWindowConstraintPart XmMainWindowConstraintPart;
+TYPEDEF _XmMainWindowConstraintPart * XmMainWindowConstraint;

+FIELD (struct) XmMainWindowClassPart := { 

	XtPointer		extension;
};


+FIELD (struct) _XmMainWindowClassRec := { 

	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ConstraintClassPart		constraint_class;
	XmManagerClassPart		manager_class;
	XmScrolledWindowClassPart	swindow_class;
	XmMainWindowClassPart		mwindow_class;
};

+TYPEDEF _XmMainWindowClassRec XmMainWindowClassRec;

+EXP lvalue XmMainWindowClassRec xmMainWindowClassRec;

+FIELD (struct) XmMainWindowPart := { 

	Dimension			AreaWidth;
	Dimension			AreaHeight;
	Dimension			margin_width;
	Dimension			margin_height;
	Widget				CommandWindow;
	Widget				MenuBar;
	Widget				Message;
	unsigned char			CommandLoc;
	XmSeparatorGadget		Sep1;
	XmSeparatorGadget		Sep2;
	XmSeparatorGadget		Sep3;
	Boolean				ManagingSep;
	Boolean				ShowSep;
};


+FIELD (struct) _XmMainWindowRec := {

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmScrolledWindowPart	swindow;
	XmMainWindowPart	mwindow;
};

+TYPEDEF _XmMainWindowRec XmMainWindowRec;


