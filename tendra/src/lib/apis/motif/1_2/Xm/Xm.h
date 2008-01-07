/*
    COPYRIGHT NOTICE

    This program is the proprietary property of the Secretary of State
    for Defence (United Kingdom) acting through the Defence Research
    Agency (DRA).  Use, reproduction, production of amended versions
    and/or transfer of this program is permitted PROVIDED THAT:

    (a)	 This legend be preserved on any such reproduction and amended
	 version.

    (b)	 Any amended version of this program be clearly marked to show
	 the nature of the amendment and the name of the amending
	 organisation.

    (c)	 Any recipient of such reproduction or amended version accept
	 the conditions set out in this legend.

    The DRA accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Crown Copyright (c) 1994.
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


/* SCO CID (IXI) Xm.h,v 1.1 1996/08/08 14:13:59 wendland Exp */

+USE "x5/t", "X11/Intrinsic.h";
+USE "x5/lib", "X11/Xatom.h";
+USE "motif/1_2", "Xm/XmStrDefs.h";
+USE "motif/1_2", "Xm/VirtKeys.h";

%%
#define XmVERSION 1
#define XmREVISION 2
#define XmUPDATE_LEVEL 5
#define XmVersion (XmVERSION * 1000 + XmREVISION)
%%

+CONST int xmUseVersion;

/* was in both LabelP.h and SelectioBP.h which clashes */
/* +CONST int XmUNSPECIFIED; */

+CONST int XmUNSPECIFIED_PIXMAP ;

+CONST String XmSTRING_ISO8859_1 ;
+CONST String XmSTRING_OS_CHARSET ;
+CONST String XmFALLBACK_CHARSET ;

+ENUM XmFontType := {XmFONT_IS_FONT, XmFONT_IS_FONTSET};

/*
 *	This is an anonymous enum (with a weird default).  Is there
 *	a better way?
 */

+CONST int XmSTRING_DIRECTION_L_TO_R ;
+CONST int XmSTRING_DIRECTION_R_TO_L ;
+CONST int XmSTRING_DIRECTION_DEFAULT ;

+TYPE XmString;
+TYPEDEF XmString *XmStringTable;
+TYPEDEF char *XmStringCharSet;
+TYPEDEF unsigned char XmStringComponentType;
+TYPEDEF unsigned char XmStringDirection;

/* 
** opaque types, not defined anywhere.
*/
+TYPE ~XmFontListRec;
+TYPE (struct) ~XmStringContextRec;
+TYPE (struct) ~XmStringRec;
+TYPE (struct) ~XmtStringContextRec;
+TYPE (struct) ~XmFontListContextRec;
+TYPEDEF ~XmFontListRec *XmFontList;
+TYPEDEF ~XmFontListRec *XmFontListEntry;
+TYPEDEF ~XmStringContextRec *_XmStringContext;
+TYPEDEF ~XmStringRec *_XmString;
+TYPEDEF ~XmtStringContextRec *XmStringContext;
+TYPEDEF ~XmFontListContextRec *XmFontContext;



/*
 *	This is an anonymouse enum.
 */

+CONST int XmSTRING_COMPONENT_UNKNOWN ;
+CONST int XmSTRING_COMPONENT_CHARSET ;
+CONST int XmSTRING_COMPONENT_TEXT ;
+CONST int XmSTRING_COMPONENT_DIRECTION ;
+CONST int XmSTRING_COMPONENT_SEPARATOR;
#+CONST int XmSTRING_COMPONENT_FONTLIST_ELEMENT_TAG;
+CONST int XmSTRING_COMPONENT_LOCALE_TEXT;
#+CONST int XmSTRING_COMPONENT_TAG;

+CONST int XmSTRING_COMPONENT_END;

+CONST int XmSTRING_COMPONENT_USER_BEGIN;
+CONST int XmSTRING_COMPONENT_USER_END ;
%%
#define XmSTRING_DEFAULT_CHARSET ""
#define XmFONTLIST_DEFAULT_TAG ""
%%




+EXP lvalue WidgetClass xmPrimitiveWidgetClass;

+TYPE struct _XmPrimitiveClassRec;
+TYPE struct _XmPrimitiveRec;
+TYPEDEF struct _XmPrimitiveClassRec * XmPrimitiveWidgetClass;
+TYPEDEF struct _XmPrimitiveRec * XmPrimitiveWidget;



+EXP lvalue WidgetClass xmGadgetClass;

+TYPE struct _XmGadgetClassRec;
+TYPE struct _XmGadgetRec;
+TYPEDEF struct _XmGadgetClassRec * XmGadgetClass;
+TYPEDEF struct _XmGadgetRec * XmGadget;




+EXP lvalue WidgetClass xmManagerWidgetClass;

+TYPE struct _XmManagerClassRec;
+TYPE struct _XmManagerRec;
+TYPEDEF struct _XmManagerClassRec * XmManagerWidgetClass;
+TYPEDEF struct _XmManagerRec * XmManagerWidget;


+MACRO Boolean XmIsPrimitive(Widget w);
+MACRO Boolean XmIsGadget(Widget w);
+MACRO Boolean XmIsManager(Widget w);


#+CONST String XmNforeground ;
#+CONST String XmCForeground ;

+CONST String XmRPrimForegroundPixmap ;

+CONST String XmRManForegroundPixmap ;

+CONST String XmCBackgroundPixmap ;
+CONST String XmRBackgroundPixmap ;

+CONST String XmNtraversalOn ;
+CONST String XmCTraversalOn ;

+CONST String XmNhighlightOnEnter ;
+CONST String XmCHighlightOnEnter ;

+CONST String XmNsizePolicy ;
+CONST String XmCSizePolicy ;
+CONST String XmRSizePolicy ;

+CONST String XmNhighlightThickness ;
+CONST String XmCHighlightThickness ;

+CONST String XmNhighlightColor ;
+CONST String XmCHighlightColor ;

+CONST String XmNhighlightPixmap ;
+CONST String XmCHighlightPixmap ;
+CONST String XmRPrimHighlightPixmap ;

+CONST String XmNshadowThickness ;
+CONST String XmCShadowThickness ;

+CONST String XmNtopShadowColor ;
+CONST String XmCTopShadowColor ;

+CONST String XmNtopShadowPixmap ;
+CONST String XmCTopShadowPixmap ;
+CONST String XmRPrimTopShadowPixmap ;

+CONST String XmNbottomShadowColor ;
+CONST String XmCBottomShadowColor ;

+CONST String XmNbottomShadowPixmap ;
+CONST String XmCBottomShadowPixmap ;
+CONST String XmRPrimBottomShadowPixmap ;

+CONST String XmNunitType ;
+CONST String XmCUnitType ;
+CONST String XmRUnitType ;

