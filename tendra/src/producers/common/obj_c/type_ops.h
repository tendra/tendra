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

#ifndef TYPE_OPS_H_INCLUDED
#define TYPE_OPS_H_INCLUDED

/* Operations for union TYPE */

#define TAG_type( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for component qual of union TYPE */

#define type_qual( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component name of union TYPE */

#define type_name( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for field pre of union TYPE */

#define type_pre_tag			( ( unsigned ) 0 )
#define IS_type_pre( P )		( CHECK_NULL ( P )->ag_tag == 0 )

#define type_pre_rep( P )		( CHECK_TAG ( ( P ), 0 ) + 3 )
#define type_pre_nqual( P )		( CHECK_TAG ( ( P ), 0 ) + 4 )

#define MAKE_type_pre( qual_, rep_, nqual_, c_class_type )\
    {\
	c_class *x226_ = GEN_c_class ( 5, TYPEID_type ) ;\
	x226_->ag_tag = 0 ;\
	COPY_cv ( x226_ + 1, ( qual_ ) ) ;\
	COPY_id ( x226_ + 2, NULL_id ) ;\
	COPY_btype ( x226_ + 3, ( rep_ ) ) ;\
	COPY_qual ( x226_ + 4, ( nqual_ ) ) ;\
	( c_class_type ) = x226_ ;\
    }

#define DECONS_type_pre( qual_, name_, rep_, nqual_, c_class_type )\
    {\
	c_class *x227_ = CHECK_TAG ( ( c_class_type ), 0 ) ;\
	( qual_ ) = DEREF_cv ( x227_ + 1 ) ;\
	( name_ ) = DEREF_id ( x227_ + 2 ) ;\
	( rep_ ) = DEREF_btype ( x227_ + 3 ) ;\
	( nqual_ ) = DEREF_qual ( x227_ + 4 ) ;\
    }

#define DESTROY_type_pre( destroyer_, qual_, name_, rep_, nqual_, c_class_type )\
    {\
	c_class *x228_ = CHECK_TAG ( ( c_class_type ), 0 ) ;\
	( qual_ ) = DEREF_cv ( x228_ + 1 ) ;\
	( name_ ) = DEREF_id ( x228_ + 2 ) ;\
	( rep_ ) = DEREF_btype ( x228_ + 3 ) ;\
	( nqual_ ) = DEREF_qual ( x228_ + 4 ) ;\
	( destroyer_ ) ( x228_, ( unsigned ) 5 ) ;\
    }


/* Operations for field integer of union TYPE */

#define type_integer_tag		( ( unsigned ) 1 )
#define IS_type_integer( P )		( CHECK_NULL ( P )->ag_tag == 1 )

#define type_integer_rep( P )		( CHECK_TAG ( ( P ), 1 ) + 3 )
#define type_integer_sem( P )		( CHECK_TAG ( ( P ), 1 ) + 4 )

#define MAKE_type_integer( qual_, rep_, sem_, c_class_type )\
    {\
	c_class *x229_ = GEN_c_class ( 5, TYPEID_type ) ;\
	x229_->ag_tag = 1 ;\
	COPY_cv ( x229_ + 1, ( qual_ ) ) ;\
	COPY_id ( x229_ + 2, NULL_id ) ;\
	COPY_itype ( x229_ + 3, ( rep_ ) ) ;\
	COPY_itype ( x229_ + 4, ( sem_ ) ) ;\
	( c_class_type ) = x229_ ;\
    }

#define DECONS_type_integer( qual_, name_, rep_, sem_, c_class_type )\
    {\
	c_class *x230_ = CHECK_TAG ( ( c_class_type ), 1 ) ;\
	( qual_ ) = DEREF_cv ( x230_ + 1 ) ;\
	( name_ ) = DEREF_id ( x230_ + 2 ) ;\
	( rep_ ) = DEREF_itype ( x230_ + 3 ) ;\
	( sem_ ) = DEREF_itype ( x230_ + 4 ) ;\
    }

#define DESTROY_type_integer( destroyer_, qual_, name_, rep_, sem_, c_class_type )\
    {\
	c_class *x231_ = CHECK_TAG ( ( c_class_type ), 1 ) ;\
	( qual_ ) = DEREF_cv ( x231_ + 1 ) ;\
	( name_ ) = DEREF_id ( x231_ + 2 ) ;\
	( rep_ ) = DEREF_itype ( x231_ + 3 ) ;\
	( sem_ ) = DEREF_itype ( x231_ + 4 ) ;\
	( destroyer_ ) ( x231_, ( unsigned ) 5 ) ;\
    }


/* Operations for field floating of union TYPE */

#define type_floating_tag		( ( unsigned ) 2 )
#define IS_type_floating( P )		( CHECK_NULL ( P )->ag_tag == 2 )

#define type_floating_rep( P )		( CHECK_TAG ( ( P ), 2 ) + 3 )
#define type_floating_sem( P )		( CHECK_TAG ( ( P ), 2 ) + 4 )

