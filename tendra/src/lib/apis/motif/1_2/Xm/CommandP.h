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


/* SCO CID (IXI) CommandP.h,v 1.1 1996/08/08 14:12:25 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/SelectioBP.h";
+USE "motif/1_2", "Xm/Command.h";


+FIELD (struct) _XmCommandConstraintPart := { 

	char	unused;
};

+TYPEDEF _XmCommandConstraintPart XmCommandConstraintPart;
+TYPEDEF _XmCommandConstraintPart * XmCommandConstraint;

+FIELD (struct) XmCommandClassPart := { 

	XtPointer	extension;
};


+FIELD (struct) _XmCommandClassRec := { 

	CoreClassPart			core_class;
	CompositeClassPart		composite_class;
	ConstraintClassPart		constraint_class;
	XmManagerClassPart		manager_class;
	XmBulletinBoardClassPart	bulletin_board_class;
	XmSelectionBoxClassPart		selection_box_class;
	XmCommandClassPart		command_class;
};

+TYPEDEF _XmCommandClassRec XmCommandClassRec;

+EXP lvalue XmCommandClassRec xmCommandClassRec;

+FIELD (struct) XmCommandPart := {

	XtCallbackList		callback;
	XtCallbackList		value_changed_callback;
	int			history_max_items;
	Boolean			error;
}; 

+FIELD (struct) _XmCommandRec := { 

	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart       	manager;
	XmBulletinBoardPart 	bulletin_board;
	XmSelectionBoxPart  	selection_box;
	XmCommandPart       	command;
};

+TYPEDEF _XmCommandRec XmCommandRec;

+FUNC void _XmCommandReturn(Widget, XEvent *, String *, Cardinal *);
+FUNC void _XmCommandUpOrDown(Widget, XEvent *, String *, Cardinal *);


