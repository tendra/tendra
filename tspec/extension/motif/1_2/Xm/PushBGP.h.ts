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

+USE "motif/1_2", "Xm/PushBG.h.ts";
+USE "motif/1_2", "Xm/LabelGP.h.ts";

+FIELD (struct) _XmPushButtonGCacheObjClassPart := { 

	int	foo;
};

+TYPEDEF _XmPushButtonGCacheObjClassPart XmPushButtonGCacheObjClassPart;


+FIELD (struct) _XmPushButtonGCacheObjClassRec := { 

	ObjectClassPart				object_class;
	XmExtClassPart				ext_class;
	XmLabelGCacheObjClassPart		label_class_cache;
	XmPushButtonGCacheObjClassPart		pushbutton_class_cache;
};

+TYPEDEF _XmPushButtonGCacheObjClassRec XmPushButtonGCacheObjClassRec;


+EXP lvalue XmPushButtonGCacheObjClassRec xmPushButtonGCacheObjClassRec;


+FIELD (struct) _XmPushButtonGCacheObjPart := { 

	Boolean			fill_on_arm;
	Pixel			arm_color;
	Pixmap			arm_pixmap;
	Pixmap			unarm_pixmap;
	unsigned char		multiClick;
	Dimension		default_button_shadow_thickness;

	GC			fill_gc;
	GC			background_gc;
	XtIntervalId		timer;
};

+TYPEDEF _XmPushButtonGCacheObjPart XmPushButtonGCacheObjPart;

+FIELD (struct) _XmPushButtonGCacheObjRec := { 

	ObjectPart			object;
	XmExtPart			ext;
	XmLabelGCacheObjPart		label_cache;
	XmPushButtonGCacheObjPart	pushbutton_cache;
};

+TYPEDEF _XmPushButtonGCacheObjRec XmPushButtonGCacheObjRec;

+FIELD (struct) _XmPushButtonGadgetClassPart := {

	XtPointer			extension;
};

+TYPEDEF _XmPushButtonGadgetClassPart XmPushButtonGadgetClassPart;

+FIELD (struct) _XmPushButtonGadgetClassRec := { 

	RectObjClassPart		rect_class;
	XmGadgetClassPart		gadget_class;
	XmLabelGadgetClassPart		label_class;
	XmPushButtonGadgetClassPart	pushbutton_class;
};

+TYPEDEF _XmPushButtonGadgetClassRec XmPushButtonGadgetClassRec;


+EXP lvalue XmPushButtonGadgetClassRec xmPushButtonGadgetClassRec;

		
+FIELD (struct) _XmPushButtonGadgetPart := { 

	XtCallbackList			activate_callback;
	XtCallbackList			arm_callback;
	XtCallbackList			disarm_callback;

	Dimension			show_as_default;
	Boolean				armed;
	int				click_count;

	Boolean				compatible;

	XmPushButtonGCacheObjPart	*cache;
};

+TYPEDEF _XmPushButtonGadgetPart XmPushButtonGadgetPart;

+FIELD (struct) _XmPushButtonGadgetRec := { 

	ObjectPart			object;
	RectObjPart			rectangle;
	XmGadgetPart			gadget;
	XmLabelGadgetPart		label;
	XmPushButtonGadgetPart		pushbutton;
};

+TYPEDEF _XmPushButtonGadgetRec XmPushButtonGadgetRec;

+MACRO Boolean PBG_FillOnArm(Widget);
+MACRO Pixel PBG_ArmColor(Widget);
+MACRO GC PBG_FillGc(Widget);
+MACRO GC PBG_BackgroundGc(Widget);
+MACRO XtIntervalId PBG_Timer(Widget);
+MACRO Pixmap PBG_ArmPixmap(Widget);
+MACRO Pixmap PBG_UnarmPixmap(Widget);
+MACRO unsigned char PBG_MultiClick(Widget);
+MACRO Dimension PBG_DefaultButtonShadowThickness(Widget);
+MACRO XtCallbackList PBG_ActivateCallback(Widget);
+MACRO XtCallbackList PBG_ArmCallback(Widget);
+MACRO XtCallbackList PBG_DisarmCallback(Widget);
+MACRO Boolean PBG_Armed(Widget);
+MACRO int PBG_ClickCount(Widget);
+MACRO Boolean PBG_Compatible(Widget);
+MACRO Dimension PBG_ShowAsDefault(Widget);

+MACRO XmPushButtonGCacheObjPart * PBG_Cache(Widget);
+MACRO XmCacheClassPartPtr PBG_ClassCachePart(Widget);

+FUNC void _XmClearBGCompatibility(Widget);

