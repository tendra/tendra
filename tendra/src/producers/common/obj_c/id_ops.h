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

#ifndef ID_OPS_H_INCLUDED
#define ID_OPS_H_INCLUDED

/* Operations for union IDENTIFIER */

#define TAG_id( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for component name of union IDENTIFIER */

#define id_name( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component storage of union IDENTIFIER */

#define id_storage( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for component parent of union IDENTIFIER */

#define id_parent( P )			( CHECK_NULL ( P ) + 3 )


/* Operations for component loc of union IDENTIFIER */

#define id_loc( P )			( CHECK_NULL ( P ) + 4 )


/* Operations for component alias of union IDENTIFIER */

#define id_alias( P )			( CHECK_NULL ( P ) + 7 )


/* Operations for component no of union IDENTIFIER */

#define id_no( P )			( CHECK_NULL ( P ) + 8 )


/* Operations for component dump of union IDENTIFIER */

#define id_dump( P )			( CHECK_NULL ( P ) + 9 )


/* Operations for field dummy of union IDENTIFIER */

#define id_dummy_tag			( ( unsigned ) 0 )
#define IS_id_dummy( P )		( CHECK_NULL ( P )->ag_tag == 0 )


#define MAKE_id_dummy( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x317_ = GEN_c_class ( 10, TYPEID_id ) ;\
	x317_->ag_tag = 0 ;\
	COPY_hashid ( x317_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x317_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x317_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x317_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x317_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x317_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x317_ + 7, x317_ ) ;\
	COPY_ulong ( x317_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x317_ + 9, LINK_NONE ) ;\
	( c_class_id ) = x317_ ;\
    }

#define DECONS_id_dummy( name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x318_ = CHECK_TAG ( ( c_class_id ), 0 ) ;\
	( name_ ) = DEREF_hashid ( x318_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x318_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x318_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x318_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x318_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x318_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x318_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x318_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x318_ + 9 ) ;\
    }

#define DESTROY_id_dummy( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x319_ = CHECK_TAG ( ( c_class_id ), 0 ) ;\
	( name_ ) = DEREF_hashid ( x319_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x319_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x319_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x319_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x319_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x319_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x319_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x319_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x319_ + 9 ) ;\
	( destroyer_ ) ( x319_, ( unsigned ) 10 ) ;\
    }


/* Operations for field set keyword_etc of union IDENTIFIER */

#define id_keyword_etc_tag		( ( unsigned ) 4 )
#define IS_id_keyword_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 1 ) < ( unsigned ) 3 )


#define MAKE_id_keyword_etc( tag, name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x320_ = GEN_c_class ( 10, TYPEID_id ) ;\
	x320_->ag_tag = ( tag ) ;\
	COPY_hashid ( x320_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x320_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x320_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x320_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x320_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x320_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x320_ + 7, x320_ ) ;\
	COPY_ulong ( x320_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x320_ + 9, LINK_NONE ) ;\
	( c_class_id ) = CHECK_TAG_ETC ( x320_, 1, 4 ) ;\
    }

#define MODIFY_id_keyword_etc( tag, c_class_id )\
    {\
	c_class *x321_ = CHECK_TAG_ETC ( ( c_class_id ), 1, 4 ) ;\
	x321_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x321_, 1, 4 ) ;\
    }

#define DECONS_id_keyword_etc( name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x322_ = CHECK_TAG_ETC ( ( c_class_id ), 1, 4 ) ;\
	( name_ ) = DEREF_hashid ( x322_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x322_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x322_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x322_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x322_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x322_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x322_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x322_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x322_ + 9 ) ;\
    }

#define DESTROY_id_keyword_etc( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x323_ = CHECK_TAG_ETC ( ( c_class_id ), 1, 4 ) ;\
	( name_ ) = DEREF_hashid ( x323_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x323_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x323_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x323_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x323_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x323_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x323_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x323_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x323_ + 9 ) ;\
	( destroyer_ ) ( x323_, ( unsigned ) 10 ) ;\
    }


/* Operations for field keyword of union IDENTIFIER */

#define id_keyword_tag			( ( unsigned ) 1 )
#define IS_id_keyword( P )		( CHECK_NULL ( P )->ag_tag == 1 )


#define MAKE_id_keyword( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x324_ = GEN_c_class ( 10, TYPEID_id ) ;\
	x324_->ag_tag = 1 ;\
	COPY_hashid ( x324_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x324_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x324_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x324_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x324_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x324_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x324_ + 7, x324_ ) ;\
	COPY_ulong ( x324_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x324_ + 9, LINK_NONE ) ;\
	( c_class_id ) = x324_ ;\
    }

#define DECONS_id_keyword( name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x325_ = CHECK_TAG ( ( c_class_id ), 1 ) ;\
	( name_ ) = DEREF_hashid ( x325_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x325_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x325_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x325_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x325_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x325_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x325_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x325_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x325_ + 9 ) ;\
    }

#define DESTROY_id_keyword( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x326_ = CHECK_TAG ( ( c_class_id ), 1 ) ;\
	( name_ ) = DEREF_hashid ( x326_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x326_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x326_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x326_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x326_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x326_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x326_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x326_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x326_ + 9 ) ;\
	( destroyer_ ) ( x326_, ( unsigned ) 10 ) ;\
    }


/* Operations for field iso_keyword of union IDENTIFIER */

#define id_iso_keyword_tag		( ( unsigned ) 2 )
#define IS_id_iso_keyword( P )		( CHECK_NULL ( P )->ag_tag == 2 )


#define MAKE_id_iso_keyword( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x327_ = GEN_c_class ( 10, TYPEID_id ) ;\
	x327_->ag_tag = 2 ;\
	COPY_hashid ( x327_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x327_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x327_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x327_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x327_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x327_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x327_ + 7, x327_ ) ;\
	COPY_ulong ( x327_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x327_ + 9, LINK_NONE ) ;\
	( c_class_id ) = x327_ ;\
    }

#define DECONS_id_iso_keyword( name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x328_ = CHECK_TAG ( ( c_class_id ), 2 ) ;\
	( name_ ) = DEREF_hashid ( x328_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x328_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x328_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x328_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x328_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x328_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x328_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x328_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x328_ + 9 ) ;\
    }

#define DESTROY_id_iso_keyword( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x329_ = CHECK_TAG ( ( c_class_id ), 2 ) ;\
	( name_ ) = DEREF_hashid ( x329_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x329_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x329_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x329_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x329_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x329_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x329_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x329_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x329_ + 9 ) ;\
	( destroyer_ ) ( x329_, ( unsigned ) 10 ) ;\
    }


/* Operations for field reserved of union IDENTIFIER */

#define id_reserved_tag			( ( unsigned ) 3 )
#define IS_id_reserved( P )		( CHECK_NULL ( P )->ag_tag == 3 )


#define MAKE_id_reserved( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x330_ = GEN_c_class ( 10, TYPEID_id ) ;\
	x330_->ag_tag = 3 ;\
	COPY_hashid ( x330_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x330_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x330_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x330_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x330_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x330_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x330_ + 7, x330_ ) ;\
	COPY_ulong ( x330_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x330_ + 9, LINK_NONE ) ;\
	( c_class_id ) = x330_ ;\
    }

#define DECONS_id_reserved( name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x331_ = CHECK_TAG ( ( c_class_id ), 3 ) ;\
	( name_ ) = DEREF_hashid ( x331_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x331_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x331_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x331_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x331_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x331_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x331_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x331_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x331_ + 9 ) ;\
    }

#define DESTROY_id_reserved( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x332_ = CHECK_TAG ( ( c_class_id ), 3 ) ;\
	( name_ ) = DEREF_hashid ( x332_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x332_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x332_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x332_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x332_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x332_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x332_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x332_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x332_ + 9 ) ;\
	( destroyer_ ) ( x332_, ( unsigned ) 10 ) ;\
    }


/* Operations for field builtin of union IDENTIFIER */

#define id_builtin_tag			( ( unsigned ) 4 )
#define IS_id_builtin( P )		( CHECK_NULL ( P )->ag_tag == 4 )

#define id_builtin_ret( P )		( CHECK_TAG ( ( P ), 4 ) + 10 )
#define id_builtin_ptypes( P )		( CHECK_TAG ( ( P ), 4 ) + 11 )

#define MAKE_id_builtin( name_, storage_, parent_, loc_, ret_, ptypes_, c_class_id )\
    {\
	c_class *x333_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x333_->ag_tag = 4 ;\
	COPY_hashid ( x333_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x333_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x333_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x333_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x333_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x333_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x333_ + 7, x333_ ) ;\
	COPY_ulong ( x333_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x333_ + 9, LINK_NONE ) ;\
	COPY_type ( x333_ + 10, ( ret_ ) ) ;\
	COPY_list ( x333_ + 11, ( ptypes_ ) ) ;\
	( c_class_id ) = x333_ ;\
    }

