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


#ifndef BASIC_INCLUDED
#define BASIC_INCLUDED


/*
    BASIC TDF DECODING ROUTINES

    This file contains the basic decoding routines for TDF integers,
    strings etc.
*/

extern external de_extern_name PROTO_S ( ( void ) ) ;
extern sortid de_sort_name PROTO_S ( ( int ) ) ;
extern string de_tdfstring PROTO_S ( ( void ) ) ;
extern string de_tdfstring_align PROTO_S ( ( void ) ) ;
extern unique de_unique PROTO_S ( ( void ) ) ;
extern long fetch_extn PROTO_S ( ( int ) ) ;
extern long tdf_int PROTO_S ( ( void ) ) ;
extern char *tdf_int_str PROTO_S ( ( void ) ) ;
extern string get_string PROTO_S ( ( long, long ) ) ;
extern void add_foreign_sort PROTO_S ( ( char *, char *, int ) ) ;
extern int tdf_int_digits ;
extern sortid *foreign_sorts ;
extern long no_foreign_sorts ;
extern int do_foreign_sorts ;

#define tdf_bool()		( fetch ( 1 ) )

#define check_list()\
	if ( fetch ( 1 ) ) {\
	    out ( "<error>" ) ;\
	    input_error ( "Illegal LIST value" ) ;\
	}


/*
    START OF EXTRA SORTS

    Normal TDF sorts are represented by small values (see tdf.h).  Foreign
    sorts are represented by values starting at extra_sorts.
*/

#define extra_sorts     100


#endif
