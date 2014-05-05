# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


/*
    I'M NOT AT ALL SURE ABOUT MOST OF THIS
*/

+USE "x5/lib", "X11/X.h.ts" ;
+USE "x5/lib", "X11/Xproto.h.ts" ;
+USE "x5/proto", "X11/Xprotostr.h.ts" ;

/* Basic types */
+TYPE ( int ) INT8, ( int ) INT16, ( int ) INT32 ;
+TYPE ( int ) CARD8, ( int ) CARD16, ( int ) CARD32 ;
+TYPE ( int ) BYTE, ( int ) BOOL ;

+IFNDEF ~building_libs
%%
/* Haven't done this properly yet */
#define B16	:16
#define B32	:32
%%
+ENDIF

/* Special types */
+TYPE ( int ) INT16_BF, ( int ) INT32_BF ;
+TYPE ( int ) CARD16_BF, ( int ) CARD32_BF ;

/* Error values */
+CONST int X_Reply, X_Error ;

/* Auxilliary structures */

+FIELD ( struct ) xCharInfo {
    INT16_BF leftSideBearing, rightSideBearing ;
    INT16_BF characterWidth, ascent, descent ;
    CARD16_BF attributes ;
} ;

/* Request and Reply structures */

+FIELD xReq {
    CARD8 reqType ;
    CARD8 data ;
    CARD16_BF length ;
} ;

+FIELD ( struct ) xResourceReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF id ;
} ;

+FIELD ( struct ) xCreateWindowReq {
    CARD8 reqType ;
    CARD8 depth ;
    CARD16_BF length ;
    CARD32_BF wid, parent ;
    INT16_BF x, y ;
    CARD16_BF width, height, borderWidth ;
    CARD16_BF class ;
    CARD32_BF visual ;
    CARD32_BF mask ;
} ;

+FIELD ( struct ) xChangeWindowAttributesReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD32_BF valueMask ;
} ;

+FIELD ( struct ) xChangeSaveSetReq {
    CARD8 reqType ;
    BYTE mode ;
    CARD16_BF length ;
    CARD32_BF window ;
} ;

+FIELD ( struct ) xReparentWindowReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window, parent ;
    INT16_BF x, y ;
} ;

+FIELD ( struct ) xConfigureWindowReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD16_BF mask ;
} ;

+FIELD ( struct ) xCirculateWindowReq {
    CARD8 reqType ;
    CARD8 direction ;
    CARD16_BF length ;
    CARD32_BF window ;
} ;

+FIELD ( struct ) xInternAtomReq {
    CARD8 reqType ;
    BOOL onlyIfExists ;
    CARD16_BF length ;
    CARD16_BF nbytes ;
} ;

+FIELD ( struct ) xChangePropertyReq {
    CARD8 reqType ;
    CARD8 mode ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD32_BF property, type ;
    CARD8 format ;
    CARD32_BF nUnits ;
} ;

+FIELD ( struct ) xDeletePropertyReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD32_BF property ;
} ;

+FIELD ( struct ) xGetPropertyReq {
    CARD8 reqType ;
    BOOL delete ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD32_BF property, type ;
    CARD32_BF longOffset ;
    CARD32_BF longLength ;
} ;

+FIELD ( struct ) xSetSelectionOwnerReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD32_BF selection ;
    CARD32_BF time ;
} ;

+FIELD ( struct ) xConvertSelectionReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF requestor ;
    CARD32_BF selection, target, property ;
    CARD32_BF time ;
} ;

+FIELD ( struct ) xSendEventReq {
    CARD8 reqType ;
    BOOL propagate ;
    CARD16_BF length ;
    CARD32_BF destination ;
    CARD32_BF eventMask ;
    xEvent event ;
} ;

+FIELD ( struct ) xGrabPointerReq {
    CARD8 reqType ;
    BOOL ownerEvents ;
    CARD16_BF length ;
    CARD32_BF grabWindow ;
    CARD16_BF eventMask ;
    BYTE pointerMode, keyboardMode ;
    CARD32_BF confineTo ;
    CARD32_BF cursor ;
    CARD32_BF time ;
} ;

+FIELD ( struct ) xGrabButtonReq {
    CARD8 reqType ;
    BOOL ownerEvents ;
    CARD16_BF length ;
    CARD32_BF grabWindow ;
    CARD16_BF eventMask ;
    BYTE pointerMode, keyboardMode ;
    CARD32_BF confineTo ;
    CARD32_BF cursor ;
    CARD8 button ;
    CARD16_BF modifiers ;
} ;

