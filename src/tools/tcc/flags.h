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


#ifndef FLAGS_INCLUDED
#define FLAGS_INCLUDED


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with initialising and updating the
    values of the various compilation options.
*/

extern void initialise_options PROTO_S ( ( void ) ) ;
extern void update_options PROTO_S ( ( void ) ) ;
extern void set_machine PROTO_S ( ( void ) ) ;
extern void set_stage PROTO_S ( ( int, int ) ) ;


/*
    STRING VARIABLES

    These variables give various compilation constants.
*/

extern char *api_info ;
extern char *api_output ;
extern char *dump_opts ;
extern char *environ_dir ;
extern char *final_name ;
extern char *machine_name ;
extern char *name_E_file ;
extern char *name_h_file ;
extern char *name_j_file ;
extern char *name_k_file ;
extern char *name_K_file ;
extern char *name_d_file ;
extern char *name_p_file ;
extern char *temporary_dir ;
extern char *tokdef_output ;
extern char *version_flag ;


/*
    INTERNAL OPTIONS

    These variables control the behaviour of tcc.
*/

extern boolean api_checks ;
extern boolean checker ;
extern boolean copyright ;
extern boolean dry_run ;
extern boolean link_specs ;
extern boolean make_up_names ;
extern boolean show_api ;
extern boolean show_errors ;
extern boolean suffix_overrides ;
extern boolean taciturn ;
extern boolean tidy_up ;
extern boolean time_commands ;
extern boolean verbose ;
extern boolean warnings ;


/*
    COMPILATION CONTROL OPTIONS

    These variables control the overall flow of the compilation.
*/


extern boolean make_archive ;
extern boolean make_complex ;
extern boolean make_preproc ;
extern boolean make_pretty ;
extern boolean make_tspec ;
extern boolean use_assembler ;
extern boolean use_mips_assembler ;
extern boolean use_alpha_assembler ;
extern boolean use_hp_linker ;
extern boolean use_sparc_cc ;
extern boolean use_system_cc ;
extern boolean use_dynlink ;
extern boolean allow_cpp ;
extern boolean allow_notation ;
extern boolean allow_pl_tdf ;
extern boolean allow_specs ;


/*
    FILE PRESERVATION AND CONSTRUCTION OPTIONS

    These tables control whether output files of the various file types
    should be kept and whether the compilation stops after they are
    produced.
*/

extern boolean keeps [] ;
extern boolean keeps_aux [] ;
extern boolean stops [] ;


/*
    EXTRA FILE TYPES

    These dummy file types are in addition to those listed in filename.h.
    They are used in the keeps and stops arrays to resolve questions about,
    for example, TDF building, which in terms of file types maps :

		INDEP_TDF x ... x INDEP_TDF -> INDEP_TDF

    By introducing a dummy type for the output we can refine the keeps and
    stops information to, for example, keep the output but not the input.
*/

#define INDEP_TDF_COMPLEX	( UNKNOWN_TYPE + 1 )
#define C_SPEC_1		( UNKNOWN_TYPE + 2 )
#define C_SPEC_2		( UNKNOWN_TYPE + 3 )
#define CPP_SPEC_1		( UNKNOWN_TYPE + 4 )
#define CPP_SPEC_2		( UNKNOWN_TYPE + 5 )
#define INDEP_TDF_AUX		( UNKNOWN_TYPE + 6 )
#define BINARY_OBJ_AUX		( UNKNOWN_TYPE + 7 )
#define TYPE_ARRAY_SIZE		( UNKNOWN_TYPE + 8 )


/*
    PRESERVATION AND CONSTRUCTION FLAGS

    These identifiers are used by set_stage to set the keeps and stops
    options for the various file types.  STOP_STAGE means "stop and keep",
    STOP_ONLY_STAGE means "stop", KEEP_STAGE means "keep" and
    DONT_KEEP_STAGE means "don't keep".
*/

