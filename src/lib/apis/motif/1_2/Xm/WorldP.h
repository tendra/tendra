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



/* SCO CID (IXI) WorldP.h,v 1.1 1996/08/08 14:13:56 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/DesktopP.h";

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

