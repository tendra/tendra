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



/* SCO CID (IXI) DropSMgrP.h,v 1.1 1996/08/08 14:12:45 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";
+USE "motif/1_2", "Xm/DropSMgr.h";

+TYPEDEF void (*XmDSMCreateInfoProc)(XmDropSiteManagerObject, Widget, ArgList, Cardinal);

+TYPEDEF void (*XmDSMDestroyInfoProc)(XmDropSiteManagerObject, Widget);

+TYPEDEF void (*XmDSMStartUpdateProc)(XmDropSiteManagerObject, Widget);

+TYPEDEF void (*XmDSMRetrieveInfoProc)(XmDropSiteManagerObject, Widget, ArgList, Cardinal);

+TYPEDEF void (*XmDSMUpdateInfoProc) (XmDropSiteManagerObject, Widget, ArgList, Cardinal);

+TYPEDEF void (*XmDSMEndUpdateProc) (XmDropSiteManagerObject, Widget);

+TYPEDEF void (*XmDSMUpdateProc) (XmDropSiteManagerObject, XtPointer, XtPointer);

+TYPEDEF void (*XmDSMProcessMotionProc) (XmDropSiteManagerObject, XtPointer, XtPointer);

+TYPEDEF void (*XmDSMProcessDropProc) (XmDropSiteManagerObject, XtPointer, XtPointer);

+TYPEDEF void (*XmDSMOperationChangedProc) (XmDropSiteManagerObject, XtPointer, XtPointer);

+TYPEDEF void (*XmDSMChangeRootProc) (XmDropSiteManagerObject, XtPointer, XtPointer);

+TYPEDEF void (*XmDSMInsertInfoProc) (XmDropSiteManagerObject, XtPointer, XtPointer);

+TYPEDEF void (*XmDSMRemoveInfoProc) (XmDropSiteManagerObject, XtPointer);

+TYPEDEF void (*XmDSMSyncTreeProc) (XmDropSiteManagerObject, Widget);

+TYPEDEF int  (*XmDSMGetTreeFromDSMProc) (XmDropSiteManagerObject, Widget, XtPointer);

+TYPEDEF void (*XmDSMCreateDSInfoTable) (XmDropSiteManagerObject);

+TYPEDEF void (*XmDSMDestroyDSInfoTable) (XmDropSiteManagerObject);

+TYPEDEF void (*XmDSMRegisterInfoProc) (XmDropSiteManagerObject, Widget, XtPointer);

+TYPEDEF XtPointer (*XmDSMWidgetToInfoProc) (XmDropSiteManagerObject, Widget);

+TYPEDEF void (*XmDSMUnregisterInfoProc)(XmDropSiteManagerObject, XtPointer);

+FIELD (struct) XmDropSiteManagerClassPart := { 

	XmDSMCreateInfoProc	createInfo;
	XmDSMDestroyInfoProc	destroyInfo;
	XmDSMStartUpdateProc	startUpdate;
	XmDSMRetrieveInfoProc	retrieveInfo;
	XmDSMUpdateInfoProc	updateInfo;
	XmDSMEndUpdateProc	endUpdate;

	XmDSMUpdateProc		updateDSM;
	
	XmDSMProcessMotionProc	processMotion;
	XmDSMProcessDropProc	processDrop;
	XmDSMOperationChangedProc	operationChanged;
	XmDSMChangeRootProc	changeRoot;

	XmDSMInsertInfoProc	insertInfo;
	XmDSMRemoveInfoProc	removeInfo;

	XmDSMSyncTreeProc	syncTree;
	XmDSMGetTreeFromDSMProc	getTreeFromDSM;

	XmDSMCreateDSInfoTable	createTable;
	XmDSMDestroyDSInfoTable	destroyTable;
	XmDSMRegisterInfoProc	registerInfo;
	XmDSMWidgetToInfoProc	widgetToInfo;
	XmDSMUnregisterInfoProc	unregisterInfo;

	XtPointer		extension;
};

+FIELD (struct) _XmDropSiteManagerClassRec := { 

	ObjectClassPart		object_class;
	XmDropSiteManagerClassPart	dropManager_class;
};

+TYPEDEF _XmDropSiteManagerClassRec XmDropSiteManagerClassRec;

+EXP lvalue XmDropSiteManagerClassRec xmDropSiteManagerClassRec;

+MACRO void DSMCreateInfo(XmDropSiteManagerObject, Widget, ArgList, Cardinal);
+MACRO void DSMDestroyInfo(XmDropSiteManagerObject, Widget);
+MACRO void DSMStartUpdate(XmDropSiteManagerObject, Widget);
+MACRO void DSMRetrieveInfo(XmDropSiteManagerObject, Widget, ArgList, Cardinal);
+MACRO void DSMUpdateInfo(XmDropSiteManagerObject, Widget, ArgList, Cardinal);
+MACRO void DSMEndUpdate(XmDropSiteManagerObject, Widget);
+MACRO void DSMUpdate(XmDropSiteManagerObject, XtPointer, XtPointer);
+MACRO void DSMProcessMotion(XmDropSiteManagerObject, XtPointer, XtPointer);
+MACRO void DSMProcessDrop(XmDropSiteManagerObject, XtPointer, XtPointer);
+MACRO void DSMOperationChanged(XmDropSiteManagerObject, XtPointer, XtPointer);
+MACRO void DSMChangeRoot(XmDropSiteManagerObject, XtPointer, XtPointer);
+MACRO void DSMInsertInfo(XmDropSiteManagerObject, XtPointer, XtPointer);
+MACRO void DSMRemoveInfo(XmDropSiteManagerObject, XtPointer);
+MACRO void DSMSyncTree(XmDropSiteManagerObject, Widget);
+MACRO int  DSMGetTreeFromDSM(XmDropSiteManagerObject, Widget, XtPointer);
+MACRO void DSMCreateTable(XmDropSiteManagerObject);
+MACRO void DSMDestroyTable(XmDropSiteManagerObject);
+MACRO void DSMRegisterInfo(XmDropSiteManagerObject, Widget, XtPointer);
+MACRO void DSMWidgetToInfo(XmDropSiteManagerObject, Widget);
+MACRO void DSMUnregisterInfo(XmDropSiteManagerObject, XtPointer);

+TYPE (struct) __XmDropSiteUpdateInfoRec;

+FIELD (struct) __XmDropSiteUpdateInfoRec := { 

	XmDropSiteManagerObject		dsm;
	Widget				refWidget;
	__XmDropSiteUpdateInfoRec	*next;
};

+TYPEDEF __XmDropSiteUpdateInfoRec _XmDropSiteUpdateInfoRec;
+TYPEDEF __XmDropSiteUpdateInfoRec *_XmDropSiteUpdateInfo;

+FIELD (struct) _XmDropSiteManagerPart := { 

	XtCallbackProc		notifyProc;
	XtCallbackProc		treeUpdateProc;
	XtPointer		client_data;
	XtPointer		dragUnderData;
	XtPointer		curInfo;
	Time			curTime;
	Position		curX;
	Position		curY;
	Position		oldX;
	Position		oldY;
	unsigned char		curDropSiteStatus;
	Widget			curDragContext;
	Boolean			curAnimate;
	unsigned char		curOperations;
	unsigned char 		curOperation;
	XmRegion		curAncestorClipRegion;
	XmRegion		newAncestorClipRegion;
	XtPointer		dsTable;
	XtPointer		dsRoot;
	Position		rootX;
	Position		rootY;
	Dimension		rootW;
	Dimension		rootH;
	XtPointer		clipperList;
	_XmDropSiteUpdateInfo	updateInfo;
};

+TYPEDEF _XmDropSiteManagerPart XmDropSiteManagerPart;
+TYPEDEF _XmDropSiteManagerPart *XmDropSiteManagerPartPtr;

+FIELD (struct) _XmDropSiteManagerRec := { 

	ObjectPart		object;
	XmDropSiteManagerPart	dropManager;
};

+TYPEDEF _XmDropSiteManagerRec XmDropSiteManagerRec;

+FUNC void _XmDSMUpdate(XmDropSiteManagerObject, XtPointer, XtPointer);
+FUNC int _XmDSMGetTreeFromDSM(XmDropSiteManagerObject, Widget, XtPointer);
+FUNC Boolean _XmDropSiteShell(Widget);
+FUNC Boolean _XmDropSiteWrapperCandidate(Widget);
+FUNC Widget _XmGetActiveDropSite(Widget);
+FUNC void _XmSyncDropSiteTree(Widget);
+FUNC void _XmIEndUpdate(XtPointer, XtIntervalId *);

