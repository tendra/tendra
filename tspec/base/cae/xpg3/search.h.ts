# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+SUBSET "srch_proto" := {
    +USE "c/c89", "stddef.h.ts", "size_t" (!?) ;

    +FIELD struct entry { char *key ; } ;
    +TYPEDEF struct entry ENTRY ;

    +ENUM ACTION := { FIND, ENTER } ;
    +ENUM VISIT := { preorder, postorder, endorder, leaf } ;

    +FUNC void hdestroy ( void ) ;
    +FUNC ENTRY *hsearch ( ENTRY, ACTION ) ;
    +FUNC void *tsearch ( const void *, void **,
			  int (*) ( const void *, const void * ) ) ;
    +FUNC void *tdelete ( const void *, void **, 
			  int (*) ( const void *, const void * ) ) ;
    +FUNC void *tfind ( const void *, void * const *,
			int (*) ( const void *, const void * ) ) ;
    +FUNC void *lfind ( const void *, const void *, size_t *, size_t,
			int (*) ( const void *, const void * ) ) ;
    +FUNC void *lsearch ( const void *, void *, size_t *, size_t,
			  int (*) ( const void *, const void * ) ) ;
} ;

+FIELD struct entry { char *data ; } ;
+FUNC void twalk ( void *, void (*) ( const void *, VISIT, int ) ) ;
+IFNDEF ~building_libs
+FUNC int hcreate ( unsigned ) ;
+ELSE
+FUNC int __old_hcreate | hcreate.1 ( unsigned ) ;
%%%
#define __old_hcreate( X )	hcreate ( X )
%%%
+ENDIF

%%%
/* This is sufficiently common to put here */
#pragma TenDRA begin
#pragma TenDRA compatible type : char * == void * : allow
%%%
