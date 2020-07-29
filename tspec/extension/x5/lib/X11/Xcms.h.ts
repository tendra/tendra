# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Colour management facilities

+USE "x5/lib", "X11/Xlib.h.ts" ;		# needed


# Colour Structures (6.1)

+TYPE ( int ) XcmsColorFormat ;		# RCA : ulong in spec, uint in mit
+TYPEDEF double XcmsFloat ;

+FIELD ( struct ) XcmsRGB := { unsigned short red, green, blue ; } ;
+FIELD ( struct ) XcmsRGBi := { XcmsFloat red, green, blue ; } ;
+FIELD ( struct ) XcmsCIEXYZ := { XcmsFloat X, Y, Z ; } ;
+FIELD ( struct ) XcmsCIEuvY := { XcmsFloat u_prime, v_prime, Y ; } ;
+FIELD ( struct ) XcmsCIExyY := { XcmsFloat x, y, Y ; } ;
+FIELD ( struct ) XcmsCIELab := { XcmsFloat L_star, a_star, b_star ; } ;
+FIELD ( struct ) XcmsCIELuv := { XcmsFloat L_star, u_star, v_star ; } ;
+FIELD ( struct ) XcmsTekHVC := { XcmsFloat H, V, C ; } ;
+FIELD ( struct ) XcmsPad := { XcmsFloat pad0, pad1, pad2, pad3 ; } ;

+FIELD union ~XcmsSpec := {
    XcmsRGB RGB ;
    XcmsRGBi RGBi ;
    XcmsCIEXYZ CIEXYZ ;
    XcmsCIEuvY CIEuvY ;
    XcmsCIExyY CIExyY ;
    XcmsCIELab CIELab ;
    XcmsCIELuv CIELuv ;
    XcmsTekHVC TekHVC ;
    XcmsPad Pad ;
} ;

+FIELD ( struct ) XcmsColor := {
    union ~XcmsSpec spec ;
    XcmsColorFormat format ;
    unsigned long pixel ;
} ;

+DEFINE XcmsUndefinedFormat	%% 0x00000000 %% ;
+DEFINE XcmsCIEXYZFormat	%% 0x00000001 %% ;
+DEFINE XcmsCIEuvYFormat	%% 0x00000002 %% ;
+DEFINE XcmsCIExyYFormat	%% 0x00000003 %% ;
+DEFINE XcmsCIELabFormat	%% 0x00000004 %% ;
+DEFINE XcmsCIELuvFormat	%% 0x00000005 %% ;
+DEFINE XcmsTekHVCFormat	%% 0x00000006 %% ;
+DEFINE XcmsRGBFormat		%% 0x80000000 %% ;
+DEFINE XcmsRGBiFormat		%% 0x80000001 %% ;


# Mapping colour names to values (6.5)

+CONST Status XcmsSuccess, XcmsSuccessWithCompression, XcmsFailure ;
+FUNC Status XcmsLookupColor ( Display *, Colormap, char *, XcmsColor *,
    XcmsColor *, XcmsColorFormat ) ;


# Allocating and Freeing Colour cells (6.6)

+FUNC Status XcmsAllocColor ( Display *, Colormap, XcmsColor *,
    XcmsColorFormat ) ;
+FUNC Status XcmsAllocNamedColor ( Display *, Colormap, char *,
    XcmsColor *, XcmsColor *, XcmsColorFormat ) ; # RCA : Error in spec?


# Modifying and Querying Colormap Cells (6.7)

+FUNC Status XcmsStoreColor ( Display *, Colormap, XcmsColor * ) ;
+FUNC Status XcmsStoreColors ( Display *, Colormap, XcmsColor [],
    unsigned int, Bool [] ) ;	# RCA : Error in spec ?
+FUNC Status XcmsQueryColor ( Display *, Colormap, XcmsColor *,
    XcmsColorFormat ) ;
+FUNC Status XcmsQueryColors ( Display *, Colormap, XcmsColor [],
    unsigned int, XcmsColorFormat ) ;


# Colour Conversion Contexts (6.8, 6.10.1, 6.10.3)

+TYPE ~XcmsCCCRec ;
+TYPEDEF ~XcmsCCCRec *XcmsCCC ;	# RCA : no information given

+TYPEDEF Status ( *XcmsCompressionProc ) ( XcmsCCC, XcmsColor [],
    unsigned int, unsigned int, Bool [] ) ;

