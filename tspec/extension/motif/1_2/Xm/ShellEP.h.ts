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
+USE "x5/t", "X11/Shell.h.ts";
+USE "x5/t", "X11/Intrinsic.h.ts";

+DEFINE XmInheritEventHandler %% ((XtEventHandler)_XtInherit) %%;

+CONST int _XmRAW_MAP;
+CONST int _XmPOPUP_MAP;
+CONST int _XmMANAGE_MAP;



+FIELD (struct) XmShellExtClassPart := { 

	XtEventHandler		structureNotifyHandler;
	XtPointer		extension;
};

+TYPEDEF XmShellExtClassPart *XmShellExtClassPartPtr;

+FIELD (struct) XmShellExtClassRec := { 

	ObjectClassPart		object_class;
	XmExtClassPart		ext_class;
	XmDesktopClassPart	desktop_class;
	XmShellExtClassPart	shell_class;
};


+FIELD (struct) XmShellExtPart := { 

	unsigned long		lastConfigureRequest;
	Boolean			useAsyncGeometry;
};

+TYPEDEF XmShellExtPart *XmShellExtPartPtr;

+EXP lvalue XmShellExtClassRec  xmShellExtClassRec;


+FIELD (struct) XmShellExtRec := { 

	ObjectPart		object;
	XmExtPart		ext;
	XmDesktopPart		desktop;
	XmShellExtPart		shell;
};



 
