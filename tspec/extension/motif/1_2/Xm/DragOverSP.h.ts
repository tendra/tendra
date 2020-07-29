# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "x5/t", "X11/Shell.h.ts";
+USE "x5/t", "X11/ShellP.h.ts";
+USE "motif/1_2", "Xm/XmP.h.ts";
+USE "motif/1_2", "Xm/DragIconP.h.ts";
+USE "motif/1_2", "Xm/DragOverS.h.ts";

/* unused */

+DEFINE DOExpose(do) %% ((XtClass(do))->core_class.expose) ((Widget)(do), NULL, NULL) %% ;

+FIELD (struct) XmDragOverShellClassPart := { 

	XtPointer		extension;
};


+FIELD (struct) _XmDragOverShellClassRec := { 

	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ShellClassPart			shell_class;
	WMShellClassPart		wm_shell_class;
	VendorShellClassPart		vendor_shell_class;
	XmDragOverShellClassPart	dragOver_shell_class;
};

+TYPEDEF _XmDragOverShellClassRec XmDragOverShellClassRec;

+EXP lvalue XmDragOverShellClassRec xmDragOverShellClassRec;

+FIELD (struct) _XmBackingRec := { 

	Position	x;
	Position	y;
	Pixmap 		pixmap;
};

+TYPEDEF _XmBackingRec XmBackingRec;
+TYPEDEF _XmBackingRec *XmBacking;

+FIELD (struct) _XmDragOverBlendRec := { 

	XmDragIconObject	sourceIcon;
	Position		sourceX;
	Position		sourceY;
	XmDragIconObject	mixedIcon;
	GC			gc;
};

+TYPEDEF _XmDragOverBlendRec XmDragOverBlendRec;
+TYPEDEF _XmDragOverBlendRec *XmDragOverBlend;

+FIELD (struct) _XmDragOverShellPart :={ 

	Position		hotX;
	Position		hotY;
	unsigned char		cursorState;
	unsigned char		mode;
	unsigned char		activeMode;

	Position		initialX;
	Position		initialY;

	XmDragIconObject	stateIcon;
	XmDragIconObject	opIcon;

	XmDragOverBlendRec	cursorBlend;
	XmDragOverBlendRec	rootBlend;
	Pixel			cursorForeground;
	Pixel			cursorBackground;
	Cursor			ncCursor;
	Cursor			activeCursor;

	XmBackingRec		backing;
	Pixmap			tmpPix;
	Pixmap			tmpBit;
	Boolean			isVisible;
};

+TYPEDEF _XmDragOverShellPart XmDragOverShellPart;

+FIELD (struct) _XmDragOverShellRec := { 

	CorePart		core;
	CompositePart		composite;
	ShellPart		shell;
	WMShellPart		wm;
	VendorShellPart		vendor;
	XmDragOverShellPart	drag;
};

+TYPEDEF _XmDragOverShellRec XmDragOverShellRec;