#define STOP_STAGE		0
#define STOP_ONLY_STAGE		1
#define KEEP_STAGE		2
#define DONT_KEEP_STAGE		3


/*
    INDIVIDUAL OPTIONS

    These flags control those individual executable options which are
    not easily integrated into the main scheme of things.
*/

extern boolean flag_diag ;
extern boolean flag_incl ;
extern boolean flag_keep_err ;
extern boolean flag_merge_all ;
extern boolean flag_nepc ;
extern boolean flag_no_files ;
extern boolean flag_optim ;
extern boolean flag_prof ;
extern boolean flag_startup ;
extern boolean flag_strip ;


/*
    EXECUTABLES

    These variables give the values of the various executables used by
    the system.
*/

extern list *exec_produce ;
extern list *exec_preproc ;
extern list *exec_cpp_produce ;
extern list *exec_cpp_preproc ;
extern list *exec_tdf_link ;
extern list *exec_translate ;
extern list *exec_assemble ;
extern list *exec_assemble_mips ;
extern list *exec_link ;
extern list *exec_notation ;
extern list *exec_pl_tdf ;
extern list *exec_pretty ;
extern list *exec_spec_link ;
extern list *exec_cpp_spec_link ;
extern list *exec_split_arch ;
extern list *exec_build_arch ;
extern list *exec_cat ;
extern list *exec_cc ;
extern list *exec_mkdir ;
extern list *exec_move ;
extern list *exec_remove ;
extern list *exec_touch ;
extern list *exec_dynlink ;
extern list *exec_dump_anal ;
extern list *exec_dump_link ;


/*
    BUILT-IN OPTIONS

    These lists of options are built into the system, although they may
    be altered by environments and command-line options.
*/

extern list *std_prod_incldirs ;
extern list *std_prod_portfile ;
extern list *std_prod_startdirs ;
extern list *std_prod_startup ;
extern list *std_cpp_prod_incldirs ;
extern list *std_cpp_prod_startdirs ;
extern list *std_cpp_prod_startup ;
extern list *std_tdf_link_libdirs ;
extern list *std_tdf_link_libs ;
extern list *std_link_crt0 ;
extern list *std_link_crt1 ;
extern list *std_link_crtp_n ;
extern list *std_link_crtn ;
extern list *std_link_libdirs ;
extern list *std_link_libs ;
extern list *std_link_c_libs ;
extern list *std_link_entry ;


/*
    COMMAND-LINE OPTIONS

    These lists of options are those specified on the command-line.
*/

extern list *usr_prod_incldirs ;
extern list *usr_prod_foptions ;
extern list *usr_prod_eoptions ;
extern list *usr_prod_startup ;
extern list *usr_cpp_prod_startup ;
extern list *usr_pl_tdf_incldirs ;
extern list *usr_tdf_link_libdirs ;
extern list *usr_tdf_link_libs ;
extern list *usr_link_libdirs ;
extern list *usr_link_libs ;


/*
    EXECUTABLE OPTIONS

    These lists record the command-line options which are passed
    directly to the various executables.
*/

extern list *opt_produce ;
extern list *opt_preproc ;
extern list *opt_cpp_produce ;
extern list *opt_cpp_preproc ;
extern list *opt_tdf_link ;
extern list *opt_translate ;
extern list *opt_assemble ;
extern list *opt_assemble_mips ;
extern list *opt_dynlink ;
extern list *opt_link ;
extern list *opt_notation ;
extern list *opt_pl_tdf ;
extern list *opt_pretty ;
extern list *opt_spec_link ;
extern list *opt_cpp_spec_link ;
extern list *opt_dump_anal ;
extern list *opt_dump_link ;
extern list *opt_archive ;
extern list *opt_joiner ;
extern list *opt_cc ;
extern list *opt_startup ;
extern list *opt_endup ;
extern list *opt_unknown ;


#endif