#define DECONS_id_builtin( name_, storage_, parent_, loc_, alias_, no_, dump_, ret_, ptypes_, c_class_id )\
    {\
	c_class *x334_ = CHECK_TAG ( ( c_class_id ), 4 ) ;\
	( name_ ) = DEREF_hashid ( x334_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x334_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x334_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x334_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x334_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x334_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x334_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x334_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x334_ + 9 ) ;\
	( ret_ ) = DEREF_type ( x334_ + 10 ) ;\
	( ptypes_ ) = DEREF_list ( x334_ + 11 ) ;\
    }

#define DESTROY_id_builtin( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, ret_, ptypes_, c_class_id )\
    {\
	c_class *x335_ = CHECK_TAG ( ( c_class_id ), 4 ) ;\
	( name_ ) = DEREF_hashid ( x335_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x335_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x335_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x335_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x335_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x335_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x335_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x335_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x335_ + 9 ) ;\
	( ret_ ) = DEREF_type ( x335_ + 10 ) ;\
	( ptypes_ ) = DEREF_list ( x335_ + 11 ) ;\
	( destroyer_ ) ( x335_, ( unsigned ) 12 ) ;\
    }


/* Operations for field obj_macro of union IDENTIFIER */

#define id_obj_macro_tag		( ( unsigned ) 5 )
#define IS_id_obj_macro( P )		( CHECK_NULL ( P )->ag_tag == 5 )

#define id_obj_macro_defn( P )		( CHECK_TAG ( ( P ), 5 ) + 10 )

#define MAKE_id_obj_macro( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x336_ = GEN_c_class ( 11, TYPEID_id ) ;\
	x336_->ag_tag = 5 ;\
	COPY_hashid ( x336_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x336_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x336_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x336_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x336_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x336_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x336_ + 7, x336_ ) ;\
	COPY_ulong ( x336_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x336_ + 9, LINK_NONE ) ;\
	COPY_pptok ( x336_ + 10, ( defn_ ) ) ;\
	( c_class_id ) = x336_ ;\
    }

#define DECONS_id_obj_macro( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x337_ = CHECK_TAG ( ( c_class_id ), 5 ) ;\
	( name_ ) = DEREF_hashid ( x337_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x337_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x337_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x337_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x337_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x337_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x337_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x337_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x337_ + 9 ) ;\
	( defn_ ) = DEREF_pptok ( x337_ + 10 ) ;\
    }

#define DESTROY_id_obj_macro( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x338_ = CHECK_TAG ( ( c_class_id ), 5 ) ;\
	( name_ ) = DEREF_hashid ( x338_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x338_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x338_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x338_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x338_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x338_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x338_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x338_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x338_ + 9 ) ;\
	( defn_ ) = DEREF_pptok ( x338_ + 10 ) ;\
	( destroyer_ ) ( x338_, ( unsigned ) 11 ) ;\
    }


/* Operations for field func_macro of union IDENTIFIER */

#define id_func_macro_tag		( ( unsigned ) 6 )
#define IS_id_func_macro( P )		( CHECK_NULL ( P )->ag_tag == 6 )

#define id_func_macro_defn( P )		( CHECK_TAG ( ( P ), 6 ) + 10 )
#define id_func_macro_params( P )	( CHECK_TAG ( ( P ), 6 ) + 11 )
#define id_func_macro_no_params( P )	( CHECK_TAG ( ( P ), 6 ) + 12 )

#define MAKE_id_func_macro( name_, storage_, parent_, loc_, defn_, params_, no_params_, c_class_id )\
    {\
	c_class *x339_ = GEN_c_class ( 13, TYPEID_id ) ;\
	x339_->ag_tag = 6 ;\
	COPY_hashid ( x339_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x339_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x339_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x339_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x339_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x339_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x339_ + 7, x339_ ) ;\
	COPY_ulong ( x339_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x339_ + 9, LINK_NONE ) ;\
	COPY_pptok ( x339_ + 10, ( defn_ ) ) ;\
	COPY_list ( x339_ + 11, ( params_ ) ) ;\
	COPY_unsigned ( x339_ + 12, ( no_params_ ) ) ;\
	( c_class_id ) = x339_ ;\
    }

#define DECONS_id_func_macro( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, params_, no_params_, c_class_id )\
    {\
	c_class *x340_ = CHECK_TAG ( ( c_class_id ), 6 ) ;\
	( name_ ) = DEREF_hashid ( x340_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x340_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x340_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x340_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x340_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x340_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x340_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x340_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x340_ + 9 ) ;\
	( defn_ ) = DEREF_pptok ( x340_ + 10 ) ;\
	( params_ ) = DEREF_list ( x340_ + 11 ) ;\
	( no_params_ ) = DEREF_unsigned ( x340_ + 12 ) ;\
    }

#define DESTROY_id_func_macro( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, params_, no_params_, c_class_id )\
    {\
	c_class *x341_ = CHECK_TAG ( ( c_class_id ), 6 ) ;\
	( name_ ) = DEREF_hashid ( x341_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x341_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x341_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x341_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x341_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x341_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x341_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x341_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x341_ + 9 ) ;\
	( defn_ ) = DEREF_pptok ( x341_ + 10 ) ;\
	( params_ ) = DEREF_list ( x341_ + 11 ) ;\
	( no_params_ ) = DEREF_unsigned ( x341_ + 12 ) ;\
	( destroyer_ ) ( x341_, ( unsigned ) 13 ) ;\
    }


/* Operations for field predicate of union IDENTIFIER */

#define id_predicate_tag		( ( unsigned ) 7 )
#define IS_id_predicate( P )		( CHECK_NULL ( P )->ag_tag == 7 )

#define id_predicate_values( P )	( CHECK_TAG ( ( P ), 7 ) + 10 )

#define MAKE_id_predicate( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x342_ = GEN_c_class ( 11, TYPEID_id ) ;\
	x342_->ag_tag = 7 ;\
	COPY_hashid ( x342_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x342_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x342_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x342_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x342_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x342_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x342_ + 7, x342_ ) ;\
	COPY_ulong ( x342_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x342_ + 9, LINK_NONE ) ;\
	COPY_list ( x342_ + 10, NULL_list ( PPTOKEN_P ) ) ;\
	( c_class_id ) = x342_ ;\
    }

#define DECONS_id_predicate( name_, storage_, parent_, loc_, alias_, no_, dump_, values_, c_class_id )\
    {\
	c_class *x343_ = CHECK_TAG ( ( c_class_id ), 7 ) ;\
	( name_ ) = DEREF_hashid ( x343_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x343_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x343_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x343_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x343_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x343_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x343_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x343_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x343_ + 9 ) ;\
	( values_ ) = DEREF_list ( x343_ + 10 ) ;\
    }

#define DESTROY_id_predicate( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, values_, c_class_id )\
    {\
	c_class *x344_ = CHECK_TAG ( ( c_class_id ), 7 ) ;\
	( name_ ) = DEREF_hashid ( x344_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x344_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x344_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x344_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x344_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x344_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x344_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x344_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x344_ + 9 ) ;\
	( values_ ) = DEREF_list ( x344_ + 10 ) ;\
	( destroyer_ ) ( x344_, ( unsigned ) 11 ) ;\
    }


/* Operations for field set class_name_etc of union IDENTIFIER */

#define id_class_name_etc_tag		( ( unsigned ) 13 )
#define IS_id_class_name_etc( P )	( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 8 ) < ( unsigned ) 5 )

#define id_class_name_etc_defn( P )	( CHECK_TAG_ETC ( ( P ), 8, 13 ) + 10 )
#define id_class_name_etc_rep( P )	( CHECK_TAG_ETC ( ( P ), 8, 13 ) + 11 )

#define MAKE_id_class_name_etc( tag, name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x345_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x345_->ag_tag = ( tag ) ;\
	COPY_hashid ( x345_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x345_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x345_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x345_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x345_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x345_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x345_ + 7, x345_ ) ;\
	COPY_ulong ( x345_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x345_ + 9, LINK_NONE ) ;\
	COPY_type ( x345_ + 10, ( defn_ ) ) ;\
	COPY_btype ( x345_ + 11, btype_none ) ;\
	( c_class_id ) = CHECK_TAG_ETC ( x345_, 8, 13 ) ;\
    }

#define MODIFY_id_class_name_etc( tag, c_class_id )\
    {\
	c_class *x346_ = CHECK_TAG_ETC ( ( c_class_id ), 8, 13 ) ;\
	x346_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x346_, 8, 13 ) ;\
    }

#define DECONS_id_class_name_etc( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x347_ = CHECK_TAG_ETC ( ( c_class_id ), 8, 13 ) ;\
	( name_ ) = DEREF_hashid ( x347_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x347_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x347_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x347_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x347_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x347_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x347_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x347_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x347_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x347_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x347_ + 11 ) ;\
    }

