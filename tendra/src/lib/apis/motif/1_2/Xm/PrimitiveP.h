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



/* SCO CID (IXI) PrimitiveP.h,v 1.1 1996/08/08 14:13:10 wendland Exp */


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

%%
#define PRIMITIVE
%%

+USE "motif/1_2", "Xm/XmP.h";


+CONST long XmPrimitiveClassExtVersion;

+FIELD (struct)  XmPrimitiveClassExtRec := {

    XtPointer           	next_extension;
    XrmQuark            	record_type;
    long                	version;
    Cardinal            	record_size;
    XmWidgetBaselineProc 	widget_baseline;
    XmWidgetDisplayRectProc  	widget_display_rect;
    XmWidgetMarginsProc 	widget_margins;
};

+TYPEDEF XmPrimitiveClassExtRec *XmPrimitiveClassExt;

+MACRO XmPrimitiveClassExt * PCEPTR(WidgetClass);
+MACRO XmPrimitiveClassExt * _XmGetPrimitiveClassExtPtr(WidgetClass, XrmQuark);

+FIELD (struct) XmPrimitiveClassPart := {

   XtWidgetProc        	 	border_highlight;
   XtWidgetProc         	border_unhighlight;
   String               	translations;
   XtActionProc         	arm_and_activate;
   XmSyntheticResource 		* syn_resources;   
   int                  	num_syn_resources;   
   XtPointer            	extension;
};


+FIELD (struct) XmPrimitiveClassRec := {

    CoreClassPart        	core_class;
    XmPrimitiveClassPart 	primitive_class;
};

+EXP lvalue XmPrimitiveClassRec xmPrimitiveClassRec;

+FIELD (struct) XmPrimitivePart := {

   Pixel   		foreground;

   Dimension   		shadow_thickness;
   Pixel   		top_shadow_color;
   Pixmap  		top_shadow_pixmap;
   Pixel   		bottom_shadow_color;
   Pixmap  		bottom_shadow_pixmap;

   Dimension   		highlight_thickness;
   Pixel   		highlight_color;
   Pixmap  		highlight_pixmap;

   XtCallbackList 	help_callback;
   XtPointer      	user_data;

   Boolean 		traversal_on;
   Boolean 		highlight_on_enter;
   Boolean 		have_traversal;

   unsigned char 	unit_type;
   XmNavigationType 	navigation_type;

   Boolean 		highlight_drawn;
   Boolean 		highlighted;

   GC      		highlight_GC;
   GC      		top_shadow_GC;
   GC      		bottom_shadow_GC;
};


+FIELD (struct)  _XmPrimitiveRec := {

   CorePart        core;
   XmPrimitivePart primitive;
};

+TYPEDEF _XmPrimitiveRec XmPrimitiveRec;

+FUNC Dimension Prim_ShadowThickness(Widget);
+FUNC Dimension Prim_HaveTraversal(Widget);


/*
 *	Function prototypes
 */

+FUNC void _XmTraverseLeft(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraverseRight(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraverseUp(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraverseDown(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraverseNext(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraversePrev(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraverseHome(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraverseNextTabGroup(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmTraversePrevTabGroup(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmPrimitiveHelp(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmPrimitiveParentActivate(Widget pw, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmPrimitiveParentCancel(Widget pw, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC Boolean _XmDifferentBackground(Widget w, Widget parent) ;

