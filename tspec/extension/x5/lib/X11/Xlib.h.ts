# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Main Xlib header

+USE "x5/lib", "X11/X.h.ts" ;	# see 1.3
+USE "x5/lib", "X11/Xproto.h.ts" (!?) ;
+USE "x5/lib", "X11/Xresource.h.ts" (!?) ;
+USE "x5/lib", "X11/Xutil.h.ts" (!?) ;


# Specification version (1.3)

+DEFINE XlibSpecificationRelease 5 ;


# Miscellaneous types

+SUBSET "types" := {
    +USE "x5/lib", "X11/X.h.ts" ;

    # Miscellaneous types
    +TYPE ( struct ) Display ;	# see 2.1
    +TYPE ( struct ) Visual ;	# see 3.1
    +TYPE ( struct ) Screen ;	# see 2.1
    +TYPEDEF char *XPointer ;	# see 1.4 (generic?)

    # Transfering Images between Client and Server (8.7)
    +TYPE ( struct ) XImage ;

    +FIELD struct funcs := {
	XImage *( *create_image ) () ;
	int ( *destroy_image ) () ;
	unsigned long ( *get_pixel ) () ;
	int ( *put_pixel ) () ;
	XImage *( *sub_image ) () ;
	int ( *add_pixel ) () ;
    } ;

    +FIELD XImage := {
	int width, height ;
	int xoffset ;
	int format ;
	char *data ;
	int byte_order ;
	int bitmap_unit ;
	int bitmap_bit_order ;
	int bitmap_pad ;
	int depth ;
	int bytes_per_line ;
	int bits_per_pixel ;
	unsigned long red_mask, green_mask, blue_mask ;
	XPointer obdata ;
	struct funcs f ;
    } ;
} ;

+TYPE ~GCRec ;
+TYPEDEF ~GCRec *GC ;		# RCA : not specified
+TYPE ( struct ) XExtData ;	# see below

+FIELD ( struct ) XColor := {	# see 6.1
    unsigned long pixel ;
    unsigned short red, green, blue ;
    char flags ;
    char pad ;
} ;


# Opening the Display (2.1)

+FUNC Display *XOpenDisplay ( char * ) ;


# Display macros (2.2.1)

+FUNC unsigned long XAllPlanes ( void ) ;
+FUNC unsigned long XBlackPixel ( Display *, int ) ;
+FUNC unsigned long XWhitePixel ( Display *, int ) ;
+FUNC int XConnectionNumber ( Display * ) ;
+FUNC Colormap XDefaultColormap ( Display *, int ) ;
+FUNC int XDefaultDepth ( Display *, int ) ;
+FUNC int *XListDepths ( Display *, int, int * ) ;
+FUNC GC XDefaultGC ( Display *, int ) ;
+FUNC Window XDefaultRootWindow ( Display * ) ;
+FUNC Screen *XDefaultScreenOfDisplay ( Display * ) ;
+FUNC Screen *XScreenOfDisplay ( Display *, int ) ;
+FUNC int XDefaultScreen ( Display * ) ;
+FUNC Visual *XDefaultVisual ( Display *, int ) ;
+FUNC int XDisplayCells ( Display *, int ) ;
+FUNC int XDisplayPlanes ( Display *, int ) ;
+FUNC char *XDisplayString ( Display * ) ;
+FUNC long XMaxRequestSize ( Display * ) ;
+FUNC unsigned long XLastKnownRequestProcessed ( Display * ) ;
+FUNC unsigned long XNextRequest ( Display * ) ;
+FUNC int XProtocolVersion ( Display * ) ;
+FUNC int XProtocolRevision ( Display * ) ;
+FUNC int XQLength ( Display * ) ;
+FUNC Window XRootWindow ( Display *, int ) ;
+FUNC int XScreenCount ( Display * ) ;
+FUNC char *XServerVendor ( Display * ) ;
+FUNC int XVendorRelease ( Display * ) ;

+CONST unsigned long AllPlanes ;
+MACRO unsigned long BlackPixel ( Display *, int ) ;
+MACRO unsigned long WhitePixel ( Display *, int ) ;
+MACRO int ConnectionNumber ( Display * ) ;
+MACRO Colormap DefaultColormap ( Display *, int ) ;
+MACRO int DefaultDepth ( Display *, int ) ;
+MACRO GC DefaultGC ( Display *, int ) ;
+MACRO Window DefaultRootWindow ( Display * ) ;
+MACRO Screen *DefaultScreenOfDisplay ( Display * ) ;
+MACRO Screen *ScreenOfDisplay ( Display *, int ) ;
+MACRO int DefaultScreen ( Display * ) ;
+MACRO Visual *DefaultVisual ( Display *, int ) ;
+MACRO int DisplayCells ( Display *, int ) ;
+MACRO int DisplayPlanes ( Display *, int ) ;
+MACRO char *DisplayString ( Display * ) ;
+MACRO unsigned long LastKnownRequestProcessed ( Display * ) ;
+MACRO unsigned long NextRequest ( Display * ) ;
+MACRO int ProtocolVersion ( Display * ) ;
+MACRO int ProtocolRevision ( Display * ) ;
+MACRO int QLength ( Display * ) ;
+MACRO Window RootWindow ( Display *, int ) ;
+MACRO int ScreenCount ( Display * ) ;
+MACRO char *ServerVendor ( Display * ) ;
+MACRO int VendorRelease ( Display * ) ;


# Image format functions (2.2.2)

+FIELD ( struct ) XPixmapFormatValues := {
    int depth ;
    int bits_per_pixel ;
    int scanline_pad ;
} ;

+FUNC XPixmapFormatValues *XListPixmapFormats ( Display *, int * ) ;

+FUNC int XImageByteOrder ( Display * ) ;
+FUNC int XBitmapUnit ( Display * ) ;
+FUNC int XBitmapBitOrder ( Display * ) ;
+FUNC int XBitmapPad ( Display * ) ;
+FUNC int XDisplayHeight ( Display *, int ) ;
+FUNC int XDisplayHeightMM ( Display *, int ) ;
+FUNC int XDisplayWidth ( Display *, int ) ;
+FUNC int XDisplayWidthMM ( Display *, int ) ;

+MACRO int ImageByteOrder ( Display * ) ;
+MACRO int BitmapUnit ( Display * ) ;
+MACRO int BitmapBitOrder ( Display * ) ;
+MACRO int BitmapPad ( Display * ) ;
+MACRO int DisplayHeight ( Display *, int ) ;
+MACRO int DisplayHeightMM ( Display *, int ) ;
+MACRO int DisplayWidth ( Display *, int ) ;
+MACRO int DisplayWidthMM ( Display *, int ) ;


# Screen Information Macros (2.2.3)

+FUNC unsigned long XBlackPixelOfScreen ( Screen * ) ;
+FUNC unsigned long XWhitePixelOfScreen ( Screen * ) ;
+FUNC int XCellsOfScreen ( Screen * ) ;
+FUNC Colormap XDefaultColormapOfScreen ( Screen * ) ;
+FUNC int XDefaultDepthOfScreen ( Screen * ) ;
+FUNC GC XDefaultGCOfScreen ( Screen * ) ;
+FUNC Visual *XDefaultVisualOfScreen ( Screen * ) ;
+FUNC int XDoesBackingStore ( Screen * ) ;
+FUNC Bool XDoesSaveUnders ( Screen * ) ;
+FUNC Display *XDisplayOfScreen ( Screen * ) ;
+FUNC int XScreenNumberOfScreen ( Screen * ) ;
+FUNC long XEventMaskOfScreen ( Screen * ) ;
+FUNC int XWidthOfScreen ( Screen * ) ;
+FUNC int XHeightOfScreen ( Screen * ) ;
+FUNC int XWidthMMOfScreen ( Screen * ) ;
+FUNC int XHeightMMOfScreen ( Screen * ) ;
+FUNC int XMaxCmapsOfScreen ( Screen * ) ;
+FUNC int XMinCmapsOfScreen ( Screen * ) ;
+FUNC int XPlanesOfScreen ( Screen * ) ;
+FUNC Window XRootWindowOfScreen ( Screen * ) ;

