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


#include "config.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "copyright.h"
#include "environ.h"
#include "flags.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"


/*
    STRING VARIABLES

    These variables given various compilation values, including the
    location of the main temporary directory.
*/

char *api_info = "unknown" ;
char *api_output = API_ANAL_NAME ;
char *dump_opts = null ;
char *environ_dir = "." ;
char *final_name = null ;
char *machine_name = "unknown" ;
char *name_E_file = ENDUP_NAME ;
char *name_h_file = STARTUP_NAME ;
char *name_j_file = TDF_COMPLEX_NAME ;
char *name_k_file = C_SPEC_COMPLEX_NAME ;
char *name_K_file = CPP_SPEC_COMPLEX_NAME ;
char *name_p_file = TOKDEF_NAME ;
char *temporary_dir = "/usr/tmp" ;
char *tokdef_output = null ;
char *version_flag = "" ;


/*
    INTERNAL OPTIONS

    These variables control the overall behaviour of tcc.  For example,
    should we be running in verbose mode?
*/

boolean api_checks = 0 ;
boolean checker = 0 ;
boolean copyright = 0 ;
boolean dry_run = 0 ;
boolean link_specs = 1 ;
boolean make_up_names = 0 ;
boolean show_api = 0 ;
boolean show_errors = 0 ;
boolean suffix_overrides = 0 ;
boolean taciturn = 0 ;
boolean tidy_up = 0 ;
boolean time_commands = 0 ;
boolean verbose = 0 ;
boolean warnings = 1 ;


/*
    COMPILATION CONTROL OPTIONS

    These variables control the main compilation path taken.  For example,
    should we form a TDF archive?
*/


boolean make_archive = 0 ;
boolean make_complex = 0 ;
boolean make_preproc = 0 ;
boolean make_pretty = 0 ;
boolean make_tspec = 0 ;
boolean use_assembler = 1 ;
boolean use_mips_assembler = 0 ;
boolean use_alpha_assembler = 0 ; 
boolean use_hp_linker = 0 ;
boolean use_dynlink = 0 ;
boolean use_sparc_cc = 0 ;
boolean use_system_cc = 0 ;
boolean allow_cpp = 0 ;
boolean allow_notation = 0 ;
boolean allow_pl_tdf = 0 ;
boolean allow_specs = 0 ;


/*
    FILE PRESERVATION AND CONSTRUCTION OPTIONS

    These arrays control the creation and storage of the various file
    types.  In the keeps array, a nonzero value indicates that any file
    of this type which is created should be preserved.  In the stops
    array, it indicates that the compilation halts at this stage.  In
    either case, 0 means "false but changeable", 1 means "true but
    changeable", and 2 means "true and unchangeable".  The special
    variable, keep_ofiles, indicates whether all binary object files
    should be kept when more than one input file is given (this is for
    cc compatibility).  The keeps_aux array keeps track of the explicit
    file preservation options.  These tables need to be kept in step with
    Table 1.
*/

boolean keeps [ TYPE_ARRAY_SIZE ] = {
    0,	/* C_SOURCE */
    0,	/* PREPROC_C */
    0,	/* CPP_SOURCE */
    0,	/* PREPROC_CPP */
    0,	/* INDEP_TDF */
    0,	/* DEP_TDF */
    0,	/* AS_SOURCE */
    0,	/* BINARY_OBJ */
    2,	/* EXECUTABLE */
    1,	/* PRETTY_TDF */
    0,	/* PL_TDF */
    2,	/* TDF_ARCHIVE */
    0,	/* MIPS_G_FILE */
    0,	/* MIPS_T_FILE */
    0,	/* C_SPEC */
    0,	/* CPP_SPEC */
    0,	/* STARTUP_FILE */
    0,	/* UNKNOWN_TYPE */
    0,	/* INDEP_TDF_COMPLEX (dummy type) */
    0,	/* C_SPEC_1 (dummy type) */
    1,	/* C_SPEC_2 (dummy type) */
    0,	/* CPP_SPEC_1 (dummy type) */
    1,	/* CPP_SPEC_2 (dummy type) */
    0,	/* INDEP_TDF_AUX (dummy type) */
    0	/* BINARY_OBJ_AUX (dummy type) */
} ;

