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

#ifndef NSPACE_OPS_H_INCLUDED
#define NSPACE_OPS_H_INCLUDED

/* Operations for union NAMESPACE */

#define TAG_nspace( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for component name of union NAMESPACE */

#define nspace_name( P )		( CHECK_NULL ( P ) + 1 )


/* Operations for component last of union NAMESPACE */

#define nspace_last( P )		( CHECK_NULL ( P ) + 2 )


/* Operations for component prev of union NAMESPACE */

#define nspace_prev( P )		( CHECK_NULL ( P ) + 3 )


/* Operations for component parent of union NAMESPACE */

#define nspace_parent( P )		( CHECK_NULL ( P ) + 4 )


/* Operations for component use of union NAMESPACE */

#define nspace_use( P )			( CHECK_NULL ( P ) + 5 )


/* Operations for component join of union NAMESPACE */

#define nspace_join( P )		( CHECK_NULL ( P ) + 6 )


/* Operations for component set of union NAMESPACE */

#define nspace_set( P )			( CHECK_NULL ( P ) + 7 )


/* Operations for component dump of union NAMESPACE */

#define nspace_dump( P )		( CHECK_NULL ( P ) + 8 )


/* Operations for field set block_etc of union NAMESPACE */

#define nspace_block_etc_tag		( ( unsigned ) 5 )
#define IS_nspace_block_etc( P )	( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 0 ) < ( unsigned ) 5 )


#define MAKE_nspace_block_etc( tag, name_, parent_, c_class_nspace )\
    {\
	c_class *x430_ = GEN_c_class ( 9, TYPEID_nspace ) ;\
	x430_->ag_tag = ( tag ) ;\
	COPY_id ( x430_ + 1, ( name_ ) ) ;\
	COPY_member ( x430_ + 2, NULL_member ) ;\
	COPY_member ( x430_ + 3, NULL_member ) ;\
	COPY_nspace ( x430_ + 4, ( parent_ ) ) ;\
	COPY_list ( x430_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x430_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x430_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x430_ + 8, LINK_NONE ) ;\
	( c_class_nspace ) = CHECK_TAG_ETC ( x430_, 0, 5 ) ;\
    }

#define MODIFY_nspace_block_etc( tag, c_class_nspace )\
    {\
	c_class *x431_ = CHECK_TAG_ETC ( ( c_class_nspace ), 0, 5 ) ;\
	x431_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x431_, 0, 5 ) ;\
    }

#define DECONS_nspace_block_etc( name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x432_ = CHECK_TAG_ETC ( ( c_class_nspace ), 0, 5 ) ;\
	( name_ ) = DEREF_id ( x432_ + 1 ) ;\
	( last_ ) = DEREF_member ( x432_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x432_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x432_ + 4 ) ;\
	( use_ ) = DEREF_list ( x432_ + 5 ) ;\
	( join_ ) = DEREF_list ( x432_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x432_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x432_ + 8 ) ;\
    }

#define DESTROY_nspace_block_etc( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x433_ = CHECK_TAG_ETC ( ( c_class_nspace ), 0, 5 ) ;\
	( name_ ) = DEREF_id ( x433_ + 1 ) ;\
	( last_ ) = DEREF_member ( x433_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x433_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x433_ + 4 ) ;\
	( use_ ) = DEREF_list ( x433_ + 5 ) ;\
	( join_ ) = DEREF_list ( x433_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x433_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x433_ + 8 ) ;\
	( destroyer_ ) ( x433_, ( unsigned ) 9 ) ;\
    }


/* Operations for field block of union NAMESPACE */

#define nspace_block_tag		( ( unsigned ) 0 )
#define IS_nspace_block( P )		( CHECK_NULL ( P )->ag_tag == 0 )


#define MAKE_nspace_block( name_, parent_, c_class_nspace )\
    {\
	c_class *x434_ = GEN_c_class ( 9, TYPEID_nspace ) ;\
	x434_->ag_tag = 0 ;\
	COPY_id ( x434_ + 1, ( name_ ) ) ;\
	COPY_member ( x434_ + 2, NULL_member ) ;\
	COPY_member ( x434_ + 3, NULL_member ) ;\
	COPY_nspace ( x434_ + 4, ( parent_ ) ) ;\
	COPY_list ( x434_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x434_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x434_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x434_ + 8, LINK_NONE ) ;\
	( c_class_nspace ) = x434_ ;\
    }

