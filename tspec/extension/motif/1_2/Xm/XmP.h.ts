# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1995, Open Software Foundation, Inc.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "c/c89", "stddef.h.ts", "size_t" (!?) ;
+USE "motif/1_2", "Xm/Xm.h.ts";
+USE "x5/lib", "X11/Xresource.h.ts";
+USE "x5/t", "X11/IntrinsicP.h.ts";

/*
 *	These appear to be functions that the Motif designers thought
 *	should have been in the Xt spec.  Note that XmP redefines
 *	some Xt macros, but that changes the implementation, not
 *	the interface, so we don't need them here.
 */

#	Oh yes we do!  At least, if not done, we got the wrong
#	semantics for these macros in xdt!

#
#   Macros replacing toolkit macros so that gadgets are handled properly. 
#

# osf_ri: commented out the following
#+FUNC String __Xm_XtName ( Widget ) ;
#+FUNC Display *__Xm_XtDisplay ( Widget ) ;
#+FUNC Screen *__Xm_XtScreen ( Widget ) ;
#+FUNC Window __Xm_XtWindow ( Widget ) ;
#+FUNC WidgetClass __Xm_XtClass ( Widget ) ;
#+FUNC WidgetClass __Xm_XtSuperclass ( Widget ) ;
#+FUNC Boolean __Xm_XtIsRealized ( Widget ) ;
#+FUNC Boolean __Xm_XtIsManaged ( Widget ) ;
#+FUNC Boolean __Xm_XtIsSensitive(Widget);
#+FUNC Widget __Xm_XtParent ( Widget ) ;

%%
/** osf_ri: forget the following:
#undef XtName
#define XtName(widget) __Xm_XtName(widget)
 ** osf_ri */

#undef XtDisplay

/** osf_ri: forget the following:
#define XtDisplay(widget) __Xm_XtDisplay(widget)
#undef XtScreen
#define XtScreen(widget) __Xm_XtScreen(widget) 
#undef XtWindow
#define XtWindow(widget) __Xm_XtWindow(widget)
#undef XtClass
#define XtClass(widget)	__Xm_XtClass(widget)
#undef XtSuperclass
#define XtSuperclass(widget) __Xm_XtSuperclass(widget)
#undef XtIsRealized
#define XtIsRealized(widget) __Xm_XtIsRealized(widget)
#undef XtIsManaged
#define XtIsManaged(widget) __Xm_XtIsManaged(widget)
#undef XtIsSensitive
#define XtIsSensitive(widget) __Xm_XtIsSensitive(widget)
#undef XtParent
#define XtParent(widget) __Xm_XtParent(widget)
 ** osf_ri */
%%

+FUNC Dimension XtX(Widget);
+FUNC Dimension XtY(Widget);
+FUNC Dimension XtWidth(Widget);
+FUNC Dimension XtHeight(Widget);
+FUNC Dimension XtBorderWidth(Widget);
+FUNC Pixel XtBackground(Widget);
+FUNC Boolean XtSensitive(Widget);

+TYPEDEF unsigned long Mask;

+FIELD (struct) XrmResource := {
	XrmQuark  xrm_name;
	XrmQuark  xrm_class;
	XrmQuark  xrm_type;
	Cardinal  xrm_size;
	long int  xrm_offset;
	XrmQuark  xrm_default_type;
	XtPointer xrm_default_addr;
};
+TYPEDEF XrmResource *XrmResourceList;


/*
 *	XtCoreProc is a bit difficult ... left out for now.
 */

+CONST int XmMENU_POPDOWN;
+CONST int XmMENU_PROCESS_TREE;
+CONST int XmMENU_TRAVERSAL;
+CONST int XmMENU_SHELL_POPDOWN;
+CONST int XmMENU_CALLBACK;
+CONST int XmMENU_BUTTON;
+CONST int XmMENU_CASCADING;
+CONST int XmMENU_SUBMENU;
+CONST int XmMENU_ARM;
+CONST int XmMENU_DISARM;
+CONST int XmMENU_BAR_CLEANUP;
+CONST int XmMENU_STATUS;
+CONST int XmMENU_MEMWIDGET_UPDATE;
+CONST int XmMENU_BUTTON_POPDOWN;
+CONST int XmMENU_RESTORE_EXCLUDED_TEAROFF_TO_TOPLEVEL_SHELL;
+CONST int XmMENU_RESTORE_TEAROFF_TO_TOPLEVEL_SHELL;
+CONST int XmMENU_RESTORE_TEAROFF_TO_MENUSHELL;
+CONST int XmMENU_GET_LAST_SELECT_TOPLEVEL;
+CONST int XmMENU_TEAR_OFF_ARM;

+CONST int XmMENU_TORN_BIT;
+CONST int XmMENU_TEAR_OFF_SHELL_DESCENDANT_BIT;
+CONST int XmMENU_POPUP_POSTED_BIT;

+FUNC Boolean XmIsTorn(int);
+FUNC Boolean XmIsTearOffShellDescendant(int);
+FUNC Boolean XmPopupPosted(int);

+TYPEDEF void (*XmMenuProc)(int, Widget, ...);

+FIELD (struct) XmSimpleMenuRec := {
	int count;
	int post_from_button;
	XtCallbackProc callback;
	XmStringTable label_string;
	String *accelerator;
	XmStringTable accelerator_text;
	XmKeySymTable mnemonic;
	XmStringCharSetTable mnemonic_charset;
	XmButtonTypeTable button_type;
	int button_set;
	XmString option_label;
        KeySym option_mnemonic;
};

+TYPEDEF XmSimpleMenuRec* XmSimpleMenu;

+CONST int XmIGNORE_EVENTTYPE;
+CONST int XmDEFAULT_INDICATOR_DIM;

+CONST int Xm3D_ENHANCE_PIXEL;
+CONST int XmDEFAULT_TOP_MARGIN;
+CONST int XmDEFAULT_BOTTOM_MARGIN;

+ENUM XmImportOperator := {XmSYNTHETIC_NONE, XmSYNTHETIC_LOAD};

+TYPEDEF void (*XmExportProc)( Widget, int, XtArgVal *);
+TYPEDEF XmImportOperator (*XmImportProc)( Widget, int, XtArgVal *) ;

+FIELD ( struct ) XmSyntheticResource := {
   String   resource_name;
   Cardinal resource_size;
   Cardinal resource_offset;
   XmExportProc export_proc;
   XmImportProc import_proc;
};

+TYPE XmParentProcessData;


+CONST int XmPARENT_PROCESS_ANY;
+CONST int XmINPUT_ACTION;
+CONST int XmPARENT_ACTIVATE;
+CONST int XmPARENT_CANCEL;

%%
#define XmRETURN XmPARENT_ACTIVATE
#define XmCANCEL XmPARENT_CANCEL
%%

+CONST int XmINVALID_DIMENSION;

+CONST int XmBASELINE_GET;
+CONST int XmBASELINE_SET;

+FIELD (struct) XmBaselineMargins := {
  unsigned char get_or_set;
  Dimension margin_top;
  Dimension margin_bottom;
  Dimension shadow;
  Dimension highlight;
  Dimension text_height;
  Dimension margin_height;
};

+ENUM XmFocusChange := {XmFOCUS_IN, XmFOCUS_OUT, XmENTER, XmLEAVE};

+ENUM XmNavigability := {
        XmNOT_NAVIGABLE,                XmCONTROL_NAVIGABLE,
	XmTAB_NAVIGABLE,                XmDESCENDANTS_NAVIGABLE,
	XmDESCENDANTS_TAB_NAVIGABLE
 };