+CONST String XmNhelpCallback ;
+CONST String XmNuserData ;
+CONST String XmCUserData ;


/*
 *	anonymous enum
 */

+CONST int XmCHANGE_ALL ;
+CONST int XmCHANGE_NONE ;
+CONST int XmCHANGE_WIDTH ;
+CONST int XmCHANGE_HEIGHT ;

+CONST int XmBELL;

+CONST String XmRManTopShadowPixmap ;
+CONST String XmRManBottomShadowPixmap ;
+CONST String XmRManHighlightPixmap ;

+CONST String XmNchildPosition ;




+CONST int XmNO_ORIENTATION ;
+CONST int XmVERTICAL ;
+CONST int XmHORIZONTAL ;

+CONST int XmWORK_AREA ;
+CONST int XmMENU_BAR ;
+CONST int XmMENU_PULLDOWN ;
+CONST int XmMENU_POPUP ;
+CONST int XmMENU_OPTION ;

+CONST int XmNO_PACKING ;
+CONST int XmPACK_TIGHT ;
+CONST int XmPACK_COLUMN ;
+CONST int XmPACK_NONE ;



+CONST int XmALIGNMENT_BEGINNING ;
+CONST int XmALIGNMENT_CENTER ;
+CONST int XmALIGNMENT_END ;

+CONST int XmALIGNMENT_CONTENTS_TOP;
+CONST int XmALIGNMENT_CONTENTS_BOTTOM;

+CONST int XmALIGNMENT_BASELINE_TOP;
+CONST int XmALIGNMENT_BASELINE_BOTTOM;
#+CONST int XmALIGNMENT_BASELINE;
+CONST int XmALIGNMENT_WIDGET_TOP;
+CONST int XmALIGNMENT_WIDGET_BOTTOM;

+CONST int XmFRAME_TITLE_CHILD;
+CONST int XmFRAME_WORKAREA_CHILD;
+CONST int XmFRAME_GENERIC_CHILD;

+CONST int XmTEAR_OFF_ENABLED;
+CONST int XmTEAR_OFF_DISABLED;

+CONST int XmUNPOST;
+CONST int XmUNPOST_AND_REPLAY;

+CONST int XmLAST_POSITION;
+CONST int XmFIRST_POSITION;

+CONST int XmN_OF_MANY ;
+CONST int XmONE_OF_MANY ;


+CONST String XmNhorizontalSpacing ;
+CONST String XmNverticalSpacing ;

+CONST String XmNfractionBase ;
+CONST String XmCMaxValue ;

+CONST String XmNrubberPositioning ;
+CONST String XmCRubberPositioning ;

+CONST String XmNresizePolicy ;
+CONST String XmCResizePolicy ;
+CONST String XmRResizePolicy ;



+CONST String XmNtopAttachment ;
+CONST String XmNbottomAttachment ;
+CONST String XmNleftAttachment ;
+CONST String XmNrightAttachment ;
+CONST String XmCAttachment ;
+CONST String XmRAttachment ;

+CONST String XmNtopWidget ;
+CONST String XmNbottomWidget ;
+CONST String XmNleftWidget ;
+CONST String XmNrightWidget ;
+CONST String XmCWidget ;

+CONST String XmNtopPosition ;
+CONST String XmNbottomPosition ;
+CONST String XmNleftPosition ;
+CONST String XmNrightPosition ;
+CONST String XmNtopOffset ;
+CONST String XmNbottomOffset ;
+CONST String XmNleftOffset ;
+CONST String XmNrightOffset ;
+CONST String XmCOffset ;

+CONST String XmNresizable ;



+CONST int XmATTACH_NONE ;
+CONST int XmATTACH_FORM ;
+CONST int XmATTACH_OPPOSITE_FORM ;
+CONST int XmATTACH_WIDGET ;
+CONST int XmATTACH_OPPOSITE_WIDGET ;
+CONST int XmATTACH_POSITION ;
+CONST int XmATTACH_SELF ;

+CONST int XmRESIZE_ANY ;
+CONST int XmRESIZE_NONE ;
+CONST int XmRESIZE_GROW ;




+CONST int XmCR_NONE ;
+CONST int XmCR_HELP ;
+CONST int XmCR_VALUE_CHANGED ;
+CONST int XmCR_INCREMENT ;
+CONST int XmCR_DECREMENT ;
+CONST int XmCR_PAGE_INCREMENT ;
+CONST int XmCR_PAGE_DECREMENT ;
+CONST int XmCR_TO_TOP ;
+CONST int XmCR_TO_BOTTOM ;
+CONST int XmCR_DRAG ;
+CONST int XmCR_ACTIVATE ;
+CONST int XmCR_ARM ;
+CONST int XmCR_DISARM ;
+CONST int XmCR_MAP ;
+CONST int XmCR_UNMAP ;
+CONST int XmCR_FOCUS ;
+CONST int XmCR_LOSING_FOCUS ;
+CONST int XmCR_MODIFYING_TEXT_VALUE ;
+CONST int XmCR_MOVING_INSERT_CURSOR ;
+CONST int XmCR_EXECUTE ;
+CONST int XmCR_SINGLE_SELECT ;
+CONST int XmCR_MULTIPLE_SELECT ;
+CONST int XmCR_EXTENDED_SELECT ;
+CONST int XmCR_BROWSE_SELECT ;
+CONST int XmCR_DEFAULT_ACTION ;
+CONST int XmCR_CLIPBOARD_DATA_REQUEST ;
+CONST int XmCR_CLIPBOARD_DATA_DELETE ;
+CONST int XmCR_CASCADING ;
+CONST int XmCR_OK ;
+CONST int XmCR_CANCEL ;
+CONST int XmCR_APPLY ;
+CONST int XmCR_NO_MATCH ;
+CONST int XmCR_COMMAND_ENTERED ;
+CONST int XmCR_COMMAND_CHANGED ;
+CONST int XmCR_EXPOSE ;
+CONST int XmCR_RESIZE ;
+CONST int XmCR_INPUT ;
+CONST int XmCR_GAIN_PRIMARY ;
+CONST int XmCR_LOSE_PRIMARY ;
+CONST int XmCR_CREATE ;
+CONST int XmCR_TEAR_OFF_ACTIVATE;
+CONST int XmCR_TEAR_OFF_DEACTIVATE;
+CONST int XmCR_OBSCURED_TRAVERSAL;
#+CONST int XmCR_PROTOCOLS;

+TYPE (struct) XmAnyCallbackStruct;
+FIELD XmAnyCallbackStruct
{
    int     reason;
    XEvent  *event;
};

+TYPE (struct) XmArrowButtonCallbackStruct;
+FIELD XmArrowButtonCallbackStruct
{
    int     reason;
    XEvent  *event;
    int	    click_count;
};

