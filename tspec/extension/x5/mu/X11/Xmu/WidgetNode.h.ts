# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

+TYPE XmuWidgetNode ;	# RCA : not specified
+FUNC void XmuWnInitializeNodes ( XmuWidgetNode *, int ) ;
+FUNC void XmuWnFetchResources ( XmuWidgetNode *, Widget, XmuWidgetNode * ) ;
+FUNC int XmuWnCountOwnedResources ( XmuWidgetNode *, XmuWidgetNode *, Bool ) ;
+FUNC XmuWidgetNode *XmuWnNameToNode ( XmuWidgetNode *, int, char * ) ;
