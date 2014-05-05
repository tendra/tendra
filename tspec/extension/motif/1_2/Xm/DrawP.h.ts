# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h.ts";

+FUNC void _XmDrawShadows(Display *, Drawable, GC, GC, Position, Position, Dimension, Dimension, Dimension, unsigned int);

+FUNC void _XmClearBorder(Display *, Window, Position, Position, Dimension, Dimension, Dimension);

+FUNC void _XmDrawSeparator(Display *, Drawable, GC, GC, GC, Position, Position, Dimension, Dimension, Dimension, Dimension, unsigned char, unsigned char);

+FUNC void _XmDrawDiamond(Display *, Drawable, GC, GC, GC, Position, Position, Dimension, Dimension, Dimension, Dimension);

+FUNC void _XmDrawSimpleHighlight(Display *, Drawable, GC, Position, Position, Dimension, Dimension, Dimension);

+FUNC void _XmDrawHighlight(Display*, Drawable, GC, Position, Position, Dimension, Dimension, Dimension, int);

+FUNC void _XmDrawArrow(Display *, Drawable, GC, GC, GC, Position, Position, Dimension, Dimension, Dimension, unsigned char);


