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


#ifndef NODE_INCLUDED
#define NODE_INCLUDED


/*
    PROCEDURES FOR MANIPULATING NODES
*/

extern boolean dont_check ;
extern node *new_node PROTO_S ( ( void ) ) ;
extern void free_node PROTO_S ( ( node * ) ) ;
extern node *completion PROTO_S ( ( node * ) ) ;
extern boolean eq_node PROTO_S ( ( node *, node * ) ) ;


/*
    PROCEDURES FOR MANIPULATING CONSTRUCTS
*/

extern construct *new_construct PROTO_S ( ( void ) ) ;
extern construct *make_construct PROTO_S ( ( sortname ) ) ;
extern void copy_construct PROTO_S ( ( construct * ) ) ;
extern void free_construct PROTO_S ( ( construct ** ) ) ;
extern void set_token_sort PROTO_S ( ( construct *, sortname, char *, node * ) ) ;
extern void set_tag_type PROTO_S ( ( construct *, int ) ) ;
extern boolean is_local_name PROTO_S ( ( char * ) ) ;
extern char *skip_text PROTO_S ( ( char * ) ) ;
extern char *local_prefix ;


/*
    MACRO FOR RENUMBERING TOKEN CONSTRUCTS
*/

#define adjust_token( X )\
    if ( ( X )->encoding == -1 ) {\
	( X )->encoding = ( sort_count [ SORT_token ] )++ ;\
    }


#endif
