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


/* SCO CID (IXI) SashP.h,v 1.1 1996/08/08 14:13:20 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2","Xm/PrimitiveP.h" ;

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