+TYPE (struct) XmDrawingAreaCallbackStruct;
+FIELD XmDrawingAreaCallbackStruct
{
    int     reason;
    XEvent  *event;
    Window  window;
};

+TYPE (struct) XmDrawnButtonCallbackStruct;
+FIELD XmDrawnButtonCallbackStruct
{
    int     reason;
    XEvent  *event;
    Window  window;
    int	    click_count;
};

+TYPE (struct) XmPushButtonCallbackStruct;
+FIELD XmPushButtonCallbackStruct
{
    int     reason;
    XEvent  *event;
    int	    click_count;
};

+TYPE (struct) XmRowColumnCallbackStruct;
+FIELD XmRowColumnCallbackStruct
{
    int     reason;
    XEvent  *event;
    Widget  widget;
    char    *data;
    char    *callbackstruct;
};

+TYPE (struct) XmScrollBarCallbackStruct;
+FIELD XmScrollBarCallbackStruct
{
   int reason;
   XEvent * event;
   int value;
   int pixel;
};

+TYPE (struct) XmToggleButtonCallbackStruct;
+FIELD XmToggleButtonCallbackStruct
{
   int reason;
   XEvent * event;
   int set;
};

+TYPE (struct) XmListCallbackStruct;
+FIELD XmListCallbackStruct
{
   int 	     reason;
   XEvent    *event;
   XmString  item;
   int       item_length;
   int       item_position;
   XmString  *selected_items;
   int       selected_item_count;
   int       *selected_item_positions;
   char      selection_type;
};

+TYPE (struct) XmSelectionBoxCallbackStruct;
+FIELD XmSelectionBoxCallbackStruct
{
    int reason;
    XEvent	*event;
    XmString	value;
    int		length;
};

+TYPE (struct) XmCommandCallbackStruct;
+FIELD XmCommandCallbackStruct
{
    int reason;
    XEvent	*event;
    XmString	value;
    int		length;
};

+TYPE (struct) XmFileSelectionBoxCallbackStruct;
+FIELD XmFileSelectionBoxCallbackStruct
{
    int 	reason;
    XEvent	*event;
    XmString	value;
    int		length;
    XmString	mask;
    int		mask_length;
    XmString	dir ;
    int		dir_length ;
    XmString    pattern ;
    int		pattern_length ;
};


+TYPE (struct) XmScaleCallbackStruct;
+FIELD XmScaleCallbackStruct
{
   int reason;
   XEvent * event;
   int value;
};




+CONST String XmNfillOnArm ;
+CONST String XmCFillOnArm ;

+CONST String XmNarmColor ;
+CONST String XmCArmColor ;

+CONST String XmNarmPixmap ;
+CONST String XmCArmPixmap ;

+CONST String XmNshowAsDefault ;
+CONST String XmCShowAsDefault ;
+CONST String XmRBooleanDimension ;

+CONST String XmNdefaultButtonShadowThickness ;
+CONST String XmCDefaultButtonShadowThickness ;

+CONST String XmNmultiClick ;
+CONST String XmCMultiClick ;
+CONST String XmRMultiClick ;

+CONST int XmMULTICLICK_DISCARD ;
+CONST int XmMULTICLICK_KEEP ;


+CONST String XmNpushButtonEnabled ;
+CONST String XmCPushButtonEnabled ;

+CONST String XmNshadowType ;
+CONST String XmCShadowType ;
+CONST String XmRShadowType ;

+CONST int XmSHADOW_IN ;
+CONST int XmSHADOW_OUT ;


+CONST String XmNarrowDirection ;
+CONST String XmCArrowDirection ;
+CONST String XmRArrowDirection ;

+CONST String XmNactivateCallback ;
#+CONST String XmNhelpCallback ;

+CONST int XmARROW_UP ;
+CONST int XmARROW_DOWN ;
+CONST int XmARROW_LEFT ;
+CONST int XmARROW_RIGHT ;




+CONST String XmNmargin ;

+CONST String XmNseparatorType ;
+CONST String XmCSeparatorType ;
+CONST String XmRSeparatorType ;

+CONST int XmNO_LINE ;
+CONST int XmSINGLE_LINE ;
+CONST int XmDOUBLE_LINE ;
+CONST int XmSINGLE_DASHED_LINE ;
+CONST int XmDOUBLE_DASHED_LINE ;
+CONST int XmSHADOW_ETCHED_IN ;
+CONST int XmSHADOW_ETCHED_OUT ;
+CONST int XmSHADOW_ETCHED_IN_DASH;
+CONST int XmSHADOW_ETCHED_OUT_DASH;
+CONST int XmINVALID_SEPARATOR_TYPE;

+CONST int XmPIXMAP ;
+CONST int XmSTRING ;





+CONST String XmNminimum ;
+CONST String XmCMinimum ;

+CONST String XmNmaximum ;
+CONST String XmCMaximum ;

+CONST String XmNsliderSize ;
+CONST String XmCSliderSize ;

+CONST String XmNshowArrows ;
+CONST String XmCShowArrows ;

+CONST String XmNprocessingDirection ;
+CONST String XmCProcessingDirection ;
+CONST String XmRProcessingDirection ;

+CONST String XmNincrement ;
+CONST String XmCIncrement ;
+CONST String XmNpageIncrement ;
+CONST String XmCPageIncrement ;

+CONST String XmNinitialDelay ;
+CONST String XmCInitialDelay ;
+CONST String XmNrepeatDelay ;
+CONST String XmCRepeatDelay ;

+CONST String XmNvalueChangedCallback ;
+CONST String XmNincrementCallback ;
+CONST String XmNdecrementCallback ;
+CONST String XmNpageIncrementCallback ;
+CONST String XmNpageDecrementCallback ;
+CONST String XmNtoTopCallback ;
+CONST String XmNtoBottomCallback ;
+CONST String XmNdragCallback ;



+CONST int XmMAX_ON_TOP ;
+CONST int XmMAX_ON_BOTTOM ;
+CONST int XmMAX_ON_LEFT ;
+CONST int XmMAX_ON_RIGHT ;




+CONST String XmNlistSpacing ;
+CONST String XmCListSpacing ;
+CONST String XmRListSpacing ;

+CONST String XmNlistMarginWidth ;
+CONST String XmCListMarginWidth ;
+CONST String XmRListMarginWidth ;

+CONST String XmNlistMarginHeight ;
+CONST String XmCListMarginHeight ;
+CONST String XmRListMarginHeight ;

+CONST String XmNitems ;
+CONST String XmCItems ;
+CONST String XmRItems ;

+CONST String XmNitemCount ;
+CONST String XmCItemCount ;
+CONST String XmRItemCount ;

