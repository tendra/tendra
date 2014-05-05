# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

+FUNC Status XmuAllStandardColormaps ( Display * ) ;
+FUNC Status XmuVisualStandardColormaps ( Display *, int, VisualID,
    unsigned int, Bool, Bool ) ;
+FUNC Status XmuLookupStandardColormap ( Display *, int, VisualID,
    unsigned int, Atom, Bool, Bool ) ;
+FUNC Status XmuGetColormapAllocation ( XVisualInfo *, Atom,
    unsigned long *, unsigned long *, unsigned long * ) ;
+FUNC XStandardColormap *XmuStandardColormap ( Display *, int, VisualID,
    unsigned int, Atom, Colormap, unsigned long, unsigned long,
    unsigned long ) ;
+FUNC Status XmuCreateColormap ( Display *, XStandardColormap * ) ;
+FUNC void XmuDeleteStandardColormap ( Display *, int, Atom ) ;
