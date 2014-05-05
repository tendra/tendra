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

+USE "motif/1_2", "Xm/DesktopP.h.ts";

+TYPE (struct) _XmWorldRec;
+TYPE (struct) _XmWorldClassRec;
+TYPEDEF _XmWorldRec *XmWorldObject;
+TYPEDEF _XmWorldClassRec *XmWorldObjectClass;

+EXP lvalue WidgetClass xmWorldClass;

+FIELD (struct) _XmWorldClassPart := {

	XtPointer		extension;
};

+TYPEDEF _XmWorldClassPart XmWorldClassPart;
+TYPEDEF _XmWorldClassPart *XmWorldClassPartPtr;


+FIELD (struct) _XmWorldClassRec := { 

	ObjectClassPart		object_class;
	XmExtClassPart		ext_class;
	XmDesktopClassPart	desktop_class;
	XmWorldClassPart	world_class;
};

+TYPEDEF _XmWorldClassRec XmWorldClassRec;

+FIELD (struct) XmWorldPart := {

	int			foo;
};

+TYPEDEF XmWorldPart *XmWorldPartPtr;

+EXP lvalue XmWorldClassRec xmWorldClassRec;

+FIELD (struct) _XmWorldRec := { 

	ObjectPart		object;
	XmExtPart		ext;
	XmDesktopPart		desktop;
	XmWorldPart		world;
};

+TYPEDEF _XmWorldRec XmWorldRec;

+FUNC XmWorldObject _XmGetWorldObject(Widget, ArgList, Cardinal *);

