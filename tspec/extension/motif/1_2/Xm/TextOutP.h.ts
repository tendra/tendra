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
+USE "motif/1_2", "Xm/Text.h.ts";

+FIELD (struct) _LineTableExtraRec := {

	Dimension		width;
	Boolean			wrappedbychar;
};

+TYPEDEF _LineTableExtraRec LineTableExtraRec;
+TYPEDEF _LineTableExtraRec *LineTableExtra ;


+TYPEDEF unsigned int LineNum;

+TYPEDEF int OnOrOff;
+CONST int on;
+CONST int off;

+CONST int NOLINE;

+FIELD (struct) _OutputDataRec := {

	XmFontList		fontlist;
	unsigned int		blinkrate;
	Boolean			wordwrapl;
	Boolean			cursor_position_visible;
	Boolean			autoshowinsertpoint;
	Boolean			hasfocus;
	Boolean			has_rect;
	Boolean			handlingexposures;
	Boolean			exposevscroll;
	Boolean			exposehscroll;
	Boolean 		resizewidth;
	Boolean			resizeheight;
	Boolean			scrollvertical;
	Boolean			scrollhorizontal;
	Boolean			scrollleftside;
	Boolean			scrolltopside;
	Boolean			ignorevbar;
	Boolean			ignorehbar;
	short			cursor_on;
	Boolean			refresh_ibeam_off;
	Boolean			suspend_hoffset;
	Boolean			use_fontset;
	Boolean			have_inverted_image_gc;

	OnOrOff			blinkstate;
	
	Position		insertx;
	Position		inserty;

	int			number_lines;
	int			leftmargin;
	int			rightmargin;
	int			topmargin;
	int			bottommargin;
	int			scrollwidth;
	int			vsliderSize;
	int			hoffset;
	int			averagecharwidth;
	int			tabwidth;
	short 			columns;
	short			rows;
	Dimension		lineheight;
	Dimension		minwidth;
	Dimension		minheight;
	Dimension 		prevW;
	Dimension		prevH;
	Dimension		cursorwidth;
	Dimension		cursorheight;
	Dimension		font_ascent;
	Dimension		font_descent;
	XtIntervalId		timerid;
	Pixmap			cursor;
	Pixmap			add_mode_cursor;
	Pixmap			ibeam_off;
	Pixmap			stipple_tile;
	GC			gc;
	GC			imagegc;
	Widget			vbar;
	Widget			hbar;
	XFontStruct		*font;

	GC			save_gc;
	short			columns_set;
	short			rows_set;
};

+TYPEDEF _OutputDataRec OutputDataRec;
+TYPEDEF _OutputDataRec *OutputData;

+TYPEDEF void (*OutputCreateProc)(Widget, ArgList, Cardinal);
+TYPEDEF XmTextPosition (*XYToPosProc)(XmTextWidget, Position, Position);
+TYPEDEF Boolean (*PosToXYProc)(XmTextWidget, XmTextPosition, Position *, Position *);

+CONST long PASTENDPOS;

+TYPEDEF Boolean (*MeasureLineProc)(XmTextWidget, LineNum, XmTextPosition, XmTextPosition *, LineTableExtraRec **);

+TYPEDEF void (*DrawProc)(XmTextWidget, LineNum, XmTextPosition, XmTextPosition, XmHighlightMode);

+TYPEDEF void (*DrawInsertionPointProc)(XmTextWidget, XmTextPosition, OnOrOff);
+TYPEDEF void (*MakePositionVisibleProc)(XmTextWidget, XmTextPosition);

+TYPEDEF Boolean (*MoveLinesProc)(XmTextWidget, LineNum, LineNum, LineNum);

+TYPEDEF void (*InvalidateProc)(XmTextWidget, XmTextPosition, XmTextPosition, long);

+TYPEDEF void (*GetPreferredSizeProc)(Widget, Dimension *, Dimension *);

+TYPEDEF void (*GetValuesProc)(Widget, ArgList, Cardinal);

+TYPEDEF Boolean (*SetValuesProc)(Widget, Widget, Widget, ArgList, Cardinal *);

+FIELD (struct) _OutputRec := { 

	OutputDataRec		*data;
	XYToPosProc		XYToPos;
	PosToXYProc		PosToXY;
	MeasureLineProc		MeasureLine;
	DrawProc		Draw;
	DrawInsertionPointProc	DrawInsertionPoint;
	MakePositionVisibleProc	MakePositionVisible;
	MoveLinesProc		MoveLines;
	InvalidateProc		Invalidate;
	GetPreferredSizeProc	GetPreferredSize;
	GetValuesProc		GetValues;
	SetValuesProc		SetValues;
	XmRealizeOutProc	realize;
	XtWidgetProc		destroy;
	XmResizeFlagProc	resize;
	XtExposeProc		expose;
};

+TYPEDEF _OutputRec OutputRec;

+FUNC void _XmTextFreeContextData(Widget, XtPointer, XtPointer);
+FUNC void _XmTextResetClipOrigin(XmTextWidget, XmTextPosition, Boolean);
+FUNC void _XmTextAdjustGC(XmTextWidget);
+FUNC Boolean _XmTextShouldWordWrap(XmTextWidget);
+FUNC Boolean _XmTextScrollable(XmTextWidget);
+FUNC XmTextPosition _XmTextFindLineEnd(XmTextWidget, XmTextPosition, LineTableExtra *);
+FUNC void _XmTextOutputGetSecResData(XmSecondaryResourceData *);
+FUNC int _XmTextGetNumberLines(XmTextWidget);
+FUNC void _XmTextMovingCursorPosition(XmTextWidget, XmTextPosition);
+FUNC void _XmTextDrawDestination(XmTextWidget);
+FUNC void _XmTextClearDestination(XmTextWidget, Boolean);
+FUNC void _XmTextDestinationVisible(Widget, Boolean);
+FUNC void _XmTextChangeBlinkBehavior(XmTextWidget, Boolean);
+FUNC void _XmTextOutputCreate(Widget, ArgList, Cardinal);
+FUNC Boolean _XmTextGetBaselines(Widget, Dimension **, int *);
+FUNC Boolean _XmTextGetDisplayRect(Widget, XRectangle *);
+FUNC void _XmTextMarginsProc(Widget, XmBaselineMargins *);
+FUNC void _XmTextChangeHOffset(XmTextWidget, int);
+FUNC void _XmTextToggleCursorGC(Widget);


+DEFINE ShouldWordWrap(data, widget) %% (data->wordwrap && (!(data->scrollhorizontal && (XtClass(widget->core.parent) == xmScrolledWindowWidgetClass))) && widget->text.edit_mode != XmSINGLE_LINE_EDIT && !data->resizewidth) %% ;
