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
# Types and constants for X protocol to be used by applications

+USE "ansi", "stddef.h", "wchar_t" (!?) ;


# Types

+TYPE ( int ) XID ;		# see 1.1
+TYPEDEF XID Window ;		# see 1.1
+TYPEDEF XID Font ;		# see 1.1
+TYPEDEF XID Pixmap ;		# see 1.1
+TYPEDEF XID Colormap ;		# see 1.1
+TYPEDEF XID Cursor ;		# see 1.1
+TYPEDEF XID GContext ;		# see 1.1
+TYPEDEF XID Drawable ;		# can be a Window or a Pixmap (see 4.2)

+TYPE ( int ) Atom ;		# see 4.3
+TYPE ( int ) Bool ;		# see 1.4
+TYPE ( int ) KeyCode ;		# see 12.7
+TYPE ( int ) KeySym ;		# see 12.7
+TYPE ( int ) Status ;		# see 1.2
+TYPE ( int ) Time ;		# see 4.5 and 12.1
+TYPE ( int ) VisualID ;	# see 3.1


# Miscellaneous constants

+DEFINE None 0 ;		# universal null (see 1.4)
+CONST Bool True, False ;	# see 1.4
+CONST XID AllTemporary ;	# see 9.6
+CONST XID InputFocus ;		# see 11.6
+DEFINE CopyFromParent 0 ;	# see 3.2.2 etc, can be int or ptr
+CONST XID ParentRelative ;	# see 3.2.1 etc
+CONST XID PointerRoot ;	# see 12.5
+CONST XID PointerWindow ;	# see 11.6
+CONST int AnyKey ;		# see 12.2
+CONST unsigned AnyButton ;	# see 12.1
+CONST unsigned AnyModifier ;	# see 12.2
+CONST Atom AnyPropertyType ;	# see 4.4
+CONST KeySym NoSymbol ;	# see 12.7
+CONST Status Success ;		# see 4.4 etc
+CONST Time CurrentTime ;	# see 4.5


# Event Types (10.1)

+CONST int KeyPress, KeyRelease ;
+CONST int ButtonPress, ButtonRelease, MotionNotify ;
+CONST int EnterNotify, LeaveNotify ;
+CONST int FocusIn, FocusOut ;
+CONST int KeymapNotify ;
+CONST int Expose, GraphicsExpose, NoExpose ;
+CONST int CirculateRequest, ConfigureRequest, MapRequest, ResizeRequest ;
+CONST int CirculateNotify, ConfigureNotify, CreateNotify, DestroyNotify ;
+CONST int GravityNotify, MapNotify, MappingNotify, ReparentNotify ;
+CONST int UnmapNotify, VisibilityNotify ;
+CONST int ColormapNotify, ClientMessage, PropertyNotify ;
+CONST int SelectionClear, SelectionNotify, SelectionRequest ;


# Event Masks (see 3.2.7, 10.3)

+CONST long NoEventMask, KeyPressMask, KeyReleaseMask ;
+CONST long ButtonPressMask, ButtonReleaseMask ;
+CONST long EnterWindowMask, LeaveWindowMask ;
+CONST long PointerMotionMask, PointerMotionHintMask ;
+CONST long Button1MotionMask, Button2MotionMask, Button3MotionMask ; 
+CONST long Button4MotionMask, Button5MotionMask, ButtonMotionMask ; 
+CONST long KeymapStateMask, ExposureMask, VisibilityChangeMask ; 
+CONST long StructureNotifyMask, ResizeRedirectMask ;
+CONST long SubstructureNotifyMask, SubstructureRedirectMask ;
+CONST long FocusChangeMask, PropertyChangeMask, ColormapChangeMask ;
+CONST long OwnerGrabButtonMask ;


# Error Codes (see 11.8.2)

+CONST int BadAccess, BadAlloc, BadAtom, BadColor, BadCursor ;
+CONST int BadDrawable, BadFont, BadGC, BadIDChoice, BadImplementation ;
+CONST int BadLength, BadMatch, BadName, BadPixmap, BadRequest ;
+CONST int BadValue, BadWindow ;


# Creating Windows (3.3)
+CONST int InputOutput, InputOnly ;

# Window attributes (3.2)
+DEFINE CWBackPixmap	 	%% (1L<<0) %% ;
+DEFINE CWBackPixel		%% (1L<<1) %% ;
+DEFINE CWBorderPixmap		%% (1L<<2) %% ;
+DEFINE CWBorderPixel		%% (1L<<3) %% ;
+DEFINE CWBitGravity		%% (1L<<4) %% ;
+DEFINE CWWinGravity		%% (1L<<5) %% ;
+DEFINE CWBackingStore		%% (1L<<6) %% ;
+DEFINE CWBackingPlanes		%% (1L<<7) %% ;
+DEFINE CWBackingPixel		%% (1L<<8) %% ;
+DEFINE CWOverrideRedirect	%% (1L<<9) %% ;
+DEFINE CWSaveUnder		%% (1L<<10) %% ;
+DEFINE CWEventMask		%% (1L<<11) %% ;
+DEFINE CWDontPropagate		%% (1L<<12) %% ;
+DEFINE CWColormap		%% (1L<<13) %% ;
+DEFINE CWCursor		%% (1L<<14) %% ;


