# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/SelectioBP.h.ts";
+USE "motif/1_2", "Xm/Command.h.ts";


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


