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


/* SCO CID (IXI) FrameP.h,v 1.1 1996/08/08 14:12:52 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/Frame.h";
+USE "motif/1_2", "Xm/ManagerP.h";

+FIELD (struct) XmFrameClassPart :=
{
   XtPointer extension;
};


+FIELD (struct) _XmFrameClassRec :=
{
   CoreClassPart       core_class;
   CompositeClassPart  composite_class;
   ConstraintClassPart constraint_class;
   XmManagerClassPart  manager_class;
   XmFrameClassPart    frame_class;
};

+TYPEDEF _XmFrameClassRec XmFrameClassRec;
+EXP lvalue XmFrameClassRec xmFrameClassRec;


+FIELD (struct) XmFramePart := 
{
   Dimension 	margin_width;
   Dimension 	margin_height;
   unsigned char shadow_type;
   Dimension 	old_width;
   Dimension 	old_height;
   Dimension 	old_shadow_thickness;
   Position 	old_shadow_x;
   Position 	old_shadow_y;
   Widget 	work_area;
   Widget 	title_area;
   Boolean 	processing_constraints;
};


+FIELD (struct) _XmFrameRec :=
{
    CorePart	   core;
    CompositePart  composite;
    ConstraintPart constraint;
    XmManagerPart  manager;
    XmFramePart    frame;
};

+TYPEDEF _XmFrameRec XmFrameRec;

+FIELD (struct) _XmFrameConstraintPart :=
{
   int 			unused;
   unsigned char 	child_type;
   unsigned char 	child_h_alignment;
   Dimension 		child_h_spacing;
   unsigned char 	child_v_alignment;
};

+TYPEDEF _XmFrameConstraintPart XmFrameConstraintPart;
+TYPEDEF _XmFrameConstraintPart * XmFrameConstraint;

+FIELD (struct) _XmFrameConstraintRec :=
{
   XmManagerConstraintPart manager;
   XmFrameConstraintPart   frame;
};

+TYPEDEF _XmFrameConstraintRec XmFrameConstraintRec;
+TYPEDEF _XmFrameConstraintRec * XmFrameConstraintPtr;