#define MAKE_type_floating( qual_, rep_, sem_, c_class_type )\
    {\
	c_class *x232_ = GEN_c_class ( 5, TYPEID_type ) ;\
	x232_->ag_tag = 2 ;\
	COPY_cv ( x232_ + 1, ( qual_ ) ) ;\
	COPY_id ( x232_ + 2, NULL_id ) ;\
	COPY_ftype ( x232_ + 3, ( rep_ ) ) ;\
	COPY_ftype ( x232_ + 4, ( sem_ ) ) ;\
	( c_class_type ) = x232_ ;\
    }

#define DECONS_type_floating( qual_, name_, rep_, sem_, c_class_type )\
    {\
	c_class *x233_ = CHECK_TAG ( ( c_class_type ), 2 ) ;\
	( qual_ ) = DEREF_cv ( x233_ + 1 ) ;\
	( name_ ) = DEREF_id ( x233_ + 2 ) ;\
	( rep_ ) = DEREF_ftype ( x233_ + 3 ) ;\
	( sem_ ) = DEREF_ftype ( x233_ + 4 ) ;\
    }

#define DESTROY_type_floating( destroyer_, qual_, name_, rep_, sem_, c_class_type )\
    {\
	c_class *x234_ = CHECK_TAG ( ( c_class_type ), 2 ) ;\
	( qual_ ) = DEREF_cv ( x234_ + 1 ) ;\
	( name_ ) = DEREF_id ( x234_ + 2 ) ;\
	( rep_ ) = DEREF_ftype ( x234_ + 3 ) ;\
	( sem_ ) = DEREF_ftype ( x234_ + 4 ) ;\
	( destroyer_ ) ( x234_, ( unsigned ) 5 ) ;\
    }


/* Operations for field set top_etc of union TYPE */

#define type_top_etc_tag		( ( unsigned ) 5 )
#define IS_type_top_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 3 ) < ( unsigned ) 2 )


#define MAKE_type_top_etc( tag, qual_, c_class_type )\
    {\
	c_class *x235_ = GEN_c_class ( 3, TYPEID_type ) ;\
	x235_->ag_tag = ( tag ) ;\
	COPY_cv ( x235_ + 1, ( qual_ ) ) ;\
	COPY_id ( x235_ + 2, NULL_id ) ;\
	( c_class_type ) = CHECK_TAG_ETC ( x235_, 3, 5 ) ;\
    }

#define MODIFY_type_top_etc( tag, c_class_type )\
    {\
	c_class *x236_ = CHECK_TAG_ETC ( ( c_class_type ), 3, 5 ) ;\
	x236_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x236_, 3, 5 ) ;\
    }

#define DECONS_type_top_etc( qual_, name_, c_class_type )\
    {\
	c_class *x237_ = CHECK_TAG_ETC ( ( c_class_type ), 3, 5 ) ;\
	( qual_ ) = DEREF_cv ( x237_ + 1 ) ;\
	( name_ ) = DEREF_id ( x237_ + 2 ) ;\
    }

#define DESTROY_type_top_etc( destroyer_, qual_, name_, c_class_type )\
    {\
	c_class *x238_ = CHECK_TAG_ETC ( ( c_class_type ), 3, 5 ) ;\
	( qual_ ) = DEREF_cv ( x238_ + 1 ) ;\
	( name_ ) = DEREF_id ( x238_ + 2 ) ;\
	( destroyer_ ) ( x238_, ( unsigned ) 3 ) ;\
    }


/* Operations for field top of union TYPE */

#define type_top_tag			( ( unsigned ) 3 )
#define IS_type_top( P )		( CHECK_NULL ( P )->ag_tag == 3 )


#define MAKE_type_top( qual_, c_class_type )\
    {\
	c_class *x239_ = GEN_c_class ( 3, TYPEID_type ) ;\
	x239_->ag_tag = 3 ;\
	COPY_cv ( x239_ + 1, ( qual_ ) ) ;\
	COPY_id ( x239_ + 2, NULL_id ) ;\
	( c_class_type ) = x239_ ;\
    }

#define DECONS_type_top( qual_, name_, c_class_type )\
    {\
	c_class *x240_ = CHECK_TAG ( ( c_class_type ), 3 ) ;\
	( qual_ ) = DEREF_cv ( x240_ + 1 ) ;\
	( name_ ) = DEREF_id ( x240_ + 2 ) ;\
    }

#define DESTROY_type_top( destroyer_, qual_, name_, c_class_type )\
    {\
	c_class *x241_ = CHECK_TAG ( ( c_class_type ), 3 ) ;\
	( qual_ ) = DEREF_cv ( x241_ + 1 ) ;\
	( name_ ) = DEREF_id ( x241_ + 2 ) ;\
	( destroyer_ ) ( x241_, ( unsigned ) 3 ) ;\
    }


/* Operations for field bottom of union TYPE */

#define type_bottom_tag			( ( unsigned ) 4 )
#define IS_type_bottom( P )		( CHECK_NULL ( P )->ag_tag == 4 )


