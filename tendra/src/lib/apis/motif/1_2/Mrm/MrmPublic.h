/*
    Copyright (c) 1995 Open Software Foundation, Inc.

    All Rights Reserved

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, provided
    that the above copyright notice appears in all copies and that both the
    copyright notice and this permission notice appear in supporting
    documentation.

    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
    INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
    CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
    COPYRIGHT NOTICE

    This program contains amendments to Motif 1.1 API headers in
    order to represent the Motif 1.2 API. These amendments are the
    property of IXI Ltd, a subsidiary of the Santa Cruz Operation (SCO).
    Use, reproduction, production of amended versions and/or transfer of
    this program is permitted PROVIDED THAT:

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



/* SCO CID (IXI) MrmPublic.h,v 1.1 1996/08/08 14:12:02 wendland Exp */

+USE "x5/t","X11/Intrinsic.h";
+USE "motif/1_2", "Xm/Xm.h";
+USE "motif/1_2", "Mrm/MrmDecls.h";

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