#define DESTROY_id_class_name_etc( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x348_ = CHECK_TAG_ETC ( ( c_class_id ), 8, 13 ) ;\
	( name_ ) = DEREF_hashid ( x348_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x348_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x348_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x348_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x348_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x348_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x348_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x348_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x348_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x348_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x348_ + 11 ) ;\
	( destroyer_ ) ( x348_, ( unsigned ) 12 ) ;\
    }


/* Operations for field class_name of union IDENTIFIER */

#define id_class_name_tag		( ( unsigned ) 8 )
#define IS_id_class_name( P )		( CHECK_NULL ( P )->ag_tag == 8 )

#define id_class_name_defn( P )		( CHECK_TAG ( ( P ), 8 ) + 10 )
#define id_class_name_rep( P )		( CHECK_TAG ( ( P ), 8 ) + 11 )

#define MAKE_id_class_name( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x349_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x349_->ag_tag = 8 ;\
	COPY_hashid ( x349_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x349_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x349_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x349_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x349_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x349_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x349_ + 7, x349_ ) ;\
	COPY_ulong ( x349_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x349_ + 9, LINK_NONE ) ;\
	COPY_type ( x349_ + 10, ( defn_ ) ) ;\
	COPY_btype ( x349_ + 11, btype_none ) ;\
	( c_class_id ) = x349_ ;\
    }

#define DECONS_id_class_name( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x350_ = CHECK_TAG ( ( c_class_id ), 8 ) ;\
	( name_ ) = DEREF_hashid ( x350_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x350_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x350_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x350_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x350_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x350_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x350_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x350_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x350_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x350_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x350_ + 11 ) ;\
    }

#define DESTROY_id_class_name( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x351_ = CHECK_TAG ( ( c_class_id ), 8 ) ;\
	( name_ ) = DEREF_hashid ( x351_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x351_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x351_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x351_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x351_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x351_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x351_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x351_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x351_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x351_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x351_ + 11 ) ;\
	( destroyer_ ) ( x351_, ( unsigned ) 12 ) ;\
    }


/* Operations for field enum_name of union IDENTIFIER */

#define id_enum_name_tag		( ( unsigned ) 9 )
#define IS_id_enum_name( P )		( CHECK_NULL ( P )->ag_tag == 9 )

#define id_enum_name_defn( P )		( CHECK_TAG ( ( P ), 9 ) + 10 )
#define id_enum_name_rep( P )		( CHECK_TAG ( ( P ), 9 ) + 11 )

#define MAKE_id_enum_name( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x352_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x352_->ag_tag = 9 ;\
	COPY_hashid ( x352_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x352_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x352_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x352_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x352_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x352_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x352_ + 7, x352_ ) ;\
	COPY_ulong ( x352_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x352_ + 9, LINK_NONE ) ;\
	COPY_type ( x352_ + 10, ( defn_ ) ) ;\
	COPY_btype ( x352_ + 11, btype_none ) ;\
	( c_class_id ) = x352_ ;\
    }

#define DECONS_id_enum_name( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x353_ = CHECK_TAG ( ( c_class_id ), 9 ) ;\
	( name_ ) = DEREF_hashid ( x353_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x353_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x353_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x353_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x353_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x353_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x353_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x353_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x353_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x353_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x353_ + 11 ) ;\
    }

#define DESTROY_id_enum_name( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x354_ = CHECK_TAG ( ( c_class_id ), 9 ) ;\
	( name_ ) = DEREF_hashid ( x354_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x354_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x354_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x354_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x354_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x354_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x354_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x354_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x354_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x354_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x354_ + 11 ) ;\
	( destroyer_ ) ( x354_, ( unsigned ) 12 ) ;\
    }


/* Operations for field class_alias of union IDENTIFIER */

#define id_class_alias_tag		( ( unsigned ) 10 )
#define IS_id_class_alias( P )		( CHECK_NULL ( P )->ag_tag == 10 )

#define id_class_alias_defn( P )	( CHECK_TAG ( ( P ), 10 ) + 10 )
#define id_class_alias_rep( P )		( CHECK_TAG ( ( P ), 10 ) + 11 )

#define MAKE_id_class_alias( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x355_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x355_->ag_tag = 10 ;\
	COPY_hashid ( x355_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x355_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x355_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x355_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x355_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x355_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x355_ + 7, x355_ ) ;\
	COPY_ulong ( x355_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x355_ + 9, LINK_NONE ) ;\
	COPY_type ( x355_ + 10, ( defn_ ) ) ;\
	COPY_btype ( x355_ + 11, btype_none ) ;\
	( c_class_id ) = x355_ ;\
    }

#define DECONS_id_class_alias( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x356_ = CHECK_TAG ( ( c_class_id ), 10 ) ;\
	( name_ ) = DEREF_hashid ( x356_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x356_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x356_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x356_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x356_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x356_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x356_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x356_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x356_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x356_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x356_ + 11 ) ;\
    }

#define DESTROY_id_class_alias( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x357_ = CHECK_TAG ( ( c_class_id ), 10 ) ;\
	( name_ ) = DEREF_hashid ( x357_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x357_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x357_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x357_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x357_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x357_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x357_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x357_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x357_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x357_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x357_ + 11 ) ;\
	( destroyer_ ) ( x357_, ( unsigned ) 12 ) ;\
    }


/* Operations for field enum_alias of union IDENTIFIER */

#define id_enum_alias_tag		( ( unsigned ) 11 )
#define IS_id_enum_alias( P )		( CHECK_NULL ( P )->ag_tag == 11 )

#define id_enum_alias_defn( P )		( CHECK_TAG ( ( P ), 11 ) + 10 )
#define id_enum_alias_rep( P )		( CHECK_TAG ( ( P ), 11 ) + 11 )

#define MAKE_id_enum_alias( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x358_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x358_->ag_tag = 11 ;\
	COPY_hashid ( x358_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x358_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x358_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x358_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x358_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x358_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x358_ + 7, x358_ ) ;\
	COPY_ulong ( x358_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x358_ + 9, LINK_NONE ) ;\
	COPY_type ( x358_ + 10, ( defn_ ) ) ;\
	COPY_btype ( x358_ + 11, btype_none ) ;\
	( c_class_id ) = x358_ ;\
    }

#define DECONS_id_enum_alias( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x359_ = CHECK_TAG ( ( c_class_id ), 11 ) ;\
	( name_ ) = DEREF_hashid ( x359_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x359_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x359_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x359_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x359_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x359_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x359_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x359_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x359_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x359_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x359_ + 11 ) ;\
    }

#define DESTROY_id_enum_alias( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x360_ = CHECK_TAG ( ( c_class_id ), 11 ) ;\
	( name_ ) = DEREF_hashid ( x360_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x360_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x360_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x360_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x360_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x360_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x360_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x360_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x360_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x360_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x360_ + 11 ) ;\
	( destroyer_ ) ( x360_, ( unsigned ) 12 ) ;\
    }


/* Operations for field type_alias of union IDENTIFIER */

#define id_type_alias_tag		( ( unsigned ) 12 )
#define IS_id_type_alias( P )		( CHECK_NULL ( P )->ag_tag == 12 )

#define id_type_alias_defn( P )		( CHECK_TAG ( ( P ), 12 ) + 10 )
#define id_type_alias_rep( P )		( CHECK_TAG ( ( P ), 12 ) + 11 )

#define MAKE_id_type_alias( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x361_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x361_->ag_tag = 12 ;\
	COPY_hashid ( x361_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x361_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x361_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x361_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x361_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x361_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x361_ + 7, x361_ ) ;\
	COPY_ulong ( x361_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x361_ + 9, LINK_NONE ) ;\
	COPY_type ( x361_ + 10, ( defn_ ) ) ;\
	COPY_btype ( x361_ + 11, btype_none ) ;\
	( c_class_id ) = x361_ ;\
    }

#define DECONS_id_type_alias( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x362_ = CHECK_TAG ( ( c_class_id ), 12 ) ;\
	( name_ ) = DEREF_hashid ( x362_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x362_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x362_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x362_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x362_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x362_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x362_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x362_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x362_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x362_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x362_ + 11 ) ;\
    }

#define DESTROY_id_type_alias( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, rep_, c_class_id )\
    {\
	c_class *x363_ = CHECK_TAG ( ( c_class_id ), 12 ) ;\
	( name_ ) = DEREF_hashid ( x363_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x363_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x363_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x363_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x363_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x363_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x363_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x363_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x363_ + 9 ) ;\
	( defn_ ) = DEREF_type ( x363_ + 10 ) ;\
	( rep_ ) = DEREF_btype ( x363_ + 11 ) ;\
	( destroyer_ ) ( x363_, ( unsigned ) 12 ) ;\
    }


/* Operations for field set nspace_name_etc of union IDENTIFIER */

#define id_nspace_name_etc_tag		( ( unsigned ) 15 )
#define IS_id_nspace_name_etc( P )	( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 13 ) < ( unsigned ) 2 )

