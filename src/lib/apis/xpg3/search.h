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
+SUBSET "srch_proto" := {
    +USE "ansi", "stddef.h", "size_t" (!?) ;

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