#define MAKE_type_bottom( qual_, c_class_type )\
    {\
	c_class *x242_ = GEN_c_class ( 3, TYPEID_type ) ;\
	x242_->ag_tag = 4 ;\
	COPY_cv ( x242_ + 1, ( qual_ ) ) ;\
	COPY_id ( x242_ + 2, NULL_id ) ;\
	( c_class_type ) = x242_ ;\
    }

#define DECONS_type_bottom( qual_, name_, c_class_type )\
    {\
	c_class *x243_ = CHECK_TAG ( ( c_class_type ), 4 ) ;\
	( qual_ ) = DEREF_cv ( x243_ + 1 ) ;\
	( name_ ) = DEREF_id ( x243_ + 2 ) ;\
    }

#define DESTROY_type_bottom( destroyer_, qual_, name_, c_class_type )\
    {\
	c_class *x244_ = CHECK_TAG ( ( c_class_type ), 4 ) ;\
	( qual_ ) = DEREF_cv ( x244_ + 1 ) ;\
	( name_ ) = DEREF_id ( x244_ + 2 ) ;\
	( destroyer_ ) ( x244_, ( unsigned ) 3 ) ;\
    }


/* Operations for field set ptr_etc of union TYPE */

#define type_ptr_etc_tag		( ( unsigned ) 7 )
#define IS_type_ptr_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 5 ) < ( unsigned ) 2 )

#define type_ptr_etc_sub( P )		( CHECK_TAG_ETC ( ( P ), 5, 7 ) + 3 )

#define MAKE_type_ptr_etc( tag, qual_, sub_, c_class_type )\
    {\
	c_class *x245_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x245_->ag_tag = ( tag ) ;\
	COPY_cv ( x245_ + 1, ( qual_ ) ) ;\
	COPY_id ( x245_ + 2, NULL_id ) ;\
	COPY_type ( x245_ + 3, ( sub_ ) ) ;\
	( c_class_type ) = CHECK_TAG_ETC ( x245_, 5, 7 ) ;\
    }

#define MODIFY_type_ptr_etc( tag, c_class_type )\
    {\
	c_class *x246_ = CHECK_TAG_ETC ( ( c_class_type ), 5, 7 ) ;\
	x246_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x246_, 5, 7 ) ;\
    }

#define DECONS_type_ptr_etc( qual_, name_, sub_, c_class_type )\
    {\
	c_class *x247_ = CHECK_TAG_ETC ( ( c_class_type ), 5, 7 ) ;\
	( qual_ ) = DEREF_cv ( x247_ + 1 ) ;\
	( name_ ) = DEREF_id ( x247_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x247_ + 3 ) ;\
    }

#define DESTROY_type_ptr_etc( destroyer_, qual_, name_, sub_, c_class_type )\
    {\
	c_class *x248_ = CHECK_TAG_ETC ( ( c_class_type ), 5, 7 ) ;\
	( qual_ ) = DEREF_cv ( x248_ + 1 ) ;\
	( name_ ) = DEREF_id ( x248_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x248_ + 3 ) ;\
	( destroyer_ ) ( x248_, ( unsigned ) 4 ) ;\
    }


/* Operations for field ptr of union TYPE */

#define type_ptr_tag			( ( unsigned ) 5 )
#define IS_type_ptr( P )		( CHECK_NULL ( P )->ag_tag == 5 )

#define type_ptr_sub( P )		( CHECK_TAG ( ( P ), 5 ) + 3 )

#define MAKE_type_ptr( qual_, sub_, c_class_type )\
    {\
	c_class *x249_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x249_->ag_tag = 5 ;\
	COPY_cv ( x249_ + 1, ( qual_ ) ) ;\
	COPY_id ( x249_ + 2, NULL_id ) ;\
	COPY_type ( x249_ + 3, ( sub_ ) ) ;\
	( c_class_type ) = x249_ ;\
    }

#define DECONS_type_ptr( qual_, name_, sub_, c_class_type )\
    {\
	c_class *x250_ = CHECK_TAG ( ( c_class_type ), 5 ) ;\
	( qual_ ) = DEREF_cv ( x250_ + 1 ) ;\
	( name_ ) = DEREF_id ( x250_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x250_ + 3 ) ;\
    }

#define DESTROY_type_ptr( destroyer_, qual_, name_, sub_, c_class_type )\
    {\
	c_class *x251_ = CHECK_TAG ( ( c_class_type ), 5 ) ;\
	( qual_ ) = DEREF_cv ( x251_ + 1 ) ;\
	( name_ ) = DEREF_id ( x251_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x251_ + 3 ) ;\
	( destroyer_ ) ( x251_, ( unsigned ) 4 ) ;\
    }


/* Operations for field ref of union TYPE */

#define type_ref_tag			( ( unsigned ) 6 )
#define IS_type_ref( P )		( CHECK_NULL ( P )->ag_tag == 6 )

#define type_ref_sub( P )		( CHECK_TAG ( ( P ), 6 ) + 3 )

