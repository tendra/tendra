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



/* SCO CID (IXI) ShellEP.h,v 1.1 1996/08/08 14:13:32 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/DesktopP.h";
+USE "x5/t", "X11/Shell.h";
+USE "x5/t", "X11/Intrinsic.h";

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



 
