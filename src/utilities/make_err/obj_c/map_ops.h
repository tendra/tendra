/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef MAP_OPS_H_INCLUDED
#define MAP_OPS_H_INCLUDED

/* Operations for union MAP */

#define TAG_map( P )			( ( unsigned ) 0 )


/* Operations for component key of union MAP */

#define map_key( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component msg of union MAP */

#define map_msg( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component alt_msg of union MAP */

#define map_alt_msg( P )		( CHECK_NULL ( P ) + 2 )


/* Operations for field basic of union MAP */

#define map_basic_tag			( ( unsigned ) 0 )
#define IS_map_basic( P )		1


#define MAKE_map_basic( key_, msg_, alt_msg_, errors_map )\
    {\
	errors *x59_ = GEN_errors ( 3, TYPEID_map ) ;\
	COPY_name ( x59_ + 0, ( key_ ) ) ;\
	COPY_list ( x59_ + 1, ( msg_ ) ) ;\
	COPY_list ( x59_ + 2, ( alt_msg_ ) ) ;\
	( errors_map ) = x59_ ;\
    }

#define DECONS_map_basic( key_, msg_, alt_msg_, errors_map )\
    {\
	errors *x60_ = ( errors_map ) ;\
	( key_ ) = DEREF_name ( x60_ + 0 ) ;\
	( msg_ ) = DEREF_list ( x60_ + 1 ) ;\
	( alt_msg_ ) = DEREF_list ( x60_ + 2 ) ;\
    }

#define DESTROY_map_basic( destroyer_, key_, msg_, alt_msg_, errors_map )\
    {\
	errors *x61_ = ( errors_map ) ;\
	( key_ ) = DEREF_name ( x61_ + 0 ) ;\
	( msg_ ) = DEREF_list ( x61_ + 1 ) ;\
	( alt_msg_ ) = DEREF_list ( x61_ + 2 ) ;\
	( destroyer_ ) ( x61_, ( unsigned ) 3 ) ;\
    }


#endif