+MACRO unsigned long BlackPixelOfScreen ( Screen * ) ;
+MACRO unsigned long WhitePixelOfScreen ( Screen * ) ;
+MACRO int CellsOfScreen ( Screen * ) ;
+MACRO Colormap DefaultColormapOfScreen ( Screen * ) ;
+MACRO int DefaultDepthOfScreen ( Screen * ) ;
+MACRO GC DefaultGCOfScreen ( Screen * ) ;
+MACRO Visual *DefaultVisualOfScreen ( Screen * ) ;
+MACRO int DoesBackingStore ( Screen * ) ;
+MACRO Bool DoesSaveUnders ( Screen * ) ;
+MACRO Display *DisplayOfScreen ( Screen * ) ;
+MACRO long EventMaskOfScreen ( Screen * ) ;
+MACRO int WidthOfScreen ( Screen * ) ;
+MACRO int HeightOfScreen ( Screen * ) ;
+MACRO int WidthMMOfScreen ( Screen * ) ;
+MACRO int HeightMMOfScreen ( Screen * ) ;
+MACRO int MaxCmapsOfScreen ( Screen * ) ;
+MACRO int MinCmapsOfScreen ( Screen * ) ;
+MACRO int PlanesOfScreen ( Screen * ) ;
+MACRO Window RootWindowOfScreen ( Screen * ) ;


# NoOperation Protocol Request (2.3)

+FUNC void XNoOp ( Display * ) ;


# Freeing data (2.4)

+FUNC void XFree ( void * ) ;


# Closing the display (2.5)

+FUNC void XCloseDisplay ( Display * ) ;
+FUNC void XSetCloseDownMode ( Display *, int ) ;


# Visual types (3.1)

+FUNC VisualID XVisualIDFromVisual ( Visual * ) ;


# Window attributes (3.2)

+FIELD ( struct ) XSetWindowAttributes := {
    Pixmap background_pixmap ;
    unsigned long background_pixel ;
    Pixmap border_pixmap ;
    unsigned long border_pixel ;
    int bit_gravity ;
    int win_gravity ;
    int backing_store ;
    unsigned long backing_planes ;
    unsigned long backing_pixel ;
    Bool save_under ;
    long event_mask ;
    long do_not_propagate_mask ;
    Bool override_redirect ;
    Colormap colormap ;
    Cursor cursor ;
} ;


# Creating Windows (3.3)

+FUNC Window XCreateWindow ( Display *, Window, int, int, unsigned int,
    unsigned int, unsigned int, int, unsigned int, Visual *, unsigned long,
    XSetWindowAttributes * ) ;

+FUNC Window XCreateSimpleWindow ( Display *, Window, int, int, unsigned int,
    unsigned int, unsigned int, unsigned long, unsigned long ) ;


# Destroying Windows (3.4)

+FUNC void XDestroyWindow ( Display *, Window ) ;
+FUNC void XDestroySubwindows ( Display *, Window ) ;


# Mapping Windows (3.5)

+FUNC void XMapWindow ( Display *, Window ) ;
+FUNC void XMapRaised ( Display *, Window ) ;
+FUNC void XMapSubwindows ( Display *, Window ) ;


# Unmapping Windows (3.6)

+FUNC void XUnmapWindow ( Display *, Window ) ;
+FUNC void XUnmapSubwindows ( Display *, Window ) ;


# Configuring Windows (3.7)

+FIELD ( struct ) XWindowChanges := {
    int x, y ;
    int width, height ;
    int border_width ;
    Window sibling ;
    int stack_mode ;
} ;

+FUNC void XConfigureWindow ( Display *, Window, unsigned int,
    XWindowChanges * ) ;
+FUNC void XMoveWindow ( Display *, Window, int, int ) ;
+FUNC void XResizeWindow ( Display *, Window, unsigned int, unsigned int ) ;
+FUNC void XMoveResizeWindow ( Display *, Window, int, int, unsigned int,
    unsigned int ) ;
+FUNC void XSetWindowBorderWidth ( Display *, Window, unsigned int ) ;


# Changing Window Stacking Order (3.8)

+FUNC void XRaiseWindow ( Display *, Window ) ;
+FUNC void XLowerWindow ( Display *, Window ) ;
+FUNC void XCirculateSubwindows ( Display *, Window, int ) ;
+FUNC void XCirculateSubwindowsUp ( Display *, Window ) ;
+FUNC void XCirculateSubwindowsDown ( Display *, Window ) ;
+FUNC void XRestackWindows ( Display *, Window [], int ) ;


# Changing Window Attributes (3.9)

+FUNC void XChangeWindowAttributes ( Display *, Window, unsigned long,
    XSetWindowAttributes * ) ;
+FUNC void XSetWindowBackground ( Display *, Window, unsigned long ) ;
+FUNC void XSetWindowBackgroundPixmap ( Display *, Window, Pixmap ) ;
+FUNC void XSetWindowBorder ( Display *, Window, unsigned long ) ;
+FUNC void XSetWindowBorderPixmap ( Display *, Window, Pixmap ) ;
+FUNC void XSetWindowColormap ( Display *, Window, Colormap ) ;
+FUNC void XDefineCursor ( Display *, Window, Cursor ) ;
+FUNC void XUndefineCursor ( Display *, Window ) ;


# Obtaining Window Information (4.1)

+FIELD ( struct ) XWindowAttributes := {
    int x, y ;
    int width, height ;
    int border_width ;
    int depth ;
    Visual *visual ;
    Window root ;
    int class ;
    int bit_gravity ;
    int win_gravity ;
    int backing_store ;
    unsigned long backing_planes ;
    unsigned long backing_pixels ;
    Bool save_under ;
    Colormap colormap ;
    Bool map_installed ;
    int map_state ;
    long all_event_masks ;
    long your_event_mask ;
    long do_not_propagate_mask ;
    Bool override_redirect ;
    Screen *screen ;
} ;

+FUNC Status XQueryTree ( Display *, Window, Window *, Window *,
    Window **, unsigned int * ) ;
+FUNC Status XGetWindowAttributes ( Display *, Window, XWindowAttributes * ) ;
+FUNC Status XGetGeometry ( Display *, Drawable, Window *, int *, int *,
    unsigned int *, unsigned int *, unsigned int *, unsigned int * ) ;


# Translating Screen Coordinates (4.2)

+FUNC Bool XTranslateCoordinates ( Display *, Window, Window, int, int,
    int *, int *, Window * ) ;
+FUNC Bool XQueryPointer ( Display *, Window, Window *, Window *, int *,
    int *, int *, int *, unsigned int * ) ;


# Properties and Atoms (4.3)

+FUNC Atom XInternAtom ( Display *, char *, Bool ) ;
+FUNC char *XGetAtomName ( Display *, Atom ) ;


# Obtaining and Changing Window Properties (4.4)

+FUNC int XGetWindowProperty ( Display *, Window, Atom, long, long, Bool,
    Atom, Atom *, int *, unsigned long *, unsigned long *, unsigned char ** ) ;
+FUNC Atom *XListProperties ( Display *, Window, int * ) ;
+FUNC void XChangeProperty ( Display *, Window, Atom, Atom, int, int,
    unsigned char *, int ) ;
+FUNC void XRotateWindowProperties ( Display *, Window, Atom [], int, int ) ;
+FUNC void XDeleteProperty ( Display *, Window, Atom ) ;


# Selections (4.5)

+FUNC void XSetSelectionOwner ( Display *, Atom, Window, Time ) ;
+FUNC Window XGetSelectionOwner ( Display *, Atom ) ;
+FUNC void XConvertSelection ( Display *, Atom, Atom, Atom, Window, Time ) ;


# Creating and Freeing Pixmaps (5.1)

+FUNC Pixmap XCreatePixmap ( Display *, Drawable, unsigned int, unsigned int,
    unsigned int ) ;
+FUNC void XFreePixmap ( Display *, Pixmap ) ;


# Creating and Freeing Cursors (5.2)

+FUNC Cursor XCreateFontCursor ( Display *, unsigned int ) ;
+FUNC Cursor XCreateGlyphCursor ( Display *, Font, Font, unsigned int,
    unsigned int, XColor *, XColor * ) ;
+FUNC Cursor XCreatePixmapCursor ( Display *, Pixmap, Pixmap, XColor *,
    XColor *, unsigned int, unsigned int ) ;
+FUNC Status XQueryBestCursor ( Display *, Drawable, unsigned int,
    unsigned int, unsigned int *, unsigned int * ) ;
+FUNC void XRecolorCursor ( Display *, Cursor, XColor *, XColor * ) ;
+FUNC void XFreeCursor ( Display *, Cursor ) ;


# Creating, Copying and Destroying Colormaps (6.4)

+FUNC Colormap XCreateColormap ( Display *, Window, Visual *, int ) ;
+FUNC Colormap XCopyColormapAndFree ( Display *, Colormap ) ;
+FUNC void XFreeColormap ( Display *, Colormap ) ;


