# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/lib", "X11/Xlib.h.ts" ;

+SUBSET "widget" := {
    # Core Widgets (1.4.1)
    +TYPE ( struct ) WidgetClassRec ;
    +TYPEDEF WidgetClassRec *WidgetClass ;
    +EXP lvalue WidgetClass widgetClass ;
    +TYPE ( struct ) WidgetRec ;
    +TYPEDEF WidgetRec *Widget ;


    # Core Widgets (1.4.1)
    +TYPE ( struct ) CoreClassRec ;
    +TYPEDEF CoreClassRec *CoreWidgetClass ;
    +EXP lvalue WidgetClass coreWidgetClass ;
    +TYPE ( struct ) CoreRec ;
    +TYPEDEF CoreRec *CoreWidget ;


    # Composite Widgets (1.4.2)
    +TYPE ( struct ) CompositeClassRec ;
    +TYPEDEF CompositeClassRec *CompositeWidgetClass ;
    +EXP lvalue WidgetClass compositeWidgetClass ;
    +TYPE ( struct ) CompositeRec ;
    +TYPEDEF CompositeRec *CompositeWidget ;


    # Constraint Widgets (1.4.2)
    +TYPE ( struct ) ConstraintClassRec ;
    +TYPEDEF ConstraintClassRec *ConstraintWidgetClass ;
    +EXP lvalue WidgetClass constraintWidgetClass ;
    +TYPE ( struct ) ConstraintRec ;
    +TYPEDEF ConstraintRec *ConstraintWidget ;


    # ObjectClassPart Definition (12.2.1)
    +TYPE ( struct ) ObjectClassRec ;
    +TYPEDEF ObjectClassRec *ObjectClass ;
    +EXP lvalue WidgetClass objectClass ;


    # ObjectPart Definition (12.2.2)
    +TYPE ( struct ) ObjectRec ;
    +TYPEDEF ObjectRec *Object ;


    # RectObjClassPart Definition (12.3.1)
    +TYPE ( struct ) RectObjClassRec ;
    +TYPEDEF RectObjClassRec *RectObjClass ;
    +EXP lvalue WidgetClass rectObjClass ;


    # RectObjPart Definition (12.3.2)
    +TYPE ( struct ) RectObjRec ;
    +TYPEDEF RectObjRec *RectObj ;
} ;

+USE "x5/t", "X11/Object.h.ts" ;
+USE "x5/t", "X11/RectObj.h.ts" ;


# Implementation-specific types (1.5)

+TYPE ( int ) Boolean ;
+TYPE ( int ) Cardinal ;
+TYPE ( int ) Dimension ;
+TYPE ( int ) Position ;
+TYPEDEF void *XtPointer ;	# That's what it says
+TYPE ( int ) XtEnum ;

+DEFINE TRUE %% True %% ;
+DEFINE FALSE %% False %% ;


# Definition of XtArgVal and conversions (1.5)

+TYPE XtArgVal ;
+TOKEN __MyXtArgValToPtr
%% PROC { TYPE t, EXP rvalue : XtArgVal : e | EXP e } EXP rvalue : t * : %% ;
+TOKEN __MyPtrToXtArgVal
%% PROC { TYPE t, EXP rvalue : t * : e | EXP e } EXP rvalue : XtArgVal : %% ;
+TOKEN __MyXtArgValToInt
%% PROC { VARIETY v, EXP rvalue : XtArgVal : e | EXP e } EXP rvalue : v : %% ;
+TOKEN __MyIntToXtArgVal
%% PROC { VARIETY v, EXP rvalue : v : e | EXP e } EXP rvalue : XtArgVal : %% ;

+IFNDEF ~building_libs
%%
#pragma accept conversion __MyXtArgValToPtr
#pragma accept conversion __MyPtrToXtArgVal
#pragma accept conversion __MyXtArgValToInt
#pragma accept conversion __MyIntToXtArgVal
%%
+ENDIF


# Widget Naming Conventions (1.6.1)

+TYPEDEF char *String ;


# CorePart Default Values (1.4.1.4)

+CONST String XtDefaultForeground, XtDefaultBackground ;
+CONST Pixmap XtUnspecifiedPixmap ;


# Widget Class and Superclass Look up (1.6.5)

+FUNC WidgetClass XtClass ( Widget ) ;
+FUNC WidgetClass XtSuperclass ( Widget ) ;


# Widget Subclass Verification (1.6.6)

+FUNC Boolean XtIsSubclass ( Widget, WidgetClass ) ;
+FUNC Boolean XtIsObject ( Widget ) ;
+FUNC Boolean XtIsRectObj ( Widget ) ;
+FUNC Boolean XtIsWidget ( Widget ) ;
+FUNC Boolean XtIsComposite ( Widget ) ;
+FUNC Boolean XtIsConstraint ( Widget ) ;
+FUNC Boolean XtIsShell ( Widget ) ;
+FUNC Boolean XtIsOverrideShell ( Widget ) ;
+FUNC Boolean XtIsWMShell ( Widget ) ;
+FUNC Boolean XtIsVendorShell ( Widget ) ;
+FUNC Boolean XtIsTransientShell ( Widget ) ;
+FUNC Boolean XtIsTopLevelShell ( Widget ) ;
+FUNC Boolean XtIsApplicationShell ( Widget ) ;


# Initializing a Widget Class (1.6.9)