#define id_nspace_name_etc_defn( P )	( CHECK_TAG_ETC ( ( P ), 13, 15 ) + 10 )

#define MAKE_id_nspace_name_etc( tag, name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x364_ = GEN_c_class ( 11, TYPEID_id ) ;\
	x364_->ag_tag = ( tag ) ;\
	COPY_hashid ( x364_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x364_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x364_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x364_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x364_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x364_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x364_ + 7, x364_ ) ;\
	COPY_ulong ( x364_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x364_ + 9, LINK_NONE ) ;\
	COPY_nspace ( x364_ + 10, ( defn_ ) ) ;\
	( c_class_id ) = CHECK_TAG_ETC ( x364_, 13, 15 ) ;\
    }

#define MODIFY_id_nspace_name_etc( tag, c_class_id )\
    {\
	c_class *x365_ = CHECK_TAG_ETC ( ( c_class_id ), 13, 15 ) ;\
	x365_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x365_, 13, 15 ) ;\
    }

#define DECONS_id_nspace_name_etc( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x366_ = CHECK_TAG_ETC ( ( c_class_id ), 13, 15 ) ;\
	( name_ ) = DEREF_hashid ( x366_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x366_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x366_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x366_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x366_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x366_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x366_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x366_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x366_ + 9 ) ;\
	( defn_ ) = DEREF_nspace ( x366_ + 10 ) ;\
    }

#define DESTROY_id_nspace_name_etc( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x367_ = CHECK_TAG_ETC ( ( c_class_id ), 13, 15 ) ;\
	( name_ ) = DEREF_hashid ( x367_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x367_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x367_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x367_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x367_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x367_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x367_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x367_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x367_ + 9 ) ;\
	( defn_ ) = DEREF_nspace ( x367_ + 10 ) ;\
	( destroyer_ ) ( x367_, ( unsigned ) 11 ) ;\
    }


/* Operations for field nspace_name of union IDENTIFIER */

#define id_nspace_name_tag		( ( unsigned ) 13 )
#define IS_id_nspace_name( P )		( CHECK_NULL ( P )->ag_tag == 13 )

#define id_nspace_name_defn( P )	( CHECK_TAG ( ( P ), 13 ) + 10 )

#define MAKE_id_nspace_name( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x368_ = GEN_c_class ( 11, TYPEID_id ) ;\
	x368_->ag_tag = 13 ;\
	COPY_hashid ( x368_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x368_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x368_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x368_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x368_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x368_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x368_ + 7, x368_ ) ;\
	COPY_ulong ( x368_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x368_ + 9, LINK_NONE ) ;\
	COPY_nspace ( x368_ + 10, ( defn_ ) ) ;\
	( c_class_id ) = x368_ ;\
    }

#define DECONS_id_nspace_name( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x369_ = CHECK_TAG ( ( c_class_id ), 13 ) ;\
	( name_ ) = DEREF_hashid ( x369_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x369_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x369_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x369_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x369_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x369_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x369_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x369_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x369_ + 9 ) ;\
	( defn_ ) = DEREF_nspace ( x369_ + 10 ) ;\
    }

#define DESTROY_id_nspace_name( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x370_ = CHECK_TAG ( ( c_class_id ), 13 ) ;\
	( name_ ) = DEREF_hashid ( x370_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x370_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x370_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x370_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x370_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x370_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x370_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x370_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x370_ + 9 ) ;\
	( defn_ ) = DEREF_nspace ( x370_ + 10 ) ;\
	( destroyer_ ) ( x370_, ( unsigned ) 11 ) ;\
    }


/* Operations for field nspace_alias of union IDENTIFIER */

#define id_nspace_alias_tag		( ( unsigned ) 14 )
#define IS_id_nspace_alias( P )		( CHECK_NULL ( P )->ag_tag == 14 )

#define id_nspace_alias_defn( P )	( CHECK_TAG ( ( P ), 14 ) + 10 )

#define MAKE_id_nspace_alias( name_, storage_, parent_, loc_, defn_, c_class_id )\
    {\
	c_class *x371_ = GEN_c_class ( 11, TYPEID_id ) ;\
	x371_->ag_tag = 14 ;\
	COPY_hashid ( x371_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x371_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x371_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x371_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x371_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x371_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x371_ + 7, x371_ ) ;\
	COPY_ulong ( x371_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x371_ + 9, LINK_NONE ) ;\
	COPY_nspace ( x371_ + 10, ( defn_ ) ) ;\
	( c_class_id ) = x371_ ;\
    }

#define DECONS_id_nspace_alias( name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x372_ = CHECK_TAG ( ( c_class_id ), 14 ) ;\
	( name_ ) = DEREF_hashid ( x372_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x372_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x372_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x372_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x372_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x372_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x372_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x372_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x372_ + 9 ) ;\
	( defn_ ) = DEREF_nspace ( x372_ + 10 ) ;\
    }

#define DESTROY_id_nspace_alias( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, defn_, c_class_id )\
    {\
	c_class *x373_ = CHECK_TAG ( ( c_class_id ), 14 ) ;\
	( name_ ) = DEREF_hashid ( x373_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x373_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x373_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x373_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x373_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x373_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x373_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x373_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x373_ + 9 ) ;\
	( defn_ ) = DEREF_nspace ( x373_ + 10 ) ;\
	( destroyer_ ) ( x373_, ( unsigned ) 11 ) ;\
    }


/* Operations for field set variable_etc of union IDENTIFIER */

#define id_variable_etc_tag		( ( unsigned ) 18 )
#define IS_id_variable_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 15 ) < ( unsigned ) 3 )

#define id_variable_etc_type( P )	( CHECK_TAG_ETC ( ( P ), 15, 18 ) + 10 )
#define id_variable_etc_init( P )	( CHECK_TAG_ETC ( ( P ), 15, 18 ) + 11 )
#define id_variable_etc_term( P )	( CHECK_TAG_ETC ( ( P ), 15, 18 ) + 12 )

#define MAKE_id_variable_etc( tag, name_, storage_, parent_, loc_, type_, c_class_id )\
    {\
	c_class *x374_ = GEN_c_class ( 13, TYPEID_id ) ;\
	x374_->ag_tag = ( tag ) ;\
	COPY_hashid ( x374_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x374_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x374_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x374_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x374_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x374_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x374_ + 7, x374_ ) ;\
	COPY_ulong ( x374_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x374_ + 9, LINK_NONE ) ;\
	COPY_type ( x374_ + 10, ( type_ ) ) ;\
	COPY_exp ( x374_ + 11, NULL_exp ) ;\
	COPY_exp ( x374_ + 12, NULL_exp ) ;\
	( c_class_id ) = CHECK_TAG_ETC ( x374_, 15, 18 ) ;\
    }

#define MODIFY_id_variable_etc( tag, c_class_id )\
    {\
	c_class *x375_ = CHECK_TAG_ETC ( ( c_class_id ), 15, 18 ) ;\
	x375_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x375_, 15, 18 ) ;\
    }

#define DECONS_id_variable_etc( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x376_ = CHECK_TAG_ETC ( ( c_class_id ), 15, 18 ) ;\
	( name_ ) = DEREF_hashid ( x376_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x376_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x376_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x376_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x376_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x376_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x376_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x376_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x376_ + 9 ) ;\
	( type_ ) = DEREF_type ( x376_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x376_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x376_ + 12 ) ;\
    }

#define DESTROY_id_variable_etc( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x377_ = CHECK_TAG_ETC ( ( c_class_id ), 15, 18 ) ;\
	( name_ ) = DEREF_hashid ( x377_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x377_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x377_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x377_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x377_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x377_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x377_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x377_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x377_ + 9 ) ;\
	( type_ ) = DEREF_type ( x377_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x377_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x377_ + 12 ) ;\
	( destroyer_ ) ( x377_, ( unsigned ) 13 ) ;\
    }


/* Operations for field variable of union IDENTIFIER */

#define id_variable_tag			( ( unsigned ) 15 )
#define IS_id_variable( P )		( CHECK_NULL ( P )->ag_tag == 15 )

#define id_variable_type( P )		( CHECK_TAG ( ( P ), 15 ) + 10 )
#define id_variable_init( P )		( CHECK_TAG ( ( P ), 15 ) + 11 )
#define id_variable_term( P )		( CHECK_TAG ( ( P ), 15 ) + 12 )

#define MAKE_id_variable( name_, storage_, parent_, loc_, type_, c_class_id )\
    {\
	c_class *x378_ = GEN_c_class ( 13, TYPEID_id ) ;\
	x378_->ag_tag = 15 ;\
	COPY_hashid ( x378_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x378_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x378_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x378_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x378_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x378_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x378_ + 7, x378_ ) ;\
	COPY_ulong ( x378_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x378_ + 9, LINK_NONE ) ;\
	COPY_type ( x378_ + 10, ( type_ ) ) ;\
	COPY_exp ( x378_ + 11, NULL_exp ) ;\
	COPY_exp ( x378_ + 12, NULL_exp ) ;\
	( c_class_id ) = x378_ ;\
    }

