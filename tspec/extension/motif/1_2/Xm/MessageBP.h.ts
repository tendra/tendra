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
+USE "motif/1_2", "Xm/MessageB.h.ts";

+FIELD (struct) _XmMessageBoxConstraintPart := { 

	char		unused;
};

+TYPEDEF _XmMessageBoxConstraintPart XmMessageBoxConstraintPart;
+TYPEDEF _XmMessageBoxConstraintPart * XmMessageBoxConstraint;

+FIELD (struct) XmMessageBoxClassPart := {

	XtPointer		extension;
};


+FIELD (struct) _XmMessageBoxClassRec := { 

	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmBulletinBoardClassPart	bulletin_board_class;
	XmMessageBoxClassPart	message_box_class;
};

+TYPEDEF _XmMessageBoxClassRec XmMessageBoxClassRec;

+EXP lvalue XmMessageBoxClassRec xmMessageBoxClassRec;

+FIELD (struct) XmMessageBoxPart := { 

	unsigned char		dialog_type;
	unsigned char		default_type;
	Boolean			internal_pixmap;
	Boolean			minimize_buttons;

	unsigned char		message_alignment;
	XmString		message_string;
	Widget			message_wid;
	
	Pixmap			symbol_pixmap;
	Widget			symbol_wid;

	XmString		ok_label_string;
	XtCallbackList		ok_callback;
	Widget			ok_button;

	XmString		cancel_label_string;
	XtCallbackList		cancel_callback;

	XmString		help_label_string;
	Widget			help_button;
	
	Widget			separator;
};


+FUNC XmGeoMatrix _XmMessageBoxGeoMatrixCreate(Widget, Widget, XtWidgetGeometry *);

+FUNC Boolean _XmMessageBoxNoGeoRequest(XmGeoMatrix);