+FIELD ( struct ) xUngrabButtonReq {
    CARD8 reqType ;
    CARD8 button ;
    CARD16_BF length ;
    CARD32_BF grabWindow ;
    CARD16_BF modifiers ;
} ;

+FIELD ( struct ) xChangeActivePointerGrabReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cursor ;
    CARD32_BF time ;
    CARD16_BF eventMask ;
} ;

+FIELD ( struct ) xGrabKeyboardReq {
    CARD8 reqType ;
    BOOL ownerEvents ;
    CARD16_BF length ;
    CARD32_BF grabWindow ;
    CARD32_BF time ;
    BYTE pointerMode, keyboardMode ;
} ;

+FIELD ( struct ) xGrabKeyReq {
    CARD8 reqType ;
    BOOL ownerEvents ;
    CARD16_BF length ;
    CARD32_BF grabWindow ;
    CARD16_BF modifiers ;
    CARD8 key ;
    BYTE pointerMode, keyboardMode ;
} ;

+FIELD ( struct ) xUngrabKeyReq {
    CARD8 reqType ;
    CARD8 key ;
    CARD16_BF length ;
    CARD32_BF grabWindow ;
    CARD16_BF modifiers ;
} ;

+FIELD ( struct ) xAllowEventsReq {
    CARD8 reqType ;
    CARD8 mode ;
    CARD16_BF length ;
    CARD32_BF time ;
} ;

+FIELD ( struct ) xGetMotionEventsReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD32_BF start, stop ;
} ;

+FIELD ( struct ) xTranslateCoordsReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF srcWid, dstWid ;
    INT16_BF srcX, srcY ;
} ;

+FIELD ( struct ) xWarpPointerReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF srcWid, dstWid ;
    INT16_BF srcX, srcY ;
    CARD16_BF srcWidth, srcHeight ;
    INT16_BF dstX, dstY ;
} ;

+FIELD ( struct ) xSetInputFocusReq {
    CARD8 reqType ;
    CARD8 revertTo ;
    CARD16_BF length ;
    CARD32_BF focus ;
    CARD32_BF time ;
} ;

+FIELD ( struct ) xOpenFontReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF fid ;
    CARD16_BF nbytes ;
} ;

+FIELD ( struct ) xQueryTextExtentsReq {
    CARD8 reqType ;
    BOOL oddLength ;
    CARD16_BF length ;
    CARD32_BF fid ;
} ;

+FIELD ( struct ) xListFontsReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD16_BF maxNames ;
    CARD16_BF nbytes ;
} ;

+TYPEDEF xListFontsReq xListFontsWithInfoReq ;

+FIELD ( struct ) xSetFontPathReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD16_BF nFonts ;
} ;

+FIELD ( struct ) xCreatePixmapReq {
    CARD8 reqType ;
    CARD8 depth ;
    CARD16_BF length ;
    CARD32_BF pid ;
    CARD32_BF drawable ;
    CARD16_BF width, height ;
} ;

+FIELD ( struct ) xCreateGCReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF gc ;
    CARD32_BF drawable ;
    CARD32_BF mask ;
} ;

+FIELD ( struct ) xChangeGCReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF gc ;
    CARD32_BF mask ;
} ;

+FIELD ( struct ) xCopyGCReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF srcGC, dstGC ;
    CARD32_BF mask ;
} ;

+FIELD ( struct ) xSetDashesReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF gc ;
    CARD16_BF dashOffset ;
    CARD16_BF nDashes ;
} ;

+FIELD ( struct ) xSetClipRectanglesReq {
    CARD8 reqType ;
    BYTE ordering ;
    CARD16_BF length ;
    CARD32_BF gc ;
    INT16_BF xOrigin, yOrigin ;
} ;

+FIELD ( struct ) xClearAreaReq {
    CARD8 reqType ;
    BOOL exposures ;
    CARD16_BF length ;
    CARD32_BF window ;
    INT16_BF x, y ;
    CARD16_BF width, height ;
} ;

+FIELD ( struct ) xCopyAreaReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF srcDrawable, dstDrawable ;
    CARD32_BF gc ;
    INT16_BF srcX, srcY, dstX, dstY ;
    CARD16_BF width, height ;
} ;

+FIELD ( struct ) xCopyPlaneReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF srcDrawable, dstDrawable ;
    CARD32_BF gc ;
    INT16_BF srcX, srcY, dstX, dstY ;
    CARD16_BF width, height ;
    CARD32_BF bitPlane ;
} ;

+FIELD ( struct ) xPolyPointReq {
    CARD8 reqType ;
    BYTE coordMode ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD32_BF gc ;
} ;

+TYPEDEF xPolyPointReq xPolyLineReq ;