/* In 1.2.5 this is in Traversal.h */

/* 
	CDE 1.2.3 uses member names old_focus and new_focus, whereas
	OSF 1.2.5 uses old and new
*/
+FIELD (struct) _XmFocusMovedCallbackStruct {

	int 		reason;
	XEvent  	*event;
	Boolean 	cont;
	Widget		old_focus;
	Widget		new_focus;
	unsigned char 	focus_policy;
};

+TYPEDEF _XmFocusMovedCallbackStruct XmFocusMovedCallbackStruct;
+TYPEDEF _XmFocusMovedCallbackStruct *XmFocusMovedCallback;

+TYPE (struct) _XmFocusDataRec;
+TYPEDEF _XmFocusDataRec *XmFocusData;

+FUNC XmFocusData _XmCreateFocusData (void);
+FUNC void _XmDestroyFocusData (XmFocusData focusData);
+FUNC void _XmSetActiveTabGroup (XmFocusData focusData, Widget tabGroup);
+FUNC Widget _XmGetActiveItem (Widget w);
+FUNC void _XmNavigInitialize (Widget request, Widget new, ArgList args, Cardinal *num_args);
+FUNC Boolean _XmChangeNavigationType (Widget current, XmNavigationType newNavType);
+FUNC Boolean _XmNavigSetValues (Widget current, Widget request, Widget new, ArgList args, Cardinal *num_args);
+FUNC void _XmNavigResize (Widget w); /* in CDE 1.2.3 only */
+FUNC void _XmValidateFocus (Widget w); /* in CDE 1.2.3 only */
+FUNC void _XmNavigDestroy (Widget w);
+FUNC Boolean _XmCallFocusMoved (Widget old, Widget new, XEvent *event);
# +FUNC Boolean _XmMgrTraversal (Widget w, int direction);
+FUNC Boolean _XmMgrTraversal (Widget w, XmTraversalDirection direction);#osf_ri
+FUNC void _XmClearFocusPath (Widget w);
+FUNC Boolean _XmFocusIsHere (Widget w);
+FUNC void _XmProcessTraversal (Widget w, int dir, Boolean check);
+FUNC unsigned char _XmGetFocusPolicy (Widget w);
+FUNC Widget _XmFindTopMostShell (Widget w);
+FUNC void _XmFocusModelChanged (Widget topmost_shell, XtPointer client_data, XtPointer call_data);
+FUNC Boolean _XmGrabTheFocus (Widget w, XEvent *event);
+FUNC XmFocusData _XmGetFocusData (Widget topmost_shell);
+FUNC Boolean _XmCreateVisibilityRect (Widget w, XRectangle *rectPtr);
+FUNC void _XmSetRect (XRectangle *rect, Widget w);
+FUNC int _XmIntersectRect (XRectangle *srcRectA, Widget widget, XRectangle *dstRect);
+FUNC int _XmEmptyRect (XRectangle *r);
+FUNC void _XmClearRect (XRectangle *r);
+FUNC Boolean _XmIsNavigable(Widget w); /* CDE 1.2.3 only */
+FUNC void _XmWidgetFocusChange(Widget w, XmFocusChange c); /* CDE 1.2.3 only */
+FUNC Widget _XmNavigate(Widget w, XmTraversalDirection d); /* CDE 1.2.3 only */
+FUNC Widget _XmFindNextTabGroup (Widget w);
+FUNC Widget _XmFindPrevTabGroup (Widget w);
+FUNC void _XmSetInitialOfTabGroup( Widget group, Widget focus); /* CDE 1.2.3 only */
+FUNC void _XmResetTravGraph( Widget w); /* CDE 1.2.3 only */
+FUNC Boolean _XmFocusIsInShell( Widget w); /* CDE 1.2.3 only */
+FUNC Boolean _XmShellIsExclusive( Widget w); /* CDE 1.2.3 only */
+FUNC Widget _XmGetFirstFocus( Widget w); /* CDE 1.2.3 only */


/* FUNC void _XmPrimitiveEnter (Widget pw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* FUNC void _XmPrimitiveLeave (Widget pw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmPrimitiveUnmap (Widget pw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmPrimitiveFocusInInternal (Widget pw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmPrimitiveFocusOut (Widget pw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmPrimitiveFocusIn (Widget pw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmManagerEnter (Widget mw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmManagerFocusInInternal (Widget mw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmManagerFocusIn (Widget mw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmManagerFocusOut (Widget mw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmManagerUnmap (Widget mw, XEvent *event, String *params, Cardinal *num_params); NOT in CDE 1.2.3 */
/* +FUNC void _XmClearKbdFocus (Widget tabGroup); NOT in CDE 1.2.3 */
/* +FUNC Boolean _XmFindTraversablePrim (Widget tabGroup); NOT in CDE 1.2.3 */
/* +FUNC Boolean _XmTestTraversability (Widget widget, XRectangle *visRect); NOT in CDE 1.2.3 */
/* +FUNC Boolean XmProcessTraversal (Widget w, int dir); NOT in CDE 1.2.3 */
/* +FUNC void _XmClearTabGroup (Widget w); NOT in CDE 1.2.3 */
/* +FUNC Widget _XmFindTabGroup (Widget w); NOT in CDE 1.2.3 */
/* +FUNC Widget _XmGetTabGroup (Widget w); NOT in CDE 1.2.3 */
/* +FUNC void XmAddTabGroup (Widget tabGroup); NOT in CDE 1.2.3 */
/* +FUNC void XmRemoveTabGroup (Widget w); NOT in CDE 1.2.3 */
/* +FUNC Boolean _XmGetManagedInfo (Widget w); NOT in CDE 1.2.3 */

%%
#define XmVoidProc	XtProc
%%

+TYPEDEF Boolean (*XmParentProcessProc)( Widget, XmParentProcessData) ;
+TYPEDEF void (*XmWidgetDispatchProc)( Widget, XEvent *, Mask) ;
+TYPEDEF void (*XmMenuPopupProc)( Widget, Widget, XEvent *) ;
+TYPEDEF void (*XmMenuTraversalProc)( Widget, Widget, XmTraversalDirection) ;
+TYPEDEF void (*XmResizeFlagProc)(Widget, Boolean) ;
+TYPEDEF void (*XmRealizeOutProc)( Widget, Mask *, XSetWindowAttributes *) ;
+TYPEDEF Boolean (*XmVisualChangeProc)( Widget, Widget, Widget) ;
+TYPEDEF void (*XmTraversalProc)( Widget, XtPointer, XtPointer, int) ;
+TYPEDEF void (*XmFocusMovedProc)( Widget, XtPointer, XtPointer) ;
+TYPEDEF void (*XmCacheCopyProc)( XtPointer, XtPointer, size_t) ;
+TYPEDEF void (*XmGadgetCacheProc)( XtPointer) ;
+TYPEDEF int (*XmCacheCompareProc)( XtPointer, XtPointer) ;
+TYPEDEF Boolean (*XmWidgetBaselineProc)(Widget, Dimension **, int *);
+TYPEDEF Boolean (*XmWidgetDisplayRectProc)(Widget, XRectangle *);
+TYPEDEF void (*XmWidgetMarginsProc)(Widget, XmBaselineMargins *);
+TYPEDEF XmNavigability (*XmWidgetNavigableProc)( Widget) ;
+TYPEDEF void (*XmFocusChangeProc)(Widget, XmFocusChange);


