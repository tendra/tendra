/*
    COPYRIGHT NOTICE

    This program is the proprietary property of the Secretary of State
    for Defence (United Kingdom) acting through the Defence Research
    Agency (DRA).  Use, reproduction, production of amended versions
    and/or transfer of this program is permitted PROVIDED THAT:

    (a)	 This legend be preserved on any such reproduction and amended
	 version.

    (b)	 Any amended version of this program be clearly marked to show
	 the nature of the amendment and the name of the amending
	 organisation.

    (c)	 Any recipient of such reproduction or amended version accept
	 the conditions set out in this legend.

    The DRA accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Crown Copyright (c) 1994.
*/

/*
    COPYRIGHT NOTICE

    This program contains amendments to Motif 1.1 API headers in
    order to represent the Motif 1.2 API. These amendments are the
    property of IXI Ltd, a subsidiary of the Santa Cruz Operation (SCO).
    Use, reproduction, production of amended versions and/or transfer of
    this program is permitted PROVIDED THAT:

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


/* SCO CID (IXI) Text.h,v 1.1 1996/08/08 14:13:36 wendland Exp */

+USE "motif/1_2","Xm/Xm.h";
+USE "ansi", "stdio.h"; 

+TYPE (struct) _XmTextSourceRec;
+TYPE (struct) _XmTextClassRec;
+TYPE (struct) _XmTextRec;
+TYPEDEF _XmTextSourceRec *XmTextSource;
+TYPEDEF _XmTextClassRec *XmTextWidgetClass;
+TYPEDEF _XmTextRec *XmTextWidget;

+EXP lvalue WidgetClass xmTextWidgetClass;

+FUNC void XmTextSetHighlight (Widget w, XmTextPosition left, XmTextPosition right, XmHighlightMode mode);
+FUNC Widget XmCreateScrolledText (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateText (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC char *XmTextGetString (Widget widget);
+FUNC XmTextPosition XmTextGetLastPosition (Widget widget);
+FUNC void XmTextSetString (Widget widget, char *value);
+FUNC void XmTextReplace (Widget widget, XmTextPosition frompos, XmTextPosition topos, char *value);
+FUNC void XmTextInsert (Widget widget, XmTextPosition position, char *value);
+FUNC void XmTextSetAddMode (Widget widget,Boolean state);
+FUNC Boolean XmTextGetAddMode (Widget widget);
+FUNC Boolean XmTextGetEditable (Widget widget);
+FUNC void XmTextSetEditable (Widget widget,Boolean editable);
+FUNC int XmTextGetMaxLength (Widget widget);
+FUNC void XmTextSetMaxLength (Widget widget, int max_length);
+FUNC XmTextPosition XmTextGetTopCharacter (Widget widget);
+FUNC void XmTextSetTopCharacter (Widget widget, XmTextPosition top_character);
+FUNC XmTextPosition XmTextGetCursorPosition (Widget widget);
+FUNC void XmTextSetCursorPosition (Widget widget, XmTextPosition position);
+FUNC XmTextPosition XmTextGetInsertionPosition (Widget widget);
+FUNC void XmTextSetInsertionPosition (Widget widget, XmTextPosition position);
+FUNC Boolean XmTextRemove (Widget widget);
+FUNC Boolean XmTextCopy (Widget widget, Time copy_time);
+FUNC Boolean XmTextCut (Widget widget, Time cut_time);
+FUNC Boolean XmTextPaste (Widget widget);
+FUNC char *XmTextGetSelection (Widget widget);
+FUNC void XmTextSetSelection (Widget widget, XmTextPosition first, XmTextPosition last, Time set_time);
+FUNC void XmTextClearSelection (Widget widget, Time clear_time);
+FUNC Boolean XmTextGetSelectionPosition (Widget widget, XmTextPosition *left, XmTextPosition *right);
+FUNC XmTextPosition XmTextXYToPos (Widget widget,Position x, Position y);
+FUNC Boolean XmTextPosToXY (Widget widget, XmTextPosition position, Position *x, Position *y);
+FUNC XmTextSource XmTextGetSource (Widget widget);
+FUNC void XmTextSetSource (Widget widget, XmTextSource source, XmTextPosition top_character, XmTextPosition cursor_position);
+FUNC void XmTextShowPosition (Widget widget, XmTextPosition position);
+FUNC void XmTextScroll (Widget widget, int n);
+FUNC int XmTextGetBaseLine (Widget widget);
+FUNC void XmTextDisableRedisplay(Widget widget);
+FUNC void XmTextEnableRedisplay(Widget widget);
+FUNC Boolean XmTextFindString(Widget widget, XmTextPosition start, char *string, XmTextDirection direction, XmTextPosition *position);
+FUNC Boolean XmTextFindStringWcs(Widget widget, XmTextPosition start, wchar_t *wcstring, XmTextDirection direction, XmTextPosition *position);
+FUNC wchar_t *XmTextGetSelectionWcs(Widget widget);
+FUNC wchar_t *XmTextGetStringWcs(Widget widget);
+FUNC int XmTextGetSubstring(Widget widget, XmTextPosition start, int num_chars, int buffer_size, char *buffer);
+FUNC int XmTextGetSubstringWcs(Widget widget, XmTextPosition start, int num_chars, int buffer_size, wchar_t *buffer);
+FUNC void XmTextInsertWcs(Widget widget, XmTextPosition position, wchar_t *wcstring);
+FUNC void XmTextReplaceWcs(Widget widget, XmTextPosition from_pos, XmTextPosition to_pos, wchar_t *wcstring);
+FUNC void XmTextSetStringWcs(Widget widget, wchar_t *wcstring);
