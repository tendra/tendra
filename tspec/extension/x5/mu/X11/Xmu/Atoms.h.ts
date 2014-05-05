# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;

+MACRO Atom XA_ATOM_PAIR ( Display * ) ;
+MACRO Atom XA_CHARACTER_POSITION ( Display * ) ;
+MACRO Atom XA_CLASS ( Display * ) ;
+MACRO Atom XA_CLIENT_WINDOW ( Display * ) ;
+MACRO Atom XA_CLIPBOARD ( Display * ) ;
+MACRO Atom XA_COMPOUND_TEXT ( Display * ) ;
+MACRO Atom XA_DECNET_ADDRESS ( Display * ) ;
+MACRO Atom XA_DELETE ( Display * ) ;
+MACRO Atom XA_FILENAME ( Display * ) ;
+MACRO Atom XA_HOSTNAME ( Display * ) ;
+MACRO Atom XA_IP_ADDRESS ( Display * ) ;
+MACRO Atom XA_LENGTH ( Display * ) ;
+MACRO Atom XA_LIST_LENGTH ( Display * ) ;
+MACRO Atom XA_NAME ( Display * ) ;
+MACRO Atom XA_NET_ADDRESS ( Display * ) ;
+MACRO Atom XA_NULL ( Display * ) ;
+MACRO Atom XA_OWNER_OS ( Display * ) ;
+MACRO Atom XA_SPAN ( Display * ) ;
+MACRO Atom XA_TARGETS ( Display * ) ;
+MACRO Atom XA_TEXT ( Display * ) ;
+MACRO Atom XA_TIMESTAMP ( Display * ) ;
+MACRO Atom XA_USER ( Display * ) ;

+TYPE AtomPtr ;
+FUNC AtomPtr XmuMakeAtom ( char * ) ;
+FUNC char *XmuNameOfAtom ( AtomPtr ) ;
+FUNC Atom XmuInternAtom ( Display *, AtomPtr ) ;
+FUNC char *XmuGetAtomName ( Display *, Atom ) ;
+FUNC void XmuInternStrings ( Display *, String *, Cardinal, Atom * ) ;