+TYPEDEF Status ( *XcmsWhiteAdjustProc ) ( XcmsCCC, XcmsColor *,
    XcmsColor *, XcmsColorFormat, XcmsColor [], unsigned int, Bool [] ) ;


# Getting and Setting CCC of a Colormap (6.8.1)

+FUNC XcmsCCC XcmsCCCOfColormap ( Display *, Colormap ) ;
+FUNC XcmsCCC XcmsSetCCCOfColormap ( Display *, Colormap, XcmsCCC ) ;


# Getting the default CC (6.8.2)

+FUNC XcmsCCC XcmsDefaultCCC ( Display *, int ) ;


# CCC macros (6.8.3)

+FUNC Display *XcmsDisplayOfCCC ( XcmsCCC ) ;
+FUNC Visual *XcmsVisualOfCCC ( XcmsCCC ) ;
+FUNC int XcmsScreenNumberOfCCC ( XcmsCCC ) ;
+FUNC XcmsColor *XcmsScreenWhitePointOfCCC ( XcmsCCC ) ;
+FUNC XcmsColor *XcmsClientWhitePointOfCCC ( XcmsCCC ) ;

+MACRO Display *DisplayOfCCC ( XcmsCCC ) ;
+MACRO Visual *VisualOfCCC ( XcmsCCC ) ;
+MACRO int ScreenNumberOfCCC ( XcmsCCC ) ;
+MACRO XcmsColor *ScreenWhitePointOfCCC ( XcmsCCC ) ;
+MACRO XcmsColor *ClientWhitePointOfCCC ( XcmsCCC ) ;


# Modifying attributes of a CCC (6.8.4)

+FUNC Status XcmsSetWhitePoint ( XcmsCCC, XcmsColor * ) ;
+FUNC XcmsCompressionProc XcmsSetCompressionProc ( XcmsCCC,
    XcmsCompressionProc, XPointer ) ;
+FUNC XcmsWhiteAdjustProc XcmsSetWhiteAdjustProc ( XcmsCCC,
    XcmsWhiteAdjustProc, XPointer ) ;


# Creating and Freeing a CCC (6.8.5)

+FUNC XcmsCCC XcmsCreateCCC ( Display *, int, Visual *, XcmsColor *,
    XcmsCompressionProc, XPointer, XcmsWhiteAdjustProc, XPointer ) ;
+FUNC void XcmsFreeCCC ( XcmsCCC ) ;


# Converting between Colour spaces (6.9)

+FUNC Status XcmsConvertColors ( XcmsCCC, XcmsColor [], unsigned int,
    XcmsColorFormat, Bool [] ) ;


# Supplied Gamut Compression Procedures (6.10.2)

+FUNC Status XcmsCIELabClipL ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsCIELabClipab ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsCIELabClipLab ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsCIELuvClipL ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsCIELuvClipuv ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsCIELuvClipLuv ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsTekHVCClipV ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsTekHVCClipC ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;
+FUNC Status XcmsTekHVCClipVC ( XcmsCCC, XcmsColor [], unsigned int,
    unsigned int, Bool [] ) ;


# Supplied White Point Adjustment Procedures (6.10.4)

+FUNC Status XcmsCIELabWhiteShiftColors ( XcmsCCC, XcmsColor *,
    XcmsColor *, XcmsColorFormat, XcmsColor [], unsigned int, Bool [] ) ;
+FUNC Status XcmsCIELuvWhiteShiftColors ( XcmsCCC, XcmsColor *,
    XcmsColor *, XcmsColorFormat, XcmsColor [], unsigned int, Bool [] ) ;
+FUNC Status XcmsTekHVCWhiteShiftColors ( XcmsCCC, XcmsColor *,
    XcmsColor *, XcmsColorFormat, XcmsColor [], unsigned int, Bool [] ) ;


# Red, Green and Blue Queries (6.11.1)

+FUNC Status XcmsQueryBlack ( XcmsCCC, XcmsColorFormat, XcmsColor * ) ;
+FUNC Status XcmsQueryBlue ( XcmsCCC, XcmsColorFormat, XcmsColor * ) ;
+FUNC Status XcmsQueryGreen ( XcmsCCC, XcmsColorFormat, XcmsColor * ) ;
+FUNC Status XcmsQueryRed ( XcmsCCC, XcmsColorFormat, XcmsColor * ) ;
+FUNC Status XcmsQueryWhite ( XcmsCCC, XcmsColorFormat, XcmsColor * ) ;


