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


/* SCO CID (IXI) FormP.h,v 1.1 1996/08/08 14:12:51 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/BulletinBP.h";
+USE "motif/1_2", "Xm/Form.h";


+CONST int SORTED_LEFT_TO_RIGHT;
+CONST int SORTED_TOP_TO_BOTTOM;
+CONST int DONT_USE_BOTTOM;
+CONST int DONT_USE_RIGHT;
+CONST int WIDGET_DONT_USE_BOTTOM;
+CONST int WIDGET_DONT_USE_RIGHT;
+CONST int LEFT_NOT_MOVABLE;
+CONST int RIGHT_NOT_MOVABLE;
+CONST int TOP_NOT_MOVABLE;
+CONST int BOTTOM_NOT_MOVABLE;
+CONST int NOT_MOVABLE_RIGHT;
+CONST int NOT_MOVABLE_DOWN;
+CONST int DONT_ATTEMPT_MOVE_RIGHT;
+CONST int DONT_ATTEMPT_MOVE_DOWN;


+FIELD (struct) _XmFormAttachmentRec := {

	unsigned char	type;
	Widget 		w;
	int 		percent;
	int 		offset;
	int 		value;
	int 		tempValue;
};

+TYPEDEF _XmFormAttachmentRec XmFormAttachmentRec;
+TYPEDEF _XmFormAttachmentRec *XmFormAttachment;


+FIELD (struct) _XmFormConstraintPart := {

	XmFormAttachmentRec 	att[4];
	Widget 			next_siblings[2];
	int			flags;
	XtWidgetGeometry	geom;
	Boolean 		resizable;
	Widget			next_sibling;
	Boolean			sorted;
	Dimension 		preferred_width; 
	Dimension		preferred_height;
};

+TYPEDEF _XmFormConstraintPart XmFormConstraintPart;
+TYPEDEF _XmFormConstraintPart * XmFormConstraint;

+FIELD (struct) _XmFormConstraintRec {

	XmManagerConstraintPart manager;
	XmFormConstraintPart    form;
};

+TYPEDEF _XmFormConstraintRec XmFormConstraintRec;
+TYPEDEF _XmFormConstraintRec * XmFormConstraintPtr;

+FIELD (struct) _XmFormClassPart := {

	XtPointer extension;
};

+TYPEDEF _XmFormClassPart XmFormClassPart;

+FIELD ( struct ) _XmFormClassRec := {

	CoreClassPart       		core_class;
	CompositeClassPart  		composite_class;
	ConstraintClassPart 		constraint_class;
	XmManagerClassPart  		manager_class;
	XmBulletinBoardClassPart  	bulletin_board_class;
	XmFormClassPart     		form_class;
};

+TYPEDEF _XmFormClassRec XmFormClassRec;

+EXP lvalue XmFormClassRec xmFormClassRec;

+FIELD ( struct ) _XmFormPart := {

	Dimension		horizontal_spacing;
	Dimension		vertical_spacing;
	int			fraction_base;
	Boolean			rubber_positioning;
	Boolean			need_sorting;
	Widget			sorted_children[2];
	Widget			first_child;
	Boolean			initial_width;
	Boolean			initial_height;
	Boolean			processing_constraints;
};

+TYPEDEF _XmFormPart XmFormPart;

+FIELD ( struct ) _XmFormRec := {
	CorePart	  	core;
	CompositePart  		composite;
	ConstraintPart 		constraint;
	XmManagerPart  		manager;
	XmBulletinBoardPart  	bulletin_board;
	XmFormPart     		form;
};

+TYPEDEF _XmFormRec XmFormRec;

+FIELD (struct) XmFormDelayedConversionRec := { 

	unsigned int		magic;
	String			name;
};

+TYPEDEF XmFormDelayedConversionRec *XmFormDelayedConversion;

+CONST unsigned long FORM_MAGIC;
+MACRO Boolean XmFormIsDelayedConversion(XmFormDelayedConversion);

