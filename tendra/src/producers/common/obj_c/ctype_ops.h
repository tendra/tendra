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

#ifndef CTYPE_OPS_H_INCLUDED
#define CTYPE_OPS_H_INCLUDED

/* Operations for union CLASS_TYPE */

#define TAG_ctype( P )			( ( unsigned ) 0 )


/* Operations for component name of union CLASS_TYPE */

#define ctype_name( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component info of union CLASS_TYPE */

#define ctype_info( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component usage of union CLASS_TYPE */

#define ctype_usage( P )		( CHECK_NULL ( P ) + 2 )


/* Operations for component member of union CLASS_TYPE */

#define ctype_member( P )		( CHECK_NULL ( P ) + 3 )


/* Operations for component base of union CLASS_TYPE */

#define ctype_base( P )			( CHECK_NULL ( P ) + 4 )


/* Operations for component no_bases of union CLASS_TYPE */

#define ctype_no_bases( P )		( CHECK_NULL ( P ) + 5 )


/* Operations for component prev of union CLASS_TYPE */

#define ctype_prev( P )			( CHECK_NULL ( P ) + 6 )


/* Operations for component form of union CLASS_TYPE */

#define ctype_form( P )			( CHECK_NULL ( P ) + 7 )


/* Operations for component constr of union CLASS_TYPE */

#define ctype_constr( P )		( CHECK_NULL ( P ) + 8 )


/* Operations for component destr of union CLASS_TYPE */

#define ctype_destr( P )		( CHECK_NULL ( P ) + 9 )


/* Operations for component virt of union CLASS_TYPE */

#define ctype_virt( P )			( CHECK_NULL ( P ) + 10 )


/* Operations for component vbase of union CLASS_TYPE */

#define ctype_vbase( P )		( CHECK_NULL ( P ) + 11 )


/* Operations for component conv of union CLASS_TYPE */

#define ctype_conv( P )			( CHECK_NULL ( P ) + 12 )


/* Operations for component chums of union CLASS_TYPE */

#define ctype_chums( P )		( CHECK_NULL ( P ) + 13 )


/* Operations for component pals of union CLASS_TYPE */

#define ctype_pals( P )			( CHECK_NULL ( P ) + 14 )


/* Operations for component nest of union CLASS_TYPE */

#define ctype_nest( P )			( CHECK_NULL ( P ) + 15 )


/* Operations for component tok1 of union CLASS_TYPE */

#define ctype_tok1( P )			( CHECK_NULL ( P ) + 16 )


/* Operations for component tok2 of union CLASS_TYPE */

#define ctype_tok2( P )			( CHECK_NULL ( P ) + 17 )


/* Operations for field basic of union CLASS_TYPE */

#define ctype_basic_tag			( ( unsigned ) 0 )
#define IS_ctype_basic( P )		1


#define MAKE_ctype_basic( name_, info_, usage_, member_, base_, no_bases_, prev_, c_class_ctype )\
    {\
	c_class *x199_ = GEN_c_class ( 18, TYPEID_ctype ) ;\
	COPY_id ( x199_ + 0, ( name_ ) ) ;\
	COPY_cinfo ( x199_ + 1, ( info_ ) ) ;\
	COPY_cusage ( x199_ + 2, ( usage_ ) ) ;\
	COPY_nspace ( x199_ + 3, ( member_ ) ) ;\
	COPY_graph ( x199_ + 4, ( base_ ) ) ;\
	COPY_unsigned ( x199_ + 5, ( no_bases_ ) ) ;\
	COPY_type ( x199_ + 6, ( prev_ ) ) ;\
	COPY_type ( x199_ + 7, NULL_type ) ;\
	COPY_id ( x199_ + 8, NULL_id ) ;\
	COPY_id ( x199_ + 9, NULL_id ) ;\
	COPY_virt ( x199_ + 10, NULL_virt ) ;\
	COPY_list ( x199_ + 11, NULL_list ( GRAPH ) ) ;\
	COPY_list ( x199_ + 12, NULL_list ( IDENTIFIER ) ) ;\
	COPY_list ( x199_ + 13, NULL_list ( CLASS_TYPE ) ) ;\
	COPY_list ( x199_ + 14, NULL_list ( IDENTIFIER ) ) ;\
	COPY_list ( x199_ + 15, NULL_list ( IDENTIFIER ) ) ;\
	COPY_ulong ( x199_ + 16, LINK_NONE ) ;\
	COPY_ulong ( x199_ + 17, LINK_NONE ) ;\
	( c_class_ctype ) = x199_ ;\
    }