+FUNC void XtInitializeWidgetClass ( WidgetClass ) ;


# Initializing the X Toolkit (2.1)

+IFNDEF __TDF_XTAPPCONTEXT_PTR
+TYPE XtAppContext ;				# opaque, as specified
+ELSE
+TYPE ~XtAppContextRec ;
+TYPEDEF ~XtAppContextRec *XtAppContext.1 ;	# TK/RW: Motif 1.2 requires ptr
+ENDIF

+FUNC void XtToolkitInitialize ( void ) ;
+FUNC XtAppContext XtCreateApplicationContext ( void ) ;
+FUNC void XtDestroyApplicationContext ( XtAppContext ) ;
+FUNC XtAppContext XtWidgetToApplicationContext ( Widget ) ;
+FUNC void XtDisplayInitialize ( XtAppContext, Display *, String, String,
    XrmOptionDescRec *, Cardinal, int *, String * ) ;
+FUNC Display *XtOpenDisplay ( XtAppContext, String, String, String,
    XrmOptionDescRec *, Cardinal, int *, String * ) ;
+FUNC void XtCloseDisplay ( Display * ) ;


# Establishing the Locale (2.2)

+TYPEDEF String ( *XtLanguageProc ) ( Display *, String, XtPointer ) ;
+FUNC XtLanguageProc XtSetLanguageProc ( XtAppContext, XtLanguageProc,
    XtPointer ) ;


# Loading the Resource Database (2.3)

+FUNC XrmDatabase XtScreenDatabase ( Screen * ) ;
+FUNC XrmDatabase XtDatabase ( Display * ) ;
+FUNC void XtAppSetFallbackResources ( XtAppContext, String * ) ;


# Creating and Merging Argument Lists (2.5.1)

+FIELD ( struct ) Arg := {
    String name ;
    XtArgVal value ;
} ;
+TYPEDEF Arg *ArgList ;

+MACRO void XtSetArg ( lvalue Arg, String, XtArgVal ) ;
+FUNC ArgList XtMergeArgLists ( ArgList, Cardinal, ArgList, Cardinal ) ;

+CONST String XtVaTypedArg, XtVaNestedList ;
+TYPEDEF XtPointer XtVarArgsList ;
+FUNC XtVarArgsList XtVaCreateArgsList ( XtPointer, ... ) ;


# Creating a Widget Instance (2.5.2)

+FUNC Widget XtCreateWidget ( String,
    WidgetClass, Widget, ArgList, Cardinal ) ;
+FUNC Widget XtVaCreateWidget ( String,
    WidgetClass, Widget, ... ) ;


# Creating an Application Shell Instance (2.5.3)

+FUNC Widget XtAppCreateShell ( String, String,
    WidgetClass, Display *, ArgList, Cardinal ) ;
+FUNC Widget XtVaAppCreateShell ( String, String,
    WidgetClass, Display *, ... ) ;


# Convenience Procedures to Initialize an Application (2.5.4)

+FUNC Widget XtAppInitialize ( XtAppContext *, String,
    XrmOptionDescList, Cardinal, int *, String *, String *, ArgList,
    Cardinal ) ;
+FUNC Widget XtVaAppInitialize ( XtAppContext *, String,
    XrmOptionDescList, Cardinal, int *, String *, String *, ... ) ;


# Widget Instance Initialization : the initialize Procedure (2.5.5)

+TYPEDEF void ( *XtInitProc ) ( Widget, Widget, ArgList, Cardinal * ) ;


# Nonwidget Data Initialization : the initialize_hook Procedure (2.5.7)

+TYPEDEF void ( *XtArgsProc ) ( Widget, ArgList, Cardinal * ) ;


# Realizing Widgets (2.6)

+FUNC void XtRealizeWidget ( Widget ) ;
+FUNC Boolean XtIsRealized ( Widget ) ;


# Widget Instance Window Creation : the realize Procedure (2.6.1)

+TYPE ( int ) XtValueMask ;	# RCA : not specified
+TYPEDEF void ( *XtRealizeProc ) ( Widget, XtValueMask *,
    XSetWindowAttributes * ) ;


# Window Creation Convenience Routine (2.6.2)

+FUNC void XtCreateWindow ( Widget, unsigned int, Visual *,
    XtValueMask, XSetWindowAttributes * ) ;


# Obtaining Window Information from a Widget (2.7)

+FUNC Display *XtDisplay ( Widget ) ;
+FUNC Widget XtParent ( Widget ) ;
+FUNC Screen *XtScreen ( Widget ) ;
+FUNC Window XtWindow ( Widget ) ;
+FUNC Display *XtDisplayOfObject ( Widget ) ;
+FUNC Screen *XtScreenOfObject ( Widget ) ;
+FUNC Window XtWindowOfObject ( Widget ) ;
+FUNC String XtName ( Widget ) ;


# Unrealizing Widgets (2.7.1)

+FUNC void XtUnrealizeWidget ( Widget ) ;


# Destroying Widgets (2.8)

+FUNC void XtDestroyWidget ( Widget ) ;


# Dynamic Data Deallocation : the destroy Procedure (2.8.2)

+TYPEDEF void ( *XtWidgetProc ) ( Widget ) ;


# Insertion Order of Children : the insert_position procedure (3.2)

+TYPEDEF Cardinal ( *XtOrderProc ) ( Widget ) ;


# Managing Children (3.4.1)

