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

+USE "motif/1_2", "Xm/ShellEP.h.ts";
+USE "motif/1_2", "Xm/MwmUtil.h.ts";

+TYPE (struct) _XmVendorShellExtRec;
+TYPE (struct) _XmVendorShellExtClassRec;
+TYPEDEF _XmVendorShellExtRec *XmVendorShellExtObject;
+TYPEDEF _XmVendorShellExtClassRec *XmVendorShellExtObjectClass;

+DEFINE XmInheritProtocolHandler %% ((XtCallbackProc)_XtInherit) %%;


+FIELD (struct) _XmVendorShellExtClassPart := {

	XtCallbackProc			delete_window_handler;
	XtCallbackProc			offset_handler;
	XtPointer			extension;
};

+TYPEDEF _XmVendorShellExtClassPart XmVendorShellExtClassPart;
+TYPEDEF _XmVendorShellExtClassPart *XmVendorShellExtClassPartPtr;

+FIELD (struct) _XmVendorShellExtClassRec := { 

	ObjectClassPart			object_class;
	XmExtClassPart			ext_class;
	XmDesktopClassPart		desktop_class;
	XmShellExtClassPart		shell_class;
	XmVendorShellExtClassPart	vendor_class;
};

+TYPEDEF _XmVendorShellExtClassRec XmVendorShellExtClassRec;

+FIELD (struct) XmVendorShellExtPart := { 

	XmFontList			default_font_list;
	unsigned char			focus_policy;
	XmFocusData			focus_data;
	unsigned char			delete_response;
 	unsigned char			unit_type;
	MwmHints			mwm_hints;
	MwmInfo				mwm_info;
	String				mwm_menu;
	XtCallbackList			focus_moved_callback;

	Widget				old_managed;
	Position			xAtMap;
	Position			yAtMap;
	Position			xOffset;
	Position			yOffset;
	unsigned long			lastOffsetSerial;
	unsigned long			lastMapRequest;
	Boolean				externalReposition;
	unsigned char			mapStyle;
	XtCallbackList			realize_callback;
	XtGrabKind			grab_kind;
	Boolean				audible_warning;
	XmFontList			button_font_list;
	XmFontList			label_font_list;
	XmFontList			text_font_list;
	String				input_method_string;
	String				preedit_type_string;
	unsigned int			light_threshold;
	unsigned int			dark_threshold;
	unsigned int			foreground_threshold;
	unsigned int			im_height;
	XtPointer			im_info;
	Boolean				im_vs_height_set;
};

+TYPEDEF XmVendorShellExtPart *XmVendorShellExtPartPtr;


+EXP lvalue XmVendorShellExtClassRec xmVendorShellExtClassRec;


+FIELD (struct) _XmVendorShellExtRec := { 

	ObjectPart			object;
	XmExtPart			ext;
	XmDesktopPart			desktop;
	XmShellExtPart			shell;
	XmVendorShellExtPart		vendor;
};

+TYPEDEF _XmVendorShellExtRec XmVendorShellExtRec;

+FUNC unsigned char _XmGetAudibleWarning(Widget);
+FUNC char * _XmGetIconPixmapName( void );
+FUNC void _XmClearIconPixmapName( void );
          
