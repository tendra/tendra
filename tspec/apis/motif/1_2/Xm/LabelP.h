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



/* SCO CID (IXI) LabelP.h,v 1.1 1996/08/08 14:12:58 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/Label.h";
+USE "motif/1_2", "Xm/PrimitiveP.h";

+FIELD (struct) _XmLabelClassPart := {

        XtWidgetProc	setOverrideCallback;
	XmMenuProc	menuProcs;
        String  	translations;
        XtPointer	extension;
};

+TYPEDEF _XmLabelClassPart XmLabelClassPart;

+FIELD (struct) _XmLabelClassRec := {
    CoreClassPart        core_class;
    XmPrimitiveClassPart primitive_class;
    XmLabelClassPart	 label_class;
};

+TYPEDEF _XmLabelClassRec XmLabelClassRec;

+EXP lvalue XmLabelClassRec xmLabelClassRec;

+CONST int LABEL_ACC_PAD;


/*  The Label instance record  */

+FIELD (struct) _XmLabelPart := {
	_XmString	_label;
        _XmString	_acc_text;
	 KeySym		mnemonic;
        XmStringCharSet mnemonicCharset;
        char 		*accelerator;
        unsigned char	label_type;
        unsigned char	alignment;
        unsigned char	string_direction;
        XmFontList	font;
	
	Dimension	margin_height;
        Dimension	margin_width;

	Dimension 	margin_left;
        Dimension	margin_right;
        Dimension	margin_top;
        Dimension	margin_bottom;

        Boolean 	recompute_size;

        Pixmap		pixmap; 
        Pixmap		pixmap_insen; 

        GC		normal_GC;
        GC		insensitive_GC;
        XRectangle	TextRect;
        XRectangle	acc_TextRect;
	Boolean		skipCallback;
	unsigned char   menu_type;
};

+TYPEDEF _XmLabelPart XmLabelPart;

+FIELD (struct) _XmLabelRec := {
   CorePart         core;
   XmPrimitivePart  primitive;
   XmLabelPart	    label;
};

+TYPEDEF _XmLabelRec XmLabelRec;


+MACRO Dimension Lab_MarginWidth(Widget);
+MACRO Dimension Lab_MarginHeight(Widget);
+MACRO Dimension Lab_MarginTop(Widget);
+MACRO Dimension Lab_MarginBottom(Widget);
+MACRO Dimension Lab_MarginRight(Widget);
+MACRO Dimension Lab_MarginLeft(Widget);
+MACRO short Lab_TextRect_x(Widget);
+MACRO short Lab_TextRect_y(Widget);
+MACRO unsigned short Lab_TextRect_width(Widget);
+MACRO unsigned short Lab_TextRect_height(Widget);

+MACRO Boolean Lab_IsText(Widget);
+MACRO Boolean Lab_IsPixmap(Widget);

+MACRO XmFontList Lab_Font(Widget);

+MACRO KeySym Lab_Mnemonic(Widget);
+MACRO char * Lab_Accelerator(Widget);
+MACRO _XmString Lab_AcceleratorText(Widget);
+MACRO unsigned char Lab_MenuType(Widget);
+MACRO Dimension Lab_Shadow(Widget);
+MACRO Dimension Lab_Highlight(Widget);
+MACRO Dimension Lab_Baseline(Widget);

+FUNC void _XmCalcLabelDimensions(Widget wid);