+TYPEDEF Widget *WidgetList ;
+FUNC void XtManageChildren ( WidgetList, Cardinal ) ;	# RCA
+FUNC void XtManageChild ( Widget ) ;
+FUNC Widget XtCreateManagedWidget ( String,
    WidgetClass, Widget, ArgList, Cardinal ) ;
+FUNC Widget XtVaCreateManagedWidget ( String,
    WidgetClass, Widget, ... ) ;


# Unmanaging Children (3.4.2)

+FUNC void XtUnmanageChildren ( WidgetList, Cardinal ) ; # RCA
+FUNC void XtUnmanageChild ( Widget ) ;


# Determining if a Widget is Managed (3.4.3)

+FUNC Boolean XtIsManaged ( Widget ) ;


# Controlling when Widgets get Mapped (3.5)

+FUNC void XtSetMappedWhenManaged ( Widget, Boolean ) ;
+FUNC void XtMapWidget ( Widget ) ;
+FUNC void XtUnmapWidget ( Widget ) ;


# Shell Part Default Values (4.1.4)

+CONST int XtUnspecifiedWindow ;
+CONST int XtUnspecifiedWindowGroup ;
+CONST int XtUnspecifiedShellInt ;


# Creating a Pop-up Shell (5.2)

+FUNC Widget XtCreatePopupShell ( String,
    WidgetClass, Widget, ArgList, Cardinal ) ;
+FUNC Widget XtVaCreatePopupShell ( String,
    WidgetClass, Widget, ... ) ;


# Mapping a Pop-up Widget (5.4)

+ENUM XtGrabKind := { XtGrabNone, XtGrabNonexclusive, XtGrabExclusive } ;
+TYPEDEF void ( *XtCreatePopupChildProc ) ( Widget ) ;

+FUNC void XtPopup ( Widget, XtGrabKind ) ;
+FUNC void XtPopupSpringLoaded ( Widget ) ;
+FUNC void XtCallbackNone ( Widget, XtPointer, XtPointer ) ;
+FUNC void XtCallbackNonexclusive ( Widget, XtPointer, XtPointer ) ;
+FUNC void XtCallbackExclusive ( Widget, XtPointer, XtPointer ) ;
+FUNC void XtMenuPopup ( String ) ;
+FUNC void MenuPopup ( String ) ;
+FUNC void XtMenuPopupAction ( Widget, XEvent *, String *, Cardinal * ) ;


# Unmapping a Pop-up Widget (5.5)

+FUNC void XtPopdown ( Widget ) ;
+FUNC void XtCallbackPopdown ( Widget, XtPointer, XtPointer ) ;

+FIELD ( struct ) XtPopdownIDRec := {
    Widget shell_widget ;
    Widget enable_widget ;
} ;

+TYPEDEF XtPopdownIDRec *XtPopdownID ;

+FUNC void XtMenuPopdown ( String ) ;
+FUNC void MenuPopdown ( String ) ;


# General Geometry Manager Requests (6.2)

+TYPE ( int ) XtGeometryMask ;	# RCA : MIT disagrees with spec

+FIELD ( struct ) XtWidgetGeometry := {
    XtGeometryMask request_mode ;
    Position x, y ;
    Dimension width, height ;
    Dimension border_width ;
    Widget sibling ;
    int stack_mode ;
} ;

+ENUM XtGeometryResult := {
    XtGeometryYes,
    XtGeometryNo,
    XtGeometryAlmost,
    XtGeometryDone
} ;

+FUNC XtGeometryResult XtMakeGeometryRequest ( Widget,
    XtWidgetGeometry *, XtWidgetGeometry * ) ;

+DEFINE XtCWQueryOnly		%% (1<<7) %% ;
+DEFINE XtSMDontChange		%% 5 %% ;


# Resize Requests (6.3)

+FUNC XtGeometryResult XtMakeResizeRequest ( Widget,
    Dimension, Dimension, Dimension *, Dimension * ) ;


# Child Geometry Management : the geometry_manager Procedure (6.5)

+TYPEDEF XtGeometryResult ( *XtGeometryHandler ) ( Widget,
    XtWidgetGeometry *, XtWidgetGeometry * ) ;


# Widget Placement and Sizing (6.6)

+FUNC void XtMoveWidget ( Widget, Position, Position ) ;
+FUNC void XtResizeWidget ( Widget, Dimension, Dimension,
    Dimension ) ;
+FUNC void XtConfigureWidget ( Widget, Position, Position,
    Dimension, Dimension, Dimension ) ;
+FUNC void XtResizeWindow ( Widget ) ;


# Preferred Geometry (6.7)

+FUNC XtGeometryResult XtQueryGeometry ( Widget,
    XtWidgetGeometry *, XtWidgetGeometry * ) ; 


# Adding and Removing Input Sources (7.1.1)

+TYPE ( int ) XtInputId ;		# RCA : not specified
+TYPEDEF void ( *XtInputCallbackProc ) ( XtPointer, int *, XtInputId * ) ;

+CONST int XtInputReadMask, XtInputWriteMask, XtInputExceptMask ;

+FUNC XtInputId XtAppAddInput ( XtAppContext, int, XtPointer,
    XtInputCallbackProc, XtPointer ) ;
+FUNC void XtRemoveInput ( XtInputId ) ;


# Adding and Removing Timeouts (7.1.2)

