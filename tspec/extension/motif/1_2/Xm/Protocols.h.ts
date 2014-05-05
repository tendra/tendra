# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";
+USE "motif/1_2","Xm/AtomMgr.h.ts";
+IMPLEMENT "xpg3", "sys/types.h.ts", "caddr_t";


+CONST Atom XmCR_WM_PROTOCOLS;
 
+MACRO Atom XM_WM_PROTOCOL_ATOM(Widget);

+MACRO void XmAddWMProtocols(Widget, Atom *, Cardinal);
+MACRO void XmRemoveWMProtocols(Widget, Atom *, Cardinal);
+MACRO void XmAddWMProtocolCallback(Widget, Atom, XtCallbackProc, XtPointer);
+MACRO void XmRemoveWMProtocolCallback(Widget, Atom, XtCallbackProc, XtPointer);
+MACRO void XmActivateWMProtocol(Widget, Atom );
+MACRO void XmDeactivateWMProtocol(Widget, Atom);
+MACRO void XmSetWMProtocolHooks(Widget, Atom, XtCallbackProc, XtPointer, XtCallbackProc, XtPointer);

+FUNC void XmAddProtocols(Widget, Atom, Atom *, Cardinal);
+FUNC void XmRemoveProtocols(Widget, Atom, Atom *, Cardinal);
+FUNC void XmAddProtocolCallback(Widget, Atom, Atom, XtCallbackProc, XtPointer);
+FUNC void XmRemoveProtocolCallback(Widget, Atom, Atom, XtCallbackProc, XtPointer);
+FUNC void XmActivateProtocol(Widget, Atom, Atom);
+FUNC void XmDeactivateProtocol(Widget, Atom, Atom);
+FUNC void XmSetProtocolHooks(Widget, Atom, Atom, XtCallbackProc, XtPointer, XtCallbackProc, XtPointer);


