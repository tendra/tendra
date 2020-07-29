# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif Private Headers
#endif
%%

+USE "motif/1_2", "Xm/GadgetP.h.ts";
+USE "motif/1_2", "Xm/ArrowBG.h.ts";

+FIELD (struct) _XmArrowButtonGadgetClassPart := {
	XtPointer extension;
};

+TYPEDEF _XmArrowButtonGadgetClassPart XmArrowButtonGadgetClassPart;

+FIELD (struct) _XmArrowButtonGadgetClassRec := {
	RectObjClassPart		rect_class;
	XmGadgetClassPart		gadget_class;
	XmArrowButtonGadgetClassPart	arrow_button_class;
};

+TYPEDEF _XmArrowButtonGadgetClassRec XmArrowButtonGadgetClassRec;

+EXP lvalue XmArrowButtonGadgetClassRec xmArrowButtonGadgetClassRec;

+FIELD (struct) _XmArrowButtonGadgetPart := {

	XtCallbackList		activate_callback;
	XtCallbackList		arm_callback;
	XtCallbackList		disarm_callback;
	unsigned char		direction;

	Boolean			selected;

	short			top_count;
	short			cent_count;
	short			bot_count;
	XRectangle		*top;
	XRectangle		*cent;
	XRectangle		*bot;

	Position		old_x;
	Position		old_y;

	GC			arrow_GC;
	XtIntervalId		timer;

	unsigned char 		multiClick;

	int			click_count;
	GC			insensitive_GC;
};

+TYPEDEF _XmArrowButtonGadgetPart XmArrowButtonGadgetPart;

+FIELD (struct) _XmArrowButtonGadgetRec := { 

	ObjectPart		object;
	RectObjPart		rectangle;
	XmGadgetPart		gadget;
	XmArrowButtonGadgetPart	arrowbutton;
};

+TYPEDEF _XmArrowButtonGadgetRec XmArrowButtonGadgetRec;

	

