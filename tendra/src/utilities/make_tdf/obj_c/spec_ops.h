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

#ifndef SPEC_OPS_H_INCLUDED
#define SPEC_OPS_H_INCLUDED

/* Operations for union SPECIFICATION */

#define TAG_spec( P )			( ( unsigned ) 0 )


/* Operations for component major of union SPECIFICATION */

#define spec_major( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component minor of union SPECIFICATION */

#define spec_minor( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component sorts of union SPECIFICATION */

#define spec_sorts( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for component vars of union SPECIFICATION */

#define spec_vars( P )			( CHECK_NULL ( P ) + 3 )


/* Operations for component eqns of union SPECIFICATION */

#define spec_eqns( P )			( CHECK_NULL ( P ) + 4 )


/* Operations for component foreign of union SPECIFICATION */

#define spec_foreign( P )		( CHECK_NULL ( P ) + 5 )


/* Operations for field basic of union SPECIFICATION */

#define spec_basic_tag			( ( unsigned ) 0 )
#define IS_spec_basic( P )		1


#define MAKE_spec_basic( major_, minor_, sorts_, vars_, eqns_, foreign_, tdf_spec )\
    {\
	tdf *x99_ = GEN_tdf ( 6, TYPEID_spec ) ;\
	COPY_unsigned ( x99_ + 0, ( major_ ) ) ;\
	COPY_unsigned ( x99_ + 1, ( minor_ ) ) ;\
	COPY_list ( x99_ + 2, ( sorts_ ) ) ;\
	COPY_list ( x99_ + 3, ( vars_ ) ) ;\
	COPY_list ( x99_ + 4, ( eqns_ ) ) ;\
	COPY_list ( x99_ + 5, ( foreign_ ) ) ;\
	( tdf_spec ) = x99_ ;\
    }

#define DECONS_spec_basic( major_, minor_, sorts_, vars_, eqns_, foreign_, tdf_spec )\
    {\
	tdf *x100_ = ( tdf_spec ) ;\
	( major_ ) = DEREF_unsigned ( x100_ + 0 ) ;\
	( minor_ ) = DEREF_unsigned ( x100_ + 1 ) ;\
	( sorts_ ) = DEREF_list ( x100_ + 2 ) ;\
	( vars_ ) = DEREF_list ( x100_ + 3 ) ;\
	( eqns_ ) = DEREF_list ( x100_ + 4 ) ;\
	( foreign_ ) = DEREF_list ( x100_ + 5 ) ;\
    }

#define DESTROY_spec_basic( destroyer_, major_, minor_, sorts_, vars_, eqns_, foreign_, tdf_spec )\
    {\
	tdf *x101_ = ( tdf_spec ) ;\
	( major_ ) = DEREF_unsigned ( x101_ + 0 ) ;\
	( minor_ ) = DEREF_unsigned ( x101_ + 1 ) ;\
	( sorts_ ) = DEREF_list ( x101_ + 2 ) ;\
	( vars_ ) = DEREF_list ( x101_ + 3 ) ;\
	( eqns_ ) = DEREF_list ( x101_ + 4 ) ;\
	( foreign_ ) = DEREF_list ( x101_ + 5 ) ;\
	( destroyer_ ) ( x101_, ( unsigned ) 6 ) ;\
    }


#endif
