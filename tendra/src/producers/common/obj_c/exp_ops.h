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

#ifndef EXP_OPS_H_INCLUDED
#define EXP_OPS_H_INCLUDED

/* Operations for union EXP */

#define TAG_exp( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for component type of union EXP */

#define exp_type( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for field set identifier_etc of union EXP */

#define exp_identifier_etc_tag		( ( unsigned ) 4 )
#define IS_exp_identifier_etc( P )	( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 0 ) < ( unsigned ) 4 )

#define exp_identifier_etc_id( P )	( CHECK_TAG_ETC ( ( P ), 0, 4 ) + 2 )
#define exp_identifier_etc_qual( P )	( CHECK_TAG_ETC ( ( P ), 0, 4 ) + 3 )

#define MAKE_exp_identifier_etc( tag, type_, id_, qual_, c_class_exp )\
    {\
	c_class *x486_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x486_->ag_tag = ( tag ) ;\
	COPY_type ( x486_ + 1, ( type_ ) ) ;\
	COPY_id ( x486_ + 2, ( id_ ) ) ;\
	COPY_qual ( x486_ + 3, ( qual_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x486_, 0, 4 ) ;\
    }

#define MODIFY_exp_identifier_etc( tag, c_class_exp )\
    {\
	c_class *x487_ = CHECK_TAG_ETC ( ( c_class_exp ), 0, 4 ) ;\
	x487_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x487_, 0, 4 ) ;\
    }

#define DECONS_exp_identifier_etc( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x488_ = CHECK_TAG_ETC ( ( c_class_exp ), 0, 4 ) ;\
	( type_ ) = DEREF_type ( x488_ + 1 ) ;\
	( id_ ) = DEREF_id ( x488_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x488_ + 3 ) ;\
    }

#define DESTROY_exp_identifier_etc( destroyer_, type_, id_, qual_, c_class_exp )\
    {\
	c_class *x489_ = CHECK_TAG_ETC ( ( c_class_exp ), 0, 4 ) ;\
	( type_ ) = DEREF_type ( x489_ + 1 ) ;\
	( id_ ) = DEREF_id ( x489_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x489_ + 3 ) ;\
	( destroyer_ ) ( x489_, ( unsigned ) 4 ) ;\
    }


/* Operations for field identifier of union EXP */

#define exp_identifier_tag		( ( unsigned ) 0 )
#define IS_exp_identifier( P )		( CHECK_NULL ( P )->ag_tag == 0 )

#define exp_identifier_id( P )		( CHECK_TAG ( ( P ), 0 ) + 2 )
#define exp_identifier_qual( P )	( CHECK_TAG ( ( P ), 0 ) + 3 )

#define MAKE_exp_identifier( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x490_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x490_->ag_tag = 0 ;\
	COPY_type ( x490_ + 1, ( type_ ) ) ;\
	COPY_id ( x490_ + 2, ( id_ ) ) ;\
	COPY_qual ( x490_ + 3, ( qual_ ) ) ;\
	( c_class_exp ) = x490_ ;\
    }

#define DECONS_exp_identifier( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x491_ = CHECK_TAG ( ( c_class_exp ), 0 ) ;\
	( type_ ) = DEREF_type ( x491_ + 1 ) ;\
	( id_ ) = DEREF_id ( x491_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x491_ + 3 ) ;\
    }

#define DESTROY_exp_identifier( destroyer_, type_, id_, qual_, c_class_exp )\
    {\
	c_class *x492_ = CHECK_TAG ( ( c_class_exp ), 0 ) ;\
	( type_ ) = DEREF_type ( x492_ + 1 ) ;\
	( id_ ) = DEREF_id ( x492_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x492_ + 3 ) ;\
	( destroyer_ ) ( x492_, ( unsigned ) 4 ) ;\
    }


/* Operations for field member of union EXP */

#define exp_member_tag			( ( unsigned ) 1 )
#define IS_exp_member( P )		( CHECK_NULL ( P )->ag_tag == 1 )

#define exp_member_id( P )		( CHECK_TAG ( ( P ), 1 ) + 2 )
#define exp_member_qual( P )		( CHECK_TAG ( ( P ), 1 ) + 3 )

#define MAKE_exp_member( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x493_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x493_->ag_tag = 1 ;\
	COPY_type ( x493_ + 1, ( type_ ) ) ;\
	COPY_id ( x493_ + 2, ( id_ ) ) ;\
	COPY_qual ( x493_ + 3, ( qual_ ) ) ;\
	( c_class_exp ) = x493_ ;\
    }

#define DECONS_exp_member( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x494_ = CHECK_TAG ( ( c_class_exp ), 1 ) ;\
	( type_ ) = DEREF_type ( x494_ + 1 ) ;\
	( id_ ) = DEREF_id ( x494_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x494_ + 3 ) ;\
    }

#define DESTROY_exp_member( destroyer_, type_, id_, qual_, c_class_exp )\
    {\
	c_class *x495_ = CHECK_TAG ( ( c_class_exp ), 1 ) ;\
	( type_ ) = DEREF_type ( x495_ + 1 ) ;\
	( id_ ) = DEREF_id ( x495_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x495_ + 3 ) ;\
	( destroyer_ ) ( x495_, ( unsigned ) 4 ) ;\
    }


/* Operations for field ambiguous of union EXP */

#define exp_ambiguous_tag		( ( unsigned ) 2 )
#define IS_exp_ambiguous( P )		( CHECK_NULL ( P )->ag_tag == 2 )

#define exp_ambiguous_id( P )		( CHECK_TAG ( ( P ), 2 ) + 2 )
#define exp_ambiguous_qual( P )		( CHECK_TAG ( ( P ), 2 ) + 3 )

#define MAKE_exp_ambiguous( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x496_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x496_->ag_tag = 2 ;\
	COPY_type ( x496_ + 1, ( type_ ) ) ;\
	COPY_id ( x496_ + 2, ( id_ ) ) ;\
	COPY_qual ( x496_ + 3, ( qual_ ) ) ;\
	( c_class_exp ) = x496_ ;\
    }

#define DECONS_exp_ambiguous( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x497_ = CHECK_TAG ( ( c_class_exp ), 2 ) ;\
	( type_ ) = DEREF_type ( x497_ + 1 ) ;\
	( id_ ) = DEREF_id ( x497_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x497_ + 3 ) ;\
    }

#define DESTROY_exp_ambiguous( destroyer_, type_, id_, qual_, c_class_exp )\
    {\
	c_class *x498_ = CHECK_TAG ( ( c_class_exp ), 2 ) ;\
	( type_ ) = DEREF_type ( x498_ + 1 ) ;\
	( id_ ) = DEREF_id ( x498_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x498_ + 3 ) ;\
	( destroyer_ ) ( x498_, ( unsigned ) 4 ) ;\
    }


/* Operations for field undeclared of union EXP */

#define exp_undeclared_tag		( ( unsigned ) 3 )
#define IS_exp_undeclared( P )		( CHECK_NULL ( P )->ag_tag == 3 )

#define exp_undeclared_id( P )		( CHECK_TAG ( ( P ), 3 ) + 2 )
#define exp_undeclared_qual( P )	( CHECK_TAG ( ( P ), 3 ) + 3 )

#define MAKE_exp_undeclared( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x499_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x499_->ag_tag = 3 ;\
	COPY_type ( x499_ + 1, ( type_ ) ) ;\
	COPY_id ( x499_ + 2, ( id_ ) ) ;\
	COPY_qual ( x499_ + 3, ( qual_ ) ) ;\
	( c_class_exp ) = x499_ ;\
    }

#define DECONS_exp_undeclared( type_, id_, qual_, c_class_exp )\
    {\
	c_class *x500_ = CHECK_TAG ( ( c_class_exp ), 3 ) ;\
	( type_ ) = DEREF_type ( x500_ + 1 ) ;\
	( id_ ) = DEREF_id ( x500_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x500_ + 3 ) ;\
    }

#define DESTROY_exp_undeclared( destroyer_, type_, id_, qual_, c_class_exp )\
    {\
	c_class *x501_ = CHECK_TAG ( ( c_class_exp ), 3 ) ;\
	( type_ ) = DEREF_type ( x501_ + 1 ) ;\
	( id_ ) = DEREF_id ( x501_ + 2 ) ;\
	( qual_ ) = DEREF_qual ( x501_ + 3 ) ;\
	( destroyer_ ) ( x501_, ( unsigned ) 4 ) ;\
    }


/* Operations for field int_lit of union EXP */

#define exp_int_lit_tag			( ( unsigned ) 4 )
#define IS_exp_int_lit( P )		( CHECK_NULL ( P )->ag_tag == 4 )

#define exp_int_lit_nat( P )		( CHECK_TAG ( ( P ), 4 ) + 2 )
#define exp_int_lit_etag( P )		( CHECK_TAG ( ( P ), 4 ) + 3 )

#define MAKE_exp_int_lit( type_, nat_, etag_, c_class_exp )\
    {\
	c_class *x502_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x502_->ag_tag = 4 ;\
	COPY_type ( x502_ + 1, ( type_ ) ) ;\
	COPY_nat ( x502_ + 2, ( nat_ ) ) ;\
	COPY_unsigned ( x502_ + 3, ( etag_ ) ) ;\
	( c_class_exp ) = x502_ ;\
    }

#define DECONS_exp_int_lit( type_, nat_, etag_, c_class_exp )\
    {\
	c_class *x503_ = CHECK_TAG ( ( c_class_exp ), 4 ) ;\
	( type_ ) = DEREF_type ( x503_ + 1 ) ;\
	( nat_ ) = DEREF_nat ( x503_ + 2 ) ;\
	( etag_ ) = DEREF_unsigned ( x503_ + 3 ) ;\
    }

#define DESTROY_exp_int_lit( destroyer_, type_, nat_, etag_, c_class_exp )\
    {\
	c_class *x504_ = CHECK_TAG ( ( c_class_exp ), 4 ) ;\
	( type_ ) = DEREF_type ( x504_ + 1 ) ;\
	( nat_ ) = DEREF_nat ( x504_ + 2 ) ;\
	( etag_ ) = DEREF_unsigned ( x504_ + 3 ) ;\
	( destroyer_ ) ( x504_, ( unsigned ) 4 ) ;\
    }


/* Operations for field float_lit of union EXP */

#define exp_float_lit_tag		( ( unsigned ) 5 )
#define IS_exp_float_lit( P )		( CHECK_NULL ( P )->ag_tag == 5 )

#define exp_float_lit_flt( P )		( CHECK_TAG ( ( P ), 5 ) + 2 )

#define MAKE_exp_float_lit( type_, flt_, c_class_exp )\
    {\
	c_class *x505_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x505_->ag_tag = 5 ;\
	COPY_type ( x505_ + 1, ( type_ ) ) ;\
	COPY_flt ( x505_ + 2, ( flt_ ) ) ;\
	( c_class_exp ) = x505_ ;\
    }

#define DECONS_exp_float_lit( type_, flt_, c_class_exp )\
    {\
	c_class *x506_ = CHECK_TAG ( ( c_class_exp ), 5 ) ;\
	( type_ ) = DEREF_type ( x506_ + 1 ) ;\
	( flt_ ) = DEREF_flt ( x506_ + 2 ) ;\
    }

#define DESTROY_exp_float_lit( destroyer_, type_, flt_, c_class_exp )\
    {\
	c_class *x507_ = CHECK_TAG ( ( c_class_exp ), 5 ) ;\
	( type_ ) = DEREF_type ( x507_ + 1 ) ;\
	( flt_ ) = DEREF_flt ( x507_ + 2 ) ;\
	( destroyer_ ) ( x507_, ( unsigned ) 3 ) ;\
    }


/* Operations for field char_lit of union EXP */

#define exp_char_lit_tag		( ( unsigned ) 6 )
#define IS_exp_char_lit( P )		( CHECK_NULL ( P )->ag_tag == 6 )

#define exp_char_lit_str( P )		( CHECK_TAG ( ( P ), 6 ) + 2 )
#define exp_char_lit_digit( P )		( CHECK_TAG ( ( P ), 6 ) + 3 )

#define MAKE_exp_char_lit( type_, str_, digit_, c_class_exp )\
    {\
	c_class *x508_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x508_->ag_tag = 6 ;\
	COPY_type ( x508_ + 1, ( type_ ) ) ;\
	COPY_str ( x508_ + 2, ( str_ ) ) ;\
	COPY_int ( x508_ + 3, ( digit_ ) ) ;\
	( c_class_exp ) = x508_ ;\
    }

#define DECONS_exp_char_lit( type_, str_, digit_, c_class_exp )\
    {\
	c_class *x509_ = CHECK_TAG ( ( c_class_exp ), 6 ) ;\
	( type_ ) = DEREF_type ( x509_ + 1 ) ;\
	( str_ ) = DEREF_str ( x509_ + 2 ) ;\
	( digit_ ) = DEREF_int ( x509_ + 3 ) ;\
    }

#define DESTROY_exp_char_lit( destroyer_, type_, str_, digit_, c_class_exp )\
    {\
	c_class *x510_ = CHECK_TAG ( ( c_class_exp ), 6 ) ;\
	( type_ ) = DEREF_type ( x510_ + 1 ) ;\
	( str_ ) = DEREF_str ( x510_ + 2 ) ;\
	( digit_ ) = DEREF_int ( x510_ + 3 ) ;\
	( destroyer_ ) ( x510_, ( unsigned ) 4 ) ;\
    }


/* Operations for field string_lit of union EXP */

#define exp_string_lit_tag		( ( unsigned ) 7 )
#define IS_exp_string_lit( P )		( CHECK_NULL ( P )->ag_tag == 7 )

#define exp_string_lit_str( P )		( CHECK_TAG ( ( P ), 7 ) + 2 )

#define MAKE_exp_string_lit( type_, str_, c_class_exp )\
    {\
	c_class *x511_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x511_->ag_tag = 7 ;\
	COPY_type ( x511_ + 1, ( type_ ) ) ;\
	COPY_str ( x511_ + 2, ( str_ ) ) ;\
	( c_class_exp ) = x511_ ;\
    }

#define DECONS_exp_string_lit( type_, str_, c_class_exp )\
    {\
	c_class *x512_ = CHECK_TAG ( ( c_class_exp ), 7 ) ;\
	( type_ ) = DEREF_type ( x512_ + 1 ) ;\
	( str_ ) = DEREF_str ( x512_ + 2 ) ;\
    }

#define DESTROY_exp_string_lit( destroyer_, type_, str_, c_class_exp )\
    {\
	c_class *x513_ = CHECK_TAG ( ( c_class_exp ), 7 ) ;\
	( type_ ) = DEREF_type ( x513_ + 1 ) ;\
	( str_ ) = DEREF_str ( x513_ + 2 ) ;\
	( destroyer_ ) ( x513_, ( unsigned ) 3 ) ;\
    }


/* Operations for field value of union EXP */

#define exp_value_tag			( ( unsigned ) 8 )
#define IS_exp_value( P )		( CHECK_NULL ( P )->ag_tag == 8 )


#define MAKE_exp_value( type_, c_class_exp )\
    {\
	c_class *x514_ = GEN_c_class ( 2, TYPEID_exp ) ;\
	x514_->ag_tag = 8 ;\
	COPY_type ( x514_ + 1, ( type_ ) ) ;\
	( c_class_exp ) = x514_ ;\
    }

#define DECONS_exp_value( type_, c_class_exp )\
    {\
	c_class *x515_ = CHECK_TAG ( ( c_class_exp ), 8 ) ;\
	( type_ ) = DEREF_type ( x515_ + 1 ) ;\
    }

#define DESTROY_exp_value( destroyer_, type_, c_class_exp )\
    {\
	c_class *x516_ = CHECK_TAG ( ( c_class_exp ), 8 ) ;\
	( type_ ) = DEREF_type ( x516_ + 1 ) ;\
	( destroyer_ ) ( x516_, ( unsigned ) 2 ) ;\
    }


/* Operations for field set null_etc of union EXP */

#define exp_null_etc_tag		( ( unsigned ) 11 )
#define IS_exp_null_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 9 ) < ( unsigned ) 2 )


#define MAKE_exp_null_etc( tag, type_, c_class_exp )\
    {\
	c_class *x517_ = GEN_c_class ( 2, TYPEID_exp ) ;\
	x517_->ag_tag = ( tag ) ;\
	COPY_type ( x517_ + 1, ( type_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x517_, 9, 11 ) ;\
    }

#define MODIFY_exp_null_etc( tag, c_class_exp )\
    {\
	c_class *x518_ = CHECK_TAG_ETC ( ( c_class_exp ), 9, 11 ) ;\
	x518_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x518_, 9, 11 ) ;\
    }

#define DECONS_exp_null_etc( type_, c_class_exp )\
    {\
	c_class *x519_ = CHECK_TAG_ETC ( ( c_class_exp ), 9, 11 ) ;\
	( type_ ) = DEREF_type ( x519_ + 1 ) ;\
    }

#define DESTROY_exp_null_etc( destroyer_, type_, c_class_exp )\
    {\
	c_class *x520_ = CHECK_TAG_ETC ( ( c_class_exp ), 9, 11 ) ;\
	( type_ ) = DEREF_type ( x520_ + 1 ) ;\
	( destroyer_ ) ( x520_, ( unsigned ) 2 ) ;\
    }


/* Operations for field null of union EXP */

#define exp_null_tag			( ( unsigned ) 9 )
#define IS_exp_null( P )		( CHECK_NULL ( P )->ag_tag == 9 )


#define MAKE_exp_null( type_, c_class_exp )\
    {\
	c_class *x521_ = GEN_c_class ( 2, TYPEID_exp ) ;\
	x521_->ag_tag = 9 ;\
	COPY_type ( x521_ + 1, ( type_ ) ) ;\
	( c_class_exp ) = x521_ ;\
    }

#define DECONS_exp_null( type_, c_class_exp )\
    {\
	c_class *x522_ = CHECK_TAG ( ( c_class_exp ), 9 ) ;\
	( type_ ) = DEREF_type ( x522_ + 1 ) ;\
    }

#define DESTROY_exp_null( destroyer_, type_, c_class_exp )\
    {\
	c_class *x523_ = CHECK_TAG ( ( c_class_exp ), 9 ) ;\
	( type_ ) = DEREF_type ( x523_ + 1 ) ;\
	( destroyer_ ) ( x523_, ( unsigned ) 2 ) ;\
    }


/* Operations for field zero of union EXP */

#define exp_zero_tag			( ( unsigned ) 10 )
#define IS_exp_zero( P )		( CHECK_NULL ( P )->ag_tag == 10 )


#define MAKE_exp_zero( type_, c_class_exp )\
    {\
	c_class *x524_ = GEN_c_class ( 2, TYPEID_exp ) ;\
	x524_->ag_tag = 10 ;\
	COPY_type ( x524_ + 1, ( type_ ) ) ;\
	( c_class_exp ) = x524_ ;\
    }

#define DECONS_exp_zero( type_, c_class_exp )\
    {\
	c_class *x525_ = CHECK_TAG ( ( c_class_exp ), 10 ) ;\
	( type_ ) = DEREF_type ( x525_ + 1 ) ;\
    }

#define DESTROY_exp_zero( destroyer_, type_, c_class_exp )\
    {\
	c_class *x526_ = CHECK_TAG ( ( c_class_exp ), 10 ) ;\
	( type_ ) = DEREF_type ( x526_ + 1 ) ;\
	( destroyer_ ) ( x526_, ( unsigned ) 2 ) ;\
    }


/* Operations for field set paren_etc of union EXP */

#define exp_paren_etc_tag		( ( unsigned ) 13 )
#define IS_exp_paren_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 11 ) < ( unsigned ) 2 )

#define exp_paren_etc_arg( P )		( CHECK_TAG_ETC ( ( P ), 11, 13 ) + 2 )

#define MAKE_exp_paren_etc( tag, type_, arg_, c_class_exp )\
    {\
	c_class *x527_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x527_->ag_tag = ( tag ) ;\
	COPY_type ( x527_ + 1, ( type_ ) ) ;\
	COPY_exp ( x527_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x527_, 11, 13 ) ;\
    }

#define MODIFY_exp_paren_etc( tag, c_class_exp )\
    {\
	c_class *x528_ = CHECK_TAG_ETC ( ( c_class_exp ), 11, 13 ) ;\
	x528_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x528_, 11, 13 ) ;\
    }

#define DECONS_exp_paren_etc( type_, arg_, c_class_exp )\
    {\
	c_class *x529_ = CHECK_TAG_ETC ( ( c_class_exp ), 11, 13 ) ;\
	( type_ ) = DEREF_type ( x529_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x529_ + 2 ) ;\
    }

#define DESTROY_exp_paren_etc( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x530_ = CHECK_TAG_ETC ( ( c_class_exp ), 11, 13 ) ;\
	( type_ ) = DEREF_type ( x530_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x530_ + 2 ) ;\
	( destroyer_ ) ( x530_, ( unsigned ) 3 ) ;\
    }


/* Operations for field paren of union EXP */

