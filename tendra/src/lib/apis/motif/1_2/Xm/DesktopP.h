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



/* SCO CID (IXI) $ID$ */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ExtObjectP.h";


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