#define DECONS_nspace_block( name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x435_ = CHECK_TAG ( ( c_class_nspace ), 0 ) ;\
	( name_ ) = DEREF_id ( x435_ + 1 ) ;\
	( last_ ) = DEREF_member ( x435_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x435_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x435_ + 4 ) ;\
	( use_ ) = DEREF_list ( x435_ + 5 ) ;\
	( join_ ) = DEREF_list ( x435_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x435_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x435_ + 8 ) ;\
    }

#define DESTROY_nspace_block( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x436_ = CHECK_TAG ( ( c_class_nspace ), 0 ) ;\
	( name_ ) = DEREF_id ( x436_ + 1 ) ;\
	( last_ ) = DEREF_member ( x436_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x436_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x436_ + 4 ) ;\
	( use_ ) = DEREF_list ( x436_ + 5 ) ;\
	( join_ ) = DEREF_list ( x436_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x436_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x436_ + 8 ) ;\
	( destroyer_ ) ( x436_, ( unsigned ) 9 ) ;\
    }


/* Operations for field param of union NAMESPACE */

#define nspace_param_tag		( ( unsigned ) 1 )
#define IS_nspace_param( P )		( CHECK_NULL ( P )->ag_tag == 1 )


#define MAKE_nspace_param( name_, parent_, c_class_nspace )\
    {\
	c_class *x437_ = GEN_c_class ( 9, TYPEID_nspace ) ;\
	x437_->ag_tag = 1 ;\
	COPY_id ( x437_ + 1, ( name_ ) ) ;\
	COPY_member ( x437_ + 2, NULL_member ) ;\
	COPY_member ( x437_ + 3, NULL_member ) ;\
	COPY_nspace ( x437_ + 4, ( parent_ ) ) ;\
	COPY_list ( x437_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x437_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x437_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x437_ + 8, LINK_NONE ) ;\
	( c_class_nspace ) = x437_ ;\
    }

#define DECONS_nspace_param( name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x438_ = CHECK_TAG ( ( c_class_nspace ), 1 ) ;\
	( name_ ) = DEREF_id ( x438_ + 1 ) ;\
	( last_ ) = DEREF_member ( x438_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x438_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x438_ + 4 ) ;\
	( use_ ) = DEREF_list ( x438_ + 5 ) ;\
	( join_ ) = DEREF_list ( x438_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x438_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x438_ + 8 ) ;\
    }

#define DESTROY_nspace_param( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x439_ = CHECK_TAG ( ( c_class_nspace ), 1 ) ;\
	( name_ ) = DEREF_id ( x439_ + 1 ) ;\
	( last_ ) = DEREF_member ( x439_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x439_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x439_ + 4 ) ;\
	( use_ ) = DEREF_list ( x439_ + 5 ) ;\
	( join_ ) = DEREF_list ( x439_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x439_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x439_ + 8 ) ;\
	( destroyer_ ) ( x439_, ( unsigned ) 9 ) ;\
    }


/* Operations for field dummy of union NAMESPACE */

#define nspace_dummy_tag		( ( unsigned ) 2 )
#define IS_nspace_dummy( P )		( CHECK_NULL ( P )->ag_tag == 2 )


#define MAKE_nspace_dummy( name_, parent_, c_class_nspace )\
    {\
	c_class *x440_ = GEN_c_class ( 9, TYPEID_nspace ) ;\
	x440_->ag_tag = 2 ;\
	COPY_id ( x440_ + 1, ( name_ ) ) ;\
	COPY_member ( x440_ + 2, NULL_member ) ;\
	COPY_member ( x440_ + 3, NULL_member ) ;\
	COPY_nspace ( x440_ + 4, ( parent_ ) ) ;\
	COPY_list ( x440_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x440_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x440_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x440_ + 8, LINK_NONE ) ;\
	( c_class_nspace ) = x440_ ;\
    }