#define exp_paren_tag			( ( unsigned ) 11 )
#define IS_exp_paren( P )		( CHECK_NULL ( P )->ag_tag == 11 )

#define exp_paren_arg( P )		( CHECK_TAG ( ( P ), 11 ) + 2 )

#define MAKE_exp_paren( type_, arg_, c_class_exp )\
    {\
	c_class *x531_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x531_->ag_tag = 11 ;\
	COPY_type ( x531_ + 1, ( type_ ) ) ;\
	COPY_exp ( x531_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x531_ ;\
    }

#define DECONS_exp_paren( type_, arg_, c_class_exp )\
    {\
	c_class *x532_ = CHECK_TAG ( ( c_class_exp ), 11 ) ;\
	( type_ ) = DEREF_type ( x532_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x532_ + 2 ) ;\
    }

#define DESTROY_exp_paren( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x533_ = CHECK_TAG ( ( c_class_exp ), 11 ) ;\
	( type_ ) = DEREF_type ( x533_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x533_ + 2 ) ;\
	( destroyer_ ) ( x533_, ( unsigned ) 3 ) ;\
    }


/* Operations for field copy of union EXP */

#define exp_copy_tag			( ( unsigned ) 12 )
#define IS_exp_copy( P )		( CHECK_NULL ( P )->ag_tag == 12 )

#define exp_copy_arg( P )		( CHECK_TAG ( ( P ), 12 ) + 2 )

#define MAKE_exp_copy( type_, arg_, c_class_exp )\
    {\
	c_class *x534_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x534_->ag_tag = 12 ;\
	COPY_type ( x534_ + 1, ( type_ ) ) ;\
	COPY_exp ( x534_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x534_ ;\
    }

#define DECONS_exp_copy( type_, arg_, c_class_exp )\
    {\
	c_class *x535_ = CHECK_TAG ( ( c_class_exp ), 12 ) ;\
	( type_ ) = DEREF_type ( x535_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x535_ + 2 ) ;\
    }

#define DESTROY_exp_copy( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x536_ = CHECK_TAG ( ( c_class_exp ), 12 ) ;\
	( type_ ) = DEREF_type ( x536_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x536_ + 2 ) ;\
	( destroyer_ ) ( x536_, ( unsigned ) 3 ) ;\
    }


/* Operations for field assign of union EXP */

#define exp_assign_tag			( ( unsigned ) 13 )
#define IS_exp_assign( P )		( CHECK_NULL ( P )->ag_tag == 13 )

#define exp_assign_ref( P )		( CHECK_TAG ( ( P ), 13 ) + 2 )
#define exp_assign_arg( P )		( CHECK_TAG ( ( P ), 13 ) + 3 )

#define MAKE_exp_assign( type_, ref_, arg_, c_class_exp )\
    {\
	c_class *x537_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x537_->ag_tag = 13 ;\
	COPY_type ( x537_ + 1, ( type_ ) ) ;\
	COPY_exp ( x537_ + 2, ( ref_ ) ) ;\
	COPY_exp ( x537_ + 3, ( arg_ ) ) ;\
	( c_class_exp ) = x537_ ;\
    }

#define DECONS_exp_assign( type_, ref_, arg_, c_class_exp )\
    {\
	c_class *x538_ = CHECK_TAG ( ( c_class_exp ), 13 ) ;\
	( type_ ) = DEREF_type ( x538_ + 1 ) ;\
	( ref_ ) = DEREF_exp ( x538_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x538_ + 3 ) ;\
    }

#define DESTROY_exp_assign( destroyer_, type_, ref_, arg_, c_class_exp )\
    {\
	c_class *x539_ = CHECK_TAG ( ( c_class_exp ), 13 ) ;\
	( type_ ) = DEREF_type ( x539_ + 1 ) ;\
	( ref_ ) = DEREF_exp ( x539_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x539_ + 3 ) ;\
	( destroyer_ ) ( x539_, ( unsigned ) 4 ) ;\
    }


/* Operations for field init of union EXP */

#define exp_init_tag			( ( unsigned ) 14 )
#define IS_exp_init( P )		( CHECK_NULL ( P )->ag_tag == 14 )

#define exp_init_id( P )		( CHECK_TAG ( ( P ), 14 ) + 2 )
#define exp_init_arg( P )		( CHECK_TAG ( ( P ), 14 ) + 3 )

#define MAKE_exp_init( type_, id_, arg_, c_class_exp )\
    {\
	c_class *x540_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x540_->ag_tag = 14 ;\
	COPY_type ( x540_ + 1, ( type_ ) ) ;\
	COPY_id ( x540_ + 2, ( id_ ) ) ;\
	COPY_exp ( x540_ + 3, ( arg_ ) ) ;\
	( c_class_exp ) = x540_ ;\
    }

#define DECONS_exp_init( type_, id_, arg_, c_class_exp )\
    {\
	c_class *x541_ = CHECK_TAG ( ( c_class_exp ), 14 ) ;\
	( type_ ) = DEREF_type ( x541_ + 1 ) ;\
	( id_ ) = DEREF_id ( x541_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x541_ + 3 ) ;\
    }

#define DESTROY_exp_init( destroyer_, type_, id_, arg_, c_class_exp )\
    {\
	c_class *x542_ = CHECK_TAG ( ( c_class_exp ), 14 ) ;\
	( type_ ) = DEREF_type ( x542_ + 1 ) ;\
	( id_ ) = DEREF_id ( x542_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x542_ + 3 ) ;\
	( destroyer_ ) ( x542_, ( unsigned ) 4 ) ;\
    }


/* Operations for field preinc of union EXP */

#define exp_preinc_tag			( ( unsigned ) 15 )
#define IS_exp_preinc( P )		( CHECK_NULL ( P )->ag_tag == 15 )

#define exp_preinc_ref( P )		( CHECK_TAG ( ( P ), 15 ) + 2 )
#define exp_preinc_op( P )		( CHECK_TAG ( ( P ), 15 ) + 3 )
#define exp_preinc_becomes( P )		( CHECK_TAG ( ( P ), 15 ) + 4 )

#define MAKE_exp_preinc( type_, ref_, op_, becomes_, c_class_exp )\
    {\
	c_class *x543_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x543_->ag_tag = 15 ;\
	COPY_type ( x543_ + 1, ( type_ ) ) ;\
	COPY_exp ( x543_ + 2, ( ref_ ) ) ;\
	COPY_exp ( x543_ + 3, ( op_ ) ) ;\
	COPY_int ( x543_ + 4, ( becomes_ ) ) ;\
	( c_class_exp ) = x543_ ;\
    }

#define DECONS_exp_preinc( type_, ref_, op_, becomes_, c_class_exp )\
    {\
	c_class *x544_ = CHECK_TAG ( ( c_class_exp ), 15 ) ;\
	( type_ ) = DEREF_type ( x544_ + 1 ) ;\
	( ref_ ) = DEREF_exp ( x544_ + 2 ) ;\
	( op_ ) = DEREF_exp ( x544_ + 3 ) ;\
	( becomes_ ) = DEREF_int ( x544_ + 4 ) ;\
    }

#define DESTROY_exp_preinc( destroyer_, type_, ref_, op_, becomes_, c_class_exp )\
    {\
	c_class *x545_ = CHECK_TAG ( ( c_class_exp ), 15 ) ;\
	( type_ ) = DEREF_type ( x545_ + 1 ) ;\
	( ref_ ) = DEREF_exp ( x545_ + 2 ) ;\
	( op_ ) = DEREF_exp ( x545_ + 3 ) ;\
	( becomes_ ) = DEREF_int ( x545_ + 4 ) ;\
	( destroyer_ ) ( x545_, ( unsigned ) 5 ) ;\
    }


/* Operations for field postinc of union EXP */

#define exp_postinc_tag			( ( unsigned ) 16 )
#define IS_exp_postinc( P )		( CHECK_NULL ( P )->ag_tag == 16 )

#define exp_postinc_ref( P )		( CHECK_TAG ( ( P ), 16 ) + 2 )
#define exp_postinc_value( P )		( CHECK_TAG ( ( P ), 16 ) + 3 )
#define exp_postinc_op( P )		( CHECK_TAG ( ( P ), 16 ) + 4 )

#define MAKE_exp_postinc( type_, ref_, value_, op_, c_class_exp )\
    {\
	c_class *x546_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x546_->ag_tag = 16 ;\
	COPY_type ( x546_ + 1, ( type_ ) ) ;\
	COPY_exp ( x546_ + 2, ( ref_ ) ) ;\
	COPY_exp ( x546_ + 3, ( value_ ) ) ;\
	COPY_exp ( x546_ + 4, ( op_ ) ) ;\
	( c_class_exp ) = x546_ ;\
    }

#define DECONS_exp_postinc( type_, ref_, value_, op_, c_class_exp )\
    {\
	c_class *x547_ = CHECK_TAG ( ( c_class_exp ), 16 ) ;\
	( type_ ) = DEREF_type ( x547_ + 1 ) ;\
	( ref_ ) = DEREF_exp ( x547_ + 2 ) ;\
	( value_ ) = DEREF_exp ( x547_ + 3 ) ;\
	( op_ ) = DEREF_exp ( x547_ + 4 ) ;\
    }

#define DESTROY_exp_postinc( destroyer_, type_, ref_, value_, op_, c_class_exp )\
    {\
	c_class *x548_ = CHECK_TAG ( ( c_class_exp ), 16 ) ;\
	( type_ ) = DEREF_type ( x548_ + 1 ) ;\
	( ref_ ) = DEREF_exp ( x548_ + 2 ) ;\
	( value_ ) = DEREF_exp ( x548_ + 3 ) ;\
	( op_ ) = DEREF_exp ( x548_ + 4 ) ;\
	( destroyer_ ) ( x548_, ( unsigned ) 5 ) ;\
    }


/* Operations for field indir of union EXP */

#define exp_indir_tag			( ( unsigned ) 17 )
#define IS_exp_indir( P )		( CHECK_NULL ( P )->ag_tag == 17 )

#define exp_indir_ptr( P )		( CHECK_TAG ( ( P ), 17 ) + 2 )
#define exp_indir_index( P )		( CHECK_TAG ( ( P ), 17 ) + 3 )

#define MAKE_exp_indir( type_, ptr_, c_class_exp )\
    {\
	c_class *x549_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x549_->ag_tag = 17 ;\
	COPY_type ( x549_ + 1, ( type_ ) ) ;\
	COPY_exp ( x549_ + 2, ( ptr_ ) ) ;\
	COPY_int ( x549_ + 3, 0 ) ;\
	( c_class_exp ) = x549_ ;\
    }

#define DECONS_exp_indir( type_, ptr_, index_, c_class_exp )\
    {\
	c_class *x550_ = CHECK_TAG ( ( c_class_exp ), 17 ) ;\
	( type_ ) = DEREF_type ( x550_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x550_ + 2 ) ;\
	( index_ ) = DEREF_int ( x550_ + 3 ) ;\
    }

#define DESTROY_exp_indir( destroyer_, type_, ptr_, index_, c_class_exp )\
    {\
	c_class *x551_ = CHECK_TAG ( ( c_class_exp ), 17 ) ;\
	( type_ ) = DEREF_type ( x551_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x551_ + 2 ) ;\
	( index_ ) = DEREF_int ( x551_ + 3 ) ;\
	( destroyer_ ) ( x551_, ( unsigned ) 4 ) ;\
    }


/* Operations for field contents of union EXP */

#define exp_contents_tag		( ( unsigned ) 18 )
#define IS_exp_contents( P )		( CHECK_NULL ( P )->ag_tag == 18 )

#define exp_contents_ptr( P )		( CHECK_TAG ( ( P ), 18 ) + 2 )

#define MAKE_exp_contents( type_, ptr_, c_class_exp )\
    {\
	c_class *x552_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x552_->ag_tag = 18 ;\
	COPY_type ( x552_ + 1, ( type_ ) ) ;\
	COPY_exp ( x552_ + 2, ( ptr_ ) ) ;\
	( c_class_exp ) = x552_ ;\
    }

#define DECONS_exp_contents( type_, ptr_, c_class_exp )\
    {\
	c_class *x553_ = CHECK_TAG ( ( c_class_exp ), 18 ) ;\
	( type_ ) = DEREF_type ( x553_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x553_ + 2 ) ;\
    }

#define DESTROY_exp_contents( destroyer_, type_, ptr_, c_class_exp )\
    {\
	c_class *x554_ = CHECK_TAG ( ( c_class_exp ), 18 ) ;\
	( type_ ) = DEREF_type ( x554_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x554_ + 2 ) ;\
	( destroyer_ ) ( x554_, ( unsigned ) 3 ) ;\
    }


/* Operations for field address of union EXP */

#define exp_address_tag			( ( unsigned ) 19 )
#define IS_exp_address( P )		( CHECK_NULL ( P )->ag_tag == 19 )

#define exp_address_arg( P )		( CHECK_TAG ( ( P ), 19 ) + 2 )

#define MAKE_exp_address( type_, arg_, c_class_exp )\
    {\
	c_class *x555_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x555_->ag_tag = 19 ;\
	COPY_type ( x555_ + 1, ( type_ ) ) ;\
	COPY_exp ( x555_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x555_ ;\
    }

#define DECONS_exp_address( type_, arg_, c_class_exp )\
    {\
	c_class *x556_ = CHECK_TAG ( ( c_class_exp ), 19 ) ;\
	( type_ ) = DEREF_type ( x556_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x556_ + 2 ) ;\
    }

#define DESTROY_exp_address( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x557_ = CHECK_TAG ( ( c_class_exp ), 19 ) ;\
	( type_ ) = DEREF_type ( x557_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x557_ + 2 ) ;\
	( destroyer_ ) ( x557_, ( unsigned ) 3 ) ;\
    }


/* Operations for field address_mem of union EXP */

#define exp_address_mem_tag		( ( unsigned ) 20 )
#define IS_exp_address_mem( P )		( CHECK_NULL ( P )->ag_tag == 20 )

#define exp_address_mem_arg( P )	( CHECK_TAG ( ( P ), 20 ) + 2 )
#define exp_address_mem_paren( P )	( CHECK_TAG ( ( P ), 20 ) + 3 )

#define MAKE_exp_address_mem( type_, arg_, paren_, c_class_exp )\
    {\
	c_class *x558_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x558_->ag_tag = 20 ;\
	COPY_type ( x558_ + 1, ( type_ ) ) ;\
	COPY_exp ( x558_ + 2, ( arg_ ) ) ;\
	COPY_int ( x558_ + 3, ( paren_ ) ) ;\
	( c_class_exp ) = x558_ ;\
    }

#define DECONS_exp_address_mem( type_, arg_, paren_, c_class_exp )\
    {\
	c_class *x559_ = CHECK_TAG ( ( c_class_exp ), 20 ) ;\
	( type_ ) = DEREF_type ( x559_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x559_ + 2 ) ;\
	( paren_ ) = DEREF_int ( x559_ + 3 ) ;\
    }

#define DESTROY_exp_address_mem( destroyer_, type_, arg_, paren_, c_class_exp )\
    {\
	c_class *x560_ = CHECK_TAG ( ( c_class_exp ), 20 ) ;\
	( type_ ) = DEREF_type ( x560_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x560_ + 2 ) ;\
	( paren_ ) = DEREF_int ( x560_ + 3 ) ;\
	( destroyer_ ) ( x560_, ( unsigned ) 4 ) ;\
    }


/* Operations for field func of union EXP */

#define exp_func_tag			( ( unsigned ) 21 )
#define IS_exp_func( P )		( CHECK_NULL ( P )->ag_tag == 21 )

#define exp_func_fn( P )		( CHECK_TAG ( ( P ), 21 ) + 2 )
#define exp_func_args( P )		( CHECK_TAG ( ( P ), 21 ) + 3 )
#define exp_func_extra( P )		( CHECK_TAG ( ( P ), 21 ) + 4 )

#define MAKE_exp_func( type_, fn_, args_, c_class_exp )\
    {\
	c_class *x561_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x561_->ag_tag = 21 ;\
	COPY_type ( x561_ + 1, ( type_ ) ) ;\
	COPY_exp ( x561_ + 2, ( fn_ ) ) ;\
	COPY_list ( x561_ + 3, ( args_ ) ) ;\
	COPY_unsigned ( x561_ + 4, 0 ) ;\
	( c_class_exp ) = x561_ ;\
    }

#define DECONS_exp_func( type_, fn_, args_, extra_, c_class_exp )\
    {\
	c_class *x562_ = CHECK_TAG ( ( c_class_exp ), 21 ) ;\
	( type_ ) = DEREF_type ( x562_ + 1 ) ;\
	( fn_ ) = DEREF_exp ( x562_ + 2 ) ;\
	( args_ ) = DEREF_list ( x562_ + 3 ) ;\
	( extra_ ) = DEREF_unsigned ( x562_ + 4 ) ;\
    }

#define DESTROY_exp_func( destroyer_, type_, fn_, args_, extra_, c_class_exp )\
    {\
	c_class *x563_ = CHECK_TAG ( ( c_class_exp ), 21 ) ;\
	( type_ ) = DEREF_type ( x563_ + 1 ) ;\
	( fn_ ) = DEREF_exp ( x563_ + 2 ) ;\
	( args_ ) = DEREF_list ( x563_ + 3 ) ;\
	( extra_ ) = DEREF_unsigned ( x563_ + 4 ) ;\
	( destroyer_ ) ( x563_, ( unsigned ) 5 ) ;\
    }


/* Operations for field func_id of union EXP */

#define exp_func_id_tag			( ( unsigned ) 22 )
#define IS_exp_func_id( P )		( CHECK_NULL ( P )->ag_tag == 22 )

#define exp_func_id_id( P )		( CHECK_TAG ( ( P ), 22 ) + 2 )
#define exp_func_id_args( P )		( CHECK_TAG ( ( P ), 22 ) + 3 )
#define exp_func_id_virt( P )		( CHECK_TAG ( ( P ), 22 ) + 4 )
#define exp_func_id_extra( P )		( CHECK_TAG ( ( P ), 22 ) + 5 )

#define MAKE_exp_func_id( type_, id_, args_, virt_, c_class_exp )\
    {\
	c_class *x564_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x564_->ag_tag = 22 ;\
	COPY_type ( x564_ + 1, ( type_ ) ) ;\
	COPY_id ( x564_ + 2, ( id_ ) ) ;\
	COPY_list ( x564_ + 3, ( args_ ) ) ;\
	COPY_exp ( x564_ + 4, ( virt_ ) ) ;\
	COPY_unsigned ( x564_ + 5, 0 ) ;\
	( c_class_exp ) = x564_ ;\
    }

#define DECONS_exp_func_id( type_, id_, args_, virt_, extra_, c_class_exp )\
    {\
	c_class *x565_ = CHECK_TAG ( ( c_class_exp ), 22 ) ;\
	( type_ ) = DEREF_type ( x565_ + 1 ) ;\
	( id_ ) = DEREF_id ( x565_ + 2 ) ;\
	( args_ ) = DEREF_list ( x565_ + 3 ) ;\
	( virt_ ) = DEREF_exp ( x565_ + 4 ) ;\
	( extra_ ) = DEREF_unsigned ( x565_ + 5 ) ;\
    }

#define DESTROY_exp_func_id( destroyer_, type_, id_, args_, virt_, extra_, c_class_exp )\
    {\
	c_class *x566_ = CHECK_TAG ( ( c_class_exp ), 22 ) ;\
	( type_ ) = DEREF_type ( x566_ + 1 ) ;\
	( id_ ) = DEREF_id ( x566_ + 2 ) ;\
	( args_ ) = DEREF_list ( x566_ + 3 ) ;\
	( virt_ ) = DEREF_exp ( x566_ + 4 ) ;\
	( extra_ ) = DEREF_unsigned ( x566_ + 5 ) ;\
	( destroyer_ ) ( x566_, ( unsigned ) 6 ) ;\
    }


/* Operations for field call of union EXP */

#define exp_call_tag			( ( unsigned ) 23 )
#define IS_exp_call( P )		( CHECK_NULL ( P )->ag_tag == 23 )

#define exp_call_ptr( P )		( CHECK_TAG ( ( P ), 23 ) + 2 )
#define exp_call_arg( P )		( CHECK_TAG ( ( P ), 23 ) + 3 )
#define exp_call_base( P )		( CHECK_TAG ( ( P ), 23 ) + 4 )

#define MAKE_exp_call( type_, ptr_, arg_, base_, c_class_exp )\
    {\
	c_class *x567_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x567_->ag_tag = 23 ;\
	COPY_type ( x567_ + 1, ( type_ ) ) ;\
	COPY_exp ( x567_ + 2, ( ptr_ ) ) ;\
	COPY_exp ( x567_ + 3, ( arg_ ) ) ;\
	COPY_graph ( x567_ + 4, ( base_ ) ) ;\
	( c_class_exp ) = x567_ ;\
    }

#define DECONS_exp_call( type_, ptr_, arg_, base_, c_class_exp )\
    {\
	c_class *x568_ = CHECK_TAG ( ( c_class_exp ), 23 ) ;\
	( type_ ) = DEREF_type ( x568_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x568_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x568_ + 3 ) ;\
	( base_ ) = DEREF_graph ( x568_ + 4 ) ;\
    }

