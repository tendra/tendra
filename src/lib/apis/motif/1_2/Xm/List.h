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


/* SCO CID (IXI) List.h,v 1.1 1996/08/08 14:12:59 wendland Exp */

+USE "motif/1_2","Xm/Xm.h";

+EXP lvalue WidgetClass xmListWidgetClass;

+CONST int XmINITIAL;
+CONST int XmADDITION;
+CONST int XmMODIFICATION;

+TYPE (struct) _XmListClassRec;
+TYPE (struct) _XmListRec;
+TYPEDEF _XmListClassRec * XmListWidgetClass;
+TYPEDEF _XmListRec      * XmListWidget;


+FUNC void XmListAddItem (Widget widget, XmString item, int position);
+FUNC void XmListAddItemUnselected (Widget widget, XmString item, int position);
+FUNC void XmListAddItems (Widget widget, XmString *items, int item_count, int position);
+FUNC void XmListAddItemsUnselected (Widget widget, XmString *items, int item_count, int position);
+FUNC void XmListDeleteAllItems (Widget widget);
+FUNC void XmListDeleteItem (Widget widget, XmString item);
+FUNC void XmListDeleteItemsPos (Widget widget, int item_count, int position);
+FUNC void XmListDeleteItems (Widget widget, XmString *items, int item_count);
+FUNC void XmListDeletePos (Widget widget, int position);
+FUNC void XmListDeletePositions (Widget widget, int *position_list, int position_count);
+FUNC void XmListDeselectAllItems (Widget widget);
+FUNC void XmListDeselectItem (Widget widget, XmString item);
+FUNC void XmListDeselectPos (Widget widget, int position);
+FUNC int XmListGetKbdItemPos (Widget widget);
+FUNC Boolean XmListGetMatchPos (Widget widget, XmString item, int **position_list, int *position_count);
+FUNC Boolean XmListGetSelectedPos (Widget widget, int **position_list, int *position_count);
+FUNC Boolean XmListItemExists (Widget widget, XmString item);
+FUNC int XmListItemPos (Widget widget, XmString item);
+FUNC Boolean XmListPosSelected (Widget widget, int position);
+FUNC Boolean XmListPostoBounds (Widget widget, int position, Position *x, Position *y, Dimension *width, Dimension *height);
+FUNC void XmListReplaceItems (Widget widget, XmString *old_items, int item_count, XmString *new_items);
+FUNC void XmListReplaceItemsPos (Widget widget, XmString *new_items, int item_count, int position);
+FUNC void XmListReplaceItemsPosUnselected (Widget widget, XmString *new_items, int item_count, int position);
+FUNC void XmListReplaceItemsUnslected (Widget widget, XmString *old_items, int item_count, XmString *new_items);
+FUNC void XmListReplacePositions (Widget widget, int *position_list, XmString *item_list, int item_count);
+FUNC void XmListSelectItem (Widget widget, XmString item, Boolean notify);
+FUNC void XmListSelectPos (Widget widget, int position, Boolean notify);
+FUNC void XmListSetAddMode (Widget widget,Boolean state);
+FUNC void XmListSetBottomItem (Widget widget, XmString item);
+FUNC void XmListSetBottomPos (Widget widget, int position);
+FUNC void XmListSetHorizPos (Widget widget, int location);
+FUNC void XmListSetItem (Widget widget, XmString item);
+FUNC Boolean XmListSetKbdItemPos (Widget widget, int position);
+FUNC void XmListSetPos (Widget widget, int position);
+FUNC void XmListUpdateSelectedList (Widget widget);
+FUNC int XmListYToPos (Widget widget, Position y);

+FUNC Widget XmCreateList (Widget parent, String name, ArgList arglist, Cardinal argCount);
+FUNC Widget XmCreateScrolledList (Widget parent, String name, ArgList arglist, Cardinal argCount);
