/*
    		 Crown Copyright (c) 1997, 1998
    
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
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.2)
*/

#ifndef ETYPE_OPS_H_INCLUDED
#define ETYPE_OPS_H_INCLUDED

/* Operations for union ENUM_TYPE */

#define TAG_etype( P )			( ( unsigned ) 0 )


/* Operations for component name of union ENUM_TYPE */

#define etype_name( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component info of union ENUM_TYPE */

#define etype_info( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component rep of union ENUM_TYPE */

#define etype_rep( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for component form of union ENUM_TYPE */

#define etype_form( P )			( CHECK_NULL ( P ) + 3 )


/* Operations for component values of union ENUM_TYPE */

#define etype_values( P )		( CHECK_NULL ( P ) + 4 )


/* Operations for component value of union ENUM_TYPE */

#define etype_value( P )		( CHECK_NULL ( P ) + 5 )


/* Operations for component plus of union ENUM_TYPE */

#define etype_plus( P )			( CHECK_NULL ( P ) + 6 )


/* Operations for field basic of union ENUM_TYPE */

#define etype_basic_tag			( ( unsigned ) 0 )
#define IS_etype_basic( P )		1


#define MAKE_etype_basic( name_, info_, rep_, c_class_etype )\
    {\
	c_class *x223_ = GEN_c_class ( 7, TYPEID_etype ) ;\
	COPY_id ( x223_ + 0, ( name_ ) ) ;\
	COPY_cinfo ( x223_ + 1, ( info_ ) ) ;\
	COPY_type ( x223_ + 2, ( rep_ ) ) ;\
	COPY_type ( x223_ + 3, NULL_type ) ;\
	COPY_list ( x223_ + 4, NULL_list ( IDENTIFIER ) ) ;\
	COPY_exp ( x223_ + 5, NULL_exp ) ;\
	COPY_ulong ( x223_ + 6, 0 ) ;\
	( c_class_etype ) = x223_ ;\
    }

#define DECONS_etype_basic( name_, info_, rep_, form_, values_, value_, plus_, c_class_etype )\
    {\
	c_class *x224_ = ( c_class_etype ) ;\
	( name_ ) = DEREF_id ( x224_ + 0 ) ;\
	( info_ ) = DEREF_cinfo ( x224_ + 1 ) ;\
	( rep_ ) = DEREF_type ( x224_ + 2 ) ;\
	( form_ ) = DEREF_type ( x224_ + 3 ) ;\
	( values_ ) = DEREF_list ( x224_ + 4 ) ;\
	( value_ ) = DEREF_exp ( x224_ + 5 ) ;\
	( plus_ ) = DEREF_ulong ( x224_ + 6 ) ;\
    }

#define DESTROY_etype_basic( destroyer_, name_, info_, rep_, form_, values_, value_, plus_, c_class_etype )\
    {\
	c_class *x225_ = ( c_class_etype ) ;\
	( name_ ) = DEREF_id ( x225_ + 0 ) ;\
	( info_ ) = DEREF_cinfo ( x225_ + 1 ) ;\
	( rep_ ) = DEREF_type ( x225_ + 2 ) ;\
	( form_ ) = DEREF_type ( x225_ + 3 ) ;\
	( values_ ) = DEREF_list ( x225_ + 4 ) ;\
	( value_ ) = DEREF_exp ( x225_ + 5 ) ;\
	( plus_ ) = DEREF_ulong ( x225_ + 6 ) ;\
	( destroyer_ ) ( x225_, ( unsigned ) 7 ) ;\
    }


#endif