+FIELD (struct) _XmBuildVirtualKeyStruct := {
     Modifiers mod;
     char      *key;
     char      *action;
  };
              

+FIELD (struct) _XmTextInsertPair := {
    Atom selection;
    Atom target;
};

+FIELD (struct) _XmHighlightRec := {
    XmTextPosition position;
    XmHighlightMode mode;
};

+FIELD (struct) _XmHighlightData := {
    Cardinal number;
    Cardinal maximum;
    _XmHighlightRec *list;
};

+ENUM XmSelectType := { XmDEST_SELECT, XmPRIM_SELECT };

+FIELD (struct) _XmInsertSelect := {
    Boolean done_status;
    Boolean success_status;
    XmSelectType select_type;
    XSelectionRequestEvent *event;
};

+FIELD (struct) _XmTextActionRec := {
    XEvent *event;
    String *params;
    Cardinal *num_params;
};

+FIELD (struct) _XmTextDropTransferRec := {
    Widget widget;
    XmTextPosition insert_pos;
    int num_chars;
    Time timestamp;
    Boolean move;
};

+FIELD (struct) _XmTextPrimSelect := {
    XmTextPosition position;
    Atom target;
    Time time;
    int num_chars;
    int ref_count;
};

+FIELD (struct) XmTextContextDataRec := {
    Screen *screen;
    XContext context;
    unsigned char type;
};

+TYPEDEF XmTextContextDataRec *XmTextContextData;

+CONST int _XM_IS_DEST_CTX;
+CONST int _XM_IS_GC_DATA_CTX;
+CONST int _XM_IS_PIXMAP_CTX;

+CONST int XmTEXT_DRAG_ICON_WIDTH;
+CONST int XmTEXT_DRAG_ICON_HEIGHT;
+CONST int XmTEXT_DRAG_ICON_X_HOT;
+CONST int XmTEXT_DRAG_ICON_Y_HOT;

/* Defines used by geometry manager utilities */

+CONST int XmGET_ACTUAL_SIZE;
+CONST int XmGET_PREFERRED_SIZE;
+CONST int XmGEO_PRE_SET;
+CONST int XmGEO_POST_SET;

+CONST int XmGEO_EXPAND;
+CONST int XmGEO_CENTER;
+CONST int XmGEO_PACK;

+CONST int XmGEO_PROPORTIONAL;
+CONST int XmGEO_AVERAGING;
+CONST int XmGEO_WRAP;

+CONST int XmGEO_ROW_MAJOR;
+CONST int XmGEO_COLUMN_MAJOR;

+TYPE (struct) _XmGeoMatrixRec;
+TYPEDEF _XmGeoMatrixRec *XmGeoMatrix;

+TYPE (union) _XmGeoMajorLayoutRec;
+TYPEDEF _XmGeoMajorLayoutRec *XmGeoMajorLayout;

+FIELD (struct) XmKidGeometryRec := {
    Widget   kid;
    XtWidgetGeometry	box;
};

+TYPEDEF XmKidGeometryRec *XmKidGeometry;

+TYPEDEF void (*XmGeoArrangeProc)(XmGeoMatrix, Position, Position, Dimension *, Dimension *) ;
+TYPEDEF Boolean (*XmGeoExceptProc)( XmGeoMatrix ) ;
+TYPEDEF void (*XmGeoExtDestructorProc)( XtPointer ) ;
+TYPEDEF void (*XmGeoSegmentFixUpProc)( XmGeoMatrix, int, XmGeoMajorLayout,
                                                               XmKidGeometry) ;
+FIELD (struct) XmGeoRowLayoutRec := {
    Boolean         end ;
    XmGeoSegmentFixUpProc fix_up ;
    Dimension       even_width ;
    Dimension       even_height ;
    Dimension       min_height ;
    Boolean         stretch_height ;
    Boolean         uniform_border ;
    Dimension       border ;
    unsigned char   fill_mode ;
    unsigned char   fit_mode ;
    Boolean         sticky_end ;
    Dimension       space_above ;
    Dimension       space_end ;
    Dimension       space_between ;
    Dimension       max_box_height ;
    Dimension       boxes_width ;
    Dimension       fill_width ;
    Dimension       box_count ;
    };

+TYPEDEF XmGeoRowLayoutRec *XmGeoRowLayout ;

+FIELD (struct) XmGeoColumnLayoutRec := {
    Boolean         end ;
    XmGeoSegmentFixUpProc fix_up ;
    Dimension       even_height ;
    Dimension       even_width ;
    Dimension       min_width ;
    Boolean         stretch_width ;
    Boolean         uniform_border ;
    Dimension       border ;
    unsigned char   fill_mode ;
    unsigned char   fit_mode ;
    Boolean         sticky_end ;
    Dimension       space_left ;
    Dimension       space_end ;
    Dimension       space_between ;
    Dimension       max_box_width ;
    Dimension       boxes_height ;
    Dimension       fill_height ;
    Dimension       box_count ;
    };

+TYPEDEF XmGeoColumnLayoutRec *XmGeoColumnLayout ;

+FIELD (union) _XmGeoMajorLayoutRec := {
  XmGeoRowLayoutRec row ;
  XmGeoColumnLayoutRec col ;
};

+FIELD (struct) _XmGeoMatrixRec := {
    Widget          composite ;
    Widget          instigator ;
    XtWidgetGeometry instig_request ;
    XtWidgetGeometry parent_request ;
    XtWidgetGeometry *in_layout ;
    XmKidGeometry   boxes ;
    XmGeoMajorLayout layouts ;
    Dimension       margin_w ;
    Dimension       margin_h ;
    Boolean         stretch_boxes ;
    Boolean         uniform_border ;
    Dimension       border ;
    Dimension       max_major ;
    Dimension       boxes_minor ;
    Dimension       fill_minor ;
    Dimension       width ;
    Dimension       height ;
    XmGeoExceptProc set_except ;
    XmGeoExceptProc almost_except ;
    XmGeoExceptProc no_geo_request ;
    XtPointer       extension ;
    XmGeoExtDestructorProc ext_destructor ;
    XmGeoArrangeProc arrange_boxes ;
    unsigned char   major_order ;
    };

+TYPEDEF _XmGeoMatrixRec XmGeoMatrixRec;

+TYPEDEF XmGeoMatrix (*XmGeoCreateProc)( Widget, Widget, XtWidgetGeometry *) ;

