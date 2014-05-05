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

+USE "motif/1_2", "Xm/BulletinBP.h.ts";
+USE "motif/1_2", "Xm/SelectioB.h.ts";

+CONST int XmSB_MAX_WIDGETS_VERT;

+FIELD (struct) _XmSelectionBoxConstraintPart := {

	char		unused;
};

+TYPEDEF _XmSelectionBoxConstraintPart XmSelectionBoxConstraintPart;
+TYPEDEF _XmSelectionBoxConstraintPart * XmSelectionBoxConstraint;

+FIELD (struct) XmSelectionBoxClassPart := {

	XtCallbackProc	list_callback;
	XtPointer	extension;
};

+FIELD (struct) _XmSelectionBoxClassRec := {

	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ConstraintClassPart		constraint_class;
	XmManagerClassPart		manager_class;
	XmBulletinBoardClassPart	bulletin_board_class;
	XmSelectionBoxClassPart		selection_box_class;
};

+TYPEDEF _XmSelectionBoxClassRec XmSelectionBoxClassRec;

+EXP lvalue XmSelectionBoxClassRec xmSelectionBoxClassRec;

+FIELD (struct) XmSelectionBoxPart := { 

	Widget		list_label;
	XmString	list_label_string;

	Widget		list;
	XmString	*list_items;
	int		list_item_count;
	int		list_visible_item_count;
	int		list_selected_item_position;
	
	Widget		selection_label;
	XmString	selection_label_string;

	Widget		text;
	XmString	text_string;
	short		text_columns;

	Widget		work_area;
	
	Widget		separator;

	Widget		ok_button;
	XmString	ok_label_string;

	Widget		apply_button;
	XmString	apply_label_string;
	
	XmString	cancel_label_string;

	Widget		help_button;
	XmString	help_label_string;

	XtCallbackList	ok_callback;
	XtCallbackList	apply_callback;
	XtCallbackList	cancel_callback;
	XtCallbackList	no_match_callback;

	XtAccelerators	text_accelerators;

	Boolean		must_match;
	Boolean		adding_sel_widgets;
	Boolean		minimize_buttons;

	unsigned char	dialog_type;

	unsigned char	child_placement;
};

+FIELD (struct) _XmSelectionBoxRec := { 

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmBulletinBoardPart	bulletin_board;
	XmSelectionBoxPart	selection_box;
};

+TYPEDEF _XmSelectionBoxRec XmSelectionBoxRec;

+MACRO Widget SB_ListLabel(Widget);
+MACRO Widget SB_List(Widget);
+MACRO Widget SB_SelectionLabel(Widget);
+MACRO Widget SB_Text(Widget);
+MACRO Widget SB_WorkArea(Widget);
+MACRO Widget SB_Separator(Widget);
+MACRO Widget SB_OkButton(Widget);
+MACRO Widget SB_ApplyButton(Widget);
+MACRO Widget SB_CancelButton(Widget);
+MACRO Widget SB_HelpButton(Widget);
+MACRO Widget SB_DefaultButton(Widget);
+MACRO Dimension SB_MarginHeight(Widget);
+MACRO Dimension SB_MarginWidth(Widget);
+MACRO XmFontList SB_ButtonFontList(Widget);
+MACRO XmFontList SB_LabelFontList(Widget);
+MACRO XmFontList SB_TextFontList(Widget);
+MACRO XmStringDirection SB_StringDirection(Widget);
+MACRO Boolean SB_AddingSelWidgets(Widget);
+MACRO XtAccelerators SB_TextAccelerators(Widget);
+MACRO int SB_ListItemCount(Widget);
+MACRO int SB_ListSelectedItemPosition(Widget);
+MACRO int SB_ListVisibleItemCount(Widget);
+MACRO int SB_TextColumns(Widget);
+MACRO Boolean SB_MinimizeButtons(Widget);
+MACRO Boolean SB_MustMatch(Widget);

+FUNC void _XmSelectionBoxCreateListLabel(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateSelectionLabel(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateList(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateText(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateSeparator(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateOkButton(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateApplyButton(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateCancelButton(XmSelectionBoxWidget);
+FUNC void _XmSelectionBoxCreateHelpButton(XmSelectionBoxWidget);
+FUNC XmGeoMatrix _XmSelectionBoxGeoMatrixCreate(Widget, Widget, XtWidgetGeometry *); 
+FUNC Boolean _XmSelectionBoxNoGeoRequest(XmGeoMatrix);
+FUNC void _XmSelectionBoxGetSelectionLabelString(Widget,int, XtArgVal *);
+FUNC void _XmSelectionBoxGetListLabelString(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetTextColumns(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetTextString(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetListItems(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetListItemCount(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetListVisibleItemCount(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetOkLabelString(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetApplyLabelString(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetCancelLabelString(Widget, int, XtArgVal *);
+FUNC void _XmSelectionBoxGetHelpLabelString(Widget, int,XtArgVal *);
+FUNC void _XmSelectionBoxUpOrDown(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmSelectionBoxRestore(Widget, XEvent *, String *, Cardinal *);



