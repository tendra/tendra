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


/* SCO CID (IXI) ArrowBGP.h,v 1.1 1996/08/08 14:12:11 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif Private Headers
#endif
%%

+USE "motif/1_2", "Xm/GadgetP.h";
+USE "motif/1_2", "Xm/ArrowBG.h";

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

	