#define DESTROY_exp_call( destroyer_, type_, ptr_, arg_, base_, c_class_exp )\
    {\
	c_class *x569_ = CHECK_TAG ( ( c_class_exp ), 23 ) ;\
	( type_ ) = DEREF_type ( x569_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x569_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x569_ + 3 ) ;\
	( base_ ) = DEREF_graph ( x569_ + 4 ) ;\
	( destroyer_ ) ( x569_, ( unsigned ) 5 ) ;\
    }


/* Operations for field set negate_etc of union EXP */

#define exp_negate_etc_tag		( ( unsigned ) 28 )
#define IS_exp_negate_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 24 ) < ( unsigned ) 4 )

#define exp_negate_etc_arg( P )		( CHECK_TAG_ETC ( ( P ), 24, 28 ) + 2 )

#define MAKE_exp_negate_etc( tag, type_, arg_, c_class_exp )\
    {\
	c_class *x570_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x570_->ag_tag = ( tag ) ;\
	COPY_type ( x570_ + 1, ( type_ ) ) ;\
	COPY_exp ( x570_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x570_, 24, 28 ) ;\
    }

#define MODIFY_exp_negate_etc( tag, c_class_exp )\
    {\
	c_class *x571_ = CHECK_TAG_ETC ( ( c_class_exp ), 24, 28 ) ;\
	x571_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x571_, 24, 28 ) ;\
    }

#define DECONS_exp_negate_etc( type_, arg_, c_class_exp )\
    {\
	c_class *x572_ = CHECK_TAG_ETC ( ( c_class_exp ), 24, 28 ) ;\
	( type_ ) = DEREF_type ( x572_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x572_ + 2 ) ;\
    }

#define DESTROY_exp_negate_etc( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x573_ = CHECK_TAG_ETC ( ( c_class_exp ), 24, 28 ) ;\
	( type_ ) = DEREF_type ( x573_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x573_ + 2 ) ;\
	( destroyer_ ) ( x573_, ( unsigned ) 3 ) ;\
    }


/* Operations for field negate of union EXP */

#define exp_negate_tag			( ( unsigned ) 24 )
#define IS_exp_negate( P )		( CHECK_NULL ( P )->ag_tag == 24 )

#define exp_negate_arg( P )		( CHECK_TAG ( ( P ), 24 ) + 2 )

#define MAKE_exp_negate( type_, arg_, c_class_exp )\
    {\
	c_class *x574_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x574_->ag_tag = 24 ;\
	COPY_type ( x574_ + 1, ( type_ ) ) ;\
	COPY_exp ( x574_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x574_ ;\
    }

#define DECONS_exp_negate( type_, arg_, c_class_exp )\
    {\
	c_class *x575_ = CHECK_TAG ( ( c_class_exp ), 24 ) ;\
	( type_ ) = DEREF_type ( x575_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x575_ + 2 ) ;\
    }

#define DESTROY_exp_negate( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x576_ = CHECK_TAG ( ( c_class_exp ), 24 ) ;\
	( type_ ) = DEREF_type ( x576_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x576_ + 2 ) ;\
	( destroyer_ ) ( x576_, ( unsigned ) 3 ) ;\
    }


/* Operations for field compl of union EXP */

#define exp_compl_tag			( ( unsigned ) 25 )
#define IS_exp_compl( P )		( CHECK_NULL ( P )->ag_tag == 25 )

#define exp_compl_arg( P )		( CHECK_TAG ( ( P ), 25 ) + 2 )

#define MAKE_exp_compl( type_, arg_, c_class_exp )\
    {\
	c_class *x577_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x577_->ag_tag = 25 ;\
	COPY_type ( x577_ + 1, ( type_ ) ) ;\
	COPY_exp ( x577_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x577_ ;\
    }

#define DECONS_exp_compl( type_, arg_, c_class_exp )\
    {\
	c_class *x578_ = CHECK_TAG ( ( c_class_exp ), 25 ) ;\
	( type_ ) = DEREF_type ( x578_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x578_ + 2 ) ;\
    }

#define DESTROY_exp_compl( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x579_ = CHECK_TAG ( ( c_class_exp ), 25 ) ;\
	( type_ ) = DEREF_type ( x579_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x579_ + 2 ) ;\
	( destroyer_ ) ( x579_, ( unsigned ) 3 ) ;\
    }


/* Operations for field not of union EXP */

#define exp_not_tag			( ( unsigned ) 26 )
#define IS_exp_not( P )			( CHECK_NULL ( P )->ag_tag == 26 )

#define exp_not_arg( P )		( CHECK_TAG ( ( P ), 26 ) + 2 )

#define MAKE_exp_not( type_, arg_, c_class_exp )\
    {\
	c_class *x580_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x580_->ag_tag = 26 ;\
	COPY_type ( x580_ + 1, ( type_ ) ) ;\
	COPY_exp ( x580_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x580_ ;\
    }

#define DECONS_exp_not( type_, arg_, c_class_exp )\
    {\
	c_class *x581_ = CHECK_TAG ( ( c_class_exp ), 26 ) ;\
	( type_ ) = DEREF_type ( x581_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x581_ + 2 ) ;\
    }

#define DESTROY_exp_not( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x582_ = CHECK_TAG ( ( c_class_exp ), 26 ) ;\
	( type_ ) = DEREF_type ( x582_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x582_ + 2 ) ;\
	( destroyer_ ) ( x582_, ( unsigned ) 3 ) ;\
    }


/* Operations for field abs of union EXP */

#define exp_abs_tag			( ( unsigned ) 27 )
#define IS_exp_abs( P )			( CHECK_NULL ( P )->ag_tag == 27 )

#define exp_abs_arg( P )		( CHECK_TAG ( ( P ), 27 ) + 2 )

#define MAKE_exp_abs( type_, arg_, c_class_exp )\
    {\
	c_class *x583_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x583_->ag_tag = 27 ;\
	COPY_type ( x583_ + 1, ( type_ ) ) ;\
	COPY_exp ( x583_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x583_ ;\
    }

#define DECONS_exp_abs( type_, arg_, c_class_exp )\
    {\
	c_class *x584_ = CHECK_TAG ( ( c_class_exp ), 27 ) ;\
	( type_ ) = DEREF_type ( x584_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x584_ + 2 ) ;\
    }

#define DESTROY_exp_abs( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x585_ = CHECK_TAG ( ( c_class_exp ), 27 ) ;\
	( type_ ) = DEREF_type ( x585_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x585_ + 2 ) ;\
	( destroyer_ ) ( x585_, ( unsigned ) 3 ) ;\
    }


/* Operations for field set plus_etc of union EXP */

#define exp_plus_etc_tag		( ( unsigned ) 42 )
#define IS_exp_plus_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 28 ) < ( unsigned ) 14 )

#define exp_plus_etc_arg1( P )		( CHECK_TAG_ETC ( ( P ), 28, 42 ) + 2 )
#define exp_plus_etc_arg2( P )		( CHECK_TAG_ETC ( ( P ), 28, 42 ) + 3 )

#define MAKE_exp_plus_etc( tag, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x586_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x586_->ag_tag = ( tag ) ;\
	COPY_type ( x586_ + 1, ( type_ ) ) ;\
	COPY_exp ( x586_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x586_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x586_, 28, 42 ) ;\
    }

#define MODIFY_exp_plus_etc( tag, c_class_exp )\
    {\
	c_class *x587_ = CHECK_TAG_ETC ( ( c_class_exp ), 28, 42 ) ;\
	x587_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x587_, 28, 42 ) ;\
    }

#define DECONS_exp_plus_etc( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x588_ = CHECK_TAG_ETC ( ( c_class_exp ), 28, 42 ) ;\
	( type_ ) = DEREF_type ( x588_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x588_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x588_ + 3 ) ;\
    }

#define DESTROY_exp_plus_etc( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x589_ = CHECK_TAG_ETC ( ( c_class_exp ), 28, 42 ) ;\
	( type_ ) = DEREF_type ( x589_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x589_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x589_ + 3 ) ;\
	( destroyer_ ) ( x589_, ( unsigned ) 4 ) ;\
    }


/* Operations for field plus of union EXP */

#define exp_plus_tag			( ( unsigned ) 28 )
#define IS_exp_plus( P )		( CHECK_NULL ( P )->ag_tag == 28 )

#define exp_plus_arg1( P )		( CHECK_TAG ( ( P ), 28 ) + 2 )
#define exp_plus_arg2( P )		( CHECK_TAG ( ( P ), 28 ) + 3 )

#define MAKE_exp_plus( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x590_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x590_->ag_tag = 28 ;\
	COPY_type ( x590_ + 1, ( type_ ) ) ;\
	COPY_exp ( x590_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x590_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x590_ ;\
    }

#define DECONS_exp_plus( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x591_ = CHECK_TAG ( ( c_class_exp ), 28 ) ;\
	( type_ ) = DEREF_type ( x591_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x591_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x591_ + 3 ) ;\
    }

#define DESTROY_exp_plus( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x592_ = CHECK_TAG ( ( c_class_exp ), 28 ) ;\
	( type_ ) = DEREF_type ( x592_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x592_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x592_ + 3 ) ;\
	( destroyer_ ) ( x592_, ( unsigned ) 4 ) ;\
    }


/* Operations for field minus of union EXP */

#define exp_minus_tag			( ( unsigned ) 29 )
#define IS_exp_minus( P )		( CHECK_NULL ( P )->ag_tag == 29 )

#define exp_minus_arg1( P )		( CHECK_TAG ( ( P ), 29 ) + 2 )
#define exp_minus_arg2( P )		( CHECK_TAG ( ( P ), 29 ) + 3 )

#define MAKE_exp_minus( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x593_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x593_->ag_tag = 29 ;\
	COPY_type ( x593_ + 1, ( type_ ) ) ;\
	COPY_exp ( x593_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x593_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x593_ ;\
    }

#define DECONS_exp_minus( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x594_ = CHECK_TAG ( ( c_class_exp ), 29 ) ;\
	( type_ ) = DEREF_type ( x594_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x594_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x594_ + 3 ) ;\
    }

#define DESTROY_exp_minus( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x595_ = CHECK_TAG ( ( c_class_exp ), 29 ) ;\
	( type_ ) = DEREF_type ( x595_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x595_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x595_ + 3 ) ;\
	( destroyer_ ) ( x595_, ( unsigned ) 4 ) ;\
    }


/* Operations for field mult of union EXP */

#define exp_mult_tag			( ( unsigned ) 30 )
#define IS_exp_mult( P )		( CHECK_NULL ( P )->ag_tag == 30 )

#define exp_mult_arg1( P )		( CHECK_TAG ( ( P ), 30 ) + 2 )
#define exp_mult_arg2( P )		( CHECK_TAG ( ( P ), 30 ) + 3 )

#define MAKE_exp_mult( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x596_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x596_->ag_tag = 30 ;\
	COPY_type ( x596_ + 1, ( type_ ) ) ;\
	COPY_exp ( x596_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x596_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x596_ ;\
    }

#define DECONS_exp_mult( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x597_ = CHECK_TAG ( ( c_class_exp ), 30 ) ;\
	( type_ ) = DEREF_type ( x597_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x597_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x597_ + 3 ) ;\
    }

#define DESTROY_exp_mult( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x598_ = CHECK_TAG ( ( c_class_exp ), 30 ) ;\
	( type_ ) = DEREF_type ( x598_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x598_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x598_ + 3 ) ;\
	( destroyer_ ) ( x598_, ( unsigned ) 4 ) ;\
    }


/* Operations for field div of union EXP */

#define exp_div_tag			( ( unsigned ) 31 )
#define IS_exp_div( P )			( CHECK_NULL ( P )->ag_tag == 31 )

#define exp_div_arg1( P )		( CHECK_TAG ( ( P ), 31 ) + 2 )
#define exp_div_arg2( P )		( CHECK_TAG ( ( P ), 31 ) + 3 )

#define MAKE_exp_div( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x599_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x599_->ag_tag = 31 ;\
	COPY_type ( x599_ + 1, ( type_ ) ) ;\
	COPY_exp ( x599_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x599_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x599_ ;\
    }

#define DECONS_exp_div( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x600_ = CHECK_TAG ( ( c_class_exp ), 31 ) ;\
	( type_ ) = DEREF_type ( x600_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x600_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x600_ + 3 ) ;\
    }

#define DESTROY_exp_div( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x601_ = CHECK_TAG ( ( c_class_exp ), 31 ) ;\
	( type_ ) = DEREF_type ( x601_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x601_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x601_ + 3 ) ;\
	( destroyer_ ) ( x601_, ( unsigned ) 4 ) ;\
    }


/* Operations for field rem of union EXP */

#define exp_rem_tag			( ( unsigned ) 32 )
#define IS_exp_rem( P )			( CHECK_NULL ( P )->ag_tag == 32 )

#define exp_rem_arg1( P )		( CHECK_TAG ( ( P ), 32 ) + 2 )
#define exp_rem_arg2( P )		( CHECK_TAG ( ( P ), 32 ) + 3 )

#define MAKE_exp_rem( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x602_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x602_->ag_tag = 32 ;\
	COPY_type ( x602_ + 1, ( type_ ) ) ;\
	COPY_exp ( x602_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x602_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x602_ ;\
    }

#define DECONS_exp_rem( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x603_ = CHECK_TAG ( ( c_class_exp ), 32 ) ;\
	( type_ ) = DEREF_type ( x603_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x603_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x603_ + 3 ) ;\
    }

#define DESTROY_exp_rem( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x604_ = CHECK_TAG ( ( c_class_exp ), 32 ) ;\
	( type_ ) = DEREF_type ( x604_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x604_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x604_ + 3 ) ;\
	( destroyer_ ) ( x604_, ( unsigned ) 4 ) ;\
    }


/* Operations for field and of union EXP */

#define exp_and_tag			( ( unsigned ) 33 )
#define IS_exp_and( P )			( CHECK_NULL ( P )->ag_tag == 33 )

#define exp_and_arg1( P )		( CHECK_TAG ( ( P ), 33 ) + 2 )
#define exp_and_arg2( P )		( CHECK_TAG ( ( P ), 33 ) + 3 )

#define MAKE_exp_and( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x605_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x605_->ag_tag = 33 ;\
	COPY_type ( x605_ + 1, ( type_ ) ) ;\
	COPY_exp ( x605_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x605_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x605_ ;\
    }

#define DECONS_exp_and( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x606_ = CHECK_TAG ( ( c_class_exp ), 33 ) ;\
	( type_ ) = DEREF_type ( x606_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x606_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x606_ + 3 ) ;\
    }

#define DESTROY_exp_and( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x607_ = CHECK_TAG ( ( c_class_exp ), 33 ) ;\
	( type_ ) = DEREF_type ( x607_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x607_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x607_ + 3 ) ;\
	( destroyer_ ) ( x607_, ( unsigned ) 4 ) ;\
    }


/* Operations for field or of union EXP */

#define exp_or_tag			( ( unsigned ) 34 )
#define IS_exp_or( P )			( CHECK_NULL ( P )->ag_tag == 34 )

#define exp_or_arg1( P )		( CHECK_TAG ( ( P ), 34 ) + 2 )
#define exp_or_arg2( P )		( CHECK_TAG ( ( P ), 34 ) + 3 )

#define MAKE_exp_or( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x608_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x608_->ag_tag = 34 ;\
	COPY_type ( x608_ + 1, ( type_ ) ) ;\
	COPY_exp ( x608_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x608_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x608_ ;\
    }

#define DECONS_exp_or( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x609_ = CHECK_TAG ( ( c_class_exp ), 34 ) ;\
	( type_ ) = DEREF_type ( x609_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x609_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x609_ + 3 ) ;\
    }

#define DESTROY_exp_or( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x610_ = CHECK_TAG ( ( c_class_exp ), 34 ) ;\
	( type_ ) = DEREF_type ( x610_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x610_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x610_ + 3 ) ;\
	( destroyer_ ) ( x610_, ( unsigned ) 4 ) ;\
    }


/* Operations for field xor of union EXP */

#define exp_xor_tag			( ( unsigned ) 35 )
#define IS_exp_xor( P )			( CHECK_NULL ( P )->ag_tag == 35 )

#define exp_xor_arg1( P )		( CHECK_TAG ( ( P ), 35 ) + 2 )
#define exp_xor_arg2( P )		( CHECK_TAG ( ( P ), 35 ) + 3 )

#define MAKE_exp_xor( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x611_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x611_->ag_tag = 35 ;\
	COPY_type ( x611_ + 1, ( type_ ) ) ;\
	COPY_exp ( x611_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x611_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x611_ ;\
    }

#define DECONS_exp_xor( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x612_ = CHECK_TAG ( ( c_class_exp ), 35 ) ;\
	( type_ ) = DEREF_type ( x612_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x612_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x612_ + 3 ) ;\
    }

#define DESTROY_exp_xor( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x613_ = CHECK_TAG ( ( c_class_exp ), 35 ) ;\
	( type_ ) = DEREF_type ( x613_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x613_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x613_ + 3 ) ;\
	( destroyer_ ) ( x613_, ( unsigned ) 4 ) ;\
    }


/* Operations for field log_and of union EXP */

#define exp_log_and_tag			( ( unsigned ) 36 )
#define IS_exp_log_and( P )		( CHECK_NULL ( P )->ag_tag == 36 )

#define exp_log_and_arg1( P )		( CHECK_TAG ( ( P ), 36 ) + 2 )
#define exp_log_and_arg2( P )		( CHECK_TAG ( ( P ), 36 ) + 3 )

#define MAKE_exp_log_and( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x614_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x614_->ag_tag = 36 ;\
	COPY_type ( x614_ + 1, ( type_ ) ) ;\
	COPY_exp ( x614_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x614_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x614_ ;\
    }

#define DECONS_exp_log_and( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x615_ = CHECK_TAG ( ( c_class_exp ), 36 ) ;\
	( type_ ) = DEREF_type ( x615_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x615_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x615_ + 3 ) ;\
    }

#define DESTROY_exp_log_and( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x616_ = CHECK_TAG ( ( c_class_exp ), 36 ) ;\
	( type_ ) = DEREF_type ( x616_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x616_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x616_ + 3 ) ;\
	( destroyer_ ) ( x616_, ( unsigned ) 4 ) ;\
    }


/* Operations for field log_or of union EXP */

#define exp_log_or_tag			( ( unsigned ) 37 )
#define IS_exp_log_or( P )		( CHECK_NULL ( P )->ag_tag == 37 )

#define exp_log_or_arg1( P )		( CHECK_TAG ( ( P ), 37 ) + 2 )
#define exp_log_or_arg2( P )		( CHECK_TAG ( ( P ), 37 ) + 3 )

#define MAKE_exp_log_or( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x617_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x617_->ag_tag = 37 ;\
	COPY_type ( x617_ + 1, ( type_ ) ) ;\
	COPY_exp ( x617_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x617_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x617_ ;\
    }

#define DECONS_exp_log_or( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x618_ = CHECK_TAG ( ( c_class_exp ), 37 ) ;\
	( type_ ) = DEREF_type ( x618_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x618_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x618_ + 3 ) ;\
    }

#define DESTROY_exp_log_or( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x619_ = CHECK_TAG ( ( c_class_exp ), 37 ) ;\
	( type_ ) = DEREF_type ( x619_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x619_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x619_ + 3 ) ;\
	( destroyer_ ) ( x619_, ( unsigned ) 4 ) ;\
    }


/* Operations for field lshift of union EXP */

#define exp_lshift_tag			( ( unsigned ) 38 )
#define IS_exp_lshift( P )		( CHECK_NULL ( P )->ag_tag == 38 )

#define exp_lshift_arg1( P )		( CHECK_TAG ( ( P ), 38 ) + 2 )
#define exp_lshift_arg2( P )		( CHECK_TAG ( ( P ), 38 ) + 3 )

#define MAKE_exp_lshift( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x620_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x620_->ag_tag = 38 ;\
	COPY_type ( x620_ + 1, ( type_ ) ) ;\
	COPY_exp ( x620_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x620_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x620_ ;\
    }

#define DECONS_exp_lshift( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x621_ = CHECK_TAG ( ( c_class_exp ), 38 ) ;\
	( type_ ) = DEREF_type ( x621_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x621_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x621_ + 3 ) ;\
    }

#define DESTROY_exp_lshift( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x622_ = CHECK_TAG ( ( c_class_exp ), 38 ) ;\
	( type_ ) = DEREF_type ( x622_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x622_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x622_ + 3 ) ;\
	( destroyer_ ) ( x622_, ( unsigned ) 4 ) ;\
    }


/* Operations for field rshift of union EXP */

#define exp_rshift_tag			( ( unsigned ) 39 )
#define IS_exp_rshift( P )		( CHECK_NULL ( P )->ag_tag == 39 )

#define exp_rshift_arg1( P )		( CHECK_TAG ( ( P ), 39 ) + 2 )
#define exp_rshift_arg2( P )		( CHECK_TAG ( ( P ), 39 ) + 3 )

