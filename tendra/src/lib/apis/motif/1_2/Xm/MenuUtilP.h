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



/* SCO CID (IXI) MenuUtilP.h,v 1.1 1996/08/08 14:13:05 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";
+USE "motif/1_2", "Xm/RowColumnP.h";

+TYPE struct _XmTranslRec;
+FIELD struct _XmTranslRec := { 

	XtTranslations		translations;
	struct _XmTranslRec	* next;
};

+FUNC Widget _XmGetRC_PopupPosted(Widget);
+FUNC Boolean _XmGetInDragMode(Widget);
+FUNC void _XmSetInDragMode(Widget, Boolean);
+FUNC void _XmSaveMenuProcContext(XtPointer);
+FUNC XtPointer _XmGetMenuProcContext(void);
+FUNC int _XmGrabPointer(Widget, int, unsigned int, int, int, Window, Cursor, Time);
+FUNC int _XmGrabKeyboard(Widget, int, int, int, Time);
+FUNC void _XmMenuSetInPMMode(Widget, Boolean);
+FUNC void _XmSetMenuTraversal(Widget, Boolean);
+FUNC void _XmLeafPaneFocusOut(Widget);
+FUNC void _XmMenuTraverseLeft(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmMenuTraverseRight(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmMenuTraverseUp(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmMenuTraverseDown(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmMenuEscape(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmRC_GadgetTraverseDown(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmRC_GadgetTraverseUp(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmRC_GadgetTraverseLeft(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmRC_GadgetTraverseRight(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmMenuTraversalHandler(Widget, Widget, XmTraversalDirection);
+FUNC void _XmSaveCoreClassTranslations(Widget);
+FUNC void _XmRestoreCoreClassTranslations(Widget);
+FUNC XmMenuState _XmGetMenuState(Widget);