#define DECONS_nspace_dummy( name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x441_ = CHECK_TAG ( ( c_class_nspace ), 2 ) ;\
	( name_ ) = DEREF_id ( x441_ + 1 ) ;\
	( last_ ) = DEREF_member ( x441_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x441_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x441_ + 4 ) ;\
	( use_ ) = DEREF_list ( x441_ + 5 ) ;\
	( join_ ) = DEREF_list ( x441_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x441_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x441_ + 8 ) ;\
    }

#define DESTROY_nspace_dummy( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x442_ = CHECK_TAG ( ( c_class_nspace ), 2 ) ;\
	( name_ ) = DEREF_id ( x442_ + 1 ) ;\
	( last_ ) = DEREF_member ( x442_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x442_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x442_ + 4 ) ;\
	( use_ ) = DEREF_list ( x442_ + 5 ) ;\
	( join_ ) = DEREF_list ( x442_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x442_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x442_ + 8 ) ;\
	( destroyer_ ) ( x442_, ( unsigned ) 9 ) ;\
    }


/* Operations for field label of union NAMESPACE */

#define nspace_label_tag		( ( unsigned ) 3 )
#define IS_nspace_label( P )		( CHECK_NULL ( P )->ag_tag == 3 )


#define MAKE_nspace_label( name_, parent_, c_class_nspace )\
    {\
	c_class *x443_ = GEN_c_class ( 9, TYPEID_nspace ) ;\
	x443_->ag_tag = 3 ;\
	COPY_id ( x443_ + 1, ( name_ ) ) ;\
	COPY_member ( x443_ + 2, NULL_member ) ;\
	COPY_member ( x443_ + 3, NULL_member ) ;\
	COPY_nspace ( x443_ + 4, ( parent_ ) ) ;\
	COPY_list ( x443_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x443_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x443_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x443_ + 8, LINK_NONE ) ;\
	( c_class_nspace ) = x443_ ;\
    }

#define DECONS_nspace_label( name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x444_ = CHECK_TAG ( ( c_class_nspace ), 3 ) ;\
	( name_ ) = DEREF_id ( x444_ + 1 ) ;\
	( last_ ) = DEREF_member ( x444_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x444_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x444_ + 4 ) ;\
	( use_ ) = DEREF_list ( x444_ + 5 ) ;\
	( join_ ) = DEREF_list ( x444_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x444_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x444_ + 8 ) ;\
    }

#define DESTROY_nspace_label( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x445_ = CHECK_TAG ( ( c_class_nspace ), 3 ) ;\
	( name_ ) = DEREF_id ( x445_ + 1 ) ;\
	( last_ ) = DEREF_member ( x445_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x445_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x445_ + 4 ) ;\
	( use_ ) = DEREF_list ( x445_ + 5 ) ;\
	( join_ ) = DEREF_list ( x445_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x445_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x445_ + 8 ) ;\
	( destroyer_ ) ( x445_, ( unsigned ) 9 ) ;\
    }


/* Operations for field templ of union NAMESPACE */

#define nspace_templ_tag		( ( unsigned ) 4 )
#define IS_nspace_templ( P )		( CHECK_NULL ( P )->ag_tag == 4 )


#define MAKE_nspace_templ( name_, parent_, c_class_nspace )\
    {\
	c_class *x446_ = GEN_c_class ( 9, TYPEID_nspace ) ;\
	x446_->ag_tag = 4 ;\
	COPY_id ( x446_ + 1, ( name_ ) ) ;\
	COPY_member ( x446_ + 2, NULL_member ) ;\
	COPY_member ( x446_ + 3, NULL_member ) ;\
	COPY_nspace ( x446_ + 4, ( parent_ ) ) ;\
	COPY_list ( x446_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x446_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x446_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x446_ + 8, LINK_NONE ) ;\
	( c_class_nspace ) = x446_ ;\
    }

#define DECONS_nspace_templ( name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x447_ = CHECK_TAG ( ( c_class_nspace ), 4 ) ;\
	( name_ ) = DEREF_id ( x447_ + 1 ) ;\
	( last_ ) = DEREF_member ( x447_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x447_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x447_ + 4 ) ;\
	( use_ ) = DEREF_list ( x447_ + 5 ) ;\
	( join_ ) = DEREF_list ( x447_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x447_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x447_ + 8 ) ;\
    }