#define MAKE_exp_rshift( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x623_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x623_->ag_tag = 39 ;\
	COPY_type ( x623_ + 1, ( type_ ) ) ;\
	COPY_exp ( x623_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x623_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x623_ ;\
    }

#define DECONS_exp_rshift( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x624_ = CHECK_TAG ( ( c_class_exp ), 39 ) ;\
	( type_ ) = DEREF_type ( x624_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x624_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x624_ + 3 ) ;\
    }

#define DESTROY_exp_rshift( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x625_ = CHECK_TAG ( ( c_class_exp ), 39 ) ;\
	( type_ ) = DEREF_type ( x625_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x625_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x625_ + 3 ) ;\
	( destroyer_ ) ( x625_, ( unsigned ) 4 ) ;\
    }


/* Operations for field max of union EXP */

#define exp_max_tag			( ( unsigned ) 40 )
#define IS_exp_max( P )			( CHECK_NULL ( P )->ag_tag == 40 )

#define exp_max_arg1( P )		( CHECK_TAG ( ( P ), 40 ) + 2 )
#define exp_max_arg2( P )		( CHECK_TAG ( ( P ), 40 ) + 3 )

#define MAKE_exp_max( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x626_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x626_->ag_tag = 40 ;\
	COPY_type ( x626_ + 1, ( type_ ) ) ;\
	COPY_exp ( x626_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x626_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x626_ ;\
    }

#define DECONS_exp_max( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x627_ = CHECK_TAG ( ( c_class_exp ), 40 ) ;\
	( type_ ) = DEREF_type ( x627_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x627_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x627_ + 3 ) ;\
    }

#define DESTROY_exp_max( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x628_ = CHECK_TAG ( ( c_class_exp ), 40 ) ;\
	( type_ ) = DEREF_type ( x628_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x628_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x628_ + 3 ) ;\
	( destroyer_ ) ( x628_, ( unsigned ) 4 ) ;\
    }


/* Operations for field min of union EXP */

#define exp_min_tag			( ( unsigned ) 41 )
#define IS_exp_min( P )			( CHECK_NULL ( P )->ag_tag == 41 )

#define exp_min_arg1( P )		( CHECK_TAG ( ( P ), 41 ) + 2 )
#define exp_min_arg2( P )		( CHECK_TAG ( ( P ), 41 ) + 3 )

#define MAKE_exp_min( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x629_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x629_->ag_tag = 41 ;\
	COPY_type ( x629_ + 1, ( type_ ) ) ;\
	COPY_exp ( x629_ + 2, ( arg1_ ) ) ;\
	COPY_exp ( x629_ + 3, ( arg2_ ) ) ;\
	( c_class_exp ) = x629_ ;\
    }

#define DECONS_exp_min( type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x630_ = CHECK_TAG ( ( c_class_exp ), 41 ) ;\
	( type_ ) = DEREF_type ( x630_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x630_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x630_ + 3 ) ;\
    }

#define DESTROY_exp_min( destroyer_, type_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x631_ = CHECK_TAG ( ( c_class_exp ), 41 ) ;\
	( type_ ) = DEREF_type ( x631_ + 1 ) ;\
	( arg1_ ) = DEREF_exp ( x631_ + 2 ) ;\
	( arg2_ ) = DEREF_exp ( x631_ + 3 ) ;\
	( destroyer_ ) ( x631_, ( unsigned ) 4 ) ;\
    }


/* Operations for field test of union EXP */

#define exp_test_tag			( ( unsigned ) 42 )
#define IS_exp_test( P )		( CHECK_NULL ( P )->ag_tag == 42 )

#define exp_test_tst( P )		( CHECK_TAG ( ( P ), 42 ) + 2 )
#define exp_test_arg( P )		( CHECK_TAG ( ( P ), 42 ) + 3 )

#define MAKE_exp_test( type_, tst_, arg_, c_class_exp )\
    {\
	c_class *x632_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x632_->ag_tag = 42 ;\
	COPY_type ( x632_ + 1, ( type_ ) ) ;\
	COPY_ntest ( x632_ + 2, ( tst_ ) ) ;\
	COPY_exp ( x632_ + 3, ( arg_ ) ) ;\
	( c_class_exp ) = x632_ ;\
    }

#define DECONS_exp_test( type_, tst_, arg_, c_class_exp )\
    {\
	c_class *x633_ = CHECK_TAG ( ( c_class_exp ), 42 ) ;\
	( type_ ) = DEREF_type ( x633_ + 1 ) ;\
	( tst_ ) = DEREF_ntest ( x633_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x633_ + 3 ) ;\
    }

#define DESTROY_exp_test( destroyer_, type_, tst_, arg_, c_class_exp )\
    {\
	c_class *x634_ = CHECK_TAG ( ( c_class_exp ), 42 ) ;\
	( type_ ) = DEREF_type ( x634_ + 1 ) ;\
	( tst_ ) = DEREF_ntest ( x634_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x634_ + 3 ) ;\
	( destroyer_ ) ( x634_, ( unsigned ) 4 ) ;\
    }


/* Operations for field compare of union EXP */

#define exp_compare_tag			( ( unsigned ) 43 )
#define IS_exp_compare( P )		( CHECK_NULL ( P )->ag_tag == 43 )

#define exp_compare_tst( P )		( CHECK_TAG ( ( P ), 43 ) + 2 )
#define exp_compare_arg1( P )		( CHECK_TAG ( ( P ), 43 ) + 3 )
#define exp_compare_arg2( P )		( CHECK_TAG ( ( P ), 43 ) + 4 )

#define MAKE_exp_compare( type_, tst_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x635_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x635_->ag_tag = 43 ;\
	COPY_type ( x635_ + 1, ( type_ ) ) ;\
	COPY_ntest ( x635_ + 2, ( tst_ ) ) ;\
	COPY_exp ( x635_ + 3, ( arg1_ ) ) ;\
	COPY_exp ( x635_ + 4, ( arg2_ ) ) ;\
	( c_class_exp ) = x635_ ;\
    }

#define DECONS_exp_compare( type_, tst_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x636_ = CHECK_TAG ( ( c_class_exp ), 43 ) ;\
	( type_ ) = DEREF_type ( x636_ + 1 ) ;\
	( tst_ ) = DEREF_ntest ( x636_ + 2 ) ;\
	( arg1_ ) = DEREF_exp ( x636_ + 3 ) ;\
	( arg2_ ) = DEREF_exp ( x636_ + 4 ) ;\
    }

#define DESTROY_exp_compare( destroyer_, type_, tst_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x637_ = CHECK_TAG ( ( c_class_exp ), 43 ) ;\
	( type_ ) = DEREF_type ( x637_ + 1 ) ;\
	( tst_ ) = DEREF_ntest ( x637_ + 2 ) ;\
	( arg1_ ) = DEREF_exp ( x637_ + 3 ) ;\
	( arg2_ ) = DEREF_exp ( x637_ + 4 ) ;\
	( destroyer_ ) ( x637_, ( unsigned ) 5 ) ;\
    }


/* Operations for field cast of union EXP */

#define exp_cast_tag			( ( unsigned ) 44 )
#define IS_exp_cast( P )		( CHECK_NULL ( P )->ag_tag == 44 )

#define exp_cast_conv( P )		( CHECK_TAG ( ( P ), 44 ) + 2 )
#define exp_cast_arg( P )		( CHECK_TAG ( ( P ), 44 ) + 3 )

#define MAKE_exp_cast( type_, conv_, arg_, c_class_exp )\
    {\
	c_class *x638_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x638_->ag_tag = 44 ;\
	COPY_type ( x638_ + 1, ( type_ ) ) ;\
	COPY_unsigned ( x638_ + 2, ( conv_ ) ) ;\
	COPY_exp ( x638_ + 3, ( arg_ ) ) ;\
	( c_class_exp ) = x638_ ;\
    }

#define DECONS_exp_cast( type_, conv_, arg_, c_class_exp )\
    {\
	c_class *x639_ = CHECK_TAG ( ( c_class_exp ), 44 ) ;\
	( type_ ) = DEREF_type ( x639_ + 1 ) ;\
	( conv_ ) = DEREF_unsigned ( x639_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x639_ + 3 ) ;\
    }

#define DESTROY_exp_cast( destroyer_, type_, conv_, arg_, c_class_exp )\
    {\
	c_class *x640_ = CHECK_TAG ( ( c_class_exp ), 44 ) ;\
	( type_ ) = DEREF_type ( x640_ + 1 ) ;\
	( conv_ ) = DEREF_unsigned ( x640_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x640_ + 3 ) ;\
	( destroyer_ ) ( x640_, ( unsigned ) 4 ) ;\
    }


/* Operations for field base_cast of union EXP */

#define exp_base_cast_tag		( ( unsigned ) 45 )
#define IS_exp_base_cast( P )		( CHECK_NULL ( P )->ag_tag == 45 )

#define exp_base_cast_conv( P )		( CHECK_TAG ( ( P ), 45 ) + 2 )
#define exp_base_cast_arg( P )		( CHECK_TAG ( ( P ), 45 ) + 3 )
#define exp_base_cast_off( P )		( CHECK_TAG ( ( P ), 45 ) + 4 )

#define MAKE_exp_base_cast( type_, conv_, arg_, off_, c_class_exp )\
    {\
	c_class *x641_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x641_->ag_tag = 45 ;\
	COPY_type ( x641_ + 1, ( type_ ) ) ;\
	COPY_unsigned ( x641_ + 2, ( conv_ ) ) ;\
	COPY_exp ( x641_ + 3, ( arg_ ) ) ;\
	COPY_off ( x641_ + 4, ( off_ ) ) ;\
	( c_class_exp ) = x641_ ;\
    }

#define DECONS_exp_base_cast( type_, conv_, arg_, off_, c_class_exp )\
    {\
	c_class *x642_ = CHECK_TAG ( ( c_class_exp ), 45 ) ;\
	( type_ ) = DEREF_type ( x642_ + 1 ) ;\
	( conv_ ) = DEREF_unsigned ( x642_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x642_ + 3 ) ;\
	( off_ ) = DEREF_off ( x642_ + 4 ) ;\
    }

#define DESTROY_exp_base_cast( destroyer_, type_, conv_, arg_, off_, c_class_exp )\
    {\
	c_class *x643_ = CHECK_TAG ( ( c_class_exp ), 45 ) ;\
	( type_ ) = DEREF_type ( x643_ + 1 ) ;\
	( conv_ ) = DEREF_unsigned ( x643_ + 2 ) ;\
	( arg_ ) = DEREF_exp ( x643_ + 3 ) ;\
	( off_ ) = DEREF_off ( x643_ + 4 ) ;\
	( destroyer_ ) ( x643_, ( unsigned ) 5 ) ;\
    }


/* Operations for field dyn_cast of union EXP */

#define exp_dyn_cast_tag		( ( unsigned ) 46 )
#define IS_exp_dyn_cast( P )		( CHECK_NULL ( P )->ag_tag == 46 )

#define exp_dyn_cast_arg( P )		( CHECK_TAG ( ( P ), 46 ) + 2 )
#define exp_dyn_cast_except( P )	( CHECK_TAG ( ( P ), 46 ) + 3 )

#define MAKE_exp_dyn_cast( type_, arg_, except_, c_class_exp )\
    {\
	c_class *x644_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x644_->ag_tag = 46 ;\
	COPY_type ( x644_ + 1, ( type_ ) ) ;\
	COPY_exp ( x644_ + 2, ( arg_ ) ) ;\
	COPY_exp ( x644_ + 3, ( except_ ) ) ;\
	( c_class_exp ) = x644_ ;\
    }

#define DECONS_exp_dyn_cast( type_, arg_, except_, c_class_exp )\
    {\
	c_class *x645_ = CHECK_TAG ( ( c_class_exp ), 46 ) ;\
	( type_ ) = DEREF_type ( x645_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x645_ + 2 ) ;\
	( except_ ) = DEREF_exp ( x645_ + 3 ) ;\
    }

#define DESTROY_exp_dyn_cast( destroyer_, type_, arg_, except_, c_class_exp )\
    {\
	c_class *x646_ = CHECK_TAG ( ( c_class_exp ), 46 ) ;\
	( type_ ) = DEREF_type ( x646_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x646_ + 2 ) ;\
	( except_ ) = DEREF_exp ( x646_ + 3 ) ;\
	( destroyer_ ) ( x646_, ( unsigned ) 4 ) ;\
    }


/* Operations for field add_ptr of union EXP */

#define exp_add_ptr_tag			( ( unsigned ) 47 )
#define IS_exp_add_ptr( P )		( CHECK_NULL ( P )->ag_tag == 47 )

#define exp_add_ptr_ptr( P )		( CHECK_TAG ( ( P ), 47 ) + 2 )
#define exp_add_ptr_off( P )		( CHECK_TAG ( ( P ), 47 ) + 3 )
#define exp_add_ptr_virt( P )		( CHECK_TAG ( ( P ), 47 ) + 4 )

#define MAKE_exp_add_ptr( type_, ptr_, off_, virt_, c_class_exp )\
    {\
	c_class *x647_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x647_->ag_tag = 47 ;\
	COPY_type ( x647_ + 1, ( type_ ) ) ;\
	COPY_exp ( x647_ + 2, ( ptr_ ) ) ;\
	COPY_off ( x647_ + 3, ( off_ ) ) ;\
	COPY_int ( x647_ + 4, ( virt_ ) ) ;\
	( c_class_exp ) = x647_ ;\
    }

#define DECONS_exp_add_ptr( type_, ptr_, off_, virt_, c_class_exp )\
    {\
	c_class *x648_ = CHECK_TAG ( ( c_class_exp ), 47 ) ;\
	( type_ ) = DEREF_type ( x648_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x648_ + 2 ) ;\
	( off_ ) = DEREF_off ( x648_ + 3 ) ;\
	( virt_ ) = DEREF_int ( x648_ + 4 ) ;\
    }

#define DESTROY_exp_add_ptr( destroyer_, type_, ptr_, off_, virt_, c_class_exp )\
    {\
	c_class *x649_ = CHECK_TAG ( ( c_class_exp ), 47 ) ;\
	( type_ ) = DEREF_type ( x649_ + 1 ) ;\
	( ptr_ ) = DEREF_exp ( x649_ + 2 ) ;\
	( off_ ) = DEREF_off ( x649_ + 3 ) ;\
	( virt_ ) = DEREF_int ( x649_ + 4 ) ;\
	( destroyer_ ) ( x649_, ( unsigned ) 5 ) ;\
    }


/* Operations for field offset_size of union EXP */

#define exp_offset_size_tag		( ( unsigned ) 48 )
#define IS_exp_offset_size( P )		( CHECK_NULL ( P )->ag_tag == 48 )

#define exp_offset_size_off( P )	( CHECK_TAG ( ( P ), 48 ) + 2 )
#define exp_offset_size_step( P )	( CHECK_TAG ( ( P ), 48 ) + 3 )
#define exp_offset_size_pad( P )	( CHECK_TAG ( ( P ), 48 ) + 4 )

#define MAKE_exp_offset_size( type_, off_, step_, pad_, c_class_exp )\
    {\
	c_class *x650_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x650_->ag_tag = 48 ;\
	COPY_type ( x650_ + 1, ( type_ ) ) ;\
	COPY_off ( x650_ + 2, ( off_ ) ) ;\
	COPY_type ( x650_ + 3, ( step_ ) ) ;\
	COPY_int ( x650_ + 4, ( pad_ ) ) ;\
	( c_class_exp ) = x650_ ;\
    }

#define DECONS_exp_offset_size( type_, off_, step_, pad_, c_class_exp )\
    {\
	c_class *x651_ = CHECK_TAG ( ( c_class_exp ), 48 ) ;\
	( type_ ) = DEREF_type ( x651_ + 1 ) ;\
	( off_ ) = DEREF_off ( x651_ + 2 ) ;\
	( step_ ) = DEREF_type ( x651_ + 3 ) ;\
	( pad_ ) = DEREF_int ( x651_ + 4 ) ;\
    }

#define DESTROY_exp_offset_size( destroyer_, type_, off_, step_, pad_, c_class_exp )\
    {\
	c_class *x652_ = CHECK_TAG ( ( c_class_exp ), 48 ) ;\
	( type_ ) = DEREF_type ( x652_ + 1 ) ;\
	( off_ ) = DEREF_off ( x652_ + 2 ) ;\
	( step_ ) = DEREF_type ( x652_ + 3 ) ;\
	( pad_ ) = DEREF_int ( x652_ + 4 ) ;\
	( destroyer_ ) ( x652_, ( unsigned ) 5 ) ;\
    }


/* Operations for field constr of union EXP */

#define exp_constr_tag			( ( unsigned ) 49 )
#define IS_exp_constr( P )		( CHECK_NULL ( P )->ag_tag == 49 )

#define exp_constr_call( P )		( CHECK_TAG ( ( P ), 49 ) + 2 )
#define exp_constr_obj( P )		( CHECK_TAG ( ( P ), 49 ) + 3 )
#define exp_constr_alt( P )		( CHECK_TAG ( ( P ), 49 ) + 4 )
#define exp_constr_info( P )		( CHECK_TAG ( ( P ), 49 ) + 5 )

#define MAKE_exp_constr( type_, call_, obj_, alt_, info_, c_class_exp )\
    {\
	c_class *x653_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x653_->ag_tag = 49 ;\
	COPY_type ( x653_ + 1, ( type_ ) ) ;\
	COPY_exp ( x653_ + 2, ( call_ ) ) ;\
	COPY_exp ( x653_ + 3, ( obj_ ) ) ;\
	COPY_exp ( x653_ + 4, ( alt_ ) ) ;\
	COPY_int ( x653_ + 5, ( info_ ) ) ;\
	( c_class_exp ) = x653_ ;\
    }

#define DECONS_exp_constr( type_, call_, obj_, alt_, info_, c_class_exp )\
    {\
	c_class *x654_ = CHECK_TAG ( ( c_class_exp ), 49 ) ;\
	( type_ ) = DEREF_type ( x654_ + 1 ) ;\
	( call_ ) = DEREF_exp ( x654_ + 2 ) ;\
	( obj_ ) = DEREF_exp ( x654_ + 3 ) ;\
	( alt_ ) = DEREF_exp ( x654_ + 4 ) ;\
	( info_ ) = DEREF_int ( x654_ + 5 ) ;\
    }

#define DESTROY_exp_constr( destroyer_, type_, call_, obj_, alt_, info_, c_class_exp )\
    {\
	c_class *x655_ = CHECK_TAG ( ( c_class_exp ), 49 ) ;\
	( type_ ) = DEREF_type ( x655_ + 1 ) ;\
	( call_ ) = DEREF_exp ( x655_ + 2 ) ;\
	( obj_ ) = DEREF_exp ( x655_ + 3 ) ;\
	( alt_ ) = DEREF_exp ( x655_ + 4 ) ;\
	( info_ ) = DEREF_int ( x655_ + 5 ) ;\
	( destroyer_ ) ( x655_, ( unsigned ) 6 ) ;\
    }


/* Operations for field destr of union EXP */

#define exp_destr_tag			( ( unsigned ) 50 )
#define IS_exp_destr( P )		( CHECK_NULL ( P )->ag_tag == 50 )

#define exp_destr_call( P )		( CHECK_TAG ( ( P ), 50 ) + 2 )
#define exp_destr_obj( P )		( CHECK_TAG ( ( P ), 50 ) + 3 )
#define exp_destr_count( P )		( CHECK_TAG ( ( P ), 50 ) + 4 )

#define MAKE_exp_destr( type_, call_, obj_, c_class_exp )\
    {\
	c_class *x656_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x656_->ag_tag = 50 ;\
	COPY_type ( x656_ + 1, ( type_ ) ) ;\
	COPY_exp ( x656_ + 2, ( call_ ) ) ;\
	COPY_exp ( x656_ + 3, ( obj_ ) ) ;\
	COPY_exp ( x656_ + 4, NULL_exp ) ;\
	( c_class_exp ) = x656_ ;\
    }

#define DECONS_exp_destr( type_, call_, obj_, count_, c_class_exp )\
    {\
	c_class *x657_ = CHECK_TAG ( ( c_class_exp ), 50 ) ;\
	( type_ ) = DEREF_type ( x657_ + 1 ) ;\
	( call_ ) = DEREF_exp ( x657_ + 2 ) ;\
	( obj_ ) = DEREF_exp ( x657_ + 3 ) ;\
	( count_ ) = DEREF_exp ( x657_ + 4 ) ;\
    }

#define DESTROY_exp_destr( destroyer_, type_, call_, obj_, count_, c_class_exp )\
    {\
	c_class *x658_ = CHECK_TAG ( ( c_class_exp ), 50 ) ;\
	( type_ ) = DEREF_type ( x658_ + 1 ) ;\
	( call_ ) = DEREF_exp ( x658_ + 2 ) ;\
	( obj_ ) = DEREF_exp ( x658_ + 3 ) ;\
	( count_ ) = DEREF_exp ( x658_ + 4 ) ;\
	( destroyer_ ) ( x658_, ( unsigned ) 5 ) ;\
    }


