# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/ScrollBar.h.ts";
+USE "motif/1_2", "Xm/PrimitiveP.h.ts";

+CONST int MIN_SLIDER_THICKNESS;
+CONST int MIN_SLIDER_LENGTH;

+FIELD (struct) _XmScrollBarClassPart := {

   int foo;
};

+TYPEDEF _XmScrollBarClassPart XmScrollBarClassPart;

+FIELD (struct) _XmScrollBarClassRec := {

   CoreClassPart        core_class;
   XmPrimitiveClassPart primitive_class;
   XmScrollBarClassPart scrollBar_class;
};

+TYPEDEF _XmScrollBarClassRec XmScrollBarClassRec;

+EXP lvalue XmScrollBarClassRec xmScrollBarClassRec;

+FIELD (struct) _XmScrollBarPart := {

   int 			value;
   int 			minimum;
   int 			maximum;
   int 			slider_size;

   unsigned char 	orientation;
   unsigned char 	processing_direction;
   Boolean 		show_arrows;

   int 			increment;
   int 			page_increment;

   int 			initial_delay;
   int 			repeat_delay;

   XtCallbackList 	value_changed_callback;
   XtCallbackList 	increment_callback;
   XtCallbackList 	decrement_callback;
   XtCallbackList 	page_increment_callback;
   XtCallbackList 	page_decrement_callback;
   XtCallbackList 	to_top_callback;
   XtCallbackList 	to_bottom_callback;
   XtCallbackList 	drag_callback;

   GC 			unhighlight_GC;

   GC 			foreground_GC;
   Pixel 		trough_color;

   Drawable 		pixmap;
   Boolean  		sliding_on;
   Boolean  		etched_slider;
   int 			saved_value;

   unsigned char 	flags;

   unsigned char 	change_type;
   XtIntervalId 	timer;

   short 		initial_x;
   short 		initial_y;
   short 		separation_x;
   short 		separation_y;

   short 		slider_x;
   short 		slider_y;
   short 		slider_width;
   short 		slider_height;

   short 		slider_area_x;
   short 		slider_area_y;
   short 		slider_area_width;
   short 		slider_area_height;

   short 		arrow1_x;
   short 		arrow1_y;
   unsigned char 	arrow1_orientation;
   Boolean 		arrow1_selected;

   short 		arrow2_x;
   short 		arrow2_y;
   unsigned char 	arrow2_orientation;
   Boolean 		arrow2_selected;

   short 		arrow_width;
   short 		arrow_height;

   short 		arrow1_top_count;
   short 		arrow1_cent_count;
   short 		arrow1_bot_count;

   XRectangle 		* arrow1_top;
   XRectangle 		* arrow1_cent;
   XRectangle 		* arrow1_bot;

   short 		arrow2_top_count;
   short 		arrow2_cent_count;
   short 		arrow2_bot_count;

   XRectangle 		* arrow2_top;
   XRectangle 		* arrow2_cent;
   XRectangle 		* arrow2_bot;

   GC			unavailable_GC;
};

+TYPEDEF _XmScrollBarPart XmScrollBarPart;


+FIELD (struct) _XmScrollBarRec := {

   CorePart	   core;
   XmPrimitivePart primitive;
   XmScrollBarPart scrollBar;
};

+TYPEDEF _XmScrollBarRec XmScrollBarRec;

+FUNC void _XmSetEtchedSlider(XmScrollBarWidget sbw) ;

