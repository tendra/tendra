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



/* SCO CID (IXI) DrawingAP.h,v 1.1 1996/08/08 14:12:42 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ManagerP.h";
+USE "motif/1_2", "Xm/DrawingA.h";

+CONST int XmRESIZE_SWINDOW;

+FIELD (struct) _XmDrawingAreaConstraintPart := { 

	char	unused;
};

+TYPEDEF _XmDrawingAreaConstraintPart XmDrawingAreaConstraintPart;
+TYPEDEF _XmDrawingAreaConstraintPart * XmDrawingAreaConstraint;


+FIELD (struct) XmDrawingAreaClassPart := { 

	XtPointer		extension;
};


+FIELD (struct) _XmDrawingAreaClassRec := { 

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmDrawingAreaClassPart	drawing_area_class;
};

+TYPEDEF _XmDrawingAreaClassRec XmDrawingAreaClassRec;

+EXP lvalue XmDrawingAreaClassRec xmDrawingAreaClassRec;

+FIELD (struct) XmDrawingAreaPart := { 

	Dimension		margin_width;
	Dimension		margin_height;

	XtCallbackList		resize_callback;
	XtCallbackList		expose_callback;
	XtCallbackList		input_callback;

	unsigned char		resize_policy;
};


+FIELD (struct) _XmDrawingAreaRec := { 

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmDrawingAreaPart	drawing_area;
};

+TYPEDEF _XmDrawingAreaRec XmDrawingAreaRec;

+FUNC void _XmDrawingAreaInput(Widget, XEvent *, String *, Cardinal *);


