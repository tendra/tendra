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


/* SCO CID (IXI) ScrolledWP.h,v 1.1 1996/08/08 14:13:27 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ManagerP.h";
+USE "motif/1_2", "Xm/ScrolledW.h";
+USE "motif/1_2", "Xm/ScrollBar.h";
+USE "motif/1_2", "Xm/DrawingA.h";

+FIELD (struct) _XmScrolledWindowConstraintPart := { 
	
	unsigned char	child_type;
};

+TYPEDEF _XmScrolledWindowConstraintPart XmScrolledWindowConstraintPart;
+TYPEDEF _XmScrolledWindowConstraintPart * XmScrolledWindowConstraint;


+FIELD (struct) XmScrolledWindowClassPart:= {

     	XtPointer	extension;
};


+FIELD (struct) _XmScrolledWindowClassRec := {

    CoreClassPart		core_class;
    CompositeClassPart  	composite_class;
    ConstraintClassPart 	constraint_class;
    XmManagerClassPart  	manager_class;
    XmScrolledWindowClassPart	swindow_class;
};

+TYPEDEF _XmScrolledWindowClassRec XmScrolledWindowClassRec;

+EXP lvalue XmScrolledWindowClassRec xmScrolledWindowClassRec;

+FIELD (struct) XmScrolledWindowPart := {

   int 			vmin;
   int 			vmax;
   int 			vOrigin;
   int 			vExtent;

   int 			hmin;
   int 			hmax;
   int 			hOrigin;
   int 			hExtent;

   Position 		hsbX,hsbY;
   Dimension 		hsbWidth,hsbHeight;

   Position 		vsbX,vsbY;
   Dimension 		vsbWidth,vsbHeight;

   Dimension    	GivenHeight, GivenWidth;

   Dimension		AreaWidth,AreaHeight;
   Dimension		WidthPad,HeightPad;
   Position		XOffset, YOffset;

   Dimension		pad;

   Boolean		hasHSB;
   Boolean		hasVSB;
   Boolean		InInit;
   Boolean		FromResize;

   unsigned char	VisualPolicy;
   unsigned char	ScrollPolicy;
   unsigned char	ScrollBarPolicy;
   unsigned char	Placement;
   
   XmScrollBarWidget   	hScrollBar;
   XmScrollBarWidget   	vScrollBar;
   XmDrawingAreaWidget 	ClipWindow;
   Widget              	WorkWindow;
   
   XtCallbackList       traverseObscuredCallback;
};


+FIELD (struct) _XmScrolledWindowRec := {

    CorePart	    	core;
    CompositePart   	composite;
    ConstraintPart 	constraint;
    XmManagerPart   	manager;
    XmScrolledWindowPart   swindow;
};

+TYPEDEF _XmScrolledWindowRec XmScrolledWindowRec;

+CONST int DEFAULT_HEIGHT;
+CONST int DEFAULT_WIDTH;


+FUNC char * _XmGetRealXlations(Display *dpy, _XmBuildVirtualKeyStruct *keys,
				int num_keys) ;
+FUNC void _XmInitializeScrollBars(Widget w) ;