+CONST String XmNselectedItems ;
+CONST String XmCSelectedItems ;
+CONST String XmRSelectedItems ;

+CONST String XmNselectedItemCount ;
+CONST String XmCSelectedItemCount ;
+CONST String XmRSelectedItemCount ;

+CONST String XmNvisibleItemCount ;
+CONST String XmCVisibleItemCount ;
+CONST String XmRVisibleItemCount ;

+CONST String XmNselectionPolicy ;
+CONST String XmCSelectionPolicy ;
+CONST String XmRSelectionPolicy ;

+CONST String XmNlistSizePolicy ;
+CONST String XmCListSizePolicy ;
+CONST String XmRListSizePolicy ;

+CONST String XmNdoubleClickInterval ;
+CONST String XmCDoubleClickInterval ;
+CONST String XmRDoubleClickInterval ;

+CONST String XmNsingleSelectionCallback ;
+CONST String XmNmultipleSelectionCallback ;
+CONST String XmNextendedSelectionCallback ;
+CONST String XmNbrowseSelectionCallback ;
+CONST String XmNdefaultActionCallback ;

+CONST String XmNautomaticSelection ;
+CONST String XmCAutomaticSelection ;

+CONST String XmNtopItemPosition ;
+CONST String XmCTopItemPosition ;

+CONST int XmSINGLE_SELECT ;
+CONST int XmMULTIPLE_SELECT ;
+CONST int XmEXTENDED_SELECT ;
+CONST int XmBROWSE_SELECT ;

+CONST int XmSTATIC ;
+CONST int XmDYNAMIC ;

+CONST String XmNhorizontalScrollBar ;
+CONST String XmCHorizontalScrollBar ;

+CONST String XmNverticalScrollBar ;
+CONST String XmCVerticalScrollBar ;

+CONST String XmNworkWindow ;
+CONST String XmCWorkWindow ;

+CONST String XmNclipWindow ;
+CONST String XmCClipWindow ;

+CONST String XmNscrollingPolicy ;
+CONST String XmCScrollingPolicy ;
+CONST String XmRScrollingPolicy ;

+CONST String XmNvisualPolicy ;
+CONST String XmCVisualPolicy ;
+CONST String XmRVisualPolicy ;

+CONST String XmNscrollBarDisplayPolicy ;
+CONST String XmCScrollBarDisplayPolicy ;
+CONST String XmRScrollBarDisplayPolicy ;

+CONST String XmNscrollBarPlacement ;
+CONST String XmCScrollBarPlacement ;
+CONST String XmRScrollBarPlacement ;

+CONST String XmNupdateSliderSize ;
+CONST String XmCUpdateSliderSize ;

+CONST String XmNscrolledWindowMarginHeight ;
+CONST String XmCScrolledWindowMarginHeight ;

+CONST String XmNscrolledWindowMarginWidth ;
+CONST String XmCScrolledWindowMarginWidth ;


+CONST int XmVARIABLE ;
+CONST int XmCONSTANT ;
+CONST int XmRESIZE_IF_POSSIBLE ;

+CONST int XmAUTOMATIC ;
+CONST int XmAPPLICATION_DEFINED ;

+CONST int XmAS_NEEDED ;

+CONST int SW_TOP ;
+CONST int SW_BOTTOM ;
+CONST int SW_LEFT ;
+CONST int SW_RIGHT ;
%%
#define XmTOP_LEFT (SW_TOP | SW_LEFT)
#define XmBOTTOM_LEFT (SW_BOTTOM | SW_LEFT)
#define XmTOP_RIGHT (SW_TOP | SW_RIGHT)
#define XmBOTTOM_RIGHT (SW_BOTTOM | SW_RIGHT)
%%


+CONST String XmNcommandWindow ;
+CONST String XmCCommandWindow ;
+CONST String XmNmenuBar ;
+CONST String XmCMenuBar ;
+CONST String XmNmessageWindow ;
+CONST String XmCMessageWindow ;
+CONST String XmNmainWindowMarginHeight ;
+CONST String XmCMainWindowMarginHeight ;
+CONST String XmNmainWindowMarginWidth ;
+CONST String XmCMainWindowMarginWidth ;
+CONST String XmNshowSeparator ;
+CONST String XmCShowSeparator ;

+CONST int XmCOMMAND_ABOVE_WORKSPACE ;
+CONST int XmCOMMAND_BELOW_WORKSPACE ;


+CONST String XmNsource ;
+CONST String XmCSource ;

+CONST String XmNoutputCreate ;
+CONST String XmCOutputCreate ;

+CONST String XmNinputCreate ;
+CONST String XmCInputCreate ;

+CONST String XmNautoShowCursorPosition ;
+CONST String XmCAutoShowCursorPosition ;

+CONST String XmNcursorPosition ;
+CONST String XmCCursorPosition ;

+CONST String XmNeditable ;
+CONST String XmCEditable ;

+CONST String XmNmaxLength ;
+CONST String XmCMaxLength ;

+CONST String XmNfocusCallback ;
+CONST String XmNlosingFocusCallback ;
+CONST String XmNmodifyVerifyCallback ;
+CONST String XmNmotionVerifyCallback ;
+CONST String XmNgainPrimaryCallback ;
+CONST String XmNlosePrimaryCallback ;

+CONST String XmNverifyBell ;
+CONST String XmCVerifyBell ;

+CONST String XmNwordWrap ;
+CONST String XmCWordWrap ;

+CONST String XmNblinkRate ;
+CONST String XmCBlinkRate ;

+CONST String XmNresizeWidth ;
+CONST String XmCResizeWidth ;

+CONST String XmNresizeHeight ;
+CONST String XmCResizeHeight ;

+CONST String XmNscrollHorizontal ;
+CONST String XmNscrollVertical ;
+CONST String XmCScroll ;

+CONST String XmNscrollLeftSide ;
+CONST String XmNscrollTopSide ;
+CONST String XmCScrollSide ;

+CONST String XmNcursorPositionVisible ;
+CONST String XmCCursorPositionVisible ;

+CONST String XmNtoPositionCallback ;

+CONST String XmNcolumns ;
+CONST String XmCColumns ;

+CONST String XmNrows ;
+CONST String XmCRows ;

+CONST String XmNselectThreshold ;
+CONST String XmCSelectThreshold ;

+CONST String XmNselectionArrayCount ;
+CONST String XmCSelectionArrayCount ;

+CONST String XmNpendingDelete ;
+CONST String XmCPendingDelete ;

+CONST String XmNeditMode ;
+CONST String XmCEditMode ;

+CONST int XmMULTI_LINE_EDIT ;
+CONST int XmSINGLE_LINE_EDIT ;

+ENUM XmTextDirection := {XmTEXT_FORWARD, XmTEXT_BACKWARD};

