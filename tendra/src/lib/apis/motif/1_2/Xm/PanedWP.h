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



/* SCO CID (IXI) PanedWP.h,v 1.1 1996/08/08 14:13:09 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/PanedW.h";
+USE "motif/1_2", "Xm/ManagerP.h";


+FIELD (struct)  _XmPanedWindowClassPart := { 

	XtPointer	extension;
}; 

+TYPEDEF _XmPanedWindowClassPart XmPanedWindowClassPart;

+FIELD (struct) _XmPanedWindowClassRec := {

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmPanedWindowClassPart	paned_window_class;
};

+TYPEDEF _XmPanedWindowClassRec XmPanedWindowClassRec;

+EXP lvalue XmPanedWindowClassRec xmPanedWindowClassRec;

+FIELD (struct) _XmPanedWindowConstraintPart := { 

	int			position;
	int			dheight;
	Position		dy;
	Position		olddy;
	Dimension		min;
	Dimension		max;
	Boolean			isPane;

	Boolean			allow_resize;
	Boolean			skip_adjust;

	Widget			sash;
	Widget			separator;
	short			position_index;
};

+TYPEDEF _XmPanedWindowConstraintPart XmPanedWindowConstraintPart;

+FIELD (struct) _XmPanedWindowConstraintRec := { 

	XmManagerConstraintPart		manager;
	XmPanedWindowConstraintPart	panedw;
};

+TYPEDEF _XmPanedWindowConstraintRec XmPanedWindowConstraintRec;
+TYPEDEF _XmPanedWindowConstraintRec * XmPanedWindowConstraintPtr;

+FIELD (struct) XmPanedWindowPart := { 

	Boolean				refiguremode;
	Boolean				separator_on;
	
	Dimension			margin_width;
	Dimension			margin_height;
	
	Dimension			spacing;

	Dimension			sash_width;
	Dimension			sash_height;
	Dimension			sash_shadow_thickness;

	Position			sash_indent;

	int				starty;

	short				increment_count;
	short				pane_count;
	short				num_slots;
	short				num_managed_children;

	Boolean				recursively_called;
	
	Boolean				resize_at_realize;

	XmPanedWindowConstraintPtr	top_pane;
	XmPanedWindowConstraintPtr	bottom_pane;

	GC				flipgc;

	WidgetList			managed_children;
};


+FIELD (struct) _XmPanedWindowRec := { 

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmPanedWindowPart	paned_window;
};

+TYPEDEF _XmPanedWindowRec XmPanedWindowRec;



	