boolean keeps_aux [ TYPE_ARRAY_SIZE ] = {
    0,	/* C_SOURCE */
    0,	/* PREPROC_C */
    0,	/* CPP_SOURCE */
    0,	/* PREPROC_CPP */
    0,	/* INDEP_TDF */
    0,	/* DEP_TDF */
    0,	/* AS_SOURCE */
    0,	/* BINARY_OBJ */
    0,	/* EXECUTABLE */
    0,	/* PRETTY_TDF */
    0,	/* PL_TDF */
    0,	/* TDF_ARCHIVE */
    0,	/* MIPS_G_FILE */
    0,	/* MIPS_T_FILE */
    0,	/* C_SPEC */
    0,	/* CPP_SPEC */
    0,	/* STARTUP_FILE */
    0,	/* UNKNOWN_TYPE */
    0,	/* INDEP_TDF_COMPLEX (dummy type) */
    0,	/* C_SPEC_1 (dummy type) */
    0,	/* C_SPEC_2 (dummy type) */
    0,	/* CPP_SPEC_1 (dummy type) */
    0,	/* CPP_SPEC_2 (dummy type) */
    0,	/* INDEP_TDF_AUX (dummy type) */
    0	/* BINARY_OBJ_AUX (dummy type) */
} ;

boolean stops [ TYPE_ARRAY_SIZE ] = {
    0,	/* C_SOURCE */
    0,	/* PREPROC_C */
    0,	/* CPP_SOURCE */
    0,	/* PREPROC_CPP */
    0,	/* INDEP_TDF */
    0,	/* DEP_TDF */
    0,	/* AS_SOURCE */
    0,	/* BINARY_OBJ */
    2,	/* EXECUTABLE */
    2,	/* PRETTY_TDF */
    0,	/* PL_TDF */
    2,	/* TDF_ARCHIVE */
    0,	/* MIPS_G_FILE */
    0,	/* MIPS_T_FILE */
    0,	/* C_SPEC */
    0,	/* CPP_SPEC */
    0,	/* STARTUP_FILE */
    0,	/* UNKNOWN_TYPE */
    0,	/* INDEP_TDF_COMPLEX (dummy type) */
    0,	/* C_SPEC_1 (dummy type) */
    0,	/* C_SPEC_2 (dummy type) */
    0,	/* CPP_SPEC_1 (dummy type) */
    0,	/* CPP_SPEC_2 (dummy type) */
    0,	/* INDEP_TDF_AUX (dummy type) */
    0	/* BINARY_OBJ_AUX (dummy type) */
} ;

static boolean keep_all = 0 ;
static boolean keep_ofiles = 1 ;


/*
    INDIVIDUAL OPTIONS

    These flags control those individual executable options which are
    not easily integrated into the main scheme of things.
*/

boolean flag_diag = 0 ;
boolean flag_keep_err = 0 ;
boolean flag_incl = 0 ;
boolean flag_merge_all = 0 ;
boolean flag_nepc = 0 ;
boolean flag_no_files = 0 ;
boolean flag_optim = 0 ;
boolean flag_prof = 0 ;
boolean flag_startup = 1 ;
boolean flag_strip = 0 ;


/*
    EXECUTABLES

    These variables give the values of the various executables comprising
    the system.  For example, exec_produce gives the location of the C to
    TDF producer.
*/

list *exec_produce = null ;
list *exec_preproc = null ;
list *exec_cpp_produce = null ;
list *exec_cpp_preproc = null ;
list *exec_tdf_link = null ;
list *exec_translate = null ;
list *exec_assemble = null ;
list *exec_assemble_mips = null ;
list *exec_link = null ;
list *exec_notation = null ;
list *exec_pl_tdf = null ;
list *exec_pretty = null ;
list *exec_spec_link = null ;
list *exec_cpp_spec_link = null ;
list *exec_split_arch = null ;
list *exec_build_arch = null ;
list *exec_cat = null ;
list *exec_cc = null ;
list *exec_mkdir = null ;
list *exec_move = null ;
list *exec_remove = null ;
list *exec_touch = null ;
list *exec_dynlink = null ;
list *exec_dump_anal = null ;
list *exec_dump_link = null ;