+DEFINE XmInheritCallbackProc %% ((XtCallbackProc) _XtInherit) %% ;
+DEFINE XmInheritTraversalProc %% ((XmTraversalProc) _XtInherit) %% ;
+DEFINE XmInheritParentProcess %% ((XmParentProcessProc) _XtInherit) %% ;
+DEFINE XmInheritWidgetProc %% ((XtWidgetProc) _XtInherit) %% ;
+DEFINE XmInheritMenuProc %% ((XmMenuProc) _XtInherit) %% ;
+DEFINE XmInheritTranslations %% XtInheritTranslations %% ;
+DEFINE XmInheritCachePart	%% ((XmCacheClassPartPtr) _XtInherit) %% ;
+DEFINE XmInheritBaselineProc %% ((XmWidgetBaselineProc) _XtInherit) %% ;
+DEFINE XmInheritDisplayRectProc %% ((XmWidgetDisplayRectProc) _XtInherit) %% ;
+DEFINE XmInheritGeoMatrixCreate %% ((XmGeoCreateProc) _XtInherit) %% ;
+DEFINE XmInheritFocusMovedProc %% ((XmFocusMovedProc) _XtInherit) %% ;
+DEFINE XmInheritClass		   %% ((WidgetClass) &_XmInheritClass) %% ;
+DEFINE XmInheritInitializePrehook %% ((XtInitProc) _XtInherit) %% ;
+DEFINE XmInheritSetValuesPrehook  %% ((XtSetValuesFunc) _XtInherit) %% ;
+DEFINE XmInheritGetValuesPrehook  %% ((XtArgsProc) _XtInherit) %% ;
+DEFINE XmInheritInitializePosthook %% ((XtInitProc) _XtInherit) %% ;
+DEFINE XmInheritSetValuesPosthook  %% ((XtSetValuesFunc) _XtInherit) %% ;
+DEFINE XmInheritGetValuesPosthook  %% ((XtArgsProc) _XtInherit) %% ;
+DEFINE XmInheritSecObjectCreate   %% ((XtInitProc) _XtInherit) %% ;
+DEFINE XmInheritGetSecResData	   %% ((XmGetSecResDataFunc) _XtInherit) %% ;
+DEFINE XmInheritInputDispatch	   %% ((XmWidgetDispatchProc) _XtInherit) %% ;
+DEFINE XmInheritVisualChange	   %% ((XmVisualChangeProc) _XtInherit) %% ;
+DEFINE XmInheritArmAndActivate	   %% ((XtActionProc) _XtInherit) %% ;
+DEFINE XmInheritActionProc	   %% ((XtActionProc) _XtInherit) %% ;
+DEFINE XmInheritFocusChange       %% ((XmFocusChangeProc) _XtInherit) %% ;
+DEFINE XmInheritWidgetNavigable   %% ((XmWidgetNavigableProc) _XtInherit) %% ;
+DEFINE XmInheritClassPartInitPrehook %% ((XtWidgetClassProc) _XtInherit) %% ;
+DEFINE XmInheritClassPartInitPosthook %% ((XtWidgetClassProc) _XtInherit) %% ;
+DEFINE XmInheritBorderHighlight   %% ((XtWidgetProc) _XtInherit) %% ;
+DEFINE XmInheritBorderUnhighlight   %% ((XtWidgetProc) _XtInherit) %% ;

+DEFINE XmInheritRealize  %% ((XtRealizeProc) _XtInherit) %%;
+DEFINE XmInheritResize %% ((XtWidgetProc) _XtInherit) %%;
+DEFINE XmInheritSetOverrideCallback %% ((XtWidgetProc) _XtInherit) %%;

+CONST int XmFIRST_APPLICATION_SUBCLASS_BIT;

+CONST int XmCASCADE_BUTTON_BIT;
+CONST int XmCASCADE_BUTTON_GADGET_BIT;
+CONST int XmCOMMAND_BOX_BIT;
+CONST int XmDIALOG_SHELL_BIT;
+CONST int XmLIST_BIT;
+CONST int XmFORM_BIT;
+CONST int XmTEXT_FIELD_BIT;
+CONST int XmGADGET_BIT;
+CONST int XmLABEL_BIT;
+CONST int XmLABEL_GADGET_BIT;
+CONST int XmMAIN_WINDOW_BIT;
+CONST int XmMANAGER_BIT;
+CONST int XmMENU_SHELL_BIT;
+CONST int XmDRAWN_BUTTON_BIT;
+CONST int XmPRIMITIVE_BIT;
+CONST int XmPUSH_BUTTON_BIT;
+CONST int XmPUSH_BUTTON_GADGET_BIT;
+CONST int XmROW_COLUMN_BIT;
+CONST int XmSCROLL_BAR_BIT;
+CONST int XmSCROLLED_WINDOW_BIT;
+CONST int XmSELECTION_BOX_BIT;
+CONST int XmSEPARATOR_BIT;
+CONST int XmSEPARATOR_GADGET_BIT;
+CONST int XmTEXT_BIT;
+CONST int XmTOGGLE_BUTTON_BIT;
+CONST int XmTOGGLE_BUTTON_GADGET_BIT;
+CONST int XmDROP_TRANSFER_BIT;
+CONST int XmDROP_SITE_MANAGER_BIT;
+CONST int XmDISPLAY_BIT, XmSCREEN_BIT;
+CONST int XmARROW_BUTTON_BIT;
+CONST int XmARROW_BUTTON_GADGET_BIT;
+CONST int XmBULLETIN_BOARD_BIT;
+CONST int XmDRAWING_AREA_BIT;
+CONST int XmFILE_SELECTION_BOX_BIT;
+CONST int XmFRAME_BIT;
+CONST int XmMESSAGE_BOX_BIT;
+CONST int XmSASH_BIT;
+CONST int XmSCALE_BIT;
+CONST int XmPANED_WINDOW_BIT;
+CONST int XmVENDOR_SHELL_BIT;
+CONST int XmFAST_SUBCLASS_TAIL_BIT;

+CONST int XmLAST_FAST_SUBCLASS_BIT;

+CONST int XmObjectIndex;
+CONST int ObjectIndex;
+CONST int XmRectObjIndex;
+CONST int RectObjIndex;
+CONST int XmWindowObjIndex;
+CONST int WindowObjIndex;
+CONST int XmCoreIndex;
+CONST int CoreIndex;
+CONST int XmCompositeIndex;
+CONST int CompositeIndex;
+CONST int XmConstraintIndex;
+CONST int ConstraintIndex;
+CONST int XmGadgetIndex;
+CONST int XmPrimitiveIndex;
+CONST int XmManagerIndex;

+CONST int XmArrowBIndex;
+CONST int XmArrowButtonIndex;
+CONST int XmLabelIndex;
+CONST int XmListIndex;
+CONST int XmScrollBarIndex;
+CONST int XmSeparatorIndex;
+CONST int XmTextIndex;

+CONST int XmCascadeBIndex;
+CONST int XmCascadeButtonIndex;
+CONST int XmDrawnBIndex;
+CONST int XmDrawnButtonIndex;
+CONST int XmPushBIndex;
+CONST int XmPushButtonIndex;
+CONST int XmToggleBIndex;
+CONST int XmToggleButtonIndex;

+CONST int XmArrowBGIndex;
+CONST int XmArrowButtonGadgetIndex;
+CONST int XmLabelGIndex;
+CONST int XmLabelGadgetIndex;
+CONST int XmSeparatoGIndex;
+CONST int XmSeparatorGadgetIndex;

+CONST int XmCascadeBGIndex;
+CONST int XmCascadeButtonGadgetIndex;
+CONST int XmPushBGIndex;
+CONST int XmPushButtonGadgetIndex;
+CONST int XmToggleBGIndex;
+CONST int XmToggleButtonGadgetIndex;

+CONST int XmBulletinBIndex;
+CONST int XmBulletinBoardIndex;
+CONST int XmDrawingAIndex;
+CONST int XmDrawingAreaIndex;
+CONST int XmFrameIndex;
+CONST int XmPanedWIndex;
+CONST int XmPanedWindowIndex;
+CONST int XmRowColumnIndex;
+CONST int XmScaleIndex;
+CONST int XmScrolledWIndex;
+CONST int XmScrolledWindowIndex;

+CONST int XmFormIndex;
+CONST int XmMessageBIndex;
+CONST int XmMessageBoxIndex;
+CONST int XmSelectioBIndex;
+CONST int XmSelectionBoxIndex;