+TYPE ( int ) XtIntervalId ;		# RCA : not specified
+TYPEDEF void ( *XtTimerCallbackProc ) ( XtPointer, XtIntervalId * ) ;

+FUNC XtIntervalId XtAppAddTimeOut ( XtAppContext, unsigned long,
    XtTimerCallbackProc, XtPointer ) ;
+FUNC void XtRemoveTimeOut ( XtIntervalId ) ;


# Constraining Events to a Cascade of Widgets (7.2)

+FUNC void XtAddGrab ( Widget, Boolean, Boolean ) ;
+FUNC void XtRemoveGrab ( Widget ) ;


# Requesting Key and Button Grabs (7.2.1)

+TYPEDEF unsigned int Modifiers ;	# Why?
+FUNC void XtGrabKey ( Widget, KeyCode, Modifiers, Boolean,
    int, int ) ;
+FUNC void XtUngrabKey ( Widget, KeyCode, Modifiers ) ;
+FUNC int XtGrabKeyboard ( Widget, Boolean, int, int, Time ) ;
+FUNC void XtUngrabKeyboard ( Widget, Time ) ;
+FUNC void XtGrabButton ( Widget, int, Modifiers,
    Boolean, unsigned int, int, int, Window, Cursor ) ;
+FUNC void XtUngrabButton ( Widget, unsigned int, Modifiers ) ;
+FUNC int XtGrabPointer ( Widget, Boolean, unsigned int,
    int, int, Window, Cursor, Time ) ;
+FUNC void XtUngrabPointer ( Widget, Time ) ;


# Focusing Events on a Child (7.3)

+TYPEDEF Boolean ( *XtAcceptFocusProc ) ( Widget, Time * ) ;

+FUNC void XtSetKeyboardFocus ( Widget, Widget ) ;
+FUNC Boolean XtCallAcceptFocus ( Widget, Time * ) ;


# Querying Event Sources (7.4)

+TYPE ( int ) XtInputMask ;
+CONST XtInputMask XtIMXEvent, XtIMTimer, XtIMAlternateInput, XtIMAll ;
+FUNC XtInputMask XtAppPending ( XtAppContext ) ;
+FUNC Boolean XtAppPeekEvent ( XtAppContext, XEvent * ) ;
+FUNC void XtAppNextEvent ( XtAppContext, XEvent * ) ;


# Dispatching Events (7.5)

+FUNC void XtAppProcessEvent ( XtAppContext, XtInputMask ) ;
+FUNC Boolean XtDispatchEvent ( XEvent * ) ;


# The Application Input Loop (7.6)

+FUNC void XtAppMainLoop ( XtAppContext ) ;


# Checking and Setting the Sensitivity State of a Widget (7.7)

+FUNC void XtSetSensitive ( Widget, Boolean ) ;
+FUNC Boolean XtIsSensitive ( Widget ) ;


# Adding Background Work Procedures (7.8)

+TYPE ( int ) XtWorkProcId ;		# RCA : not specified
+TYPEDEF Boolean ( *XtWorkProc ) ( XtPointer ) ;

+FUNC XtWorkProcId XtAppAddWorkProc ( XtAppContext, XtWorkProc, XtPointer ) ;
+FUNC void XtRemoveWorkProc ( XtWorkProcId ) ;


# Exposure Compression (7.9.3)

+DEFINE XtExposeNoCompress	%% ((XtEnum) False) %% ;
+DEFINE XtExposeCompressSeries	%% ((XtEnum) True) %% ;

+CONST XtEnum XtExposeCompressMultiple, XtExposeCompressMaximal ;
+CONST XtEnum XtExposeGraphicsExpose, XtExposeGraphicsExposeMerged ;
+CONST XtEnum XtExposeNoExpose ;


# Redisplay of a Widget : the expose Procedure

+TYPEDEF void ( *XtExposeProc ) ( Widget, XEvent *, Region ) ;


# X Event Handlers (7.11)

+TYPEDEF void ( *XtEventHandler ) ( Widget, XtPointer, XEvent *, Boolean * ) ;


# Event Handlers that Select Events (7.11.1)

+TYPE ( int ) EventMask ;	# RCA : not specified
+CONST EventMask XtAllEvents ;
+ENUM XtListPosition := { XtListHead, XtListTail } ;

+FUNC void XtAddEventHandler ( Widget, EventMask, Boolean,
    XtEventHandler, XtPointer ) ;
+FUNC void XtRemoveEventHandler ( Widget, EventMask, Boolean,
    XtEventHandler, XtPointer ) ;
+FUNC void XtInsertEventHandler ( Widget, EventMask, Boolean,
    XtEventHandler, XtPointer, XtListPosition ) ;


# Event Handlers that do not Select Events (7.11.2)

+FUNC void XtAddRawEventHandler ( Widget, EventMask,
    Boolean, XtEventHandler, XtPointer ) ;
+FUNC void XtRemoveRawEventHandler ( Widget, EventMask,
    Boolean, XtEventHandler, XtPointer ) ;
+FUNC void XtInsertRawEventHandler ( Widget, EventMask,
    Boolean, XtEventHandler, XtPointer, XtListPosition ) ;


# Current Event Mask (7.11.3)

+FUNC EventMask XtBuildEventMask ( Widget ) ;


# Using Callback Procedure and Callback List Definitions (8.1)

