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

+USE "motif/1_2", "Xm/PrimitiveP.h.ts";
+USE "motif/1_2", "Xm/TextF.h.ts";

+CONST int IBEAM_WIDTH;
+CONST int CARET_WIDTH;
+CONST int CARET_HEIGHT;

+FIELD (struct) _XmTextFieldClassPart := { 

	XtPointer	extension;
};

+TYPEDEF _XmTextFieldClassPart XmTextFieldClassPart;

+FIELD (struct) _XmTextFieldClassRec := { 

	CoreClassPart		core_class;
	XmPrimitiveClassPart	primitive_class;
	XmTextFieldClassPart	text_class;
};

+TYPEDEF _XmTextFieldClassRec XmTextFieldClassRec;

+EXP lvalue XmTextFieldClassRec xmTextFieldClassRec;

+FIELD (struct) _XmTextFieldPart := { 

	XtCallbackList		activate_callback;
	XtCallbackList		focus_callback;
	XtCallbackList		losing_focus_callback;
	XtCallbackList		modify_verify_callback;
	XtCallbackList		wcs_modify_verify_callback;
	XtCallbackList		motion_verify_callback;
	XtCallbackList		gain_primary_callback;
	XtCallbackList		lose_primary_callback;
	XtCallbackList		value_changed_callback;

	char			*value;
	wchar_t			*wc_value;

	XmFontList		font_list;
	XFontStruct		*font;
	XmTextScanType		*selection_array;

	_XmHighlightData	highlight;

	GC			gc;
	GC			image_gc;
	GC			save_gc;

	Pixmap			ibeam_off;
	Pixmap			add_mode_cursor;
	Pixmap			cursor;
	Pixmap			putback;
	Pixmap			stipple_tile;
	Pixmap			image_clip;

	XmTextPosition		cursor_position;
	XmTextPosition		new_h_offset;
	XmTextPosition		h_offset;
	XmTextPosition		orig_left;
	XmTextPosition		orig_right;
	XmTextPosition		prim_pos_left;
	XmTextPosition		prim_pos_right;
	XmTextPosition		prim_anchor;

	XmTextPosition		sec_pos_left;
	XmTextPosition		sec_pos_right;
	XmTextPosition		sec_anchor;

	XmTextPosition		stuff_pos;

	Position		select_pos_x;

	Time			prim_time;
	Time			dest_time;
	Time			sec_time;
	Time			last_time;

	XtIntervalId		timer_id;
	XtIntervalId		select_id;

	int			blink_rate;
	int			selection_array_count;
	int			threshold;
	int			size_allocd;
	int			string_length;
	int			cursor_height;
	int			cursor_width;
	int			sarray_index;
	int			max_length;
	int			max_char_size;
	short			columns;

	Dimension		margin_width;
	Dimension		margin_height;
	Dimension		average_char_width;
	Dimension		margin_top;
	Dimension		margin_bottom;
	Dimension		font_ascent;
	Dimension		font_descent;

	Boolean 		resize_width;
    	Boolean			pending_delete;
	Boolean			editable;
	Boolean			verify_bell;

	Boolean 		cursor_position_visible;
	Boolean 		traversed;
	Boolean 		add_mode;
	Boolean			has_focus;
	Boolean 		blink_on;
	short			cursor_on;
	Boolean 		refresh_ibeam_off;
	Boolean 		have_inverted_image_gc;
	Boolean 		has_primary;
	Boolean 		has_secondary;
	Boolean 		has_destination;
	Boolean 		sec_drag;
	Boolean			selection_move;
	Boolean			pending_off;
	Boolean			fontlist_created;
	Boolean			has_rect;
	Boolean			do_drop;
	Boolean 		cancel;
	Boolean			extending;
	Boolean			sec_extending;
	Boolean			changed_visible;
	Boolean			have_fontset;
	Boolean			in_setvalues;
	Boolean			do_resize;
	Boolean			redisplay;
	Boolean			overstrike;
	Boolean 		sel_start;
	XtPointer		extension;
};

+TYPEDEF _XmTextFieldPart XmTextFieldPart;

+FIELD (struct) _XmTextFieldRec := { 

	CorePart		core;
	XmPrimitivePart		primitive;
	XmTextFieldPart		text;
};

+TYPEDEF _XmTextFieldRec XmTextFieldRec;


+MACRO XtCallbackList TextF_ActivateCallback(Widget);
+MACRO XtCallbackList TextF_LosingFocusCallback(Widget);
+MACRO XtCallbackList TextF_FocusCallback(Widget);
+MACRO XtCallbackList TextF_ModifyVerifyCallback(Widget);
+MACRO XtCallbackList TextF_ModifyVerifyCallbackWcs(Widget);
+MACRO XtCallbackList TextF_MotionVerifyCallback(Widget);
+MACRO XtCallbackList TextF_ValueChangedCallback(Widget);
+MACRO String TextF_Value(Widget);
+MACRO wchar_t * TextF_WcValue(Widget);
+MACRO Dimension TextF_MarginHeight(Widget);
+MACRO Dimension TextF_MarginWidth(Widget);
+MACRO XmTextPosition TextF_CursorPosition(Widget);
+MACRO short TextF_Columns(Widget);
+MACRO int TextF_MaxLength(Widget);
+MACRO int TextF_BlinkRate(Widget);
+MACRO XmFontList TextF_FontList(Widget);
+MACRO XFontStruct * TextF_Font(Widget);
+MACRO Dimension TextF_FontAscent(Widget);
+MACRO Dimension TextF_FontDescent(Widget);
+MACRO XmTextScanType *TextF_SelectionArray(Widget);
+MACRO int TextF_SelectionArrayCount(Widget);
+MACRO Boolean TextF_ResizeWidth(Widget);
+MACRO Boolean TextF_PendingDelete(Widget);
+MACRO Boolean TextF_Editable(Widget);
+MACRO Boolean TextF_CursorPositionVisible(Widget);
+MACRO int TextF_Threshold(Widget);
+MACRO Boolean TextF_UseFontSet(Widget);

+FUNC int _XmTextFieldCountBytes(XmTextFieldWidget, wchar_t *, int);
+FUNC Widget _XmTextFieldGetDropReciever(Widget);
+FUNC void _XmTextFToggleCursorGC(Widget);
+FUNC void _XmTextFieldDrawInsertionPoint(XmTextFieldWidget, Boolean);
+FUNC void _XmTextFieldSetCursorPosition(XmTextFieldWidget, XEvent *, XmTextPosition, Boolean, Boolean);
+FUNC Boolean _XmTextFieldReplaceText(XmTextFieldWidget, XEvent *, XmTextPosition, XmTextPosition, char *, int, Boolean);
+FUNC void _XmTextFieldDeselectSelection(Widget, Boolean, Time);
+FUNC Boolean _XmTextFieldSetDestination(Widget, XmTextPosition, Time);
+FUNC void _XmTextFieldStartSelection(XmTextFieldWidget, XmTextPosition, XmTextPosition, Time);
+FUNC void _XmTextFieldSetSel2(Widget, XmTextPosition, XmTextPosition, Boolean, Time);
 	
	