+CONST int XmMainWIndex;
+CONST int XmMainWindowIndex;

+CONST int XmCommandIndex;
+CONST int XmFileSBIndex;
+CONST int XmFileSelectionBoxIndex;

+CONST int XmShellIndex;
+CONST int ShellIndex;
+CONST int XmOverrideShellIndex;
+CONST int OverrideShellIndex;
+CONST int XmWMShellIndex;
+CONST int WMShellIndex;
+CONST int XmVendorShellIndex;
+CONST int VendorShellIndex;
+CONST int XmTransientShellIndex;
+CONST int TransientShellIndex;
+CONST int XmTopLevelShellIndex;
+CONST int TopLevelShellIndex;
+CONST int XmApplicationShellIndex;
+CONST int ApplicationShellIndex;

+CONST int XmDialogSIndex;
+CONST int XmDialogShellIndex;
+CONST int XmMenuShellIndex;


+FIELD (struct) XmPartResource := {
    String     resource_name;
    String     resource_class;
    String     resource_type;
    Cardinal   resource_size;
    Cardinal   resource_offset;
    String     default_type;
    XtPointer  default_addr;
};

/* Not sure what to do about XmPartOffset, et al. */

+FIELD (struct) XmRegionBox := {
    short x1, x2, y1, y2;
};

+FIELD (struct) XmRegionRec {
    long	size;
    long	numRects;
    XmRegionBox	*rects;
    XmRegionBox	extents;
};

+TYPEDEF XmRegionRec *XmRegion;


+FUNC XmGadget _XmInputInGadget(Widget cw, int x, int y) ;
+FUNC XmGadget _XmInputForGadget(Widget cw, int x, int y) ;
+FUNC void _XmConfigureObject(Widget g, Position x, Position y, Dimension width, Dimension height, Dimension border_width) ;
+FUNC void _XmResizeObject(Widget g, Dimension width, Dimension height, Dimension border_width) ;
+FUNC void _XmMoveObject(Widget g, Position x, Position y) ;
+FUNC void _XmRedisplayGadgets(Widget w, XEvent *event, Region region) ;
+FUNC void _XmDispatchGadgetInput(Widget g, XEvent *event, Mask mask) ;

+FUNC Boolean _XmInstallImage(XImage *image, char *image_name, int hot_x, int hot_y) ;
+FUNC Boolean _XmGetImage(Screen *screen, char *image_name, XImage **image) ;
+FUNC Boolean _XmGetPixmapData(Screen *screen, Pixmap pixmap,
			       char **image_name, int *depth,
			       Pixel *foreground, Pixel *background,
			       int *hot_x, int *hot_y, unsigned int *width,
			       unsigned int *height) ;
+FUNC Pixmap _XmGetPixmap(Screen *screen, char *image_name, int depth,
			  Pixel foreground, Pixel background) ;
+FUNC Boolean _XmInstallPixmap(Pixmap pixmap, Screen *screen, char *image_name,
			       Pixel foreground, Pixel background) ;

+FUNC Boolean _XmMapBtnEvent(String str, int *eventType, 
			     unsigned int *button, unsigned int *modifiers) ;
+FUNC Boolean _XmMapKeyEvent(String str, int *eventType, unsigned *keysym,
			     unsigned int *modifiers) ;
+FUNC Boolean _XmMatchBtnEvent(XEvent *event, int eventType, 
			       unsigned int button, unsigned int modifiers) ;
+FUNC Boolean _XmMatchKeyEvent(XEvent *event, int eventType, unsigned int key,
			       unsigned int modifiers) ;
+FUNC XImage * _XmGetImageFromFile(char *filename) ;
+FUNC XImage * _XmGetImageAndHotSpotFromFile(char *filename, int *hot_x, int *hot_y) ;

+CONST int XmLABEL_FONTLIST;
+CONST int XmBUTTON_FONTLIST;
+CONST int XmTEXT_FONTLIST;

+FUNC void _XmRegisterConverters( void ) ;
+FUNC void _XmWarning(Widget w, char *message) ;
+FUNC Boolean _XmStringsAreEqual(char *in_str, char *test_str) ;
+FUNC XmFontList _XmGetDefaultFontList(Widget w, unsigned char fontListType) ;
+FUNC char * _XmConvertCSToString(XmString cs) ;
+FUNC Boolean _XmCvtXmStringToCT(XrmValue *from, XrmValue *to) ;

+FUNC void _XmBuildResources(XmSyntheticResource **wc_resources_ptr, 
			     int *wc_num_resources_ptr, XmSyntheticResource *sc_resources,
			     int sc_num_resources) ;
+FUNC void _XmInitializeSyntheticResources(XmSyntheticResource *resources,
					   int num_resources) ;
