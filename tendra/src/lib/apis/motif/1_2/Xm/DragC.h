/*
    Copyright (c) 1995 Open Software Foundation, Inc.

    All Rights Reserved

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, provided
    that the above copyright notice appears in all copies and that both the
    copyright notice and this permission notice appear in supporting
    documentation.

    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
    INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
    CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
    COPYRIGHT NOTICE

    This program contains amendments to Motif 1.1 API headers in
    order to represent the Motif 1.2 API. These amendments are the
    property of IXI Ltd, a subsidiary of the Santa Cruz Operation (SCO).
    Use, reproduction, production of amended versions and/or transfer of
    this program is permitted PROVIDED THAT:

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


/* SCO CID (IXI) DragC.h,v 1.1 1996/08/08 14:12:33 wendland Exp */

+USE "motif/1_2", "Xm/Xm.h";

+CONST int XmHELP;

+TYPEDEF unsigned int XmID;

+CONST String _XA_MOTIF_DROP;
+CONST String _XA_DRAG_SUCCESS;

/* these were enums */
+CONST int XmTOP_LEVEL_ENTER;
+CONST int XmTOP_LEVEL_LEAVE;
+CONST int XmDRAG_MOTION;
+CONST int XmDROP_SITE_ENTER;
+CONST int XmDROP_SITE_LEAVE;
+CONST int XmDROP_START;
+CONST int XmDROP_FINISH;
+CONST int XmDRAG_DROP_FINISH;
+CONST int XmOPERATION_CHANGED;

+CONST int XmDROP;
+CONST int XmDROP_HELP;
+CONST int XmDROP_CANCEL;

+CONST int XmDROP_NOOP;
+CONST int XmDROP_MOVE;
+CONST int XmDROP_COPY;
+CONST int XmDROP_LINK;

+CONST int XmBLEND_ALL;
+CONST int XmBLEND_STATE_SOURCE;
+CONST int XmBLEND_JUST_SOURCE;
+CONST int XmBLEND_NONE;


+CONST int XmDROP_FAILURE;
+CONST int XmDROP_SUCCESS;

+CONST int XmCR_TOP_LEVEL_ENTER;
+CONST int XmCR_TOP_LEVEL_LEAVE;
+CONST int XmCR_DRAG_MOTION;
+CONST int XmCR_DROP_SITE_ENTER;
+CONST int XmCR_DROP_SITE_LEAVE;
+CONST int XmCR_DROP_START;
+CONST int XmCR_DROP_FINISH;
+CONST int XmCR_DRAG_DROP_FINISH;
+CONST int XmCR_OPERATION_CHANGED;
+CONST int _XmNUMBER_DND_CB_REASONS;

+TYPE (struct) _XmDragContextClassRec;
+TYPE (struct) _XmDragContextRec;
+TYPEDEF _XmDragContextClassRec *XmDragContextClass;
+TYPEDEF _XmDragContextRec *XmDragContext;

+EXP lvalue WidgetClass xmDragContextClass;

+FIELD (struct) _XmAnyICCCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
};

+TYPEDEF _XmAnyICCCallbackStruct XmAnyICCCallbackStruct;
+TYPEDEF _XmAnyICCCallbackStruct *XmAnyICCCallback;


+FIELD (struct) _XmTopLevelEnterCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
	Screen		*screen;
	Window		window;
	Position	x;
	Position	y;
	unsigned char	dragProtocolStyle;
	Atom 		iccHandle;
};

+TYPEDEF _XmTopLevelEnterCallbackStruct XmTopLevelEnterCallbackStruct;
+TYPEDEF _XmTopLevelEnterCallbackStruct *XmTopLevelEnterCallback;

+FIELD (struct) _XmTopLevelLeaveCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
	Screen		*screen;
	Window		window;
};

+TYPEDEF _XmTopLevelLeaveCallbackStruct XmTopLevelLeaveCallbackStruct;
+TYPEDEF _XmTopLevelLeaveCallbackStruct *XmTopLevelLeaveCallback;

+FIELD (struct) _XmDropSiteEnterCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
	unsigned char	operation;
	unsigned char	operations;
	unsigned char	dropSiteStatus;
	Position	x;
	Position	y;
};

+TYPEDEF _XmDropSiteEnterCallbackStruct XmDropSiteEnterCallbackStruct;
+TYPEDEF _XmDropSiteEnterCallbackStruct *XmDropSiteEnterCallback;

+FIELD (struct) _XmDropSiteLeaveCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
};

+TYPEDEF _XmDropSiteLeaveCallbackStruct XmDropSiteLeaveCallbackStruct;
+TYPEDEF _XmDropSiteLeaveCallbackStruct *XmDropSiteLeaveCallback;

+FIELD (struct) _XmDragMotionCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
};

+TYPEDEF _XmDragMotionCallbackStruct XmDragMotionCallbackStruct;
+TYPEDEF _XmDragMotionCallbackStruct *XmDragMotionCallback;

+FIELD (struct) _XmOperationChangedCallbackStruct := { 

        int             reason;
        XEvent          *event;
        Time            timeStamp;
        unsigned char   operation;
        unsigned char   operations;
        unsigned char   dropSiteStatus;
};

+TYPEDEF _XmOperationChangedCallbackStruct XmOperationChangedCallbackStruct;
+TYPEDEF _XmOperationChangedCallbackStruct *XmOperationChangedCallback;

+FIELD (struct) _XmDropStartCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
	unsigned char	operation;
	unsigned char	operations;
	unsigned char	dropSiteStatus;
	unsigned char	dropAction;
	Position	x;
	Position	y;
	Window		window;
	Atom		iccHandle;
};

+TYPEDEF _XmDropStartCallbackStruct XmDropStartCallbackStruct;
+TYPEDEF _XmDropStartCallbackStruct *XmDropStartCallback;


+FIELD (struct) _XmDropFinishCallbackStruct := { 

        int             reason;
        XEvent          *event;
        Time            timeStamp;
        unsigned char   operation;
        unsigned char   operations;
        unsigned char   dropSiteStatus;
        unsigned char   dropAction;
	unsigned char	completionStatus;
};

+TYPEDEF _XmDropFinishCallbackStruct XmDropFinishCallbackStruct;
+TYPEDEF _XmDropFinishCallbackStruct *XmDropFinishCallback;

+FIELD (struct) _XmDragDropFinishCallbackStruct := { 

	int		reason;
	XEvent		*event;
	Time		timeStamp;
};

+TYPEDEF _XmDragDropFinishCallbackStruct XmDragDropFinishCallbackStruct;
+TYPEDEF _XmDragDropFinishCallbackStruct *XmDragDropFinishCallback;


+FUNC Widget XmDragStart(Widget, XEvent *, ArgList, Cardinal );
+FUNC void XmDragCancel(Widget);
+FUNC Boolean XmTargetsAreCompatible(Display *, Atom *, Cardinal, Atom *, Cardinal);

