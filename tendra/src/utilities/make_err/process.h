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


#ifndef PROCESS_INCLUDED
#define PROCESS_INCLUDED


/*
    DECLARATIONS FOR PROCESSING ROUTINES
*/

extern char *db_name ;
extern char *db_name_alt ;
extern char *rig_name ;
extern char *rig_comp_output ;
extern char *rig_from_comp ;
extern char *rig_from_db ;
extern LIST ( ENTRY ) all_entries ;
extern LIST ( KEY ) all_keys ;
extern LIST ( PROPERTY ) all_props ;
extern LIST ( TYPE ) all_types ;
extern LIST ( USAGE ) all_usages ;
extern LIST ( KEY ) all_keys_aux ;
extern LIST ( PROPERTY ) all_props_aux ;
extern LIST ( TYPE ) all_types_aux ;
extern LIST ( USAGE ) all_usages_aux ;
extern LIST ( KEY ) all_keys_alt ;
extern LIST ( PROPERTY ) all_props_alt ;
extern LIST ( TYPE ) all_types_alt ;
extern LIST ( USAGE ) all_usages_alt ;
extern void output_all PROTO_S ( ( char *, int ) ) ;


#endif
