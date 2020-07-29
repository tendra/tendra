# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Needed for extensions (Appendix C)

+USE "x5/lib", "X11/Xlib.h.ts" ;		# see 1.3
+USE "x5/lib", "X11/Xproto.h.ts" ;		# see 1.3
+USE "c/c89", "stddef.h.ts", "size_t" (!?) ;

# RCA : GetReq, GetReqExtra, GetResReq, GetEmptyReq

+CONST int EPERBATCH ;

+FUNC void LockDisplay ( Display * ) ;
+FUNC void UnlockDisplay ( Display * ) ;

+STATEMENT Data ( Display *, char *, long ) ;
+STATEMENT Data16 ( Display *, short *, long ) ;
+STATEMENT Data32 ( Display *, long *, long ) ;

+FUNC void _XSend ( Display *, char *, long ) ;
+FUNC void _XReply ( Display *, xReply *, int, Bool ) ;
+FUNC void _XRead ( Display *, char *, long ) ;
+FUNC void _XRead16 ( Display *, short *, long ) ;
+FUNC void _XRead32 ( Display *, long *, long ) ;
+FUNC void _XReadPad ( Display *, char *, long ) ;
+FUNC void _XRead16Pad ( Display *, short *, long ) ;

+STATEMENT PackData ( Display *, char *, long ) ;
+STATEMENT PackData16 ( Display *, short *, long ) ;
+STATEMENT PackData32 ( Display *, long *, long ) ;

+STATEMENT __MySyncHandle ( Display * ) ;
+IFNDEF ~building_libs
+DEFINE SyncHandle ()	%% __MySyncHandle( dpy ) %% ;
+ENDIF

+FUNC void *Xmalloc ( size_t ) ;
+FUNC void *Xcalloc ( size_t, size_t ) ;
+FUNC void *Xrealloc ( void *, size_t ) ;
+FUNC void Xfree ( void * ) ;
+FUNC char *_XAllocScratch ( Display *, unsigned long ) ;