# Mapping colour names to values (6.5)

+FUNC Status XLookupColor ( Display *, Colormap, char *, XColor *, XColor * ) ;
+FUNC Status XParseColor ( Display *, Colormap, char *, XColor * ) ;


# Allocating and Freeing Colour cells (6.6)

+FUNC Status XAllocColor ( Display *, Colormap, XColor * ) ;
+FUNC Status XAllocNamedColor ( Display *, Colormap, char *, XColor *,
    XColor * ) ;
+FUNC Status XAllocColorCells ( Display *, Colormap, Bool, unsigned long [],
    unsigned int, unsigned long [], unsigned int ) ;
+FUNC Status XAllocColorPlanes ( Display *, Colormap, Bool, unsigned long [],
    int, int, int, int, unsigned long *, unsigned long *, unsigned long * ) ;
+FUNC void XFreeColors ( Display *, Colormap, unsigned long [], int,
    unsigned long ) ;


# Modifying and Querying Colormap Cells (6.7)

+FUNC void XStoreColor ( Display *, Colormap, XColor * ) ;
+FUNC void XStoreColors ( Display *, Colormap, XColor [], int ) ;
+FUNC void XStoreNamedColor ( Display *, Colormap, char *, unsigned long,
    int ) ;
+FUNC void XQueryColor ( Display *, Colormap, XColor * ) ;
+FUNC void XQueryColors ( Display *, Colormap, XColor [], int ) ;


# Manipulating GCs (7.1)

+FIELD ( struct ) XGCValues := {
    int function ;
    unsigned long plane_mask ;
    unsigned long foreground ;
    unsigned long background ;
    int line_width ;
    int line_style ;
    int cap_style ;
    int join_style ;
    int fill_style ;
    int fill_rule ;
    int arc_mode ;
    Pixmap tile ;
    Pixmap stipple ;
    int ts_x_origin ;
    int ts_y_origin ;
    Font font ;
    int subwindow_mode ;
    Bool graphics_exposures ;
    int clip_x_origin ;
    int clip_y_origin ;
    Pixmap clip_mask ;
    int dash_offset ;
    char dashes ;
} ;

+FUNC GC XCreateGC ( Display *, Drawable, unsigned long, XGCValues * ) ;
+FUNC void XCopyGC ( Display *, GC, unsigned long, GC ) ;
+FUNC void XChangeGC ( Display *, GC, unsigned long, XGCValues * ) ;
+FUNC Status XGetGCValues ( Display *, GC, unsigned long, XGCValues * ) ;
+FUNC void XFreeGC ( Display *, GC ) ;
+FUNC GContext XGContextFromGC ( GC ) ;
+FUNC void XFlushGC ( Display *, GC ) ;


# Drawing Points, Lines, Rectangles and Arcs (8.3)

+FIELD ( struct ) XSegment := {
    short x1, y1, x2, y2 ;
} ;

+FIELD ( struct ) XPoint := {
    short x, y ;
} ;

+FIELD ( struct ) XRectangle := {
    short x, y ;
    unsigned short width, height ;
} ;

+FIELD ( struct ) XArc := {
    short x, y ;
    unsigned short width, height ;
    short angle1, angle2 ;
} ;


# Setting the Foreground etc of a GC (7.2.1 to 7.2.7)

+FUNC void XSetState ( Display *, GC, unsigned long, unsigned long,
    int, unsigned long ) ;
+FUNC void XSetForeground ( Display *, GC, unsigned long ) ;
+FUNC void XSetBackground ( Display *, GC, unsigned long ) ;
+FUNC void XSetFunction ( Display *, GC, int ) ;
+FUNC void XSetPlaneMask ( Display *, GC, unsigned long ) ;
+FUNC void XSetLineAttributes ( Display *, GC, unsigned int, int, int, int ) ;
+FUNC void XSetDashes ( Display *, GC, int, char [], int ) ;
+FUNC void XSetFillStyle ( Display *, GC, int ) ;
+FUNC void XSetFillRule ( Display *, GC, int ) ;
+FUNC Status XQueryBestSize ( Display *, int, Drawable, unsigned int,
    unsigned int, unsigned int *, unsigned int * ) ;
+FUNC Status XQueryBestTile ( Display *, Drawable, unsigned int,
    unsigned int, unsigned int *, unsigned int * ) ;
+FUNC Status XQueryBestStipple ( Display *, Drawable, unsigned int,
    unsigned int, unsigned int *, unsigned int * ) ;
+FUNC void XSetTile ( Display *, GC, Pixmap ) ;
+FUNC void XSetStipple ( Display *, GC, Pixmap ) ;
+FUNC void XSetTSOrigin ( Display *, GC, int, int ) ;
+FUNC void XSetFont ( Display *, GC, Font ) ;
+FUNC void XSetClipOrigin ( Display *, GC, int, int ) ;
+FUNC void XSetClipMask ( Display *, GC, Pixmap ) ;
+FUNC void XSetClipRectangles ( Display *, GC, int, int, XRectangle [],
    int, int ) ;
+FUNC void XSetArcMode ( Display *, GC, int ) ;
+FUNC void XSetSubwindowMode ( Display *, GC, int ) ;
+FUNC void XSetGraphicsExposures ( Display *, GC, Bool ) ;


# Clearing Areas (8.1)

+FUNC void XClearArea ( Display *, Window, int, int, unsigned int,
    unsigned int, Bool ) ;
+FUNC void XClearWindow ( Display *, Window ) ;


# Copying Areas (8.2)

+FUNC void XCopyArea ( Display *, Drawable, Drawable, GC, int, int,
    unsigned int, unsigned int, int, int ) ;
+FUNC void XCopyPlane ( Display *, Drawable, Drawable, GC, int, int,
    unsigned int, unsigned int, int, int, unsigned long ) ;


# Drawing Single and Multiple Points etc (8.3.1 to 8.3.4)

+FUNC void XDrawPoint ( Display *, Drawable, GC, int, int ) ;
+FUNC void XDrawPoints ( Display *, Drawable, GC, XPoint *, int, int ) ;
+FUNC void XDrawLine ( Display *, Drawable, GC, int, int, int, int ) ;
+FUNC void XDrawLines ( Display *, Drawable, GC, XPoint *, int, int ) ;
+FUNC void XDrawSegments ( Display *, Drawable, GC, XSegment *, int ) ;
+FUNC void XDrawRectangle ( Display *, Drawable, GC, int, int,
    unsigned int, unsigned int ) ;
+FUNC void XDrawRectangles ( Display *, Drawable, GC, XRectangle [], int ) ;
+FUNC void XDrawArc ( Display *, Drawable, GC, int, int, unsigned int,
    unsigned int, int, int ) ;
+FUNC void XDrawArcs ( Display *, Drawable, GC, XArc *, int ) ;


# Filling Areas (8.4)

+FUNC void XFillRectangle ( Display *, Drawable, GC, int, int,
    unsigned int, unsigned int ) ;
+FUNC void XFillRectangles ( Display *, Drawable, GC, XRectangle *, int ) ;
+FUNC void XFillPolygon ( Display *, Drawable, GC, XPoint *, int, int, int ) ;
+FUNC void XFillArc ( Display *, Drawable, GC, int, int, unsigned int,
    unsigned int, int, int ) ;
+FUNC void XFillArcs ( Display *, Drawable, GC, XArc *, int ) ;


# Font Metrics (8.5)

+FIELD ( struct ) XCharStruct := {
    short lbearing ;
    short rbearing ;
    short width ;
    short ascent ;
    short descent ;
    unsigned short attributes ;
} ;

+FIELD ( struct ) XFontProp := {
    Atom name ;
    unsigned long card32 ;
} ;

+FIELD ( struct ) XChar2b := {
    unsigned char byte1 ;
    unsigned char byte2 ;
} ;

+FIELD ( struct ) XFontStruct := {
    XExtData *ext_data ;
    Font fid ;
    unsigned direction ;
    unsigned min_char_or_byte2 ;
    unsigned max_char_or_byte2 ;
    unsigned min_byte1 ;
    unsigned max_byte1 ;
    Bool all_chars_exist ;
    unsigned default_char ;
    int n_properties ;
    XFontProp *properties ;
    XCharStruct min_bounds ;
    XCharStruct max_bounds ;
    XCharStruct *per_char ;
    int ascent ;
    int descent ;
} ;


# Loading and Freeing Fonts (8.5.1)