/* Operations for field alloc of union EXP */

#define exp_alloc_tag			( ( unsigned ) 51 )
#define IS_exp_alloc( P )		( CHECK_NULL ( P )->ag_tag == 51 )

#define exp_alloc_call( P )		( CHECK_TAG ( ( P ), 51 ) + 2 )
#define exp_alloc_init( P )		( CHECK_TAG ( ( P ), 51 ) + 3 )
#define exp_alloc_garbage( P )		( CHECK_TAG ( ( P ), 51 ) + 4 )
#define exp_alloc_size( P )		( CHECK_TAG ( ( P ), 51 ) + 5 )

#define MAKE_exp_alloc( type_, call_, init_, garbage_, size_, c_class_exp )\
    {\
	c_class *x659_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x659_->ag_tag = 51 ;\
	COPY_type ( x659_ + 1, ( type_ ) ) ;\
	COPY_exp ( x659_ + 2, ( call_ ) ) ;\
	COPY_exp ( x659_ + 3, ( init_ ) ) ;\
	COPY_exp ( x659_ + 4, ( garbage_ ) ) ;\
	COPY_exp ( x659_ + 5, ( size_ ) ) ;\
	( c_class_exp ) = x659_ ;\
    }

#define DECONS_exp_alloc( type_, call_, init_, garbage_, size_, c_class_exp )\
    {\
	c_class *x660_ = CHECK_TAG ( ( c_class_exp ), 51 ) ;\
	( type_ ) = DEREF_type ( x660_ + 1 ) ;\
	( call_ ) = DEREF_exp ( x660_ + 2 ) ;\
	( init_ ) = DEREF_exp ( x660_ + 3 ) ;\
	( garbage_ ) = DEREF_exp ( x660_ + 4 ) ;\
	( size_ ) = DEREF_exp ( x660_ + 5 ) ;\
    }

#define DESTROY_exp_alloc( destroyer_, type_, call_, init_, garbage_, size_, c_class_exp )\
    {\
	c_class *x661_ = CHECK_TAG ( ( c_class_exp ), 51 ) ;\
	( type_ ) = DEREF_type ( x661_ + 1 ) ;\
	( call_ ) = DEREF_exp ( x661_ + 2 ) ;\
	( init_ ) = DEREF_exp ( x661_ + 3 ) ;\
	( garbage_ ) = DEREF_exp ( x661_ + 4 ) ;\
	( size_ ) = DEREF_exp ( x661_ + 5 ) ;\
	( destroyer_ ) ( x661_, ( unsigned ) 6 ) ;\
    }


/* Operations for field dealloc of union EXP */

#define exp_dealloc_tag			( ( unsigned ) 52 )
#define IS_exp_dealloc( P )		( CHECK_NULL ( P )->ag_tag == 52 )

#define exp_dealloc_term( P )		( CHECK_TAG ( ( P ), 52 ) + 2 )
#define exp_dealloc_call( P )		( CHECK_TAG ( ( P ), 52 ) + 3 )
#define exp_dealloc_arg( P )		( CHECK_TAG ( ( P ), 52 ) + 4 )
#define exp_dealloc_size( P )		( CHECK_TAG ( ( P ), 52 ) + 5 )

#define MAKE_exp_dealloc( type_, term_, call_, arg_, size_, c_class_exp )\
    {\
	c_class *x662_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x662_->ag_tag = 52 ;\
	COPY_type ( x662_ + 1, ( type_ ) ) ;\
	COPY_exp ( x662_ + 2, ( term_ ) ) ;\
	COPY_exp ( x662_ + 3, ( call_ ) ) ;\
	COPY_exp ( x662_ + 4, ( arg_ ) ) ;\
	COPY_exp ( x662_ + 5, ( size_ ) ) ;\
	( c_class_exp ) = x662_ ;\
    }

#define DECONS_exp_dealloc( type_, term_, call_, arg_, size_, c_class_exp )\
    {\
	c_class *x663_ = CHECK_TAG ( ( c_class_exp ), 52 ) ;\
	( type_ ) = DEREF_type ( x663_ + 1 ) ;\
	( term_ ) = DEREF_exp ( x663_ + 2 ) ;\
	( call_ ) = DEREF_exp ( x663_ + 3 ) ;\
	( arg_ ) = DEREF_exp ( x663_ + 4 ) ;\
	( size_ ) = DEREF_exp ( x663_ + 5 ) ;\
    }

#define DESTROY_exp_dealloc( destroyer_, type_, term_, call_, arg_, size_, c_class_exp )\
    {\
	c_class *x664_ = CHECK_TAG ( ( c_class_exp ), 52 ) ;\
	( type_ ) = DEREF_type ( x664_ + 1 ) ;\
	( term_ ) = DEREF_exp ( x664_ + 2 ) ;\
	( call_ ) = DEREF_exp ( x664_ + 3 ) ;\
	( arg_ ) = DEREF_exp ( x664_ + 4 ) ;\
	( size_ ) = DEREF_exp ( x664_ + 5 ) ;\
	( destroyer_ ) ( x664_, ( unsigned ) 6 ) ;\
    }


/* Operations for field rtti of union EXP */

#define exp_rtti_tag			( ( unsigned ) 53 )
#define IS_exp_rtti( P )		( CHECK_NULL ( P )->ag_tag == 53 )

#define exp_rtti_arg( P )		( CHECK_TAG ( ( P ), 53 ) + 2 )
#define exp_rtti_except( P )		( CHECK_TAG ( ( P ), 53 ) + 3 )
#define exp_rtti_op( P )		( CHECK_TAG ( ( P ), 53 ) + 4 )

#define MAKE_exp_rtti( type_, arg_, except_, op_, c_class_exp )\
    {\
	c_class *x665_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x665_->ag_tag = 53 ;\
	COPY_type ( x665_ + 1, ( type_ ) ) ;\
	COPY_exp ( x665_ + 2, ( arg_ ) ) ;\
	COPY_exp ( x665_ + 3, ( except_ ) ) ;\
	COPY_int ( x665_ + 4, ( op_ ) ) ;\
	( c_class_exp ) = x665_ ;\
    }

#define DECONS_exp_rtti( type_, arg_, except_, op_, c_class_exp )\
    {\
	c_class *x666_ = CHECK_TAG ( ( c_class_exp ), 53 ) ;\
	( type_ ) = DEREF_type ( x666_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x666_ + 2 ) ;\
	( except_ ) = DEREF_exp ( x666_ + 3 ) ;\
	( op_ ) = DEREF_int ( x666_ + 4 ) ;\
    }

#define DESTROY_exp_rtti( destroyer_, type_, arg_, except_, op_, c_class_exp )\
    {\
	c_class *x667_ = CHECK_TAG ( ( c_class_exp ), 53 ) ;\
	( type_ ) = DEREF_type ( x667_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x667_ + 2 ) ;\
	( except_ ) = DEREF_exp ( x667_ + 3 ) ;\
	( op_ ) = DEREF_int ( x667_ + 4 ) ;\
	( destroyer_ ) ( x667_, ( unsigned ) 5 ) ;\
    }


/* Operations for field rtti_type of union EXP */

#define exp_rtti_type_tag		( ( unsigned ) 54 )
#define IS_exp_rtti_type( P )		( CHECK_NULL ( P )->ag_tag == 54 )

#define exp_rtti_type_arg( P )		( CHECK_TAG ( ( P ), 54 ) + 2 )
#define exp_rtti_type_op( P )		( CHECK_TAG ( ( P ), 54 ) + 3 )

#define MAKE_exp_rtti_type( type_, arg_, op_, c_class_exp )\
    {\
	c_class *x668_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x668_->ag_tag = 54 ;\
	COPY_type ( x668_ + 1, ( type_ ) ) ;\
	COPY_type ( x668_ + 2, ( arg_ ) ) ;\
	COPY_int ( x668_ + 3, ( op_ ) ) ;\
	( c_class_exp ) = x668_ ;\
    }

#define DECONS_exp_rtti_type( type_, arg_, op_, c_class_exp )\
    {\
	c_class *x669_ = CHECK_TAG ( ( c_class_exp ), 54 ) ;\
	( type_ ) = DEREF_type ( x669_ + 1 ) ;\
	( arg_ ) = DEREF_type ( x669_ + 2 ) ;\
	( op_ ) = DEREF_int ( x669_ + 3 ) ;\
    }

#define DESTROY_exp_rtti_type( destroyer_, type_, arg_, op_, c_class_exp )\
    {\
	c_class *x670_ = CHECK_TAG ( ( c_class_exp ), 54 ) ;\
	( type_ ) = DEREF_type ( x670_ + 1 ) ;\
	( arg_ ) = DEREF_type ( x670_ + 2 ) ;\
	( op_ ) = DEREF_int ( x670_ + 3 ) ;\
	( destroyer_ ) ( x670_, ( unsigned ) 4 ) ;\
    }


/* Operations for field rtti_no of union EXP */

#define exp_rtti_no_tag			( ( unsigned ) 55 )
#define IS_exp_rtti_no( P )		( CHECK_NULL ( P )->ag_tag == 55 )

#define exp_rtti_no_arg( P )		( CHECK_TAG ( ( P ), 55 ) + 2 )

#define MAKE_exp_rtti_no( type_, arg_, c_class_exp )\
    {\
	c_class *x671_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x671_->ag_tag = 55 ;\
	COPY_type ( x671_ + 1, ( type_ ) ) ;\
	COPY_type ( x671_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x671_ ;\
    }

#define DECONS_exp_rtti_no( type_, arg_, c_class_exp )\
    {\
	c_class *x672_ = CHECK_TAG ( ( c_class_exp ), 55 ) ;\
	( type_ ) = DEREF_type ( x672_ + 1 ) ;\
	( arg_ ) = DEREF_type ( x672_ + 2 ) ;\
    }

#define DESTROY_exp_rtti_no( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x673_ = CHECK_TAG ( ( c_class_exp ), 55 ) ;\
	( type_ ) = DEREF_type ( x673_ + 1 ) ;\
	( arg_ ) = DEREF_type ( x673_ + 2 ) ;\
	( destroyer_ ) ( x673_, ( unsigned ) 3 ) ;\
    }


/* Operations for field dynamic of union EXP */

#define exp_dynamic_tag			( ( unsigned ) 56 )
#define IS_exp_dynamic( P )		( CHECK_NULL ( P )->ag_tag == 56 )

#define exp_dynamic_arg( P )		( CHECK_TAG ( ( P ), 56 ) + 2 )

#define MAKE_exp_dynamic( type_, arg_, c_class_exp )\
    {\
	c_class *x674_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x674_->ag_tag = 56 ;\
	COPY_type ( x674_ + 1, ( type_ ) ) ;\
	COPY_exp ( x674_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x674_ ;\
    }

#define DECONS_exp_dynamic( type_, arg_, c_class_exp )\
    {\
	c_class *x675_ = CHECK_TAG ( ( c_class_exp ), 56 ) ;\
	( type_ ) = DEREF_type ( x675_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x675_ + 2 ) ;\
    }

#define DESTROY_exp_dynamic( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x676_ = CHECK_TAG ( ( c_class_exp ), 56 ) ;\
	( type_ ) = DEREF_type ( x676_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x676_ + 2 ) ;\
	( destroyer_ ) ( x676_, ( unsigned ) 3 ) ;\
    }


/* Operations for field aggregate of union EXP */

#define exp_aggregate_tag		( ( unsigned ) 57 )
#define IS_exp_aggregate( P )		( CHECK_NULL ( P )->ag_tag == 57 )

#define exp_aggregate_args( P )		( CHECK_TAG ( ( P ), 57 ) + 2 )
#define exp_aggregate_offs( P )		( CHECK_TAG ( ( P ), 57 ) + 3 )

#define MAKE_exp_aggregate( type_, args_, offs_, c_class_exp )\
    {\
	c_class *x677_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x677_->ag_tag = 57 ;\
	COPY_type ( x677_ + 1, ( type_ ) ) ;\
	COPY_list ( x677_ + 2, ( args_ ) ) ;\
	COPY_list ( x677_ + 3, ( offs_ ) ) ;\
	( c_class_exp ) = x677_ ;\
    }

#define DECONS_exp_aggregate( type_, args_, offs_, c_class_exp )\
    {\
	c_class *x678_ = CHECK_TAG ( ( c_class_exp ), 57 ) ;\
	( type_ ) = DEREF_type ( x678_ + 1 ) ;\
	( args_ ) = DEREF_list ( x678_ + 2 ) ;\
	( offs_ ) = DEREF_list ( x678_ + 3 ) ;\
    }

#define DESTROY_exp_aggregate( destroyer_, type_, args_, offs_, c_class_exp )\
    {\
	c_class *x679_ = CHECK_TAG ( ( c_class_exp ), 57 ) ;\
	( type_ ) = DEREF_type ( x679_ + 1 ) ;\
	( args_ ) = DEREF_list ( x679_ + 2 ) ;\
	( offs_ ) = DEREF_list ( x679_ + 3 ) ;\
	( destroyer_ ) ( x679_, ( unsigned ) 4 ) ;\
    }


/* Operations for field initialiser of union EXP */

#define exp_initialiser_tag		( ( unsigned ) 58 )
#define IS_exp_initialiser( P )		( CHECK_NULL ( P )->ag_tag == 58 )

#define exp_initialiser_args( P )	( CHECK_TAG ( ( P ), 58 ) + 2 )
#define exp_initialiser_offs( P )	( CHECK_TAG ( ( P ), 58 ) + 3 )
#define exp_initialiser_kind( P )	( CHECK_TAG ( ( P ), 58 ) + 4 )
#define exp_initialiser_virt( P )	( CHECK_TAG ( ( P ), 58 ) + 5 )
#define exp_initialiser_base( P )	( CHECK_TAG ( ( P ), 58 ) + 6 )

#define MAKE_exp_initialiser( type_, args_, offs_, kind_, virt_, base_, c_class_exp )\
    {\
	c_class *x680_ = GEN_c_class ( 7, TYPEID_exp ) ;\
	x680_->ag_tag = 58 ;\
	COPY_type ( x680_ + 1, ( type_ ) ) ;\
	COPY_list ( x680_ + 2, ( args_ ) ) ;\
	COPY_list ( x680_ + 3, ( offs_ ) ) ;\
	COPY_int ( x680_ + 4, ( kind_ ) ) ;\
	COPY_unsigned ( x680_ + 5, ( virt_ ) ) ;\
	COPY_unsigned ( x680_ + 6, ( base_ ) ) ;\
	( c_class_exp ) = x680_ ;\
    }

#define DECONS_exp_initialiser( type_, args_, offs_, kind_, virt_, base_, c_class_exp )\
    {\
	c_class *x681_ = CHECK_TAG ( ( c_class_exp ), 58 ) ;\
	( type_ ) = DEREF_type ( x681_ + 1 ) ;\
	( args_ ) = DEREF_list ( x681_ + 2 ) ;\
	( offs_ ) = DEREF_list ( x681_ + 3 ) ;\
	( kind_ ) = DEREF_int ( x681_ + 4 ) ;\
	( virt_ ) = DEREF_unsigned ( x681_ + 5 ) ;\
	( base_ ) = DEREF_unsigned ( x681_ + 6 ) ;\
    }

#define DESTROY_exp_initialiser( destroyer_, type_, args_, offs_, kind_, virt_, base_, c_class_exp )\
    {\
	c_class *x682_ = CHECK_TAG ( ( c_class_exp ), 58 ) ;\
	( type_ ) = DEREF_type ( x682_ + 1 ) ;\
	( args_ ) = DEREF_list ( x682_ + 2 ) ;\
	( offs_ ) = DEREF_list ( x682_ + 3 ) ;\
	( kind_ ) = DEREF_int ( x682_ + 4 ) ;\
	( virt_ ) = DEREF_unsigned ( x682_ + 5 ) ;\
	( base_ ) = DEREF_unsigned ( x682_ + 6 ) ;\
	( destroyer_ ) ( x682_, ( unsigned ) 7 ) ;\
    }


/* Operations for field nof of union EXP */

#define exp_nof_tag			( ( unsigned ) 59 )
#define IS_exp_nof( P )			( CHECK_NULL ( P )->ag_tag == 59 )

#define exp_nof_start( P )		( CHECK_TAG ( ( P ), 59 ) + 2 )
#define exp_nof_size( P )		( CHECK_TAG ( ( P ), 59 ) + 3 )
#define exp_nof_pad( P )		( CHECK_TAG ( ( P ), 59 ) + 4 )
#define exp_nof_end( P )		( CHECK_TAG ( ( P ), 59 ) + 5 )

#define MAKE_exp_nof( type_, start_, size_, pad_, end_, c_class_exp )\
    {\
	c_class *x683_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x683_->ag_tag = 59 ;\
	COPY_type ( x683_ + 1, ( type_ ) ) ;\
	COPY_exp ( x683_ + 2, ( start_ ) ) ;\
	COPY_nat ( x683_ + 3, ( size_ ) ) ;\
	COPY_exp ( x683_ + 4, ( pad_ ) ) ;\
	COPY_exp ( x683_ + 5, ( end_ ) ) ;\
	( c_class_exp ) = x683_ ;\
    }

#define DECONS_exp_nof( type_, start_, size_, pad_, end_, c_class_exp )\
    {\
	c_class *x684_ = CHECK_TAG ( ( c_class_exp ), 59 ) ;\
	( type_ ) = DEREF_type ( x684_ + 1 ) ;\
	( start_ ) = DEREF_exp ( x684_ + 2 ) ;\
	( size_ ) = DEREF_nat ( x684_ + 3 ) ;\
	( pad_ ) = DEREF_exp ( x684_ + 4 ) ;\
	( end_ ) = DEREF_exp ( x684_ + 5 ) ;\
    }

#define DESTROY_exp_nof( destroyer_, type_, start_, size_, pad_, end_, c_class_exp )\
    {\
	c_class *x685_ = CHECK_TAG ( ( c_class_exp ), 59 ) ;\
	( type_ ) = DEREF_type ( x685_ + 1 ) ;\
	( start_ ) = DEREF_exp ( x685_ + 2 ) ;\
	( size_ ) = DEREF_nat ( x685_ + 3 ) ;\
	( pad_ ) = DEREF_exp ( x685_ + 4 ) ;\
	( end_ ) = DEREF_exp ( x685_ + 5 ) ;\
	( destroyer_ ) ( x685_, ( unsigned ) 6 ) ;\
    }


/* Operations for field comma of union EXP */

#define exp_comma_tag			( ( unsigned ) 60 )
#define IS_exp_comma( P )		( CHECK_NULL ( P )->ag_tag == 60 )

#define exp_comma_args( P )		( CHECK_TAG ( ( P ), 60 ) + 2 )

#define MAKE_exp_comma( type_, args_, c_class_exp )\
    {\
	c_class *x686_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x686_->ag_tag = 60 ;\
	COPY_type ( x686_ + 1, ( type_ ) ) ;\
	COPY_list ( x686_ + 2, ( args_ ) ) ;\
	( c_class_exp ) = x686_ ;\
    }

#define DECONS_exp_comma( type_, args_, c_class_exp )\
    {\
	c_class *x687_ = CHECK_TAG ( ( c_class_exp ), 60 ) ;\
	( type_ ) = DEREF_type ( x687_ + 1 ) ;\
	( args_ ) = DEREF_list ( x687_ + 2 ) ;\
    }

#define DESTROY_exp_comma( destroyer_, type_, args_, c_class_exp )\
    {\
	c_class *x688_ = CHECK_TAG ( ( c_class_exp ), 60 ) ;\
	( type_ ) = DEREF_type ( x688_ + 1 ) ;\
	( args_ ) = DEREF_list ( x688_ + 2 ) ;\
	( destroyer_ ) ( x688_, ( unsigned ) 3 ) ;\
    }


/* Operations for field set set_etc of union EXP */

#define exp_set_etc_tag			( ( unsigned ) 63 )
#define IS_exp_set_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 61 ) < ( unsigned ) 2 )

#define exp_set_etc_arg( P )		( CHECK_TAG_ETC ( ( P ), 61, 63 ) + 2 )

#define MAKE_exp_set_etc( tag, type_, arg_, c_class_exp )\
    {\
	c_class *x689_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x689_->ag_tag = ( tag ) ;\
	COPY_type ( x689_ + 1, ( type_ ) ) ;\
	COPY_exp ( x689_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x689_, 61, 63 ) ;\
    }

#define MODIFY_exp_set_etc( tag, c_class_exp )\
    {\
	c_class *x690_ = CHECK_TAG_ETC ( ( c_class_exp ), 61, 63 ) ;\
	x690_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x690_, 61, 63 ) ;\
    }

#define DECONS_exp_set_etc( type_, arg_, c_class_exp )\
    {\
	c_class *x691_ = CHECK_TAG_ETC ( ( c_class_exp ), 61, 63 ) ;\
	( type_ ) = DEREF_type ( x691_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x691_ + 2 ) ;\
    }

