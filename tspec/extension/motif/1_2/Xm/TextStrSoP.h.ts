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


+TYPE XmTextScanDirection;
+TYPE XmTextStatus;

+FIELD (struct) _XmSourceDataRec := { 

	XmTextSource		source;
	XmTextWidget		*widgets;
	XmTextPosition		left;
	XmTextPosition		right;
	char			* ptr;
	char			*value;
	char			* gap_start;
	char			* gap_end;
	char			* PSWC_NWLN;
	int			length;
	int			maxlength;
	int			old_length;
	int			numwidgets;
	int			maxallowed;
	Time			prim_time;
	Boolean			hasselection;
	Boolean			editable;
};

+TYPEDEF _XmSourceDataRec XmSourceDataRec;
+TYPEDEF _XmSourceDataRec *XmSourceData;

+TYPEDEF void (*AddWidgetProc)(XmTextSource, XmTextWidget);
+TYPEDEF int (*CountLinesProc)(XmTextSource, XmTextPosition, unsigned long);
+TYPEDEF void (*RemoveWidgetProc)(XmTextSource, XmTextWidget);
+TYPEDEF XmTextPosition (*ReadProc)(XmTextSource, XmTextPosition, XmTextPosition, XmTextBlock);
+TYPEDEF XmTextStatus (*ReplaceProc)(XmTextWidget, XEvent *,XmTextPosition *, XmTextPosition *, XmTextBlock, Boolean);
+TYPEDEF XmTextPosition (*ScanProc)(XmTextSource, XmTextPosition, XmTextScanType, XmTextScanDirection, int, Boolean);
+TYPEDEF Boolean (*GetSelectionProc)(XmTextSource, XmTextPosition *, XmTextPosition *);
+TYPEDEF void (*SetSelectionProc)(XmTextSource, XmTextPosition, XmTextPosition, Time);

+FIELD (struct) _XmTextSourceRec := { 

	XmSourceDataRec		*data;
	AddWidgetProc		AddWidget;
	CountLinesProc		CountLines;
	RemoveWidgetProc	RemoveWidget;
	ReadProc		ReadSource;
	ReplaceProc		Replace;
	ScanProc		Scan;
	GetSelectionProc	GetSelection;
	SetSelectionProc	SetSelection;
};

+TYPEDEF _XmTextSourceRec XmTextSourceRec;

+FUNC char *_XmStringSourceGetString(XmTextWidget, XmTextPosition, XmTextPosition, Boolean);
+FUNC Boolean _XmTextFindStringBackwards(Widget, XmTextPosition, char *, XmTextPosition *);
+FUNC Boolean _XmTextFindStringForwards(Widget, XmTextPosition, char *, XmTextPosition *);
+FUNC Boolean _XmStringSourceFindString(Widget, XmTextPosition, char *, XmTextPosition *);
+FUNC void _XmStringSourceSetGappedBuffer(XmSourceData, XmTextPosition);
+FUNC Boolean _XmTextModifyVerify(XmTextWidget, XEvent *, XmTextPosition *, XmTextPosition *, XmTextPosition *, XmTextBlock, XmTextBlock, Boolean *);
+FUNC XmTextSource _XmStringSourceCreate(char *, Boolean);
+FUNC void _XmStringSourceDestroy(XmTextSource);
+FUNC char * _XmStringSourceGetValue(XmTextSource, Boolean);
+FUNC void _XmStringSourceSetValue(XmTextWidget, char *);
+FUNC Boolean _XmStringSourceHasSelection(XmTextSource);
+FUNC Boolean _XmStringSourceGetEditable(XmTextSource);
+FUNC void _XmStringSourceSetEditable(XmTextSource, Boolean);
+FUNC int _XmStringSourceGetMaxLength(XmTextSource);
+FUNC void _XmStringSourceSetMaxLength(XmTextSource, int);
+FUNC void _XmTextValueChanged(XmTextWidget, XEvent *);

