# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h.ts";
+USE "motif/1_2", "Xm/VirtKeys.h.ts";

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
	