#define MAKE_type_ref( qual_, sub_, c_class_type )\
    {\
	c_class *x252_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x252_->ag_tag = 6 ;\
	COPY_cv ( x252_ + 1, ( qual_ ) ) ;\
	COPY_id ( x252_ + 2, NULL_id ) ;\
	COPY_type ( x252_ + 3, ( sub_ ) ) ;\
	( c_class_type ) = x252_ ;\
    }

#define DECONS_type_ref( qual_, name_, sub_, c_class_type )\
    {\
	c_class *x253_ = CHECK_TAG ( ( c_class_type ), 6 ) ;\
	( qual_ ) = DEREF_cv ( x253_ + 1 ) ;\
	( name_ ) = DEREF_id ( x253_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x253_ + 3 ) ;\
    }

#define DESTROY_type_ref( destroyer_, qual_, name_, sub_, c_class_type )\
    {\
	c_class *x254_ = CHECK_TAG ( ( c_class_type ), 6 ) ;\
	( qual_ ) = DEREF_cv ( x254_ + 1 ) ;\
	( name_ ) = DEREF_id ( x254_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x254_ + 3 ) ;\
	( destroyer_ ) ( x254_, ( unsigned ) 4 ) ;\
    }


/* Operations for field ptr_mem of union TYPE */

#define type_ptr_mem_tag		( ( unsigned ) 7 )
#define IS_type_ptr_mem( P )		( CHECK_NULL ( P )->ag_tag == 7 )

#define type_ptr_mem_of( P )		( CHECK_TAG ( ( P ), 7 ) + 3 )
#define type_ptr_mem_sub( P )		( CHECK_TAG ( ( P ), 7 ) + 4 )

#define MAKE_type_ptr_mem( qual_, of_, sub_, c_class_type )\
    {\
	c_class *x255_ = GEN_c_class ( 5, TYPEID_type ) ;\
	x255_->ag_tag = 7 ;\
	COPY_cv ( x255_ + 1, ( qual_ ) ) ;\
	COPY_id ( x255_ + 2, NULL_id ) ;\
	COPY_ctype ( x255_ + 3, ( of_ ) ) ;\
	COPY_type ( x255_ + 4, ( sub_ ) ) ;\
	( c_class_type ) = x255_ ;\
    }

#define DECONS_type_ptr_mem( qual_, name_, of_, sub_, c_class_type )\
    {\
	c_class *x256_ = CHECK_TAG ( ( c_class_type ), 7 ) ;\
	( qual_ ) = DEREF_cv ( x256_ + 1 ) ;\
	( name_ ) = DEREF_id ( x256_ + 2 ) ;\
	( of_ ) = DEREF_ctype ( x256_ + 3 ) ;\
	( sub_ ) = DEREF_type ( x256_ + 4 ) ;\
    }

#define DESTROY_type_ptr_mem( destroyer_, qual_, name_, of_, sub_, c_class_type )\
    {\
	c_class *x257_ = CHECK_TAG ( ( c_class_type ), 7 ) ;\
	( qual_ ) = DEREF_cv ( x257_ + 1 ) ;\
	( name_ ) = DEREF_id ( x257_ + 2 ) ;\
	( of_ ) = DEREF_ctype ( x257_ + 3 ) ;\
	( sub_ ) = DEREF_type ( x257_ + 4 ) ;\
	( destroyer_ ) ( x257_, ( unsigned ) 5 ) ;\
    }


/* Operations for field func of union TYPE */

#define type_func_tag			( ( unsigned ) 8 )
#define IS_type_func( P )		( CHECK_NULL ( P )->ag_tag == 8 )

#define type_func_ret( P )		( CHECK_TAG ( ( P ), 8 ) + 3 )
#define type_func_ptypes( P )		( CHECK_TAG ( ( P ), 8 ) + 4 )
#define type_func_ellipsis( P )		( CHECK_TAG ( ( P ), 8 ) + 5 )
#define type_func_mqual( P )		( CHECK_TAG ( ( P ), 8 ) + 6 )
#define type_func_mtypes( P )		( CHECK_TAG ( ( P ), 8 ) + 7 )
#define type_func_pars( P )		( CHECK_TAG ( ( P ), 8 ) + 8 )
#define type_func_pids( P )		( CHECK_TAG ( ( P ), 8 ) + 9 )
#define type_func_except( P )		( CHECK_TAG ( ( P ), 8 ) + 10 )

#define MAKE_type_func( qual_, ret_, ptypes_, ellipsis_, mqual_, mtypes_, pars_, pids_, except_, c_class_type )\
    {\
	c_class *x258_ = GEN_c_class ( 11, TYPEID_type ) ;\
	x258_->ag_tag = 8 ;\
	COPY_cv ( x258_ + 1, ( qual_ ) ) ;\
	COPY_id ( x258_ + 2, NULL_id ) ;\
	COPY_type ( x258_ + 3, ( ret_ ) ) ;\
	COPY_list ( x258_ + 4, ( ptypes_ ) ) ;\
	COPY_int ( x258_ + 5, ( ellipsis_ ) ) ;\
	COPY_cv ( x258_ + 6, ( mqual_ ) ) ;\
	COPY_list ( x258_ + 7, ( mtypes_ ) ) ;\
	COPY_nspace ( x258_ + 8, ( pars_ ) ) ;\
	COPY_list ( x258_ + 9, ( pids_ ) ) ;\
	COPY_list ( x258_ + 10, ( except_ ) ) ;\
	( c_class_type ) = x258_ ;\
    }

