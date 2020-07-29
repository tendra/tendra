# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


/*
 *	Allow subclassing of bulletin boards.  Probably not complete.
 */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/BulletinB.h.ts";
+USE "motif/1_2", "Xm/ManagerP.h.ts" ;

+CONST char *XmDIALOG_SUFFIX;
+CONST int XmDIALOG_SUFFIX_SIZE;

+FIELD ( struct ) XmBulletinBoardClassPart := {
	Boolean			always_install_accelerators;
	XmGeoCreateProc         geo_matrix_create ;
	XmFocusMovedProc	focus_moved_proc ;
	XtPointer		extension;
};

+FIELD (struct) _XmBulletinBoardClassRec := {
	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ConstraintClassPart		constraint_class;
	XmManagerClassPart		manager_class;
	XmBulletinBoardClassPart	bulletin_board_class;
};

+TYPEDEF _XmBulletinBoardClassRec XmBulletinBoardClassRec;

+EXP lvalue XmBulletinBoardClassRec xmBulletinBoardClassRec;

+FIELD ( struct ) XmBulletinBoardPart := {
	Dimension	margin_width;
	Dimension	margin_height;

	Widget		default_button;
	Widget		dynamic_default_button;
	Widget		cancel_button;
	Widget		dynamic_cancel_button;

	XtCallbackList	focus_callback;
	XtCallbackList	map_callback;
	XtCallbackList	unmap_callback;

	XtTranslations	text_translations;

	XmFontList	button_font_list;
	XmFontList	label_font_list;
	XmFontList	text_font_list;

	Boolean		allow_overlap;
	Boolean		default_position;
	Boolean		auto_unmanage;
	unsigned char	resize_policy;

	Dimension	old_width;
	Dimension	old_height;
	Dimension	old_shadow_thickness;
	unsigned char	shadow_type;

	Boolean		in_set_values;
	Boolean		initial_focus ;

	Boolean		no_resize;
	unsigned char	dialog_style;
	XmString	dialog_title;
	Widget		shell;
	Widget		_UNUSED;

	XmGeoMatrix     geo_cache ;
};

+TYPEDEF _XmBulletinBoardRec XmBulletinBoardRec;

+FIELD (struct) _XmBulletinBoardRec := {
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmBulletinBoardPart	bulletin_board;
};

+MACRO Widget BB_CancelButton(Widget);
+MACRO Widget BB_DynamicCancelButton(Widget);
+MACRO Widget BB_DefaultButton(Widget);
+MACRO Widget BB_DynamicDefaultButton(Widget);
+MACRO Dimension BB_MarginHeight(Widget);
+MACRO Dimension BB_MarginWidth(Widget);
+MACRO XmFontList BB_ButtonFontList(Widget);
+MACRO XmFontList BB_LabelFontList(Widget);
+MACRO XmFontList BB_TextFontList(Widget);
+MACRO int BB_StringDirection(Widget);
+MACRO unsigned char BB_ResizePolicy(Widget);
+MACRO Boolean BB_InSetValues(Widget);
+MACRO Boolean BB_InitialFocus(Widget);


+FUNC Widget _XmBB_CreateButtonG(Widget bb, XmString l_string, char *name) ;
+FUNC Widget _XmBB_CreateLabelG(Widget bb, XmString l_string, char *name) ;

+FUNC void _XmBulletinBoardSizeUpdate(Widget wid) ;
+FUNC void _XmBulletinBoardFocusMoved(Widget wid, XtPointer client_data, XtPointer data) ;
+FUNC void _XmBulletinBoardReturn(Widget wid, XEvent *event, String *params, Cardinal *numParams) ;
+FUNC void _XmBulletinBoardCancel(Widget wid, XEvent *event, String *params, Cardinal *numParams) ;
+FUNC void _XmBulletinBoardMap(Widget wid, XEvent *event, String *params, Cardinal *numParams) ;
+FUNC void _XmBulletinBoardSetDefaultShadow(Widget button) ;
+FUNC void _XmBulletinBoardSetDynDefaultButton(Widget wid, Widget newDefaultButton) ;
+FUNC void _XmBBUpdateDynDefaultButton(Widget bb) ;

