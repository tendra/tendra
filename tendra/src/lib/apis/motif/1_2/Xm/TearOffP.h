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



/* SCO CID (IXI) TearOffP.h,v 1.1 1996/08/08 14:13:35 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";

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

