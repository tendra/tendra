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


#ifndef STAGES_INCLUDED
#define STAGES_INCLUDED


/*
    PROCEDURE DECLARATIONS

    These routines perform the main compilation tasks, one routine
    corresponding to each compilation phase.  Each routine takes a
    list of input files and returns a list of output files.
*/

extern filename *do_produce PROTO_S ( ( filename * ) ) ;
extern filename *do_preproc PROTO_S ( ( filename * ) ) ;
extern filename *do_cpp_produce PROTO_S ( ( filename * ) ) ;
extern filename *do_cpp_preproc PROTO_S ( ( filename * ) ) ;
extern filename *do_tdf_link PROTO_S ( ( filename * ) ) ;
extern filename *do_tdf_build PROTO_S ( ( filename * ) ) ;
extern filename *do_translate PROTO_S ( ( filename * ) ) ;
extern filename *do_assemble PROTO_S ( ( filename * ) ) ;
extern filename *do_dynlink PROTO_S ( ( filename * ) ) ;
extern filename *do_link PROTO_S ( ( filename * ) ) ;
extern filename *do_notation PROTO_S ( ( filename * ) ) ;
extern filename *do_pl_tdf PROTO_S ( ( filename * ) ) ;
extern filename *do_pretty PROTO_S ( ( filename * ) ) ;
extern filename *do_split_arch PROTO_S ( ( filename * ) ) ;
extern filename *do_build_arch PROTO_S ( ( filename * ) ) ;
extern filename *do_build_file PROTO_S ( ( filename *, int ) ) ;
extern filename *do_link_specs PROTO_S ( ( filename *, int ) ) ;
extern filename *do_cc PROTO_S ( ( filename *, int ) ) ;
extern filename *do_keep PROTO_S ( ( filename * ) ) ;
extern int binary_obj_type ;


#endif