/*
    BUILT-IN OPTIONS

    These lists of options are built into the system, although they may
    be altered by environments and command-line options.
*/

list *std_prod_incldirs = null ;
list *std_prod_portfile = null ;
list *std_prod_startdirs = null ;
list *std_prod_startup = null ;
list *std_cpp_prod_incldirs = null ;
list *std_cpp_prod_startdirs = null ;
list *std_cpp_prod_startup = null ;
list *std_tdf_link_libdirs = null ;
list *std_tdf_link_libs = null ;
list *std_link_crt0 = null ;
list *std_link_crt1 = null ;
list *std_link_crtp_n = null ;
list *std_link_crtn = null ;
list *std_link_libdirs = null ;
list *std_link_libs = null ;
list *std_link_c_libs = null ;
list *std_link_entry = null ;



/*
    COMMAND-LINE OPTIONS

    These lists of options are those specified on the command-line.
*/

list *usr_prod_incldirs = null ;
list *usr_prod_foptions = null ;
list *usr_prod_eoptions = null ;
list *usr_prod_startup = null ;
list *usr_cpp_prod_startup = null ;
list *usr_pl_tdf_incldirs = null ;
list *usr_tdf_link_libdirs = null ;
list *usr_tdf_link_libs = null ;
list *usr_link_libdirs = null ;
list *usr_link_libs = null ;


/*
    EXECUTABLE OPTIONS

    These lists record the command-line options which are passed
    directly to the various executables.
*/

list *opt_produce = null ;
list *opt_preproc = null ;
list *opt_cpp_produce = null ;
list *opt_cpp_preproc = null ;
list *opt_tdf_link = null ;
list *opt_translate = null ;
list *opt_assemble = null ;
list *opt_assemble_mips = null ;
list *opt_dynlink = null ;
list *opt_link = null ;
list *opt_notation = null ;
list *opt_pl_tdf = null ;
list *opt_pretty = null ;
list *opt_spec_link = null ;
list *opt_cpp_spec_link = null ;
list *opt_dump_anal = null ;
list *opt_dump_link = null ;
list *opt_archive = null ;
list *opt_joiner = null ;
list *opt_cc = null ;
list *opt_startup = null ;
list *opt_endup = null ;
list *opt_unknown = null ;


/*
    SET A KEEP OR STOP OPTION

    This routine sets a value in the keeps or stops arrays.  t gives
    the file type (including ALL_TYPES) and k gives the storage command
    (see flags.h).
*/