#define DESTROY_nspace_templ( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, c_class_nspace )\
    {\
	c_class *x448_ = CHECK_TAG ( ( c_class_nspace ), 4 ) ;\
	( name_ ) = DEREF_id ( x448_ + 1 ) ;\
	( last_ ) = DEREF_member ( x448_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x448_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x448_ + 4 ) ;\
	( use_ ) = DEREF_list ( x448_ + 5 ) ;\
	( join_ ) = DEREF_list ( x448_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x448_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x448_ + 8 ) ;\
	( destroyer_ ) ( x448_, ( unsigned ) 9 ) ;\
    }


/* Operations for field set named_etc of union NAMESPACE */

#define nspace_named_etc_tag		( ( unsigned ) 9 )
#define IS_nspace_named_etc( P )	( ( unsigned ) ( CHECK_NULL ( P )->ag_tag - 5 ) < ( unsigned ) 4 )

#define nspace_named_etc_first( P )	( CHECK_TAG_ETC ( ( P ), 5, 9 ) + 9 )
#define nspace_named_etc_extra( P )	( CHECK_TAG_ETC ( ( P ), 5, 9 ) + 10 )
#define nspace_named_etc_size( P )	( CHECK_TAG_ETC ( ( P ), 5, 9 ) + 11 )
#define nspace_named_etc_table( P )	( CHECK_TAG_ETC ( ( P ), 5, 9 ) + 12 )

#define MAKE_nspace_named_etc( tag, name_, parent_, size_, table_, c_class_nspace )\
    {\
	c_class *x449_ = GEN_c_class ( 13, TYPEID_nspace ) ;\
	x449_->ag_tag = ( tag ) ;\
	COPY_id ( x449_ + 1, ( name_ ) ) ;\
	COPY_member ( x449_ + 2, NULL_member ) ;\
	COPY_member ( x449_ + 3, NULL_member ) ;\
	COPY_nspace ( x449_ + 4, ( parent_ ) ) ;\
	COPY_list ( x449_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x449_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x449_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x449_ + 8, LINK_NONE ) ;\
	COPY_member ( x449_ + 9, NULL_member ) ;\
	COPY_list ( x449_ + 10, NULL_list ( IDENTIFIER ) ) ;\
	COPY_ulong ( x449_ + 11, ( size_ ) ) ;\
	COPY_ptr ( x449_ + 12, ( table_ ) ) ;\
	( c_class_nspace ) = CHECK_TAG_ETC ( x449_, 5, 9 ) ;\
    }

#define MODIFY_nspace_named_etc( tag, c_class_nspace )\
    {\
	c_class *x450_ = CHECK_TAG_ETC ( ( c_class_nspace ), 5, 9 ) ;\
	x450_->ag_tag = ( tag ) ;\
	( void ) CHECK_TAG_ETC ( x450_, 5, 9 ) ;\
    }

#define DECONS_nspace_named_etc( name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x451_ = CHECK_TAG_ETC ( ( c_class_nspace ), 5, 9 ) ;\
	( name_ ) = DEREF_id ( x451_ + 1 ) ;\
	( last_ ) = DEREF_member ( x451_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x451_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x451_ + 4 ) ;\
	( use_ ) = DEREF_list ( x451_ + 5 ) ;\
	( join_ ) = DEREF_list ( x451_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x451_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x451_ + 8 ) ;\
	( first_ ) = DEREF_member ( x451_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x451_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x451_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x451_ + 12 ) ;\
    }

#define DESTROY_nspace_named_etc( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x452_ = CHECK_TAG_ETC ( ( c_class_nspace ), 5, 9 ) ;\
	( name_ ) = DEREF_id ( x452_ + 1 ) ;\
	( last_ ) = DEREF_member ( x452_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x452_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x452_ + 4 ) ;\
	( use_ ) = DEREF_list ( x452_ + 5 ) ;\
	( join_ ) = DEREF_list ( x452_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x452_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x452_ + 8 ) ;\
	( first_ ) = DEREF_member ( x452_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x452_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x452_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x452_ + 12 ) ;\
	( destroyer_ ) ( x452_, ( unsigned ) 13 ) ;\
    }


