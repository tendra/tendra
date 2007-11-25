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



/* SCO CID (IXI) TextP.h,v 1.1 1996/08/08 14:13:43 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/PrimitiveP.h";
+USE "motif/1_2", "Xm/TextOutP.h";
+USE "motif/1_2", "Xm/TextInP.h";


+TYPE struct _InputRec;
+TYPE struct _OutputRec;
+TYPEDEF _InputRec *Input;
+TYPEDEF _OutputRec *Output;

+CONST String TEXTWIDGETCLASS;

+MACRO XmTextSource GetSrc(Widget);

+IFNDEF MIN
+DEFINE MIN(x,y) %% ((x) < (y) ? (x) : (y)) %% ;
+ENDIF

+FIELD (struct) XmTextClassPart := { 

	XtPointer		extension;
};


+FIELD (struct) _XmTextClassRec := { 

	CoreClassPart		core_class;
	XmPrimitiveClassPart	primitive_class;
	XmTextClassPart		text_class;
};

+TYPEDEF _XmTextClassRec XmTextClassRec;

+EXP lvalue XmTextClassRec xmTextClassRec;

+FIELD (struct) LineRec := {

	XmTextPosition		start;
	Boolean			changed;
	XmTextPosition		changed_position;
	Boolean			past_end;
	LineTableExtra		extra;
};

+TYPEDEF LineRec *Line;

+FIELD (struct) _XmTextLineTableRec := { 

	unsigned int		start_pos;
	unsigned int		virt_line;
};

+TYPEDEF _XmTextLineTableRec XmTextLineTableRec;
+TYPEDEF _XmTextLineTableRec *XmTextLineTable;

+FIELD (struct) RangeRec := { 

	XmTextPosition		from;
	XmTextPosition		to;
};


+FIELD (struct) Ranges := { 

	Cardinal		number;
	Cardinal		maximum;
	RangeRec		*range;
};


+FIELD (struct) _XmTextPart := { 

	XmTextSource		source;
	XtCallbackList		activate_callback;
	XtCallbackList		focus_callback;
	XtCallbackList		losing_focus_callback;
	XtCallbackList		value_changed_callback;
	XtCallbackList		modify_verify_callback;
	XtCallbackList		wcs_modify_verify_callback;
	XtCallbackList		motion_verify_callback;
	XtCallbackList		gain_primary_callback;
	XtCallbackList		lose_primary_callback;

	char			*value;
	wchar_t			*wc_value;

	Dimension		margin_height;
	Dimension		margin_width;
	Position		cursor_position_x;
	OutputCreateProc	output_create;
	InputCreateProc		input_create;

	XmTextPosition		top_character;
	XmTextPosition		bottom_position;
	XmTextPosition		cursor_position;
	int			max_length;
	int			edit_mode;

	Boolean			auto_show_cursor_position;
	Boolean			editable;
	Boolean			verify_bell;

	Boolean			add_mode;
	Boolean			traversed;

	Boolean			in_redisplay;
	Boolean			needs_redisplay;
	Boolean			in_refigure_lines;
	Boolean			needs_refigure_lines;
	Boolean 		in_setvalues;
	Boolean			in_resize;
	Boolean			in_expose;
	Boolean			highlight_changed;
	Boolean			pendingoff;
	char			char_size;
	
	OnOrOff			on_or_off;

	Output			output;
	Input			input;

	XmTextPosition		first_position;
	XmTextPosition		last_position;
	XmTextPosition		forget_past;
	XmTextPosition		force_display;
	XmTextPosition		new_top;
	XmTextPosition		last_top_char;
	XmTextPosition		dest_position;
	int			disable_depth;

	int			pending_scroll;
	int			total_lines;
	int			top_line;
	int			vsbar_scrolling;
	
	Cardinal		number_lines;
	Cardinal		maximum_lines;
	Line			line;

	Ranges			repaint;
	_XmHighlightData	highlight;
	_XmHighlightData	old_highlight;
	Widget			inner_widget;

	XmTextLineTable		line_table;
	unsigned int		table_size;
	unsigned int		table_index;
};

+TYPEDEF _XmTextPart XmTextPart;

+FIELD (struct) _XmTextRec := { 

	CorePart		core;
	XmPrimitivePart		primitive;
	XmTextPart		text;
};

+TYPEDEF _XmTextRec XmTextRec;

+FUNC XmTextPosition _XmTextFindScroll(XmTextWidget, XmTextPosition, int);
+FUNC int _XmTextGetTotalLines(Widget);
+FUNC XmTextLineTable _XmTextGetLineTable(Widget, int *);
+FUNC void _XmTextRealignLineTable(XmTextWidget, XmTextLineTable *, int *, unsigned int, XmTextPosition, XmTextPosition);

+FUNC unsigned int _XmTextGetTableIndex(XmTextWidget, XmTextPosition);
+FUNC void _XmTextUpdateLineTable(Widget, XmTextPosition, XmTextPosition, XmTextBlock, Boolean);
+FUNC void _XmTextMarkRedraw(XmTextWidget, XmTextPosition, XmTextPosition);
+FUNC LineNum _XmTextNumLines(XmTextWidget);
+FUNC void _XmTextLineInfo(XmTextWidget, LineNum, XmTextPosition *, LineTableExtra *);
+FUNC LineNum _XmTextPosToLine(XmTextWidget, XmTextPosition);
+FUNC void _XmTextInvalidate(XmTextWidget, XmTextPosition, XmTextPosition, long);
+FUNC void _XmTextSetTopCharacter(Widget, XmTextPosition);
+FUNC int _XmTextCountCharacters(char *, int);
+FUNC void _XmTextSetCursorPosition(Widget, XmTextPosition);
+FUNC void _XmTextDisableRedisplay(XmTextWidget, Boolean);
+FUNC void _XmTextEnableRedisplay(XmTextWidget);