+FUNC Font XLoadFont ( Display *, char * ) ;
+FUNC XFontStruct *XQueryFont ( Display *, XID ) ;
+FUNC XFontStruct *XLoadQueryFont ( Display *, char * ) ;
+FUNC void XFreeFont ( Display *, XFontStruct * ) ;
+FUNC Bool XGetFontProperty ( XFontStruct *, Atom, unsigned long * ) ;
+FUNC void XUnloadFont ( Display *, Font ) ;


# Obtaining and Freeing Font Names (8.5.2)

+FUNC char **XListFonts ( Display *, char *, int, int * ) ;
+FUNC void XFreeFontNames ( char * [] ) ;
+FUNC char **XListFontsWithInfo ( Display *, char *, int, int *,
    XFontStruct ** ) ;
+FUNC void XFreeFontInfo ( char **, XFontStruct *, int ) ;


# Computing Character String Sizes (8.5.3)

+FUNC int XTextWidth ( XFontStruct *, char *, int ) ;
+FUNC int XTextWidth16 ( XFontStruct *, XChar2b *, int ) ;


# Computing Logical Extents (8.5.4)

+FUNC void XTextExtents ( XFontStruct *, char *, int, int *, int *,
    int *, XCharStruct * ) ;
+FUNC void XTextExtents16 ( XFontStruct *, XChar2b *, int, int *, int *,
    int *, XCharStruct * ) ;


# Querying Character String Sizes (8.5.5)

+FUNC void XQueryTextExtents ( Display *, XID, char *, int, int *,
    int *, int *, XCharStruct * ) ;
+FUNC void XQueryTextExtents16 ( Display *, XID, XChar2b *, int, int *,
    int *, int *, XCharStruct * ) ;


# Drawing Text (8.6)

+FIELD ( struct ) XTextItem := {
    char *chars ;
    int nchars ;
    int delta ;
    Font font ;
} ;

+FIELD ( struct ) XTextItem16 := {
    XChar2b *chars ;
    int nchars ;
    int delta ;
    Font font ;
} ;


# Drawing Complex Text (8.6.1)

+FUNC void XDrawText ( Display *, Drawable, GC, int, int, XTextItem *, int ) ;
+FUNC void XDrawText16 ( Display *, Drawable, GC, int, int, XTextItem16 *,
    int ) ;


# Drawing Text Characters (8.6.2)

+FUNC void XDrawString ( Display *, Drawable, GC, int, int, char *, int ) ;
+FUNC void XDrawString16 ( Display *, Drawable, GC, int, int, XChar2b *,
    int ) ;


# Drawing Image Text Characters (8.6.3)

+FUNC void XDrawImageString ( Display *, Drawable, GC, int, int,
    char *, int ) ;
+FUNC void XDrawImageString16 ( Display *, Drawable, GC, int, int,
    XChar2b *, int ) ;


# Transfering Images between Client and Server (8.7)

+FUNC void XPutImage ( Display *, Drawable, GC, XImage *, int, int,
    int, int, unsigned int, unsigned int ) ;
+FUNC XImage *XGetImage ( Display *, Drawable, int, int, unsigned int,
    unsigned int, unsigned long, int ) ;
+FUNC XImage *XGetSubImage ( Display *, Drawable, int, int, unsigned int,
    unsigned int, unsigned long, int, XImage *, int, int ) ;


# Changing the Parent of a Window (9.1)

+FUNC void XReparentWindow ( Display *, Window, Window, int, int ) ;


# Controlling the Lifetime of a Window (9.2)

+FUNC void XChangeSaveSet ( Display *, Window, int ) ;
+FUNC void XAddToSaveSet ( Display *, Window ) ;
+FUNC void XRemoveFromSaveSet ( Display *, Window ) ;


# Managing Installer Colormaps (9.3)

+FUNC void XInstallColormap ( Display *, Colormap ) ;
+FUNC void XUninstallColormap ( Display *, Colormap ) ;
+FUNC Colormap *XListInstalledColormaps ( Display *, Window, int * ) ;


# Setting and Retrieving Font Search Paths (9.4)

+FUNC void XSetFontPath ( Display *, char **, int ) ;
+FUNC char **XGetFontPath ( Display *, int * ) ;
+FUNC void XFreeFontPath ( char ** ) ;


# Server Grabbing (9.5)

+FUNC void XGrabServer ( Display * ) ;
+FUNC void XUngrabServer ( Display * ) ;


# Killing Clients (9.6)

+FUNC void XKillClient ( Display *, XID ) ;


# Screen Saver Control (9.7)

+FUNC void XSetScreenSaver ( Display *, int, int, int, int ) ;
+FUNC void XForceScreenSaver ( Display *, int ) ;
+FUNC void XActivateScreenSaver ( Display * ) ;
+FUNC void XResetScreenSaver ( Display * ) ;
+FUNC void XGetScreenSaver ( Display *, int *, int *, int *, int * ) ;


# Adding, Getting and Removing Hosts (9.8.1)

+FIELD ( struct ) XHostAddress := {
    int family ;
    int length ;
    char *address ;
} ;

+FUNC void XAddHost ( Display *, XHostAddress * ) ;
+FUNC void XAddHosts ( Display *, XHostAddress *, int ) ;
+FUNC XHostAddress *XListHosts ( Display *, int *, Bool * ) ;
+FUNC void XRemoveHost ( Display *, XHostAddress * ) ;
+FUNC void XRemoveHosts ( Display *, XHostAddress *, int ) ;


# Changing, Enabling or Disabling Access Control (9.8.2)

+FUNC void XSetAccessControl ( Display *, int ) ;
+FUNC void XEnableAccessControl ( Display * ) ;
+FUNC void XDisableAccessControl ( Display * ) ;


# Event Structures (10.2)

+FIELD ( struct ) XAnyEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
} ;


# Keyboard and Pointer Events (10.5.2)

+FIELD ( struct ) XButtonEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Window root ;
    Window subwindow ;
    Time time ;
    int x, y ;
    int x_root, y_root ;
    unsigned int state ;
    unsigned int button ;
    Bool same_screen ;
} ;

+TYPEDEF XButtonEvent XButtonPressedEvent ;
+TYPEDEF XButtonEvent XButtonReleasedEvent ;

+FIELD ( struct ) XKeyEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Window root ;
    Window subwindow ;
    Time time ;
    int x, y ;
    int x_root, y_root ;
    unsigned int state ;
    unsigned int keycode ;
    Bool same_screen ;
} ;

+TYPEDEF XKeyEvent XKeyPressedEvent ;
+TYPEDEF XKeyEvent XKeyReleasedEvent ;

+FIELD ( struct ) XMotionEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Window root ;
    Window subwindow ;
    Time time ;
    int x, y ;
    int x_root, y_root ;
    unsigned int state ;
    char is_hint ;
    Bool same_screen ;
} ;

+TYPEDEF XMotionEvent XPointerMovedEvent ;


# Window Entry/Exit Events (10.6)

+FIELD ( struct ) XCrossingEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Window root ;
    Window subwindow ;
    Time time ;
    int x, y ;
    int x_root, y_root ;
    int mode ;
    int detail ;
    Bool same_screen ;
    Bool focus ;
    unsigned int state ;
} ;

+TYPEDEF XCrossingEvent XEnterWindowEvent ;
+TYPEDEF XCrossingEvent XLeaveWindowEvent ;


# Input Focus Events (10.7)

+FIELD ( struct ) XFocusChangeEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    int mode ;
    int detail ;
} ;

+TYPEDEF XFocusChangeEvent XFocusInEvent ;
+TYPEDEF XFocusChangeEvent XFocusOutEvent ;


# Keymap State Notification Events (10.8)

+FIELD ( struct ) XKeymapEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    char key_vector [32] ;
} ;


# Exposure Events (10.9)

+FIELD ( struct ) XExposeEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    int x, y ;
    int width, height ;
    int count ;
} ;

+FIELD ( struct ) XGraphicsExposeEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Drawable drawable ;
    int x, y ;
    int width, height ;
    int count ;
    int major_code ;
    int minor_code ;
} ;

+FIELD ( struct ) XNoExposeEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Drawable drawable ;
    int major_code ;
    int minor_code ;
} ;


# Window State Change Events (10.10)

+FIELD ( struct ) XCirculateEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
    int place ;
} ;

+FIELD ( struct ) XConfigureEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
    int x, y ;
    int width, height ;
    int border_width ;
    Window above ;
    Bool override_redirect ;
} ;

+FIELD ( struct ) XCreateWindowEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window parent ;
    Window window ;
    int x, y ;
    int width, height ;
    int border_width ;
    Bool override_redirect ;
} ;

