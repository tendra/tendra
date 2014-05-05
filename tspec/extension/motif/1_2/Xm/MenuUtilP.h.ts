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

+USE "motif/1_2", "Xm/XmP.h.ts";
+USE "motif/1_2", "Xm/RowColumnP.h.ts";

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