#define DECONS_type_func( qual_, name_, ret_, ptypes_, ellipsis_, mqual_, mtypes_, pars_, pids_, except_, c_class_type )\
    {\
	c_class *x259_ = CHECK_TAG ( ( c_class_type ), 8 ) ;\
	( qual_ ) = DEREF_cv ( x259_ + 1 ) ;\
	( name_ ) = DEREF_id ( x259_ + 2 ) ;\
	( ret_ ) = DEREF_type ( x259_ + 3 ) ;\
	( ptypes_ ) = DEREF_list ( x259_ + 4 ) ;\
	( ellipsis_ ) = DEREF_int ( x259_ + 5 ) ;\
	( mqual_ ) = DEREF_cv ( x259_ + 6 ) ;\
	( mtypes_ ) = DEREF_list ( x259_ + 7 ) ;\
	( pars_ ) = DEREF_nspace ( x259_ + 8 ) ;\
	( pids_ ) = DEREF_list ( x259_ + 9 ) ;\
	( except_ ) = DEREF_list ( x259_ + 10 ) ;\
    }

#define DESTROY_type_func( destroyer_, qual_, name_, ret_, ptypes_, ellipsis_, mqual_, mtypes_, pars_, pids_, except_, c_class_type )\
    {\
	c_class *x260_ = CHECK_TAG ( ( c_class_type ), 8 ) ;\
	( qual_ ) = DEREF_cv ( x260_ + 1 ) ;\
	( name_ ) = DEREF_id ( x260_ + 2 ) ;\
	( ret_ ) = DEREF_type ( x260_ + 3 ) ;\
	( ptypes_ ) = DEREF_list ( x260_ + 4 ) ;\
	( ellipsis_ ) = DEREF_int ( x260_ + 5 ) ;\
	( mqual_ ) = DEREF_cv ( x260_ + 6 ) ;\
	( mtypes_ ) = DEREF_list ( x260_ + 7 ) ;\
	( pars_ ) = DEREF_nspace ( x260_ + 8 ) ;\
	( pids_ ) = DEREF_list ( x260_ + 9 ) ;\
	( except_ ) = DEREF_list ( x260_ + 10 ) ;\
	( destroyer_ ) ( x260_, ( unsigned ) 11 ) ;\
    }


/* Operations for field array of union TYPE */

#define type_array_tag			( ( unsigned ) 9 )
#define IS_type_array( P )		( CHECK_NULL ( P )->ag_tag == 9 )

#define type_array_sub( P )		( CHECK_TAG ( ( P ), 9 ) + 3 )
#define type_array_size( P )		( CHECK_TAG ( ( P ), 9 ) + 4 )

#define MAKE_type_array( qual_, sub_, size_, c_class_type )\
    {\
	c_class *x261_ = GEN_c_class ( 5, TYPEID_type ) ;\
	x261_->ag_tag = 9 ;\
	COPY_cv ( x261_ + 1, ( qual_ ) ) ;\
	COPY_id ( x261_ + 2, NULL_id ) ;\
	COPY_type ( x261_ + 3, ( sub_ ) ) ;\
	COPY_nat ( x261_ + 4, ( size_ ) ) ;\
	( c_class_type ) = x261_ ;\
    }

#define DECONS_type_array( qual_, name_, sub_, size_, c_class_type )\
    {\
	c_class *x262_ = CHECK_TAG ( ( c_class_type ), 9 ) ;\
	( qual_ ) = DEREF_cv ( x262_ + 1 ) ;\
	( name_ ) = DEREF_id ( x262_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x262_ + 3 ) ;\
	( size_ ) = DEREF_nat ( x262_ + 4 ) ;\
    }

#define DESTROY_type_array( destroyer_, qual_, name_, sub_, size_, c_class_type )\
    {\
	c_class *x263_ = CHECK_TAG ( ( c_class_type ), 9 ) ;\
	( qual_ ) = DEREF_cv ( x263_ + 1 ) ;\
	( name_ ) = DEREF_id ( x263_ + 2 ) ;\
	( sub_ ) = DEREF_type ( x263_ + 3 ) ;\
	( size_ ) = DEREF_nat ( x263_ + 4 ) ;\
	( destroyer_ ) ( x263_, ( unsigned ) 5 ) ;\
    }


/* Operations for field bitfield of union TYPE */

#define type_bitfield_tag		( ( unsigned ) 10 )
#define IS_type_bitfield( P )		( CHECK_NULL ( P )->ag_tag == 10 )

