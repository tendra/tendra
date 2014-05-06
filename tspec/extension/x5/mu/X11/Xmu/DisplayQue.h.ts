# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/types.h.ts", "caddr_t" (!?) ;
+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/mu", "X11/Xmu/CloseHook.h.ts" (!?) ;

+TYPE ( struct ) XmuDisplayQueueEntry ;

+FIELD XmuDisplayQueueEntry := {
    XmuDisplayQueueEntry *prev ;
    XmuDisplayQueueEntry *next ;
    Display *display ;
    CloseHook closehook ;
    caddr_t data ;
} ;

+TYPE ( struct ) XmuDisplayQueue ;

+FIELD XmuDisplayQueue := {
    int nentries ;
    XmuDisplayQueueEntry *head ;
    XmuDisplayQueueEntry *tail ;
    int ( *closefunc ) () ;
    int ( *freefunc ) () ;
    caddr_t data ;
} ;

+FUNC XmuDisplayQueue *XmuDQCreate ( int (*) (), int (*) (), caddr_t ) ;
+FUNC XmuDisplayQueueEntry *XmuDQAddDisplay ( XmuDisplayQueue *,
    Display *, caddr_t ) ;
+FUNC XmuDisplayQueueEntry *XmuDQLookupDisplay ( XmuDisplayQueue *,
    Display * ) ;
+MACRO int XmuDQNDisplays ( XmuDisplayQueue * ) ;
+FUNC Bool XmuDQRemoveDisplay ( XmuDisplayQueue *, Display * ) ;
+FUNC Bool XmuDQDestroy ( XmuDisplayQueue *, Bool ) ;
