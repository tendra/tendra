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


/* SCO CID (IXI) DragCP.h,v 1.1 1996/08/08 14:12:34 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";
+USE "motif/1_2", "Xm/DragC.h";

+USE "x5/t", "X11/Shell.h";
+USE "x5/t", "X11/ShellP.h";

+USE "motif/1_2", "Xm/DragIcon.h";
+USE "motif/1_2", "Xm/DragOverS.h";
+USE "motif/1_2", "Xm/DropSMgrP.h";

+TYPEDEF void (*XmDragStartProc)( XmDragContext, Widget, XEvent *);
+TYPEDEF void (*XmDragCancelProc)( XmDragContext) ;

+FIELD (struct) XmDragContextClassPart := { 
	
	XmDragStartProc		start;
	XmDragCancelProc	cancel;
	XtPointer		extension;
};

+FIELD (struct) _XmDragContextClassRec := { 

	CoreClassPart		core_class;
	XmDragContextClassPart	drag_class;
};

+TYPEDEF _XmDragContextClassRec XmDragContextClassRec;

+EXP lvalue XmDragContextClassRec xmDragContextClassRec;

+CONST int XtDragByPoll;
+CONST int XtDragByEvent;

+FIELD (struct) XmDragReceiverInfoStruct := { 

	Window			frame;
	Window			window;
	Widget			shell;
	unsigned char		flags;
	unsigned char		dragProtocolStyle;
	int			xOrigin;
	int			yOrigin;
	unsigned int		width;
	unsigned int 		height;
	unsigned int		depth;
	XtPointer		iccInfo;
};

+TYPEDEF XmDragReceiverInfoStruct *XmDragReceiverInfo;

+FIELD (union) _XmConvertSelectionRec := { 

	XtConvertSelectionIncrProc	sel_incr;
	XtConvertSelectionProc		sel;
};

+TYPEDEF _XmConvertSelectionRec XmConvertSelectionRec;

+FIELD (struct) _XmDragContextPart := { 

	Atom			*exportTargets;
	Cardinal		numExportTargets;
	XmConvertSelectionRec	convertProc;
	XtPointer		clientData;
	XmDragIconObject	sourceCursorIcon;
	XmDragIconObject	stateCursorIcon;
	XmDragIconObject	operationCursorIcon;
	XmDragIconObject	sourcePixmapIcon;
	Pixel			cursorBackground;
	Pixel			cursorForeground;
	Pixel			validCursorForeground;
	Pixel			invalidCursorForeground;
	Pixel			noneCursorForeground;
	XtCallbackList		dragMotionCallback;
	XtCallbackList		operationChangedCallback;
	XtCallbackList		siteEnterCallback;
	XtCallbackList		siteLeaveCallback;
	XtCallbackList		topLevelEnterCallback;
	XtCallbackList		topLevelLeaveCallback;
	XtCallbackList		dropStartCallback;
	XtCallbackList		dropFinishCallback;
	XtCallbackList		dragDropFinishCallback;
	unsigned char		dragOperations;
	Boolean			incremental;
	unsigned char		blendModel;

	Window			srcWindow;
	Time			dragStartTime;
	Atom			iccHandle;
	Widget			sourceWidget;
	Boolean			sourceIsExternal;

	Boolean			topWindowsFetched;
	unsigned char		commType;
	unsigned char		animationType;
	
	unsigned char		operation;
	unsigned char		operations;
	unsigned int		lastEventState;
	unsigned char		dragCompletionStatus;
	unsigned char		dragDropCompletionStatus;
	Boolean			forceIPC;
	Boolean			serverGrabbed;
	Boolean			useLocal;
	Boolean			inDropSite;
	XtIntervalId		dragTimerId;

	Time			roundOffTime;
	Time			lastChangeTime;
	Time			crossingTime;
	
	Time			dragFinishTime;
	Time			dropFinishTime;

	Atom			dropSelection;
	Widget			srcShell;
	Position		startX;
	Position		startY;

	XmID			siteID;

	Screen			*currScreen;
	Window			currWmRoot;
	XmDragOverShellWidget	curDragOver;
	XmDragOverShellWidget	origDragOver;
	
	XmDragReceiverInfoStruct	*currReceiverInfo;
	XmDragReceiverInfoStruct	*rootReceiverInfo;
	XmDragReceiverInfoStruct	*receiverInfos;
	Cardinal		numReceiverInfos;
	Cardinal		maxReceiverInfos;
	
	unsigned char		trackingMode;
	unsigned char		activeProtocolStyle;
	unsigned char		activeBlendModel;
	Boolean			dragDropCancelEffect;
};

+TYPEDEF _XmDragContextPart XmDragContextPart;

+FIELD (struct) _XmDragContextRec := { 

	CorePart		core;
	XmDragContextPart	drag;
};

+TYPEDEF _XmDragContextRec XmDragContextRec;

/* not used anywhere */
+DEFINE _XmDCtoDD(dc) %% ((XmDisplay)XtParent(dc)) %%;

+MACRO void _XmDragStart(XmDragContext, Widget, XEvent *);
+MACRO void _XmDragCancel(XmDragContext);

+FUNC XmDragReceiverInfo _XmAllocReceiverInfo(XmDragContext);
+FUNC unsigned char _XmGetActiveProtocolStyle(Widget);

	