#define type_bitfield_defn( P )		( CHECK_TAG ( ( P ), 10 ) + 3 )

#define MAKE_type_bitfield( qual_, defn_, c_class_type )\
    {\
	c_class *x264_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x264_->ag_tag = 10 ;\
	COPY_cv ( x264_ + 1, ( qual_ ) ) ;\
	COPY_id ( x264_ + 2, NULL_id ) ;\
	COPY_itype ( x264_ + 3, ( defn_ ) ) ;\
	( c_class_type ) = x264_ ;\
    }

#define DECONS_type_bitfield( qual_, name_, defn_, c_class_type )\
    {\
	c_class *x265_ = CHECK_TAG ( ( c_class_type ), 10 ) ;\
	( qual_ ) = DEREF_cv ( x265_ + 1 ) ;\
	( name_ ) = DEREF_id ( x265_ + 2 ) ;\
	( defn_ ) = DEREF_itype ( x265_ + 3 ) ;\
    }

#define DESTROY_type_bitfield( destroyer_, qual_, name_, defn_, c_class_type )\
    {\
	c_class *x266_ = CHECK_TAG ( ( c_class_type ), 10 ) ;\
	( qual_ ) = DEREF_cv ( x266_ + 1 ) ;\
	( name_ ) = DEREF_id ( x266_ + 2 ) ;\
	( defn_ ) = DEREF_itype ( x266_ + 3 ) ;\
	( destroyer_ ) ( x266_, ( unsigned ) 4 ) ;\
    }


/* Operations for field compound of union TYPE */

#define type_compound_tag		( ( unsigned ) 11 )
#define IS_type_compound( P )		( CHECK_NULL ( P )->ag_tag == 11 )

#define type_compound_defn( P )		( CHECK_TAG ( ( P ), 11 ) + 3 )

#define MAKE_type_compound( qual_, defn_, c_class_type )\
    {\
	c_class *x267_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x267_->ag_tag = 11 ;\
	COPY_cv ( x267_ + 1, ( qual_ ) ) ;\
	COPY_id ( x267_ + 2, NULL_id ) ;\
	COPY_ctype ( x267_ + 3, ( defn_ ) ) ;\
	( c_class_type ) = x267_ ;\
    }

#define DECONS_type_compound( qual_, name_, defn_, c_class_type )\
    {\
	c_class *x268_ = CHECK_TAG ( ( c_class_type ), 11 ) ;\
	( qual_ ) = DEREF_cv ( x268_ + 1 ) ;\
	( name_ ) = DEREF_id ( x268_ + 2 ) ;\
	( defn_ ) = DEREF_ctype ( x268_ + 3 ) ;\
    }

#define DESTROY_type_compound( destroyer_, qual_, name_, defn_, c_class_type )\
    {\
	c_class *x269_ = CHECK_TAG ( ( c_class_type ), 11 ) ;\
	( qual_ ) = DEREF_cv ( x269_ + 1 ) ;\
	( name_ ) = DEREF_id ( x269_ + 2 ) ;\
	( defn_ ) = DEREF_ctype ( x269_ + 3 ) ;\
	( destroyer_ ) ( x269_, ( unsigned ) 4 ) ;\
    }


/* Operations for field enumerate of union TYPE */

#define type_enumerate_tag		( ( unsigned ) 12 )
#define IS_type_enumerate( P )		( CHECK_NULL ( P )->ag_tag == 12 )

#define type_enumerate_defn( P )	( CHECK_TAG ( ( P ), 12 ) + 3 )

#define MAKE_type_enumerate( qual_, defn_, c_class_type )\
    {\
	c_class *x270_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x270_->ag_tag = 12 ;\
	COPY_cv ( x270_ + 1, ( qual_ ) ) ;\
	COPY_id ( x270_ + 2, NULL_id ) ;\
	COPY_etype ( x270_ + 3, ( defn_ ) ) ;\
	( c_class_type ) = x270_ ;\
    }

#define DECONS_type_enumerate( qual_, name_, defn_, c_class_type )\
    {\
	c_class *x271_ = CHECK_TAG ( ( c_class_type ), 12 ) ;\
	( qual_ ) = DEREF_cv ( x271_ + 1 ) ;\
	( name_ ) = DEREF_id ( x271_ + 2 ) ;\
	( defn_ ) = DEREF_etype ( x271_ + 3 ) ;\
    }

#define DESTROY_type_enumerate( destroyer_, qual_, name_, defn_, c_class_type )\
    {\
	c_class *x272_ = CHECK_TAG ( ( c_class_type ), 12 ) ;\
	( qual_ ) = DEREF_cv ( x272_ + 1 ) ;\
	( name_ ) = DEREF_id ( x272_ + 2 ) ;\
	( defn_ ) = DEREF_etype ( x272_ + 3 ) ;\
	( destroyer_ ) ( x272_, ( unsigned ) 4 ) ;\
    }


/* Operations for field token of union TYPE */

