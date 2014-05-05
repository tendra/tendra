# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+FUNC Atom XmInternAtom (Display *display, String name,Boolean only_if_exists);
+FUNC String XmGetAtomName (Display *display, Atom atom);