+FUNC void _XmPrimitiveGetValuesHook(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmGadgetGetValuesHook(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmManagerGetValuesHook(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmExtGetValuesHook(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmExtImportArgs(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmPrimitiveImportArgs(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmGadgetImportArgs(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmGadgetImportSecondaryArgs(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC void _XmManagerImportArgs(Widget w, ArgList args, Cardinal *num_args) ;
+FUNC int _XmConvertUnits(Screen *screen, int dimension, int from_type,
			  int from_val, int to_type) ;
+FUNC XmImportOperator _XmToHorizontalPixels(Widget widget, int offset, XtArgVal *value) ;
+FUNC XmImportOperator _XmToVerticalPixels(Widget widget, int offset, XtArgVal *value) ;
+FUNC void _XmFromHorizontalPixels(Widget widget, int offset, XtArgVal *value) ;
+FUNC void _XmFromVerticalPixels(Widget widget, int offset, XtArgVal *value) ;
+FUNC void _XmSortResourceList(XrmResource *list[], Cardinal len) ;
+FUNC void _XmUnitTypeDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC unsigned char _XmGetUnitType(Widget widget) ;

+FUNC Boolean _XmIsEventUnique(XEvent *event) ;
+FUNC void _XmRecordEvent(XEvent *event) ;

+CONST int XmLOOK_AT_SCREEN;
+CONST int XmLOOK_AT_CMAP;
+CONST int XmLOOK_AT_BACKGROUND;
+CONST int XmLOOK_AT_FOREGROUND;
+CONST int XmLOOK_AT_TOP_SHADOW;
+CONST int XmLOOK_AT_BOTTOM_SHADOW;
+CONST int XmLOOK_AT_SELECT;

+CONST int XmBACKGROUND;
+CONST int XmFOREGROUND;
+CONST int XmTOP_SHADOW;
+CONST int XmBOTTOM_SHADOW;
+CONST int XmSELECT;

+FIELD (struct) XmColorData := {
   Screen * screen;
   Colormap color_map;
   unsigned char allocated;
   XColor background;
   XColor foreground;
   XColor top_shadow;
   XColor bottom_shadow;
   XColor select;
};

+FUNC void _XmRegisterPixmapConverters( void ) ;
+FUNC char * _XmGetBGPixmapName( void ) ;
+FUNC void _XmClearBGPixmapName( void ) ;
+FUNC void _XmForegroundColorDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmHighlightColorDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmBackgroundColorDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmTopShadowColorDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmBottomShadowColorDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmSelectColorDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmPrimitiveTopShadowPixmapDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmManagerTopShadowPixmapDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmPrimitiveHighlightPixmapDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmManagerHighlightPixmapDefault(Widget widget, int offset, XrmValue *value) ;
+FUNC void _XmGetDefaultThresholdsForScreen(Screen *screen) ; 
+FUNC String _XmGetDefaultBackgroundColorSpec(Screen *screen) ;
+FUNC void _XmSetDefaultBackgroundColorSpec(Screen *screen, String new_color_spec) ;
+FUNC XmColorData * _XmGetDefaultColors(Screen *screen, Colormap color_map) ; 
+FUNC Boolean _XmSearchColorCache(unsigned int which, XmColorData *values, XmColorData **ret) ;
+FUNC XmColorData * _XmAddToColorCache(XmColorData *new_rec) ; 
+FUNC Pixel _XmBlackPixel(Screen *screen, Colormap colormap, XColor blackcolor) ;
+FUNC Pixel _XmWhitePixel( Screen *screen, Colormap colormap, XColor whitecolor) ;
+FUNC Pixel _XmAccessColorData(XmColorData *cd, unsigned char which) ;
+FUNC XmColorData * _XmGetColors(Screen *screen, Colormap color_map, Pixel background) ;

+FUNC XFontStruct * _XmGetFirstFont(XmFontListEntry entry) ;
+FUNC Boolean _XmFontListGetDefaultFont(XmFontList fontlist, XFontStruct **font_struct) ;
+FUNC Boolean _XmFontListSearch(XmFontList fontlist, XmStringCharSet charset, short *indx, XFontStruct **font_struct) ;
+FUNC Boolean _XmStringIsXmString(XmString string) ; 
+FUNC Boolean _XmStringInitContext(_XmStringContext *context, _XmString string) ;
+FUNC Boolean _XmStringGetNextSegment(_XmStringContext context, XmStringCharSet *charset,
			XmStringDirection *direction, char **text,
			short *char_count, Boolean *separator) ;
+FUNC void _XmStringFreeContext(_XmStringContext context) ;
+FUNC Dimension _XmStringWidth(XmFontList fontlist, _XmString string) ;
+FUNC Dimension _XmStringHeight(XmFontList fontlist, _XmString string) ;
+FUNC void _XmStringExtent(XmFontList fontlist, _XmString string, Dimension *width, Dimension *height) ;
+FUNC Boolean _XmStringEmpty(_XmString string) ; 
+FUNC void _XmStringDraw(Display *d, Window w, XmFontList fontlist, 
			 _XmString string, GC gc, Position x, Position y,
			 Dimension width, unsigned char align, unsigned char lay_dir,
			 XRectangle *clip) ;
+FUNC void _XmStringDrawImage(Display *d, Window w, XmFontList fontlist,
			      _XmString string, GC gc, Position x, Position y,
			      Dimension width, unsigned char align, unsigned char lay_dir,
			      XRectangle *clip) ;
+FUNC void _XmStringDrawUnderline(Display *d, Window w, XmFontList f,
				  _XmString s, GC gc, Position x, Position y,
				  Dimension width, unsigned char align, unsigned char lay_dir,
				  XRectangle *clip, _XmString u) ;
+FUNC void _XmStringDrawMnemonic(Display *d, Window w, XmFontList fontlist, 
				 _XmString string, GC gc, Position x, Position y,
				 Dimension width, unsigned char align, unsigned char lay_dir,
				 XRectangle *clip, String mnemonic, XmStringCharSet charset) ;
+FUNC _XmString _XmStringCreate(XmString cs) ;
+FUNC void _XmStringFree(_XmString string) ;
+FUNC char * _XmStringGetCurrentCharset( void ) ;
+FUNC char * _XmCharsetCanonicalize(String charset) ;
+FUNC void _XmStringUpdate(XmFontList fontlist, _XmString string) ;
+FUNC _XmString _XmStringCopy(_XmString string) ;
+FUNC Boolean _XmStringByteCompare(_XmString a, _XmString b) ;
+FUNC Boolean _XmStringHasSubstring(_XmString string, _XmString substring) ;
+FUNC XmString _XmStringCreateExternal(XmFontList fontlist, _XmString cs) ;
+FUNC Dimension _XmStringBaseline(XmFontList fontlist, _XmString string) ;
+FUNC int _XmStringLineCount(_XmString string) ;
+FUNC char * _XmStringGetTextConcat(XmString string) ;
+FUNC Boolean _XmStringIsCurrentCharset(XmStringCharSet c) ;
+FUNC Boolean _XmStringSingleSegment(XmString str, char **pTextOut, XmStringCharSet *pCharsetOut ) ;
+FUNC void _XmStringUpdateWMShellTitle(XmString xmstr, Widget shell) ;

+CONST int XmTAB_ANY;
+CONST int XmNONE_OR_BC;


+FUNC XtGeometryResult _XmHandleQueryGeometry(Widget wid, XtWidgetGeometry *intended,
				XtWidgetGeometry *desired, unsigned char policy,
				XmGeoCreateProc createMatrix) ;
+FUNC XtGeometryResult _XmHandleGeometryManager(Widget wid, Widget instigator,
				XtWidgetGeometry *desired, XtWidgetGeometry *allowed,
				unsigned char policy, XmGeoMatrix *cachePtr,
				XmGeoCreateProc createMatrix) ;
+FUNC void _XmHandleSizeUpdate(Widget wid, unsigned char policy, XmGeoCreateProc createMatrix) ;
+FUNC XmGeoMatrix _XmGeoMatrixAlloc(unsigned int numRows, unsigned int numBoxes,
				    unsigned int extSize) ;
+FUNC void _XmGeoMatrixFree(XmGeoMatrix geo_spec) ;
+FUNC Boolean _XmGeoSetupKid(XmKidGeometry geo, Widget kidWid) ;
+FUNC void _XmGeoMatrixGet(XmGeoMatrix geoSpec, int geoType) ;
+FUNC void _XmGeoMatrixSet(XmGeoMatrix geoSpec) ;
+FUNC void _XmGeoAdjustBoxes(XmGeoMatrix geoSpec) ;
+FUNC void _XmGeoGetDimensions(XmGeoMatrix geoSpec) ;
+FUNC void _XmGeoArrangeBoxes(XmGeoMatrix geoSpec, Position x, Position y,
			      Dimension *pW, Dimension *pH) ;
+FUNC Dimension _XmGeoBoxesSameWidth(XmKidGeometry rowPtr, Dimension width) ;
+FUNC Dimension _XmGeoBoxesSameHeight(XmKidGeometry rowPtr, Dimension height) ;
+FUNC void _XmSeparatorFix(XmGeoMatrix geoSpec, int action, XmGeoMajorLayout layoutPtr,
			   XmKidGeometry rowPtr) ;
+FUNC void _XmMenuBarFix(XmGeoMatrix geoSpec, int action, 
			 XmGeoMajorLayout layoutPtr, XmKidGeometry rowPtr) ;
+FUNC void _XmGeoLoadValues(Widget wid, int geoType, Widget instigator, XtWidgetGeometry *request,
			    XtWidgetGeometry *geoResult) ;
+FUNC int _XmGeoCount_kids(CompositeWidget c) ;
+FUNC XmKidGeometry _XmGetKidGeo(Widget wid, Widget instigator, 
				 XtWidgetGeometry *request, int uniform_border,
				 Dimension border, int uniform_width_margins,
				 int uniform_height_margins, Widget help,
				 int geo_type) ;
+FUNC void _XmGeoClearRectObjAreas( RectObj r, XWindowChanges *old) ;
+FUNC void _XmSetKidGeo(XmKidGeometry kg, Widget instigator) ;
+FUNC Boolean _XmGeometryEqual(Widget wid, XtWidgetGeometry *geoA, XtWidgetGeometry *geoB) ;
+FUNC Boolean _XmGeoReplyYes(Widget wid, XtWidgetGeometry *desired, XtWidgetGeometry *response) ;
+FUNC XtGeometryResult _XmMakeGeometryRequest(Widget w, XtWidgetGeometry *geom) ;

+FUNC void _XmSetDestination(Display *dpy, Widget w) ;

+FUNC void _XmImChangeManaged( Widget vw) ;
+FUNC void _XmImRealize( Widget vw) ;
+FUNC void _XmImResize( Widget vw) ;
+FUNC void _XmImRedisplay( Widget vw) ;

+FUNC void _XmInitAtomPairs( Display *display) ;
+FUNC void _XmInitTargetsTable( Display *display) ;
+FUNC Cardinal _XmIndexToTargets( Widget shell, Cardinal t_index, Atom **targetsRtn) ;
+FUNC Cardinal _XmTargetsToIndex( Widget shell, Atom *targets, Cardinal numTargets) ;
+FUNC Atom _XmAllocMotifAtom( Widget shell, Time time) ;
+FUNC void _XmFreeMotifAtom( Widget shell, Atom atom) ;
+FUNC void _XmDestroyMotifWindow( Display *dpy) ;
+FUNC Window _XmGetDragProxyWindow(Display *display) ;

+FUNC void _XmDragOverHide( Widget w, Position clipOriginX, Position clipOriginY, XmRegion clipRegion) ;
+FUNC void _XmDragOverShow( Widget w, Position clipOriginX, Position clipOriginY, XmRegion clipRegion) ;
+FUNC void _XmDragOverMove( Widget w, Position x, Position y) ;
+FUNC void _XmDragOverChange( Widget w, unsigned char dropSiteStatus) ;
+FUNC void _XmDragOverFinish( Widget w, unsigned char completionStatus) ;

+FUNC Cursor _XmDragOverGetActiveCursor(Widget w) ;
+FUNC void _XmDragOverSetInitialPosition(Widget w, Position initialX,
			Position initialY) ;
+FUNC XmRegion _XmRegionCreate( void ) ;
+FUNC XmRegion _XmRegionCreateSize(long size) ;
+FUNC void _XmRegionComputeExtents(XmRegion r) ;
+FUNC void _XmRegionGetExtents( XmRegion r, XRectangle *rect) ;
+FUNC void _XmRegionUnionRectWithRegion( XRectangle *rect, XmRegion source,
					XmRegion dest) ;
+FUNC void _XmRegionIntersectRectWithRegion( XRectangle *rect, XmRegion source,
					    XmRegion dest) ;
+FUNC long _XmRegionGetNumRectangles(XmRegion r) ;
+FUNC void _XmRegionGetRectangles( XmRegion r, XRectangle **rects, long *nrects) ;
+FUNC void _XmRegionSetGCRegion( Display *dpy, GC gc, int x_origin, int y_origin,
				XmRegion r) ;
+FUNC void _XmRegionDestroy( XmRegion r) ;
+FUNC void _XmRegionOffset( XmRegion pRegion, int x, int y) ;
+FUNC void _XmRegionIntersect( XmRegion reg1, XmRegion reg2, XmRegion newReg) ;
+FUNC void _XmRegionUnion( XmRegion reg1, XmRegion reg2, XmRegion newReg) ;
+FUNC void _XmRegionSubtract( XmRegion regM, XmRegion regS, XmRegion regD) ;
+FUNC Boolean _XmRegionIsEmpty( XmRegion r) ;
+FUNC Boolean _XmRegionEqual( XmRegion r1, XmRegion r2) ;
+FUNC Boolean _XmRegionPointInRegion( XmRegion pRegion, int x, int y) ;
+FUNC void _XmRegionClear(XmRegion r ) ;
+FUNC void _XmRegionShrink(XmRegion r, int dx, int dy) ;
+FUNC void _XmRegionDrawShadow(Display	*display, Drawable d, GC top_gc,
			GC bottom_gc, XmRegion region,
			Dimension border_thick, Dimension shadow_thick,
			unsigned int shadow_type ) ;

+FUNC void _XmDragUnderAnimation( Widget w, XtPointer clientData, XtPointer callData) ;

#
#	The "recursive" relationship between XmP and BaseClass
#	made tspec unhappy, and later, I couldn't get the build
#	to accept _XmFastSubClassInit as a definition for a token.
#	So, I'm defining the necessary bits here.  These really
#	should be abstracted, and put in BaseClassP.h, I think.

/* 
+TYPEDEF Cardinal (*XmGetSecResDataFunc)( WidgetClass, XmSecondaryResourceData **);

+FIELD (struct) _XmObjectClassExtRec := {
    XtPointer 		next_extension;	
    XrmQuark 		record_type;	
    long 		version;	
    Cardinal 		record_size;	
};

+TYPEDEF _XmObjectClassExtRec XmObjectClassExtRec;

+TYPEDEF XmObjectClassExtRec *XmObjectClassExt;

+FIELD (struct) _XmGenericClassExtRec := {
    XtPointer 		next_extension;	
    XrmQuark 		record_type;	
    long 		version;	
    Cardinal 		record_size;	
};

+TYPEDEF _XmGenericClassExtRec XmGenericClassExtRec;
+TYPEDEF XmGenericClassExtRec *XmGenericClassExt;

+FIELD (struct) _XmWrapperDataRec := {
    _XmWrapperDataRec *next;
    WidgetClass		widgetClass;
    XtInitProc		initializeLeaf;
    XtSetValuesFunc	setValuesLeaf;
    XtArgsProc		getValuesLeaf;
    XtRealizeProc	realize;
    XtWidgetClassProc	classPartInitLeaf;
    XtWidgetProc	resize;
    XtGeometryHandler   geometry_manager;
};

+TYPEDEF _XmWrapperDataRec XmWrapperDataRec;
+TYPEDEF XmWrapperDataRec *XmWrapperData;

+FIELD (struct) _XmBaseClassExtRec := {
    XtPointer 		next_extension;	
    XrmQuark 		record_type;	
    long 		version;	
    Cardinal 		record_size;	
    XtInitProc		initializePrehook;
    XtSetValuesFunc 	setValuesPrehook;
    XtInitProc		initializePosthook;
    XtSetValuesFunc 	setValuesPosthook;
    WidgetClass		secondaryObjectClass;
    XtInitProc		secondaryObjectCreate;
    XmGetSecResDataFunc	getSecResData;
    unsigned char	flags[32];
    XtArgsProc		getValuesPrehook;
    XtArgsProc		getValuesPosthook;
    XtWidgetClassProc	classPartInitPrehook;
    XtWidgetClassProc	classPartInitPosthook;
    XtResourceList	ext_resources;
    XtResourceList	compiled_ext_resources;
    Cardinal		num_ext_resources;
    Boolean		use_sub_resources;
    XmWidgetNavigableProc widgetNavigable;
    XmFocusChangeProc	focusChange;
    XmWrapperData	wrapperData;
};

+TYPEDEF _XmBaseClassExtRec XmBaseClassExtRec;
+TYPEDEF XmBaseClassExtRec *XmBaseClassExt;

+FIELD (struct) _XmWidgetExtDataRec := {
    Widget		widget;
    Widget		reqWidget;
    Widget		oldWidget;
};

+TYPEDEF _XmWidgetExtDataRec XmWidgetExtDataRec;
+TYPEDEF XmWidgetExtDataRec *XmWidgetExtData;

+EXP lvalue XrmQuark		XmQmotif;
+EXP lvalue int 	_XmInheritClass;

+DEFINE _XmBCEPTR(wc)	%% ((XmBaseClassExt *)(&(((WidgetClass)(wc))->core_class.extension))) %%;
+DEFINE _XmBCE(wc)	%% ((XmBaseClassExt)(((WidgetClass)(wc))->core_class.extension)) %%;
+DEFINE _XmGetBaseClassExtPtr(wc, owner) %% ((_XmBCE(wc) && (((_XmBCE(wc))->record_type) == owner)) ? _XmBCEPTR(wc) : ((XmBaseClassExt *) _XmGetClassExtensionPtr(((XmGenericClassExt *) _XmBCEPTR( wc)), owner))) %%;

+DEFINE _XmGetFlagsBit(field, bit) %% ((field[ (bit >> 3) ]) & (1 << (bit & 0x07))) %%;

+DEFINE _XmSetFlagsBit(field, bit) %% (field[ (bit >> 3) ] |= (1 << (bit & 0x07))) %%;

+DEFINE _XmFastSubclassInit(wc, bit_field) %% {XmBaseClassExt * _Xm_fastPtr;if(_Xm_fastPtr = _XmGetBaseClassExtPtr( wc, XmQmotif)) _XmSetFlagsBit((*_Xm_fastPtr)->flags, bit_field) ;} %%;

+DEFINE _XmIsFastSubclass(wc, bit) %% (_XmGetFlagsBit( ((*_XmGetBaseClassExtPtr((wc),XmQmotif))->flags), bit) ? TRUE : FALSE) %%;

*/


/*
 *	Replacement defines for fast subclass operations
 */

%%

#undef XmIsCascadeButton
#define XmIsCascadeButton(w)  \
  (_XmIsFastSubclass(XtClass(w), XmCASCADE_BUTTON_BIT))

#undef XmIsCascadeButtonGadget
#define XmIsCascadeButtonGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmCASCADE_BUTTON_GADGET_BIT))

#undef XmIsCommandBox
#define XmIsCommandBox(w)  \
  (_XmIsFastSubclass(XtClass(w), XmCOMMAND_BOX_BIT))

#undef XmIsDialogShell
#define XmIsDialogShell(w)  \
  (_XmIsFastSubclass(XtClass(w), XmDIALOG_SHELL_BIT))

#undef XmIsDisplay
#define XmIsDisplay(w)  \
  (_XmIsFastSubclass(XtClass(w), XmDISPLAY_BIT))

#undef XmIsList
#define XmIsList(w)  \
  (_XmIsFastSubclass(XtClass(w), XmLIST_BIT))

#undef XmIsForm
#define XmIsForm(w)  \
  (_XmIsFastSubclass(XtClass(w), XmFORM_BIT))

#undef XmIsTextField
#define XmIsTextField(w)  \
  (_XmIsFastSubclass(XtClass(w), XmTEXT_FIELD_BIT))

#undef XmIsGadget
#define XmIsGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmGADGET_BIT))

#undef XmIsLabel
#define XmIsLabel(w)  \
  (_XmIsFastSubclass(XtClass(w), XmLABEL_BIT))

#undef XmIsLabelGadget
#define XmIsLabelGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmLABEL_GADGET_BIT))

#undef XmIsMainWindow
#define XmIsMainWindow(w)  \
  (_XmIsFastSubclass(XtClass(w), XmMAIN_WINDOW_BIT))

#undef XmIsManager
#define XmIsManager(w)  \
  (_XmIsFastSubclass(XtClass(w), XmMANAGER_BIT))

#undef XmIsMenuShell
#define XmIsMenuShell(w)  \
  (_XmIsFastSubclass(XtClass(w), XmMENU_SHELL_BIT))

#undef XmIsDrawnButton
#define XmIsDrawnButton(w)  \
  (_XmIsFastSubclass(XtClass(w), XmDRAWN_BUTTON_BIT))

#undef XmIsPrimitive
#define XmIsPrimitive(w)  \
  (_XmIsFastSubclass(XtClass(w), XmPRIMITIVE_BIT))

#undef XmIsPushButton
#define XmIsPushButton(w)  \
  (_XmIsFastSubclass(XtClass(w), XmPUSH_BUTTON_BIT))

#undef XmIsPushButtonGadget
#define XmIsPushButtonGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmPUSH_BUTTON_GADGET_BIT))

#undef XmIsRowColumn
#define XmIsRowColumn(w)  \
  (_XmIsFastSubclass(XtClass(w), XmROW_COLUMN_BIT))

#undef XmIsScreen
#define XmIsScreen(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSCREEN_BIT))

#undef XmIsScrollBar
#define XmIsScrollBar(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSCROLL_BAR_BIT))

#undef XmIsScrolledWindow
#define XmIsScrolledWindow(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSCROLLED_WINDOW_BIT))

#undef XmIsSelectionBox
#define XmIsSelectionBox(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSELECTION_BOX_BIT))

#undef XmIsSeparator
#define XmIsSeparator(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSEPARATOR_BIT))

#undef XmIsSeparatorGadget
#define XmIsSeparatorGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSEPARATOR_GADGET_BIT))

#undef XmIsText
#define XmIsText(w)  \
  (_XmIsFastSubclass(XtClass(w), XmTEXT_BIT))

#undef XmIsToggleButton
#define XmIsToggleButton(w)  \
  (_XmIsFastSubclass(XtClass(w), XmTOGGLE_BUTTON_BIT))

#undef XmIsToggleButtonGadget
#define XmIsToggleButtonGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmTOGGLE_BUTTON_GADGET_BIT))

#undef XmIsArrowButton
#define XmIsArrowButton(w)  \
  (_XmIsFastSubclass(XtClass(w), XmARROW_BUTTON_BIT))

#undef XmIsArrowButtonGadget
#define XmIsArrowButtonGadget(w)  \
  (_XmIsFastSubclass(XtClass(w), XmARROW_BUTTON_GADGET_BIT))

#undef XmIsBulletinBoard
#define XmIsBulletinBoard(w)  \
  (_XmIsFastSubclass(XtClass(w), XmBULLETIN_BOARD_BIT))

#undef XmIsDrawingArea
#define XmIsDrawingArea(w)  \
  (_XmIsFastSubclass(XtClass(w), XmDRAWING_AREA_BIT))

#undef XmIsFileSelectionBox
#define XmIsFileSelectionBox(w)  \
  (_XmIsFastSubclass(XtClass(w), XmFILE_SELECTION_BOX_BIT))

#undef XmIsFrame
#define XmIsFrame(w)  \
  (_XmIsFastSubclass(XtClass(w), XmFRAME_BIT))

#undef XmIsMessageBox
#define XmIsMessageBox(w)  \
  (_XmIsFastSubclass(XtClass(w), XmMESSAGE_BOX_BIT))

#undef XmIsSash
#define XmIsSash(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSASH_BIT))

#undef XmIsScale
#define XmIsScale(w)  \
  (_XmIsFastSubclass(XtClass(w), XmSCALE_BIT))

#undef XmIsPanedWindow
#define XmIsPanedWindow(w)  \
  (_XmIsFastSubclass(XtClass(w), XmPANED_WINDOW_BIT))

%%
