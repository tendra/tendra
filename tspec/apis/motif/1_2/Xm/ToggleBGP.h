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



/* SCO CID (IXI) ToggleBGP.h,v 1.1 1996/08/08 14:13:48 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ToggleBG.h";
+USE "motif/1_2", "Xm/LabelGP.h";

+FIELD (struct) _XmToggleButtonGCacheObjClassPart := { 

	int		foo;
};

+TYPEDEF _XmToggleButtonGCacheObjClassPart XmToggleButtonGCacheObjClassPart;

+FIELD (struct) _XmToggleButtonGCacheObjClassRec := { 

	ObjectClassPart			object_class;
	XmExtClassPart			ext_class;
	XmLabelGCacheObjClassPart	label_class_cache;
	XmToggleButtonGCacheObjClassPart	toggle_class_cache;
};

+TYPEDEF _XmToggleButtonGCacheObjClassRec XmToggleButtonGCacheObjClassRec;

+EXP lvalue XmToggleButtonGCacheObjClassRec xmToggleButtonGCacheObjClassRec;

+FIELD (struct) _XmToggleButtonGCacheObjPart := { 

	unsigned char			ind_type;
	Boolean				visible;
	Dimension			spacing;
	Dimension			indicator_dim;
	Pixmap				on_pixmap;
	Pixmap				insen_pixmap;
	Boolean				ind_on;
	Boolean				fill_on_select;
	Pixel				select_color;
	GC				select_GC;
	GC				background_gc;
};

+TYPEDEF _XmToggleButtonGCacheObjPart XmToggleButtonGCacheObjPart;

+FIELD (struct) _XmToggleButtonGCacheObjRec := { 

	ObjectPart			object;
	XmExtPart			ext;
	XmLabelGCacheObjPart		label_cache;
	XmToggleButtonGCacheObjPart	toggle_cache;
};

+TYPEDEF _XmToggleButtonGCacheObjRec XmToggleButtonGCacheObjRec;

+FIELD (struct) _XmToggleButtonGadgetClassPart := { 

	XtPointer			extension;
};

+TYPEDEF _XmToggleButtonGadgetClassPart XmToggleButtonGadgetClassPart;

+FIELD (struct) _XmToggleButtonGadgetClassRec := { 

	RectObjClassPart		rect_class;
	XmGadgetClassPart		gadget_class;
	XmLabelGadgetClassPart		label_class;
	XmToggleButtonGadgetClassPart	toggle_class;
};

+TYPEDEF _XmToggleButtonGadgetClassRec XmToggleButtonGadgetClassRec;

+EXP lvalue XmToggleButtonGadgetClassRec xmToggleButtonGadgetClassRec;

+FIELD (struct) _XmToggleButtonGadgetPart := { 

	Boolean				indicator_set;
	Boolean				set;
	Boolean				visual_set;
	Boolean				Armed;
	XtCallbackList			value_changed_CB;
	XtCallbackList			arm_CB;
	XtCallbackList			disarm_CB;
	XmToggleButtonGCacheObjPart	*cache;
};

+TYPEDEF _XmToggleButtonGadgetPart XmToggleButtonGadgetPart;

+FIELD (struct) _XmToggleButtonGadgetRec := { 

	ObjectPart			object;
	RectObjPart			rectangle;
	XmGadgetPart			gadget;
	XmLabelGadgetPart		label;
	XmToggleButtonGadgetPart	toggle;
};

+TYPEDEF _XmToggleButtonGadgetRec XmToggleButtonGadgetRec;

+MACRO unsigned char TBG_IndType(Widget);
+MACRO Boolean TBG_Visible(Widget);
+MACRO Dimension TBG_Spacing(Widget);
+MACRO Dimension TBG_IndicatorDim(Widget);
+MACRO Pixmap TBG_OnPixmap(Widget);
+MACRO Pixmap TBG_InsenPixmap(Widget);
+MACRO Boolean TBG_IndOn(Widget);
+MACRO Boolean TBG_FillOnSelect(Widget);
+MACRO Pixel TBG_SelectColor(Widget);
+MACRO GC TBG_SelectGC(Widget);
+MACRO GC TBG_BackgroundGC(Widget);

+MACRO Boolean TBG_IndicatorSet(Widget);
+MACRO Boolean TBG_Set(Widget);
+MACRO Boolean TBG_VisualSet(Widget);
+MACRO XtCallbackList TBG_ValueChangedCB(Widget);
+MACRO XtCallbackList TBG_ArmCB(Widget);
+MACRO XtCallbackList TBG_DisarmCB(Widget);
+MACRO XtCallbackList TBG_Armed(Widget);

+MACRO XmToggleButtonGCacheObjPart * TBG_Cache(Widget);

+MACRO XmCacheClassPartPtr TBG_ClassCachePart(Widget);

+FUNC int _XmToggleBCacheCompare(XtPointer, XtPointer);


