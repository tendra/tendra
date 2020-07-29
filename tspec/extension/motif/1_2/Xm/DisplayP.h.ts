# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/DesktopP.h.ts";
+USE "motif/1_2", "Xm/VendorSEP.h.ts";
+USE "motif/1_2", "Xm/DropSMgr.h.ts";
+USE "motif/1_2", "Xm/Display.h.ts";
+USE "motif/1_2", "Xm/ScreenP.h.ts";

+USE "motif/1_2", "Xm/DragCP.h.ts";
+USE "motif/1_2", "Xm/VirtKeysP.h.ts";

+TYPEDEF Widget (*XmDisplayGetDisplayProc)(Display *);

+FIELD (struct) XmDisplayClassPart := { 

	XmDisplayGetDisplayProc	GetDisplay;
	XtPointer		extension;

};


+FIELD (struct) _XmDisplayClassRec := { 

	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ShellClassPart			shell_class;
	WMShellClassPart		wm_shell_class;
	VendorShellClassPart		vendor_shell_class;
	TopLevelShellClassPart		top_level_shell_class;
	ApplicationShellClassPart	application_shell_class;
	XmDisplayClassPart		display_class;
};

+TYPEDEF _XmDisplayClassRec XmDisplayClassRec;

+FIELD (struct) _XmModalDataRec := { 

	Widget				wid;
	XmVendorShellExtObject		ve;
	XmVendorShellExtObject		grabber;
	Boolean				exclusive;
	Boolean				springLoaded;
};

+TYPEDEF _XmModalDataRec XmModalDataRec;
+TYPEDEF _XmModalDataRec *XmModalData;

+FIELD (struct) XmDisplayPart := { 

	unsigned char			dragInitiatorProtocolStyle;
	unsigned char			dragReceiverProtocolStyle;
	unsigned char			userGrabbed;
	WidgetClass			dragContextClass;
	WidgetClass			dropTransferClass;
	WidgetClass			dropSiteManagerClass;
	XmDragContext			activeDC;
	XmDropSiteManagerObject		dsm;
	Time				lastDragTime;
	Window				proxyWindow;

	XmModalData			modals;
	Cardinal			numModals;
	Cardinal			maxModals;
	XtPointer			xmim_info;

	String				bindingsString;
	XmKeyBindingRec			*bindings;
	XKeyEvent			*lastKeyEvent;
	unsigned char			keycode_tag[XmKEYCODE_TAG_SIZE];

	int				shellCount;
	XtPointer			displayInfo;
};

+TYPEDEF XmDisplayPart *XmDisplayPartPtr;

+FIELD (struct) _XmDisplayInfo := { 

	Cursor		SashCursor;
	Widget		destinationWidget;
	Cursor		TearOffCursor;
	XtPointer	UniqueStamp;
	XtPointer	keypad_info;
	XtPointer	mod_info;
};

+TYPEDEF _XmDisplayInfo XmDisplayInfo;


+FIELD (struct) _XmDisplayRec := { 

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	WMShellPart		wm;
	VendorShellPart		vendor;
	TopLevelShellPart	topLevel;
	ApplicationShellPart	application;
	XmDisplayPart		display;
};

+TYPEDEF _XmDisplayRec XmDisplayRec;

+EXP lvalue XmDisplayClassRec xmDisplayClassRec;

+CONST String _Xm_MOTIF_DRAG_AND_DROP_MESSAGE;


+FUNC XmDropSiteManagerObject _XmGetDropSiteManagerObject(XmDisplay);
+FUNC unsigned char _XmGetDragProtocolStyle(Widget);
+FUNC unsigned char _XmGetDragTrackingMode(Widget);
+FUNC Widget _XmGetDragContextFromHandle(Widget, Atom);

+FUNC WidgetClass _XmGetXmDisplayClass(void);
+FUNC WidgetClass _XmSetXmDisplayClass(WidgetClass);



