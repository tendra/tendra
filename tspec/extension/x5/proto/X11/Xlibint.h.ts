# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/lib", "X11/Xlibint.h.ts" ;
+USE "x5/proto", "X11/Xproto.h.ts" ;

+STATEMENT __MyDisplayFlush ( Display *, int ) ;
+MACRO void *__MyDisplayLastRequest ( lvalue Display * ) ;
+MACRO void __MyDisplayAddBuffer ( lvalue Display *, int ) ;
+MACRO void __MyDisplayNextRequest ( lvalue Display * ) ;

+IFNDEF ~building_libs
%%
#define __MyGetReq( reqtype, reqno, n, req )\
    __MyDisplayFlush ( dpy, sizeof ( reqtype ) + ( n ) ) ;\
    ( req ) = ( reqtype * ) __MyDisplayLastRequest ( dpy ) ;\
    ( req )->reqType = ( reqno ) ;\
    ( req )->length = ( sizeof ( reqtype ) + ( n ) ) >> 2 ;\
    __MyDisplayAddBuffer ( dpy, sizeof ( reqtype ) + ( n ) ) ;\
    __MyDisplayNextRequest ( dpy )

#define GetReq( name, req )\
    __MyGetReq ( x##name##Req, X_##name, 0, req )

#define GetReqExtra( name, n, req )\
    __MyGetReq ( x##name##Req, X_##name, n, req )

#define GetResReq( name, rid, req )\
    __MyGetReq ( x##name##Req, X_##name, 0, req ) ;\
    ( req )->id = ( rid )

#define GetEmptyReq( name, req )\
    __MyGetReq ( xReq, X_##name, 0, req )
%%
+ENDIF
