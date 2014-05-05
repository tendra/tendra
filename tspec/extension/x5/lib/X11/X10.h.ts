# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# X10 compatibility functions (Appendix D)

+USE "x5/lib", "X11/Xlib.h.ts" ;

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
