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
# Abstracted from system header

+USE "x5/lib", "X11/Xlib.h" ;

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
