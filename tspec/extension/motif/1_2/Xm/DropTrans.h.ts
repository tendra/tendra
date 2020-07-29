# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2", "Xm/Xm.h.ts";

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

