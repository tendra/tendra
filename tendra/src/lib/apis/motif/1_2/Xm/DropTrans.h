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




/* SCO CID (IXI) DropTrans.h,v 1.1 1996/08/08 14:12:46 wendland Exp */

+USE "motif/1_2", "Xm/Xm.h";

+CONST int XmTRANSFER_FAILURE;
+CONST int XmTRANSFER_SUCCESS;

+EXP lvalue WidgetClass xmDropTransferObjectClass;

+TYPE (struct) _XmDropTransferClassRec;
+TYPE (struct) _XmDropTransferRec;
+TYPEDEF _XmDropTransferClassRec * XmDropTransferObjectClass;
+TYPEDEF _XmDropTransferRec * XmDropTransferObject;


+FIELD (struct) _XmDropTransferEntryRec := { 

	XtPointer		client_data;
	Atom			target;
};

+TYPEDEF _XmDropTransferEntryRec XmDropTransferEntryRec;
+TYPEDEF _XmDropTransferEntryRec * XmDropTransferEntry;


+FUNC Widget XmDropTransferStart(Widget, ArgList, Cardinal);
+FUNC void XmDropTransferAdd(Widget, XmDropTransferEntry, Cardinal);