+TYPEDEF void ( *XtCallbackProc ) ( Widget, XtPointer, XtPointer ) ;

+FIELD ( struct ) XtCallbackRec := {
    XtCallbackProc callback ;
    XtPointer closure ;
} ;

+TYPEDEF XtCallbackRec *XtCallbackList ;


# Adding Callback Procedures (8.3)

+FUNC void XtAddCallback ( Widget, String, XtCallbackProc,
    XtPointer ) ;
+FUNC void XtAddCallbacks ( Widget, String, XtCallbackList ) ;


# Removing Callback Procedures (8.4)

+FUNC void XtRemoveCallback ( Widget, String, XtCallbackProc,
    XtPointer ) ;
+FUNC void XtRemoveCallbacks ( Widget, String, XtCallbackList ) ;
+FUNC void XtRemoveAllCallbacks ( Widget, String ) ;


# Executing Callback Procedures (8.5)

+FUNC void XtCallCallbacks ( Widget, String, XtPointer ) ;
+FUNC void XtCallCallbackList ( Widget, XtCallbackList,
    XtPointer ) ;


# Checking the Status of a Callback List (8.6)

+ENUM XtCallbackStatus := {
    XtCallbackNoList,
    XtCallbackHasNone,
    XtCallbackHasSome
} ;

+FUNC XtCallbackStatus XtHasCallbacks ( Widget, String ) ;


# Resource Lists (9.1)

+FIELD ( struct ) XtResource := {
    String resource_name ;
    String resource_class ;
    String resource_type ;
    Cardinal resource_size ;
    Cardinal resource_offset ;
    String default_type ;
    XtPointer default_addr ;
} ;

+TYPEDEF XtResource *XtResourceList ;
+TYPEDEF void ( *XtResourceDefaultProc ) ( Widget, int, XrmValue * ) ;

+FUNC void XtGetResourceList ( WidgetClass,
    XtResourceList *, Cardinal * ) ;
+FUNC void XtGetConstraintResourceList ( WidgetClass,
    XtResourceList *, Cardinal * ) ;


# Byte Offset Calculations (9.2)

+TOKEN XtOffsetOf # This is tricky
%% PROC { STRUCT s, TYPE t, MEMBER t : s : m |\
   TYPE s, MEMBER s : m } EXP rvalue : Cardinal : %% ;

+TOKEN XtOffset # This is tricky
%% PROC { STRUCT s, TYPE t, MEMBER t : s : m |\
   TYPE s *, MEMBER s : m } EXP rvalue : Cardinal : %% ;


# Subresources (9.4)

+FUNC void XtGetSubresources ( Widget, XtPointer, String,
    String, XtResourceList, Cardinal, ArgList, Cardinal ) ;
+FUNC void XtVaGetSubresources ( Widget, XtPointer, String,
    String, XtResourceList, Cardinal, ... ) ;


# Obtaining Application Resources (9.5)

+FUNC void XtGetApplicationResources ( Widget, XtPointer,
    XtResourceList, Cardinal, ArgList, Cardinal ) ;
+FUNC void XtVaGetApplicationResources ( Widget, XtPointer,
    XtResourceList, Cardinal, ... ) ;


# Predefined Resource Converters (9.6.1)

+TYPEDEF unsigned long Pixel ;	# RW : not specified but example suggests same
				# type as XColor.pixel, as required by Motif 1.2