+TYPEDEF long XmTextPosition;
+TYPEDEF Atom XmTextFormat;

+CONST Atom XmFMT_8_BIT;
+CONST Atom XmFMT_16_BIT; 

+ENUM XmTextScanType:= { XmSELECT_POSITION, XmSELECT_WHITESPACE, XmSELECT_WORD,
               XmSELECT_LINE, XmSELECT_ALL, XmSELECT_PARAGRAPH };

+ENUM XmHighlightMode:= {XmHIGHLIGHT_NORMAL, XmHIGHLIGHT_SELECTED,
	      XmHIGHLIGHT_SECONDARY_SELECTED};


+TYPE (struct) XmTextBlockRec;
+FIELD XmTextBlockRec {
  char *ptr;
  int length;
  XmTextFormat format;
};

+TYPEDEF XmTextBlockRec *XmTextBlock;


+TYPE (struct) XmTextVerifyCallbackStruct;
+FIELD XmTextVerifyCallbackStruct
{
    int reason;
    XEvent  *event;
    Boolean doit;
    XmTextPosition currInsert, newInsert;
    XmTextPosition startPos, endPos;
    XmTextBlock text;
};

+TYPEDEF XmTextVerifyCallbackStruct *XmTextVerifyPtr;

+TYPE (struct) XmTextBlockRecWcs;
+FIELD XmTextBlockRecWcs
{
	wchar_t *wcsptr;
	int length;
};

+TYPEDEF XmTextBlockRecWcs *XmTextBlockWcs;

+TYPE (struct) XmTextVerifyCallbackStructWcs;
+FIELD XmTextVerifyCallbackStructWcs
{
	int reason;
	XEvent *event;
	Boolean doit;
	XmTextPosition currInsert, newInsert;
	XmTextPosition startPos, endPos;
	XmTextBlockWcs text;
};

+TYPEDEF XmTextVerifyCallbackStructWcs *XmTextVerifyPtrWcs;

+CONST String XmNtopCharacter ;

#+CONST String XmGetTopPosition ;
#+CONST String XmSetTopPosition ;

+CONST int XmCOPY_FAILED;
+CONST int XmCOPY_SUCCEEDED;
+CONST int XmCOPY_TRUNCATED;

+CONST String XmNrefigureMode ;

+CONST String XmNseparatorOn ;
+CONST String XmCSeparatorOn ;

+CONST String XmNsashIndent ;
+CONST String XmCSashIndent ;

+CONST String XmNsashWidth ;
+CONST String XmCSashWidth ;

+CONST String XmNsashHeight ;
+CONST String XmCSashHeight ;

+CONST String XmNsashShadowThickness ;



+CONST String XmNallowResize ;
+CONST String XmNskipAdjust ;
+CONST String XmNpaneMinimum ;
+CONST String XmNpaneMaximum ;

+CONST String XmCPaneMinimum ;
+CONST String XmCPaneMaximum ;




+CONST String XmNinputCallback ;



+CONST int XmDIALOG_APPLY_BUTTON ;
+CONST int XmDIALOG_CANCEL_BUTTON ;
+CONST int XmDIALOG_DEFAULT_BUTTON ;
+CONST int XmDIALOG_OK_BUTTON ;
+CONST int XmDIALOG_FILTER_LABEL ;
+CONST int XmDIALOG_FILTER_TEXT ;
+CONST int XmDIALOG_HELP_BUTTON ;
+CONST int XmDIALOG_LIST ;
+CONST int XmDIALOG_HISTORY_LIST ;
+CONST int XmDIALOG_LIST_LABEL ;
+CONST int XmDIALOG_MESSAGE_LABEL ;
+CONST int XmDIALOG_SELECTION_LABEL ;
+CONST int XmDIALOG_PROMPT_LABEL;
+CONST int XmDIALOG_SYMBOL_LABEL ;
+CONST int XmDIALOG_TEXT ;
+CONST int XmDIALOG_VALUE_TEXT ;
+CONST int XmDIALOG_COMMAND_TEXT ;
+CONST int XmDIALOG_SEPARATOR ;
+CONST int XmDIALOG_DIR_LIST ;
+CONST int XmDIALOG_DIR_LIST_LABEL ;
+CONST int XmDIALOG_FILE_LIST ;
+CONST int XmDIALOG_FILE_LIST_LABEL ;

+CONST String XmNokCallback ;
+CONST String XmNcancelCallback ;
+CONST String XmNapplyCallback ;
+CONST String XmNnoMatchCallback ;
+CONST String XmNcommandEnteredCallback ;
+CONST String XmNcommandChangedCallback ;


+CONST String XmNokLabelString ;
+CONST String XmNcancelLabelString ;
+CONST String XmNhelpLabelString ;
+CONST String XmNapplyLabelString ;
+CONST String XmNselectionLabelString ;
+CONST String XmNlistLabelString ;
+CONST String XmNpromptString ;


+CONST String XmCOkLabelString ;
+CONST String XmCCancelLabelString ;
+CONST String XmCHelpLabelString ;
+CONST String XmCApplyLabelString ;
+CONST String XmCSelectionLabelString ;
+CONST String XmCListLabelString ;
+CONST String XmCPromptString ;

+CONST String XmNdefaultButton ;
+CONST String XmNcancelButton ;

+CONST String XmNbuttonFontList ;
+CONST String XmCButtonFontList ;
+CONST String XmNlabelFontList ;
+CONST String XmCLabelFontList ;
+CONST String XmNtextFontList ;
+CONST String XmCTextFontList ;

+CONST String XmNtextTranslations ;

+CONST String XmNallowOverlap ;
+CONST String XmCAllowOverlap ;

+CONST String XmNdefaultPosition ;
+CONST String XmCDefaultPosition ;

+CONST String XmNautoUnmanage ;
+CONST String XmCAutoUnmanage ;

+CONST String XmNdialogTitle ;
+CONST String XmCDialogTitle ;

+CONST String XmNnoResize ;
+CONST String XmCNoResize ;

+CONST String XmNdialogStyle ;
+CONST String XmCDialogStyle ;
+CONST String XmRDialogStyle ;

+CONST int XmDIALOG_MODELESS ;
+CONST int XmDIALOG_PRIMARY_APPLICATION_MODAL ;
+CONST int XmDIALOG_FULL_APPLICATION_MODAL ;
+CONST int XmDIALOG_SYSTEM_MODAL ;

+CONST int XmDIALOG_APPLICATION_MODAL ;

+CONST int XmPLACE_TOP;
+CONST int XmPLACE_ABOVE_SELECTION;
+CONST int XmPLACE_BELOW_SELECTION;

