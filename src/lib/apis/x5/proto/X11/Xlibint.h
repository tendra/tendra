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
+USE "x5/lib", "X11/Xlibint.h" ;
+USE "x5/proto", "X11/Xproto.h" ;

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
