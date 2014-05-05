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

+USE "motif/1_2", "Xm/LabelG.h.ts";
+USE "motif/1_2", "Xm/GadgetP.h.ts";
+USE "motif/1_2", "Xm/ExtObjectP.h.ts";

+FIELD ( struct ) _XmLabelGCacheObjClassPart := {

    	int 		foo;
};

+TYPEDEF _XmLabelGCacheObjClassPart XmLabelGCacheObjClassPart;

+FIELD ( struct )  _XmLabelGCacheObjClassRec := {

    ObjectClassPart			object_class;
    XmExtClassPart                 	ext_class;
    XmLabelGCacheObjClassPart	 	label_class_cache;
};

+TYPEDEF _XmLabelGCacheObjClassRec XmLabelGCacheObjClassRec;

+EXP lvalue XmLabelGCacheObjClassRec xmLabelGCacheObjClassRec;

+FIELD ( struct )  _XmLabelGCacheObjPart := {

        unsigned char	label_type;
        unsigned char	alignment;
        unsigned char	string_direction;
	
	Dimension	margin_height;
	Dimension	margin_width;

	Dimension	margin_left;
	Dimension	margin_right;
	Dimension	margin_top;
	Dimension	margin_bottom;

	Boolean 	recompute_size;

	Boolean		skipCallback;
	unsigned char   menu_type;
};

+TYPEDEF _XmLabelGCacheObjPart XmLabelGCacheObjPart;


+FIELD ( struct )  _XmLabelGCacheObjRec := {

    ObjectPart               object;
    XmExtPart	             ext;
    XmLabelGCacheObjPart     label_cache;
};

+TYPEDEF _XmLabelGCacheObjRec XmLabelGCacheObjRec;

+FIELD ( struct )  _XmLabelGadgetClassPart := {

        XtWidgetProc		setOverrideCallback;
	XmMenuProc		menuProcs;
        XtPointer		extension; 
};

+TYPEDEF _XmLabelGadgetClassPart XmLabelGadgetClassPart;

+FIELD ( struct )  _XmLabelGadgetClassRec := {

    RectObjClassPart       rect_class;
    XmGadgetClassPart      gadget_class;
    XmLabelGadgetClassPart label_class;
};

+TYPEDEF _XmLabelGadgetClassRec XmLabelGadgetClassRec;


+EXP lvalue XmLabelGadgetClassRec xmLabelGadgetClassRec;

+FIELD ( struct )  _XmLabelGadgetPart := {
	_XmString		_label;
        _XmString       	_acc_text;
        KeySym          	mnemonic;
	XmStringCharSet 	mnemonicCharset;
        char 			*accelerator;
        XmFontList		font;

        Pixmap			pixmap; 
        Pixmap			pixmap_insen; 

        GC			normal_GC;
	GC			insensitive_GC;
        XRectangle		TextRect;
        XRectangle		acc_TextRect;
	XmLabelGCacheObjPart 	*cache;
};

+TYPEDEF _XmLabelGadgetPart XmLabelGadgetPart;

+FIELD ( struct )  _XmLabelGadgetRec := {
   	ObjectPart        	object;
   	RectObjPart       	rectangle;
   	XmGadgetPart      	gadget;
   	XmLabelGadgetPart 	label;
};

+TYPEDEF _XmLabelGadgetRec XmLabelGadgetRec;

+CONST int LABELG_ACC_PAD;

+MACRO unsigned char LabG_LabelType(Widget);
+MACRO unsigned char LabG_Alignment(Widget);
+MACRO unsigned char LabG_StringDirection(Widget);
+MACRO Dimension LabG_MarginHeight(Widget);
+MACRO Dimension LabG_MarginWidth(Widget);
+MACRO Dimension LabG_MarginLeft(Widget);
+MACRO Dimension LabG_MarginRight(Widget);
+MACRO Dimension LabG_MarginTop(Widget);
+MACRO Dimension LabG_MarginBottom(Widget);
+MACRO Boolean LabG_RecomputeSize(Widget);
+MACRO Boolean LabG_SkipCallback(Widget);
+MACRO unsigned char LabG_MenuType(Widget);

+MACRO _XmString LabG__label(Widget);
+MACRO _XmString LabG__acceleratorText(Widget);
+MACRO XmFontList LabG_Font(Widget);
+MACRO KeySym LabG_Mnemonic(Widget);
+MACRO XmStringCharSet LabG_MnemonicCharset(Widget);
+MACRO char * LabG_Accelerator(Widget);
+MACRO Pixmap LabG_Pixmap(Widget);
+MACRO Pixmap LabG_PixmapInsensitive(Widget);
+MACRO GC LabG_NormalGC(Widget);
+MACRO GC LabG_InsensitiveGC(Widget);
+MACRO XRectangle LabG_TextRect(Widget);
+MACRO XRectangle LabG_AccTextRect(Widget);


+MACRO Position LabG_TextRect_x(Widget);
+MACRO Position LabG_TextRect_y(Widget);
+MACRO Dimension LabG_TextRect_width(Widget);
+MACRO Dimension LabG_TextRect_height(Widget);
+MACRO Boolean LabG_IsText(Widget);
+MACRO Boolean LabG_IsPixmap(Widget);
+MACRO XmLabelGCacheObjPart * LabG_Cache(Widget);
+MACRO Dimension LabG_Shadow(XmLabelGadgetRec *);
+MACRO Dimension LabG_Highlight(XmGadget);
+MACRO Dimension LabG_Baseline(Widget);
+MACRO XmCacheClassPartPtr LabG_ClassCachePart(Widget);

+FUNC int _XmLabelCacheCompare(XtPointer, XtPointer);
+FUNC void _XmCalcLabelGDimensions(Widget);
+FUNC void _XmReCacheLabG(Widget);
+FUNC void _XmAssignLabG_MarginHeight(XmLabelGadget, Dimension);
+FUNC void _XmAssignLabG_MarginWidth(XmLabelGadget, Dimension);
+FUNC void _XmAssignLabG_MarginLeft(XmLabelGadget, Dimension);
+FUNC void _XmAssignLabG_MarginRight(XmLabelGadget, Dimension);
+FUNC void _XmAssignLabG_MarginTop(XmLabelGadget, Dimension);
+FUNC void _XmAssignLabG_MarginBottom(XmLabelGadget, Dimension);
+FUNC void _XmProcessDrag(Widget, XEvent *, String *, Cardinal *);

 