+FIELD ( struct ) XDestroyWindowEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
} ;

+FIELD ( struct ) XGravityEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
    int x, y ;
} ;

+FIELD ( struct ) XMapEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
    Bool override_redirect ;
} ;

+FIELD ( struct ) XMappingEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    int request ;
    int first_keycode ;
    int count ;
} ;

+FIELD ( struct ) XReparentEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
    Window parent ;
    int x, y ;
    Bool override_redirect ;
} ;

+FIELD ( struct ) XUnmapEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window event ;
    Window window ;
    Bool from_configure ;
} ;

+FIELD ( struct ) XVisibilityEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    int state ;
} ;


# Structure Control Events (10.11)

+FIELD ( struct ) XCirculateRequestEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window parent ;
    Window window ;
    int place ;
} ;

+FIELD ( struct ) XConfigureRequestEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window parent ;
    Window window ;
    int x, y ;
    int width, height ;
    int border_width ;
    Window above ;
    int detail ;
    unsigned long value_mask ;
} ;

+FIELD ( struct ) XMapRequestEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window parent ;
    Window window ;
} ;

+FIELD ( struct ) XResizeRequestEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    int width, height ;
} ;


# Colormap State Change Events (10.12)

+FIELD ( struct ) XColormapEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Colormap colormap ;
    Bool new ;
    int state ;
} ;


# Client Communication Events (10.13)

+FIELD union ~XClientMessageData := {
    char b [20] ;
    short s [10] ;
    long l [5] ;
} ;

+FIELD ( struct ) XClientMessageEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Atom message_type ;
    int format ;
    union ~XClientMessageData data ;
} ;

+FIELD ( struct ) XPropertyEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Atom atom ;
    Time time ;
    int state ;
} ;

+FIELD ( struct ) XSelectionClearEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window window ;
    Atom selection ;
    Time time ;
} ;

+FIELD ( struct ) XSelectionRequestEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window owner ;
    Window requestor ;
    Atom selection ;
    Atom target ;
    Atom property ;
    Time time ;
} ;

+FIELD ( struct ) XSelectionEvent := {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Window requestor ;
    Atom selection ;
    Atom target ;
    Atom property ;
    Time time ;
} ;


# Handing Protocol Errors (11.8): "contains" taken to mean inexact definition

+FIELD ( struct ) XErrorEvent {
    int type ;
    Display *display ;
    XID resourceid ;		# Moved from end to reflect implementations
    unsigned long serial ;
    unsigned char error_code ;
    unsigned char request_code ;
    unsigned char minor_code ;
} ;


# Event Structures (10.2)

+FIELD ( union ) XEvent := {
    int type ;
    XAnyEvent xany ;
    XKeyEvent xkey ;
    XButtonEvent xbutton ;
    XMotionEvent xmotion ;
    XCrossingEvent xcrossing ;
    XFocusChangeEvent xfocus ;
    XExposeEvent xexpose ;
    XGraphicsExposeEvent xgraphicsexpose ;
    XNoExposeEvent xnoexpose ;
    XVisibilityEvent xvisibility ;
    XCreateWindowEvent xcreatewindow ;
    XDestroyWindowEvent xdestroywindow ;
    XUnmapEvent xunmap ;
    XMapEvent xmap ;
    XMapRequestEvent xmaprequest ;
    XReparentEvent xreparent ;
    XConfigureEvent xconfigure ;
    XGravityEvent xgravity ;
    XResizeRequestEvent xresizerequest ;
    XConfigureRequestEvent xconfigurerequest ;
    XCirculateEvent xcirculate ;
    XCirculateRequestEvent xcirculaterequest ;
    XPropertyEvent xproperty ;
    XSelectionClearEvent xselectionclear ;
    XSelectionRequestEvent xselectionrequest ;
    XSelectionEvent xselection ;
    XColormapEvent xcolormap ;
    XClientMessageEvent xclient ;
    XMappingEvent xmapping ;
    XErrorEvent xerror ;
    XKeymapEvent xkeymap ;
    long pad [24] ;
} ;


# Selecting Events (11.1)

+FUNC void XSelectInput ( Display *, Window, long ) ;


# Handling the Output Buffer (11.2)

+FUNC void XFlush ( Display * ) ;
+FUNC void XSync ( Display *, Bool ) ;


# Event Queue Management (11.3)

+FUNC int XEventsQueued ( Display *, int ) ;
+FUNC int XPending ( Display * ) ;


# Manipulating the Event Queue (11.4)

+FUNC void XNextEvent ( Display *, XEvent * ) ;
+FUNC void XPeekEvent ( Display *, XEvent * ) ;
+FUNC void XIfEvent ( Display *, XEvent *, Bool (*) (), XPointer ) ;
+FUNC Bool XCheckIfEvent ( Display *, XEvent *, Bool (*) (), XPointer ) ;
+FUNC void XPeekIfEvent ( Display *, XEvent *, Bool (*) (), XPointer ) ;
+FUNC void XWindowEvent ( Display *, Window, long, XEvent * ) ;
+FUNC Bool XCheckWindowEvent ( Display *, Window, long, XEvent * ) ;
+FUNC void XMaskEvent ( Display *, long, XEvent * ) ;
+FUNC Bool XCheckMaskEvent ( Display *, long, XEvent * ) ;
+FUNC Bool XCheckTypedEvent ( Display *, int, XEvent * ) ;
+FUNC Bool XCheckTypedWindowEvent ( Display *, Window, int, XEvent * ) ;


# Putting an Event back into the Queue (11.5)

+FUNC void XPutBackEvent ( Display *, XEvent * ) ;


# Sending Events to other Applications (11.6)

+FUNC Status XSendEvent ( Display *, Window, Bool, long, XEvent * ) ;


# Getting Pointer Motion History (11.7)

+FIELD ( struct ) XTimeCoord := {
    Time time ;
    short x, y ;
} ;

+FUNC unsigned long XDisplayMotionBufferSize ( Display * ) ;
+FUNC XTimeCoord *XGetMotionEvents ( Display *, Window, Time, Time, int * ) ;


# Handing Protocol Errors (11.8)

+FUNC int ( *XSetAfterFunction ( Display *, int (*) () ) ) () ;
+FUNC int ( *XSynchronize ( Display *, Bool ) ) () ;
+FUNC int ( *XSetErrorHandler ( int (*) ( Display *, XErrorEvent * ) ) ) () ;
+FUNC void XGetErrorText ( Display *, int, char *, int ) ;
+FUNC void XGetErrorDatabaseText ( Display *, char *, char *, char *,
    char *, int ) ;
+FUNC char *XDisplayName ( char * ) ;
+FUNC int ( *XSetIOErrorHandler ( int (*) ( Display * ) ) ) () ;


# Pointer Grabbing (12.1)

+FUNC int XGrabPointer ( Display *, Window, Bool, unsigned int, int,
    int, Window, Cursor, Time ) ;
+FUNC void XUngrabPointer ( Display *, Time ) ;
+FUNC void XChangeActivePointerGrab ( Display *, unsigned int, Cursor, Time ) ;
+FUNC void XGrabButton ( Display *, unsigned int, unsigned int, Window,
    Bool, unsigned int, int, int, Window, Cursor ) ;
+FUNC void XUngrabButton ( Display *, unsigned int, unsigned int, Window ) ;


# Keyboard Grabbing (12.2)

+FUNC int XGrabKeyboard ( Display *, Window, Bool, int, int, Time ) ;
+FUNC void XUngrabKeyboard ( Display *, Time ) ;
+FUNC void XGrabKey ( Display *, int, unsigned int, Window, Bool, int, int ) ;
+FUNC void XUngrabKey ( Display *, int, unsigned int, Window ) ;


# Resuming Event Processing (12.3)

+FUNC void XAllowEvents ( Display *, int, Time ) ;


# Moving the Pointer (12.4)

+FUNC void XWarpPointer ( Display *, Window, Window, int, int, unsigned int,
    unsigned int, int, int ) ;


# Controlling Input Focus (12.5)

+FUNC void XSetInputFocus ( Display *, Window, int, Time ) ;
+FUNC void XGetInputFocus ( Display *, Window *, int * ) ;


# Keyboard and Pointer Settings (12.6)

+FIELD ( struct ) XKeyboardControl := {
    int key_click_percent ;
    int bell_percent ;
    int bell_pitch ;
    int bell_duration ;
    int led ;
    int led_mode ;
    int key ;
    int auto_repeat_mode ;
} ;