+CONST String XmNmustMatch ;
+CONST String XmCMustMatch ;
+CONST String XmNnoMatchString ;
+CONST String XmCNoMatchString ;
+CONST String XmNdirectory ;
+CONST String XmCDirectory ;
+CONST String XmNpattern ;
+CONST String XmCPattern ;
+CONST String XmNdirSpec ;
+CONST String XmCDirSpec ;
+CONST String XmNdirMask ;
+CONST String XmCDirMask ;
+CONST String XmNfileTypeMask ;
+CONST String XmCFileTypeMask ;
+CONST String XmRFileTypeMask ;
+CONST String XmNdirectoryValid ;
+CONST String XmCDirectoryValid ;
+CONST String XmNdirListItems ;
+CONST String XmCDirListItems ;
+CONST String XmNdirListItemCount ;
+CONST String XmCDirListItemCount ;
+CONST String XmNdirListLabelString ;
+CONST String XmCDirListLabelString ;
+CONST String XmNfileListItems ;
+CONST String XmCFileListItems ;
+CONST String XmNfileListItemCount ;
+CONST String XmCFileListItemCount ;
+CONST String XmNfileListLabelString ;
+CONST String XmCFileListLabelString ;
+CONST String XmNqualifySearchDataProc ;
+CONST String XmCQualifySearchDataProc ;
+CONST String XmNdirSearchProc ;
+CONST String XmCDirSearchProc ;
+CONST String XmNfileSearchProc ;
+CONST String XmCFileSearchProc ;
+CONST String XmNlistItems ;
+CONST String XmNlistItemCount ;
+CONST String XmNlistVisibleItemCount ;
+CONST String XmNhistoryItems ;
+CONST String XmNhistoryItemCount ;
+CONST String XmNhistoryVisibleItemCount ;
+CONST String XmNhistoryMaxItems ;
+CONST String XmCMaxItems ;

+CONST String XmNtextAccelerators ;
+CONST String XmCTextString ;
+CONST String XmNtextString ;
+CONST String XmNtextColumns ;
+CONST String XmNcommand ;

+CONST int XmFILE_DIRECTORY ;
+CONST int XmFILE_REGULAR ;
%%
#define XmFILE_ANY_TYPE (XmFILE_DIRECTORY | XmFILE_REGULAR)
%%
+CONST int XmDIALOG_WORK_AREA ;
+CONST int XmDIALOG_PROMPT ;
+CONST int XmDIALOG_SELECTION ;
+CONST int XmDIALOG_COMMAND ;
+CONST int XmDIALOG_FILE_SELECTION ;



+CONST String XmNdefaultButtonType ;
+CONST String XmCDefaultButtonType ;
+CONST String XmRDefaultButtonType ;

+CONST String XmNminimizeButtons ;
+CONST String XmCMinimizeButtons ;

+CONST String XmNmessageString ;
+CONST String XmNmessageAlignment ;

+CONST String XmNsymbolPixmap ;

+CONST String XmNdialogType ;
+CONST String XmCDialogType ;
+CONST String XmRDialogType ;

+CONST int XmDIALOG_TEMPLATE ;
+CONST int XmDIALOG_ERROR ;
+CONST int XmDIALOG_INFORMATION ;
+CONST int XmDIALOG_MESSAGE ;
+CONST int XmDIALOG_QUESTION ;
+CONST int XmDIALOG_WARNING ;
+CONST int XmDIALOG_WORKING ;


+CONST String XmNscaleWidth ;
+CONST String XmCScaleWidth ;

+CONST String XmNscaleHeight ;
+CONST String XmCScaleHeight ;

+CONST String XmNdecimalPoints ;
+CONST String XmCDecimalPoints ;

+CONST String XmNshowValue ;
+CONST String XmCShowValue ;

+CONST String XmNtitleString ;
+CONST String XmCTitleString ;


+TYPEDEF void (*XmColorProc) (
 	XColor *bg_color,
 	XColor *fg_color,
 	XColor *sel_color,
 	XColor *ts_color,
 	XColor *bs_color
     );

+FUNC XmColorProc XmSetColorCalculation(XmColorProc proc);
+FUNC XmColorProc XmGetColorCalculation(void);
+FUNC void XmGetColors (Screen * screen, Colormap color_map, Pixel background,
	Pixel *foreground_ret, Pixel *top_shadow_ret,
	Pixel *bottom_shadow_ret, Pixel *select_ret);
+FUNC void XmChangeColor(Widget widget, Pixel background);


+FUNC void XmCvtStringToUnitType(XrmValuePtr args, Cardinal * num_args,
				  XrmValue * from_val, XrmValue * to_val);

+FUNC char *XmRegisterSegmentEncoding(char *fontlist_tag, char *ct_encoding);
+FUNC char *XmMapSegmentEncoding(char *fontlist_tag);

+FUNC void XmSetFontUnit (Display *display, int value);
+FUNC void XmSetFontUnits(Display *display, int hvalue, int vvalue);


+FUNC XmString XmStringDirectionCreate (XmStringDirection direction );
+FUNC XmString XmStringSegmentCreate ( char *text , XmStringCharSet charset ,XmStringDirection direction , Boolean separator );
+FUNC void XmStringDraw ( Display *d , Window w , XmFontList fontlist , XmString string , GC gc ,Position x , Position y , Dimension width , unsigned char align , unsigned char lay_dir , XRectangle *clip );
+FUNC void XmStringDrawImage ( Display *d , Window w , XmFontList fontlist , XmString string , GC gc ,Position x , Position y , Dimension width , unsigned char align , unsigned char lay_dir , XRectangle *clip );
+FUNC void XmStringDrawUnderline ( Display *d , Window w , XmFontList fntlst , XmString str , GC gc , Position x , Position y , Dimension width , unsigned char align , unsigned char lay_dir , XRectangle *clip , XmString under );

