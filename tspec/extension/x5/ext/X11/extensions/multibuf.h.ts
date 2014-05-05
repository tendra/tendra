# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Abstracted from system header

+USE "x5/lib", "X11/Xlib.h.ts" ;

+CONST char *MULTIBUFFER_PROTOCOL_NAME ;
+CONST int MULTIBUFFER_MAJOR_VERSION, MULTIBUFFER_MINOR_VERSION ;

+CONST int X_MbufGetBufferVersion, X_MbufCreateImageBuffers ;
+CONST int X_MbufDestroyImageBuffers, X_MbufDisplayImageBuffers ;
+CONST int X_MbufSetMBufferAttributes, X_MbufGetMBufferAttributes ;
+CONST int X_MbufSetBufferAttributes, X_MbufGetBufferAttributes ;
+CONST int X_MbufGetBufferInfo, X_MbufCreateStereoWindow ;

+CONST int MultibufferUpdateActionUndefined ;
+CONST int MultibufferUpdateActionBackground ;
+CONST int MultibufferUpdateActionUntouched ;
+CONST int  MultibufferUpdateActionCopied ;

+CONST int MultibufferUpdateHintFrequent, MultibufferUpdateHintIntermittent ;
+CONST int MultibufferUpdateHintStatic ;

+CONST int MultibufferWindowUpdateHint, MultibufferBufferEventMask ;

+CONST int MultibufferModeMono, MultibufferModeStereo, MultibufferSideMono ;
+CONST int MultibufferSideLeft, MultibufferSideRight ;

+CONST int MultibufferUnclobbered, MultibufferPartiallyClobbered ;
+CONST int MultibufferFullyClobbered ;

+CONST long MultibufferClobberNotifyMask, MultibufferUpdateNotifyMask ;

+CONST int MultibufferClobberNotify, MultibufferUpdateNotify ;
+CONST int MultibufferNumberEvents ;

+CONST int MultibufferBadBuffer, MultibufferNumberErrors ;

+TYPEDEF XID Multibuffer ;

+FIELD ( struct ) XmbufClobberNotifyEvent {
    int type ;
    unsigned long serial ;
    int send_event ;
    Display *display ;
    Multibuffer buffer ;
    int state ;
} ;

+FIELD ( struct ) XmbufUpdateNotifyEvent {
    int type ;
    unsigned long serial ;
    int send_event ;
    Display *display ;
    Multibuffer buffer ;
} ;

+FIELD ( struct ) XmbufWindowAttributes {
    int displayed_index ;
    int update_action ;
    int update_hint ;
    int window_mode ;
    int nbuffers ;
    Multibuffer *buffers ;
} ;

+FIELD ( struct ) XmbufSetWindowAttributes {
    int update_hint ;
} ;

+FIELD ( struct ) XmbufBufferAttributes {
    Window window ;
    unsigned long event_mask ;
    int buffer_index ;
    int side ;
} ;

+FIELD ( struct ) XmbufSetBufferAttributes {
    unsigned long event_mask ;
} ;

+FIELD ( struct ) XmbufBufferInfo {
    VisualID visualid ;
    int max_buffers ;
    int depth ;
} ;

+FUNC Bool XmbufQueryExtension ( Display *, int *, int * ) ;
+FUNC Status XmbufGetVersion ( Display *, int *, int * ) ;
+FUNC int XmbufCreateBuffers ( Display *, Window, int, int, int,
    Multibuffer * ) ;
+FUNC void XmbufDestroyBuffers ( Display *, Window ) ;
+FUNC void XmbufDisplayBuffers ( Display *, int, Multibuffer *, int, int ) ;
+FUNC Status XmbufGetWindowAttributes ( Display *, Window,
    XmbufWindowAttributes * ) ;
+FUNC void XmbufChangeWindowAttributes ( Display *, Window, unsigned long,
    XmbufSetWindowAttributes * ) ;
+FUNC Status XmbufGetBufferAttributes ( Display *, Multibuffer,
    XmbufBufferAttributes * ) ;
+FUNC void XmbufChangeBufferAttributes ( Display *, Multibuffer,
    unsigned long, XmbufSetBufferAttributes * ) ;
+FUNC Status XmbufGetScreenInfo ( Display *, Drawable, int *,
    XmbufBufferInfo **, int *, XmbufBufferInfo ** ) ;
+FUNC Window XmbufCreateStereoWindow ( Display *, Window, int, int,
    unsigned int, unsigned int, unsigned int, int, unsigned int,
    Visual *, unsigned long, XSetWindowAttributes *, Multibuffer *,
    Multibuffer * ) ;
