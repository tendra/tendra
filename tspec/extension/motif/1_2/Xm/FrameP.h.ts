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

+USE "motif/1_2", "Xm/Frame.h.ts";
+USE "motif/1_2", "Xm/ManagerP.h.ts";

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


