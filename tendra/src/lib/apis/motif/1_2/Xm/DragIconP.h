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



/* SCO CID (IXI) DragIconP.h,v 1.1 1996/08/08 14:12:37 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/VendorSEP.h";
+USE "motif/1_2", "Xm/DragIcon.h";


+TYPEDEF void (*XmCloneVisualProc)(XmDragIconObject, Widget, Widget);
+TYPEDEF void (*XmMovePixmapProc)(XmDragIconObject, XmDragIconObject, XmDragIconObject,Position, Position);

+FIELD (struct) XmDragIconClassPart := { 

	XtPointer		extension;
};



+FIELD (struct) _XmDragIconClassRec := { 

	RectObjClassPart	rectangle_class;
	XmDragIconClassPart	dragIcon_class;
};

+TYPEDEF _XmDragIconClassRec XmDragIconClassRec;


+FIELD (struct) XmDragIconPart := { 

	Cardinal		depth;
	Pixmap			pixmap;
	Dimension		width;
	Dimension		height;
	Pixmap			mask;
	Position		hot_x;
	Position		hot_y;
	Position		offset_x;
	Position		offset_y;
	unsigned char		attachment;
	Boolean			isDirty;
	Region			region;
	Region			restore_region;
	Position		x_offset;
	Position		y_offset;
};

+TYPEDEF XmDragIconPart *XmDragIconPartPtr;

+EXP lvalue XmDragIconClassRec xmDragIconClassRec;

+FIELD (struct) XmDragIconRec := { 

	ObjectPart		object;
	RectObjPart		rectangle;
	XmDragIconPart		drag;
};


+FUNC void _XmDestroyDefaultDragIcon(XmDragIconObject);
+FUNC Boolean _XmDragIconIsDirty(XmDragIconObject);
+FUNC void _XmDragIconClean(XmDragIconObject, XmDragIconObject, XmDragIconObject);
+FUNC Widget _XmGetTextualDragIcon(Widget);