+FIELD ( struct ) xPolySegmentReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD32_BF gc ;
} ;

+TYPEDEF xPolySegmentReq xPolyArcReq ;
+TYPEDEF xPolySegmentReq xPolyRectangleReq ;
+TYPEDEF xPolySegmentReq xPolyFillRectangleReq ;
+TYPEDEF xPolySegmentReq xPolyFillArcReq ;

+FIELD ( struct ) xFillPolyReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD32_BF gc ;
    BYTE shape ;
    BYTE coordMode ;
} ;

+FIELD ( struct ) xPutImageReq {
    CARD8 reqType ;
    CARD8 format ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD32_BF gc ;
    CARD16_BF width, height ;
    INT16_BF dstX, dstY ;
    CARD8 leftPad ;
    CARD8 depth ;
} ;

+FIELD ( struct ) xGetImageReq {
    CARD8 reqType ;
    CARD8 format ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    INT16_BF x, y ;
    CARD16_BF width, height ;
    CARD32_BF planeMask ;
} ;

+FIELD ( struct ) xPolyTextReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD32_BF gc ;
    INT16_BF x, y ;
} ;

+TYPEDEF xPolyTextReq xPolyText8Req ;
+TYPEDEF xPolyTextReq xPolyText16Req ;

+FIELD ( struct ) xImageTextReq {
    CARD8 reqType ;
    BYTE nChars ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD32_BF gc ;
    INT16_BF x, y ;
} ;

+TYPEDEF xImageTextReq xImageText8Req ;
+TYPEDEF xImageTextReq xImageText16Req ;

+FIELD ( struct ) xCreateColormapReq {
    CARD8 reqType ;
    BYTE alloc ;
    CARD16_BF length ;
    CARD32_BF mid ;
    CARD32_BF window ;
    CARD32_BF visual ;
} ;

+FIELD ( struct ) xCopyColormapAndFreeReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF mid ;
    CARD32_BF srcCmap ;
} ;

+FIELD ( struct ) xAllocColorReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD16_BF red, green, blue ;
} ;

+FIELD ( struct ) xAllocNamedColorReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD16_BF nbytes ;
} ;

+FIELD ( struct ) xAllocColorCellsReq {
    CARD8 reqType ;
    BOOL contiguous ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD16_BF colors, planes ;
} ;

+FIELD ( struct ) xAllocColorPlanesReq {
    CARD8 reqType ;
    BOOL contiguous ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD16_BF colors, red, green, blue ;
} ;

+FIELD ( struct ) xFreeColorsReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD32_BF planeMask ;
} ;

+FIELD ( struct ) xStoreColorsReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cmap ;
} ;

+FIELD ( struct ) xStoreNamedColorReq {
    CARD8 reqType ;
    CARD8 flags ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD32_BF pixel ;
    CARD16_BF nbytes ;
} ;

+FIELD ( struct ) xQueryColorsReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cmap ;
} ;

+FIELD ( struct ) xLookupColorReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cmap ;
    CARD16_BF nbytes ;
} ;

+FIELD ( struct ) xCreateCursorReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cid ;
    CARD32_BF source, mask ;
    CARD16_BF foreRed, foreGreen, foreBlue ;
    CARD16_BF backRed, backGreen, backBlue ;
    CARD16_BF x, y ;
} ;

+FIELD ( struct ) xCreateGlyphCursorReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cid ;
    CARD32_BF source, mask ;
    CARD16_BF sourceChar, maskChar ;
    CARD16_BF foreRed, foreGreen, foreBlue ;
    CARD16_BF backRed, backGreen, backBlue ;
} ;

+FIELD ( struct ) xRecolorCursorReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF cursor ;
    CARD16_BF foreRed, foreGreen, foreBlue ;
    CARD16_BF backRed, backGreen, backBlue ;
} ;

+FIELD ( struct ) xQueryBestSizeReq {
    CARD8 reqType ;
    CARD8 class ;
    CARD16_BF length ;
    CARD32_BF drawable ;
    CARD16_BF width, height ;
} ;

+FIELD ( struct ) xQueryExtensionReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD16_BF nbytes ;
} ;

+FIELD ( struct ) xSetModifierMappingReq {
    CARD8 reqType ;
    CARD8 numKeyPerModifier ;
    CARD16_BF length ;
} ;

+FIELD ( struct ) xSetPointerMappingReq {
    CARD8 reqType ;
    CARD8 nElts ;
    CARD16_BF length ;
} ;

+FIELD ( struct ) xGetKeyboardMappingReq {
    CARD8 reqType ;
    CARD16_BF length ;
    KeyCode firstKeyCode ;
    CARD8 count ;
} ;