#define type_token_tag			( ( unsigned ) 13 )
#define IS_type_token( P )		( CHECK_NULL ( P )->ag_tag == 13 )

#define type_token_tok( P )		( CHECK_TAG ( ( P ), 13 ) + 3 )
#define type_token_args( P )		( CHECK_TAG ( ( P ), 13 ) + 4 )
#define type_token_app( P )		( CHECK_TAG ( ( P ), 13 ) + 5 )

#define MAKE_type_token( qual_, tok_, args_, c_class_type )\
    {\
	c_class *x273_ = GEN_c_class ( 6, TYPEID_type ) ;\
	x273_->ag_tag = 13 ;\
	COPY_cv ( x273_ + 1, ( qual_ ) ) ;\
	COPY_id ( x273_ + 2, NULL_id ) ;\
	COPY_id ( x273_ + 3, ( tok_ ) ) ;\
	COPY_list ( x273_ + 4, ( args_ ) ) ;\
	COPY_inst ( x273_ + 5, NULL_inst ) ;\
	( c_class_type ) = x273_ ;\
    }

#define DECONS_type_token( qual_, name_, tok_, args_, app_, c_class_type )\
    {\
	c_class *x274_ = CHECK_TAG ( ( c_class_type ), 13 ) ;\
	( qual_ ) = DEREF_cv ( x274_ + 1 ) ;\
	( name_ ) = DEREF_id ( x274_ + 2 ) ;\
	( tok_ ) = DEREF_id ( x274_ + 3 ) ;\
	( args_ ) = DEREF_list ( x274_ + 4 ) ;\
	( app_ ) = DEREF_inst ( x274_ + 5 ) ;\
    }

#define DESTROY_type_token( destroyer_, qual_, name_, tok_, args_, app_, c_class_type )\
    {\
	c_class *x275_ = CHECK_TAG ( ( c_class_type ), 13 ) ;\
	( qual_ ) = DEREF_cv ( x275_ + 1 ) ;\
	( name_ ) = DEREF_id ( x275_ + 2 ) ;\
	( tok_ ) = DEREF_id ( x275_ + 3 ) ;\
	( args_ ) = DEREF_list ( x275_ + 4 ) ;\
	( app_ ) = DEREF_inst ( x275_ + 5 ) ;\
	( destroyer_ ) ( x275_, ( unsigned ) 6 ) ;\
    }


/* Operations for field templ of union TYPE */

#define type_templ_tag			( ( unsigned ) 14 )
#define IS_type_templ( P )		( CHECK_NULL ( P )->ag_tag == 14 )

#define type_templ_sort( P )		( CHECK_TAG ( ( P ), 14 ) + 3 )
#define type_templ_defn( P )		( CHECK_TAG ( ( P ), 14 ) + 4 )
#define type_templ_fix( P )		( CHECK_TAG ( ( P ), 14 ) + 5 )

#define MAKE_type_templ( qual_, sort_, defn_, fix_, c_class_type )\
    {\
	c_class *x276_ = GEN_c_class ( 6, TYPEID_type ) ;\
	x276_->ag_tag = 14 ;\
	COPY_cv ( x276_ + 1, ( qual_ ) ) ;\
	COPY_id ( x276_ + 2, NULL_id ) ;\
	COPY_tok ( x276_ + 3, ( sort_ ) ) ;\
	COPY_type ( x276_ + 4, ( defn_ ) ) ;\
	COPY_int ( x276_ + 5, ( fix_ ) ) ;\
	( c_class_type ) = x276_ ;\
    }

#define DECONS_type_templ( qual_, name_, sort_, defn_, fix_, c_class_type )\
    {\
	c_class *x277_ = CHECK_TAG ( ( c_class_type ), 14 ) ;\
	( qual_ ) = DEREF_cv ( x277_ + 1 ) ;\
	( name_ ) = DEREF_id ( x277_ + 2 ) ;\
	( sort_ ) = DEREF_tok ( x277_ + 3 ) ;\
	( defn_ ) = DEREF_type ( x277_ + 4 ) ;\
	( fix_ ) = DEREF_int ( x277_ + 5 ) ;\
    }

#define DESTROY_type_templ( destroyer_, qual_, name_, sort_, defn_, fix_, c_class_type )\
    {\
	c_class *x278_ = CHECK_TAG ( ( c_class_type ), 14 ) ;\
	( qual_ ) = DEREF_cv ( x278_ + 1 ) ;\
	( name_ ) = DEREF_id ( x278_ + 2 ) ;\
	( sort_ ) = DEREF_tok ( x278_ + 3 ) ;\
	( defn_ ) = DEREF_type ( x278_ + 4 ) ;\
	( fix_ ) = DEREF_int ( x278_ + 5 ) ;\
	( destroyer_ ) ( x278_, ( unsigned ) 6 ) ;\
    }


/* Operations for field instance of union TYPE */

#define type_instance_tag		( ( unsigned ) 15 )
#define IS_type_instance( P )		( CHECK_NULL ( P )->ag_tag == 15 )