/* Operations for field named of union NAMESPACE */

#define nspace_named_tag		( ( unsigned ) 5 )
#define IS_nspace_named( P )		( CHECK_NULL ( P )->ag_tag == 5 )

#define nspace_named_first( P )		( CHECK_TAG ( ( P ), 5 ) + 9 )
#define nspace_named_extra( P )		( CHECK_TAG ( ( P ), 5 ) + 10 )
#define nspace_named_size( P )		( CHECK_TAG ( ( P ), 5 ) + 11 )
#define nspace_named_table( P )		( CHECK_TAG ( ( P ), 5 ) + 12 )

#define MAKE_nspace_named( name_, parent_, size_, table_, c_class_nspace )\
    {\
	c_class *x453_ = GEN_c_class ( 13, TYPEID_nspace ) ;\
	x453_->ag_tag = 5 ;\
	COPY_id ( x453_ + 1, ( name_ ) ) ;\
	COPY_member ( x453_ + 2, NULL_member ) ;\
	COPY_member ( x453_ + 3, NULL_member ) ;\
	COPY_nspace ( x453_ + 4, ( parent_ ) ) ;\
	COPY_list ( x453_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x453_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x453_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x453_ + 8, LINK_NONE ) ;\
	COPY_member ( x453_ + 9, NULL_member ) ;\
	COPY_list ( x453_ + 10, NULL_list ( IDENTIFIER ) ) ;\
	COPY_ulong ( x453_ + 11, ( size_ ) ) ;\
	COPY_ptr ( x453_ + 12, ( table_ ) ) ;\
	( c_class_nspace ) = x453_ ;\
    }

#define DECONS_nspace_named( name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x454_ = CHECK_TAG ( ( c_class_nspace ), 5 ) ;\
	( name_ ) = DEREF_id ( x454_ + 1 ) ;\
	( last_ ) = DEREF_member ( x454_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x454_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x454_ + 4 ) ;\
	( use_ ) = DEREF_list ( x454_ + 5 ) ;\
	( join_ ) = DEREF_list ( x454_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x454_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x454_ + 8 ) ;\
	( first_ ) = DEREF_member ( x454_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x454_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x454_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x454_ + 12 ) ;\
    }

#define DESTROY_nspace_named( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x455_ = CHECK_TAG ( ( c_class_nspace ), 5 ) ;\
	( name_ ) = DEREF_id ( x455_ + 1 ) ;\
	( last_ ) = DEREF_member ( x455_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x455_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x455_ + 4 ) ;\
	( use_ ) = DEREF_list ( x455_ + 5 ) ;\
	( join_ ) = DEREF_list ( x455_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x455_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x455_ + 8 ) ;\
	( first_ ) = DEREF_member ( x455_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x455_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x455_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x455_ + 12 ) ;\
	( destroyer_ ) ( x455_, ( unsigned ) 13 ) ;\
    }


/* Operations for field unnamed of union NAMESPACE */

#define nspace_unnamed_tag		( ( unsigned ) 6 )
#define IS_nspace_unnamed( P )		( CHECK_NULL ( P )->ag_tag == 6 )

#define nspace_unnamed_first( P )	( CHECK_TAG ( ( P ), 6 ) + 9 )
#define nspace_unnamed_extra( P )	( CHECK_TAG ( ( P ), 6 ) + 10 )
#define nspace_unnamed_size( P )	( CHECK_TAG ( ( P ), 6 ) + 11 )
#define nspace_unnamed_table( P )	( CHECK_TAG ( ( P ), 6 ) + 12 )

#define MAKE_nspace_unnamed( name_, parent_, size_, table_, c_class_nspace )\
    {\
	c_class *x456_ = GEN_c_class ( 13, TYPEID_nspace ) ;\
	x456_->ag_tag = 6 ;\
	COPY_id ( x456_ + 1, ( name_ ) ) ;\
	COPY_member ( x456_ + 2, NULL_member ) ;\
	COPY_member ( x456_ + 3, NULL_member ) ;\
	COPY_nspace ( x456_ + 4, ( parent_ ) ) ;\
	COPY_list ( x456_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x456_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x456_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x456_ + 8, LINK_NONE ) ;\
	COPY_member ( x456_ + 9, NULL_member ) ;\
	COPY_list ( x456_ + 10, NULL_list ( IDENTIFIER ) ) ;\
	COPY_ulong ( x456_ + 11, ( size_ ) ) ;\
	COPY_ptr ( x456_ + 12, ( table_ ) ) ;\
	( c_class_nspace ) = x456_ ;\
    }

