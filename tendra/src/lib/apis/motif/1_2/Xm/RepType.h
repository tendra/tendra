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

/*
    Copyright (c) 1996 Open Software Foundation, Inc.

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



/* SCO CID (IXI) RepType.h,v 1.1 1996/08/08 14:13:17 wendland Exp */
/* TOG CID (osf_ri) RepType.h,v 1.1 1996/08/08 14:13:17 wendland Exp */

+USE "motif/1_2","Xm/Xm.h";

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