+FUNC XmString XmStringCreate ( char *text , XmStringCharSet charset );
+FUNC XmString XmStringCreateLocalized(char *text);
+FUNC XmString XmStringCreateSimple ( char *text );
+FUNC XmString XmStringSeparatorCreate ( void );
+FUNC XmString XmStringLtoRCreate( char *text , XmStringCharSet charset );
+FUNC XmString XmStringCreateLtoR ( char *text , XmStringCharSet charset );
+FUNC Boolean XmStringInitContext ( XmStringContext *context , XmString string );
+FUNC void XmStringFreeContext ( XmStringContext context );
+FUNC XmStringComponentType XmStringGetNextComponent ( XmStringContext context , char **text , XmStringCharSet *charset , XmStringDirection *direction , XmStringComponentType *unknown_tag , unsigned short *unknown_length , unsigned char **unknown_value );
+FUNC XmStringComponentType XmStringPeekNextComponent ( XmStringContext context );
+FUNC Boolean XmStringGetNextSegment ( XmStringContext context , char **text , XmStringCharSet *charset , XmStringDirection *direction , Boolean *separator );
+FUNC Boolean XmStringGetLtoR ( XmString string , XmStringCharSet charset , char **text );
+FUNC XmFontList XmFontListCreate ( XFontStruct *font , XmStringCharSet charset );
+FUNC XmFontList XmStringCreateFontList ( XFontStruct *font , XmStringCharSet charset );
+FUNC void XmFontListFree ( XmFontList fontlist );
+FUNC XmFontList XmFontListAdd ( XmFontList old , XFontStruct *font , XmStringCharSet charset );
+FUNC XmFontList XmFontListCopy ( XmFontList fontlist );
+FUNC Boolean XmFontListInitFontContext ( XmFontContext *context , XmFontList fontlist );
+FUNC Boolean XmFontListGetNextFont ( XmFontContext context , XmStringCharSet *charset , XFontStruct **font );
+FUNC void XmFontListFreeFontContext ( XmFontContext context );
+FUNC XmFontList XmFontListAppendEntry(XmFontList oldlist, XmFontListEntry entry);
+FUNC XmFontListEntry XmFontListEntryCreate(char *tag, XmFontType type, XtPointer font);
+FUNC void XmFontListEntryFree(XmFontListEntry *entry);
+FUNC XtPointer XmFontListEntryGetFont(XmFontListEntry entry, XmFontType *type_return);
+FUNC char *XmFontListEntryGetTag(XmFontListEntry entry);
+FUNC XmFontListEntry XmFontListEntryLoad(Display *display, char *font_name, XmFontType type, char *tag);
+FUNC XmFontListEntry XmFontListNextEntry(XmFontContext context);
+FUNC XmFontList XmFontListRemoveEntry(XmFontList oldlist, XmFontListEntry entry);
+FUNC XmString XmStringConcat ( XmString a , XmString b );
+FUNC XmString XmStringNConcat ( XmString first , XmString second , int n );
+FUNC XmString XmStringCopy ( XmString string );
+FUNC XmString XmStringNCopy ( XmString str , int n );
+FUNC Boolean XmStringByteCompare ( XmString a1 , XmString b1 );
+FUNC Boolean XmStringCompare ( XmString a , XmString b );
+FUNC int XmStringLength ( XmString string );
+FUNC Boolean XmStringEmpty ( XmString string );
+FUNC Boolean XmStringHasSubstring ( XmString string , XmString substring );
+FUNC void XmStringFree ( XmString string );
+FUNC Dimension XmStringBaseline ( XmFontList fontlist , XmString string );
+FUNC Dimension XmStringWidth ( XmFontList fontlist , XmString string );
+FUNC Dimension XmStringHeight ( XmFontList fontlist , XmString string );
+FUNC void XmStringExtent ( XmFontList fontlist , XmString string , Dimension *width , Dimension *height );
+FUNC int XmStringLineCount ( XmString string );


+TYPEDEF unsigned char XmButtonType;
+TYPEDEF XmButtonType * XmButtonTypeTable;
+TYPEDEF KeySym * XmKeySymTable;
+TYPEDEF XmStringCharSet * XmStringCharSetTable;

+CONST int XmPUSHBUTTON ;
+CONST int XmTOGGLEBUTTON ;
+CONST int XmCHECKBUTTON ;
+CONST int XmRADIOBUTTON ;
+CONST int XmCASCADEBUTTON ;
+CONST int XmSEPARATOR ;
+CONST int XmDOUBLE_SEPARATOR ;
+CONST int XmTITLE ;

+CONST String XmVaPUSHBUTTON                ;
+CONST String XmVaTOGGLEBUTTON        ;
+CONST String XmVaCHECKBUTTON         ;
+CONST String XmVaRADIOBUTTON         ;
+CONST String XmVaCASCADEBUTTON     ;
+CONST String XmVaSEPARATOR         ;
+CONST String XmVaSINGLE_SEPARATOR  ;
+CONST String XmVaDOUBLE_SEPARATOR  ;
+CONST String XmVaTITLE             ;

+CONST String XmNblendModel ;
+CONST String XmCBlendModel ;
+CONST String XmNclientData ;
+CONST String XmCClientData ;
+CONST String XmNconvertProc ;
+CONST String XmCConvertProc ;
+CONST String XmNcursorBackground ;
+CONST String XmCCursorBackground ;
+CONST String XmNcursorForeground ;
+CONST String XmCCursorForeground ;
+CONST String XmNdragDropFinishCallback ;
+CONST String XmNdragMotionCallback ;
+CONST String XmNdragOperations ;
+CONST String XmCDragOperations ;
+CONST String XmNdropFinishCallback ;
+CONST String XmNdropSiteEnterCallback ;
+CONST String XmNdropSiteLeaveCallback ;
+CONST String XmNdropStartCallback ;
+CONST String XmCExportTargets ;
+CONST String XmNincremental ;
+CONST String XmCIncremental ;
+CONST String XmNinvalidCursorForeground ;
+CONST String XmNnoneCursorForeground ;
+CONST String XmNnumExportTargets ;
+CONST String XmCNumExportTargets ;
+CONST String XmNoperationChangedCallback ;
+CONST String XmNoperationCursorIcon ;
+CONST String XmCOperationCursorIcon ;
+CONST String XmNsourceCursorIcon ;
+CONST String XmCSourceCursorIcon ;
+CONST String XmNsourcePixmapIcon ;
+CONST String XmCSourcePixmapIcon ;
+CONST String XmNstateCursorIcon ;
+CONST String XmCStateCursorIcon ;
+CONST String XmNtopLevelEnterCallback ;
+CONST String XmNtopLevelLeaveCallback ;
+CONST String XmNvalidCursorForeground ;


+CONST String XmNdragInitiatorProtocolStyle ;
+CONST String XmCDragInitiatorProtocolStyle ;
+CONST String XmNdragReceiverProtocolStyle ;
+CONST String XmCDragReceiverProtocolStyle ;

+CONST String XmNanimationMask ;
+CONST String XmCAnimationMask ;
+CONST String XmNanimationPixmap ;
+CONST String XmCAnimationPixmap ;
+CONST String XmNanimationPixmapDepth ;
+CONST String XmCAnimationPixmapDepth ;
+CONST String XmNanimationStyle ;
+CONST String XmCAnimationStyle ;
+CONST String XmNdragProc ;
+CONST String XmCDragProc ;
+CONST String XmNdropProc ;
+CONST String XmCDropProc ;
+CONST String XmNdropRectangles ;
+CONST String XmCDropRectangles ;
+CONST String XmNdropSiteActivity ;
+CONST String XmCDropSiteActivity ;
+CONST String XmNdropSiteOperations ;
+CONST String XmCDropSiteOperations ;
+CONST String XmNimportTargets ;
+CONST String XmCImportTargets ;
+CONST String XmNnumDropRectangles ;
+CONST String XmCNumDropRectangles ;
+CONST String XmNnumImportTargets ;
+CONST String XmCNumImportTargets ;