#define DECONS_nspace_unnamed( name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x457_ = CHECK_TAG ( ( c_class_nspace ), 6 ) ;\
	( name_ ) = DEREF_id ( x457_ + 1 ) ;\
	( last_ ) = DEREF_member ( x457_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x457_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x457_ + 4 ) ;\
	( use_ ) = DEREF_list ( x457_ + 5 ) ;\
	( join_ ) = DEREF_list ( x457_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x457_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x457_ + 8 ) ;\
	( first_ ) = DEREF_member ( x457_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x457_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x457_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x457_ + 12 ) ;\
    }

#define DESTROY_nspace_unnamed( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x458_ = CHECK_TAG ( ( c_class_nspace ), 6 ) ;\
	( name_ ) = DEREF_id ( x458_ + 1 ) ;\
	( last_ ) = DEREF_member ( x458_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x458_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x458_ + 4 ) ;\
	( use_ ) = DEREF_list ( x458_ + 5 ) ;\
	( join_ ) = DEREF_list ( x458_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x458_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x458_ + 8 ) ;\
	( first_ ) = DEREF_member ( x458_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x458_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x458_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x458_ + 12 ) ;\
	( destroyer_ ) ( x458_, ( unsigned ) 13 ) ;\
    }


/* Operations for field global of union NAMESPACE */

#define nspace_global_tag		( ( unsigned ) 7 )
#define IS_nspace_global( P )		( CHECK_NULL ( P )->ag_tag == 7 )

#define nspace_global_first( P )	( CHECK_TAG ( ( P ), 7 ) + 9 )
#define nspace_global_extra( P )	( CHECK_TAG ( ( P ), 7 ) + 10 )
#define nspace_global_size( P )		( CHECK_TAG ( ( P ), 7 ) + 11 )
#define nspace_global_table( P )	( CHECK_TAG ( ( P ), 7 ) + 12 )

#define MAKE_nspace_global( name_, parent_, size_, table_, c_class_nspace )\
    {\
	c_class *x459_ = GEN_c_class ( 13, TYPEID_nspace ) ;\
	x459_->ag_tag = 7 ;\
	COPY_id ( x459_ + 1, ( name_ ) ) ;\
	COPY_member ( x459_ + 2, NULL_member ) ;\
	COPY_member ( x459_ + 3, NULL_member ) ;\
	COPY_nspace ( x459_ + 4, ( parent_ ) ) ;\
	COPY_list ( x459_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x459_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x459_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x459_ + 8, LINK_NONE ) ;\
	COPY_member ( x459_ + 9, NULL_member ) ;\
	COPY_list ( x459_ + 10, NULL_list ( IDENTIFIER ) ) ;\
	COPY_ulong ( x459_ + 11, ( size_ ) ) ;\
	COPY_ptr ( x459_ + 12, ( table_ ) ) ;\
	( c_class_nspace ) = x459_ ;\
    }

#define DECONS_nspace_global( name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x460_ = CHECK_TAG ( ( c_class_nspace ), 7 ) ;\
	( name_ ) = DEREF_id ( x460_ + 1 ) ;\
	( last_ ) = DEREF_member ( x460_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x460_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x460_ + 4 ) ;\
	( use_ ) = DEREF_list ( x460_ + 5 ) ;\
	( join_ ) = DEREF_list ( x460_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x460_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x460_ + 8 ) ;\
	( first_ ) = DEREF_member ( x460_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x460_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x460_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x460_ + 12 ) ;\
    }

#define DESTROY_nspace_global( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x461_ = CHECK_TAG ( ( c_class_nspace ), 7 ) ;\
	( name_ ) = DEREF_id ( x461_ + 1 ) ;\
	( last_ ) = DEREF_member ( x461_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x461_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x461_ + 4 ) ;\
	( use_ ) = DEREF_list ( x461_ + 5 ) ;\
	( join_ ) = DEREF_list ( x461_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x461_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x461_ + 8 ) ;\
	( first_ ) = DEREF_member ( x461_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x461_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x461_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x461_ + 12 ) ;\
	( destroyer_ ) ( x461_, ( unsigned ) 13 ) ;\
    }


