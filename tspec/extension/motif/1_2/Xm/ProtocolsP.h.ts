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

+USE "motif/1_2", "Xm/Protocols.h.ts";
+USE "motif/1_2", "Xm/ExtObjectP.h.ts";

+FIELD (struct) _XmProtocolClassPart := {

	XtPointer	extension;
};

+TYPEDEF _XmProtocolClassPart XmProtocolClassPart;

+FIELD (struct) _XmProtocolClassRec := { 

	ObjectClassPart		object_class;
	XmExtClassPart		ext_class;
	XmProtocolClassPart	protocol_class;
};

+TYPEDEF _XmProtocolClassRec XmProtocolClassRec;
+TYPEDEF _XmProtocolClassRec *XmProtocolObjectClass;

+FIELD (struct) _XmProtocolPart := { 

	XtCallbackRec		pre_hook;
	XtCallbackRec		post_hook;
	XtCallbackList		callbacks;
	Atom			atom;
	Boolean			active;
};

+TYPEDEF _XmProtocolPart XmProtocolPart;
+TYPEDEF _XmProtocolPart *XmProtocolPartPtr;

+FIELD (struct) _XmProtocolRec := { 

	ObjectPart		object;
	XmExtPart		ext;
	XmProtocolPart		protocol;
};

+TYPEDEF _XmProtocolRec XmProtocolRec;
+TYPEDEF _XmProtocolRec *XmProtocol;
+TYPEDEF _XmProtocolRec **XmProtocolList;

+IFNDEF XmIsProtocol
+DEFINE XmIsProtocol(w) %% XtIsSubclass(w, xmProtocolObjectClass) %%;
+ENDIF

+EXP lvalue XmProtocolClassRec xmProtocolClassRec;
+EXP lvalue WidgetClass xmProtocolObjectClass;

+FIELD (struct) _XmProtocolMgrRec := { 

	Atom			property;
	XmProtocolList		protocols;
	Cardinal		num_protocols;
	Cardinal		max_protocols;
};

+TYPEDEF _XmProtocolMgrRec XmProtocolMgrRec;
+TYPEDEF _XmProtocolMgrRec *XmProtocolMgr;
+TYPEDEF _XmProtocolMgrRec **XmProtocolMgrList;

+FIELD (struct) _XmAllProtocolsMgrRec :={ 

	XmProtocolMgrList	protocol_mgrs;
	Cardinal		num_protocol_mgrs;
	Cardinal		max_protocol_mgrs;
	Widget			shell;
};

+TYPEDEF _XmAllProtocolsMgrRec XmAllProtocolsMgrRec;
+TYPEDEF _XmAllProtocolsMgrRec *XmAllProtocolsMgr;

+FUNC void _XmInstallProtocols(Widget);


