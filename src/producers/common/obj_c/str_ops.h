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

#ifndef STR_OPS_H_INCLUDED
#define STR_OPS_H_INCLUDED

/* Operations for union STRING */

#define TAG_str( P )			( ( unsigned ) 0 )


/* Operations for component next of union STRING */

#define str_next( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for field simple of union STRING */

#define str_simple_tag			( ( unsigned ) 0 )
#define IS_str_simple( P )		1

#define str_simple_len( P )		( ( P ) + 1 )
#define str_simple_text( P )		( ( P ) + 2 )
#define str_simple_kind( P )		( ( P ) + 3 )
#define str_simple_tok( P )		( ( P ) + 4 )

#define MAKE_str_simple( len_, text_, kind_, c_class_str )\
    {\
	c_class *x483_ = GEN_c_class ( 5, TYPEID_str ) ;\
	COPY_str ( x483_ + 0, NULL_str ) ;\
	COPY_ulong ( x483_ + 1, ( len_ ) ) ;\
	COPY_string ( x483_ + 2, ( text_ ) ) ;\
	COPY_unsigned ( x483_ + 3, ( kind_ ) ) ;\
	COPY_ulong ( x483_ + 4, LINK_NONE ) ;\
	( c_class_str ) = x483_ ;\
    }

#define DECONS_str_simple( next_, len_, text_, kind_, tok_, c_class_str )\
    {\
	c_class *x484_ = ( c_class_str ) ;\
	( next_ ) = DEREF_str ( x484_ + 0 ) ;\
	( len_ ) = DEREF_ulong ( x484_ + 1 ) ;\
	( text_ ) = DEREF_string ( x484_ + 2 ) ;\
	( kind_ ) = DEREF_unsigned ( x484_ + 3 ) ;\
	( tok_ ) = DEREF_ulong ( x484_ + 4 ) ;\
    }

#define DESTROY_str_simple( destroyer_, next_, len_, text_, kind_, tok_, c_class_str )\
    {\
	c_class *x485_ = ( c_class_str ) ;\
	( next_ ) = DEREF_str ( x485_ + 0 ) ;\
	( len_ ) = DEREF_ulong ( x485_ + 1 ) ;\
	( text_ ) = DEREF_string ( x485_ + 2 ) ;\
	( kind_ ) = DEREF_unsigned ( x485_ + 3 ) ;\
	( tok_ ) = DEREF_ulong ( x485_ + 4 ) ;\
	( destroyer_ ) ( x485_, ( unsigned ) 5 ) ;\
    }


#endif
