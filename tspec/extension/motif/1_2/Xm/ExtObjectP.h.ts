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


+CONST int XmNUM_ELEMENTS;
+NAT XmNUM_BYTES;

+FIELD (struct) _XmExtClassPart := { 

	XmSyntheticResource	*syn_resources;
	int			num_syn_resources;
	XtPointer		extension;
};

+TYPEDEF _XmExtClassPart XmExtClassPart;
+TYPEDEF _XmExtClassPart *XmExtClassPartPtr;

+FIELD (struct) XmExtClassRec := { 

	ObjectClassPart		object_class;
	XmExtClassPart		ext_class;
};


+FIELD (struct) XmExtPart := { 

	Widget			logicalParent;
	unsigned char		extensionType;
};

+TYPEDEF XmExtPart *XmExtPartPtr;

+EXP lvalue XmExtClassRec xmExtClassRec;

+FIELD (struct) XmExtRec := { 

	ObjectPart		object;
	XmExtPart		ext;
};

+FIELD (struct) _XmExtCache := { 

	char			date[XmNUM_BYTES];
	Boolean			inuse;
};

+TYPEDEF _XmExtCache XmExtCache;


+FUNC char * _XmExtObjAlloc(int);
+FUNC void _XmExtObjFree(XtPointer);
+FUNC void _XmBuildExtResources(WidgetClass);



