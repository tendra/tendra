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


/* SCO CID (IXI) BaseClassP.h,v 1.1 1996/08/08 14:12:13 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";


+DEFINE _XmGetFlagsBit(field, bit) %% ((field[ (bit >> 3) ]) & (1 << (bit & 0x07))) %%;
+DEFINE _XmSetFlagsBit(field, bit) %% (field[ (bit >> 3) ] |= (1 << (bit & 0x07))) %%;

+DEFINE _XmFastSubclassInit(wc, bit_field) %% {XmBaseClassExt * _Xm_fastPtr;if(_Xm_fastPtr = _XmGetBaseClassExtPtr( wc, XmQmotif)) _XmSetFlagsBit((*_Xm_fastPtr)->flags, bit_field) ;} %%;

+DEFINE _XmIsFastSubclass(wc, bit) %% (_XmGetFlagsBit( ((*_XmGetBaseClassExtPtr((wc),XmQmotif))->flags), bit) ? TRUE : FALSE) %%;

+CONST long XmBaseClassExtVersion;

+TYPEDEF Cardinal (*XmGetSecResDataFunc)(WidgetClass, XmSecondaryResourceData **);

+FIELD (struct) _XmObjectClassExtRec := { 

	XtPointer	next_extension;
	XrmQuark	record_type;
	long		version;
	Cardinal	record_size;
};

+TYPEDEF _XmObjectClassExtRec XmObjectClassExtRec;
+TYPEDEF _XmObjectClassExtRec *XmObjectClassExt;

+FIELD (struct) _XmGenericClassExtRec := {

	XtPointer	next_extension;
	XrmQuark	record_type;
	long		version;
	Cardinal	record_size;
};

+TYPEDEF _XmGenericClassExtRec XmGenericClassExtRec;
+TYPEDEF _XmGenericClassExtRec *XmGenericClassExt;


+TYPE (struct) _XmWrapperDataRec;

+FIELD (struct) _XmWrapperDataRec := { 

	_XmWrapperDataRec	*next;
	WidgetClass		widgetClass;
	XtInitProc		initializeLeaf;
	XtSetValuesFunc		setValuesLeaf;
	XtArgsProc		getValuesLeaf;
	XtRealizeProc		realize;
	XtWidgetClassProc	classPartInitLeaf;
	XtWidgetProc		resize;
	XtGeometryHandler	geometry_manager;
	Cardinal		init_depth;
};

+TYPEDEF _XmWrapperDataRec XmWrapperDataRec;
+TYPEDEF _XmWrapperDataRec *XmWrapperData;

+FIELD (struct) _XmBaseClassExtRec := {

	XtPointer		next_extension;
	XrmQuark		record_type;
	long			version;
	Cardinal		record_size;
	XtInitProc		initializePrehook;
	XtSetValuesFunc		setValuesPrehook;
	XtInitProc		initializePosthook;
	XtSetValuesFunc		setValuesPosthook;
	WidgetClass		secondaryObjectClass;
	XtInitProc		secondaryObjectCreate;
	XmGetSecResDataFunc	getSecResData;
	unsigned char		flags[32];
	XtArgsProc		getValuesPrehook;
	XtArgsProc		getValuesPosthook;
	XtWidgetClassProc	classPartInitPrehook;
	XtWidgetClassProc	classPartInitPosthook;
	XtResourceList		ext_resources;
	XtResourceList		compiled_ext_resources;
	Cardinal		num_ext_resources;
	Boolean			use_sub_resources;
	XmWidgetNavigableProc	widgetNavigable;
	XmFocusChangeProc	focusChange;
	XmWrapperData		wrapperData;
};

+TYPEDEF _XmBaseClassExtRec XmBaseClassExtRec;
+TYPEDEF _XmBaseClassExtRec *XmBaseClassExt;

+MACRO XmBaseClassExt * _XmBCEPTR(WidgetClass);
+MACRO XmBaseClassExt _XmBCE(WidgetClass);
+MACRO XmBaseClassExt * _XmGetBaseClassExtPtr(WidgetClass, XrmQuark);

+FIELD (struct) _XmWidgetExtDataRec := {

	Widget			widget;
	Widget			reqWidget;
	Widget			oldWidget;
};

+TYPEDEF _XmWidgetExtDataRec XmWidgetExtDataRec;
+TYPEDEF _XmWidgetExtDataRec *XmWidgetExtData;

+EXP XrmQuark XmQmotif;
+EXP int	_XmInheritClass;
+EXP XmBaseClassExt *_Xm_fastPtr;

+FUNC Boolean _XmIsSlowSubclass( WidgetClass, unsigned int);
+FUNC XmGenericClassExt *_XmGetClassExtensionPtr(XmGenericClassExt *, XrmQuark);

+FUNC void _XmPushWidgetExtData(Widget, XmWidgetExtData, unsigned char);

+FUNC void _XmPopWidgetExtData(Widget, XmWidgetExtData *, unsigned char);

+FUNC XmWidgetExtData _XmGetWidgetExtData(Widget, unsigned char);
+FUNC void _XmFreeWidgetExtData(Widget);
+FUNC void _XmBaseClassPartInitialize(WidgetClass);
+FUNC void _XmInitializeExtensions(void);
+FUNC Boolean _XmIsStandardMotifWidgetClass(WidgetClass);
+FUNC Cardinal _XmSecondaryResourceData(XmBaseClassExt, XmSecondaryResourceData **, XtPointer, String, String, XmResourceBaseProc);
+FUNC void _XmTransformSubResources(XtResourceList, Cardinal, XtResourceList *, Cardinal *);
 

