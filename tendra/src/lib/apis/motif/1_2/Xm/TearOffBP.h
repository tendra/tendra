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



/* SCO CID (IXI) $ID$ */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/PushBP.h";

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