+CONST String XmNdropTransfers ;
+CONST String XmCDropTransfers ;
+CONST String XmNnumDropTransfers ;
+CONST String XmCNumDropTransfers ;
+CONST String XmNtransferProc ;
+CONST String XmCTransferProc ;
+CONST String XmNtransferStatus ;
+CONST String XmCTransferStatus ;


+FUNC Widget XmCreateSimpleMenuBar (Widget parent, String name, ArgList args, Cardinal arg_count);
+FUNC Widget XmCreateSimplePopupMenu (Widget parent, String name, ArgList args, Cardinal arg_count);
+FUNC Widget XmCreateSimplePulldownMenu (Widget parent, String name, ArgList args, Cardinal arg_count);
+FUNC Widget XmCreateSimpleOptionMenu (Widget parent, String name, ArgList args, Cardinal arg_count);
+FUNC Widget XmCreateSimpleRadioBox (Widget parent, String name, ArgList args, Cardinal arg_count);
+FUNC Widget XmCreateSimpleCheckBox (Widget parent, String name, ArgList args, Cardinal arg_count);


+FUNC Widget XmVaCreateSimpleMenuBar (Widget parent, String name, ...);
+FUNC Widget XmVaCreateSimplePopupMenu (Widget parent, String name,
                                  XtCallbackProc callback, ...);
+FUNC Widget XmVaCreateSimplePulldownMenu (Widget parent, String name,
                                     int post_from_button,
                                     XtCallbackProc callback, ...);
+FUNC Widget XmVaCreateSimpleOptionMenu (Widget parent, String name,
                                   XmString option_label,
                                   KeySym option_mnemonic,
                                   int button_set,
                                   XtCallbackProc callback, ...);
+FUNC Widget XmVaCreateSimpleRadioBox (Widget parent, String name,
                                 int button_set, XtCallbackProc callback, ...);
+FUNC Widget XmVaCreateSimpleCheckBox (Widget parent, String name,
                                 XtCallbackProc callback, ...);

+TYPEDEF  XtPointer (*XmResourceBaseProc)(
 	Widget  widget,
 	XtPointer client_data
     );

+TYPE (struct) XmSecondaryResourceDataRec;
+FIELD XmSecondaryResourceDataRec 
{
    XmResourceBaseProc	base_proc;
    XtPointer		client_data;
    String		name;
    String		res_class;
    XtResourceList	resources;
    Cardinal		num_resources;
};

+TYPEDEF XmSecondaryResourceDataRec *XmSecondaryResourceData;

+FUNC Cardinal XmGetSecondaryResourceData (WidgetClass wclass,
                                    XmSecondaryResourceData **secondaryDataRtn);
+FUNC Widget XmTrackingLocate (Widget widget, Cursor cursor,Boolean confineTo);
+FUNC Widget XmTrackingEvent(Widget widget, Cursor cursor, Boolean confine_to, XEvent *event_return);
+FUNC int XmConvertUnits (Widget widget, int orientation, int from_type,
                            int from_val, int to_type);
+FUNC int XmCvtFromHorizontalPixels (Screen * screen, int from_val, int to_type);
+FUNC int XmCvtFromVerticalPixels (Screen * screen, int from_val, int to_type);
+FUNC int XmCvtToHorizontalPixels (Screen * screen, int from_val, int from_type);
+FUNC int XmCvtToVerticalPixels (Screen * screen, int from_val, int from_type);


+FUNC XmString XmCvtCTToXmString( char *text );
+FUNC char * XmCvtXmStringToCT( XmString string );
+FUNC Boolean XmCvtTextToXmString ( Display *display , XrmValuePtr args , Cardinal *num_args , XrmValue *from_val , XrmValue *to_val , XtPointer *converter_data );
+FUNC Boolean XmCvtXmStringToText ( Display *display , XrmValuePtr args , Cardinal *num_args , XrmValue *from_val , XrmValue *to_val , XtPointer *converter_data );


+FUNC Boolean XmUninstallImage (XImage *image);
+FUNC Boolean XmDestroyPixmap (Screen *screen, Pixmap pixmap);
+FUNC Boolean XmInstallImage (XImage *image, char *image_name);
+FUNC Pixmap XmGetPixmap (Screen *screen, char *image_name, Pixel foreground, Pixel background);
+FUNC Pixmap XmGetPixmapByDepth(Screen *screen, char *image_name, Pixel foreground, Pixel background, int depth);


+FUNC Cursor XmGetMenuCursor (Display *display);
+FUNC void XmSetMenuCursor (Display *display, Cursor cursorId);
+FUNC Widget XmGetDestination (Display *display);

+ENUM XmTraversalDirection:= {
	XmTRAVERSE_CURRENT,		XmTRAVERSE_NEXT,
	XmTRAVERSE_PREV,		XmTRAVERSE_HOME,
	XmTRAVERSE_NEXT_TAB_GROUP,	XmTRAVERSE_PREV_TAB_GROUP,
	XmTRAVERSE_UP,			XmTRAVERSE_DOWN,
	XmTRAVERSE_LEFT,		XmTRAVERSE_RIGHT};

+FIELD (struct) XmTraverseObscuredCallbackStruct := {

	int reason;
	XEvent * event;
	Widget traversal_destination;
	XmTraversalDirection direction;
};

+TYPEDEF unsigned char XmNavigationType;

+ENUM XmVisibility:= {
	XmVISIBILITY_UNOBSCURED,	XmVISIBILITY_PARTIALLY_OBSCURED,
	XmVISIBILITY_FULLY_OBSCURED};

+FUNC Boolean XmIsTraversable(Widget wid) ;
+FUNC XmVisibility XmGetVisibility(Widget wid) ;
+FUNC Widget XmGetTabGroup(Widget wid) ;
+FUNC Widget XmGetFocusWidget(Widget wid) ;


+TYPEDEF long XmOffset;
+TYPEDEF XmOffset *XmOffsetPtr;

+FUNC void XmUpdateDisplay (Widget w);
+FUNC void XmResolvePartOffsets (WidgetClass wclass, XmOffsetPtr *offset);
+FUNC void XmResolveAllPartOffsets (WidgetClass wclass, XmOffsetPtr *offset,
					XmOffsetPtr *constraint_offset);
+FUNC Boolean XmWidgetGetBaselines(Widget widget, Dimension **baselines, int *line_count);
+FUNC Boolean XmWidgetGetDisplayRect(Widget wid, XRectangle *displayrect);
