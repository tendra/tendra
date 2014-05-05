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

+USE "motif/1_2", "Xm/PushB.h.ts";
+USE "motif/1_2", "Xm/LabelP.h.ts";

+FIELD (struct) _XmPushButtonClassPart := {

   	XtPointer	extension;
};

+TYPEDEF _XmPushButtonClassPart XmPushButtonClassPart;

+FIELD (struct) _XmPushButtonClassRec := {

    CoreClassPart	  core_class;
    XmPrimitiveClassPart  primitive_class;
    XmLabelClassPart      label_class;
    XmPushButtonClassPart pushbutton_class;
};

+TYPEDEF _XmPushButtonClassRec XmPushButtonClassRec;


+EXP lvalue XmPushButtonClassRec xmPushButtonClassRec;

+FIELD (struct) _XmPushButtonPart := {

   Boolean 	    	fill_on_arm;
   Dimension        	show_as_default;
   Pixel	    	arm_color;
   Pixmap	    	arm_pixmap;
   XtCallbackList   	activate_callback;
   XtCallbackList   	arm_callback;
   XtCallbackList   	disarm_callback;

   Boolean 	    	armed;
   Pixmap	    	unarm_pixmap;
   GC               	fill_gc;
   GC               	background_gc;
   XtIntervalId     	timer;	
   unsigned char    	multiClick;
   int		   	click_count;
   Time		    	armTimeStamp;
   Boolean      	compatible;
   Dimension    	default_button_shadow_thickness;  
};

+TYPEDEF _XmPushButtonPart XmPushButtonPart;


+FIELD (struct) _XmPushButtonRec := {

    CorePart	     core;
    XmPrimitivePart  primitive;
    XmLabelPart      label;
    XmPushButtonPart pushbutton;
};

+TYPEDEF _XmPushButtonRec XmPushButtonRec;

+FUNC void _XmClearBCompatibility(Widget pb) ;