+FIELD ( struct ) xChangeKeyboardMappingReq {
    CARD8 reqType ;
    CARD8 keyCodes ;
    CARD16_BF length ;
    KeyCode firstKeyCode ;
    CARD8 keySymsPerKeyCode ;
} ;

+FIELD ( struct ) xChangeKeyboardControlReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF mask ;
} ;

+FIELD ( struct ) xBellReq {
    CARD8 reqType ;
    INT8 percent ;
    CARD16_BF length ;
} ;

+FIELD ( struct ) xChangePointerControlReq {
    CARD8 reqType ;
    CARD16_BF length ;
    INT16_BF accelNum, accelDenum ;
    INT16_BF threshold ;
    BOOL doAccel, doThresh ;
} ;

+FIELD ( struct ) xSetScreenSaverReq {
    CARD8 reqType ;
    CARD16_BF length ;
    INT16_BF timeout, interval ;
    BYTE preferBlank, allowExpose ;
} ;

+FIELD ( struct ) xChangeHostsReq {
    CARD8 reqType ;
    BYTE mode ;
    CARD16_BF length ;
    CARD8 hostFamily ;
    CARD16_BF hostLength ;
} ;

+FIELD ( struct ) xListHostsReq {
    CARD8 reqType ;
    CARD16_BF length ;
} ;

+FIELD ( struct ) xChangeModeReq {
    CARD8 reqType ;
    BYTE mode ;
    CARD16_BF length ;
} ;

+TYPEDEF xChangeModeReq xSetAccessControlReq ;
+TYPEDEF xChangeModeReq xSetCloseDownModeReq ;
+TYPEDEF xChangeModeReq xForceScreenSaverReq ;

+FIELD ( struct ) xRotatePropertiesReq {
    CARD8 reqType ;
    CARD16_BF length ;
    CARD32_BF window ;
    CARD16_BF nAtoms ;
    INT16_BF nPositions ;
} ;
+FIELD ( struct ) xGenericReply {
    BYTE type ;
    BYTE data1 ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF data00 ;
    CARD32_BF data01 ;
    CARD32_BF data02 ;
    CARD32_BF data03 ;
    CARD32_BF data04 ;
    CARD32_BF data05 ;
} ;

+FIELD ( struct ) xGetWindowAttributesReply {
    BYTE type ;
    CARD8 backingStore ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF visualID ;
    CARD16_BF class ;
    CARD8 bitGravity ;
    CARD8 winGravity ;
    CARD32_BF backingBitPlanes ;
    CARD32_BF backingPixel ;
    BOOL saveUnder ;
    BOOL mapInstalled ;
    CARD8 mapState ;
    BOOL override ;
    CARD32_BF colormap ;
    CARD32_BF allEventMasks ;
    CARD32_BF yourEventMask ;
    CARD16_BF doNotPropagateMask ;
} ;

+FIELD ( struct ) xGetGeometryReply {
    BYTE type ;
    CARD8 depth ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF root ;
    INT16_BF x, y ;
    CARD16_BF width, height ;
    CARD16_BF borderWidth ;
} ;

+FIELD ( struct ) xQueryTreeReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF root, parent ;
    CARD16_BF nChildren ;
} ;

+FIELD ( struct ) xInternAtomReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF atom ;
} ;

+FIELD ( struct ) xGetAtomNameReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nameLength ;
} ;

+FIELD ( struct ) xGetPropertyReply {
    BYTE type ;
    CARD8 format ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF propertyType ;
    CARD32_BF bytesAfter ;
    CARD32_BF nItems ;
} ;

+FIELD ( struct ) xListPropertiesReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nProperties ;
} ;

+FIELD ( struct ) xGetSelectionOwnerReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF owner ;
} ;

+FIELD ( struct ) xGrabPointerReply {
    BYTE type ;
    BYTE status ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
} ;

+TYPEDEF xGrabPointerReply xGrabKeyboardReply ;

+FIELD ( struct ) xQueryPointerReply {
    BYTE type ;
    BOOL sameScreen ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF root, child ;
    INT16_BF rootX, rootY, winX, winY ;
    CARD16_BF mask ;
} ;

+FIELD ( struct ) xGetMotionEventsReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF nEvents ;
} ;

+FIELD ( struct ) xTranslateCoordsReply {
    BYTE type ;
    BOOL sameScreen ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF child ;
    INT16_BF dstX, dstY ;
} ;

+FIELD ( struct ) xGetInputFocusReply {
    BYTE type ;
    CARD8 revertTo ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF focus ;
} ;

