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
# Needed for extensions (Appendix C)

+USE "x5/lib", "X11/Xlib.h" ;		# see 1.3
+USE "x5/lib", "X11/Xproto.h" ;		# see 1.3
+USE "ansi", "stddef.h", "size_t" (!?) ;

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
