/*
    COPYRIGHT NOTICE

    This program is the proprietary property of IXI Ltd, a subsidiary
    of the Santa Cruz Operation (SCO). Use, reproduction, production
    of amended versions and/or transfer of this program is permitted
    PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996

*/



/* SCO CID (IXI) DrawP.h,v 1.1 1996/08/08 14:12:40 wendland Exp */

%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/XmP.h";

+FUNC void _XmDrawShadows(Display *, Drawable, GC, GC, Position, Position, Dimension, Dimension, Dimension, unsigned int);

+FUNC void _XmClearBorder(Display *, Window, Position, Position, Dimension, Dimension, Dimension);

+FUNC void _XmDrawSeparator(Display *, Drawable, GC, GC, GC, Position, Position, Dimension, Dimension, Dimension, Dimension, unsigned char, unsigned char);

+FUNC void _XmDrawDiamond(Display *, Drawable, GC, GC, GC, Position, Position, Dimension, Dimension, Dimension, Dimension);

+FUNC void _XmDrawSimpleHighlight(Display *, Drawable, GC, Position, Position, Dimension, Dimension, Dimension);

+FUNC void _XmDrawHighlight(Display*, Drawable, GC, Position, Position, Dimension, Dimension, Dimension, int);

+FUNC void _XmDrawArrow(Display *, Drawable, GC, GC, GC, Position, Position, Dimension, Dimension, Dimension, unsigned char);


