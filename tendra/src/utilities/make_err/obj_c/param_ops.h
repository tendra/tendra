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

#ifndef PARAM_OPS_H_INCLUDED
#define PARAM_OPS_H_INCLUDED

/* Operations for union PARAM */

#define TAG_param( P )			( ( unsigned ) 0 )


/* Operations for component type of union PARAM */

#define param_type( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component name of union PARAM */

#define param_name( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component number of union PARAM */

#define param_number( P )		( CHECK_NULL ( P ) + 2 )


/* Operations for field basic of union PARAM */

#define param_basic_tag			( ( unsigned ) 0 )
#define IS_param_basic( P )		1


#define MAKE_param_basic( type_, name_, number_, errors_param )\
    {\
	errors *x62_ = GEN_errors ( 3, TYPEID_param ) ;\
	COPY_name ( x62_ + 0, ( type_ ) ) ;\
	COPY_string ( x62_ + 1, ( name_ ) ) ;\
	COPY_int ( x62_ + 2, ( number_ ) ) ;\
	( errors_param ) = x62_ ;\
    }

#define DECONS_param_basic( type_, name_, number_, errors_param )\
    {\
	errors *x63_ = ( errors_param ) ;\
	( type_ ) = DEREF_name ( x63_ + 0 ) ;\
	( name_ ) = DEREF_string ( x63_ + 1 ) ;\
	( number_ ) = DEREF_int ( x63_ + 2 ) ;\
    }

#define DESTROY_param_basic( destroyer_, type_, name_, number_, errors_param )\
    {\
	errors *x64_ = ( errors_param ) ;\
	( type_ ) = DEREF_name ( x64_ + 0 ) ;\
	( name_ ) = DEREF_string ( x64_ + 1 ) ;\
	( number_ ) = DEREF_int ( x64_ + 2 ) ;\
	( destroyer_ ) ( x64_, ( unsigned ) 3 ) ;\
    }


#endif
