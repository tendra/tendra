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



/* SCO CID (IXI) TextSrcP.h,v 1.1 1996/08/08 14:13:45 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "ansi", "ctype.h";

+ENUM XmTextStatus := { 

	EditDone,
	EditError,
	EditReject
};

+ENUM XmTextScanDirection := { 

	XmsdLeft,
	XmsdRight
};

+FIELD (struct) _XmSourceDataRec := { 

	XmTextSource		source;
	char			*ptr;
	char			*value;
	char			*gap_start;
	char			*gap_end;
	XmTextWidget		*widgets;
	int			length;
	int			maxlength;
	int			old_length;
	int			numwidgets;
	int			maxallowed;
	Boolean			hasselection;
	Boolean			editable;
	XmTextPosition		left;
	XmTextPosition		right;
	Time			prim_time;
};

+TYPEDEF _XmSourceDataRec XmSourceDataRec;
+TYPEDEF _XmSourceDataRec *XmSourceData;


+TYPEDEF void (*AddWidgetProc)(XmTextSource, XmTextWidget);
+TYPEDEF int (*CountLinesProc)(XmTextSource, XmTextPosition, int);
+TYPEDEF void (*RemoveWidgetProc)(XmTextSource, XmTextWidget);
+TYPEDEF XmTextPosition (*ReadProc)(XmTextSource, XmTextPosition, XmTextPosition, XmTextBlock);
+TYPEDEF XmTextStatus (*ReplaceProc)(XmTextSource, XEvent *, XmTextPosition, XmTextPosition, XmTextBlock);
+TYPEDEF XmTextPosition (*ScanProc)(XmTextSource, XmTextPosition, XmTextScanType, XmTextScanDirection, int, Boolean);
+TYPEDEF Boolean (*GetSelectionProc)(XmTextSource, XmTextPosition *, XmTextPosition *);
+TYPEDEF void (*SetSelectionProc)(XmTextSource, XmTextPosition, XmTextPosition, Time);

+FIELD (struct) _XmTextSourceRec :={ 

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

 


