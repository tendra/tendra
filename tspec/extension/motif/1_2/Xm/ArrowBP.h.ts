# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ArrowB.h.ts";
+USE "motif/1_2", "Xm/PrimitiveP.h.ts";

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