# Configuring Windows (3.7)
+DEFINE CWX			%% (1<<0) %% ;
+DEFINE CWY			%% (1<<1) %% ;
+DEFINE CWWidth			%% (1<<2) %% ;
+DEFINE CWHeight		%% (1<<3) %% ;
+DEFINE CWBorderWidth		%% (1<<4) %% ;
+DEFINE CWSibling		%% (1<<5) %% ;
+DEFINE CWStackMode		%% (1<<6) %% ;


# Gravity Attributes (3.2.3)
+CONST int NorthWestGravity, NorthGravity, NorthEastGravity ;
+CONST int WestGravity, CenterGravity, EastGravity ;
+CONST int SouthWestGravity, SouthGravity, SouthEastGravity ;
+CONST int ForgetGravity, StaticGravity, UnmapGravity ;


# Backing Store Attributes (3.2.4, see also 2.2.3)
+CONST int NotUseful, WhenMapped, Always ;


# Obtaining Window Information (4.1)
+CONST int IsUnmapped, IsUnviewable, IsViewable ;


# Closing the display (2.5)
+CONST int DestroyAll, RetainPermanent, RetainTemporary ;


# Configuring Windows (3.7)
+CONST int Above, Below, TopIf, BottomIf, Opposite ;


# Changing Window Stacking Order (3.8)
+CONST int RaiseLowest, LowerHighest ;


# Obtaining and Changing Window Properties (4.4)
+CONST int PropModeReplace, PropModePrepend, PropModeAppend ;


# Creating, Copying and Destroying Colormaps (6.4)
+CONST int AllocNone, AllocAll ;


# Colour Structures (6.1)
+CONST int DoRed, DoGreen, DoBlue ;


# Visual types (3.1)
+CONST int StaticGray, StaticColor, TrueColor, GrayScale ;
+CONST int PseudoColor, DirectColor ;


# Image format functions (2.2.2)
+CONST int LSBFirst, MSBFirst ;

# Manipulating GCs (7.1)
+DEFINE GCFunction	 	%% (1L<<0) %% ;
+DEFINE GCPlaneMask	 	%% (1L<<1) %% ;
+DEFINE GCForeground	 	%% (1L<<2) %% ;
+DEFINE GCBackground	 	%% (1L<<3) %% ;
+DEFINE GCLineWidth	 	%% (1L<<4) %% ;
+DEFINE GCLineStyle	 	%% (1L<<5) %% ;
+DEFINE GCCapStyle	 	%% (1L<<6) %% ;
+DEFINE GCJoinStyle	 	%% (1L<<7) %% ;
+DEFINE GCFillStyle	 	%% (1L<<8) %% ;
+DEFINE GCFillRule	 	%% (1L<<9) %% ;
+DEFINE GCTile		 	%% (1L<<10) %% ;
+DEFINE GCStipple	 	%% (1L<<11) %% ;
+DEFINE GCTileStipXOrigin 	%% (1L<<12) %% ;
+DEFINE GCTileStipYOrigin 	%% (1L<<13) %% ;
+DEFINE GCFont		 	%% (1L<<14) %% ;
+DEFINE GCSubwindowMode	 	%% (1L<<15) %% ;
+DEFINE GCGraphicsExposures 	%% (1L<<16) %% ;
+DEFINE GCClipXOrigin	 	%% (1L<<17) %% ;
+DEFINE GCClipYOrigin	 	%% (1L<<18) %% ;
+DEFINE GCClipMask	 	%% (1L<<19) %% ;
+DEFINE GCDashOffset	 	%% (1L<<20) %% ;
+DEFINE GCDashList	 	%% (1L<<21) %% ;
+DEFINE GCArcMode	 	%% (1L<<22) %% ;

+DEFINE GXclear		 	%% 0x0 %% ;
+DEFINE GXand		 	%% 0x1 %% ;
+DEFINE GXandReverse	 	%% 0x2 %% ;
+DEFINE GXcopy		 	%% 0x3 %% ;
+DEFINE GXandInverted	 	%% 0x4 %% ;
+DEFINE GXnoop		 	%% 0x5 %% ;
+DEFINE GXxor		 	%% 0x6 %% ;
+DEFINE GXor		 	%% 0x7 %% ;
+DEFINE GXnor		 	%% 0x8 %% ;
+DEFINE GXequiv		 	%% 0x9 %% ;
+DEFINE GXinvert		%% 0xa %% ;
+DEFINE GXorReverse	 	%% 0xb %% ;
+DEFINE GXcopyInverted	 	%% 0xc %% ;
+DEFINE GXorInverted	 	%% 0xd %% ;
+DEFINE GXnand		 	%% 0xe %% ;
+DEFINE GXset		 	%% 0xf %% ;

