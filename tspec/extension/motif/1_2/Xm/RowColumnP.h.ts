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

+USE "motif/1_2", "Xm/RowColumn.h.ts";
+USE "motif/1_2", "Xm/ManagerP.h.ts";

+FIELD (struct) _XmButtonEventStatusRec := { 

	Time		time;
	Boolean		verified;
	Boolean		waiting_to_be_managed;
	XButtonEvent	event;
};

+TYPEDEF _XmButtonEventStatusRec XmButtonEventStatusRec;

+FIELD (struct) _XmReplayInfoRec := {

	Time		time;
	Widget		toplevel_menu;
};

+TYPEDEF _XmReplayInfoRec XmReplayInfoRec;

+FIELD (struct) _XmMenuFocusRec := { 

	Widget		oldWidget;
	Window		oldFocus;
	int		oldRevert;
};

+TYPEDEF _XmMenuFocusRec XmMenuFocusRec;

+FIELD (struct) _XmMenuStateRec := { 

	Widget			RC_LastSelectToplevel;
	XmButtonEventStatusRec	RC_ButtonEventStatus;
	XmReplayInfoRec		RC_ReplayInfo;

	Widget			RC_activeItem;
	XmMenuFocusRec		RC_menuFocus;

	Boolean			RC_allowAcceleratedInsensitiveUnmanagedMenuItems;
	Time			MS_LastManagedMenuTime;
	Boolean			MU_InDragMode;
	Widget			MU_CurrentMenuChild;
	Boolean			MU_InPMMode;
};

+TYPEDEF _XmMenuStateRec XmMenuStateRec;
+TYPEDEF _XmMenuStateRec *XmMenuState;

+FIELD (struct) _XmRCKidGeometryRec := { 

	Widget			kid;
	XtWidgetGeometry	box;
	Dimension		margin_top;
	Dimension		margin_bottom;
	Dimension		baseline;
};

+TYPEDEF _XmRCKidGeometryRec XmRCKidGeometryRec;
+TYPEDEF _XmRCKidGeometryRec *XmRCKidGeometry;

+FIELD (struct) _XmRowColumnPart := { 

	Dimension		margin_height;
	Dimension		margin_width;
	
	Dimension		spacing;
	Dimension		entry_border;
	
	Widget			help_pushbutton;
	Widget			cascadeBtn;

	XmString		option_label;

	Widget			option_submenu;

	XmRCKidGeometry		boxes;

	WidgetClass		entry_class;
	
	XtCallbackList		entry_callback;
	XtCallbackList		map_callback;
	XtCallbackList		unmap_callback;

	Widget			memory_subwidget;

	short			num_columns;

	String			menuPost;
	unsigned int		postButton;
	int			postEventType;
	unsigned int		postModifiers;

	String			menu_accelerator;
	KeySym			mnemonic;
	XmStringCharSet		mnemonicCharSet;

	unsigned char		entry_alignment;

	unsigned char		packing;
	unsigned char		type;
	unsigned char		orientation;

	Boolean			armed;

	Boolean			adjust_margin;

	Boolean			adjust_last;

	Boolean			do_alignment;
	Boolean			radio;
	Boolean			radio_one;
	Boolean			homogeneous;

	Boolean			resize_width;
	Boolean			resize_height;

	Boolean			popup_enabled;

	Dimension		old_width;
	Dimension		old_height;
	Dimension		old_shadow_thickness;

	Widget			* postFromList;
	int			postFromCount;
	int			postFromListSizel;

	Widget			lastSelectToplevel;
	Widget			popupPosted;

	unsigned char		oldFocusPolicy;
	XmButtonEventStatusRec	button_status;


	unsigned char		TearOffModel;
	Widget			ParentShell;
	Widget			tear_off_control;
	Boolean			to_state;
	XtCallbackList		tear_off_activated_callback;
	XtCallbackList		tear_off_deactivated_callback;
	Widget			tear_off_lastSelectToplevel;
	Widget			tear_off_focus_item;

	unsigned char		entry_vertical_alignment;
	unsigned char		popup_menu_click;
	XtIntervalId		popup_timeout_timer;
};

