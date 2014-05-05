# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1996, Open Software Foundation, Inc.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+CONST int XmREP_TYPE_INVALID;

# osf_ri [fdf] 17/04/96:
# XmRepType needs to be same size as XtPointer on DEC Alpha / Motif 1.2.3|4

+IF %% __STRICT_MOTIF_1_2 %%
+TYPEDEF unsigned short XmRepTypeId;
+ELSE
+TYPE (unsigned) XmRepTypeId.1;
+ENDIF


+FIELD (struct) XmRepTypeEntryRec := {
	String 		rep_type_name;
	String 		*value_names;
	unsigned char 	*values;
	unsigned char 	num_values;
	Boolean 	reverse_installed;
	XmRepTypeId 	rep_type_id;
};

+TYPEDEF XmRepTypeEntryRec *XmRepTypeEntry;
+TYPEDEF XmRepTypeEntryRec XmRepTypeListRec;
+TYPEDEF XmRepTypeEntryRec *XmRepTypeList ;


+FUNC void XmRepTypeAddReverse(XmRepTypeId);
+FUNC XmRepTypeId XmRepTypeGetId(String);
+FUNC String *XmRepTypeGetNameList(XmRepTypeId, Boolean);
+FUNC XmRepTypeEntry XmRepTypeGetRecord(XmRepTypeId);
+FUNC XmRepTypeList XmRepTypeGetRegistered(void);
+FUNC void XmRepTypeInstallTearOffModelConverter(void);
+FUNC XmRepTypeId XmRepTypeRegister(String, String *, unsigned char *, unsigned char);
+FUNC Boolean XmRepTypeValidValue(XmRepTypeId, unsigned char, Widget);
