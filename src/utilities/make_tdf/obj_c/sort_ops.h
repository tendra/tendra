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

#ifndef SORT_OPS_H_INCLUDED
#define SORT_OPS_H_INCLUDED

/* Operations for union SORT */

#define TAG_sort( P )			( ( unsigned ) 0 )


/* Operations for component name of union SORT */

#define sort_name( P )			( CHECK_NULL ( P ) + 0 )


/* Operations for component caps of union SORT */

#define sort_caps( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for component link of union SORT */

#define sort_link( P )			( CHECK_NULL ( P ) + 2 )


/* Operations for component unit of union SORT */

#define sort_unit( P )			( CHECK_NULL ( P ) + 3 )


/* Operations for component code of union SORT */

#define sort_code( P )			( CHECK_NULL ( P ) + 4 )


/* Operations for component mark of union SORT */

#define sort_mark( P )			( CHECK_NULL ( P ) + 5 )


/* Operations for component special of union SORT */

#define sort_special( P )		( CHECK_NULL ( P ) + 6 )


/* Operations for component edge of union SORT */

#define sort_edge( P )			( CHECK_NULL ( P ) + 7 )


/* Operations for component info of union SORT */

#define sort_info( P )			( CHECK_NULL ( P ) + 8 )


/* Operations for field basic of union SORT */

#define sort_basic_tag			( ( unsigned ) 0 )
#define IS_sort_basic( P )		1


#define MAKE_sort_basic( name_, caps_, link_, unit_, code_, mark_, special_, edge_, info_, tdf_sort )\
    {\
	tdf *x93_ = GEN_tdf ( 9, TYPEID_sort ) ;\
	COPY_string ( x93_ + 0, ( name_ ) ) ;\
	COPY_string ( x93_ + 1, ( caps_ ) ) ;\
	COPY_string ( x93_ + 2, ( link_ ) ) ;\
	COPY_string ( x93_ + 3, ( unit_ ) ) ;\
	COPY_int ( x93_ + 4, ( code_ ) ) ;\
	COPY_int ( x93_ + 5, ( mark_ ) ) ;\
	COPY_int ( x93_ + 6, ( special_ ) ) ;\
	COPY_int ( x93_ + 7, ( edge_ ) ) ;\
	COPY_info ( x93_ + 8, ( info_ ) ) ;\
	( tdf_sort ) = x93_ ;\
    }

#define DECONS_sort_basic( name_, caps_, link_, unit_, code_, mark_, special_, edge_, info_, tdf_sort )\
    {\
	tdf *x94_ = ( tdf_sort ) ;\
	( name_ ) = DEREF_string ( x94_ + 0 ) ;\
	( caps_ ) = DEREF_string ( x94_ + 1 ) ;\
	( link_ ) = DEREF_string ( x94_ + 2 ) ;\
	( unit_ ) = DEREF_string ( x94_ + 3 ) ;\
	( code_ ) = DEREF_int ( x94_ + 4 ) ;\
	( mark_ ) = DEREF_int ( x94_ + 5 ) ;\
	( special_ ) = DEREF_int ( x94_ + 6 ) ;\
	( edge_ ) = DEREF_int ( x94_ + 7 ) ;\
	( info_ ) = DEREF_info ( x94_ + 8 ) ;\
    }

#define DESTROY_sort_basic( destroyer_, name_, caps_, link_, unit_, code_, mark_, special_, edge_, info_, tdf_sort )\
    {\
	tdf *x95_ = ( tdf_sort ) ;\
	( name_ ) = DEREF_string ( x95_ + 0 ) ;\
	( caps_ ) = DEREF_string ( x95_ + 1 ) ;\
	( link_ ) = DEREF_string ( x95_ + 2 ) ;\
	( unit_ ) = DEREF_string ( x95_ + 3 ) ;\
	( code_ ) = DEREF_int ( x95_ + 4 ) ;\
	( mark_ ) = DEREF_int ( x95_ + 5 ) ;\
	( special_ ) = DEREF_int ( x95_ + 6 ) ;\
	( edge_ ) = DEREF_int ( x95_ + 7 ) ;\
	( info_ ) = DEREF_info ( x95_ + 8 ) ;\
	( destroyer_ ) ( x95_, ( unsigned ) 9 ) ;\
    }


#endif
