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




/* SCO CID (IXI) DropSMgr.h,v 1.1 1996/08/08 14:12:44 wendland Exp */

+USE "motif/1_2", "Xm/Xm.h";
+USE "motif/1_2", "Xm/DragC.h";

+CONST int XmCR_DROP_SITE_LEAVE_MESSAGE;
+CONST int XmCR_DROP_SITE_ENTER_MESSAGE;
+CONST int XmCR_DROP_SITE_MOTION_MESSAGE;
+CONST int XmCR_DROP_MESSAGE;

+CONST int XmNO_DROP_SITE;
+CONST int XmINVALID_DROP_SITE;
+CONST int XmVALID_DROP_SITE;

/* begin OSF CR 5754 */
+CONST int XmDROP_SITE_INVALID;
+CONST int XmDROP_SITE_VALID;
/* end CR */

+CONST int XmDRAG_UNDER_NONE;
+CONST int XmDRAG_UNDER_PIXMAP;
+CONST int XmDRAG_UNDER_SHADOW_IN;
+CONST int XmDRAG_UNDER_SHADOW_OUT;
+CONST int XmDRAG_UNDER_HIGHLIGHT;

+CONST int XmDROP_SITE_SIMPLE;
+CONST int XmDROP_SITE_COMPOSITE;
+CONST int XmDROP_SITE_SIMPLE_CLIP_ONLY;
+CONST int XmDROP_SITE_COMPOSITE_CLIP_ONLY;

+CONST int XmABOVE;
+CONST int XmBELOW;

+CONST int XmDROP_SITE_ACTIVE;
+CONST int XmDROP_SITE_INACTIVE;

+FIELD (struct) _XmDragProcCallbackStruct := { 

	int			reason;
	XEvent			*event;
	Time			timeStamp;
	Widget			dragContext;
	Position		x;
	Position		y;
	unsigned char		dropSiteStatus;
	unsigned char		operation;
	unsigned char		operations;
	Boolean			animate;
};

+TYPEDEF _XmDragProcCallbackStruct XmDragProcCallbackStruct;
+TYPEDEF _XmDragProcCallbackStruct *XmDragProcCallback;

+FIELD (struct) _XmDropProcCallbackStruct := { 

	int			reason;
	XEvent			*event;
	Time			timeStamp;
	Widget			dragContext;
	Position		x;
	Position		y;
	unsigned char		dropSiteStatus;
	unsigned char		operation;
	unsigned char		operations;
	unsigned char		dropAction;
};

+TYPEDEF _XmDropProcCallbackStruct XmDropProcCallbackStruct;
+TYPEDEF _XmDropProcCallbackStruct *XmDropProcCallback;

+FIELD (struct) _XmDropSiteVisualsRec := { 

	Pixel			background;
	Pixel			foreground;
	Pixel			topShadowColor;
	Pixmap			topShadowPixmap;
	Pixel			bottomShadowColor;
	Pixmap			bottomShadowPixmap;
	Dimension		shadowThickness;
	Pixel			highlightColor;
	Pixmap			highlightPixmap;
	Dimension		highlightThickness;
	Dimension		borderWidth;
};

+TYPEDEF _XmDropSiteVisualsRec XmDropSiteVisualsRec;
+TYPEDEF _XmDropSiteVisualsRec *XmDropSiteVisuals;

+EXP lvalue WidgetClass xmDropSiteManagerObjectClass;

+TYPE (struct) _XmDropSiteManagerClassRec;
+TYPE (struct) _XmDropSiteManagerRec;
+TYPEDEF _XmDropSiteManagerClassRec *XmDropSiteManagerObjectClass;
+TYPEDEF _XmDropSiteManagerRec *XmDropSiteManagerObject;

+FUNC void XmDropSiteRegister(Widget, ArgList, Cardinal);
+FUNC void XmDropSiteUnregister(Widget);
+FUNC void XmDropSiteStartUpdate(Widget);
+FUNC void XmDropSiteUpdate(Widget, ArgList, Cardinal);
+FUNC void XmDropSiteEndUpdate(Widget);
+FUNC void XmDropSiteRetrieve(Widget, ArgList, Cardinal);
+FUNC int  XmDropSiteQueryStackingOrder(Widget, Widget *, Widget **, Cardinal *);
+FUNC void XmDropSiteConfigureStackingOrder(Widget, Widget, Cardinal);
+FUNC XmDropSiteVisuals XmDropSiteGetActiveVisuals(Widget);


