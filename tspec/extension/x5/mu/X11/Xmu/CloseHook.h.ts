# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/types.h.ts", "caddr_t" (!?) ;
+USE "x5/t", "X11/Intrinsic.h.ts" ;

# RCA : CloseHook can be NULL, so it is probably a pointer
+TYPE ~CloseHook ;
+TYPEDEF ~CloseHook *CloseHook ;

+FUNC CloseHook XmuAddCloseDisplayHook ( Display *, int (*) (), caddr_t ) ;
+FUNC Bool XmuRemoveCloseDisplayHook ( Display *, CloseHook, int (*) (),
    caddr_t ) ;
+FUNC Bool XmuLookupCloseDisplayHook ( Display *, CloseHook, int (*) (),
    caddr_t ) ;
