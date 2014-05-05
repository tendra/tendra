# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "xpg3", "search.h.ts", "srch_proto" ;

# Different from xpg3
+FIELD struct entry { void *data ; } ;
+FUNC int hcreate ( size_t ) ;
+FUNC void twalk ( const void *, void (*) ( const void *, VISIT, int ) ) ;

%%%
/* This is sufficiently common to put here */
#pragma TenDRA begin
#pragma TenDRA compatible type : char * == void * : allow
%%%