#define DECONS_ctype_basic( name_, info_, usage_, member_, base_, no_bases_, prev_, form_, constr_, destr_, virt_, vbase_, conv_, chums_, pals_, nest_, tok1_, tok2_, c_class_ctype )\
    {\
	c_class *x200_ = ( c_class_ctype ) ;\
	( name_ ) = DEREF_id ( x200_ + 0 ) ;\
	( info_ ) = DEREF_cinfo ( x200_ + 1 ) ;\
	( usage_ ) = DEREF_cusage ( x200_ + 2 ) ;\
	( member_ ) = DEREF_nspace ( x200_ + 3 ) ;\
	( base_ ) = DEREF_graph ( x200_ + 4 ) ;\
	( no_bases_ ) = DEREF_unsigned ( x200_ + 5 ) ;\
	( prev_ ) = DEREF_type ( x200_ + 6 ) ;\
	( form_ ) = DEREF_type ( x200_ + 7 ) ;\
	( constr_ ) = DEREF_id ( x200_ + 8 ) ;\
	( destr_ ) = DEREF_id ( x200_ + 9 ) ;\
	( virt_ ) = DEREF_virt ( x200_ + 10 ) ;\
	( vbase_ ) = DEREF_list ( x200_ + 11 ) ;\
	( conv_ ) = DEREF_list ( x200_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x200_ + 13 ) ;\
	( pals_ ) = DEREF_list ( x200_ + 14 ) ;\
	( nest_ ) = DEREF_list ( x200_ + 15 ) ;\
	( tok1_ ) = DEREF_ulong ( x200_ + 16 ) ;\
	( tok2_ ) = DEREF_ulong ( x200_ + 17 ) ;\
    }

#define DESTROY_ctype_basic( destroyer_, name_, info_, usage_, member_, base_, no_bases_, prev_, form_, constr_, destr_, virt_, vbase_, conv_, chums_, pals_, nest_, tok1_, tok2_, c_class_ctype )\
    {\
	c_class *x201_ = ( c_class_ctype ) ;\
	( name_ ) = DEREF_id ( x201_ + 0 ) ;\
	( info_ ) = DEREF_cinfo ( x201_ + 1 ) ;\
	( usage_ ) = DEREF_cusage ( x201_ + 2 ) ;\
	( member_ ) = DEREF_nspace ( x201_ + 3 ) ;\
	( base_ ) = DEREF_graph ( x201_ + 4 ) ;\
	( no_bases_ ) = DEREF_unsigned ( x201_ + 5 ) ;\
	( prev_ ) = DEREF_type ( x201_ + 6 ) ;\
	( form_ ) = DEREF_type ( x201_ + 7 ) ;\
	( constr_ ) = DEREF_id ( x201_ + 8 ) ;\
	( destr_ ) = DEREF_id ( x201_ + 9 ) ;\
	( virt_ ) = DEREF_virt ( x201_ + 10 ) ;\
	( vbase_ ) = DEREF_list ( x201_ + 11 ) ;\
	( conv_ ) = DEREF_list ( x201_ + 12 ) ;\
	( chums_ ) = DEREF_list ( x201_ + 13 ) ;\
	( pals_ ) = DEREF_list ( x201_ + 14 ) ;\
	( nest_ ) = DEREF_list ( x201_ + 15 ) ;\
	( tok1_ ) = DEREF_ulong ( x201_ + 16 ) ;\
	( tok2_ ) = DEREF_ulong ( x201_ + 17 ) ;\
	( destroyer_ ) ( x201_, ( unsigned ) 18 ) ;\
    }


#endif
