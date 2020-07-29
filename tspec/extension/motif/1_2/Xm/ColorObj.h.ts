# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2", "Xm/Xm.h.ts";

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

