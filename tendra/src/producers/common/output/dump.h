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


#ifndef DUMP_INCLUDED
#define DUMP_INCLUDED


/*
    DUMP FILE VERSION NUMBER

    These macros give the major and minor version numbers for the dump
    files.  The minor number is increased for upwardly compatible changes
    and the major number for incompatible changes.
*/

#define DUMP_major	( ( unsigned long ) ( DUMP_VERSION / 100 ) )
#define DUMP_minor	( ( unsigned long ) ( DUMP_VERSION % 100 ) )


/*
    DUMP FILE DECLARATIONS

    The routines in this module are concerned with the output of the
    status dump file.
*/

extern void dump_declare PROTO_S ( ( IDENTIFIER, LOCATION *, int ) ) ;
extern void dump_undefine PROTO_S ( ( IDENTIFIER, LOCATION *, int ) ) ;
extern void dump_destr PROTO_S ( ( IDENTIFIER, LOCATION * ) ) ;
extern void dump_token PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern void dump_instance PROTO_S ( ( IDENTIFIER, TYPE, TYPE ) ) ;
extern void dump_use PROTO_S ( ( IDENTIFIER, LOCATION *, int ) ) ;
extern void dump_call PROTO_S ( ( IDENTIFIER, LOCATION *, int ) ) ;
extern void dump_override PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern void dump_alias PROTO_S ( ( IDENTIFIER, IDENTIFIER, LOCATION * ) ) ;
extern void dump_using PROTO_S ( ( NAMESPACE, NAMESPACE, LOCATION * ) ) ;
extern void dump_builtin PROTO_S ( ( IDENTIFIER ) ) ;
extern void dump_token_param PROTO_S ( ( IDENTIFIER ) ) ;
extern void dump_promote PROTO_S ( ( INT_TYPE, INT_TYPE ) ) ;
extern void dump_base PROTO_S ( ( CLASS_TYPE ) ) ;
extern void dump_begin_scope PROTO_S ( ( IDENTIFIER, NAMESPACE, NAMESPACE, LOCATION * ) ) ;
extern void dump_end_scope PROTO_S ( ( IDENTIFIER, NAMESPACE, LOCATION * ) ) ;
extern void dump_string_lit PROTO_S ( ( string, string, unsigned ) ) ;
extern void dump_include PROTO_S ( ( LOCATION *, string, int, int ) ) ;
extern int dump_error PROTO_S ( ( ERROR, LOCATION *, int, int ) ) ;
extern void init_dump PROTO_S ( ( string, string ) ) ;
extern void term_dump PROTO_S ( ( void ) ) ;

#ifdef FILE_INCLUDED
extern void dump_start PROTO_S ( ( LOCATION *, INCL_DIR * ) ) ;
extern void dump_end PROTO_S ( ( LOCATION * ) ) ;
#endif

extern ulong dump_id_next ;
extern int dump_anon_class ;
extern int dump_template ;
extern int dump_implicit ;

extern int do_dump ;
extern int do_error ;
extern int do_header ;
extern int do_keyword ;
extern int do_local ;
extern int do_macro ;
extern int do_scope ;
extern int do_string ;
extern int do_usage ;


#endif