# CIELab Queries (6.11.2)

+FUNC Status XcmsCIELabQueryMaxC ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;
+FUNC Status XcmsCIELabQueryMaxL ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;
+FUNC Status XcmsCIELabQueryMaxLC ( XcmsCCC, XcmsFloat, XcmsColor * ) ;
+FUNC Status XcmsCIELabQueryMinL ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;


# CIELuv Queries (6.11.3)

+FUNC Status XcmsCIELuvQueryMaxC ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;
+FUNC Status XcmsCIELuvQueryMaxL ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;
+FUNC Status XcmsCIELuvQueryMaxLC ( XcmsCCC, XcmsFloat, XcmsColor * ) ;
+FUNC Status XcmsCIELuvQueryMinL ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;


# TekHVC Queries (6.11.4)

+FUNC Status XcmsTekHVCQueryMaxC ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;
+FUNC Status XcmsTekHVCQueryMaxV ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;
+FUNC Status XcmsTekHVCQueryMaxVC ( XcmsCCC, XcmsFloat, XcmsColor * ) ;
+FUNC Status XcmsTekHVCQueryMaxVSamples ( XcmsCCC, XcmsFloat, XcmsColor [],
    unsigned int ) ;
+FUNC Status XcmsTekHVCQueryMinV ( XcmsCCC, XcmsFloat, XcmsFloat,
    XcmsColor * ) ;


# Creating Additional Colour spaces (6.12.4, 6.12.5)

+TYPEDEF Status ( *XcmsConversionProc ) () ;
+TYPEDEF XcmsConversionProc *XcmsFuncListPtr ;
+TYPEDEF int ( *XcmsParseStringProc ) ( char *, XcmsColor * )  ;
+FIELD ( struct ) XcmsColorSpace := {
    char *prefix ;
    XcmsColorFormat format ;
    XcmsParseStringProc parseString ;
    XcmsFuncListPtr to_CIEXYZ ;
    XcmsFuncListPtr from_CIEXYZ ;
    int inverse_flag ;
} ;


# Adding Device-independent Colour spaces (6.12.2)

+FUNC Status XcmsAddColorSpace ( XcmsColorSpace * ) ;


# Querying Colour spaces (6.12.3)

+FUNC XcmsColorFormat XcmsFormatOfPrefix ( char * ) ;
+FUNC char *XcmsPrefixOfFormat ( XcmsColorFormat ) ;


# Conversion Routines (6.12.6)

+FUNC Status XcmsCIELabToCIEXYZ ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIELuvToCIEuvY ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIEXYZToCIELab ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIEXYZToCIEuvY ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIEXYZToCIExyY ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIEuvYToCIELuv ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIEuvYToCIEXYZ ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIEuvYToTekHVC ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsCIExyYToCIEXYZ ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;
+FUNC Status XcmsTekHVCToCIEuvY ( XcmsCCC, XcmsColor *, XcmsColor *,
    unsigned int ) ;

+FUNC Status XcmsCIEXYZToRGBi ( XcmsCCC, XcmsColor *, unsigned int, Bool * ) ;
+FUNC Status XcmsRGBToRGBi ( XcmsCCC, XcmsColor *, unsigned int, Bool * ) ;
+FUNC Status XcmsRGBiToCIEXYZ ( XcmsCCC, XcmsColor *, unsigned int, Bool * ) ;
+FUNC Status XcmsRGBiToRGB ( XcmsCCC, XcmsColor *, unsigned int, Bool * ) ;


# Adding Function Sets (6.12.8, 6.12.9)

+FIELD ( struct ) XcmsPerScrnInfo := {
    XcmsColor screenWhitePoint ;
    XPointer functionSet ;
    XPointer screenData ;
    unsigned char state ;
    char pad [3] ;
} ;

+TYPEDEF Status ( *XcmsScreenInitProc ) ( Display *, int,
    XcmsPerScrnInfo * ) ;
+TYPEDEF void ( *XcmsScreenFreeProc ) ( XPointer ) ;

+CONST Status XcmsInitNone, XcmsInitFailure, XcmsInitSuccess ;

+FIELD ( struct ) XcmsFunctionSet := {
    XcmsColorSpace **DDColorSpaces ;
    XcmsScreenInitProc screenInitProc ;
    XcmsScreenFreeProc screenFreeProc ;
} ;

+FUNC Status XcmsAddFunctionSet ( XcmsFunctionSet * ) ;
