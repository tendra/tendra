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

#ifndef PAR_OPS_H_INCLUDED
#define PAR_OPS_H_INCLUDED

/* Operations for union PARAMETER */

#define TAG_par( P )			( ( unsigned ) 0 )


/* Operations for component name of union PARAMETER */

#define par_name( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component type of union PARAMETER */

#define par_type( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component brk of union PARAMETER */

#define par_brk( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for component align of union PARAMETER */

#define par_align( P )			( CHECK_NULL ( P ) + 3 )


/* Operations for component intro of union PARAMETER */

#define par_intro( P )			( CHECK_NULL ( P ) + 4 )


/* Operations for field basic of union PARAMETER */

#define par_basic_tag			( ( unsigned ) 0 )
#define IS_par_basic( P )		1


#define MAKE_par_basic( name_, type_, brk_, align_, intro_, tdf_par )\
    {\
	tdf *x65_ = GEN_tdf ( 5, TYPEID_par ) ;\
	COPY_string ( x65_ + 0, ( name_ ) ) ;\
	COPY_sort ( x65_ + 1, ( type_ ) ) ;\
	COPY_int ( x65_ + 2, ( brk_ ) ) ;\
	COPY_int ( x65_ + 3, ( align_ ) ) ;\
	COPY_int ( x65_ + 4, ( intro_ ) ) ;\
	( tdf_par ) = x65_ ;\
    }

#define DECONS_par_basic( name_, type_, brk_, align_, intro_, tdf_par )\
    {\
	tdf *x66_ = ( tdf_par ) ;\
	( name_ ) = DEREF_string ( x66_ + 0 ) ;\
	( type_ ) = DEREF_sort ( x66_ + 1 ) ;\
	( brk_ ) = DEREF_int ( x66_ + 2 ) ;\
	( align_ ) = DEREF_int ( x66_ + 3 ) ;\
	( intro_ ) = DEREF_int ( x66_ + 4 ) ;\
    }

#define DESTROY_par_basic( destroyer_, name_, type_, brk_, align_, intro_, tdf_par )\
    {\
	tdf *x67_ = ( tdf_par ) ;\
	( name_ ) = DEREF_string ( x67_ + 0 ) ;\
	( type_ ) = DEREF_sort ( x67_ + 1 ) ;\
	( brk_ ) = DEREF_int ( x67_ + 2 ) ;\
	( align_ ) = DEREF_int ( x67_ + 3 ) ;\
	( intro_ ) = DEREF_int ( x67_ + 4 ) ;\
	( destroyer_ ) ( x67_, ( unsigned ) 5 ) ;\
    }


#endif
