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
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef LINK_OPS_H_INCLUDED
#define LINK_OPS_H_INCLUDED

/* Operations for union LINKAGE */

#define TAG_link( P )			( ( unsigned ) 0 )


/* Operations for component name of union LINKAGE */

#define link_name( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component type of union LINKAGE */

#define link_type( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for field basic of union LINKAGE */

#define link_basic_tag			( ( unsigned ) 0 )
#define IS_link_basic( P )		1


#define MAKE_link_basic( name_, type_, tdf_link )\
    {\
	tdf *x96_ = GEN_tdf ( 2, TYPEID_link ) ;\
	COPY_string ( x96_ + 0, ( name_ ) ) ;\
	COPY_sort ( x96_ + 1, ( type_ ) ) ;\
	( tdf_link ) = x96_ ;\
    }

#define DECONS_link_basic( name_, type_, tdf_link )\
    {\
	tdf *x97_ = ( tdf_link ) ;\
	( name_ ) = DEREF_string ( x97_ + 0 ) ;\
	( type_ ) = DEREF_sort ( x97_ + 1 ) ;\
    }

#define DESTROY_link_basic( destroyer_, name_, type_, tdf_link )\
    {\
	tdf *x98_ = ( tdf_link ) ;\
	( name_ ) = DEREF_string ( x98_ + 0 ) ;\
	( type_ ) = DEREF_sort ( x98_ + 1 ) ;\
	( destroyer_ ) ( x98_, ( unsigned ) 2 ) ;\
    }


#endif
