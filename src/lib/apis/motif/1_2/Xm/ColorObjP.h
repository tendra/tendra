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


/* SCO CID (IXI) ColorObjP.h,v 1.1 1996/08/08 14:12:22 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ColorObj.h";
+USE "motif/1_2", "Xm/VendorSP.h";

+CONST String XmNuseIconFileCache;
+CONST String XmCUseIconFileCache;

+TYPEDEF PixelSet Colors[NUM_COLORS];

+FIELD (struct) _ColorObjPart := { 

	XtArgsProc	RowColInitHook;
	PixelSet	*myColors;
	int		myScreen;
	Display		*display;
	Colors		*colors;
	int		numScreens;
	Atom		*atoms;
	Boolean		colorIsRunning;
	Boolean		done;
	int		*colorUse;
	int		primary;
	int		secondary;
	int		text;
	int		active;
	int		inactive;
	Boolean		useColorObj;
	Boolean		useText;
	Boolean		useTextForList;
	Boolean		useMask;
	Boolean		useMultiColorIcons;
	Boolean		useIconFileCache;
}; 

+TYPEDEF _ColorObjPart ColorObjPart;

+FIELD (struct) _ColorObjRec := { 

	CorePart	core;
	CompositePart	composite;
	ShellPart	shell;
	WMShellPart	wm;
	ColorObjPart	color_obj;
};

+TYPEDEF _ColorObjRec ColorObjRec;

+FIELD (struct) _ColorObjClassPart := { 

	XtPointer	extension;
};

+TYPEDEF _ColorObjClassPart ColorObjClassPart;


+FIELD (struct) _ColorObjClassRec := { 

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ShellClassPart		shell_class;
	WMShellClassPart	wm_shell_class;
	ColorObjClassPart	color_obj_class;
};

+TYPEDEF _ColorObjClassRec ColorObjClassRec;

+EXP lvalue ColorObjClassRec _xmColorObjClassRec;


+FUNC void _XmColorObjCreate(Widget, ArgList, Cardinal *);
+FUNC Boolean _XmGetPixelData(int, int *, PixelSet *, short *, short *, short *, short *);
+FUNC Boolean _XmGetIconControlInfo(Screen *, Boolean *, Boolean *, Boolean *);
+FUNC Boolean _XmUseColorObj(void);