+TYPEDEF _XmRowColumnPart XmRowColumnPart;

+FIELD (struct) _XmRowColumnRec := { 

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmRowColumnPart		row_column;
};

+TYPEDEF _XmRowColumnRec XmRowColumnRec;

/* OBSOLETE */
+FIELD (struct) XmRowColumnWidgetRec := {

        CorePart                core;
        CompositePart           composite;
        ConstraintPart          constraint;
        XmManagerPart           manager;
        XmRowColumnPart         row_column;
};

+FIELD (struct) _XmRowColumnClassPart := { 

	XmMenuProc		menuProcedures;
	XtActionProc		armAndActivate;
	XmMenuTraversalProc	traversalHandler;
	XtPointer		extension;
};

+TYPEDEF  _XmRowColumnClassPart XmRowColumnClassPart;

+FIELD (struct) _XmRowColumnClassRec := { 

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmRowColumnClassPart	row_column_class;
};

+TYPEDEF  _XmRowColumnClassRec XmRowColumnClassRec;

+EXP lvalue XmRowColumnClassRec xmRowColumnClassRec;

+FIELD (struct) _XmRowColumnConstraintPart := { 

	Boolean		was_managed;
	Dimension	margin_top;
	Dimension	margin_bottom;
	Dimension	baseline;
	short		position_index;
};

+TYPEDEF _XmRowColumnConstraintPart XmRowColumnConstraintPart;

+FIELD (struct) _XmRowColumnConstraintRec := { 

	XmManagerConstraintPart		manager;
	XmRowColumnConstraintPart	row_column;
};

+TYPEDEF _XmRowColumnConstraintRec XmRowColumnConstraintRec;

+CONST int XmRC_ARMED_BIT;
+CONST int XmRC_BEING_ARMED_BIT;
+CONST int XmRC_EXPOSE_BIT;
+CONST int XmRC_WINDOW_MOVED_BIT;
+CONST int XmRC_WIDGET_MOVED_BIT;
+CONST int XmRC_POPPING_DOWN_BIT;
+CONST int XmRC_FROM_RESIZE_BIT;

+MACRO Boolean RC_IsArmed(Widget);
+MACRO Boolean RC_BeingArmed(Widget);
+MACRO Boolean RC_DoExpose(Widget);
+MACRO Boolean RC_WidgetHasMoved(Widget);
+MACRO Boolean RC_WindowHasMoved(Widget);
+MACRO Boolean RC_PoppingDown(Widget);
+MACRO Boolean RC_FromResize(Widget);

+DEFINE RC_SetBit(byte,bit,v) %% byte = (byte & (~bit)) | (v ? bit : 0) %%;

+MACRO void RC_SetArmed(Widget,XrmQuark);
+MACRO void RC_SetBeingArmed(Widget, XrmQuark);
+MACRO void RC_SetExpose(Widget, XrmQuark);
+MACRO void RC_SetWidgetMoved(Widget, XrmQuark);
+MACRO void RC_SetWindowMoved(Widget, XrmQuark);
+MACRO void RC_SetPoppingDown(Widget, XrmQuark);
+MACRO void RC_SetFromResize(Widget, XrmQuark);

