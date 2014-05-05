# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

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
