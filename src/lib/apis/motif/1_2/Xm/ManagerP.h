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


/* SCO CID (IXI) ManagerP.h,v 1.1 1996/08/08 14:13:03 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

%%
#define MANAGER
%%

+USE "motif/1_2", "Xm/XmP.h";


+DEFINE XmInheritTraversalChildrenProc %% ((XmTraversalChildrenProc) _XtInherit) %%;

+TYPEDEF Boolean (*XmTraversalChildrenProc)( Widget, Widget **, Cardinal *) ;

+FIELD (struct) XmKeyboardData := {

	unsigned int 	eventType;
	KeySym       	keysym;
	KeyCode      	key;
	unsigned int 	modifiers;
	Widget       	component;
	Boolean      	needGrab;
	Boolean      	isMnemonic;
};

/*  The class definition  */

+FIELD (struct) XmManagerClassExtRec := {

    	XtPointer 		next_extension;
    	XrmQuark 		record_type;
    	long 			version;
    	Cardinal 		record_size;
    	XmTraversalChildrenProc traversal_children ;
};

+TYPEDEF XmManagerClassExtRec *XmManagerClassExt ;

+CONST long XmManagerClassExtVersion;

+FIELD (struct) _XmManagerClassPart := {

   	String               	translations;
   	XmSyntheticResource 	*syn_resources;   
   	int                  	num_syn_resources;   
   	XmSyntheticResource 	*syn_constraint_resources;   
   	int                  	num_syn_constraint_resources;   
   	XmParentProcessProc  	parent_process;
   	XtPointer            	extension;
};

+TYPEDEF _XmManagerClassPart XmManagerClassPart;

+FIELD (struct) _XmManagerClassRec := {

    	CoreClassPart       	core_class;
    	CompositeClassPart  	composite_class;
    	ConstraintClassPart 	constraint_class;
    	XmManagerClassPart  	manager_class;
};

+TYPEDEF _XmManagerClassRec XmManagerClassRec;

+EXP lvalue XmManagerClassRec xmManagerClassRec;

+FIELD ( struct ) _XmManagerPart := {

   	Pixel   	foreground;

   	Dimension   	shadow_thickness;
   	Pixel   	top_shadow_color;
   	Pixmap  	top_shadow_pixmap;
   	Pixel   	bottom_shadow_color;
   	Pixmap  	bottom_shadow_pixmap;

   	Pixel   	highlight_color;
   	Pixmap  	highlight_pixmap;

   	XtCallbackList 	help_callback;
   	XtPointer      	user_data;

   	Boolean 	traversal_on;
   	unsigned char 	unit_type;
   	XmNavigationType navigation_type;
   
   	Boolean 	event_handler_added;
   	Widget  	active_child;
   	Widget  	highlighted_widget;
   	Widget  	accelerator_widget;

   	Boolean 	has_focus;

   	XmStringDirection string_direction;

   	XmKeyboardData 	* keyboard_list;
   	short 		num_keyboard_entries;
   	short 		size_keyboard_list;

   	XmGadget 	selected_gadget;
   	XmGadget 	eligible_for_multi_button_event;

   	GC      	background_GC;
   	GC      	highlight_GC;
   	GC      	top_shadow_GC;
   	GC      	bottom_shadow_GC;

   	Widget  	initial_focus;
};

+TYPEDEF _XmManagerPart XmManagerPart;

+FIELD (struct)  _XmManagerRec := {

   	CorePart       core;
   	CompositePart  composite;
   	ConstraintPart constraint;
   	XmManagerPart  manager;
};

+TYPEDEF _XmManagerRec XmManagerRec;

+FIELD (struct) _XmManagerConstraintPart := {

   	int 		unused;
};

+TYPEDEF _XmManagerConstraintPart XmManagerConstraintPart;

+FIELD (struct) _XmManagerConstraintRec := {
   
	XmManagerConstraintPart manager;
};

+TYPEDEF _XmManagerConstraintRec XmManagerConstraintRec;

+TYPEDEF XmManagerConstraintRec * XmManagerConstraintPtr;

+MACRO GC XmParentTopShadowGC(Widget);
+MACRO GC XmParentBottomShadowGC(Widget);
+MACRO GC XmParentHighlightGC(Widget);
+MACRO GC XmParentBackgroundGC(Widget);
+MACRO XmKeyboardData * MGR_KeyboardList(Widget);
+MACRO short MGR_NumKeyboardEntries(Widget);
+MACRO short MGR_SizeKeyboardList(Widget);
+MACRO Dimension MGR_ShadowThickness(Widget);

+FUNC void _XmGadgetTraversePrevTabGroup(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseNextTabGroup(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseLeft(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseRight(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseUp(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseDown(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseNext(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraversePrev(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetTraverseHome(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetSelect(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmManagerParentActivate(Widget mw, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmManagerParentCancel(Widget mw, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetButtonMotion(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetKeyInput(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetArm(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetDrag(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetActivate(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmManagerHelp(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetMultiArm(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmGadgetMultiActivate(Widget wid, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC void _XmSocorro(Widget w, XEvent *event, String *params, Cardinal *num_params) ;
+FUNC Boolean _XmParentProcess(Widget widget, XmParentProcessData data) ; 
+FUNC void _XmClearShadowType(Widget w, Dimension old_width, Dimension old_height, Dimension old_shadow_thickness, Dimension old_highlight_thickness) ;
+FUNC void _XmDestroyParentCallback(Widget w, XtPointer client_data, XtPointer call_data) ;


