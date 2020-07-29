# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ToggleB.h.ts";
+USE "motif/1_2", "Xm/LabelP.h.ts";

+FIELD (struct) _XmToggleButtonClassPart := {

	XtPointer		extension;
};

+TYPEDEF _XmToggleButtonClassPart XmToggleButtonClassPart;

+FIELD (struct) _XmToggleButtonClassRec := { 

	CoreClassPart		core_class;
	XmPrimitiveClassPart	primitive_class;
	XmLabelClassPart	label_class;
	XmToggleButtonClassPart	toggle_class;
};

+TYPEDEF _XmToggleButtonClassRec XmToggleButtonClassRec;

+EXP lvalue XmToggleButtonClassRec xmToggleButtonClassRec;

+FIELD (struct) _XmToggleButtonPart := { 

	unsigned char		ind_type;
	Boolean			visible;
	Dimension		spacing;
	Dimension		indicator_dim;
	Boolean			indicator_set;
	Pixmap			on_pixmap;
	Pixmap			insen_pixmap;
	Boolean			set;
	Boolean			visual_set;
	Boolean			ind_on;
	Boolean			fill_on_select;
	Pixel			select_color;
	GC			select_GC;
	GC			background_gc;
	XtCallbackList		value_changed_CB;
	XtCallbackList		arm_CB;
	XtCallbackList		disarm_CB;
	Boolean			Armed;
};

+TYPEDEF _XmToggleButtonPart XmToggleButtonPart;

+FIELD (struct) _XmToggleButtonRec := { 

	CorePart		core;
	XmPrimitivePart		primitive;
	XmLabelPart		label;
	XmToggleButtonPart	toggle;
};

+TYPEDEF _XmToggleButtonRec XmToggleButtonRec;




