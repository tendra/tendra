# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


/* for String and Window definitions */
+USE "x5/t", "X11/Intrinsic.h.ts";

+FIELD (struct) MotifWmHints := {

    int	flags;
    int	functions;
    int	decorations;
    int	input_mode;
};

+TYPEDEF MotifWmHints MwmHints;

+CONST int MWM_HINTS_FUNCTIONS;
+CONST int MWM_HINTS_DECORATIONS;
+CONST int MWM_HINTS_INPUT_MODE;
+CONST int MWM_HINTS_STATUS;

+CONST int MWM_FUNC_ALL;
+CONST int MWM_FUNC_RESIZE;
+CONST int MWM_FUNC_MOVE;
+CONST int MWM_FUNC_MINIMIZE;
+CONST int MWM_FUNC_MAXIMIZE;
+CONST int MWM_FUNC_CLOSE;

+CONST int MWM_DECOR_ALL;
+CONST int MWM_DECOR_BORDER;
+CONST int MWM_DECOR_RESIZEH;
+CONST int MWM_DECOR_TITLE;
+CONST int MWM_DECOR_MENU;
+CONST int MWM_DECOR_MINIMIZE;
+CONST int MWM_DECOR_MAXIMIZE;

+CONST int MWM_INPUT_MODELESS;
+CONST int MWM_INPUT_PRIMARY_APPLICATION_MODAL;
+CONST int MWM_INPUT_SYSTEM_MODAL;
+CONST int MWM_INPUT_FULL_APPLICATION_MODAL;
/* OBSOLETE */
+CONST int MWM_INPUT_APPLICATION_MODAL;


+FIELD (struct) MotifWmInfo := { 

    long	flags;
    Window	wm_window;
};

+TYPEDEF MotifWmInfo MwmInfo;

+CONST int MWM_INFO_STARTUP_STANDARD;
+CONST int MWM_INFO_STARTUP_CUSTOM;


+FIELD (struct) PropMotifWmHints := {

    	unsigned long	flags;
    	unsigned long	functions;
    	unsigned long	decorations;
    	long		inputMode;
	unsigned long	status;
};

+TYPEDEF PropMotifWmHints PropMotifMwmHints;
+TYPEDEF PropMotifWmHints PropMwmHints;


+CONST int PROP_MOTIF_WM_HINTS_ELEMENTS;
+CONST int PROP_MWM_HINTS_ELEMENTS;

+CONST String _XA_MOTIF_WM_HINTS;
+CONST String _XA_MWM_HINTS;
+CONST String _XA_MOTIF_WM_MESSAGES;
+CONST String _XA_MWM_MESSAGES;
+CONST String _XA_MOTIF_WM_OFFSET;
+CONST String  _XA_MOTIF_WM_MENU;
+CONST String  _XA_MWM_MENU;


+FIELD (struct) PropMotifWmInfo  :={ 

    long 	flags;
    Window 	wmWindow;
};

+TYPEDEF PropMotifWmInfo PropMwmInfo;

+CONST int PROP_MOTIF_WM_INFO_ELEMENTS;
+CONST int PROP_MWM_INFO_ELEMENTS;

+CONST String _XA_MOTIF_WM_INFO;
+CONST String _XA_MWM_INFO;

+CONST char * _XA_MOTIF_BINDINGS;

