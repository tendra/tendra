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


#ifndef TYPEID_INCLUDED
#define TYPEID_INCLUDED


/*
    RUN-TIME TYPE INFORMATION

    The routines in this module are concerned with the run-time type
    information constructs, typeid and dynamic_cast.
*/

extern TYPE find_std_type PROTO_S ( ( CONST char *, int, int ) ) ;
extern EXP make_typeid_exp PROTO_S ( ( int, EXP, int ) ) ;
extern EXP make_typeid_type PROTO_S ( ( int, TYPE, int ) ) ;
extern EXP make_dynamic_cast_exp PROTO_S ( ( TYPE, EXP, int ) ) ;
extern void set_std_namespace PROTO_S ( ( IDENTIFIER ) ) ;
extern TYPE get_type_info PROTO_S ( ( int, TYPE, int ) ) ;


#endif