+FUNC Boolean XtCvtStringToAcceleratorTable (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToAtom (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToBoolean (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToBool (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToCursor (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToDimension (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToDisplay (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToFile (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToFloat (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToFont (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToFontSet (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToFontStruct (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToInitialState (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToInt (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToPixel (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToPosition (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToShort (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToTranslationTable (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToUnsignedChar (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtStringToVisual (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;

+FUNC Boolean XtCvtColorToPixel (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;

+FUNC Boolean XtCvtIntToBoolean (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToBool (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToColor (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToDimension (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToFloat (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToFont (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToPixel (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToPixmap (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToPosition (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToShort (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;
+FUNC Boolean XtCvtIntToUnsignedChar (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;

+FUNC Boolean XtCvtPixelToColor (
    Display *, XrmValue *, Cardinal *, XrmValue *, XrmValue *, XtPointer * ) ;

+CONST String XtDefaultFont, XtDefaultFontSet ;


# New Resource Converters (9.6.2)

+TYPEDEF Boolean ( *XtTypeConverter ) ( Display *, XrmValue *, Cardinal *,
    XrmValue *, XrmValue *, XtPointer * ) ;
+TYPEDEF void ( *XtDestructor ) ( XtAppContext, XrmValue *, XtPointer,
    XrmValue *, Cardinal * ) ;


# Issuing Conversion Warnings (9.6.3)

+FUNC void XtDisplayStringConversionWarning ( Display *, String, String ) ;
+FUNC XtAppContext XtDisplayToApplicationContext ( Display * ) ;


# Registering a New Resource Converter (9.6.4)

+TYPEDEF int XtCacheType ;
+CONST XtCacheType XtCacheNone, XtCacheAll, XtCacheByDisplay ;
+CONST XtCacheType XtCacheRefCount ;

+ENUM XtAddressMode := {
    XtAddress,
    XtBaseOffset,
    XtImmediate,
    XtResourceString,
    XtResourceQuark,
    XtWidgetBaseOffset,
    XtProcedureArg
} ;

+FIELD ( struct ) XtConvertArgRec := {
    XtAddressMode address_mode ;
    XtPointer address_id ;
    Cardinal size ;
} ;

+TYPEDEF XtConvertArgRec *XtConvertArgList ;

+TYPEDEF void ( *XtConvertArgProc ) ( Widget, Cardinal *, XrmValue * ) ;

+EXP XtConvertArgList colorConvertArgs, screenConvertArg ;

+FUNC void XtSetTypeConverter ( String, String, XtTypeConverter,
    XtConvertArgList, Cardinal, XtCacheType, XtDestructor ) ;
+FUNC void XtAppSetTypeConverter ( XtAppContext, String, String,
    XtTypeConverter, XtConvertArgList, Cardinal, XtCacheType,
    XtDestructor ) ;


# Resource Converter Invocation (9.6.5)

+TYPEDEF XtPointer XtCacheRef ;

+FUNC Boolean XtCallConverter ( Display *, XtTypeConverter, XrmValuePtr,
    Cardinal, XrmValuePtr, XrmValuePtr, XtCacheRef * ) ;
+FUNC void XtAppReleaseCacheRefs ( XtAppContext, XtCacheRef * ) ;
+FUNC void XtCallbackReleaseCacheRef ( Widget, XtPointer, XtPointer ) ;
+FUNC void XtCallbackReleaseCacheRefList ( Widget, XtPointer, XtPointer ) ;
+FUNC Boolean XtConvertAndStore ( Widget, String, XrmValuePtr,
    String, XrmValuePtr ) ;


# Obtaining Widget State (9.7.1)

+FUNC void XtGetValues ( Widget, ArgList, Cardinal ) ;
+FUNC void XtVaGetValues ( Widget, ... ) ;

+FUNC void XtGetSubvalues ( XtPointer, XtResourceList, Cardinal,
    ArgList, Cardinal ) ;
+FUNC void XtVaGetSubvalues ( XtPointer, XtResourceList, Cardinal, ... ) ;


# Setting Widget State (9.7.2)

+FUNC void XtSetValues ( Widget, ArgList, Cardinal ) ;
+FUNC void XtVaSetValues ( Widget, ... ) ;

+TYPEDEF Boolean ( *XtSetValuesFunc ) ( Widget, Widget, Widget, ArgList,
    Cardinal * ) ;
+TYPEDEF void ( *XtAlmostProc ) ( Widget, Widget, XtWidgetGeometry *,
    XtWidgetGeometry * ) ;

+FUNC void XtSetSubvalues ( XtPointer, XtResourceList, Cardinal,
    ArgList, Cardinal ) ;
+FUNC void XtVaSetSubvalues ( XtPointer, XtResourceList, Cardinal, ... ) ;

+TYPEDEF Boolean ( *XtArgsFunc ) ( Widget, ArgList, Cardinal * ) ;


# Action Tables (10.1)

+TYPEDEF void ( *XtActionProc ) ( Widget, XEvent *, String *, Cardinal * ) ;

+FIELD ( struct ) XtActionsRec := {
    String string ;
    XtActionProc proc ;
} ;

+TYPEDEF XtActionsRec *XtActionList ;

+FUNC void XtAppAddActions ( XtAppContext, XtActionList, Cardinal ) ;

+TYPEDEF void ( *XtActionHookProc ) ( Widget, XtPointer, String, XEvent *,
    String *, Cardinal * ) ;

+TYPE XtActionHookId ;		# RCA : not specified
+FUNC XtActionHookId XtAppAddActionHook ( XtAppContext, XtActionHookProc,
    XtPointer ) ;
+FUNC void XtRemoveActionHook ( XtActionHookId ) ;


# Multi-click Time (10.2.3)

+FUNC void XtSetMultiClickTime ( Display *, int ) ;
+FUNC int XtGetMultiClickTime ( Display * ) ;


# Translation Table Management (10.3)

+TYPE XtTranslations ;
+FUNC XtTranslations XtParseTranslationTable ( String ) ;
+FUNC void XtAugmentTranslations ( Widget, XtTranslations ) ;
+FUNC void XtOverrideTranslations ( Widget, XtTranslations ) ;
+FUNC void XtUninstallTranslations ( Widget ) ;


# Using Accelerators (10.4)

+TYPE XtAccelerators ;
+TYPEDEF void ( *XtStringProc ) ( Widget, String ) ;
+FUNC XtAccelerators XtParseAcceleratorTable ( String ) ;
+FUNC void XtInstallAccelerators ( Widget, Widget ) ;
+FUNC void XtInstallAllAccelerators ( Widget, Widget ) ;


# KeyCode to KeySym Conversions (10.5)

+TYPEDEF void ( *XtKeyProc ) ( Display *, KeyCode, Modifiers,
    Modifiers *, KeySym * ) ;

+FUNC KeySym *XtGetKeysymTable ( Display *, KeyCode *, int * ) ;
+FUNC void XtSetKeyTranslator ( Display *, XtKeyProc ) ;
+FUNC void XtTranslateKey ( Display *, KeyCode, Modifiers,
    Modifiers *, KeySym * ) ;
+FUNC void XtTranslateKeycode ( Display *, KeyCode, Modifiers,
    Modifiers *, KeySym * ) ;

+TYPEDEF void ( *XtCaseProc ) ( Display *, KeySym, KeySym *, KeySym * ) ;

+FUNC void XtRegisterCaseConverter ( Display *, XtCaseProc,
    KeySym, KeySym ) ;
+FUNC void XtConvertCase ( Display *, KeySym, KeySym *, KeySym * ) ;


# Obtaining a KeySym in an Action Procedure (10.6)

+FUNC KeySym XtGetActionKeysym ( XEvent *, Modifiers * ) ;


# KeySym to KeyCode Conversions (10.7)

+FUNC void XtKeysymToKeycodeList ( Display *, KeySym,
    KeyCode **, Cardinal * ) ;


# Registering Button and Key Grabs for Actions (10.8)

+FUNC void XtRegisterGrabAction ( XtActionProc, Boolean, unsigned int,
    int, int ) ;


# Invoking Actions Directly (10.9)

+FUNC void XtCallActionProc ( Widget, String, XEvent *,
    String *, Cardinal ) ;


# Obtaining a Widget's Action List (10.10)

+FUNC void XtGetActionList ( WidgetClass, XtActionList *, Cardinal * ) ;


# Determining the Number of Elements in an Array (11.1)

+DEFINE XtNumber( a )	%% ((Cardinal) (sizeof (a) / sizeof (a[0]))) %% ;


# Translating Strings to Widget Instances (11.2)

+FUNC Widget XtNameToWidget ( Widget, String ) ;


# Managing Memory Usage (11.3)

+FUNC char *XtMalloc ( Cardinal ) ;
+FUNC char *XtCalloc ( Cardinal, Cardinal ) ;
+FUNC char *XtRealloc ( char *, Cardinal ) ;
+FUNC void XtFree ( char * ) ;
# RCA : I couldn't resist abstracting these properly
+TOKEN XtNew %% PROC ( TYPE t ) EXP rvalue : t * : %% ;
+MACRO String XtNewString ( String ) ;


# Sharing Graphics Contexts (11.4)

+TYPE ( int ) XtGCMask ;	# RCA : not specified
+FUNC GC XtAllocateGC ( Widget, Cardinal, XtGCMask,
    XGCValues *, XtGCMask, XtGCMask ) ;
+FUNC GC XtGetGC ( Widget, XtGCMask, XGCValues * ) ;
+FUNC void XtReleaseGC ( Widget, GC ) ;


# Managing Selections (11.5)

+FUNC void XtAppSetSelectionTimeout ( XtAppContext, unsigned long ) ;
+FUNC unsigned long XtAppGetSelectionTimeout ( XtAppContext ) ;

+TYPEDEF Boolean ( *XtConvertSelectionProc ) ( Widget, Atom *, Atom *,
    Atom *, XtPointer *, unsigned long *, int * ) ;

+TYPEDEF XtPointer XtRequestId ;

+FUNC XSelectionRequestEvent *XtGetSelectionRequest ( Widget,
    Atom, XtRequestId ) ;

+TYPEDEF void ( *XtLoseSelectionProc ) ( Widget, Atom * ) ;
+TYPEDEF void ( *XtSelectionDoneProc ) ( Widget, Atom *, Atom * ) ;

+TYPEDEF void ( *XtSelectionCallbackProc ) ( Widget, XtPointer, Atom *,
    Atom *, XtPointer, unsigned long *, int * ) ;

+CONST Atom XT_CONVERT_FAIL ;

+FUNC void XtGetSelectionValue ( Widget, Atom, Atom,
    XtSelectionCallbackProc, XtPointer, Time ) ;
+FUNC void XtGetSelectionValues ( Widget, Atom, Atom *,
    int, XtSelectionCallbackProc, XtPointer *, Time ) ;

+FUNC Boolean XtOwnSelection ( Widget, Atom, Time,
    XtConvertSelectionProc, XtLoseSelectionProc, XtSelectionDoneProc ) ;
+FUNC void XtDisownSelection ( Widget, Atom, Time ) ;

+TYPEDEF Boolean ( *XtConvertSelectionIncrProc ) ( Widget, Atom *, Atom *,
    Atom *, XtPointer *, unsigned long *, int *, unsigned long *,
    XtPointer, XtRequestId * ) ;
+TYPEDEF void ( *XtLoseSelectionIncrProc ) ( Widget, Atom *, XtPointer ) ;
+TYPEDEF void ( *XtSelectionDoneIncrProc ) ( Widget, Atom *, Atom *,
    XtRequestId *, XtPointer ) ;
+TYPEDEF void ( *XtCancelConvertSelectionProc ) ( Widget, Atom *, Atom *,
    XtRequestId *, XtPointer ) ;

+FUNC void XtGetSelectionValueIncremental ( Widget, Atom,
    Atom, XtSelectionCallbackProc, XtPointer, Time ) ;
+FUNC void XtGetSelectionValuesIncremental ( Widget, Atom,
    Atom *, int, XtSelectionCallbackProc, XtPointer *, Time ) ;

+FUNC Boolean XtOwnSelectionIncremental ( Widget, Atom, Time,
    XtConvertSelectionIncrProc, XtLoseSelectionIncrProc,
    XtSelectionDoneIncrProc, XtCancelConvertSelectionProc,
    XtPointer ) ;

+FUNC Time XtLastTimestampProcessed ( Display * ) ;


# Merging Exposure Events into a Region (11.6)

+FUNC void XtAddExposureToRegion ( XEvent *, Region ) ;


# Translating Widget Coordinates (11.7)

+FUNC void XtTranslateCoords ( Widget, Position, Position,
   Position *, Position * ) ;


# Translating a Window to a Widget (11.8)

+FUNC Widget XtWindowToWidget ( Display *, Window ) ;


# Handling Errors (11.9)

+TYPEDEF void ( *XtErrorMsgHandler ) ( String, String, String, String,
    String *, Cardinal * ) ;

+FUNC XrmDatabase *XtAppGetErrorDatabase ( XtAppContext ) ;
+FUNC void XtAppGetErrorDatabaseText ( XtAppContext, String, String,
    String, String, String, int, XrmDatabase ) ;
+FUNC void XtGetApplicationNameAndClass ( Display *, String *, String * ) ;
+FUNC XtErrorMsgHandler XtAppSetErrorMsgHandler ( XtAppContext,
    XtErrorMsgHandler ) ;
+FUNC void XtAppErrorMsg ( XtAppContext, String, String, String, String,
    String *, Cardinal * ) ;
+FUNC XtErrorMsgHandler XtAppSetWarningMsgHandler ( XtAppContext,
    XtErrorMsgHandler ) ;
+FUNC void XtAppWarningMsg ( XtAppContext, String, String, String, String,
    String *, Cardinal * ) ;

+TYPEDEF void ( *XtErrorHandler ) ( String ) ;

+FUNC XtErrorHandler XtAppSetErrorHandler ( XtAppContext, XtErrorHandler ) ;
+FUNC void XtAppError ( XtAppContext, String ) ;
+FUNC XtErrorHandler XtAppSetWarningHandler ( XtAppContext, XtErrorHandler ) ;
+FUNC void XtAppWarning ( XtAppContext, String ) ;


# Setting WM_COLORMAP_WINDOWS (11.10)

+FUNC void XtSetWMColormapWindows ( Widget, Widget *, Cardinal ) ;


# Finding File Names (11.11)

+FIELD ( struct ) SubstitutionRec := {
    char match ;
    String substitution ;
} ;
+TYPEDEF SubstitutionRec *Substitution ;
+TYPEDEF Boolean ( *XtFilePredicate ) ( String ) ;

+FUNC String XtFindFile ( String, Substitution, Cardinal, XtFilePredicate ) ;
+FUNC String XtResolvePathname ( Display *, String, String, String, String,
    Substitution, Cardinal, XtFilePredicate ) ;


# Determining Specification Revision Level (13.1)

+DEFINE XtSpecificationRelease 5 ;


# Compatibility Functions (Appendix C)

+FUNC Widget XtInitialize ( String, String, XrmOptionDescRec [], Cardinal,
    int *, String [] ) ;
+FUNC void XtMainLoop ( void ) ;
+FUNC void XtNextEvent ( XEvent * ) ;
+FUNC void XtProcessEvent ( XtInputMask ) ;
+FUNC Boolean XtPeekEvent ( XEvent * ) ;
+FUNC XtInputMask XtPending ( void ) ;
+FUNC XtInputId XtAddInput ( int, XtPointer, XtInputCallbackProc,
    XtPointer ) ;
+FUNC XtIntervalId XtAddTimeOut ( unsigned long, XtTimerCallbackProc,
    XtPointer ) ;
+FUNC XtWorkProcId XtAddWorkProc ( XtWorkProc, XtPointer ) ;
+FUNC Widget XtCreateApplicationShell ( String, WidgetClass,
    ArgList, Cardinal ) ;

+TYPEDEF void ( *XtConverter ) ( XrmValue *, Cardinal *, XrmValue *,
    XrmValue * ) ;

+FUNC void XtStringConversionWarning ( String, String ) ;
+FUNC void XtAddConverter ( String, String, XtConverter, XtConvertArgList,
    Cardinal ) ;
+FUNC void XtAppAddConverter ( XtAppContext, String, String, XtConverter,
    XtConvertArgList, Cardinal ) ;
+FUNC void XtConvert ( Widget, String, XrmValuePtr,
    String, XrmValuePtr ) ;
+FUNC void XtDirectConvert ( XtConverter, XrmValuePtr, Cardinal,
    XrmValuePtr, XrmValuePtr ) ;
+FUNC void XtDestroyGC ( Widget, GC ) ;
+FUNC void XtAddActions ( XtActionList, Cardinal ) ;
+FUNC void XtSetSelectionTimeout ( unsigned long ) ;
+FUNC unsigned long XtGetSelectionTimeout ( void ) ;

+FUNC XrmDatabase *XtGetErrorDatabase ( void ) ;
+FUNC void XtGetErrorDatabaseText ( String, String, String, String,
    String, int ) ;
+FUNC void XtSetErrorMsgHandler ( XtErrorMsgHandler ) ;
+FUNC void XtErrorMsg ( String, String, String, String,
    String *, Cardinal * ) ;
+FUNC void XtSetWarningMsgHandler ( XtErrorMsgHandler ) ;
+FUNC void XtWarningMsg ( String, String, String, String,
    String *, Cardinal * ) ;
+FUNC void XtSetErrorHandler ( XtErrorHandler ) ;
+FUNC void XtError ( String ) ;
+FUNC void XtSetWarningHandler ( XtErrorHandler ) ;
+FUNC void XtWarning ( String ) ;
