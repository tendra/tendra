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

+USE "motif/1_2", "Xm/SeparatoG.h.ts";
+USE "motif/1_2", "Xm/GadgetP.h.ts";
+USE "motif/1_2", "Xm/ExtObjectP.h.ts";

+FIELD (struct) _XmSeparatorGCacheObjClassPart := {

	int	foo;
};

+TYPEDEF _XmSeparatorGCacheObjClassPart XmSeparatorGCacheObjClassPart;

+FIELD (struct) _XmSeparatorGCacheObjClassRec := { 

	ObjectClassPart			object_class;
	XmExtClassPart			ext_class;
	XmSeparatorGCacheObjClassPart	separator_class_cache;
};

+TYPEDEF _XmSeparatorGCacheObjClassRec XmSeparatorGCacheObjClassRec;

+EXP lvalue XmSeparatorGCacheObjClassRec xmSeparatorGCacheObjClassRec;

+FIELD (struct) _XmSeparatorGCacheObjPart := { 

	Dimension		margin;
	unsigned char		orientation;
	unsigned char		separator_type;
	GC			separator_GC;
};

+TYPEDEF _XmSeparatorGCacheObjPart XmSeparatorGCacheObjPart;

+FIELD (struct) _XmSeparatorGCacheObjRec := { 

	ObjectPart                	object;
	XmExtPart			ext;
	XmSeparatorGCacheObjPart	separator_cache;
};

+TYPEDEF _XmSeparatorGCacheObjRec XmSeparatorGCacheObjRec;

+FIELD (struct) _XmSeparatorGadgetClassPart := {

	XtPointer	extension;
};

+TYPEDEF _XmSeparatorGadgetClassPart XmSeparatorGadgetClassPart;

+FIELD (struct) _XmSeparatorGadgetClassRec := { 

	RectObjClassPart		rect_class;
	XmGadgetClassPart		gadget_class;
	XmSeparatorGadgetClassPart	separator_class;
};

+TYPEDEF _XmSeparatorGadgetClassRec XmSeparatorGadgetClassRec;

+EXP lvalue XmSeparatorGadgetClassRec xmSeparatorGadgetClassRec;

+FIELD (struct) _XmSeparatorGadgetPart := { 

	XmSeparatorGCacheObjPart	*cache;
};

+TYPEDEF _XmSeparatorGadgetPart XmSeparatorGadgetPart;

+FIELD (struct) _XmSeparatorGadgetRec := { 

	ObjectPart			object;
	RectObjPart			rectangle;
	XmGadgetPart			gadget;
	XmSeparatorGadgetPart		separator;
};

+TYPEDEF _XmSeparatorGadgetRec XmSeparatorGadgetRec;

+MACRO Dimension SEPG_Margin(Widget);
+MACRO unsigned char SEPG_Orientation(Widget);
+MACRO unsigned char SEPG_SeparatorType(Widget);
+MACRO GC SEPG_SeparatorGC(Widget);

+MACRO XmSeparatorGCacheObjPart * SEPG_Cache(Widget);
+MACRO XmCacheClassPartPtr SEPG_ClassCachePart(Widget);


+FUNC int _XmSeparatorCacheCompare(XtPointer, XtPointer);


