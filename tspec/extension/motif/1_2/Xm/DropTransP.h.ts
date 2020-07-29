# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/DropTrans.h.ts";
+USE "motif/1_2", "Xm/XmP.h.ts";

+TYPEDEF Widget (*XmDropTransferStartTransferProc)(Widget, ArgList, Cardinal);
+TYPEDEF void (*XmDropTransferAddTransferProc)(Widget, XmDropTransferEntry, Cardinal);

+FIELD (struct) _XmDropTransferClassPart := { 

	XmDropTransferStartTransferProc	start_drop_transfer;
	XmDropTransferAddTransferProc	add_drop_transfer;
	XtPointer			extension;
};

+TYPEDEF _XmDropTransferClassPart XmDropTransferClassPart;

+FIELD (struct) _XmDropTransferClassRec := { 

	ObjectClassPart		object_class;
	XmDropTransferClassPart	dropTransfer_class;
};

+TYPEDEF _XmDropTransferClassRec XmDropTransferClassRec;

+EXP lvalue XmDropTransferClassRec xmDropTransferClassRec;

+FIELD (struct) _XmDropTransferListRec := { 

	XmDropTransferEntry	transfer_list;
	Cardinal		num_transfers;
};

+TYPEDEF _XmDropTransferListRec XmDropTransferListRec;
+TYPEDEF _XmDropTransferListRec * XmDropTransferList;   

+FIELD (struct) _XmDropTransferPart := {

	XmDropTransferEntry	drop_transfers;
	Cardinal		num_drop_transfers;
	Atom			selection;
	Widget			dragContext;
	Time			timestamp;
	Boolean			incremental;
	Window			source_window;
	unsigned int		tag;
	XtSelectionCallbackProc	transfer_callback;
	unsigned char		transfer_status;
	
	Atom			motif_drop_atom;
	
	XmDropTransferList	drop_transfer_lists;
	Cardinal		num_drop_transfer_lists;
	Cardinal		cur_drop_transfer_list;
	Cardinal		cur_xfer;
	Atom			*cur_targets;
	XtPointer		*cur_client_data;
};

+TYPEDEF _XmDropTransferPart XmDropTransferPart;

+FIELD (struct) _XmDropTransferRec := { 

	ObjectPart		object;
	XmDropTransferPart	dropTransfer;
};

+TYPEDEF _XmDropTransferRec XmDropTransferRec;


