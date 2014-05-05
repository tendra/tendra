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

+USE "motif/1_2", "Xm/CascadeBG.h.ts";
+USE "motif/1_2", "Xm/LabelGP.h.ts";

+FIELD (struct) _XmArrowPixmap := { 

	Dimension	height;
	Dimension	width;

	unsigned int	depth;
	Pixel		top_shadow_color;
	Pixel		bottom_shadow_color;
	Pixel		foreground_color;

	Display		*display;
	Screen		*screen;
	Pixmap		pixmap;
};

+TYPEDEF _XmArrowPixmap XmArrowPixmap;

+FIELD (struct) XmCascadeButtonGCacheObjClassPart := { 

	int		foo;
};

+FIELD (struct) XmCascadeButtonGCacheObjClassRec := { 

	ObjectClassPart				object_class;
	XmExtClassPart				ext_class;
	XmLabelGCacheObjClassPart		label_class_cache;
	XmCascadeButtonGCacheObjClassPart	cascade_button_class_cache;
};


+EXP lvalue XmCascadeButtonGCacheObjClassRec xmCascadeButtonGCacheObjClassRec;

+FIELD (struct) XmCascadeButtonGCacheObjPart := { 

	Pixmap		cascade_pixmap;
	int		map_delay;
	Pixmap		armed_pixmap;
};


+FIELD (struct) XmCascadeButtonGCacheObjRec := { 

	ObjectPart			object;
	XmExtPart			ext;
	XmLabelGCacheObjPart		label_cache;
	XmCascadeButtonGCacheObjPart	cascade_button_cache;
};


+FIELD (struct) XmCascadeButtonGadgetPart := { 

	Widget				submenu;
	XtCallbackList			activate_callback;
	XtCallbackList			cascade_callback;

	Boolean				armed;
	XRectangle			cascade_rect;
	XtIntervalId			timer;
	XmCascadeButtonGCacheObjPart	*cache;
};


+FIELD (struct) XmCascadeButtonGadgetRec := { 

	ObjectPart			object;
	RectObjPart			rectangle;
	XmGadgetPart			gadget;
	XmLabelGadgetPart		label;
	XmCascadeButtonGadgetPart	cascade_button;
};


+FIELD (struct) XmCascadeButtonGadgetClassPart := {

	XtPointer			extension;
};

+FIELD (struct) XmCascadeButtonGadgetClassRec := { 

	RectObjClassPart		rect_class;
	XmGadgetClassPart		gadget_class;
	XmLabelGadgetClassPart		label_class;
	XmCascadeButtonGadgetClassPart	cascade_button_class;
};


+EXP lvalue XmCascadeButtonGadgetClassRec xmCascadeButtonGadgetClassRec;

+MACRO Widget CBG_Submenu(Widget);
+MACRO XtCallbackList CBG_ActivateCall(Widget);
+MACRO XtCallbackList CBG_CascadeCall(Widget);
+MACRO Boolean CBG_Armed(Widget);
+MACRO XRectangle CBG_CascadeRect(Widget);
+MACRO XtIntervalId CBG_Timer(Widget);
+MACRO Position CBG_Cascade_x(Widget);
+MACRO Position CBG_Cascade_y(Widget);
+MACRO Dimension CBG_Cascade_width(Widget);
+MACRO Dimension CBG_Cascade_height(Widget);
+MACRO Boolean CBG_HasCascade(Widget);

+CONST int XmCBG_ARMED_BIT;
+CONST int XmCBG_TRAVERSE_BIT;

+MACRO int CBG_IsArmed(Widget);
+MACRO int CBG_Traversing(Widget);

+DEFINE CBG_SetBit(byte,bit,v) %% byte = (byte & (~bit)) | (v ? bit : 0) %%;

+MACRO void CBG_SetArmed(Widget, Boolean);
+MACRO void CBG_SetTraverse(Widget, Boolean);

+MACRO Pixmap CBG_CascadePixmap(Widget);
+MACRO int CBG_MapDelay(Widget);
+MACRO Pixmap CBG_ArmedPixmap(Widget);
+MACRO XmCascadeButtonGCacheObjPart *CBG_Cache(Widget);
+MACRO XmCacheClassPartPtr CBG_ClassCachePart(Widget);

+FUNC int _XmArrowPixmapCacheCompare( XtPointer, XtPointer );
+FUNC void _XmArrowPixmapCacheDelete( XtPointer );
+FUNC void _XmCreateArrowPixmaps( Widget );

