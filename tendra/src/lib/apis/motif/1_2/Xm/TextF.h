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


/* SCO CID (IXI) TextF.h,v 1.1 1996/08/08 14:13:37 wendland Exp */

+USE "motif/1_2","Xm/Xm.h";


+TYPE (struct) _XmTextFieldClassRec;
+TYPE (struct) _XmTextFieldRec;
+TYPEDEF _XmTextFieldClassRec *XmTextFieldWidgetClass;
+TYPEDEF _XmTextFieldRec *XmTextFieldWidget;

+EXP lvalue WidgetClass xmTextFieldWidgetClass;


+FUNC char *XmTextFieldGetString (Widget widget);
+FUNC XmTextPosition XmTextFieldGetLastPosition (Widget widget);
+FUNC void XmTextFieldSetString (Widget widget, char *value);
+FUNC void XmTextFieldReplace (Widget widget, XmTextPosition from_pos, XmTextPosition to_pos, char *value);
+FUNC void XmTextFieldInsert (Widget widget, XmTextPosition position, char *value);
+FUNC void XmTextFieldSetAddMode (Widget widget,Boolean state);
+FUNC Boolean XmTextFieldGetAddMode (Widget widget);
+FUNC Boolean XmTextFieldGetEditable (Widget widget);
+FUNC void XmTextFieldSetEditable (Widget widget,Boolean editable);
+FUNC int XmTextFieldGetMaxLength (Widget widget);
+FUNC void XmTextFieldSetMaxLength (Widget widget, int max_length);
+FUNC XmTextPosition XmTextFieldGetCursorPosition (Widget widget);
+FUNC void XmTextFieldSetCursorPosition (Widget widget, XmTextPosition position);
+FUNC XmTextPosition XmTextFieldGetInsertionPosition (Widget widget);
+FUNC void XmTextFieldSetInsertionPosition (Widget widget, XmTextPosition position);
+FUNC Boolean XmTextFieldGetSelectionPosition (Widget widget, XmTextPosition *left, XmTextPosition *right);
+FUNC char *XmTextFieldGetSelection (Widget widget);
+FUNC Boolean XmTextFieldRemove (Widget widget);
+FUNC Boolean XmTextFieldCopy (Widget widget, Time clip_time);
+FUNC Boolean XmTextFieldCut (Widget widget, Time clip_time);
+FUNC Boolean XmTextFieldPaste (Widget widget);
+FUNC void XmTextFieldClearSelection (Widget widget, Time sel_time);
+FUNC void XmTextFieldSetSelection (Widget widget, XmTextPosition first, XmTextPosition last, Time sel_time);
+FUNC XmTextPosition XmTextFieldXYToPos (Widget widget,Position x, Position y);
+FUNC Boolean XmTextFieldPosToXY (Widget widget, XmTextPosition position, Position *x, Position *y);
+FUNC void XmTextFieldShowPosition (Widget widget, XmTextPosition position);
+FUNC void XmTextFieldSetHighlight (Widget widget, XmTextPosition left, XmTextPosition right, XmHighlightMode mode);
+FUNC int XmTextFieldGetBaseline (Widget widget);
+FUNC Widget XmCreateTextField (Widget parent, char *name, ArgList arglist, Cardinal argcount);
+FUNC wchar_t *XmTextFieldGetSelectionWcs(Widget widget);
+FUNC wchar_t *XmTextFieldGetStringWcs(Widget widget);
+FUNC int XmTextFieldGetSubstring(Widget widget, XmTextPosition start, int num_chars, int buffer_size, char *buffer);
+FUNC int XmTextFieldGetSubstringWcs(Widget widget, XmTextPosition start, int num_chars, int buffer_size, wchar_t *buffer);
+FUNC void XmTextFieldInsertWcs(Widget widget, XmTextPosition position, wchar_t *wcstring);
+FUNC void XmTextFieldReplaceWcs(Widget widget, XmTextPosition from_pos, XmTextPosition to_pos, wchar_t *wcstring);
+FUNC void XmTextFieldSetStringWcs(Widget widget, wchar_t *wcstring);

