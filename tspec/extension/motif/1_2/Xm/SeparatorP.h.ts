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

+USE "motif/1_2", "Xm/Separator.h.ts";
+USE "motif/1_2", "Xm/PrimitiveP.h.ts";

+FIELD (struct) _XmSeparatorClassPart := {
   XtPointer	extension;
};

+TYPEDEF _XmSeparatorClassPart XmSeparatorClassPart;

+FIELD (struct) _XmSeparatorClassRec := {

   CoreClassPart         core_class;
   XmPrimitiveClassPart  primitive_class;
   XmSeparatorClassPart  separator_class;
};

+TYPEDEF _XmSeparatorClassRec XmSeparatorClassRec;

+EXP lvalue XmSeparatorClassRec xmSeparatorClassRec;


+FIELD (struct) _XmSeparatorPart := {

   Dimension	  margin;
   unsigned char  orientation;
   unsigned char  separator_type;
   GC             separator_GC;
};

+TYPEDEF _XmSeparatorPart XmSeparatorPart;

+FIELD (struct) _XmSeparatorRec := {

   CorePart	    core;
   XmPrimitivePart  primitive;
   XmSeparatorPart  separator;
};

+TYPEDEF _XmSeparatorRec XmSeparatorRec;


