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


#ifndef CATALOG_INCLUDED
#define CATALOG_INCLUDED


/*
    ERROR CATALOGUE

    The macros and types defined in this module describe the error catalogue.
    Note that the main component of the catalogue is in the automatically
    generated file errors1.h.
*/

#define ERR_GEN		make_error
#define ERR_CONST	CONST

typedef DECL_SPEC ACCESS ;
typedef IDENTIFIER LONG_ID ;
typedef int LEX ;
typedef PTR ( LOCATION ) PTR_LOC ;
typedef int cint ;
typedef CONST char *cstring ;
typedef unsigned long ucint ;
typedef unsigned plural ;

#if c_class_SPECIFICATION
#define ERR_CHECK	1
#endif

#ifndef ERR_HEADER_OFF
#include "errors1.h"
#endif

extern void set_error_sev PROTO_S ( ( int, int ) ) ;
extern int find_error_no PROTO_S ( ( STRING, int ) ) ;
extern void init_catalog PROTO_S ( ( void ) ) ;
extern void term_catalog PROTO_S ( ( void ) ) ;
extern string find_vocab PROTO_S ( ( int ) ) ;
extern unsigned catalog_size ;


#endif
