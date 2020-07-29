# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2","Xm/PrimitiveP.h.ts" ;

+FIELD (struct) XmSashClassPart := { 

	XtPointer	extension;
};


+FIELD (struct) _XmSashClassRec := { 

	CoreClassPart		core_class;
	XmPrimitiveClassPart	primitive_class;
	XmSashClassPart		sash_class;
};

+TYPEDEF _XmSashClassRec XmSashClassRec;
+TYPEDEF _XmSashClassRec *XmSashWidgetClass;

+EXP lvalue XmSashClassRec xmSashClassRec;

+FIELD (struct) XmSashPart := { 

	XtCallbackList		sash_action;
	Boolean			has_focus;
};


+FIELD (struct) _XmSashRec := {

	CorePart		core;
	XmPrimitivePart		primitive;
	XmSashPart		sash;
};

+TYPEDEF _XmSashRec XmSashRec;
+TYPEDEF _XmSashRec *XmSashWidget;

+FIELD (struct) SashCallDataRec := { 

	XEvent		*event;
	String		*params;
	Cardinal	num_params;
};

+TYPEDEF SashCallDataRec *SashCallData;

+EXP lvalue WidgetClass xmSashWidgetClass;

+IFNDEF XmIsSash
+DEFINE XmIsSash(w) %% XtIsSubclass(w, xmSashWidgetClass) %%;
+ENDIF