#define DECONS_id_variable( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x379_ = CHECK_TAG ( ( c_class_id ), 15 ) ;\
	( name_ ) = DEREF_hashid ( x379_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x379_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x379_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x379_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x379_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x379_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x379_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x379_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x379_ + 9 ) ;\
	( type_ ) = DEREF_type ( x379_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x379_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x379_ + 12 ) ;\
    }

#define DESTROY_id_variable( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x380_ = CHECK_TAG ( ( c_class_id ), 15 ) ;\
	( name_ ) = DEREF_hashid ( x380_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x380_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x380_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x380_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x380_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x380_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x380_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x380_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x380_ + 9 ) ;\
	( type_ ) = DEREF_type ( x380_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x380_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x380_ + 12 ) ;\
	( destroyer_ ) ( x380_, ( unsigned ) 13 ) ;\
    }


/* Operations for field parameter of union IDENTIFIER */

#define id_parameter_tag		( ( unsigned ) 16 )
#define IS_id_parameter( P )		( CHECK_NULL ( P )->ag_tag == 16 )

#define id_parameter_type( P )		( CHECK_TAG ( ( P ), 16 ) + 10 )
#define id_parameter_init( P )		( CHECK_TAG ( ( P ), 16 ) + 11 )
#define id_parameter_term( P )		( CHECK_TAG ( ( P ), 16 ) + 12 )

#define MAKE_id_parameter( name_, storage_, parent_, loc_, type_, c_class_id )\
    {\
	c_class *x381_ = GEN_c_class ( 13, TYPEID_id ) ;\
	x381_->ag_tag = 16 ;\
	COPY_hashid ( x381_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x381_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x381_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x381_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x381_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x381_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x381_ + 7, x381_ ) ;\
	COPY_ulong ( x381_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x381_ + 9, LINK_NONE ) ;\
	COPY_type ( x381_ + 10, ( type_ ) ) ;\
	COPY_exp ( x381_ + 11, NULL_exp ) ;\
	COPY_exp ( x381_ + 12, NULL_exp ) ;\
	( c_class_id ) = x381_ ;\
    }

#define DECONS_id_parameter( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x382_ = CHECK_TAG ( ( c_class_id ), 16 ) ;\
	( name_ ) = DEREF_hashid ( x382_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x382_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x382_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x382_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x382_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x382_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x382_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x382_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x382_ + 9 ) ;\
	( type_ ) = DEREF_type ( x382_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x382_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x382_ + 12 ) ;\
    }

#define DESTROY_id_parameter( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x383_ = CHECK_TAG ( ( c_class_id ), 16 ) ;\
	( name_ ) = DEREF_hashid ( x383_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x383_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x383_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x383_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x383_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x383_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x383_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x383_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x383_ + 9 ) ;\
	( type_ ) = DEREF_type ( x383_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x383_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x383_ + 12 ) ;\
	( destroyer_ ) ( x383_, ( unsigned ) 13 ) ;\
    }


/* Operations for field stat_member of union IDENTIFIER */

#define id_stat_member_tag		( ( unsigned ) 17 )
#define IS_id_stat_member( P )		( CHECK_NULL ( P )->ag_tag == 17 )

#define id_stat_member_type( P )	( CHECK_TAG ( ( P ), 17 ) + 10 )
#define id_stat_member_init( P )	( CHECK_TAG ( ( P ), 17 ) + 11 )
#define id_stat_member_term( P )	( CHECK_TAG ( ( P ), 17 ) + 12 )

#define MAKE_id_stat_member( name_, storage_, parent_, loc_, type_, c_class_id )\
    {\
	c_class *x384_ = GEN_c_class ( 13, TYPEID_id ) ;\
	x384_->ag_tag = 17 ;\
	COPY_hashid ( x384_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x384_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x384_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x384_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x384_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x384_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x384_ + 7, x384_ ) ;\
	COPY_ulong ( x384_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x384_ + 9, LINK_NONE ) ;\
	COPY_type ( x384_ + 10, ( type_ ) ) ;\
	COPY_exp ( x384_ + 11, NULL_exp ) ;\
	COPY_exp ( x384_ + 12, NULL_exp ) ;\
	( c_class_id ) = x384_ ;\
    }

#define DECONS_id_stat_member( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x385_ = CHECK_TAG ( ( c_class_id ), 17 ) ;\
	( name_ ) = DEREF_hashid ( x385_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x385_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x385_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x385_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x385_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x385_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x385_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x385_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x385_ + 9 ) ;\
	( type_ ) = DEREF_type ( x385_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x385_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x385_ + 12 ) ;\
    }

#define DESTROY_id_stat_member( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, init_, term_, c_class_id )\
    {\
	c_class *x386_ = CHECK_TAG ( ( c_class_id ), 17 ) ;\
	( name_ ) = DEREF_hashid ( x386_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x386_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x386_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x386_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x386_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x386_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x386_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x386_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x386_ + 9 ) ;\
	( type_ ) = DEREF_type ( x386_ + 10 ) ;\
	( init_ ) = DEREF_exp ( x386_ + 11 ) ;\
	( term_ ) = DEREF_exp ( x386_ + 12 ) ;\
	( destroyer_ ) ( x386_, ( unsigned ) 13 ) ;\
    }


/* Operations for field weak_param of union IDENTIFIER */

#define id_weak_param_tag		( ( unsigned ) 18 )
#define IS_id_weak_param( P )		( CHECK_NULL ( P )->ag_tag == 18 )


#define MAKE_id_weak_param( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x387_ = GEN_c_class ( 10, TYPEID_id ) ;\
	x387_->ag_tag = 18 ;\
	COPY_hashid ( x387_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x387_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x387_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x387_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x387_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x387_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x387_ + 7, x387_ ) ;\
	COPY_ulong ( x387_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x387_ + 9, LINK_NONE ) ;\
	( c_class_id ) = x387_ ;\
    }

#define DECONS_id_weak_param( name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x388_ = CHECK_TAG ( ( c_class_id ), 18 ) ;\
	( name_ ) = DEREF_hashid ( x388_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x388_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x388_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x388_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x388_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x388_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x388_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x388_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x388_ + 9 ) ;\
    }

#define DESTROY_id_weak_param( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, c_class_id )\
    {\
	c_class *x389_ = CHECK_TAG ( ( c_class_id ), 18 ) ;\
	( name_ ) = DEREF_hashid ( x389_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x389_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x389_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x389_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x389_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x389_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x389_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x389_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x389_ + 9 ) ;\
	( destroyer_ ) ( x389_, ( unsigned ) 10 ) ;\
    }


/* Operations for field set function_etc of union IDENTIFIER */

#define id_function_etc_tag		( ( unsigned ) 22 )
#define IS_id_function_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 19 ) < ( unsigned ) 3 )

#define id_function_etc_type( P )	( CHECK_TAG_ETC ( ( P ), 19, 22 ) + 10 )
#define id_function_etc_over( P )	( CHECK_TAG_ETC ( ( P ), 19, 22 ) + 11 )
#define id_function_etc_form( P )	( CHECK_TAG_ETC ( ( P ), 19, 22 ) + 12 )
#define id_function_etc_chums( P )	( CHECK_TAG_ETC ( ( P ), 19, 22 ) + 13 )
#define id_function_etc_defn( P )	( CHECK_TAG_ETC ( ( P ), 19, 22 ) + 14 )

#define MAKE_id_function_etc( tag, name_, storage_, parent_, loc_, type_, over_, c_class_id )\
    {\
	c_class *x390_ = GEN_c_class ( 15, TYPEID_id ) ;\
	x390_->ag_tag = ( tag ) ;\
	COPY_hashid ( x390_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x390_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x390_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x390_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x390_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x390_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x390_ + 7, x390_ ) ;\
	COPY_ulong ( x390_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x390_ + 9, LINK_NONE ) ;\
	COPY_type ( x390_ + 10, ( type_ ) ) ;\
	COPY_id ( x390_ + 11, ( over_ ) ) ;\
	COPY_type ( x390_ + 12, NULL_type ) ;\
	COPY_list ( x390_ + 13, NULL_list ( CLASS_TYPE ) ) ;\
	COPY_exp ( x390_ + 14, NULL_exp ) ;\
	( c_class_id ) = CHECK_TAG_ETC ( x390_, 19, 22 ) ;\
    }

#define MODIFY_id_function_etc( tag, c_class_id )\
    {\
	c_class *x391_ = CHECK_TAG_ETC ( ( c_class_id ), 19, 22 ) ;\
	x391_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x391_, 19, 22 ) ;\
    }

