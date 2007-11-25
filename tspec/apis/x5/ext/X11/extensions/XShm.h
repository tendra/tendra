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
# From "MIT-SHM - The MIT Shared Memory Extension"

+USE "x5/lib", "X11/Xlib.h" ;

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
