#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "x5/t", "X11/Intrinsic.h" ;

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
