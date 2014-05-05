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

+USE "motif/1_2", "Xm/ManagerP.h.ts";
+USE "motif/1_2", "Xm/DrawingA.h.ts";

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