void set_stage
    PROTO_N ( ( t, k ) )
    PROTO_T ( int t X int k )
{
    if ( t == ALL_TYPES ) {
	boolean ks = keeps [ STARTUP_FILE ] ;
	if ( k == STOP_STAGE || k == STOP_ONLY_STAGE ) {
	    error ( WARNING, "Illegal stop option" ) ;
	} else if ( k == KEEP_STAGE ) {
	    int i ;
	    for ( i = 0 ; i < array_size ( keeps ) ; i++ ) {
		if ( keeps [i] == 0 ) keeps [i] = 1 ;
	    }
	    keep_all = 1 ;
	} else if ( k == DONT_KEEP_STAGE ) {
	    int i ;
	    for ( i = 0 ; i < array_size ( keeps ) ; i++ ) {
		if ( keeps [i] == 1 ) keeps [i] = 0 ;
	    }
	    keep_all = 0 ;
	    keep_ofiles = 0 ;
	}
	keeps [ STARTUP_FILE ] = ks ;
    } else {
	if ( k == STOP_STAGE || k == STOP_ONLY_STAGE ) {
	    static int last_stop = UNKNOWN_TYPE ;
	    if ( stops [t] == 0 ) stops [t] = 1 ;
	    if ( k == STOP_STAGE && keeps [t] == 0 ) keeps [t] = 1 ;
	    switch ( last_stop ) {
		case UNKNOWN_TYPE : {
		    break ;
		}
		case INDEP_TDF :
		case C_SPEC :
		case CPP_SPEC : {
		    if ( t == C_SPEC || t == CPP_SPEC ) break ;
		    if ( t == INDEP_TDF ) break ;
		    goto default_lab ;
		}
		case PREPROC_C :
		case PREPROC_CPP : {
		    if ( t == PREPROC_CPP ) {
			break ;
		    }
		    goto default_lab ;
		}
		default :
		default_lab : {
		    if ( t != last_stop ) {
			error ( WARNING, "More than one stop option given" ) ;
		    }
		    break ;
		}
	    }
	    last_stop = t ;
	} else if ( k == KEEP_STAGE ) {
	    if ( keeps [t] == 0 ) keeps [t] = 1 ;
	    keeps_aux [t] = 1 ;
	    if ( t == BINARY_OBJ ) keep_ofiles = 1 ;
	} else if ( k == DONT_KEEP_STAGE ) {
	    if ( keeps [t] == 1 ) keeps [t] = 0 ;
	    keeps_aux [t] = 2 ;
	    if ( t == BINARY_OBJ ) keep_ofiles = 0 ;
	}
    }
    return ;
}


/*
    SET THE MACHINE NAME

    This routine sets any special flags required by the machine indicated
    by machine_name.
*/

void set_machine
    PROTO_Z ()
{
#if 0
    char *mach = machine_name ;
    use_assembler = 1 ;
    use_mips_assembler = 0 ;
    use_alpha_assembler = 0 ;
    use_hp_linker = 0 ;
    if ( streq ( mach, "hp" ) || streq ( mach, "hppa" ) ) {
	use_hp_linker = 1 ;
    } else if ( streq ( mach, "mips" ) ) {
	use_mips_assembler = 1 ;
    } else if ( streq ( mach, "alpha" ) ) {
      use_alpha_assembler = 1 ;
    } else if ( streq ( mach, "sparc" ) || streq ( mach, "svr4_sparc" ) ) {
	use_sparc_cc = 1 ;
    } else if ( streq ( mach, "svr4_i386" ) ) {
	use_sparc_cc = 2 ;
    } else if ( streq ( mach, "transputer" ) ) {
	use_assembler = 0 ;
    }
#endif
    return ;
}


/*
    INITIALISE ALL OPTIONS

    This routine initialises any necessary values before the
    command-line options are read.
*/

void initialise_options
    PROTO_Z ()
{
    /* Initialise executables */
    list *p ;
    exec_produce = make_list ( "builtin/undef C_producer" ) ;
    exec_preproc = make_list ( "builtin/undef C_preprocessor" ) ;
    exec_cpp_produce = make_list ( "builtin/undef C++_producer" ) ;
    exec_cpp_preproc = make_list ( "builtin/undef C++_preprocessor" ) ;
    exec_tdf_link = make_list ( "builtin/undef TDF_linker" ) ;
    exec_translate = make_list ( "builtin/undef TDF_translator" ) ;
    exec_assemble = make_list ( "builtin/undef system_assembler" ) ;
    exec_assemble_mips = make_list ( "builtin/undef mips_assembler" ) ;
    exec_link = make_list ( "builtin/undef system_linker" ) ;
    exec_notation = make_list ( "builtin/undef TDF_notation_compiler" ) ;
    exec_pl_tdf = make_list ( "builtin/undef PL_TDF_compiler" ) ;
    exec_pretty = make_list ( "builtin/undef TDF_pretty_printer" ) ;
    exec_spec_link = make_list ( "builtin/undef C_spec_linker" ) ;
    exec_cpp_spec_link = make_list ( "builtin/undef C++_spec_linker" ) ;
    exec_split_arch = make_list ( "builtin/split_archive" ) ;
    exec_build_arch = make_list ( "builtin/build_archive" ) ;
    exec_cat = make_list ( "builtin/cat" ) ;
    exec_cc = make_list ( "builtin/undef system_compiler" ) ;
    exec_mkdir = make_list ( "builtin/mkdir" ) ;
    exec_move = make_list ( "builtin/move" ) ;
    exec_remove = make_list ( "builtin/remove" ) ;
    exec_touch = make_list ( "builtin/touch" ) ;
    exec_dynlink = make_list ( "builtin/undef dynamic_initialiser" ) ;

    /* Initialise other options */
    find_envpath () ;
    for ( p = opt_startup ; p != null ; p = p->next ) {
	add_to_startup ( p->item ) ;
    }
    for ( p = opt_endup ; p != null ; p = p->next ) {
	add_to_endup ( p->item ) ;
    }
    if ( checker ) allow_specs = 1 ;
    return ;
}


