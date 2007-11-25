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



/* SCO CID (IXI) MainWP.h,v 1.1 1996/08/08 14:13:02 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/MainW.h";
+USE "motif/1_2", "Xm/ScrolledWP.h";
+USE "motif/1_2", "Xm/SeparatoG.h";

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