#define DECONS_id_function_etc( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x392_ = CHECK_TAG_ETC ( ( c_class_id ), 19, 22 ) ;\
	( name_ ) = DEREF_hashid ( x392_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x392_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x392_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x392_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x392_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x392_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x392_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x392_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x392_ + 9 ) ;\
	( type_ ) = DEREF_type ( x392_ + 10 ) ;\
	( over_ ) = DEREF_id ( x392_ + 11 ) ;\
	( form_ ) = DEREF_type ( x392_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x392_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x392_ + 14 ) ;\
    }

#define DESTROY_id_function_etc( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x393_ = CHECK_TAG_ETC ( ( c_class_id ), 19, 22 ) ;\
	( name_ ) = DEREF_hashid ( x393_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x393_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x393_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x393_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x393_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x393_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x393_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x393_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x393_ + 9 ) ;\
	( type_ ) = DEREF_type ( x393_ + 10 ) ;\
	( over_ ) = DEREF_id ( x393_ + 11 ) ;\
	( form_ ) = DEREF_type ( x393_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x393_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x393_ + 14 ) ;\
	( destroyer_ ) ( x393_, ( unsigned ) 15 ) ;\
    }


/* Operations for field function of union IDENTIFIER */

#define id_function_tag			( ( unsigned ) 19 )
#define IS_id_function( P )		( CHECK_NULL ( P )->ag_tag == 19 )

#define id_function_type( P )		( CHECK_TAG ( ( P ), 19 ) + 10 )
#define id_function_over( P )		( CHECK_TAG ( ( P ), 19 ) + 11 )
#define id_function_form( P )		( CHECK_TAG ( ( P ), 19 ) + 12 )
#define id_function_chums( P )		( CHECK_TAG ( ( P ), 19 ) + 13 )
#define id_function_defn( P )		( CHECK_TAG ( ( P ), 19 ) + 14 )

#define MAKE_id_function( name_, storage_, parent_, loc_, type_, over_, c_class_id )\
    {\
	c_class *x394_ = GEN_c_class ( 15, TYPEID_id ) ;\
	x394_->ag_tag = 19 ;\
	COPY_hashid ( x394_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x394_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x394_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x394_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x394_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x394_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x394_ + 7, x394_ ) ;\
	COPY_ulong ( x394_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x394_ + 9, LINK_NONE ) ;\
	COPY_type ( x394_ + 10, ( type_ ) ) ;\
	COPY_id ( x394_ + 11, ( over_ ) ) ;\
	COPY_type ( x394_ + 12, NULL_type ) ;\
	COPY_list ( x394_ + 13, NULL_list ( CLASS_TYPE ) ) ;\
	COPY_exp ( x394_ + 14, NULL_exp ) ;\
	( c_class_id ) = x394_ ;\
    }

#define DECONS_id_function( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x395_ = CHECK_TAG ( ( c_class_id ), 19 ) ;\
	( name_ ) = DEREF_hashid ( x395_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x395_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x395_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x395_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x395_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x395_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x395_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x395_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x395_ + 9 ) ;\
	( type_ ) = DEREF_type ( x395_ + 10 ) ;\
	( over_ ) = DEREF_id ( x395_ + 11 ) ;\
	( form_ ) = DEREF_type ( x395_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x395_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x395_ + 14 ) ;\
    }

#define DESTROY_id_function( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x396_ = CHECK_TAG ( ( c_class_id ), 19 ) ;\
	( name_ ) = DEREF_hashid ( x396_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x396_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x396_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x396_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x396_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x396_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x396_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x396_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x396_ + 9 ) ;\
	( type_ ) = DEREF_type ( x396_ + 10 ) ;\
	( over_ ) = DEREF_id ( x396_ + 11 ) ;\
	( form_ ) = DEREF_type ( x396_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x396_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x396_ + 14 ) ;\
	( destroyer_ ) ( x396_, ( unsigned ) 15 ) ;\
    }


/* Operations for field mem_func of union IDENTIFIER */

#define id_mem_func_tag			( ( unsigned ) 20 )
#define IS_id_mem_func( P )		( CHECK_NULL ( P )->ag_tag == 20 )

#define id_mem_func_type( P )		( CHECK_TAG ( ( P ), 20 ) + 10 )
#define id_mem_func_over( P )		( CHECK_TAG ( ( P ), 20 ) + 11 )
#define id_mem_func_form( P )		( CHECK_TAG ( ( P ), 20 ) + 12 )
#define id_mem_func_chums( P )		( CHECK_TAG ( ( P ), 20 ) + 13 )
#define id_mem_func_defn( P )		( CHECK_TAG ( ( P ), 20 ) + 14 )

#define MAKE_id_mem_func( name_, storage_, parent_, loc_, type_, over_, c_class_id )\
    {\
	c_class *x397_ = GEN_c_class ( 15, TYPEID_id ) ;\
	x397_->ag_tag = 20 ;\
	COPY_hashid ( x397_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x397_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x397_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x397_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x397_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x397_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x397_ + 7, x397_ ) ;\
	COPY_ulong ( x397_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x397_ + 9, LINK_NONE ) ;\
	COPY_type ( x397_ + 10, ( type_ ) ) ;\
	COPY_id ( x397_ + 11, ( over_ ) ) ;\
	COPY_type ( x397_ + 12, NULL_type ) ;\
	COPY_list ( x397_ + 13, NULL_list ( CLASS_TYPE ) ) ;\
	COPY_exp ( x397_ + 14, NULL_exp ) ;\
	( c_class_id ) = x397_ ;\
    }

#define DECONS_id_mem_func( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x398_ = CHECK_TAG ( ( c_class_id ), 20 ) ;\
	( name_ ) = DEREF_hashid ( x398_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x398_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x398_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x398_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x398_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x398_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x398_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x398_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x398_ + 9 ) ;\
	( type_ ) = DEREF_type ( x398_ + 10 ) ;\
	( over_ ) = DEREF_id ( x398_ + 11 ) ;\
	( form_ ) = DEREF_type ( x398_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x398_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x398_ + 14 ) ;\
    }

#define DESTROY_id_mem_func( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x399_ = CHECK_TAG ( ( c_class_id ), 20 ) ;\
	( name_ ) = DEREF_hashid ( x399_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x399_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x399_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x399_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x399_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x399_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x399_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x399_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x399_ + 9 ) ;\
	( type_ ) = DEREF_type ( x399_ + 10 ) ;\
	( over_ ) = DEREF_id ( x399_ + 11 ) ;\
	( form_ ) = DEREF_type ( x399_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x399_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x399_ + 14 ) ;\
	( destroyer_ ) ( x399_, ( unsigned ) 15 ) ;\
    }


/* Operations for field stat_mem_func of union IDENTIFIER */

#define id_stat_mem_func_tag		( ( unsigned ) 21 )
#define IS_id_stat_mem_func( P )	( CHECK_NULL ( P )->ag_tag == 21 )

#define id_stat_mem_func_type( P )	( CHECK_TAG ( ( P ), 21 ) + 10 )
#define id_stat_mem_func_over( P )	( CHECK_TAG ( ( P ), 21 ) + 11 )
#define id_stat_mem_func_form( P )	( CHECK_TAG ( ( P ), 21 ) + 12 )
#define id_stat_mem_func_chums( P )	( CHECK_TAG ( ( P ), 21 ) + 13 )
#define id_stat_mem_func_defn( P )	( CHECK_TAG ( ( P ), 21 ) + 14 )

#define MAKE_id_stat_mem_func( name_, storage_, parent_, loc_, type_, over_, c_class_id )\
    {\
	c_class *x400_ = GEN_c_class ( 15, TYPEID_id ) ;\
	x400_->ag_tag = 21 ;\
	COPY_hashid ( x400_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x400_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x400_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x400_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x400_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x400_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x400_ + 7, x400_ ) ;\
	COPY_ulong ( x400_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x400_ + 9, LINK_NONE ) ;\
	COPY_type ( x400_ + 10, ( type_ ) ) ;\
	COPY_id ( x400_ + 11, ( over_ ) ) ;\
	COPY_type ( x400_ + 12, NULL_type ) ;\
	COPY_list ( x400_ + 13, NULL_list ( CLASS_TYPE ) ) ;\
	COPY_exp ( x400_ + 14, NULL_exp ) ;\
	( c_class_id ) = x400_ ;\
    }

#define DECONS_id_stat_mem_func( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x401_ = CHECK_TAG ( ( c_class_id ), 21 ) ;\
	( name_ ) = DEREF_hashid ( x401_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x401_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x401_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x401_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x401_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x401_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x401_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x401_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x401_ + 9 ) ;\
	( type_ ) = DEREF_type ( x401_ + 10 ) ;\
	( over_ ) = DEREF_id ( x401_ + 11 ) ;\
	( form_ ) = DEREF_type ( x401_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x401_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x401_ + 14 ) ;\
    }

