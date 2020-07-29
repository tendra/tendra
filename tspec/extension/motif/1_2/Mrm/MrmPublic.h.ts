# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1995, Open Software Foundation, Inc.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t","X11/Intrinsic.h.ts";
+USE "motif/1_2", "Xm/Xm.h.ts";
+USE "motif/1_2", "Mrm/MrmDecls.h.ts";

+CONST int MrmSUCCESS;
+CONST int MrmCREATE_NEW;
+CONST int MrmINDEX_RETRY;
+CONST int MrmINDEX_GT;
+CONST int MrmINDEX_LT;
+CONST int MrmPARTIAL_SUCCESS;

+CONST int MrmFAILURE;
+CONST int MrmNOT_FOUND;
+CONST int MrmEXISTS;
+CONST int MrmNUL_GROUP;
+CONST int MrmNUL_TYPE;
+CONST int MrmWRONG_GROUP;
+CONST int MrmWRONG_TYPE;
+CONST int MrmOUT_OF_RANGE;
+CONST int MrmBAD_RECORD;
+CONST int MrmNULL_DATA;
+CONST int MrmBAD_DATA_INDEX;
+CONST int MrmBAD_ORDER;
+CONST int MrmBAD_CONTEXT;
+CONST int MrmNOT_VALID;
+CONST int MrmBAD_BTREE;
+CONST int MrmBAD_WIDGET_REC;
+CONST int MrmBAD_CLASS_TYPE;
+CONST int MrmNO_CLASS_NAME;
+CONST int MrmTOO_MANY;
+CONST int MrmBAD_IF_MODULE;
+CONST int MrmNULL_DESC;
+CONST int MrmOUT_OF_BOUNDS;
+CONST int MrmBAD_COMPRESS;
+CONST int MrmBAD_ARG_TYPE;
+CONST int MrmNOT_IMP;
+CONST int MrmNULL_INDEX;
+CONST int MrmBAD_KEY_TYPE;
+CONST int MrmBAD_CALLBACK;
+CONST int MrmNULL_ROUTINE;
+CONST int MrmVEC_TOO_BIG;
+CONST int MrmBAD_HIERARCHY;
+CONST int MrmBAD_CLASS_CODE;
+CONST int MrmDISPLAY_NOT_OPENED;
+CONST int MrmEOF;
+CONST int MrmUNRESOLVED_REFS;


+CONST String MrmNcreateCallback;
+CONST int MrmCR_CREATE;

+CONST int MrmwcUnknown;


+CONST int MrmRtypeMin;
+CONST int MrmRtypeInteger;
+CONST int MrmRtypeBoolean;
+CONST int MrmRtypeChar8;
+CONST int MrmRtypeChar8Vector;
+CONST int MrmRtypeCString;
+CONST int MrmRtypeCStringVector;
+CONST int MrmRtypeFloat;

+CONST int MrmRtypeCallback;
+CONST int MrmRtypePixmapImage;
+CONST int MrmRtypePixmapDDIF;
+CONST int MrmRtypeResource;
+CONST int MrmRtypeNull;
+CONST int MrmRtypeAddrName;

+CONST int MrmRtypeIconImage;
+CONST int MrmRtypeFont;
+CONST int MrmRtypeFontList;
+CONST int MrmRtypeColor;
+CONST int MrmRtypeColorTable;
+CONST int MrmRtypeAny;
+CONST int MrmRtypeTransTable;
+CONST int MrmRtypeClassRecName;
+CONST int MrmRtypeIntegerVector;
+CONST int MrmRtypeXBitmapFile;
+CONST int MrmRtypeCountedVector;
+CONST int MrmRtypeKeysym;
+CONST int MrmRtypeSingleFloat;
+CONST int MrmRtypeWideCharacter;
+CONST int MrmRtypeFontSet;
+CONST int MrmRtypeMax;



+TYPEDEF short MrmCode;
+TYPEDEF unsigned char MrmSCode;
+TYPEDEF unsigned short MrmOffset;
+TYPEDEF short MrmType;
+TYPEDEF unsigned short MrmSize;
+TYPEDEF short MrmCount;
+TYPEDEF unsigned char MrmFlag;
+TYPEDEF long MrmResource_id;
+TYPEDEF short MrmGroup;

+CONST int MrmMaxResourceSize;

+CONST int MrmOsOpenParamVersion;

/* opaque types */

+TYPE (struct) MrmOsOpenParam;
+TYPEDEF MrmOsOpenParam *MrmOsOpenParamPtr;

+TYPE (struct) MrmHierarchyDescStruct;
+TYPEDEF MrmHierarchyDescStruct *MrmHierarchy;

	
+FIELD (struct) MRMRegisterArg := {

	String	name;
	XtPointer	value;

}; 

+TYPEDEF MRMRegisterArg MrmRegisterArg;
+TYPEDEF MRMRegisterArg *MrmRegisterArglist;


+CONST int URMwcUnknown;