/* Operations for field ctype of union NAMESPACE */

#define nspace_ctype_tag		( ( unsigned ) 8 )
#define IS_nspace_ctype( P )		( CHECK_NULL ( P )->ag_tag == 8 )

#define nspace_ctype_first( P )		( CHECK_TAG ( ( P ), 8 ) + 9 )
#define nspace_ctype_extra( P )		( CHECK_TAG ( ( P ), 8 ) + 10 )
#define nspace_ctype_size( P )		( CHECK_TAG ( ( P ), 8 ) + 11 )
#define nspace_ctype_table( P )		( CHECK_TAG ( ( P ), 8 ) + 12 )

#define MAKE_nspace_ctype( name_, parent_, size_, table_, c_class_nspace )\
    {\
	c_class *x462_ = GEN_c_class ( 13, TYPEID_nspace ) ;\
	x462_->ag_tag = 8 ;\
	COPY_id ( x462_ + 1, ( name_ ) ) ;\
	COPY_member ( x462_ + 2, NULL_member ) ;\
	COPY_member ( x462_ + 3, NULL_member ) ;\
	COPY_nspace ( x462_ + 4, ( parent_ ) ) ;\
	COPY_list ( x462_ + 5, NULL_list ( NAMESPACE ) ) ;\
	COPY_list ( x462_ + 6, NULL_list ( NAMESPACE ) ) ;\
	COPY_stack ( x462_ + 7, NULL_stack ( IDENTIFIER ) ) ;\
	COPY_ulong ( x462_ + 8, LINK_NONE ) ;\
	COPY_member ( x462_ + 9, NULL_member ) ;\
	COPY_list ( x462_ + 10, NULL_list ( IDENTIFIER ) ) ;\
	COPY_ulong ( x462_ + 11, ( size_ ) ) ;\
	COPY_ptr ( x462_ + 12, ( table_ ) ) ;\
	( c_class_nspace ) = x462_ ;\
    }

#define DECONS_nspace_ctype( name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x463_ = CHECK_TAG ( ( c_class_nspace ), 8 ) ;\
	( name_ ) = DEREF_id ( x463_ + 1 ) ;\
	( last_ ) = DEREF_member ( x463_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x463_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x463_ + 4 ) ;\
	( use_ ) = DEREF_list ( x463_ + 5 ) ;\
	( join_ ) = DEREF_list ( x463_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x463_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x463_ + 8 ) ;\
	( first_ ) = DEREF_member ( x463_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x463_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x463_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x463_ + 12 ) ;\
    }

#define DESTROY_nspace_ctype( destroyer_, name_, last_, prev_, parent_, use_, join_, set_, dump_, first_, extra_, size_, table_, c_class_nspace )\
    {\
	c_class *x464_ = CHECK_TAG ( ( c_class_nspace ), 8 ) ;\
	( name_ ) = DEREF_id ( x464_ + 1 ) ;\
	( last_ ) = DEREF_member ( x464_ + 2 ) ;\
	( prev_ ) = DEREF_member ( x464_ + 3 ) ;\
	( parent_ ) = DEREF_nspace ( x464_ + 4 ) ;\
	( use_ ) = DEREF_list ( x464_ + 5 ) ;\
	( join_ ) = DEREF_list ( x464_ + 6 ) ;\
	( set_ ) = DEREF_stack ( x464_ + 7 ) ;\
	( dump_ ) = DEREF_ulong ( x464_ + 8 ) ;\
	( first_ ) = DEREF_member ( x464_ + 9 ) ;\
	( extra_ ) = DEREF_list ( x464_ + 10 ) ;\
	( size_ ) = DEREF_ulong ( x464_ + 11 ) ;\
	( table_ ) = DEREF_ptr ( x464_ + 12 ) ;\
	( destroyer_ ) ( x464_, ( unsigned ) 13 ) ;\
    }


#endif
