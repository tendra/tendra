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

+FUNC Boolean _XmTextFieldConvert(Widget, Atom *, Atom *, Atom *, XtPointer *, unsigned long *, int *);
+FUNC void _XmTextFieldLoseSelection(Widget, Atom *);