+FIELD ( struct ) xQueryKeymapReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    BYTE map [32] ;
} ;

+FIELD ( struct ) xQueryFontReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    xCharInfo minBounds ;
    xCharInfo maxBounds ;
    CARD16_BF minCharOrByte2, maxCharOrByte2 ;
    CARD16_BF defaultChar ;
    CARD16_BF nFontProps ;
    CARD8 drawDirection ;
    CARD8 minByte1, maxByte1 ;
    BOOL allCharsExist ;
    INT16_BF fontAscent, fontDescent ;
    CARD32_BF nCharInfos ;
} ;

+FIELD ( struct ) xQueryTextExtentsReply {
    BYTE type ;
    CARD8 drawDirection ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    INT16_BF fontAscent, fontDescent ;
    INT16_BF overallAscent, overallDescent ;
    INT32_BF overallWidth, overallLeft, overallRight ;
} ;

+FIELD ( struct ) xListFontsReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nFonts ;
} ;

+FIELD ( struct ) xListFontsWithInfoReply {
    BYTE type ;
    CARD8 nameLength ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    xCharInfo minBounds ;
    xCharInfo maxBounds ;
    CARD16_BF minCharOrByte2, maxCharOrByte2 ;
    CARD16_BF defaultChar ;
    CARD16_BF nFontProps ;
    CARD8 drawDirection ;
    CARD8 minByte1, maxByte1 ;
    BOOL allCharsExist ;
    INT16_BF fontAscent, fontDescent ;
    CARD32_BF nReplies ;
} ;

+FIELD ( struct ) xGetFontPathReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nPaths ;
} ;

+FIELD ( struct ) xGetImageReply {
    BYTE type ;
    CARD8 depth ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF visual ;
} ;

+FIELD ( struct ) xListInstalledColormapsReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nColormaps ;
} ;

+FIELD ( struct ) xAllocColorReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF red, green, blue ;
    CARD32_BF pixel ;
} ;

+FIELD ( struct ) xAllocNamedColorReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF pixel ;
    CARD16_BF exactRed, exactGreen, exactBlue ;
    CARD16_BF screenRed, screenGreen, screenBlue ;
} ;

+FIELD ( struct ) xAllocColorCellsReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nPixels, nMasks ;
} ;

+FIELD ( struct ) xAllocColorPlanesReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nPixels ;
    CARD32_BF redMask, greenMask, blueMask ;
} ;

+FIELD ( struct ) xQueryColorsReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nColors ;
} ;

+FIELD ( struct ) xLookupColorReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF exactRed, exactGreen, exactBlue ;
    CARD16_BF screenRed, screenGreen, screenBlue ;
} ;

+FIELD ( struct ) xQueryBestSizeReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF width, height ;
} ;

+FIELD ( struct ) xQueryExtensionReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    BOOL present ;
    CARD8 major_opcode ;
    CARD8 first_event ;
    CARD8 first_error ;
} ;

+FIELD ( struct ) xListExtensionsReply {
    BYTE type ;
    CARD8 nExtensions ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
} ;

+FIELD ( struct ) xSetMappingReply {
    BYTE type ;
    CARD8 success ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
} ;

+TYPEDEF xSetMappingReply xSetPointerMappingReply ;
+TYPEDEF xSetMappingReply xSetModifierMappingReply ;

+FIELD ( struct ) xGetPointerMappingReply {
    BYTE type ;
    CARD8 nElts ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
} ;

+FIELD ( struct ) xGetKeyboardMappingReply {
    BYTE type ;
    CARD8 keySymsPerKeyCode ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
} ;

+FIELD ( struct ) xGetModifierMappingReply {
    BYTE type ;
    CARD8 numKeyPerModifier ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
} ;

+FIELD ( struct ) xGetKeyboardControlReply {
    BYTE type ;
    BOOL globalAutoRepeat ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD32_BF ledMask ;
    CARD8 keyClickPercent, bellPercent ;
    CARD16_BF bellPitch, bellDuration ;
    BYTE map [32] ;
} ;

+FIELD ( struct ) xGetPointerControlReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF accelNumerator, accelDenominator ;
    CARD16_BF threshold ;
} ;

+FIELD ( struct ) xGetScreenSaverReply {
    BYTE type ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF timeout, interval ;
    BOOL preferBlanking ;
    BOOL allowExposures ;
} ;

+FIELD ( struct ) xListHostsReply {
    BYTE type ;
    BOOL enabled ;
    CARD16_BF sequenceNumber ;
    CARD32_BF length ;
    CARD16_BF nHosts ;
} ;
