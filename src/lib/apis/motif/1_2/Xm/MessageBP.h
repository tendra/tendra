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



/* SCO CID (IXI) MessageBP.h,v 1.1 1996/08/08 14:13:07 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/BulletinBP.h";
+USE "motif/1_2", "Xm/MessageB.h";

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


