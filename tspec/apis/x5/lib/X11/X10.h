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
# X10 compatibility functions (Appendix D)

+USE "x5/lib", "X11/Xlib.h" ;

+IF 0

/* These are defunct */

+FIELD ( struct ) Vertex := {
    short x, y ;
    unsigned short flags ;
} ;

+FUNC Status XDraw ( Display *, Drawable, GC, Vertex *, int ) ;
+FUNC Status XDrawFilled ( Display *, Drawable, GC, Vertex *, int ) ;

+DEFINE VertexRelative		%% 0x0001 %% ;
+DEFINE VertexDontDraw		%% 0x0002 %% ;
+DEFINE VertexCurved		%% 0x0004 %% ;
+DEFINE VertexStartClosed	%% 0x0008 %% ;
+DEFINE VertexEndClosed		%% 0x0010 %% ;

+TYPE XAssocTable ;
+FUNC XAssocTable *XCreateAssocTable ( int ) ;
+FUNC void XMakeAssoc ( Display *, XAssocTable *, XID, char * ) ;
+FUNC char *XLookUpAssoc ( Display *, XAssocTable *, XID ) ;
+FUNC void XDeleteAssoc ( Display *, XAssocTable *, XID ) ;
+FUNC void XDestroyAssocTable ( XAssocTable * ) ;

+ENDIF
