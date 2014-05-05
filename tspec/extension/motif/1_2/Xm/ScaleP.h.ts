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

+USE "motif/1_2", "Xm/Scale.h.ts";
+USE "motif/1_2", "Xm/ManagerP.h.ts";

+FIELD (struct) _XmScaleConstraintPart := {

	char		unused;
};

+TYPEDEF _XmScaleConstraintPart XmScaleConstraintPart;
+TYPEDEF _XmScaleConstraintPart * XmScaleConstraint;

+FIELD (struct) XmScaleClassPart := { 

	XtPointer	extension;
};


+FIELD (struct) _XmScaleClassRec := { 

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmScaleClassPart	scale_class;
};

+TYPEDEF _XmScaleClassRec XmScaleClassRec;

+EXP lvalue XmScaleClassRec xmScaleClassRec;

+FIELD (struct) XmScalePart := { 

	int			value;
	int			maximum;
	int			minimum;
	unsigned char		orientation;
	unsigned char		processing_direction;
	XmString		title;
	XmFontList		font_list;
	XFontStruct		* font_struct;
	Boolean			show_value;
	short			decimal_points;
	Dimension		scale_width;
	Dimension		scale_height;
	Dimension		highlight_thickness;
	Boolean			highlight_on_enter;
	XtCallbackList		drag_callback;
	XtCallbackList		value_changed_callback;

	int			last_value;
	int			slider_size;
	GC			foreground_GC;
	int			show_value_x;
	int			show_value_y;
	int			show_value_width;
	int			show_value_height;
	int			scale_multiple;
};


+FIELD (struct) _XmScaleRec := { 

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmScalePart		scale;
};

+TYPEDEF _XmScaleRec XmScaleRec;


	

