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



/* SCO CID (IXI) ToggleBP.h,v 1.1 1996/08/08 14:13:49 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ToggleB.h";
+USE "motif/1_2", "Xm/LabelP.h";

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