#define DESTROY_id_stat_mem_func( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, over_, form_, chums_, defn_, c_class_id )\
    {\
	c_class *x402_ = CHECK_TAG ( ( c_class_id ), 21 ) ;\
	( name_ ) = DEREF_hashid ( x402_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x402_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x402_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x402_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x402_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x402_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x402_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x402_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x402_ + 9 ) ;\
	( type_ ) = DEREF_type ( x402_ + 10 ) ;\
	( over_ ) = DEREF_id ( x402_ + 11 ) ;\
	( form_ ) = DEREF_type ( x402_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x402_ + 13 ) ;\
	( defn_ ) = DEREF_exp ( x402_ + 14 ) ;\
	( destroyer_ ) ( x402_, ( unsigned ) 15 ) ;\
    }


/* Operations for field member of union IDENTIFIER */

#define id_member_tag			( ( unsigned ) 22 )
#define IS_id_member( P )		( CHECK_NULL ( P )->ag_tag == 22 )

#define id_member_type( P )		( CHECK_TAG ( ( P ), 22 ) + 10 )
#define id_member_off( P )		( CHECK_TAG ( ( P ), 22 ) + 11 )
#define id_member_base( P )		( CHECK_TAG ( ( P ), 22 ) + 12 )

#define MAKE_id_member( name_, storage_, parent_, loc_, type_, c_class_id )\
    {\
	c_class *x403_ = GEN_c_class ( 13, TYPEID_id ) ;\
	x403_->ag_tag = 22 ;\
	COPY_hashid ( x403_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x403_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x403_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x403_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x403_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x403_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x403_ + 7, x403_ ) ;\
	COPY_ulong ( x403_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x403_ + 9, LINK_NONE ) ;\
	COPY_type ( x403_ + 10, ( type_ ) ) ;\
	COPY_off ( x403_ + 11, NULL_off ) ;\
	COPY_graph ( x403_ + 12, NULL_graph ) ;\
	( c_class_id ) = x403_ ;\
    }

#define DECONS_id_member( name_, storage_, parent_, loc_, alias_, no_, dump_, type_, off_, base_, c_class_id )\
    {\
	c_class *x404_ = CHECK_TAG ( ( c_class_id ), 22 ) ;\
	( name_ ) = DEREF_hashid ( x404_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x404_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x404_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x404_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x404_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x404_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x404_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x404_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x404_ + 9 ) ;\
	( type_ ) = DEREF_type ( x404_ + 10 ) ;\
	( off_ ) = DEREF_off ( x404_ + 11 ) ;\
	( base_ ) = DEREF_graph ( x404_ + 12 ) ;\
    }

#define DESTROY_id_member( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, type_, off_, base_, c_class_id )\
    {\
	c_class *x405_ = CHECK_TAG ( ( c_class_id ), 22 ) ;\
	( name_ ) = DEREF_hashid ( x405_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x405_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x405_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x405_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x405_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x405_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x405_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x405_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x405_ + 9 ) ;\
	( type_ ) = DEREF_type ( x405_ + 10 ) ;\
	( off_ ) = DEREF_off ( x405_ + 11 ) ;\
	( base_ ) = DEREF_graph ( x405_ + 12 ) ;\
	( destroyer_ ) ( x405_, ( unsigned ) 13 ) ;\
    }


/* Operations for field enumerator of union IDENTIFIER */

#define id_enumerator_tag		( ( unsigned ) 23 )
#define IS_id_enumerator( P )		( CHECK_NULL ( P )->ag_tag == 23 )

#define id_enumerator_etype( P )	( CHECK_TAG ( ( P ), 23 ) + 10 )
#define id_enumerator_value( P )	( CHECK_TAG ( ( P ), 23 ) + 11 )

#define MAKE_id_enumerator( name_, storage_, parent_, loc_, etype_, value_, c_class_id )\
    {\
	c_class *x406_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x406_->ag_tag = 23 ;\
	COPY_hashid ( x406_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x406_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x406_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x406_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x406_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x406_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x406_ + 7, x406_ ) ;\
	COPY_ulong ( x406_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x406_ + 9, LINK_NONE ) ;\
	COPY_type ( x406_ + 10, ( etype_ ) ) ;\
	COPY_exp ( x406_ + 11, ( value_ ) ) ;\
	( c_class_id ) = x406_ ;\
    }

#define DECONS_id_enumerator( name_, storage_, parent_, loc_, alias_, no_, dump_, etype_, value_, c_class_id )\
    {\
	c_class *x407_ = CHECK_TAG ( ( c_class_id ), 23 ) ;\
	( name_ ) = DEREF_hashid ( x407_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x407_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x407_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x407_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x407_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x407_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x407_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x407_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x407_ + 9 ) ;\
	( etype_ ) = DEREF_type ( x407_ + 10 ) ;\
	( value_ ) = DEREF_exp ( x407_ + 11 ) ;\
    }

#define DESTROY_id_enumerator( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, etype_, value_, c_class_id )\
    {\
	c_class *x408_ = CHECK_TAG ( ( c_class_id ), 23 ) ;\
	( name_ ) = DEREF_hashid ( x408_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x408_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x408_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x408_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x408_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x408_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x408_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x408_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x408_ + 9 ) ;\
	( etype_ ) = DEREF_type ( x408_ + 10 ) ;\
	( value_ ) = DEREF_exp ( x408_ + 11 ) ;\
	( destroyer_ ) ( x408_, ( unsigned ) 12 ) ;\
    }


/* Operations for field label of union IDENTIFIER */

#define id_label_tag			( ( unsigned ) 24 )
#define IS_id_label( P )		( CHECK_NULL ( P )->ag_tag == 24 )

#define id_label_op( P )		( CHECK_TAG ( ( P ), 24 ) + 10 )
#define id_label_stmt( P )		( CHECK_TAG ( ( P ), 24 ) + 11 )
#define id_label_gotos( P )		( CHECK_TAG ( ( P ), 24 ) + 12 )
#define id_label_vars( P )		( CHECK_TAG ( ( P ), 24 ) + 13 )

#define MAKE_id_label( name_, storage_, parent_, loc_, op_, c_class_id )\
    {\
	c_class *x409_ = GEN_c_class ( 14, TYPEID_id ) ;\
	x409_->ag_tag = 24 ;\
	COPY_hashid ( x409_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x409_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x409_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x409_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x409_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x409_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x409_ + 7, x409_ ) ;\
	COPY_ulong ( x409_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x409_ + 9, LINK_NONE ) ;\
	COPY_int ( x409_ + 10, ( op_ ) ) ;\
	COPY_exp ( x409_ + 11, NULL_exp ) ;\
	COPY_exp ( x409_ + 12, NULL_exp ) ;\
	COPY_list ( x409_ + 13, NULL_list ( VARIABLE ) ) ;\
	( c_class_id ) = x409_ ;\
    }

#define DECONS_id_label( name_, storage_, parent_, loc_, alias_, no_, dump_, op_, stmt_, gotos_, vars_, c_class_id )\
    {\
	c_class *x410_ = CHECK_TAG ( ( c_class_id ), 24 ) ;\
	( name_ ) = DEREF_hashid ( x410_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x410_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x410_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x410_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x410_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x410_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x410_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x410_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x410_ + 9 ) ;\
	( op_ ) = DEREF_int ( x410_ + 10 ) ;\
	( stmt_ ) = DEREF_exp ( x410_ + 11 ) ;\
	( gotos_ ) = DEREF_exp ( x410_ + 12 ) ;\
	( vars_ ) = DEREF_list ( x410_ + 13 ) ;\
    }

#define DESTROY_id_label( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, op_, stmt_, gotos_, vars_, c_class_id )\
    {\
	c_class *x411_ = CHECK_TAG ( ( c_class_id ), 24 ) ;\
	( name_ ) = DEREF_hashid ( x411_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x411_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x411_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x411_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x411_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x411_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x411_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x411_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x411_ + 9 ) ;\
	( op_ ) = DEREF_int ( x411_ + 10 ) ;\
	( stmt_ ) = DEREF_exp ( x411_ + 11 ) ;\
	( gotos_ ) = DEREF_exp ( x411_ + 12 ) ;\
	( vars_ ) = DEREF_list ( x411_ + 13 ) ;\
	( destroyer_ ) ( x411_, ( unsigned ) 14 ) ;\
    }


/* Operations for field token of union IDENTIFIER */

#define id_token_tag			( ( unsigned ) 25 )
#define IS_id_token( P )		( CHECK_NULL ( P )->ag_tag == 25 )

#define id_token_sort( P )		( CHECK_TAG ( ( P ), 25 ) + 10 )
#define id_token_alt( P )		( CHECK_TAG ( ( P ), 25 ) + 11 )

