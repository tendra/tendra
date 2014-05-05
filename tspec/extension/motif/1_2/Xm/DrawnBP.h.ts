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

+USE "motif/1_2", "Xm/DrawnB.h.ts";
+USE "motif/1_2", "Xm/LabelP.h.ts";

+FIELD (struct) _XmDrawnButtonClassPart := { 

	XtPointer	extension;
};

+TYPEDEF _XmDrawnButtonClassPart XmDrawnButtonClassPart;

+FIELD (struct) _XmDrawnButtonClassRec := { 

	CoreClassPart		core_class;
	XmPrimitiveClassPart	primitive_class;
	XmLabelClassPart	label_class;
	XmDrawnButtonClassPart	drawnbutton_class;
};

+TYPEDEF _XmDrawnButtonClassRec XmDrawnButtonClassRec;


+EXP lvalue XmDrawnButtonClassRec xmDrawnButtonClassRec;

+FIELD (struct) _XmDrawnButtonPart := { 

	Boolean			pushbutton_enabled;
	unsigned char		shadow_type;
	XtCallbackList		activate_callback;
	XtCallbackList		arm_callback;
	XtCallbackList		disarm_callback;
	XtCallbackList		expose_callback;
	XtCallbackList		resize_callback;

	Boolean			armed;
	Dimension		old_width;
	Dimension		old_height;
	Dimension		old_shadow_thickness;
	Dimension		old_highlight_thickness;
	XtIntervalId		timer;
	unsigned char		multiClick;
	int			click_count;
	Time			armTimeStamp;
};

+TYPEDEF _XmDrawnButtonPart XmDrawnButtonPart;

+FIELD (struct) _XmDrawnButtonRec := { 

	CorePart		core;
	XmPrimitivePart		primitive;
	XmLabelPart		label;
	XmDrawnButtonPart	drawnbutton;
};

+TYPEDEF _XmDrawnButtonRec XmDrawnButtonRec;



