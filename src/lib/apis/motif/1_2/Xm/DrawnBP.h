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



/* SCO CID (IXI) DrawnBP.h,v 1.1 1996/08/08 14:12:43 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/DrawnB.h";
+USE "motif/1_2", "Xm/LabelP.h";

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



