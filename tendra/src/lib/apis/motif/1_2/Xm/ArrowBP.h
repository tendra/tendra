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


/* SCO CID (IXI) ArrowBP.h,v 1.1 1996/08/08 14:12:12 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ArrowB.h";
+USE "motif/1_2", "Xm/PrimitiveP.h";

+FIELD (struct) _XmArrowButtonClassPart :=
{
   XtPointer extension;
}; 

+TYPEDEF _XmArrowButtonClassPart XmArrowButtonClassPart;

+FIELD (struct) _XmArrowButtonClassRec :=
{
   CoreClassPart        	core_class;
   XmPrimitiveClassPart 	primitive_class;
   XmArrowButtonClassPart     	arrowbutton_class;
};

+TYPEDEF _XmArrowButtonClassRec XmArrowButtonClassRec;

+EXP lvalue XmArrowButtonClassRec xmArrowButtonClassRec;

+FIELD (struct) _XmArrowButtonPart :=
{
   XtCallbackList activate_callback;
   XtCallbackList arm_callback;
   XtCallbackList disarm_callback;
   unsigned char  direction;

   Boolean selected;
   short        top_count;
   short        cent_count;
   short        bot_count;
   XRectangle * top;
   XRectangle * cent;
   XRectangle * bot;

   GC      arrow_GC;
   XtIntervalId     timer;	
   unsigned char    multiClick;
   int              click_count;
   Time		    armTimeStamp;
   GC		    insensitive_GC;
};

+TYPEDEF _XmArrowButtonPart XmArrowButtonPart;

+FIELD (struct) _XmArrowButtonRec := 
{
   CorePart	   	core;
   XmPrimitivePart	primitive;
   XmArrowButtonPart    arrowbutton;
};

+TYPEDEF _XmArrowButtonRec XmArrowButtonRec;
