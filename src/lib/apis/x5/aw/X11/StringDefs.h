#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "x5/mu", "X11/StringDefs.h" ;

+CONST String XtNallowOff, XtNallowResize ;
+CONST String XtNautoFill, XtNautoReconfigure, XtNbackgroundStipple ;
+CONST String XtNbetweenCursor, XtNbottom, XtNbottomMargin ;
+CONST String XtNcanvasHeight, XtNcanvasWidth, XtNcolumnSpacing ;
+CONST String XtNcolumnWidth, XtNcornerRoundPercent, XtNcursor ;
+CONST String XtNcursorName, XtNdataCompression, XtNdecay ;
+CONST String XtNdefaultColumns, XtNdefaultDistance, XtNdefaultScale ;
+CONST String XtNdialogHOffset, XtNdialogVOffset, XtNdisplayCaret ;
+CONST String XtNdisplayNonprinting, XtNdisplayPosition, XtNecho ;
+CONST String XtNencoding, XtNflash ;
+CONST String XtNforceColumns, XtNfromHoriz, XtNfromVert ;
+CONST String XtNgetValue, XtNgravity, XtNgripCursor, XtNgripIndent ;
+CONST String XtNgripTranslations ;
+CONST String XtNhighlightThickness, XtNhorizDistance ;
+CONST String XtNhorizontalBetweenCursor, XtNhorizontalGripCursor ;
+CONST String XtNicon, XtNinitialDelay, XtNinsensitiveBorder ;
+CONST String XtNinternalBorderColor ;
+CONST String XtNinternalBorderWidth, XtNinternalSpace ;
+CONST String XtNjumpScroll, XtNlabelClass ;
+CONST String XtNleft, XtNleftBitmap, XtNleftCursor, XtNleftMargin ;
+CONST String XtNlineWidth, XtNlist, XtNlongest, XtNlowerCursor ;
+CONST String XtNmax, XtNmenuName, XtNmenuOnScreen, XtNmin, XtNminScale ;
+CONST String XtNminimumDelay, XtNminimumThumb, XtNnumberStrings ;
+CONST String XtNpasteBuffer, XtNpieceSize, XtNpopupOnEntry, XtNposition ;
+CONST String XtNpreferredPaneSize, XtNradioData, XtNradioGroup ;
+CONST String XtNrefigureMode, XtNrepeatDelay, XtNresizable ;
+CONST String XtNresizeToPreferred, XtNright, XtNrightBitmap ;
+CONST String XtNrightCursor, XtNrightMargin, XtNrowHeight, XtNrowSpacing ;
+CONST String XtNrubberBand, XtNscale, XtNscrollHorizontal ;
+CONST String XtNscrollVertical, XtNselectTypes ;
+CONST String XtNshadowColor, XtNshadowThickness, XtNshapeStyle ;
+CONST String XtNshowGrip, XtNskipAdjust, XtNsliderHeight, XtNsliderWidth ;
+CONST String XtNsliderX, XtNsliderY, XtNstartCallback, XtNstate ;
+CONST String XtNstipple, XtNstopCallback, XtNtopMargin ;
+CONST String XtNtopOfThumb, XtNtreeGC, XtNtreeParent, XtNtype ;
+CONST String XtNupperCursor, XtNuseStringInPlace,XtNvertDistance ;
+CONST String XtNvertSpace, XtNverticalBetweenCursor ;
+CONST String XtNverticalGripCursor, XtNverticalList, XtNwrap ;

+CONST String XtCAllowOff, XtCAutoFill, XtCAutoReconfigure ;
+CONST String XtCBackgroundStipple, XtCCanvasHeight ;
+CONST String XtCCanvasWidth, XtCColumnWidth, XtCColumns ;
+CONST String XtCCornerRoundPercent, XtCDataCompression, XtCDecay ;
+CONST String XtCDefaultScale, XtCDelay, XtCEdge, XtCEncoding ;
+CONST String XtCGravity, XtCGripIndent, XtCHorizontalMargins ;
+CONST String XtCIcon, XtCInsensitive, XtCInternalSpace, XtCJumpScroll ;
+CONST String XtCLabelClass, XtCLeftBitmap, XtCLineWidth, XtCList ;
+CONST String XtCLongest, XtCMax, XtCMenuName, XtCMenuOnScreen, XtCMin ;
+CONST String XtCMinimumDelay, XtCMinimumThumb, XtCNumberStrings ;
+CONST String XtCOutput, XtCPieceSize, XtCPopupOnEntry ;
+CONST String XtCPreferredPaneSize, XtCRadioData, XtCRadioGroup ;
+CONST String XtCRightBitmap, XtCRowHeight, XtCRubberBand ;
+CONST String XtCScale, XtCScroll, XtCSelectTypes, XtCShadowColor ;
+CONST String XtCShadowThickness, XtCShapeStyle, XtCShowGrip, XtCShown ;
+CONST String XtCSliderHeight, XtCSliderWidth, XtCSliderX, XtCSliderY ;
+CONST String XtCSpacing, XtCStartCallback, XtCState, XtCStipple ;
+CONST String XtCStopCallback, XtCTopOfThumb, XtCTreeGC, XtCTreeParent ;
+CONST String XtCType, XtCUseStringInPlace, XtCVertSpace ;
+CONST String XtCVerticalMargins, XtCWidget, XtCWrap ;

+CONST String XtRAsciiType, XtREdgeType, XtRGC, XtRResizeMode ;
+CONST String XtRScrollMode, XtRWrapMode ;

+CONST String XtEfile, XtEstring, XtEtextResizeBoth, XtEtextResizeHeight ;
+CONST String XtEtextResizeNever, XtEtextResizeWidth, XtEtextScrollAlways ;
+CONST String XtEtextScrollNever, XtEtextScrollWhenNeeded, XtEtextWrapLine ;
+CONST String XtEtextWrapNever, XtEtextWrapWord ;
