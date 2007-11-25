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


/* SCO CID (IXI) SeparatorP.h,v 1.1 1996/08/08 14:13:32 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/Separator.h";
+USE "motif/1_2", "Xm/PrimitiveP.h";

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