#define MAKE_id_token( name_, storage_, parent_, loc_, sort_, alt_, c_class_id )\
    {\
	c_class *x412_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x412_->ag_tag = 25 ;\
	COPY_hashid ( x412_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x412_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x412_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x412_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x412_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x412_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x412_ + 7, x412_ ) ;\
	COPY_ulong ( x412_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x412_ + 9, LINK_NONE ) ;\
	COPY_tok ( x412_ + 10, ( sort_ ) ) ;\
	COPY_id ( x412_ + 11, ( alt_ ) ) ;\
	( c_class_id ) = x412_ ;\
    }

#define DECONS_id_token( name_, storage_, parent_, loc_, alias_, no_, dump_, sort_, alt_, c_class_id )\
    {\
	c_class *x413_ = CHECK_TAG ( ( c_class_id ), 25 ) ;\
	( name_ ) = DEREF_hashid ( x413_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x413_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x413_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x413_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x413_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x413_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x413_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x413_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x413_ + 9 ) ;\
	( sort_ ) = DEREF_tok ( x413_ + 10 ) ;\
	( alt_ ) = DEREF_id ( x413_ + 11 ) ;\
    }

#define DESTROY_id_token( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, sort_, alt_, c_class_id )\
    {\
	c_class *x414_ = CHECK_TAG ( ( c_class_id ), 25 ) ;\
	( name_ ) = DEREF_hashid ( x414_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x414_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x414_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x414_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x414_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x414_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x414_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x414_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x414_ + 9 ) ;\
	( sort_ ) = DEREF_tok ( x414_ + 10 ) ;\
	( alt_ ) = DEREF_id ( x414_ + 11 ) ;\
	( destroyer_ ) ( x414_, ( unsigned ) 12 ) ;\
    }


/* Operations for field ambig of union IDENTIFIER */

#define id_ambig_tag			( ( unsigned ) 26 )
#define IS_id_ambig( P )		( CHECK_NULL ( P )->ag_tag == 26 )

#define id_ambig_ids( P )		( CHECK_TAG ( ( P ), 26 ) + 10 )
#define id_ambig_over( P )		( CHECK_TAG ( ( P ), 26 ) + 11 )

#define MAKE_id_ambig( name_, storage_, parent_, loc_, ids_, over_, c_class_id )\
    {\
	c_class *x415_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x415_->ag_tag = 26 ;\
	COPY_hashid ( x415_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x415_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x415_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x415_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x415_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x415_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x415_ + 7, x415_ ) ;\
	COPY_ulong ( x415_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x415_ + 9, LINK_NONE ) ;\
	COPY_list ( x415_ + 10, ( ids_ ) ) ;\
	COPY_int ( x415_ + 11, ( over_ ) ) ;\
	( c_class_id ) = x415_ ;\
    }

#define DECONS_id_ambig( name_, storage_, parent_, loc_, alias_, no_, dump_, ids_, over_, c_class_id )\
    {\
	c_class *x416_ = CHECK_TAG ( ( c_class_id ), 26 ) ;\
	( name_ ) = DEREF_hashid ( x416_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x416_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x416_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x416_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x416_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x416_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x416_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x416_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x416_ + 9 ) ;\
	( ids_ ) = DEREF_list ( x416_ + 10 ) ;\
	( over_ ) = DEREF_int ( x416_ + 11 ) ;\
    }

#define DESTROY_id_ambig( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, ids_, over_, c_class_id )\
    {\
	c_class *x417_ = CHECK_TAG ( ( c_class_id ), 26 ) ;\
	( name_ ) = DEREF_hashid ( x417_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x417_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x417_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x417_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x417_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x417_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x417_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x417_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x417_ + 9 ) ;\
	( ids_ ) = DEREF_list ( x417_ + 10 ) ;\
	( over_ ) = DEREF_int ( x417_ + 11 ) ;\
	( destroyer_ ) ( x417_, ( unsigned ) 12 ) ;\
    }


/* Operations for field undef of union IDENTIFIER */

#define id_undef_tag			( ( unsigned ) 27 )
#define IS_id_undef( P )		( CHECK_NULL ( P )->ag_tag == 27 )

#define id_undef_form( P )		( CHECK_TAG ( ( P ), 27 ) + 10 )

#define MAKE_id_undef( name_, storage_, parent_, loc_, c_class_id )\
    {\
	c_class *x418_ = GEN_c_class ( 11, TYPEID_id ) ;\
	x418_->ag_tag = 27 ;\
	COPY_hashid ( x418_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x418_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x418_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x418_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x418_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x418_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x418_ + 7, x418_ ) ;\
	COPY_ulong ( x418_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x418_ + 9, LINK_NONE ) ;\
	COPY_type ( x418_ + 10, NULL_type ) ;\
	( c_class_id ) = x418_ ;\
    }

#define DECONS_id_undef( name_, storage_, parent_, loc_, alias_, no_, dump_, form_, c_class_id )\
    {\
	c_class *x419_ = CHECK_TAG ( ( c_class_id ), 27 ) ;\
	( name_ ) = DEREF_hashid ( x419_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x419_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x419_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x419_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x419_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x419_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x419_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x419_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x419_ + 9 ) ;\
	( form_ ) = DEREF_type ( x419_ + 10 ) ;\
    }

#define DESTROY_id_undef( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, form_, c_class_id )\
    {\
	c_class *x420_ = CHECK_TAG ( ( c_class_id ), 27 ) ;\
	( name_ ) = DEREF_hashid ( x420_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x420_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x420_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x420_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x420_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x420_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x420_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x420_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x420_ + 9 ) ;\
	( form_ ) = DEREF_type ( x420_ + 10 ) ;\
	( destroyer_ ) ( x420_, ( unsigned ) 11 ) ;\
    }


/* Operations for field pending of union IDENTIFIER */

#define id_pending_tag			( ( unsigned ) 28 )
#define IS_id_pending( P )		( CHECK_NULL ( P )->ag_tag == 28 )

#define id_pending_itag( P )		( CHECK_TAG ( ( P ), 28 ) + 10 )
#define id_pending_type( P )		( CHECK_TAG ( ( P ), 28 ) + 11 )

#define MAKE_id_pending( name_, storage_, parent_, loc_, itag_, type_, c_class_id )\
    {\
	c_class *x421_ = GEN_c_class ( 12, TYPEID_id ) ;\
	x421_->ag_tag = 28 ;\
	COPY_hashid ( x421_ + 1, ( name_ ) ) ;\
	COPY_dspec ( x421_ + 2, ( storage_ ) ) ;\
	COPY_nspace ( x421_ + 3, ( parent_ ) ) ;\
	COPY_ulong ( x421_ + 4, ( loc_ ).line ) ;\
	COPY_ulong ( x421_ + 5, ( loc_ ).column ) ;\
	COPY_ptr ( x421_ + 6, ( loc_ ).posn ) ;\
	COPY_id ( x421_ + 7, x421_ ) ;\
	COPY_ulong ( x421_ + 8, LINK_NONE ) ;\
	COPY_ulong ( x421_ + 9, LINK_NONE ) ;\
	COPY_unsigned ( x421_ + 10, ( itag_ ) ) ;\
	COPY_type ( x421_ + 11, ( type_ ) ) ;\
	( c_class_id ) = x421_ ;\
    }

#define DECONS_id_pending( name_, storage_, parent_, loc_, alias_, no_, dump_, itag_, type_, c_class_id )\
    {\
	c_class *x422_ = CHECK_TAG ( ( c_class_id ), 28 ) ;\
	( name_ ) = DEREF_hashid ( x422_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x422_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x422_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x422_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x422_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x422_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x422_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x422_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x422_ + 9 ) ;\
	( itag_ ) = DEREF_unsigned ( x422_ + 10 ) ;\
	( type_ ) = DEREF_type ( x422_ + 11 ) ;\
    }

#define DESTROY_id_pending( destroyer_, name_, storage_, parent_, loc_, alias_, no_, dump_, itag_, type_, c_class_id )\
    {\
	c_class *x423_ = CHECK_TAG ( ( c_class_id ), 28 ) ;\
	( name_ ) = DEREF_hashid ( x423_ + 1 ) ;\
	( storage_ ) = DEREF_dspec ( x423_ + 2 ) ;\
	( parent_ ) = DEREF_nspace ( x423_ + 3 ) ;\
	( loc_ ).line = DEREF_ulong ( x423_ + 4 ) ;\
	( loc_ ).column = DEREF_ulong ( x423_ + 5 ) ;\
	( loc_ ).posn = DEREF_ptr ( x423_ + 6 ) ;\
	( alias_ ) = DEREF_id ( x423_ + 7 ) ;\
	( no_ ) = DEREF_ulong ( x423_ + 8 ) ;\
	( dump_ ) = DEREF_ulong ( x423_ + 9 ) ;\
	( itag_ ) = DEREF_unsigned ( x423_ + 10 ) ;\
	( type_ ) = DEREF_type ( x423_ + 11 ) ;\
	( destroyer_ ) ( x423_, ( unsigned ) 12 ) ;\
    }


#endif