+FIELD ( struct ) XKeyboardState := {
    int key_click_percent ;
    int bell_percent ;
    unsigned int bell_pitch ;
    unsigned int bell_duration ;
    unsigned long led_mask ;
    int global_auto_repeat ;
    char auto_repeats [32] ;
} ;

+FUNC void XChangeKeyboardControl ( Display *, unsigned long,
    XKeyboardControl * ) ;
+FUNC void XGetKeyboardControl ( Display *, XKeyboardState * ) ;
+FUNC void XAutoRepeatOn ( Display * ) ;
+FUNC void XAutoRepeatOff ( Display * ) ;
+FUNC void XBell ( Display *, int ) ;
+FUNC void XQueryKeymap ( Display *, char [32] ) ;
+FUNC int XSetPointerMapping ( Display *, unsigned char [], int ) ;
+FUNC int XGetPointerMapping ( Display *, unsigned char [], int ) ;
+FUNC void XChangePointerControl ( Display *, Bool, Bool, int, int, int ) ;
+FUNC void XGetPointerControl ( Display *, int *, int *, int * ) ;


# Keyboard Encoding (12.7)

+FIELD ( struct ) XModifierKeymap := {
    int max_keypermod ;
    KeyCode *modifiermap ;
} ;

+FUNC void XDisplayKeycodes ( Display *, int *, int * ) ;
+FUNC KeySym *XGetKeyboardMapping ( Display *, KeyCode, int, int * ) ;
+FUNC void XChangeKeyboardMapping ( Display *, int, int, KeySym *, int ) ;
+FUNC XModifierKeymap *XNewModifiermap ( int ) ;
+FUNC XModifierKeymap *XInsertModifiermapEntry ( XModifierKeymap *,
    KeyCode, int ) ;
+FUNC XModifierKeymap *XDeleteModifiermapEntry ( XModifierKeymap *,
    KeyCode, int ) ;
+FUNC void XFreeModifiermap ( XModifierKeymap * ) ;
+FUNC int XSetModifierMapping ( Display *, XModifierKeymap * ) ;
+FUNC XModifierKeymap *XGetModifierMapping ( Display * ) ;


# X Locale Management (13.1)

+FUNC Bool XSupportsLocale ( void ) ;
+FUNC char *XSetLocaleModifiers ( char * ) ;


# Creating and Freeing a Font Set (13.3)

+TYPE XFontSet ;

+FUNC XFontSet XCreateFontSet ( Display *, char *, char ***, int *,
    char ** ) ;
+FUNC int XFontsOfFontSet ( XFontSet, XFontStruct ***, char *** ) ;
+FUNC char *XBaseFontNameListOfFontSet ( XFontSet ) ;
+FUNC char *XLocaleOfFontSet ( XFontSet ) ;
+FUNC void XFreeFontSet ( Display *, XFontSet ) ;


# Obtaining Font Set Metrics (13.4)

+FIELD ( struct ) XFontSetExtents := {
    XRectangle max_ink_extent ;
    XRectangle max_logical_extent ;
} ;

+FUNC Bool XContextDependentDrawing ( XFontSet ) ;
+FUNC XFontSetExtents *XExtentsOfFontSet ( XFontSet ) ;
+FUNC int XmbTextEscapement ( XFontSet, char *, int ) ;
+FUNC int XwcTextEscapement ( XFontSet, wchar_t *, int ) ;
+FUNC int XmbTextExtents ( XFontSet, char *, int, XRectangle *,
    XRectangle * ) ;
+FUNC int XwcTextExtents ( XFontSet, wchar_t *, int, XRectangle *,
    XRectangle * ) ;
+FUNC Status XmbTextPerCharExtents ( XFontSet, char *, int, XRectangle *,
    XRectangle *, int, int *, XRectangle *, XRectangle * ) ;
+FUNC Status XwcTextPerCharExtents ( XFontSet, wchar_t *, int, XRectangle *,
    XRectangle *, int, int *, XRectangle *, XRectangle * ) ;


# Drawing Text Using Font Sets (13.5)

+FIELD ( struct ) XmbTextItem := {
    char *chars ;
    int nchars ;
    int delta ;
    XFontSet font_set ;
} ;

+FIELD ( struct ) XwcTextItem := {
    wchar_t *chars ;
    int nchars ;
    int delta ;
    XFontSet font_set ;
} ;

+FUNC void XmbDrawText ( Display *, Drawable, GC, int, int, XmbTextItem *,
    int ) ;
+FUNC void XwcDrawText ( Display *, Drawable, GC, int, int, XwcTextItem *,
    int ) ;
+FUNC void XmbDrawString ( Display *, Drawable, XFontSet, GC, int, int,
    char *, int ) ;
+FUNC void XwcDrawString ( Display *, Drawable, XFontSet, GC, int, int,
    wchar_t *, int ) ;
+FUNC void XmbDrawImageString ( Display *, Drawable, XFontSet, GC, int,
    int, char *, int ) ;
+FUNC void XwcDrawImageString ( Display *, Drawable, XFontSet, GC, int,
    int, wchar_t *, int ) ;


# Input Methods (13.6)

+TYPE XIM, XIC ;


# Variable Argument Lists (13.7)

+TYPEDEF void *XVaNestedList ;
+FUNC XVaNestedList XVaCreateNestedList ( int, ... ) ;


# Input Method Functions (13.8)

+FUNC XIM XOpenIM ( Display *, XrmDatabase, char *, char * ) ;
+FUNC Status XCloseIM ( XIM ) ;
+FUNC char *XGetIMValues ( XIM, ... ) ;

+TYPEDEF unsigned long XIMStyle ;
+FIELD ( struct ) XIMStyles := {
    unsigned short count_styles ;
    XIMStyle *supported_styles ;
} ;

+DEFINE XIMPreeditArea		%% 0x0001L %% ;
+DEFINE XIMPreeditCallbacks	%% 0x0002L %% ;
+DEFINE XIMPreeditPosition	%% 0x0004L %% ;
+DEFINE XIMPreeditNothing	%% 0x0008L %% ;
+DEFINE XIMPreeditNone		%% 0x0010L %% ;
+DEFINE XIMStatusArea		%% 0x0100L %% ;
+DEFINE XIMStatusCallbacks	%% 0x0200L %% ;
+DEFINE XIMStatusNothing	%% 0x0400L %% ;
+DEFINE XIMStatusNone		%% 0x0800L %% ;

+FUNC Display *XDisplayOfIM ( XIM ) ;
+FUNC char *XLocaleOfIM ( XIM ) ;


# Input Context Functions (13.9)

+FUNC XIC XCreateIC ( XIM, ... ) ;
+FUNC void XDestroyIC ( XIC ) ;
+FUNC void XSetICFocus ( XIC ) ;
+FUNC void XUnsetICFocus ( XIC ) ;
+FUNC char *XmbResetIC ( XIC ) ;
+FUNC wchar_t *XwcResetIC ( XIC ) ;
+FUNC XIM XIMOfIC ( XIC ) ;
+FUNC char *XSetICValues ( XIC, ... ) ;
+FUNC char *XGetICValues ( XIC, ... ) ;


# XIC Value Arguments (13.10)

+TYPEDEF void ( *XIMProc ) () ;
+FIELD ( struct ) XIMCallback := {
    XPointer client_data ;
    XIMProc callback ;
} ;


# Callback Semantic (13.11)

+TYPEDEF unsigned long XIMFeedback ;

+FIELD union ~XIMTextString := {
    char *multi_byte ;
    wchar_t *wide_char ;
} ;

+FIELD ( struct ) XIMText := {
    unsigned short length ;
    XIMFeedback *feedback ;
    Bool encoding_is_wchar ;
    union ~XIMTextString string ;
} ;

+FIELD ( struct ) XIMPreeditDrawCallbackStruct := {
    int caret ;
    int chg_first ;
    int chg_length ;
    XIMText *text ;
} ;

+DEFINE XIMReverse		%% 1 %% ;
+DEFINE XIMUnderline		%% (1L<<1) %% ;
+DEFINE XIMHighlight		%% (1L<<2) %% ;
+DEFINE XIMPrimary		%% (1L<<3) %% ;
+DEFINE XIMSecondary		%% (1L<<4) %% ;
+DEFINE XIMTertiary		%% (1L<<5) %% ;

+ENUM XIMCaretStyle := {
    XIMIsInvisible,
    XIMIsPrimary,
    XIMIsSecondary
} ;

