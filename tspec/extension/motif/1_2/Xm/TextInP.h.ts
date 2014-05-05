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

+USE "motif/1_2", "Xm/Text.h.ts";
+USE "motif/1_2", "Xm/TextStrSoP.h.ts";

+FIELD (struct) SelectionHint := { 

	int	x;
	int	y;
};


+FIELD (struct) _InputDataRec := { 

	XmTextWidget		widget;
	XmTextScanType		*sarray;
	int			sarraycount;
	int			new_sel_length;
	int			threshold;
	SelectionHint		selectionHint;
	SelectionHint		Sel2Hint;
	XtIntervalId		select_id;
	XmTextScanType		stype;
	XmTextScanDirection	extendDir;
	XmTextScanDirection	Sel2ExtendDir;
	XmTextPosition		origLeft;
	XmTextPosition		origRight;
	XmTextPosition		Sel2OrigLeft;
	XmTextPosition		Sel2OrigRight;
	XmTextPosition		stuffpos;
	XmTextPosition		sel2Left;
	XmTextPosition		sel2Right;
	XmTextPosition		anchor;
	Position		select_pos_x;
	Position		select_pos_y;
	Boolean			pendingdelete;
	Boolean			syncing;
	Boolean			extending;
	Boolean			Sel2Extending;
	Boolean			hasSel2;
	Boolean			has_destination;
	Boolean			selectionMove;
	Boolean			cancel;
	Boolean			overstrike;
	Boolean			sel_start;
	Time			dest_time;
	Time			sec_time;
	Time			lasttime;
};

+TYPEDEF _InputDataRec InputDataRec;
+TYPEDEF _InputDataRec *InputData;

+TYPEDEF void (*InputCreateProc)(Widget, ArgList, Cardinal);
+TYPEDEF void (*InputGetValuesProc)(Widget, ArgList, Cardinal);
+TYPEDEF void (*InputSetValuesProc)(Widget, Widget, Widget, ArgList, Cardinal *);
+TYPEDEF void (*InputInvalidateProc)(XmTextWidget, XmTextPosition, XmTextPosition, long);
+TYPEDEF void (*InputGetSecResProc)(XmSecondaryResourceData *);


+FIELD (struct) _InputRec := { 

	InputDataRec		*data;
	InputInvalidateProc	Invalidate;
	InputGetValuesProc	GetValues;
	InputSetValuesProc	SetValues;
	XtWidgetProc		destroy;
	InputGetSecResProc	GetSecResData;
};

+TYPEDEF _InputRec InputRec;

+EXP lvalue XtPointer _XmdefaultTextActionsTable;
+EXP lvalue Cardinal _XmdefaultTextActionsTableSize;

+FUNC Widget _XmTextGetDropReciever(Widget);
+FUNC Boolean _XmTextHasDestination(Widget);
+FUNC Boolean _XmTextSetDestinationSelection(Widget, XmTextPosition, Boolean, Time);
+FUNC Boolean _XmTextSetSel2(XmTextWidget, XmTextPosition, XmTextPosition, Time);
+FUNC Boolean _XmTextGetSel2(XmTextWidget, XmTextPosition *, XmTextPosition *);
+FUNC void _XmTextInputGetSecResData(XmSecondaryResourceData *);
+FUNC XmTextPosition _XmTextGetAnchor(XmTextWidget);
+FUNC void _XmTextInputCreate(Widget, ArgList, Cardinal);

	

	
