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

+FIELD (struct) _XmExcludedParentPaneRec := { 

	short		pane_list_size;
	Widget		*pane;
	short		num_panes;
};

+TYPEDEF _XmExcludedParentPaneRec XmExcludedParentPaneRec;

+EXP lvalue XmExcludedParentPaneRec _XmExcludedParentPane;

+FUNC void _XmTearOffBtnDownEventHandler(Widget, XtPointer, XEvent *,Boolean *);
+FUNC void _XmTearOffBtnUpEventHandler(Widget, XtPointer, XEvent *, Boolean *);
+FUNC void _XmDestroyTearOffShell(Widget);
+FUNC void _XmDismissTearOff(Widget, XtPointer, XtPointer);
+FUNC void _XmTearOffInitiate(Widget, XEvent *);
+FUNC void _XmAddTearOffEventHandlers(Widget);
+FUNC Boolean _XmIsTearOffShellDescendant(Widget);
+FUNC void _XmLowerTearOffObscuringPoppingDownPanes(Widget, Widget);
+FUNC void _XmRestoreExcludedTearOffToToplevelShell(Widget, XEvent *);
+FUNC void _XmRestoreTearOffToToplevelShell(Widget, XEvent *);
+FUNC void _XmRestoreTearOffToMenuShell(Widget, XEvent *);