+ENUM XIMCaretDirection := {
    XIMForwardChar, XIMBackwardChar,
    XIMForwardWord, XIMBackwardWord,
    XIMCaretUp, XIMCaretDown,
    XIMNextLine, XIMPreviousLine,
    XIMLineStart, XIMLineEnd,
    XIMAbsolutePosition,
    XIMDontChange
} ;

+FIELD ( struct ) XIMPreeditCaretCallbackStruct := {
    int position ;
    XIMCaretDirection direction ;
    XIMCaretStyle style ;
} ;

+ENUM XIMStatusDataType := {
    XIMTextType,
    XIMBitmapType
} ;

+FIELD union ~XIMStatusDrawCallbackData := {
    XIMText *text ;
    Pixmap bitmap ;
} ;

+FIELD ( struct ) XIMStatusDrawCallbackStruct := {
    XIMStatusDataType type ;
    union ~XIMStatusDrawCallbackData data ;
} ;


# Event Filtering (13.12)

+FUNC Bool XFilterEvent ( XEvent *, Window ) ;


# Getting Keyboard Input (13.13)

+FUNC int XmbLookupString ( XIC, XKeyPressedEvent *, char *, int,
    KeySym *, Status * ) ;
+FUNC int XwcLookupString ( XIC, XKeyPressedEvent *, wchar_t *, int,
    KeySym *, Status * ) ;

+CONST Status XBufferOverflow, XLookupNone, XLookupChars ;
+CONST Status XLookupKeySym, XLookupBoth ;


# String Constants (13.15)

+EXP char *XNVaNestedList ;
+EXP char *XNQueryInputStyle ;
+EXP char *XNClientWindow ;
+EXP char *XNInputStyle ;
+EXP char *XNFocusWindow ;
+EXP char *XNResourceName ;
+EXP char *XNResourceClass ;
+EXP char *XNGeometryCallback ;
+EXP char *XNFilterEvents ;
+EXP char *XNPreeditStartCallback ;
+EXP char *XNPreeditDoneCallback ;
+EXP char *XNPreeditDrawCallback ;
+EXP char *XNPreeditCaretCallback ;
+EXP char *XNPreeditAttributes ;
+EXP char *XNStatusStartCallback ;
+EXP char *XNStatusDoneCallback ;
+EXP char *XNStatusDrawCallback ;
+EXP char *XNStatusAttributes ;
+EXP char *XNArea ;
+EXP char *XNAreaNeeded ;
+EXP char *XNSpotLocation ;
+EXP char *XNColormap ;
+EXP char *XNStdColormap ;
+EXP char *XNForeground ;
+EXP char *XNBackground ;
+EXP char *XNBackgroundPixmap ;
+EXP char *XNFontSet ;
+EXP char *XNLineSpace ;
+EXP char *XNCursor ;


# Client to Window Manager Communication (14.1)

+FUNC Status XIconifyWindow ( Display *, Window, int ) ;
+FUNC Status XWithdrawWindow ( Display *, Window, int ) ;
+FUNC Status XReconfigureWMWindow ( Display *, Window, int, unsigned int,
    XWindowChanges * ) ;

+FIELD ( struct ) XTextProperty := {
    unsigned char *value ;
    Atom encoding ;
    int format ;
    unsigned long nitems ;
} ;

+DEFINE XNoMemory		%% -1 %% ;
+DEFINE XLocaleNotSupported	%% -2 %% ;
+DEFINE XConverterNotFound	%% -3 %% ;

+ENUM XICCEncodingStyle := {
    XStringStyle,
    XCompoundTextStyle,
    XTextStyle,
    XStdICCTextStyle
} ;

+FUNC int XmbTextListToTextProperty ( Display *, char **, int,
    XICCEncodingStyle, XTextProperty * ) ;
+FUNC int XwcTextListToTextProperty ( Display *, wchar_t **, int,
    XICCEncodingStyle, XTextProperty * ) ;
+FUNC int XmbTextPropertyToTextList ( Display *, XTextProperty *,
    char ***, int * ) ;
+FUNC int XwcTextPropertyToTextList ( Display *, XTextProperty *,
    wchar_t ***, int * ) ;
+FUNC void XwcFreeStringList ( wchar_t ** ) ;
+FUNC char *XDefaultString ( void ) ;
+FUNC Status XStringListToTextProperty ( char **, int, XTextProperty * ) ;
+FUNC Status XTextPropertyToStringList ( XTextProperty *, char ***, int * ) ;
+FUNC void XFreeStringList ( char ** ) ;
+FUNC void XSetTextProperty ( Display *, Window, XTextProperty *, Atom ) ;
+FUNC Status XGetTextProperty ( Display *, Window, XTextProperty *, Atom ) ;
+FUNC void XSetWMName ( Display *, Window, XTextProperty * ) ;
+FUNC Status XGetWMName ( Display *, Window, XTextProperty * ) ;
+FUNC void XStoreName ( Display *, Window, char * ) ;
+FUNC Status XFetchName ( Display *, Window, char ** ) ;
+FUNC void XSetWMIconName ( Display *, Window, XTextProperty * ) ;
+FUNC Status XGetWMIconName ( Display *, Window, XTextProperty * ) ;
+FUNC void XSetIconName ( Display *, Window, char * ) ;
+FUNC Status XGetIconName ( Display *, Window, char ** ) ;

+FUNC XWMHints *XAllocWMHints ( void ) ;
+FUNC void XSetWMHints ( Display *, Window, XWMHints * ) ;
+FUNC XWMHints *XGetWMHints ( Display *, Window ) ;

+FUNC XSizeHints *XAllocSizeHints ( void ) ;
+FUNC void XSetWMNormalHints ( Display *, Window, XSizeHints * ) ;
+FUNC Status XGetWMNormalHints ( Display *, Window, XSizeHints *, long * ) ;
+FUNC void XSetWMSizeHints ( Display *, Window, XSizeHints *, Atom ) ;
+FUNC Status XGetWMSizeHints ( Display *, Window, XSizeHints *, long *,
    Atom ) ;

+FUNC XClassHint *XAllocClassHint ( void ) ;
+FUNC void XSetClassHint ( Display *, Window, XClassHint * ) ;
+FUNC Status XGetClassHint ( Display *, Window, XClassHint * ) ;

+FUNC void XSetTransientForHint ( Display *, Window, Window ) ;
+FUNC Status XGetTransientForHint ( Display *, Window, Window * ) ;

+FUNC Status XSetWMProtocols ( Display *, Window, Atom *, int ) ;
+FUNC Status XGetWMProtocols ( Display *, Window, Atom **, int * ) ;

+FUNC Status XSetWMColormapWindows ( Display *, Window, Window *, int ) ;
+FUNC Status XGetWMColormapWindows ( Display *, Window, Window **, int * ) ;

+FUNC XIconSize *XAllocIconSize ( void ) ;
+FUNC void XSetIconSizes ( Display *, Window, XIconSize *, int ) ;
+FUNC Status XGetIconSizes ( Display *, Window, XIconSize **, int * ) ;

+FUNC void XmbSetWMProperties ( Display *, Window, char *, char *,
    char * [], int, XSizeHints *, XWMHints *, XClassHint * ) ;
+FUNC void XSetWMProperties ( Display *, Window, XTextProperty *,
    XTextProperty *, char **, int, XSizeHints *, XWMHints *, XClassHint * ) ;


# Client to Session Manager Communication (14.2)

+FUNC void XSetCommand ( Display *, Window, char **, int ) ;
+FUNC Status XGetCommand ( Display *, Window, char ***, int * ) ;
+FUNC void XSetWMClientMachine ( Display *, Window, XTextProperty * ) ;
+FUNC Status XGetWMClientMachine ( Display *, Window, XTextProperty * ) ;


# Standard Colormaps (14.3)

+DEFINE ReleaseByFreeingColormap	%% ((XID)1L) %% ;

+FIELD ( struct ) XStandardColormap := {
    Colormap colormap ;
    unsigned long red_max, red_mult ;
    unsigned long green_max, green_mult ;
    unsigned long blue_max, blue_mult ;
    unsigned long base_pixel ;
    VisualID visualid ;
    XID killid ;
} ;

+FUNC XStandardColormap *XAllocStandardColormap ( void ) ;

+FUNC void XSetRGBColormaps ( Display *, Window, XStandardColormap *,
    int, Atom ) ;
+FUNC Status XGetRGBColormaps ( Display *, Window, XStandardColormap **,
    int *, Atom ) ;


# Keyboard Utility Functions (16.1)

