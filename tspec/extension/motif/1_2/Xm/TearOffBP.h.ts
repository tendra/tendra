# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/PushBP.h.ts";

+FIELD (struct) _XmTearOffButtonClassPart := { 

	String		translations;
};

+TYPEDEF _XmTearOffButtonClassPart XmTearOffButtonClassPart;

+FIELD (struct) _XmTearOffButtonClassRec := { 

	CoreClassPart			core_class;
	XmPrimitiveClassPart		primitive_class;
	XmLabelClassPart		label_class;
	XmPushButtonClassPart		pushbutton_class;
	XmTearOffButtonClassPart	tearoffbutton_class;
};

+TYPEDEF _XmTearOffButtonClassRec XmTearOffButtonClassRec;

+TYPEDEF _XmTearOffButtonClassRec *XmTearOffButtonWidgetClass;

+EXP lvalue XmTearOffButtonClassRec xmTearOffButtonClassRec;

+FIELD (struct) XmTearOffButtonPart := { 

	Dimension	margin;
	unsigned char	orientation;
   	unsigned char	separator_type;
	GC		separator_GC;
};


+FIELD (struct) _XmTearOffButtonRec := { 

	CorePart		core;
	XmPrimitivePart		primitive;
	XmLabelPart		label;
	XmPushButtonPart	pushbutton;
	XmTearOffButtonPart	tear_off_button;
};

+TYPEDEF _XmTearOffButtonRec XmTearOffButtonRec;
+TYPEDEF _XmTearOffButtonRec  *XmTearOffButtonWidget;

+EXP lvalue WidgetClass xmTearOffButtonWidgetClass;



