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

#ifndef CONS_OPS_H_INCLUDED
#define CONS_OPS_H_INCLUDED

/* Operations for union CONSTRUCT */

#define TAG_cons( P )			( ( unsigned ) 0 )


/* Operations for component name of union CONSTRUCT */

#define cons_name( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component encode of union CONSTRUCT */

#define cons_encode( P )		( CHECK_NULL ( P ) + 1 )


/* Operations for component res of union CONSTRUCT */

#define cons_res( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for component pars of union CONSTRUCT */

#define cons_pars( P )			( CHECK_NULL ( P ) + 3 )


/* Operations for component kind of union CONSTRUCT */

#define cons_kind( P )			( CHECK_NULL ( P ) + 4 )


/* Operations for field basic of union CONSTRUCT */

#define cons_basic_tag			( ( unsigned ) 0 )
#define IS_cons_basic( P )		1


#define MAKE_cons_basic( name_, encode_, res_, pars_, kind_, tdf_cons )\
    {\
	tdf *x68_ = GEN_tdf ( 5, TYPEID_cons ) ;\
	COPY_string ( x68_ + 0, ( name_ ) ) ;\
	COPY_unsigned ( x68_ + 1, ( encode_ ) ) ;\
	COPY_sort ( x68_ + 2, ( res_ ) ) ;\
	COPY_list ( x68_ + 3, ( pars_ ) ) ;\
	COPY_unsigned ( x68_ + 4, ( kind_ ) ) ;\
	( tdf_cons ) = x68_ ;\
    }

#define DECONS_cons_basic( name_, encode_, res_, pars_, kind_, tdf_cons )\
    {\
	tdf *x69_ = ( tdf_cons ) ;\
	( name_ ) = DEREF_string ( x69_ + 0 ) ;\
	( encode_ ) = DEREF_unsigned ( x69_ + 1 ) ;\
	( res_ ) = DEREF_sort ( x69_ + 2 ) ;\
	( pars_ ) = DEREF_list ( x69_ + 3 ) ;\
	( kind_ ) = DEREF_unsigned ( x69_ + 4 ) ;\
    }

#define DESTROY_cons_basic( destroyer_, name_, encode_, res_, pars_, kind_, tdf_cons )\
    {\
	tdf *x70_ = ( tdf_cons ) ;\
	( name_ ) = DEREF_string ( x70_ + 0 ) ;\
	( encode_ ) = DEREF_unsigned ( x70_ + 1 ) ;\
	( res_ ) = DEREF_sort ( x70_ + 2 ) ;\
	( pars_ ) = DEREF_list ( x70_ + 3 ) ;\
	( kind_ ) = DEREF_unsigned ( x70_ + 4 ) ;\
	( destroyer_ ) ( x70_, ( unsigned ) 5 ) ;\
    }


#endif