+MACRO Dimension RC_MarginW(Widget);
+MACRO Dimension RC_MarginH(Widget);
+MACRO XtCallbackList RC_Entry_cb(Widget);
+MACRO XtCallbackList RC_Map_cb(Widget);
+MACRO XtCallbackList RC_Unmap_cb(Widget);	
+MACRO unsigned char RC_Orientation(Widget);
+MACRO Dimension RC_Spacing(Widget);
+MACRO Dimension RC_EntryBorder(Widget);
+MACRO Widget RC_HelpPb(Widget);
+MACRO Boolean RC_DoMarginAdjust(Widget);
+MACRO unsigned char RC_EntryAlignment(Widget);
+MACRO unsigned char RC_EntryVerticalAlignment(Widget);
+MACRO unsigned char RC_Packing(Widget);
+MACRO short RC_NCol(Widget);
+MACRO Boolean RC_AdjLast(Widget);
+MACRO Boolean RC_AdjMargin(Widget);
+MACRO Widget RC_MemWidget(Widget);
+MACRO Widget RC_CascadeBtn(Widget);
+MACRO XmString RC_OptionLabel(Widget);
+MACRO Widget RC_OptionSubMenu(Widget);
+MACRO Boolean RC_RadioBehavior(Widget);
+MACRO Widget RC_PopupPosted(Widget);
+MACRO Boolean RC_ResizeHeight(Widget);
+MACRO Boolean RC_ResizeWidth(Widget);
+MACRO unsigned char RC_Type(Widget); 
+MACRO WidgetClass RC_EntryClass(Widget);
+MACRO Boolean RC_IsHomogeneous(Widget);
+MACRO XmRCKidGeometry RC_Boxes(Widget);
+MACRO Boolean RC_PopupEnabled(Widget);
+MACRO String RC_MenuAccelerator(Widget);
+MACRO KeySym RC_Mnemonic(Widget);
+MACRO XmStringCharSet RC_MnemonicCharSet(Widget);
+MACRO String RC_MenuPost(Widget);
+MACRO unsigned int RC_PostButton(Widget);
+MACRO unsigned int RC_PostModifiers(Widget);
+MACRO int RC_PostEventType(Widget);
+MACRO unsigned char RC_OldFocusPolicy(Widget);
+MACRO Widget RC_ParentShell(Widget);
+MACRO Widget RC_TearOffControl(Widget);
+MACRO unsigned char RC_TearOffModel(Widget);
+MACRO unsigned char RC_popupMenuClick(Widget);

+CONST int XmTO_TORN_OFF_BIT;
+CONST int XmTO_FROM_INIT_BIT;
+CONST int XmTO_VISUAL_DIRTY_BIT;
+CONST int XmTO_ACTIVE_BIT;

+MACRO void RC_SetTornOff(Widget, XrmQuark);
+MACRO Boolean RC_TornOff(Widget);
+MACRO void RC_SetFromInit(Widget, XrmQuark);
+MACRO Boolean RC_FromInit(Widget);
+MACRO void RC_SetTearOffDirty(Widget, XrmQuark);
+MACRO Boolean RC_TearOffDirty(Widget);
+MACRO Boolean RC_TearOffActive(Widget);
+MACRO void RC_SetTearOffActive(Widget, XrmQuark);

+CONST int initial_value;

+CONST int XmADD;
+CONST int XmDELETE;
+CONST int XmREPLACE;

+CONST int XmWEAK_CHECK;
+CONST int XmMEDIUM_CHECK;
+CONST int XmSTRONG_CHECK;

+CONST int XmMENU_BEGIN;
+CONST int XmMENU_MIDDLE;
+CONST int XmMENU_END;

+CONST int ANY_CHILD;
+CONST int FIRST_BUTTON;


+FUNC void _XmPostPopupMenu(Widget, XEvent *);
+FUNC void  _XmSetPopupMenuClick(Widget, Boolean);
+FUNC Boolean _XmGetPopupMenuClick(Widget);
+FUNC void _XmAllowAcceleratedInsensitiveUnmanagedMenuItems(Widget, Boolean);
+FUNC void _XmSetSwallowEventHandler(Widget, Boolean);
+FUNC void _XmMenuFocus(Widget, int, Time);
+FUNC void _XmGetActiveTopLevelMenu(Widget, Widget *);
+FUNC Boolean _XmMatchBSelectEvent(Widget, XEvent *);
+FUNC Boolean _XmMatchBDragEvent(Widget,XEvent *);
+FUNC void _XmHandleMenuButtonPress(Widget, XEvent *);
+FUNC void _XmMenuBtnDown(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmMenuBtnUp(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmCallRowColumnMapCallback(Widget, XEvent *);
+FUNC void _XmCallRowColumnUnmapCallback(Widget, XEvent *);
+FUNC void _XmMenuPopDown(Widget, XEvent *, Boolean *);
+FUNC Boolean _XmIsActiveTearOff(Widget);
+FUNC void _XmMenuHelp(Widget, XEvent *, String *, Cardinal *);

 

