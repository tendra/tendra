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


#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED


/*
    TABLES OF CONSTRUCTS
*/

extern construct **cons_table ;
extern construct **var_table ;
extern construct **cons_hash_tables ;


/*
    TABLES OF SORT INFORMATION
*/

typedef node *( *decode_func ) PROTO_S ( ( void ) ) ;
typedef node *( *read_func ) PROTO_S ( ( long ) ) ;
extern long *sort_count ;
extern char *sort_letters ;
extern int *sort_encoding ;
extern int *sort_extension ;
extern long *sort_tokens ;
extern long *sort_conds ;
extern long *sort_removed ;
extern decode_func *sort_decode ;
extern read_func *sort_read ;


/*
    SPECIAL CONSTRUCTS
*/

extern construct bytestream_cons ;
extern construct false_cons ;
extern construct optional_cons ;
extern construct string_cons ;
extern construct token_cons ;
extern construct true_cons ;
extern construct unknown_cons ;
extern construct exp_shape ;
extern construct shape_of ;


/*
    OUTPUT FLAGS
*/

extern boolean show_tokdecs ;
extern boolean show_tokdefs ;
extern boolean show_aldecs ;
extern boolean show_aldefs ;
extern boolean show_tagdecs ;
extern boolean show_tagdefs ;


/*
    TABLE MANIPULATION ROUTINES
*/

extern void init_tables PROTO_S ( ( void ) ) ;
extern construct *add_to_cons_hash PROTO_S ( ( construct *, sortname ) ) ;
extern construct *search_cons_hash PROTO_S ( ( char *, sortname ) ) ;
extern construct *add_to_var_hash PROTO_S ( ( construct *, sortname ) ) ;
extern construct *search_var_hash PROTO_S ( ( char *, sortname ) ) ;
extern void remove_var_hash PROTO_S ( ( char *, sortname ) ) ;
extern construct *removals ;


/*
    TABLE UTILITY ROUTINES
*/

extern boolean order_names ;
typedef void ( *apply_func ) PROTO_S ( ( construct * ) ) ;
extern char *sort_name PROTO_S ( ( sortname ) ) ;
extern void sort_table PROTO_S ( ( construct **, sortname ) ) ;
extern void sort_all PROTO_S ( ( void ) ) ;
extern void apply_to_all PROTO_S ( ( apply_func, sortname ) ) ;


/*
    AUXILLIARY TABLE ROUTINES
*/

extern void new_sort PROTO_S ( ( sortname, int ) ) ;
extern void new_cons PROTO_S ( ( char *, sortname, int, char * ) ) ;


/*
    MACRO FOR ACCESSING CONSTRUCTS
*/

#define cons_no( X, Y )		( cons_table [ ( X ) ] + ( Y ) )


#endif