#define type_instance_id( P )		( CHECK_TAG ( ( P ), 15 ) + 3 )
#define type_instance_access( P )	( CHECK_TAG ( ( P ), 15 ) + 4 )

#define MAKE_type_instance( qual_, id_, access_, c_class_type )\
    {\
	c_class *x279_ = GEN_c_class ( 5, TYPEID_type ) ;\
	x279_->ag_tag = 15 ;\
	COPY_cv ( x279_ + 1, ( qual_ ) ) ;\
	COPY_id ( x279_ + 2, NULL_id ) ;\
	COPY_id ( x279_ + 3, ( id_ ) ) ;\
	COPY_dspec ( x279_ + 4, ( access_ ) ) ;\
	( c_class_type ) = x279_ ;\
    }

#define DECONS_type_instance( qual_, name_, id_, access_, c_class_type )\
    {\
	c_class *x280_ = CHECK_TAG ( ( c_class_type ), 15 ) ;\
	( qual_ ) = DEREF_cv ( x280_ + 1 ) ;\
	( name_ ) = DEREF_id ( x280_ + 2 ) ;\
	( id_ ) = DEREF_id ( x280_ + 3 ) ;\
	( access_ ) = DEREF_dspec ( x280_ + 4 ) ;\
    }

#define DESTROY_type_instance( destroyer_, qual_, name_, id_, access_, c_class_type )\
    {\
	c_class *x281_ = CHECK_TAG ( ( c_class_type ), 15 ) ;\
	( qual_ ) = DEREF_cv ( x281_ + 1 ) ;\
	( name_ ) = DEREF_id ( x281_ + 2 ) ;\
	( id_ ) = DEREF_id ( x281_ + 3 ) ;\
	( access_ ) = DEREF_dspec ( x281_ + 4 ) ;\
	( destroyer_ ) ( x281_, ( unsigned ) 5 ) ;\
    }


/* Operations for field dummy of union TYPE */

#define type_dummy_tag			( ( unsigned ) 16 )
#define IS_type_dummy( P )		( CHECK_NULL ( P )->ag_tag == 16 )

#define type_dummy_tok( P )		( CHECK_TAG ( ( P ), 16 ) + 3 )

#define MAKE_type_dummy( qual_, tok_, c_class_type )\
    {\
	c_class *x282_ = GEN_c_class ( 4, TYPEID_type ) ;\
	x282_->ag_tag = 16 ;\
	COPY_cv ( x282_ + 1, ( qual_ ) ) ;\
	COPY_id ( x282_ + 2, NULL_id ) ;\
	COPY_int ( x282_ + 3, ( tok_ ) ) ;\
	( c_class_type ) = x282_ ;\
    }

#define DECONS_type_dummy( qual_, name_, tok_, c_class_type )\
    {\
	c_class *x283_ = CHECK_TAG ( ( c_class_type ), 16 ) ;\
	( qual_ ) = DEREF_cv ( x283_ + 1 ) ;\
	( name_ ) = DEREF_id ( x283_ + 2 ) ;\
	( tok_ ) = DEREF_int ( x283_ + 3 ) ;\
    }

#define DESTROY_type_dummy( destroyer_, qual_, name_, tok_, c_class_type )\
    {\
	c_class *x284_ = CHECK_TAG ( ( c_class_type ), 16 ) ;\
	( qual_ ) = DEREF_cv ( x284_ + 1 ) ;\
	( name_ ) = DEREF_id ( x284_ + 2 ) ;\
	( tok_ ) = DEREF_int ( x284_ + 3 ) ;\
	( destroyer_ ) ( x284_, ( unsigned ) 4 ) ;\
    }


/* Operations for field error of union TYPE */

#define type_error_tag			( ( unsigned ) 17 )
#define IS_type_error( P )		( CHECK_NULL ( P )->ag_tag == 17 )


#define MAKE_type_error( qual_, c_class_type )\
    {\
	c_class *x285_ = GEN_c_class ( 3, TYPEID_type ) ;\
	x285_->ag_tag = 17 ;\
	COPY_cv ( x285_ + 1, ( qual_ ) ) ;\
	COPY_id ( x285_ + 2, NULL_id ) ;\
	( c_class_type ) = x285_ ;\
    }

#define DECONS_type_error( qual_, name_, c_class_type )\
    {\
	c_class *x286_ = CHECK_TAG ( ( c_class_type ), 17 ) ;\
	( qual_ ) = DEREF_cv ( x286_ + 1 ) ;\
	( name_ ) = DEREF_id ( x286_ + 2 ) ;\
    }

#define DESTROY_type_error( destroyer_, qual_, name_, c_class_type )\
    {\
	c_class *x287_ = CHECK_TAG ( ( c_class_type ), 17 ) ;\
	( qual_ ) = DEREF_cv ( x287_ + 1 ) ;\
	( name_ ) = DEREF_id ( x287_ + 2 ) ;\
	( destroyer_ ) ( x287_, ( unsigned ) 3 ) ;\
    }


#endif