+FUNC KeySym XLookupKeysym ( XKeyEvent *, int ) ;
+FUNC KeySym XKeycodeToKeysym ( Display *, KeyCode, int ) ;
+FUNC KeyCode XKeysymToKeycode ( Display *, KeySym ) ;
+FUNC void XRefreshKeyboardMapping ( XMappingEvent * ) ;
+FUNC KeySym XStringToKeysym ( char * ) ;
+FUNC char *XKeysymToString ( KeySym ) ;

+MACRO Bool IsCursorKey ( KeySym ) ;
+MACRO Bool IsFunctionKey ( KeySym ) ;
+MACRO Bool IsKeypadKey ( KeySym ) ;
+MACRO Bool IsMiscFunctionKey ( KeySym ) ;
+MACRO Bool IsModifierKey ( KeySym ) ;
+MACRO Bool IsPFKey ( KeySym ) ;


# Latin-1 Keyboard Event Functions (16.2)
 
+TYPE ( struct ) XComposeStatus ;
+FUNC int XLookupString ( XKeyEvent *, char *, int, KeySym *,
    XComposeStatus * ) ;
+FUNC void XRebindKeysym ( Display *, KeySym, KeySym [], int,
    unsigned char *, int ) ;


# Allocating Permanent Storage (16.3)

+FUNC char *Xpermalloc ( unsigned int ) ;


# Parsing the Window Geometry (16.4)

+FUNC int XParseGeometry ( char *, int *, int *, unsigned int *,
    unsigned int * ) ;
+FUNC int XWMGeometry ( Display *, int, char *, char *, unsigned int,
    XSizeHints *, int *, int *, int *, int *, int * ) ;


# Manipulating Regions (16.5)

+FUNC Region XCreateRegion ( void ) ;
+FUNC Region XPolygonRegion ( XPoint [], int, int ) ;
+FUNC void XSetRegion ( Display *, GC, Region ) ;
+FUNC void XDestroyRegion ( Region ) ;
+FUNC void XOffsetRegion ( Region, int, int ) ;
+FUNC void XShrinkRegion ( Region, int, int ) ;
+FUNC void XClipBox ( Region, XRectangle * ) ;
+FUNC void XIntersectRegion ( Region, Region, Region ) ;
+FUNC void XUnionRegion ( Region, Region, Region ) ;
+FUNC void XUnionRectWithRegion ( XRectangle *, Region, Region ) ;
+FUNC void XSubtractRegion ( Region, Region, Region ) ;
+FUNC void XXorRegion ( Region, Region, Region ) ;
+FUNC Bool XEmptyRegion ( Region ) ;
+FUNC Bool XEqualRegion ( Region, Region ) ;
+FUNC Bool XPointInRegion ( Region, int, int ) ;
+FUNC Bool XRectInRegion ( Region, int, int, unsigned int, unsigned int ) ;


# Using Cut Buffers (16.6)

+FUNC void XStoreBytes ( Display *, char *, int ) ;
+FUNC void XStoreBuffer ( Display *, char *, int, int ) ;
+FUNC char *XFetchBytes ( Display *, int * ) ;
+FUNC char *XFetchBuffer ( Display *, int *, int ) ;
+FUNC void XRotateBuffers ( Display *, int ) ;


# Determining a Visual Type (16.7)

+FUNC XVisualInfo *XGetVisualInfo ( Display *, long, XVisualInfo *, int * ) ;
+FUNC Status XMatchVisualInfo ( Display *, int, int, int, XVisualInfo * ) ;


# Manipulating Images (16.8)

+FUNC XImage *XCreateImage ( Display *, Visual *, unsigned int, int,
    int, char *, unsigned int, unsigned int, int, int ) ;
+FUNC void XDestroyImage ( XImage * ) ;


# Manipulating Bitmaps (16.9)

+FUNC int XReadBitmapFile ( Display *, Drawable, char *, unsigned int *,
    unsigned int *, Pixmap *, int *, int * ) ;
+FUNC int XWriteBitmapFile ( Display *, char *, Pixmap, unsigned int,
    unsigned int, int, int ) ;
+FUNC Pixmap XCreatePixmapFromBitmapData ( Display *, Drawable, char *,
    unsigned int, unsigned int, unsigned long, unsigned long, unsigned int ) ;
+FUNC Pixmap XCreateBitmapFromData ( Display *, Drawable, char *,
    unsigned int, unsigned int ) ;


# Using the Context Manager (16.10)

+TYPE XContext ;	# not actually specified
+FUNC int XSaveContext ( Display *, XID, XContext, XPointer ) ;
+FUNC int XFindContext ( Display *, XID, XContext, XPointer * ) ;
+FUNC int XDeleteContext ( Display *, XID, XContext ) ;
+FUNC XContext XUniqueContext ( void ) ;


# Extensions (Appendix C)

+FUNC Bool XQueryExtension ( Display *, char *, int *, int *, int * ) ;
+FUNC char **XListExtensions ( Display *, int * ) ;
+FUNC void XFreeExtensionList ( char ** ) ;

+FIELD ( struct ) XExtCodes := {
    int extension ;
    int major_opcode ;
    int first_event ;
    int first_error ;
} ;

+FUNC XExtCodes *XInitExtension ( Display *, char * ) ;
+FUNC XExtCodes *XAddExtension ( Display * ) ;

+FUNC int ( *XESetCloseDisplay ( Display *, int, int (*) () ) ) () ;
+FUNC int ( *XESetCreateGC ( Display *, int, int (*) () ) ) () ;
+FUNC int ( *XESetCopyGC ( Display *, int, int (*) () ) ) () ;
+FUNC int ( *XESetFreeGC ( Display *, int, int (*) () ) ) () ;
+FUNC int ( *XESetCreateFont ( Display *, int, int (*) () ) ) () ;
+FUNC int ( *XESetFreeFont ( Display *, int, int (*) () ) ) () ;
+FUNC int ( *XESetWireToEvent ( Display *, int, Status (*) () ) ) () ;
+FUNC unsigned long _XSetLastRequestRead ( Display *, xGenericReply * ) ;
+FUNC Status ( *XESetEventToWire ( Display *, int, int (*) () ) ) () ;
+FUNC Bool ( *XESetWireToError ( Display *, int, Bool (*) () ) ) () ;
+FUNC int ( *XESetError ( Display *, int, int (*) () ) ) () ;
+FUNC char *( *XESetErrorString ( Display *, int, char *(*) () ) ) () ;
+FUNC void ( *XESetPrintErrorValues ( Display *, int, void (*) () ) ) () ;
+FUNC int ( *XESetFlushGC ( Display *, int, int (*) () ) ) () ;

+FIELD XExtData := {
    int number ;
    XExtData *next ;
    int ( *free_private ) () ;
    XPointer private_data ;
} ;

+TYPE ScreenFormat ;	# RCA : not specified

+FIELD ( union ) XEDataObject := {
    Display *display ;
    GC gc ;
    Visual *visual ;
    Screen *screen ;
    ScreenFormat *pixmap_format ;
    XFontStruct *font ;
} ;

+FUNC XExtData **XEHeadOfExtensionList ( XEDataObject ) ;
+FUNC void XAddToExtensionList ( XExtData **, XExtData * ) ;
+FUNC XExtData *XFindOnExtensionList ( XExtData **, int ) ;
+MACRO XID XAllocID ( Display * ) ;
+STATEMENT FlushGC ( Display *, GC ) ;
+FUNC void _XFlushGCCache ( Display *, GC ) ;


# X11 Compatibility Functions (Appendix D)

+FUNC void XSetStandardProperties ( Display *, Window, char *, char *,
    Pixmap, char **, int, XSizeHints * ) ;
+FUNC void XSetNormalHints ( Display *, Window, XSizeHints * ) ;
+FUNC Status XGetNormalHints ( Display *, Window, XSizeHints * ) ;
+FUNC void XSetZoomHints ( Display *, Window, XSizeHints * ) ;
+FUNC Status XGetZoomHints ( Display *, Window, XSizeHints * ) ;
+FUNC void XSetSizeHints ( Display *, Window, XSizeHints *, Atom ) ;
+FUNC Status XGetSizeHints ( Display *, Window, XSizeHints *, Atom ) ;
+FUNC Status XGetStandardColormap ( Display *, Window,
    XStandardColormap *, Atom ) ;
+FUNC void XSetStandardColormap ( Display *, Window,
    XStandardColormap *, Atom ) ;
+FUNC int XGeometry ( Display *, int, char *, char *, unsigned int,
    unsigned int, unsigned int, int, int, int *, int *, int *, int * ) ;
+FUNC char *XGetDefault ( Display *, char *, char * ) ;