#define DESTROY_exp_set_etc( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x692_ = CHECK_TAG_ETC ( ( c_class_exp ), 61, 63 ) ;\
	( type_ ) = DEREF_type ( x692_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x692_ + 2 ) ;\
	( destroyer_ ) ( x692_, ( unsigned ) 3 ) ;\
    }


/* Operations for field set of union EXP */

#define exp_set_tag			( ( unsigned ) 61 )
#define IS_exp_set( P )			( CHECK_NULL ( P )->ag_tag == 61 )

#define exp_set_arg( P )		( CHECK_TAG ( ( P ), 61 ) + 2 )

#define MAKE_exp_set( type_, arg_, c_class_exp )\
    {\
	c_class *x693_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x693_->ag_tag = 61 ;\
	COPY_type ( x693_ + 1, ( type_ ) ) ;\
	COPY_exp ( x693_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x693_ ;\
    }

#define DECONS_exp_set( type_, arg_, c_class_exp )\
    {\
	c_class *x694_ = CHECK_TAG ( ( c_class_exp ), 61 ) ;\
	( type_ ) = DEREF_type ( x694_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x694_ + 2 ) ;\
    }

#define DESTROY_exp_set( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x695_ = CHECK_TAG ( ( c_class_exp ), 61 ) ;\
	( type_ ) = DEREF_type ( x695_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x695_ + 2 ) ;\
	( destroyer_ ) ( x695_, ( unsigned ) 3 ) ;\
    }


/* Operations for field unused of union EXP */

#define exp_unused_tag			( ( unsigned ) 62 )
#define IS_exp_unused( P )		( CHECK_NULL ( P )->ag_tag == 62 )

#define exp_unused_arg( P )		( CHECK_TAG ( ( P ), 62 ) + 2 )

#define MAKE_exp_unused( type_, arg_, c_class_exp )\
    {\
	c_class *x696_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x696_->ag_tag = 62 ;\
	COPY_type ( x696_ + 1, ( type_ ) ) ;\
	COPY_exp ( x696_ + 2, ( arg_ ) ) ;\
	( c_class_exp ) = x696_ ;\
    }

#define DECONS_exp_unused( type_, arg_, c_class_exp )\
    {\
	c_class *x697_ = CHECK_TAG ( ( c_class_exp ), 62 ) ;\
	( type_ ) = DEREF_type ( x697_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x697_ + 2 ) ;\
    }

#define DESTROY_exp_unused( destroyer_, type_, arg_, c_class_exp )\
    {\
	c_class *x698_ = CHECK_TAG ( ( c_class_exp ), 62 ) ;\
	( type_ ) = DEREF_type ( x698_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x698_ + 2 ) ;\
	( destroyer_ ) ( x698_, ( unsigned ) 3 ) ;\
    }


/* Operations for field set reach_etc of union EXP */

#define exp_reach_etc_tag		( ( unsigned ) 65 )
#define IS_exp_reach_etc( P )		( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 63 ) < ( unsigned ) 2 )

#define exp_reach_etc_parent( P )	( CHECK_TAG_ETC ( ( P ), 63, 65 ) + 2 )
#define exp_reach_etc_body( P )		( CHECK_TAG_ETC ( ( P ), 63, 65 ) + 3 )

#define MAKE_exp_reach_etc( tag, type_, body_, c_class_exp )\
    {\
	c_class *x699_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x699_->ag_tag = ( tag ) ;\
	COPY_type ( x699_ + 1, ( type_ ) ) ;\
	COPY_exp ( x699_ + 2, NULL_exp ) ;\
	COPY_exp ( x699_ + 3, ( body_ ) ) ;\
	( c_class_exp ) = CHECK_TAG_ETC ( x699_, 63, 65 ) ;\
    }

#define MODIFY_exp_reach_etc( tag, c_class_exp )\
    {\
	c_class *x700_ = CHECK_TAG_ETC ( ( c_class_exp ), 63, 65 ) ;\
	x700_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x700_, 63, 65 ) ;\
    }

#define DECONS_exp_reach_etc( type_, parent_, body_, c_class_exp )\
    {\
	c_class *x701_ = CHECK_TAG_ETC ( ( c_class_exp ), 63, 65 ) ;\
	( type_ ) = DEREF_type ( x701_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x701_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x701_ + 3 ) ;\
    }

#define DESTROY_exp_reach_etc( destroyer_, type_, parent_, body_, c_class_exp )\
    {\
	c_class *x702_ = CHECK_TAG_ETC ( ( c_class_exp ), 63, 65 ) ;\
	( type_ ) = DEREF_type ( x702_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x702_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x702_ + 3 ) ;\
	( destroyer_ ) ( x702_, ( unsigned ) 4 ) ;\
    }


/* Operations for field reach of union EXP */

#define exp_reach_tag			( ( unsigned ) 63 )
#define IS_exp_reach( P )		( CHECK_NULL ( P )->ag_tag == 63 )

#define exp_reach_parent( P )		( CHECK_TAG ( ( P ), 63 ) + 2 )
#define exp_reach_body( P )		( CHECK_TAG ( ( P ), 63 ) + 3 )

#define MAKE_exp_reach( type_, body_, c_class_exp )\
    {\
	c_class *x703_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x703_->ag_tag = 63 ;\
	COPY_type ( x703_ + 1, ( type_ ) ) ;\
	COPY_exp ( x703_ + 2, NULL_exp ) ;\
	COPY_exp ( x703_ + 3, ( body_ ) ) ;\
	( c_class_exp ) = x703_ ;\
    }

#define DECONS_exp_reach( type_, parent_, body_, c_class_exp )\
    {\
	c_class *x704_ = CHECK_TAG ( ( c_class_exp ), 63 ) ;\
	( type_ ) = DEREF_type ( x704_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x704_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x704_ + 3 ) ;\
    }

#define DESTROY_exp_reach( destroyer_, type_, parent_, body_, c_class_exp )\
    {\
	c_class *x705_ = CHECK_TAG ( ( c_class_exp ), 63 ) ;\
	( type_ ) = DEREF_type ( x705_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x705_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x705_ + 3 ) ;\
	( destroyer_ ) ( x705_, ( unsigned ) 4 ) ;\
    }


/* Operations for field unreach of union EXP */

#define exp_unreach_tag			( ( unsigned ) 64 )
#define IS_exp_unreach( P )		( CHECK_NULL ( P )->ag_tag == 64 )

#define exp_unreach_parent( P )		( CHECK_TAG ( ( P ), 64 ) + 2 )
#define exp_unreach_body( P )		( CHECK_TAG ( ( P ), 64 ) + 3 )

#define MAKE_exp_unreach( type_, body_, c_class_exp )\
    {\
	c_class *x706_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x706_->ag_tag = 64 ;\
	COPY_type ( x706_ + 1, ( type_ ) ) ;\
	COPY_exp ( x706_ + 2, NULL_exp ) ;\
	COPY_exp ( x706_ + 3, ( body_ ) ) ;\
	( c_class_exp ) = x706_ ;\
    }

#define DECONS_exp_unreach( type_, parent_, body_, c_class_exp )\
    {\
	c_class *x707_ = CHECK_TAG ( ( c_class_exp ), 64 ) ;\
	( type_ ) = DEREF_type ( x707_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x707_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x707_ + 3 ) ;\
    }

#define DESTROY_exp_unreach( destroyer_, type_, parent_, body_, c_class_exp )\
    {\
	c_class *x708_ = CHECK_TAG ( ( c_class_exp ), 64 ) ;\
	( type_ ) = DEREF_type ( x708_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x708_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x708_ + 3 ) ;\
	( destroyer_ ) ( x708_, ( unsigned ) 4 ) ;\
    }


/* Operations for field sequence of union EXP */

#define exp_sequence_tag		( ( unsigned ) 65 )
#define IS_exp_sequence( P )		( CHECK_NULL ( P )->ag_tag == 65 )

#define exp_sequence_parent( P )	( CHECK_TAG ( ( P ), 65 ) + 2 )
#define exp_sequence_first( P )		( CHECK_TAG ( ( P ), 65 ) + 3 )
#define exp_sequence_last( P )		( CHECK_TAG ( ( P ), 65 ) + 4 )
#define exp_sequence_decl( P )		( CHECK_TAG ( ( P ), 65 ) + 5 )
#define exp_sequence_block( P )		( CHECK_TAG ( ( P ), 65 ) + 6 )

#define MAKE_exp_sequence( type_, first_, last_, decl_, block_, c_class_exp )\
    {\
	c_class *x709_ = GEN_c_class ( 7, TYPEID_exp ) ;\
	x709_->ag_tag = 65 ;\
	COPY_type ( x709_ + 1, ( type_ ) ) ;\
	COPY_exp ( x709_ + 2, NULL_exp ) ;\
	COPY_list ( x709_ + 3, ( first_ ) ) ;\
	COPY_list ( x709_ + 4, ( last_ ) ) ;\
	COPY_nspace ( x709_ + 5, ( decl_ ) ) ;\
	COPY_int ( x709_ + 6, ( block_ ) ) ;\
	( c_class_exp ) = x709_ ;\
    }

#define DECONS_exp_sequence( type_, parent_, first_, last_, decl_, block_, c_class_exp )\
    {\
	c_class *x710_ = CHECK_TAG ( ( c_class_exp ), 65 ) ;\
	( type_ ) = DEREF_type ( x710_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x710_ + 2 ) ;\
	( first_ ) = DEREF_list ( x710_ + 3 ) ;\
	( last_ ) = DEREF_list ( x710_ + 4 ) ;\
	( decl_ ) = DEREF_nspace ( x710_ + 5 ) ;\
	( block_ ) = DEREF_int ( x710_ + 6 ) ;\
    }

#define DESTROY_exp_sequence( destroyer_, type_, parent_, first_, last_, decl_, block_, c_class_exp )\
    {\
	c_class *x711_ = CHECK_TAG ( ( c_class_exp ), 65 ) ;\
	( type_ ) = DEREF_type ( x711_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x711_ + 2 ) ;\
	( first_ ) = DEREF_list ( x711_ + 3 ) ;\
	( last_ ) = DEREF_list ( x711_ + 4 ) ;\
	( decl_ ) = DEREF_nspace ( x711_ + 5 ) ;\
	( block_ ) = DEREF_int ( x711_ + 6 ) ;\
	( destroyer_ ) ( x711_, ( unsigned ) 7 ) ;\
    }


/* Operations for field solve_stmt of union EXP */

#define exp_solve_stmt_tag		( ( unsigned ) 66 )
#define IS_exp_solve_stmt( P )		( CHECK_NULL ( P )->ag_tag == 66 )

#define exp_solve_stmt_parent( P )	( CHECK_TAG ( ( P ), 66 ) + 2 )
#define exp_solve_stmt_body( P )	( CHECK_TAG ( ( P ), 66 ) + 3 )
#define exp_solve_stmt_labels( P )	( CHECK_TAG ( ( P ), 66 ) + 4 )
#define exp_solve_stmt_vars( P )	( CHECK_TAG ( ( P ), 66 ) + 5 )

#define MAKE_exp_solve_stmt( type_, body_, c_class_exp )\
    {\
	c_class *x712_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x712_->ag_tag = 66 ;\
	COPY_type ( x712_ + 1, ( type_ ) ) ;\
	COPY_exp ( x712_ + 2, NULL_exp ) ;\
	COPY_exp ( x712_ + 3, ( body_ ) ) ;\
	COPY_list ( x712_ + 4, NULL_list ( IDENTIFIER ) ) ;\
	COPY_list ( x712_ + 5, NULL_list ( IDENTIFIER ) ) ;\
	( c_class_exp ) = x712_ ;\
    }

#define DECONS_exp_solve_stmt( type_, parent_, body_, labels_, vars_, c_class_exp )\
    {\
	c_class *x713_ = CHECK_TAG ( ( c_class_exp ), 66 ) ;\
	( type_ ) = DEREF_type ( x713_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x713_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x713_ + 3 ) ;\
	( labels_ ) = DEREF_list ( x713_ + 4 ) ;\
	( vars_ ) = DEREF_list ( x713_ + 5 ) ;\
    }

#define DESTROY_exp_solve_stmt( destroyer_, type_, parent_, body_, labels_, vars_, c_class_exp )\
    {\
	c_class *x714_ = CHECK_TAG ( ( c_class_exp ), 66 ) ;\
	( type_ ) = DEREF_type ( x714_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x714_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x714_ + 3 ) ;\
	( labels_ ) = DEREF_list ( x714_ + 4 ) ;\
	( vars_ ) = DEREF_list ( x714_ + 5 ) ;\
	( destroyer_ ) ( x714_, ( unsigned ) 6 ) ;\
    }


/* Operations for field decl_stmt of union EXP */

#define exp_decl_stmt_tag		( ( unsigned ) 67 )
#define IS_exp_decl_stmt( P )		( CHECK_NULL ( P )->ag_tag == 67 )

#define exp_decl_stmt_parent( P )	( CHECK_TAG ( ( P ), 67 ) + 2 )
#define exp_decl_stmt_id( P )		( CHECK_TAG ( ( P ), 67 ) + 3 )
#define exp_decl_stmt_body( P )		( CHECK_TAG ( ( P ), 67 ) + 4 )

#define MAKE_exp_decl_stmt( type_, id_, body_, c_class_exp )\
    {\
	c_class *x715_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x715_->ag_tag = 67 ;\
	COPY_type ( x715_ + 1, ( type_ ) ) ;\
	COPY_exp ( x715_ + 2, NULL_exp ) ;\
	COPY_id ( x715_ + 3, ( id_ ) ) ;\
	COPY_exp ( x715_ + 4, ( body_ ) ) ;\
	( c_class_exp ) = x715_ ;\
    }

#define DECONS_exp_decl_stmt( type_, parent_, id_, body_, c_class_exp )\
    {\
	c_class *x716_ = CHECK_TAG ( ( c_class_exp ), 67 ) ;\
	( type_ ) = DEREF_type ( x716_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x716_ + 2 ) ;\
	( id_ ) = DEREF_id ( x716_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x716_ + 4 ) ;\
    }

#define DESTROY_exp_decl_stmt( destroyer_, type_, parent_, id_, body_, c_class_exp )\
    {\
	c_class *x717_ = CHECK_TAG ( ( c_class_exp ), 67 ) ;\
	( type_ ) = DEREF_type ( x717_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x717_ + 2 ) ;\
	( id_ ) = DEREF_id ( x717_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x717_ + 4 ) ;\
	( destroyer_ ) ( x717_, ( unsigned ) 5 ) ;\
    }


/* Operations for field if_stmt of union EXP */

#define exp_if_stmt_tag			( ( unsigned ) 68 )
#define IS_exp_if_stmt( P )		( CHECK_NULL ( P )->ag_tag == 68 )

#define exp_if_stmt_parent( P )		( CHECK_TAG ( ( P ), 68 ) + 2 )
#define exp_if_stmt_cond( P )		( CHECK_TAG ( ( P ), 68 ) + 3 )
#define exp_if_stmt_true_code( P )	( CHECK_TAG ( ( P ), 68 ) + 4 )
#define exp_if_stmt_false_code( P )	( CHECK_TAG ( ( P ), 68 ) + 5 )
#define exp_if_stmt_label( P )		( CHECK_TAG ( ( P ), 68 ) + 6 )

#define MAKE_exp_if_stmt( type_, cond_, true_code_, false_code_, label_, c_class_exp )\
    {\
	c_class *x718_ = GEN_c_class ( 7, TYPEID_exp ) ;\
	x718_->ag_tag = 68 ;\
	COPY_type ( x718_ + 1, ( type_ ) ) ;\
	COPY_exp ( x718_ + 2, NULL_exp ) ;\
	COPY_exp ( x718_ + 3, ( cond_ ) ) ;\
	COPY_exp ( x718_ + 4, ( true_code_ ) ) ;\
	COPY_exp ( x718_ + 5, ( false_code_ ) ) ;\
	COPY_id ( x718_ + 6, ( label_ ) ) ;\
	( c_class_exp ) = x718_ ;\
    }

#define DECONS_exp_if_stmt( type_, parent_, cond_, true_code_, false_code_, label_, c_class_exp )\
    {\
	c_class *x719_ = CHECK_TAG ( ( c_class_exp ), 68 ) ;\
	( type_ ) = DEREF_type ( x719_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x719_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x719_ + 3 ) ;\
	( true_code_ ) = DEREF_exp ( x719_ + 4 ) ;\
	( false_code_ ) = DEREF_exp ( x719_ + 5 ) ;\
	( label_ ) = DEREF_id ( x719_ + 6 ) ;\
    }

#define DESTROY_exp_if_stmt( destroyer_, type_, parent_, cond_, true_code_, false_code_, label_, c_class_exp )\
    {\
	c_class *x720_ = CHECK_TAG ( ( c_class_exp ), 68 ) ;\
	( type_ ) = DEREF_type ( x720_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x720_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x720_ + 3 ) ;\
	( true_code_ ) = DEREF_exp ( x720_ + 4 ) ;\
	( false_code_ ) = DEREF_exp ( x720_ + 5 ) ;\
	( label_ ) = DEREF_id ( x720_ + 6 ) ;\
	( destroyer_ ) ( x720_, ( unsigned ) 7 ) ;\
    }


/* Operations for field while_stmt of union EXP */

#define exp_while_stmt_tag		( ( unsigned ) 69 )
#define IS_exp_while_stmt( P )		( CHECK_NULL ( P )->ag_tag == 69 )

#define exp_while_stmt_parent( P )	( CHECK_TAG ( ( P ), 69 ) + 2 )
#define exp_while_stmt_cond( P )	( CHECK_TAG ( ( P ), 69 ) + 3 )
#define exp_while_stmt_body( P )	( CHECK_TAG ( ( P ), 69 ) + 4 )
#define exp_while_stmt_break_lab( P )	( CHECK_TAG ( ( P ), 69 ) + 5 )
#define exp_while_stmt_cont_lab( P )	( CHECK_TAG ( ( P ), 69 ) + 6 )
#define exp_while_stmt_loop_lab( P )	( CHECK_TAG ( ( P ), 69 ) + 7 )
#define exp_while_stmt_cond_id( P )	( CHECK_TAG ( ( P ), 69 ) + 8 )

#define MAKE_exp_while_stmt( type_, cond_, break_lab_, cont_lab_, loop_lab_, c_class_exp )\
    {\
	c_class *x721_ = GEN_c_class ( 9, TYPEID_exp ) ;\
	x721_->ag_tag = 69 ;\
	COPY_type ( x721_ + 1, ( type_ ) ) ;\
	COPY_exp ( x721_ + 2, NULL_exp ) ;\
	COPY_exp ( x721_ + 3, ( cond_ ) ) ;\
	COPY_exp ( x721_ + 4, NULL_exp ) ;\
	COPY_id ( x721_ + 5, ( break_lab_ ) ) ;\
	COPY_id ( x721_ + 6, ( cont_lab_ ) ) ;\
	COPY_id ( x721_ + 7, ( loop_lab_ ) ) ;\
	COPY_list ( x721_ + 8, NULL_list ( IDENTIFIER ) ) ;\
	( c_class_exp ) = x721_ ;\
    }

#define DECONS_exp_while_stmt( type_, parent_, cond_, body_, break_lab_, cont_lab_, loop_lab_, cond_id_, c_class_exp )\
    {\
	c_class *x722_ = CHECK_TAG ( ( c_class_exp ), 69 ) ;\
	( type_ ) = DEREF_type ( x722_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x722_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x722_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x722_ + 4 ) ;\
	( break_lab_ ) = DEREF_id ( x722_ + 5 ) ;\
	( cont_lab_ ) = DEREF_id ( x722_ + 6 ) ;\
	( loop_lab_ ) = DEREF_id ( x722_ + 7 ) ;\
	( cond_id_ ) = DEREF_list ( x722_ + 8 ) ;\
    }

#define DESTROY_exp_while_stmt( destroyer_, type_, parent_, cond_, body_, break_lab_, cont_lab_, loop_lab_, cond_id_, c_class_exp )\
    {\
	c_class *x723_ = CHECK_TAG ( ( c_class_exp ), 69 ) ;\
	( type_ ) = DEREF_type ( x723_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x723_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x723_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x723_ + 4 ) ;\
	( break_lab_ ) = DEREF_id ( x723_ + 5 ) ;\
	( cont_lab_ ) = DEREF_id ( x723_ + 6 ) ;\
	( loop_lab_ ) = DEREF_id ( x723_ + 7 ) ;\
	( cond_id_ ) = DEREF_list ( x723_ + 8 ) ;\
	( destroyer_ ) ( x723_, ( unsigned ) 9 ) ;\
    }


/* Operations for field do_stmt of union EXP */

#define exp_do_stmt_tag			( ( unsigned ) 70 )
#define IS_exp_do_stmt( P )		( CHECK_NULL ( P )->ag_tag == 70 )

#define exp_do_stmt_parent( P )		( CHECK_TAG ( ( P ), 70 ) + 2 )
#define exp_do_stmt_cond( P )		( CHECK_TAG ( ( P ), 70 ) + 3 )
#define exp_do_stmt_body( P )		( CHECK_TAG ( ( P ), 70 ) + 4 )
#define exp_do_stmt_break_lab( P )	( CHECK_TAG ( ( P ), 70 ) + 5 )
#define exp_do_stmt_cont_lab( P )	( CHECK_TAG ( ( P ), 70 ) + 6 )
#define exp_do_stmt_loop_lab( P )	( CHECK_TAG ( ( P ), 70 ) + 7 )

