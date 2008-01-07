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



/* SCO CID (IXI) ExtObjectP.h,v 1.1 1996/08/08 14:12:47 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";


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



