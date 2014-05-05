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

+USE "motif/1_2", "Xm/VendorSEP.h.ts";
+USE "motif/1_2", "Xm/DragIcon.h.ts";


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



