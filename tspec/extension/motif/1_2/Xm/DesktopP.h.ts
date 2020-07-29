# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ExtObjectP.h.ts";


+FIELD (struct) _XmDesktopClassPart := { 

	WidgetClass	child_class;
	XtWidgetProc	insert_child;
	XtWidgetProc	delete_child;
	XtPointer	extension;
};

+TYPEDEF _XmDesktopClassPart XmDesktopClassPart;
+TYPEDEF _XmDesktopClassPart *XmDesktopClassPartPtr;


+FIELD (struct) _XmDesktopClassRec := { 

	ObjectClassPart		object_class;
	XmExtClassPart		ext_class;
	XmDesktopClassPart	desktop_class;
};

+TYPEDEF _XmDesktopClassRec XmDesktopClassRec;
+TYPEDEF _XmDesktopClassRec *XmDesktopObjectClass;

+FIELD (struct) XmDesktopPart := { 

	Widget		parent;
	Widget		*children;
	Cardinal	num_children;
	Cardinal	num_slots;
};

+TYPEDEF XmDesktopPart *XmDesktopPartPtr;

+FIELD (struct) _XmDesktopRec := { 

	ObjectPart	object;
	XmExtPart	ext;
	XmDesktopPart	desktop;
};

+TYPEDEF _XmDesktopRec XmDesktopRec;
+TYPEDEF _XmDesktopRec *XmDesktopObject;


+FUNC WidgetClass _XmGetActualClass(Display *, WidgetClass);
+FUNC void _XmSetActualClass(Display *, WidgetClass, WidgetClass);


