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



/* SCO CID (IXI) VirtKeysP.h,v 1.1 1996/08/08 14:13:56 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";
+USE "motif/1_2", "Xm/VirtKeys.h";

+NAT XmKEYCODE_TAG_SIZE;

+FIELD (struct) _XmDefaultBindingStringRec := { 

	String		vendorName;
	String		defaults;
};

+TYPEDEF _XmDefaultBindingStringRec XmDefaultBindingStringRec;
+TYPEDEF _XmDefaultBindingStringRec *XmDefaultBindingString;


+FIELD (struct) _XmKeyBindingRec := { 

	KeySym		keysym;
	unsigned int	modifiers;
};

+TYPEDEF _XmKeyBindingRec XmKeyBindingRec;
+TYPEDEF _XmKeyBindingRec *XmKeyBinding;


+FIELD (struct) _XmVirtualKeysymRec := { 

	String		name;
	KeySym		keysym;
};

+TYPEDEF _XmVirtualKeysymRec XmVirtualKeysymRec;
+TYPEDEF _XmVirtualKeysymRec *XmVirtualKeysym;

+FUNC void _XmVirtKeysDestroy(Widget);
+FUNC void _XmVirtKeysHandler(Widget, XtPointer, XEvent *, Boolean *);
+FUNC void _XmVirtualToActualKeysym(Display *, KeySym, KeySym *, Modifiers *);
+FUNC void _XmVirtKeysStoreBindings(Widget, String);
+FUNC Boolean _XmVirtKeysLoadFileBindings(char *, String *);
+FUNC int _XmVirtKeysLoadFallbackBindings(Display *, String *);
	