+CONST int LineSolid, LineDoubleDash, LineOnOffDash ;
+CONST int CapNotLast, CapButt, CapRound, CapProjecting ;
+CONST int JoinMiter, JoinRound, JoinBevel ;
+CONST int FillSolid, FillTiled, FillOpaqueStippled, FillStippled ;
+CONST int ClipByChildren, IncludeInferiors ;
+CONST int EvenOddRule, WindingRule ;
+CONST int TileShape, CursorShape, StippleShape ;
+CONST int Unsorted, YSorted, YXSorted, YXBanded ;
+CONST int ArcChord, ArcPieSlice ;


# Drawing Single and Multiple Lines (8.3.1)
+CONST int CoordModeOrigin, CoordModePrevious ;


# Filling a Single Polygon (8.4.2)
+CONST int Complex, Convex, Nonconvex ;


# Font Metrics (8.5)
+CONST unsigned FontLeftToRight, FontRightToLeft ;


# Tranferring Images between Client and Server (8.7)
+CONST int XYBitmap, XYPixmap, ZPixmap ;


# Controlling the Lifetime of a Window (9.2)
+CONST int SetModeInsert, SetModeDelete ;


# Screen Saver Control (9.7)
+CONST int DontPreferBlanking, PreferBlanking, DefaultBlanking ;
+CONST int DontAllowExposures, AllowExposures, DefaultExposures ;
+CONST int ScreenSaverActive, ScreenSaverReset ;


# Adding, Getting and Removing Hosts (9.8.1)
+CONST int FamilyInternet, FamilyDECnet, FamilyChaos ;


# Changing, Enabling and Disabling Access Control (9.8.2)
+CONST int EnableAccess, DisableAccess ;


# Event details (10.5 etc)
+CONST int NotifyAncestor, NotifyDetailNone, NotifyGrab, NotifyHint ;
+CONST int NotifyInferior, NotifyNonlinear, NotifyNonlinearVirtual ;
+CONST int NotifyNormal, NotifyPointer, NotifyPointerRoot ;
+CONST int NotifyUngrab, NotifyVirtual, NotifyWhileGrabbed ;

+CONST int Button1Mask, Button2Mask, Button3Mask, Button4Mask, Button5Mask ;
+CONST int ShiftMask, LockMask, ControlMask, Mod1Mask, Mod2Mask, Mod3Mask ;
+CONST int Mod4Mask, Mod5Mask ;

+CONST int Button1, Button2, Button3, Button4, Button5 ;


# Window State Change Events (10.10)
+CONST int PlaceOnTop, PlaceOnBottom ;
+CONST int MappingModifier, MappingKeyboard, MappingPointer ;
+CONST int VisibilityUnobscured, VisibilityPartiallyObscured ;
+CONST int VisibilityFullyObscured ;


# Colormap State Change Events (10.12)
+CONST int ColormapInstalled, ColormapUninstalled ;


# Client Communication Events (10.13)
+CONST int PropertyNewValue, PropertyDelete ;


# Event Queue Management (11.3)
+CONST int QueuedAlready, QueuedAfterFlush, QueuedAfterReading ;


# Pointer Grabbing (12.1)
+CONST int GrabSuccess ;
+CONST int GrabModeSync, GrabModeAsync ;


# Keyboard Grabbing (12.2)
+CONST int AlreadyGrabbed, GrabNotViewable, GrabFrozen, GrabInvalidTime ;


# Resuming Event Processing (12.3)
+CONST int AsyncPointer, SyncPointer, AsyncKeyboard, SyncKeyboard ;
+CONST int ReplayPointer, ReplayKeyboard, AsyncBoth, SyncBoth ;


# Controlling Input Focus (12.5)
+CONST int RevertToParent, RevertToPointerRoot, RevertToNone ;


# Keyboard and Pointer Settings (12.6)
+DEFINE KBKeyClickPercent 	%% (1L<<0) %% ;
+DEFINE KBBellPercent	 	%% (1L<<1) %% ;
+DEFINE KBBellPitch	 	%% (1L<<2) %% ;
+DEFINE KBBellDuration	 	%% (1L<<3) %% ;
+DEFINE KBLed		 	%% (1L<<4) %% ;
+DEFINE KBLedMode	 	%% (1L<<5) %% ;
+DEFINE KBKey		 	%% (1L<<6) %% ;
+DEFINE KBAutoRepeatMode 	%% (1L<<7) %% ;
+CONST int LedModeOn, LedModeOff ;
+CONST int AutoRepeatModeOn, AutoRepeatModeOff, AutoRepeatModeDefault ;
+CONST int MappingSuccess, MappingBusy, MappingFailed ;


# Locating points (16.5.5)
+CONST int RectangleIn, RectangleOut, RectanglePart ;


# Manipulating Bitmaps (16.9)
+CONST int BitmapSuccess ;
+CONST int BitmapOpenFailed, BitmapFileInvalid, BitmapNoMemory ;
