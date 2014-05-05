# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# From "MIT-SHM - The MIT Shared Memory Extension"

+USE "x5/lib", "X11/Xlib.h.ts" ;

+FUNC Status XShmQueryExtension ( Display * ) ;
+FUNC Status XShmQueryVersion ( Display *, int *, int *, Bool * ) ;

+TYPE ( int ) ShmSeg ;

+FIELD ( struct ) XShmSegmentInfo {
    ShmSeg shmseg ;
    int shmid ;
    char *shmaddr ;
    Bool readOnly ;
} ;

+FUNC Status XShmAttach ( Display *, XShmSegmentInfo * ) ;
+FUNC XImage *XShmCreateImage ( Display *, Visual *, unsigned int,
    int, char *, XShmSegmentInfo *, unsigned int, unsigned int ) ;
+FUNC Status XShmPutImage ( Display *, Drawable, GC, XImage *,
    int, int, int, int, unsigned int, unsigned int, Bool ) ;

+FIELD ( struct ) XShmCompletionEvent {
    int type ;
    unsigned long serial ;
    Bool send_event ;
    Display *display ;
    Drawable drawable ;
    int major_code ;
    int minor_code ;
    ShmSeg shmseg ;
    unsigned long offset ;
} ;

+FUNC int XShmGetEventBase ( Display * ) ;
+CONST int ShmCompletion ;
+FUNC Status XShmGetImage ( Display *, Drawable, XImage *, int, int,
    unsigned long ) ;
+FUNC int XShmPixmapFormat ( Display * ) ;
+FUNC Pixmap XShmCreatePixmap ( Display *, Drawable, char *,
    XShmSegmentInfo *, unsigned int, unsigned int, unsigned int ) ;