#define MAKE_exp_do_stmt( type_, cond_, break_lab_, cont_lab_, loop_lab_, c_class_exp )\
    {\
	c_class *x724_ = GEN_c_class ( 8, TYPEID_exp ) ;\
	x724_->ag_tag = 70 ;\
	COPY_type ( x724_ + 1, ( type_ ) ) ;\
	COPY_exp ( x724_ + 2, NULL_exp ) ;\
	COPY_exp ( x724_ + 3, ( cond_ ) ) ;\
	COPY_exp ( x724_ + 4, NULL_exp ) ;\
	COPY_id ( x724_ + 5, ( break_lab_ ) ) ;\
	COPY_id ( x724_ + 6, ( cont_lab_ ) ) ;\
	COPY_id ( x724_ + 7, ( loop_lab_ ) ) ;\
	( c_class_exp ) = x724_ ;\
    }

#define DECONS_exp_do_stmt( type_, parent_, cond_, body_, break_lab_, cont_lab_, loop_lab_, c_class_exp )\
    {\
	c_class *x725_ = CHECK_TAG ( ( c_class_exp ), 70 ) ;\
	( type_ ) = DEREF_type ( x725_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x725_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x725_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x725_ + 4 ) ;\
	( break_lab_ ) = DEREF_id ( x725_ + 5 ) ;\
	( cont_lab_ ) = DEREF_id ( x725_ + 6 ) ;\
	( loop_lab_ ) = DEREF_id ( x725_ + 7 ) ;\
    }

#define DESTROY_exp_do_stmt( destroyer_, type_, parent_, cond_, body_, break_lab_, cont_lab_, loop_lab_, c_class_exp )\
    {\
	c_class *x726_ = CHECK_TAG ( ( c_class_exp ), 70 ) ;\
	( type_ ) = DEREF_type ( x726_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x726_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x726_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x726_ + 4 ) ;\
	( break_lab_ ) = DEREF_id ( x726_ + 5 ) ;\
	( cont_lab_ ) = DEREF_id ( x726_ + 6 ) ;\
	( loop_lab_ ) = DEREF_id ( x726_ + 7 ) ;\
	( destroyer_ ) ( x726_, ( unsigned ) 8 ) ;\
    }


/* Operations for field switch_stmt of union EXP */

#define exp_switch_stmt_tag		( ( unsigned ) 71 )
#define IS_exp_switch_stmt( P )		( CHECK_NULL ( P )->ag_tag == 71 )

#define exp_switch_stmt_parent( P )	( CHECK_TAG ( ( P ), 71 ) + 2 )
#define exp_switch_stmt_control( P )	( CHECK_TAG ( ( P ), 71 ) + 3 )
#define exp_switch_stmt_body( P )	( CHECK_TAG ( ( P ), 71 ) + 4 )
#define exp_switch_stmt_cases( P )	( CHECK_TAG ( ( P ), 71 ) + 5 )
#define exp_switch_stmt_case_labs( P )	( CHECK_TAG ( ( P ), 71 ) + 6 )
#define exp_switch_stmt_default_lab( P )( CHECK_TAG ( ( P ), 71 ) + 7 )
#define exp_switch_stmt_exhaust( P )	( CHECK_TAG ( ( P ), 71 ) + 8 )
#define exp_switch_stmt_break_lab( P )	( CHECK_TAG ( ( P ), 71 ) + 9 )

#define MAKE_exp_switch_stmt( type_, control_, body_, exhaust_, break_lab_, c_class_exp )\
    {\
	c_class *x727_ = GEN_c_class ( 10, TYPEID_exp ) ;\
	x727_->ag_tag = 71 ;\
	COPY_type ( x727_ + 1, ( type_ ) ) ;\
	COPY_exp ( x727_ + 2, NULL_exp ) ;\
	COPY_exp ( x727_ + 3, ( control_ ) ) ;\
	COPY_exp ( x727_ + 4, ( body_ ) ) ;\
	COPY_list ( x727_ + 5, NULL_list ( NAT ) ) ;\
	COPY_list ( x727_ + 6, NULL_list ( IDENTIFIER ) ) ;\
	COPY_id ( x727_ + 7, NULL_id ) ;\
	COPY_int ( x727_ + 8, ( exhaust_ ) ) ;\
	COPY_id ( x727_ + 9, ( break_lab_ ) ) ;\
	( c_class_exp ) = x727_ ;\
    }

#define DECONS_exp_switch_stmt( type_, parent_, control_, body_, cases_, case_labs_, default_lab_, exhaust_, break_lab_, c_class_exp )\
    {\
	c_class *x728_ = CHECK_TAG ( ( c_class_exp ), 71 ) ;\
	( type_ ) = DEREF_type ( x728_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x728_ + 2 ) ;\
	( control_ ) = DEREF_exp ( x728_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x728_ + 4 ) ;\
	( cases_ ) = DEREF_list ( x728_ + 5 ) ;\
	( case_labs_ ) = DEREF_list ( x728_ + 6 ) ;\
	( default_lab_ ) = DEREF_id ( x728_ + 7 ) ;\
	( exhaust_ ) = DEREF_int ( x728_ + 8 ) ;\
	( break_lab_ ) = DEREF_id ( x728_ + 9 ) ;\
    }

#define DESTROY_exp_switch_stmt( destroyer_, type_, parent_, control_, body_, cases_, case_labs_, default_lab_, exhaust_, break_lab_, c_class_exp )\
    {\
	c_class *x729_ = CHECK_TAG ( ( c_class_exp ), 71 ) ;\
	( type_ ) = DEREF_type ( x729_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x729_ + 2 ) ;\
	( control_ ) = DEREF_exp ( x729_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x729_ + 4 ) ;\
	( cases_ ) = DEREF_list ( x729_ + 5 ) ;\
	( case_labs_ ) = DEREF_list ( x729_ + 6 ) ;\
	( default_lab_ ) = DEREF_id ( x729_ + 7 ) ;\
	( exhaust_ ) = DEREF_int ( x729_ + 8 ) ;\
	( break_lab_ ) = DEREF_id ( x729_ + 9 ) ;\
	( destroyer_ ) ( x729_, ( unsigned ) 10 ) ;\
    }


/* Operations for field hash_if of union EXP */

#define exp_hash_if_tag			( ( unsigned ) 72 )
#define IS_exp_hash_if( P )		( CHECK_NULL ( P )->ag_tag == 72 )

#define exp_hash_if_parent( P )		( CHECK_TAG ( ( P ), 72 ) + 2 )
#define exp_hash_if_cond( P )		( CHECK_TAG ( ( P ), 72 ) + 3 )
#define exp_hash_if_true_code( P )	( CHECK_TAG ( ( P ), 72 ) + 4 )
#define exp_hash_if_false_code( P )	( CHECK_TAG ( ( P ), 72 ) + 5 )
#define exp_hash_if_last( P )		( CHECK_TAG ( ( P ), 72 ) + 6 )

#define MAKE_exp_hash_if( type_, cond_, true_code_, false_code_, c_class_exp )\
    {\
	c_class *x730_ = GEN_c_class ( 7, TYPEID_exp ) ;\
	x730_->ag_tag = 72 ;\
	COPY_type ( x730_ + 1, ( type_ ) ) ;\
	COPY_exp ( x730_ + 2, NULL_exp ) ;\
	COPY_exp ( x730_ + 3, ( cond_ ) ) ;\
	COPY_exp ( x730_ + 4, ( true_code_ ) ) ;\
	COPY_exp ( x730_ + 5, ( false_code_ ) ) ;\
	COPY_exp ( x730_ + 6, NULL_exp ) ;\
	( c_class_exp ) = x730_ ;\
    }

#define DECONS_exp_hash_if( type_, parent_, cond_, true_code_, false_code_, last_, c_class_exp )\
    {\
	c_class *x731_ = CHECK_TAG ( ( c_class_exp ), 72 ) ;\
	( type_ ) = DEREF_type ( x731_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x731_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x731_ + 3 ) ;\
	( true_code_ ) = DEREF_exp ( x731_ + 4 ) ;\
	( false_code_ ) = DEREF_exp ( x731_ + 5 ) ;\
	( last_ ) = DEREF_exp ( x731_ + 6 ) ;\
    }

#define DESTROY_exp_hash_if( destroyer_, type_, parent_, cond_, true_code_, false_code_, last_, c_class_exp )\
    {\
	c_class *x732_ = CHECK_TAG ( ( c_class_exp ), 72 ) ;\
	( type_ ) = DEREF_type ( x732_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x732_ + 2 ) ;\
	( cond_ ) = DEREF_exp ( x732_ + 3 ) ;\
	( true_code_ ) = DEREF_exp ( x732_ + 4 ) ;\
	( false_code_ ) = DEREF_exp ( x732_ + 5 ) ;\
	( last_ ) = DEREF_exp ( x732_ + 6 ) ;\
	( destroyer_ ) ( x732_, ( unsigned ) 7 ) ;\
    }


/* Operations for field return_stmt of union EXP */

#define exp_return_stmt_tag		( ( unsigned ) 73 )
#define IS_exp_return_stmt( P )		( CHECK_NULL ( P )->ag_tag == 73 )

#define exp_return_stmt_parent( P )	( CHECK_TAG ( ( P ), 73 ) + 2 )
#define exp_return_stmt_value( P )	( CHECK_TAG ( ( P ), 73 ) + 3 )

#define MAKE_exp_return_stmt( type_, value_, c_class_exp )\
    {\
	c_class *x733_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x733_->ag_tag = 73 ;\
	COPY_type ( x733_ + 1, ( type_ ) ) ;\
	COPY_exp ( x733_ + 2, NULL_exp ) ;\
	COPY_exp ( x733_ + 3, ( value_ ) ) ;\
	( c_class_exp ) = x733_ ;\
    }

#define DECONS_exp_return_stmt( type_, parent_, value_, c_class_exp )\
    {\
	c_class *x734_ = CHECK_TAG ( ( c_class_exp ), 73 ) ;\
	( type_ ) = DEREF_type ( x734_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x734_ + 2 ) ;\
	( value_ ) = DEREF_exp ( x734_ + 3 ) ;\
    }

#define DESTROY_exp_return_stmt( destroyer_, type_, parent_, value_, c_class_exp )\
    {\
	c_class *x735_ = CHECK_TAG ( ( c_class_exp ), 73 ) ;\
	( type_ ) = DEREF_type ( x735_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x735_ + 2 ) ;\
	( value_ ) = DEREF_exp ( x735_ + 3 ) ;\
	( destroyer_ ) ( x735_, ( unsigned ) 4 ) ;\
    }


/* Operations for field goto_stmt of union EXP */

#define exp_goto_stmt_tag		( ( unsigned ) 74 )
#define IS_exp_goto_stmt( P )		( CHECK_NULL ( P )->ag_tag == 74 )

#define exp_goto_stmt_parent( P )	( CHECK_TAG ( ( P ), 74 ) + 2 )
#define exp_goto_stmt_label( P )	( CHECK_TAG ( ( P ), 74 ) + 3 )
#define exp_goto_stmt_join( P )		( CHECK_TAG ( ( P ), 74 ) + 4 )
#define exp_goto_stmt_next( P )		( CHECK_TAG ( ( P ), 74 ) + 5 )

#define MAKE_exp_goto_stmt( type_, label_, join_, next_, c_class_exp )\
    {\
	c_class *x736_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x736_->ag_tag = 74 ;\
	COPY_type ( x736_ + 1, ( type_ ) ) ;\
	COPY_exp ( x736_ + 2, NULL_exp ) ;\
	COPY_id ( x736_ + 3, ( label_ ) ) ;\
	COPY_exp ( x736_ + 4, ( join_ ) ) ;\
	COPY_exp ( x736_ + 5, ( next_ ) ) ;\
	( c_class_exp ) = x736_ ;\
    }

#define DECONS_exp_goto_stmt( type_, parent_, label_, join_, next_, c_class_exp )\
    {\
	c_class *x737_ = CHECK_TAG ( ( c_class_exp ), 74 ) ;\
	( type_ ) = DEREF_type ( x737_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x737_ + 2 ) ;\
	( label_ ) = DEREF_id ( x737_ + 3 ) ;\
	( join_ ) = DEREF_exp ( x737_ + 4 ) ;\
	( next_ ) = DEREF_exp ( x737_ + 5 ) ;\
    }

#define DESTROY_exp_goto_stmt( destroyer_, type_, parent_, label_, join_, next_, c_class_exp )\
    {\
	c_class *x738_ = CHECK_TAG ( ( c_class_exp ), 74 ) ;\
	( type_ ) = DEREF_type ( x738_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x738_ + 2 ) ;\
	( label_ ) = DEREF_id ( x738_ + 3 ) ;\
	( join_ ) = DEREF_exp ( x738_ + 4 ) ;\
	( next_ ) = DEREF_exp ( x738_ + 5 ) ;\
	( destroyer_ ) ( x738_, ( unsigned ) 6 ) ;\
    }


/* Operations for field label_stmt of union EXP */

#define exp_label_stmt_tag		( ( unsigned ) 75 )
#define IS_exp_label_stmt( P )		( CHECK_NULL ( P )->ag_tag == 75 )

#define exp_label_stmt_parent( P )	( CHECK_TAG ( ( P ), 75 ) + 2 )
#define exp_label_stmt_label( P )	( CHECK_TAG ( ( P ), 75 ) + 3 )
#define exp_label_stmt_body( P )	( CHECK_TAG ( ( P ), 75 ) + 4 )
#define exp_label_stmt_next( P )	( CHECK_TAG ( ( P ), 75 ) + 5 )

#define MAKE_exp_label_stmt( type_, label_, body_, c_class_exp )\
    {\
	c_class *x739_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x739_->ag_tag = 75 ;\
	COPY_type ( x739_ + 1, ( type_ ) ) ;\
	COPY_exp ( x739_ + 2, NULL_exp ) ;\
	COPY_id ( x739_ + 3, ( label_ ) ) ;\
	COPY_exp ( x739_ + 4, ( body_ ) ) ;\
	COPY_id ( x739_ + 5, NULL_id ) ;\
	( c_class_exp ) = x739_ ;\
    }

#define DECONS_exp_label_stmt( type_, parent_, label_, body_, next_, c_class_exp )\
    {\
	c_class *x740_ = CHECK_TAG ( ( c_class_exp ), 75 ) ;\
	( type_ ) = DEREF_type ( x740_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x740_ + 2 ) ;\
	( label_ ) = DEREF_id ( x740_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x740_ + 4 ) ;\
	( next_ ) = DEREF_id ( x740_ + 5 ) ;\
    }

#define DESTROY_exp_label_stmt( destroyer_, type_, parent_, label_, body_, next_, c_class_exp )\
    {\
	c_class *x741_ = CHECK_TAG ( ( c_class_exp ), 75 ) ;\
	( type_ ) = DEREF_type ( x741_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x741_ + 2 ) ;\
	( label_ ) = DEREF_id ( x741_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x741_ + 4 ) ;\
	( next_ ) = DEREF_id ( x741_ + 5 ) ;\
	( destroyer_ ) ( x741_, ( unsigned ) 6 ) ;\
    }


/* Operations for field try_block of union EXP */

#define exp_try_block_tag		( ( unsigned ) 76 )
#define IS_exp_try_block( P )		( CHECK_NULL ( P )->ag_tag == 76 )

#define exp_try_block_parent( P )	( CHECK_TAG ( ( P ), 76 ) + 2 )
#define exp_try_block_body( P )		( CHECK_TAG ( ( P ), 76 ) + 3 )
#define exp_try_block_func( P )		( CHECK_TAG ( ( P ), 76 ) + 4 )
#define exp_try_block_handlers( P )	( CHECK_TAG ( ( P ), 76 ) + 5 )
#define exp_try_block_htypes( P )	( CHECK_TAG ( ( P ), 76 ) + 6 )
#define exp_try_block_ellipsis( P )	( CHECK_TAG ( ( P ), 76 ) + 7 )
#define exp_try_block_ttypes( P )	( CHECK_TAG ( ( P ), 76 ) + 8 )
#define exp_try_block_tlocs( P )	( CHECK_TAG ( ( P ), 76 ) + 9 )
#define exp_try_block_no( P )		( CHECK_TAG ( ( P ), 76 ) + 10 )

#define MAKE_exp_try_block( type_, body_, func_, c_class_exp )\
    {\
	c_class *x742_ = GEN_c_class ( 11, TYPEID_exp ) ;\
	x742_->ag_tag = 76 ;\
	COPY_type ( x742_ + 1, ( type_ ) ) ;\
	COPY_exp ( x742_ + 2, NULL_exp ) ;\
	COPY_exp ( x742_ + 3, ( body_ ) ) ;\
	COPY_int ( x742_ + 4, ( func_ ) ) ;\
	COPY_list ( x742_ + 5, NULL_list ( EXP ) ) ;\
	COPY_list ( x742_ + 6, NULL_list ( TYPE ) ) ;\
	COPY_exp ( x742_ + 7, NULL_exp ) ;\
	COPY_list ( x742_ + 8, NULL_list ( TYPE ) ) ;\
	COPY_list ( x742_ + 9, NULL_list ( LOCATION ) ) ;\
	COPY_ulong ( x742_ + 10, LINK_NONE ) ;\
	( c_class_exp ) = x742_ ;\
    }

#define DECONS_exp_try_block( type_, parent_, body_, func_, handlers_, htypes_, ellipsis_, ttypes_, tlocs_, no_, c_class_exp )\
    {\
	c_class *x743_ = CHECK_TAG ( ( c_class_exp ), 76 ) ;\
	( type_ ) = DEREF_type ( x743_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x743_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x743_ + 3 ) ;\
	( func_ ) = DEREF_int ( x743_ + 4 ) ;\
	( handlers_ ) = DEREF_list ( x743_ + 5 ) ;\
	( htypes_ ) = DEREF_list ( x743_ + 6 ) ;\
	( ellipsis_ ) = DEREF_exp ( x743_ + 7 ) ;\
	( ttypes_ ) = DEREF_list ( x743_ + 8 ) ;\
	( tlocs_ ) = DEREF_list ( x743_ + 9 ) ;\
	( no_ ) = DEREF_ulong ( x743_ + 10 ) ;\
    }

#define DESTROY_exp_try_block( destroyer_, type_, parent_, body_, func_, handlers_, htypes_, ellipsis_, ttypes_, tlocs_, no_, c_class_exp )\
    {\
	c_class *x744_ = CHECK_TAG ( ( c_class_exp ), 76 ) ;\
	( type_ ) = DEREF_type ( x744_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x744_ + 2 ) ;\
	( body_ ) = DEREF_exp ( x744_ + 3 ) ;\
	( func_ ) = DEREF_int ( x744_ + 4 ) ;\
	( handlers_ ) = DEREF_list ( x744_ + 5 ) ;\
	( htypes_ ) = DEREF_list ( x744_ + 6 ) ;\
	( ellipsis_ ) = DEREF_exp ( x744_ + 7 ) ;\
	( ttypes_ ) = DEREF_list ( x744_ + 8 ) ;\
	( tlocs_ ) = DEREF_list ( x744_ + 9 ) ;\
	( no_ ) = DEREF_ulong ( x744_ + 10 ) ;\
	( destroyer_ ) ( x744_, ( unsigned ) 11 ) ;\
    }


/* Operations for field handler of union EXP */

#define exp_handler_tag			( ( unsigned ) 77 )
#define IS_exp_handler( P )		( CHECK_NULL ( P )->ag_tag == 77 )

#define exp_handler_parent( P )		( CHECK_TAG ( ( P ), 77 ) + 2 )
#define exp_handler_except( P )		( CHECK_TAG ( ( P ), 77 ) + 3 )
#define exp_handler_body( P )		( CHECK_TAG ( ( P ), 77 ) + 4 )
#define exp_handler_diag( P )		( CHECK_TAG ( ( P ), 77 ) + 5 )

#define MAKE_exp_handler( type_, except_, body_, c_class_exp )\
    {\
	c_class *x745_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x745_->ag_tag = 77 ;\
	COPY_type ( x745_ + 1, ( type_ ) ) ;\
	COPY_exp ( x745_ + 2, NULL_exp ) ;\
	COPY_id ( x745_ + 3, ( except_ ) ) ;\
	COPY_exp ( x745_ + 4, ( body_ ) ) ;\
	COPY_ulong ( x745_ + 5, LINK_NONE ) ;\
	( c_class_exp ) = x745_ ;\
    }

#define DECONS_exp_handler( type_, parent_, except_, body_, diag_, c_class_exp )\
    {\
	c_class *x746_ = CHECK_TAG ( ( c_class_exp ), 77 ) ;\
	( type_ ) = DEREF_type ( x746_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x746_ + 2 ) ;\
	( except_ ) = DEREF_id ( x746_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x746_ + 4 ) ;\
	( diag_ ) = DEREF_ulong ( x746_ + 5 ) ;\
    }

