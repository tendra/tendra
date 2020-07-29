# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __MOTIF_P_HEADERS
#error Unexpected access to Motif P headers
#endif
%%

+USE "motif/1_2", "Xm/GadgetP.h.ts";

+DEFINE DataToGadgetCache(p) %% ((char *)p - XtOffsetOf(XmGadgetCacheRef, data)) %%;

+DEFINE ClassCacheHead(cp) %% ((cp)->cache_head) %%;
+DEFINE ClassCacheCopy(cp) %% ((cp)->cache_copy) %%;
+DEFINE ClassCacheCompare(cp) %% ((cp)->cache_compare) %%;
+DEFINE CacheDataPtr(cp) %% ((XtPointer)&((XmGadgetCacheRef*)p)-> data) %%;

+FUNC void _XmCacheDelete( XtPointer );
+FUNC void _XmCacheCopy( XtPointer, XtPointer, size_t);
+FUNC XtPointer _XmCachePart(XmCacheClassPartPtr, XtPointer, size_t);