/*
    UPDATE ALL OPTIONS

    This routine updates the values of the variables above after all the
    command-line options have been read.  The stops options need to be
    kept in step with the general compilation scheme given in compile.c.
    Deciding which versions of certain file types to preserve (INDEP_TDF
    and C_SPEC in particular) gets pretty messy.
*/

void update_options
    PROTO_Z ()
{
    char *mode = null ;
    static boolean done_diag = 0 ;
    static boolean done_preproc = 0 ;
    static boolean done_prof = 0 ;
    static boolean done_time = 0 ;

    /* Process archive options */
    process_archive_opt () ;

    /* Deal with cc mode */
    if ( checker ) mode = "checker" ;
    if ( use_system_cc ) {
	if ( !checker ) {
	    error ( WARNING, "Using the system C compiler" ) ;
	}
	mode = "system compiler" ;
    }
    if ( mode ) {
	if ( make_archive ) {
	    error ( WARNING, "Can't build TDF archive in %s mode", mode ) ;
	    stops [ INDEP_TDF ] = 1 ;
	    make_archive = 0 ;
	}
	if ( make_complex ) {
	    error ( WARNING, "Can't build TDF complex in %s mode", mode ) ;
	    make_complex = 0 ;
	}
	if ( make_pretty ) {
	    error ( WARNING, "Can't pretty print TDF in %s mode", mode ) ;
	    stops [ INDEP_TDF ] = 1 ;
	    make_pretty = 0 ;
	}
	allow_notation = 0 ;
	allow_pl_tdf = 0 ;
    }

    /* Register extra stops */
    if ( make_archive ) set_stage ( TDF_ARCHIVE, STOP_STAGE ) ;
    if ( make_preproc ) {
	set_stage ( PREPROC_C, STOP_ONLY_STAGE ) ;
	set_stage ( PREPROC_CPP, STOP_ONLY_STAGE ) ;
    }
    if ( make_pretty ) set_stage ( PRETTY_TDF, STOP_STAGE ) ;

    /* Read special environments etc. */
    if ( make_preproc && keeps [ PREPROC_C ] && !done_preproc ) {
	read_env ( PREPROC_ENV ) ;
	done_preproc = 1 ;
    }
    if ( flag_diag && !done_diag ) {
	read_env ( DIAG_ENV ) ;
	done_diag = 1 ;
    }
    if ( flag_prof && !done_prof ) {
	read_env ( PROF_ENV ) ;
	done_prof = 1 ;
    }
    if ( time_commands && !done_time ) {
	read_env ( TIME_ENV ) ;
	done_time = 1 ;
    }

    /* Print API information */
    if ( show_api ) {
	error ( INFO, "API is %s", api_info ) ;
	show_api = 0 ;
    }

#if 0
    /* The option -Fk means stop after producer */
    if ( stops [ C_SPEC ] || stops [ CPP_SPEC ] ||
	 stops [ PREPROC_C ] || stops [ PREPROC_CPP ] ) {
	stops [ INDEP_TDF ] = 1 ;
    }
#endif

    /* Propagate stop options down */
    if ( stops [ INDEP_TDF ] ) {
	stops [ INDEP_TDF_COMPLEX ] = 1 ;
	stops [ DEP_TDF ] = 1 ;
	stops [ AS_SOURCE ] = 1 ;
	stops [ BINARY_OBJ ] = 1 ;
    } else if ( stops [ DEP_TDF ] ) {
	stops [ AS_SOURCE ] = 1 ;
	stops [ BINARY_OBJ ] = 1 ;
    } else if ( stops [ AS_SOURCE ] ) {
	stops [ BINARY_OBJ ] = 1 ;
    } else if ( stops [ MIPS_G_FILE ] ) {
	stops [ BINARY_OBJ ] = 1 ;
    } else if ( stops [ MIPS_T_FILE ] ) {
	stops [ BINARY_OBJ ] = 1 ;
    }

    /* Check keep options */
    if ( make_complex ) {
	if ( keeps [ INDEP_TDF ] ) {
	    keeps [ INDEP_TDF ] = keep_all ;
	    keeps [ INDEP_TDF_COMPLEX ] = 1 ;
	}
	if ( stops [ INDEP_TDF ] ) {
	    keeps [ C_SPEC_1 ] = 1 ;
	    keeps [ CPP_SPEC_1 ] = 1 ;
	}
    }
    if ( keeps [ C_SPEC ] ) {
	if ( make_complex ) {
	    keeps [ C_SPEC ] = keep_all ;
	    keeps [ C_SPEC_1 ] = 1 ;
	}
    } else {
	if ( keeps_aux [ C_SPEC ] == 2 ) {
	    keeps [ C_SPEC_1 ] = 0 ;
	    keeps [ C_SPEC_2 ] = 0 ;
	}
    }
    if ( keeps [ CPP_SPEC ] ) {
	if ( make_complex ) {
	    keeps [ CPP_SPEC ] = keep_all ;
	    keeps [ CPP_SPEC_1 ] = 1 ;
	}
    } else if ( keeps_aux [ CPP_SPEC ] == 2 ) {
	keeps [ CPP_SPEC_1 ] = 0 ;
	keeps [ CPP_SPEC_2 ] = 0 ;
    }
    if ( keep_ofiles && no_input_files > 1 && !make_complex ) {
	keeps [ BINARY_OBJ ] = 1 ;
    }
    if ( keeps_aux [ BINARY_OBJ ] == 1 ) {
	keeps [ BINARY_OBJ_AUX ] = 1 ;
    }
    if ( link_specs ) {
	boolean b ;
	if ( checker && !use_system_cc ) {
	    if ( keeps_aux [ BINARY_OBJ ] ) {
		b = 1 ;
	    } else if ( stops [ BINARY_OBJ ] && !stops [ AS_SOURCE ] ) {
		b = keeps [ BINARY_OBJ ] ;
	    } else {
		b = 0 ;
	    }
	} else {
	    b = keeps [ BINARY_OBJ ] ;
	}
	if ( b ) {
	    if ( make_complex ) {
		keeps [ C_SPEC_1 ] = 1 ;
		keeps [ CPP_SPEC_1 ] = 1 ;
	    } else {
		keeps [ C_SPEC ] = 1 ;
		keeps [ CPP_SPEC ] = 1 ;
	    }
	    keeps [ BINARY_OBJ_AUX ] = 1 ;
	}
    }

    /* Set checker options */
    if ( checker ) {
	if ( allow_specs == 0 ) allow_specs = 1 ;
	if ( !use_system_cc ) {
	    stops [ C_SPEC_2 ] = 1 ;
	    stops [ CPP_SPEC_2 ] = 1 ;
	}
    }

    /* Print the copyright message if required */
    if ( copyright ) {
	print_copyright () ;
	copyright = 0 ;
    }

    /* A couple of housekeeping routines */
    close_startup () ;
    find_envpath () ;
    return ;
}