#define DESTROY_exp_handler( destroyer_, type_, parent_, except_, body_, diag_, c_class_exp )\
    {\
	c_class *x747_ = CHECK_TAG ( ( c_class_exp ), 77 ) ;\
	( type_ ) = DEREF_type ( x747_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x747_ + 2 ) ;\
	( except_ ) = DEREF_id ( x747_ + 3 ) ;\
	( body_ ) = DEREF_exp ( x747_ + 4 ) ;\
	( diag_ ) = DEREF_ulong ( x747_ + 5 ) ;\
	( destroyer_ ) ( x747_, ( unsigned ) 6 ) ;\
    }


/* Operations for field exception of union EXP */

#define exp_exception_tag		( ( unsigned ) 78 )
#define IS_exp_exception( P )		( CHECK_NULL ( P )->ag_tag == 78 )

#define exp_exception_arg( P )		( CHECK_TAG ( ( P ), 78 ) + 2 )
#define exp_exception_size( P )		( CHECK_TAG ( ( P ), 78 ) + 3 )
#define exp_exception_destr( P )	( CHECK_TAG ( ( P ), 78 ) + 4 )
#define exp_exception_expl( P )		( CHECK_TAG ( ( P ), 78 ) + 5 )

#define MAKE_exp_exception( type_, arg_, size_, destr_, expl_, c_class_exp )\
    {\
	c_class *x748_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x748_->ag_tag = 78 ;\
	COPY_type ( x748_ + 1, ( type_ ) ) ;\
	COPY_exp ( x748_ + 2, ( arg_ ) ) ;\
	COPY_exp ( x748_ + 3, ( size_ ) ) ;\
	COPY_exp ( x748_ + 4, ( destr_ ) ) ;\
	COPY_int ( x748_ + 5, ( expl_ ) ) ;\
	( c_class_exp ) = x748_ ;\
    }

#define DECONS_exp_exception( type_, arg_, size_, destr_, expl_, c_class_exp )\
    {\
	c_class *x749_ = CHECK_TAG ( ( c_class_exp ), 78 ) ;\
	( type_ ) = DEREF_type ( x749_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x749_ + 2 ) ;\
	( size_ ) = DEREF_exp ( x749_ + 3 ) ;\
	( destr_ ) = DEREF_exp ( x749_ + 4 ) ;\
	( expl_ ) = DEREF_int ( x749_ + 5 ) ;\
    }

#define DESTROY_exp_exception( destroyer_, type_, arg_, size_, destr_, expl_, c_class_exp )\
    {\
	c_class *x750_ = CHECK_TAG ( ( c_class_exp ), 78 ) ;\
	( type_ ) = DEREF_type ( x750_ + 1 ) ;\
	( arg_ ) = DEREF_exp ( x750_ + 2 ) ;\
	( size_ ) = DEREF_exp ( x750_ + 3 ) ;\
	( destr_ ) = DEREF_exp ( x750_ + 4 ) ;\
	( expl_ ) = DEREF_int ( x750_ + 5 ) ;\
	( destroyer_ ) ( x750_, ( unsigned ) 6 ) ;\
    }


/* Operations for field thrown of union EXP */

#define exp_thrown_tag			( ( unsigned ) 79 )
#define IS_exp_thrown( P )		( CHECK_NULL ( P )->ag_tag == 79 )

#define exp_thrown_done( P )		( CHECK_TAG ( ( P ), 79 ) + 2 )

#define MAKE_exp_thrown( type_, done_, c_class_exp )\
    {\
	c_class *x751_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x751_->ag_tag = 79 ;\
	COPY_type ( x751_ + 1, ( type_ ) ) ;\
	COPY_int ( x751_ + 2, ( done_ ) ) ;\
	( c_class_exp ) = x751_ ;\
    }

#define DECONS_exp_thrown( type_, done_, c_class_exp )\
    {\
	c_class *x752_ = CHECK_TAG ( ( c_class_exp ), 79 ) ;\
	( type_ ) = DEREF_type ( x752_ + 1 ) ;\
	( done_ ) = DEREF_int ( x752_ + 2 ) ;\
    }

#define DESTROY_exp_thrown( destroyer_, type_, done_, c_class_exp )\
    {\
	c_class *x753_ = CHECK_TAG ( ( c_class_exp ), 79 ) ;\
	( type_ ) = DEREF_type ( x753_ + 1 ) ;\
	( done_ ) = DEREF_int ( x753_ + 2 ) ;\
	( destroyer_ ) ( x753_, ( unsigned ) 3 ) ;\
    }


/* Operations for field op of union EXP */

#define exp_op_tag			( ( unsigned ) 80 )
#define IS_exp_op( P )			( CHECK_NULL ( P )->ag_tag == 80 )

#define exp_op_lex( P )			( CHECK_TAG ( ( P ), 80 ) + 2 )
#define exp_op_arg1( P )		( CHECK_TAG ( ( P ), 80 ) + 3 )
#define exp_op_arg2( P )		( CHECK_TAG ( ( P ), 80 ) + 4 )

#define MAKE_exp_op( type_, lex_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x754_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x754_->ag_tag = 80 ;\
	COPY_type ( x754_ + 1, ( type_ ) ) ;\
	COPY_int ( x754_ + 2, ( lex_ ) ) ;\
	COPY_exp ( x754_ + 3, ( arg1_ ) ) ;\
	COPY_exp ( x754_ + 4, ( arg2_ ) ) ;\
	( c_class_exp ) = x754_ ;\
    }

#define DECONS_exp_op( type_, lex_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x755_ = CHECK_TAG ( ( c_class_exp ), 80 ) ;\
	( type_ ) = DEREF_type ( x755_ + 1 ) ;\
	( lex_ ) = DEREF_int ( x755_ + 2 ) ;\
	( arg1_ ) = DEREF_exp ( x755_ + 3 ) ;\
	( arg2_ ) = DEREF_exp ( x755_ + 4 ) ;\
    }

#define DESTROY_exp_op( destroyer_, type_, lex_, arg1_, arg2_, c_class_exp )\
    {\
	c_class *x756_ = CHECK_TAG ( ( c_class_exp ), 80 ) ;\
	( type_ ) = DEREF_type ( x756_ + 1 ) ;\
	( lex_ ) = DEREF_int ( x756_ + 2 ) ;\
	( arg1_ ) = DEREF_exp ( x756_ + 3 ) ;\
	( arg2_ ) = DEREF_exp ( x756_ + 4 ) ;\
	( destroyer_ ) ( x756_, ( unsigned ) 5 ) ;\
    }


/* Operations for field opn of union EXP */

#define exp_opn_tag			( ( unsigned ) 81 )
#define IS_exp_opn( P )			( CHECK_NULL ( P )->ag_tag == 81 )

#define exp_opn_lex( P )		( CHECK_TAG ( ( P ), 81 ) + 2 )
#define exp_opn_args( P )		( CHECK_TAG ( ( P ), 81 ) + 3 )

#define MAKE_exp_opn( type_, lex_, args_, c_class_exp )\
    {\
	c_class *x757_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x757_->ag_tag = 81 ;\
	COPY_type ( x757_ + 1, ( type_ ) ) ;\
	COPY_int ( x757_ + 2, ( lex_ ) ) ;\
	COPY_list ( x757_ + 3, ( args_ ) ) ;\
	( c_class_exp ) = x757_ ;\
    }

#define DECONS_exp_opn( type_, lex_, args_, c_class_exp )\
    {\
	c_class *x758_ = CHECK_TAG ( ( c_class_exp ), 81 ) ;\
	( type_ ) = DEREF_type ( x758_ + 1 ) ;\
	( lex_ ) = DEREF_int ( x758_ + 2 ) ;\
	( args_ ) = DEREF_list ( x758_ + 3 ) ;\
    }

#define DESTROY_exp_opn( destroyer_, type_, lex_, args_, c_class_exp )\
    {\
	c_class *x759_ = CHECK_TAG ( ( c_class_exp ), 81 ) ;\
	( type_ ) = DEREF_type ( x759_ + 1 ) ;\
	( lex_ ) = DEREF_int ( x759_ + 2 ) ;\
	( args_ ) = DEREF_list ( x759_ + 3 ) ;\
	( destroyer_ ) ( x759_, ( unsigned ) 4 ) ;\
    }


/* Operations for field assembler of union EXP */

#define exp_assembler_tag		( ( unsigned ) 82 )
#define IS_exp_assembler( P )		( CHECK_NULL ( P )->ag_tag == 82 )

#define exp_assembler_op( P )		( CHECK_TAG ( ( P ), 82 ) + 2 )
#define exp_assembler_args( P )		( CHECK_TAG ( ( P ), 82 ) + 3 )

#define MAKE_exp_assembler( type_, op_, args_, c_class_exp )\
    {\
	c_class *x760_ = GEN_c_class ( 4, TYPEID_exp ) ;\
	x760_->ag_tag = 82 ;\
	COPY_type ( x760_ + 1, ( type_ ) ) ;\
	COPY_str ( x760_ + 2, ( op_ ) ) ;\
	COPY_list ( x760_ + 3, ( args_ ) ) ;\
	( c_class_exp ) = x760_ ;\
    }

#define DECONS_exp_assembler( type_, op_, args_, c_class_exp )\
    {\
	c_class *x761_ = CHECK_TAG ( ( c_class_exp ), 82 ) ;\
	( type_ ) = DEREF_type ( x761_ + 1 ) ;\
	( op_ ) = DEREF_str ( x761_ + 2 ) ;\
	( args_ ) = DEREF_list ( x761_ + 3 ) ;\
    }

#define DESTROY_exp_assembler( destroyer_, type_, op_, args_, c_class_exp )\
    {\
	c_class *x762_ = CHECK_TAG ( ( c_class_exp ), 82 ) ;\
	( type_ ) = DEREF_type ( x762_ + 1 ) ;\
	( op_ ) = DEREF_str ( x762_ + 2 ) ;\
	( args_ ) = DEREF_list ( x762_ + 3 ) ;\
	( destroyer_ ) ( x762_, ( unsigned ) 4 ) ;\
    }


/* Operations for field uncompiled of union EXP */

#define exp_uncompiled_tag		( ( unsigned ) 83 )
#define IS_exp_uncompiled( P )		( CHECK_NULL ( P )->ag_tag == 83 )

#define exp_uncompiled_start( P )	( CHECK_TAG ( ( P ), 83 ) + 2 )
#define exp_uncompiled_defn( P )	( CHECK_TAG ( ( P ), 83 ) + 5 )

#define MAKE_exp_uncompiled( type_, start_, defn_, c_class_exp )\
    {\
	c_class *x763_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x763_->ag_tag = 83 ;\
	COPY_type ( x763_ + 1, ( type_ ) ) ;\
	COPY_ulong ( x763_ + 2, ( start_ ).line ) ;\
	COPY_ulong ( x763_ + 3, ( start_ ).column ) ;\
	COPY_ptr ( x763_ + 4, ( start_ ).posn ) ;\
	COPY_pptok ( x763_ + 5, ( defn_ ) ) ;\
	( c_class_exp ) = x763_ ;\
    }

#define DECONS_exp_uncompiled( type_, start_, defn_, c_class_exp )\
    {\
	c_class *x764_ = CHECK_TAG ( ( c_class_exp ), 83 ) ;\
	( type_ ) = DEREF_type ( x764_ + 1 ) ;\
	( start_ ).line = DEREF_ulong ( x764_ + 2 ) ;\
	( start_ ).column = DEREF_ulong ( x764_ + 3 ) ;\
	( start_ ).posn = DEREF_ptr ( x764_ + 4 ) ;\
	( defn_ ) = DEREF_pptok ( x764_ + 5 ) ;\
    }

#define DESTROY_exp_uncompiled( destroyer_, type_, start_, defn_, c_class_exp )\
    {\
	c_class *x765_ = CHECK_TAG ( ( c_class_exp ), 83 ) ;\
	( type_ ) = DEREF_type ( x765_ + 1 ) ;\
	( start_ ).line = DEREF_ulong ( x765_ + 2 ) ;\
	( start_ ).column = DEREF_ulong ( x765_ + 3 ) ;\
	( start_ ).posn = DEREF_ptr ( x765_ + 4 ) ;\
	( defn_ ) = DEREF_pptok ( x765_ + 5 ) ;\
	( destroyer_ ) ( x765_, ( unsigned ) 6 ) ;\
    }


/* Operations for field location of union EXP */

#define exp_location_tag		( ( unsigned ) 84 )
#define IS_exp_location( P )		( CHECK_NULL ( P )->ag_tag == 84 )

#define exp_location_end( P )		( CHECK_TAG ( ( P ), 84 ) + 2 )
#define exp_location_arg( P )		( CHECK_TAG ( ( P ), 84 ) + 5 )

#define MAKE_exp_location( type_, end_, arg_, c_class_exp )\
    {\
	c_class *x766_ = GEN_c_class ( 6, TYPEID_exp ) ;\
	x766_->ag_tag = 84 ;\
	COPY_type ( x766_ + 1, ( type_ ) ) ;\
	COPY_ulong ( x766_ + 2, ( end_ ).line ) ;\
	COPY_ulong ( x766_ + 3, ( end_ ).column ) ;\
	COPY_ptr ( x766_ + 4, ( end_ ).posn ) ;\
	COPY_exp ( x766_ + 5, ( arg_ ) ) ;\
	( c_class_exp ) = x766_ ;\
    }

#define DECONS_exp_location( type_, end_, arg_, c_class_exp )\
    {\
	c_class *x767_ = CHECK_TAG ( ( c_class_exp ), 84 ) ;\
	( type_ ) = DEREF_type ( x767_ + 1 ) ;\
	( end_ ).line = DEREF_ulong ( x767_ + 2 ) ;\
	( end_ ).column = DEREF_ulong ( x767_ + 3 ) ;\
	( end_ ).posn = DEREF_ptr ( x767_ + 4 ) ;\
	( arg_ ) = DEREF_exp ( x767_ + 5 ) ;\
    }

#define DESTROY_exp_location( destroyer_, type_, end_, arg_, c_class_exp )\
    {\
	c_class *x768_ = CHECK_TAG ( ( c_class_exp ), 84 ) ;\
	( type_ ) = DEREF_type ( x768_ + 1 ) ;\
	( end_ ).line = DEREF_ulong ( x768_ + 2 ) ;\
	( end_ ).column = DEREF_ulong ( x768_ + 3 ) ;\
	( end_ ).posn = DEREF_ptr ( x768_ + 4 ) ;\
	( arg_ ) = DEREF_exp ( x768_ + 5 ) ;\
	( destroyer_ ) ( x768_, ( unsigned ) 6 ) ;\
    }


/* Operations for field fail of union EXP */

#define exp_fail_tag			( ( unsigned ) 85 )
#define IS_exp_fail( P )		( CHECK_NULL ( P )->ag_tag == 85 )

#define exp_fail_msg( P )		( CHECK_TAG ( ( P ), 85 ) + 2 )

#define MAKE_exp_fail( type_, msg_, c_class_exp )\
    {\
	c_class *x769_ = GEN_c_class ( 3, TYPEID_exp ) ;\
	x769_->ag_tag = 85 ;\
	COPY_type ( x769_ + 1, ( type_ ) ) ;\
	COPY_string ( x769_ + 2, ( msg_ ) ) ;\
	( c_class_exp ) = x769_ ;\
    }

#define DECONS_exp_fail( type_, msg_, c_class_exp )\
    {\
	c_class *x770_ = CHECK_TAG ( ( c_class_exp ), 85 ) ;\
	( type_ ) = DEREF_type ( x770_ + 1 ) ;\
	( msg_ ) = DEREF_string ( x770_ + 2 ) ;\
    }

#define DESTROY_exp_fail( destroyer_, type_, msg_, c_class_exp )\
    {\
	c_class *x771_ = CHECK_TAG ( ( c_class_exp ), 85 ) ;\
	( type_ ) = DEREF_type ( x771_ + 1 ) ;\
	( msg_ ) = DEREF_string ( x771_ + 2 ) ;\
	( destroyer_ ) ( x771_, ( unsigned ) 3 ) ;\
    }


/* Operations for field token of union EXP */

#define exp_token_tag			( ( unsigned ) 86 )
#define IS_exp_token( P )		( CHECK_NULL ( P )->ag_tag == 86 )

#define exp_token_parent( P )		( CHECK_TAG ( ( P ), 86 ) + 2 )
#define exp_token_tok( P )		( CHECK_TAG ( ( P ), 86 ) + 3 )
#define exp_token_args( P )		( CHECK_TAG ( ( P ), 86 ) + 4 )

#define MAKE_exp_token( type_, tok_, args_, c_class_exp )\
    {\
	c_class *x772_ = GEN_c_class ( 5, TYPEID_exp ) ;\
	x772_->ag_tag = 86 ;\
	COPY_type ( x772_ + 1, ( type_ ) ) ;\
	COPY_exp ( x772_ + 2, NULL_exp ) ;\
	COPY_id ( x772_ + 3, ( tok_ ) ) ;\
	COPY_list ( x772_ + 4, ( args_ ) ) ;\
	( c_class_exp ) = x772_ ;\
    }

#define DECONS_exp_token( type_, parent_, tok_, args_, c_class_exp )\
    {\
	c_class *x773_ = CHECK_TAG ( ( c_class_exp ), 86 ) ;\
	( type_ ) = DEREF_type ( x773_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x773_ + 2 ) ;\
	( tok_ ) = DEREF_id ( x773_ + 3 ) ;\
	( args_ ) = DEREF_list ( x773_ + 4 ) ;\
    }

#define DESTROY_exp_token( destroyer_, type_, parent_, tok_, args_, c_class_exp )\
    {\
	c_class *x774_ = CHECK_TAG ( ( c_class_exp ), 86 ) ;\
	( type_ ) = DEREF_type ( x774_ + 1 ) ;\
	( parent_ ) = DEREF_exp ( x774_ + 2 ) ;\
	( tok_ ) = DEREF_id ( x774_ + 3 ) ;\
	( args_ ) = DEREF_list ( x774_ + 4 ) ;\
	( destroyer_ ) ( x774_, ( unsigned ) 5 ) ;\
    }


/* Operations for field dummy of union EXP */

#define exp_dummy_tag			( ( unsigned ) 87 )
#define IS_exp_dummy( P )		( CHECK_NULL ( P )->ag_tag == 87 )

#define exp_dummy_value( P )		( CHECK_TAG ( ( P ), 87 ) + 2 )
#define exp_dummy_no( P )		( CHECK_TAG ( ( P ), 87 ) + 3 )
#define exp_dummy_off( P )		( CHECK_TAG ( ( P ), 87 ) + 4 )
#define exp_dummy_virt( P )		( CHECK_TAG ( ( P ), 87 ) + 5 )
#define exp_dummy_cont( P )		( CHECK_TAG ( ( P ), 87 ) + 6 )

#define MAKE_exp_dummy( type_, value_, no_, off_, cont_, c_class_exp )\
    {\
	c_class *x775_ = GEN_c_class ( 7, TYPEID_exp ) ;\
	x775_->ag_tag = 87 ;\
	COPY_type ( x775_ + 1, ( type_ ) ) ;\
	COPY_exp ( x775_ + 2, ( value_ ) ) ;\
	COPY_ulong ( x775_ + 3, ( no_ ) ) ;\
	COPY_off ( x775_ + 4, ( off_ ) ) ;\
	COPY_int ( x775_ + 5, 0 ) ;\
	COPY_int ( x775_ + 6, ( cont_ ) ) ;\
	( c_class_exp ) = x775_ ;\
    }

#define DECONS_exp_dummy( type_, value_, no_, off_, virt_, cont_, c_class_exp )\
    {\
	c_class *x776_ = CHECK_TAG ( ( c_class_exp ), 87 ) ;\
	( type_ ) = DEREF_type ( x776_ + 1 ) ;\
	( value_ ) = DEREF_exp ( x776_ + 2 ) ;\
	( no_ ) = DEREF_ulong ( x776_ + 3 ) ;\
	( off_ ) = DEREF_off ( x776_ + 4 ) ;\
	( virt_ ) = DEREF_int ( x776_ + 5 ) ;\
	( cont_ ) = DEREF_int ( x776_ + 6 ) ;\
    }

#define DESTROY_exp_dummy( destroyer_, type_, value_, no_, off_, virt_, cont_, c_class_exp )\
    {\
	c_class *x777_ = CHECK_TAG ( ( c_class_exp ), 87 ) ;\
	( type_ ) = DEREF_type ( x777_ + 1 ) ;\
	( value_ ) = DEREF_exp ( x777_ + 2 ) ;\
	( no_ ) = DEREF_ulong ( x777_ + 3 ) ;\
	( off_ ) = DEREF_off ( x777_ + 4 ) ;\
	( virt_ ) = DEREF_int ( x777_ + 5 ) ;\
	( cont_ ) = DEREF_int ( x777_ + 6 ) ;\
	( destroyer_ ) ( x777_, ( unsigned ) 7 ) ;\
    }


#endif
