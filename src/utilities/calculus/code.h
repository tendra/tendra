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


#ifndef CODE_INCLUDED
#define CODE_INCLUDED


/*
    DECLARATIONS FOR MAIN C OUTPUT ROUTINES
*/

extern int extra_asserts ;
extern int extra_headers ;
extern int map_proto ;
extern void main_action_c PROTO_S ( ( char * ) ) ;
extern void print_deref PROTO_S ( ( TYPE_P, char *, char * ) ) ;
extern void print_proto PROTO_S ( ( void ) ) ;
extern void print_include PROTO_S ( ( void ) ) ;
extern void print_struct_defn PROTO_S ( ( void ) ) ;
extern void print_map_args PROTO_S ( ( char * ) ) ;
extern void print_enum_consts PROTO_S ( ( void ) ) ;
extern void print_union_map_c PROTO_S ( ( char *, char * ) ) ;
extern void print_union_hdr_c PROTO_S ( ( char *, char * ) ) ;
extern int field_not_empty PROTO_S ( ( void ) ) ;


#endif
