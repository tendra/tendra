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


#ifndef PATH_INCLUDED
#define PATH_INCLUDED


/*
    PATHNAME DECLARATIONS

    The routines in this directory are concerned with the construction
    of pathname structures.
*/

extern void init_pathname PROTO_S ( ( void ) ) ;
extern char *src_alias PROTO_S ( ( int ) ) ;
extern PATHNAME *make_pathname PROTO_S ( ( char *, int ) ) ;
extern PATHNAME *find_pathname PROTO_S ( ( PATHNAME *, char *, char *, int ) ) ;
extern PATHNAME *derived_pathname PROTO_S ( ( PATHNAME *, PATHNAME *, char * ) ) ;

extern char pathbuff [] ;
extern int dos_pathname ;

extern char *cpp_suffix ;
extern char *k_suffix ;

extern PATHNAME *root_dir ;
extern PATHNAME *current_dir ;
extern PATHNAME *home_dir ;
extern PATHNAME *work_dir ;
extern PATHNAME *nonexistant_dir ;
extern PATHNAME *anonymous_dir ;
extern PATHNAME *output_file ;

extern PATHNAME *o_files ;
extern PATHNAME *c_files ;
extern PATHNAME *h_files ;
extern PATHNAME *j_files ;
extern PATHNAME *k_files ;
extern PATHNAME *l_files ;
extern PATHNAME *y_files ;
extern PATHNAME *l_output ;
extern PATHNAME *y_output ;


#endif
