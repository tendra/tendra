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
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.2)
*/

#ifndef TYPE_OPS_H_INCLUDED
#define TYPE_OPS_H_INCLUDED

/* Operations for union TYPE */

#define TAG_type( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for component size of union TYPE */

#define type_size( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for field primitive of union TYPE */

#define type_primitive_tag		( ( unsigned ) 0 )
#define IS_type_primitive( P )		( CHECK_NULL ( P )->ag_tag == 0 )

#define type_primitive_prim( P )	( CHECK_TAG ( ( P ), 0 ) + 2 )

#define MAKE_type_primitive( size_, prim_, calculus_type )\
    {\
	calculus *x136_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x136_->ag_tag = 0 ;\
	COPY_int ( x136_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x136_ + 2, ( prim_ ) ) ;\
	x136_ [3].ag_tag = 0 ;\
	( calculus_type ) = x136_ ;\
    }

#define DECONS_type_primitive( size_, prim_, calculus_type )\
    {\
	calculus *x137_ = CHECK_TAG ( ( calculus_type ), 0 ) ;\
	( size_ ) = DEREF_int ( x137_ + 1 ) ;\
	( prim_ ) = DEREF_ptr ( x137_ + 2 ) ;\
    }

#define DESTROY_type_primitive( destroyer_, size_, prim_, calculus_type )\
    {\
	calculus *x138_ = CHECK_TAG ( ( calculus_type ), 0 ) ;\
	( size_ ) = DEREF_int ( x138_ + 1 ) ;\
	( prim_ ) = DEREF_ptr ( x138_ + 2 ) ;\
	( destroyer_ ) ( x138_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_primitive( P, N )\
    {\
	calculus *x139_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a139_ = ( N ) ;\
	x139_->ag_tag = 0 ;\
	x139_ [3].ag_tag = a139_ ;\
	set_calculus_alias ( x139_ + 3, a139_ ) ;\
	( P ) = x139_ ;\
    }

#define GET_ALIAS_type_primitive( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_primitive( P, N )set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_primitive( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field ident of union TYPE */

#define type_ident_tag			( ( unsigned ) 1 )
#define IS_type_ident( P )		( CHECK_NULL ( P )->ag_tag == 1 )

#define type_ident_id( P )		( CHECK_TAG ( ( P ), 1 ) + 2 )

#define MAKE_type_ident( size_, id_, calculus_type )\
    {\
	calculus *x140_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x140_->ag_tag = 1 ;\
	COPY_int ( x140_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x140_ + 2, ( id_ ) ) ;\
	x140_ [3].ag_tag = 0 ;\
	( calculus_type ) = x140_ ;\
    }

#define DECONS_type_ident( size_, id_, calculus_type )\
    {\
	calculus *x141_ = CHECK_TAG ( ( calculus_type ), 1 ) ;\
	( size_ ) = DEREF_int ( x141_ + 1 ) ;\
	( id_ ) = DEREF_ptr ( x141_ + 2 ) ;\
    }

#define DESTROY_type_ident( destroyer_, size_, id_, calculus_type )\
    {\
	calculus *x142_ = CHECK_TAG ( ( calculus_type ), 1 ) ;\
	( size_ ) = DEREF_int ( x142_ + 1 ) ;\
	( id_ ) = DEREF_ptr ( x142_ + 2 ) ;\
	( destroyer_ ) ( x142_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_ident( P, N )\
    {\
	calculus *x143_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a143_ = ( N ) ;\
	x143_->ag_tag = 1 ;\
	x143_ [3].ag_tag = a143_ ;\
	set_calculus_alias ( x143_ + 3, a143_ ) ;\
	( P ) = x143_ ;\
    }

#define GET_ALIAS_type_ident( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_ident( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_ident( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field enumeration of union TYPE */

#define type_enumeration_tag		( ( unsigned ) 2 )
#define IS_type_enumeration( P )	( CHECK_NULL ( P )->ag_tag == 2 )

#define type_enumeration_en( P )	( CHECK_TAG ( ( P ), 2 ) + 2 )

#define MAKE_type_enumeration( size_, en_, calculus_type )\
    {\
	calculus *x144_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x144_->ag_tag = 2 ;\
	COPY_int ( x144_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x144_ + 2, ( en_ ) ) ;\
	x144_ [3].ag_tag = 0 ;\
	( calculus_type ) = x144_ ;\
    }

#define DECONS_type_enumeration( size_, en_, calculus_type )\
    {\
	calculus *x145_ = CHECK_TAG ( ( calculus_type ), 2 ) ;\
	( size_ ) = DEREF_int ( x145_ + 1 ) ;\
	( en_ ) = DEREF_ptr ( x145_ + 2 ) ;\
    }

#define DESTROY_type_enumeration( destroyer_, size_, en_, calculus_type )\
    {\
	calculus *x146_ = CHECK_TAG ( ( calculus_type ), 2 ) ;\
	( size_ ) = DEREF_int ( x146_ + 1 ) ;\
	( en_ ) = DEREF_ptr ( x146_ + 2 ) ;\
	( destroyer_ ) ( x146_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_enumeration( P, N )\
    {\
	calculus *x147_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a147_ = ( N ) ;\
	x147_->ag_tag = 2 ;\
	x147_ [3].ag_tag = a147_ ;\
	set_calculus_alias ( x147_ + 3, a147_ ) ;\
	( P ) = x147_ ;\
    }

#define GET_ALIAS_type_enumeration( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_enumeration( P, N )set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_enumeration( N )( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field structure of union TYPE */

#define type_structure_tag		( ( unsigned ) 3 )
#define IS_type_structure( P )		( CHECK_NULL ( P )->ag_tag == 3 )

#define type_structure_struc( P )	( CHECK_TAG ( ( P ), 3 ) + 2 )

#define MAKE_type_structure( size_, struc_, calculus_type )\
    {\
	calculus *x148_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x148_->ag_tag = 3 ;\
	COPY_int ( x148_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x148_ + 2, ( struc_ ) ) ;\
	x148_ [3].ag_tag = 0 ;\
	( calculus_type ) = x148_ ;\
    }

#define DECONS_type_structure( size_, struc_, calculus_type )\
    {\
	calculus *x149_ = CHECK_TAG ( ( calculus_type ), 3 ) ;\
	( size_ ) = DEREF_int ( x149_ + 1 ) ;\
	( struc_ ) = DEREF_ptr ( x149_ + 2 ) ;\
    }

#define DESTROY_type_structure( destroyer_, size_, struc_, calculus_type )\
    {\
	calculus *x150_ = CHECK_TAG ( ( calculus_type ), 3 ) ;\
	( size_ ) = DEREF_int ( x150_ + 1 ) ;\
	( struc_ ) = DEREF_ptr ( x150_ + 2 ) ;\
	( destroyer_ ) ( x150_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_structure( P, N )\
    {\
	calculus *x151_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a151_ = ( N ) ;\
	x151_->ag_tag = 3 ;\
	x151_ [3].ag_tag = a151_ ;\
	set_calculus_alias ( x151_ + 3, a151_ ) ;\
	( P ) = x151_ ;\
    }

#define GET_ALIAS_type_structure( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_structure( P, N )set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_structure( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field onion of union TYPE */

#define type_onion_tag			( ( unsigned ) 4 )
#define IS_type_onion( P )		( CHECK_NULL ( P )->ag_tag == 4 )

#define type_onion_un( P )		( CHECK_TAG ( ( P ), 4 ) + 2 )

#define MAKE_type_onion( size_, un_, calculus_type )\
    {\
	calculus *x152_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x152_->ag_tag = 4 ;\
	COPY_int ( x152_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x152_ + 2, ( un_ ) ) ;\
	x152_ [3].ag_tag = 0 ;\
	( calculus_type ) = x152_ ;\
    }

#define DECONS_type_onion( size_, un_, calculus_type )\
    {\
	calculus *x153_ = CHECK_TAG ( ( calculus_type ), 4 ) ;\
	( size_ ) = DEREF_int ( x153_ + 1 ) ;\
	( un_ ) = DEREF_ptr ( x153_ + 2 ) ;\
    }

#define DESTROY_type_onion( destroyer_, size_, un_, calculus_type )\
    {\
	calculus *x154_ = CHECK_TAG ( ( calculus_type ), 4 ) ;\
	( size_ ) = DEREF_int ( x154_ + 1 ) ;\
	( un_ ) = DEREF_ptr ( x154_ + 2 ) ;\
	( destroyer_ ) ( x154_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_onion( P, N )\
    {\
	calculus *x155_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a155_ = ( N ) ;\
	x155_->ag_tag = 4 ;\
	x155_ [3].ag_tag = a155_ ;\
	set_calculus_alias ( x155_ + 3, a155_ ) ;\
	( P ) = x155_ ;\
    }

#define GET_ALIAS_type_onion( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_onion( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_onion( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field set ptr_etc of union TYPE */

#define type_ptr_etc_tag		( ( unsigned ) 10 )
#define IS_type_ptr_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 5 ) < ( unsigned ) 5 )

#define type_ptr_etc_sub( P )		( CHECK_TAG_ETC ( ( P ), 5, 10 ) + 2 )

#define MAKE_type_ptr_etc( tag, size_, sub_, calculus_type )\
    {\
	calculus *x156_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x156_->ag_tag = ( tag ) ;\
	COPY_int ( x156_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x156_ + 2, ( sub_ ) ) ;\
	x156_ [3].ag_tag = 0 ;\
	( calculus_type ) = CHECK_TAG_ETC ( x156_, 5, 10 ) ;\
    }

#define MODIFY_type_ptr_etc( tag, calculus_type )\
    {\
	calculus *x157_ = CHECK_TAG_ETC ( ( calculus_type ), 5, 10 ) ;\
	x157_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x157_, 5, 10 ) ;\
    }

#define DECONS_type_ptr_etc( size_, sub_, calculus_type )\
    {\
	calculus *x158_ = CHECK_TAG_ETC ( ( calculus_type ), 5, 10 ) ;\
	( size_ ) = DEREF_int ( x158_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x158_ + 2 ) ;\
    }

#define DESTROY_type_ptr_etc( destroyer_, size_, sub_, calculus_type )\
    {\
	calculus *x159_ = CHECK_TAG_ETC ( ( calculus_type ), 5, 10 ) ;\
	( size_ ) = DEREF_int ( x159_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x159_ + 2 ) ;\
	( destroyer_ ) ( x159_, ( unsigned ) 4 ) ;\
    }


/* Operations for field ptr of union TYPE */

#define type_ptr_tag			( ( unsigned ) 5 )
#define IS_type_ptr( P )		( CHECK_NULL ( P )->ag_tag == 5 )

#define type_ptr_sub( P )		( CHECK_TAG ( ( P ), 5 ) + 2 )

#define MAKE_type_ptr( size_, sub_, calculus_type )\
    {\
	calculus *x160_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x160_->ag_tag = 5 ;\
	COPY_int ( x160_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x160_ + 2, ( sub_ ) ) ;\
	x160_ [3].ag_tag = 0 ;\
	( calculus_type ) = x160_ ;\
    }

#define DECONS_type_ptr( size_, sub_, calculus_type )\
    {\
	calculus *x161_ = CHECK_TAG ( ( calculus_type ), 5 ) ;\
	( size_ ) = DEREF_int ( x161_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x161_ + 2 ) ;\
    }

#define DESTROY_type_ptr( destroyer_, size_, sub_, calculus_type )\
    {\
	calculus *x162_ = CHECK_TAG ( ( calculus_type ), 5 ) ;\
	( size_ ) = DEREF_int ( x162_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x162_ + 2 ) ;\
	( destroyer_ ) ( x162_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_ptr( P, N )\
    {\
	calculus *x163_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a163_ = ( N ) ;\
	x163_->ag_tag = 5 ;\
	x163_ [3].ag_tag = a163_ ;\
	set_calculus_alias ( x163_ + 3, a163_ ) ;\
	( P ) = x163_ ;\
    }

#define GET_ALIAS_type_ptr( P )		( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_ptr( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_ptr( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field list of union TYPE */

#define type_list_tag			( ( unsigned ) 6 )
#define IS_type_list( P )		( CHECK_NULL ( P )->ag_tag == 6 )

#define type_list_sub( P )		( CHECK_TAG ( ( P ), 6 ) + 2 )

#define MAKE_type_list( size_, sub_, calculus_type )\
    {\
	calculus *x164_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x164_->ag_tag = 6 ;\
	COPY_int ( x164_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x164_ + 2, ( sub_ ) ) ;\
	x164_ [3].ag_tag = 0 ;\
	( calculus_type ) = x164_ ;\
    }

#define DECONS_type_list( size_, sub_, calculus_type )\
    {\
	calculus *x165_ = CHECK_TAG ( ( calculus_type ), 6 ) ;\
	( size_ ) = DEREF_int ( x165_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x165_ + 2 ) ;\
    }

#define DESTROY_type_list( destroyer_, size_, sub_, calculus_type )\
    {\
	calculus *x166_ = CHECK_TAG ( ( calculus_type ), 6 ) ;\
	( size_ ) = DEREF_int ( x166_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x166_ + 2 ) ;\
	( destroyer_ ) ( x166_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_list( P, N )\
    {\
	calculus *x167_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a167_ = ( N ) ;\
	x167_->ag_tag = 6 ;\
	x167_ [3].ag_tag = a167_ ;\
	set_calculus_alias ( x167_ + 3, a167_ ) ;\
	( P ) = x167_ ;\
    }

#define GET_ALIAS_type_list( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_list( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_list( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field stack of union TYPE */

#define type_stack_tag			( ( unsigned ) 7 )
#define IS_type_stack( P )		( CHECK_NULL ( P )->ag_tag == 7 )

#define type_stack_sub( P )		( CHECK_TAG ( ( P ), 7 ) + 2 )

#define MAKE_type_stack( size_, sub_, calculus_type )\
    {\
	calculus *x168_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x168_->ag_tag = 7 ;\
	COPY_int ( x168_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x168_ + 2, ( sub_ ) ) ;\
	x168_ [3].ag_tag = 0 ;\
	( calculus_type ) = x168_ ;\
    }

#define DECONS_type_stack( size_, sub_, calculus_type )\
    {\
	calculus *x169_ = CHECK_TAG ( ( calculus_type ), 7 ) ;\
	( size_ ) = DEREF_int ( x169_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x169_ + 2 ) ;\
    }

#define DESTROY_type_stack( destroyer_, size_, sub_, calculus_type )\
    {\
	calculus *x170_ = CHECK_TAG ( ( calculus_type ), 7 ) ;\
	( size_ ) = DEREF_int ( x170_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x170_ + 2 ) ;\
	( destroyer_ ) ( x170_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_stack( P, N )\
    {\
	calculus *x171_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a171_ = ( N ) ;\
	x171_->ag_tag = 7 ;\
	x171_ [3].ag_tag = a171_ ;\
	set_calculus_alias ( x171_ + 3, a171_ ) ;\
	( P ) = x171_ ;\
    }

#define GET_ALIAS_type_stack( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_stack( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_stack( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field vec of union TYPE */

#define type_vec_tag			( ( unsigned ) 8 )
#define IS_type_vec( P )		( CHECK_NULL ( P )->ag_tag == 8 )

#define type_vec_sub( P )		( CHECK_TAG ( ( P ), 8 ) + 2 )

#define MAKE_type_vec( size_, sub_, calculus_type )\
    {\
	calculus *x172_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x172_->ag_tag = 8 ;\
	COPY_int ( x172_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x172_ + 2, ( sub_ ) ) ;\
	x172_ [3].ag_tag = 0 ;\
	( calculus_type ) = x172_ ;\
    }

#define DECONS_type_vec( size_, sub_, calculus_type )\
    {\
	calculus *x173_ = CHECK_TAG ( ( calculus_type ), 8 ) ;\
	( size_ ) = DEREF_int ( x173_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x173_ + 2 ) ;\
    }

#define DESTROY_type_vec( destroyer_, size_, sub_, calculus_type )\
    {\
	calculus *x174_ = CHECK_TAG ( ( calculus_type ), 8 ) ;\
	( size_ ) = DEREF_int ( x174_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x174_ + 2 ) ;\
	( destroyer_ ) ( x174_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_vec( P, N )\
    {\
	calculus *x175_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a175_ = ( N ) ;\
	x175_->ag_tag = 8 ;\
	x175_ [3].ag_tag = a175_ ;\
	set_calculus_alias ( x175_ + 3, a175_ ) ;\
	( P ) = x175_ ;\
    }

#define GET_ALIAS_type_vec( P )		( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_vec( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_vec( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field vec_ptr of union TYPE */

#define type_vec_ptr_tag		( ( unsigned ) 9 )
#define IS_type_vec_ptr( P )		( CHECK_NULL ( P )->ag_tag == 9 )

#define type_vec_ptr_sub( P )		( CHECK_TAG ( ( P ), 9 ) + 2 )

#define MAKE_type_vec_ptr( size_, sub_, calculus_type )\
    {\
	calculus *x176_ = GEN_calculus ( 4, TYPEID_type ) ;\
	x176_->ag_tag = 9 ;\
	COPY_int ( x176_ + 1, ( size_ ) ) ;\
	COPY_ptr ( x176_ + 2, ( sub_ ) ) ;\
	x176_ [3].ag_tag = 0 ;\
	( calculus_type ) = x176_ ;\
    }

#define DECONS_type_vec_ptr( size_, sub_, calculus_type )\
    {\
	calculus *x177_ = CHECK_TAG ( ( calculus_type ), 9 ) ;\
	( size_ ) = DEREF_int ( x177_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x177_ + 2 ) ;\
    }

#define DESTROY_type_vec_ptr( destroyer_, size_, sub_, calculus_type )\
    {\
	calculus *x178_ = CHECK_TAG ( ( calculus_type ), 9 ) ;\
	( size_ ) = DEREF_int ( x178_ + 1 ) ;\
	( sub_ ) = DEREF_ptr ( x178_ + 2 ) ;\
	( destroyer_ ) ( x178_, ( unsigned ) 4 ) ;\
    }

#ifdef calculus_IO_ROUTINES

#define NEW_ALIAS_type_vec_ptr( P, N )\
    {\
	calculus *x179_ = GEN_calculus ( 4, TYPEID_list ) ;\
	unsigned a179_ = ( N ) ;\
	x179_->ag_tag = 9 ;\
	x179_ [3].ag_tag = a179_ ;\
	set_calculus_alias ( x179_ + 3, a179_ ) ;\
	( P ) = x179_ ;\
    }

#define GET_ALIAS_type_vec_ptr( P )	( ( CHECK_NULL ( P ) + 3 )->ag_tag )
#define SET_ALIAS_type_vec_ptr( P, N )	set_calculus_alias ( CHECK_NULL ( P ) + 3, ( N ) )
#define FIND_ALIAS_type_vec_ptr( N )	( find_calculus_alias ( N ) - 3 )

#endif


/* Operations for field quote of union TYPE */

#define type_quote_tag			( ( unsigned ) 10 )
#define IS_type_quote( P )		( CHECK_NULL ( P )->ag_tag == 10 )

#define type_quote_defn( P )		( CHECK_TAG ( ( P ), 10 ) + 2 )

#define MAKE_type_quote( size_, defn_, calculus_type )\
    {\
	calculus *x180_ = GEN_calculus ( 3, TYPEID_type ) ;\
	x180_->ag_tag = 10 ;\
	COPY_int ( x180_ + 1, ( size_ ) ) ;\
	COPY_string ( x180_ + 2, ( defn_ ) ) ;\
	( calculus_type ) = x180_ ;\
    }

#define DECONS_type_quote( size_, defn_, calculus_type )\
    {\
	calculus *x181_ = CHECK_TAG ( ( calculus_type ), 10 ) ;\
	( size_ ) = DEREF_int ( x181_ + 1 ) ;\
	( defn_ ) = DEREF_string ( x181_ + 2 ) ;\
    }

#define DESTROY_type_quote( destroyer_, size_, defn_, calculus_type )\
    {\
	calculus *x182_ = CHECK_TAG ( ( calculus_type ), 10 ) ;\
	( size_ ) = DEREF_int ( x182_ + 1 ) ;\
	( defn_ ) = DEREF_string ( x182_ + 2 ) ;\
	( destroyer_ ) ( x182_, ( unsigned ) 3 ) ;\
    }


/* Operations for field undef of union TYPE */

#define type_undef_tag			( ( unsigned ) 11 )
#define IS_type_undef( P )		( CHECK_NULL ( P )->ag_tag == 11 )

#define type_undef_name( P )		( CHECK_TAG ( ( P ), 11 ) + 2 )

#define MAKE_type_undef( size_, name_, calculus_type )\
    {\
	calculus *x183_ = GEN_calculus ( 3, TYPEID_type ) ;\
	x183_->ag_tag = 11 ;\
	COPY_int ( x183_ + 1, ( size_ ) ) ;\
	COPY_string ( x183_ + 2, ( name_ ) ) ;\
	( calculus_type ) = x183_ ;\
    }

#define DECONS_type_undef( size_, name_, calculus_type )\
    {\
	calculus *x184_ = CHECK_TAG ( ( calculus_type ), 11 ) ;\
	( size_ ) = DEREF_int ( x184_ + 1 ) ;\
	( name_ ) = DEREF_string ( x184_ + 2 ) ;\
    }

#define DESTROY_type_undef( destroyer_, size_, name_, calculus_type )\
    {\
	calculus *x185_ = CHECK_TAG ( ( calculus_type ), 11 ) ;\
	( size_ ) = DEREF_int ( x185_ + 1 ) ;\
	( name_ ) = DEREF_string ( x185_ + 2 ) ;\
	( destroyer_ ) ( x185_, ( unsigned ) 3 ) ;\
    }


#endif
