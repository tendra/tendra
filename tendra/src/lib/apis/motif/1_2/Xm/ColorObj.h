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



/* SCO CID (IXI) ColorObj.h,v 1.1 1996/08/08 14:12:21 wendland Exp */

+USE "motif/1_2", "Xm/Xm.h";

+EXP lvalue WidgetClass _xmColorObjClass;

+TYPE (struct) _ColorObjClassRec;
+TYPE (struct) _ColorObjRec;
+TYPEDEF _ColorObjClassRec *ColorObjClass;
+TYPEDEF _ColorObjRec *ColorObj;

+CONST String XmNprimaryColorSetId;
+CONST String XmCPrimaryColorSetId;
+CONST String XmNsecondaryColorSetId;
+CONST String XmCSecondaryColorSetId;
+CONST String XmNactiveColorSetId;
+CONST String XmCActiveColorSetId;
+CONST String XmNinactiveColorSetId;
+CONST String XmCInactiveColorSetId;
+CONST String XmNuseColorObj;
+CONST String XmCUseColorObj;
+CONST String XmNtextColorSetId;
+CONST String XmCTextColorSetId;
+CONST String XmNuseTextColor;
+CONST String XmCUseTextColor;
+CONST String XmNuseTextColorForList;
+CONST String XmCUseTextColorForList;
+CONST String XmNuseMask;
+CONST String XmCUseMask;
+CONST String XmNuseMultiColorIcons;
+CONST String XmCUseMultiColorIcons;

+FIELD (struct) PixelSet := {

	Pixel	fg;
	Pixel	bg;
	Pixel	ts;
	Pixel	bs;
	Pixel	sc;
};

+MACRO int DitherTopShadow(Display *, Screen *, PixelSet *);
+MACRO int DitherBottomShadow(Display *, Screen *, PixelSet *);

+CONST String DITHER;
+CONST String NO_DITHER;

+CONST int B_W;
+CONST int LOW_COLOR;
+CONST int MEDIUM_COLOR;
+CONST int HIGH_COLOR;

+CONST String COLOR_SRV_NAME;

+CONST int VALUE_THRESHOLD;

+CONST String PIXEL_SET;
+CONST String PALETTE_NAME;
+CONST String TYPE_OF_MONITOR;
+CONST String UPDATE_FILE;
+CONST String CUST_DATA;

+CONST int MAX_NUM_COLORS;
+NAT NUM_COLORS;

