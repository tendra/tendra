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
#include "environ.h"
#include "flags.h"
#include "main.h"
#include "options.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"


/*
    THE LIST OF ALL INPUT FILES

    All input files found by process_options are added to this list.
*/

filename *input_files = null ;


/*
    THE MAIN OPTION MAP

    This table gives all the command-line options.
*/

optmap main_optmap [] = {
    /* Common options */
    { "^-$", "I?$0", "specifies an input file" },
    { "-o+$", "SFN$1", "specifies output file name" },
    { "-D+$=$", "D#define$s$1$s$2$n|AOC$0", "defines a macro" },
    { "-D+$", "D#define$s$1$s1$n|AOC$0", "defines a macro to be 1" },
    { "-F?", "H$1", "halts the compilation at the given stage" },
    { "-I+$", "AUI$0|AOC$0|AUP$0", "specifies an include file directory" },
    { "-L+$", "1ON|Io$0|AUL$0", "specifies a system library directory" },
    { "-N+$:+$", "AUI$0|AOC-I$2",
		 "specifies an include file directory (with mode)" },
    { "-O$", "1OP|AOC$0", "switches optimisation level" },
    { "-P?*", "K$1", "causes intermediate files to be preserved" },
    { "-S", "Hs", "halts compilation after creating .s files" },
    { "-T+$", "CAT:$1|AOC-D$1", "specifies a command-line token" },
    { "-U+$", "D#undef$s$1$n|AOC$0", "undefines a macro" },
    { "-W?,+$,+*", "AQ$1$2", "passed an option to a compilation tool" },
    { "-W?:+$", "AQ$1$2", "passed an option to a compilation tool" },
    { "-X:+$,+*", "CAP:$1", "specifies a compilation option" },
    { "-X$", "EX$1", "specifies a compilation mode" },
    { "-Y+$", "E$1", "reads an environment" },
    { "-copyright", "1CR", "outputs copyright notice" },
    { "-c", "Ho", "halts compilation after creating .o files" },
    { "-d", "Hd", "halts compilation after creating .d files" },
    { "-dry", "1VB|1DR", "causes a dry run"  },
    { "-e+$", "AUe$0", "specifies a producer end-up file" },
    { "-f+$", "AUf$0", "specifies a producer start-up file" },
    { "-g", "1DG", "produces debugging information (default format)" },
    { "-g1", "1DG", "produces debugging information (old format)" },
    { "-g2", "2DG", "produces debugging information (new format)" },
    { "-g3", "3DG", "produces debugging information (new format)" },
    { "-k", "Hk|HK", "halts compilation after creating .k and .K files" },
    { "-l+$", "1ON|Io$0|AUl$0", "specifies a system library" },
    { "-not_ansi", "ASs-fnot_ansi", "allows some non-ANSI C features" },
    { "-nepc", "1NE|ASs-fnepc", "switches off extra portability checks" },
    { "-sym", "1CS|SDO-d=", "enables symbol table dump linking" },
    { "-sym:$", "1CS|SDO-d$1=", "enables symbol table dump linking with flags" },
    { "-v", "1VB", "specifies verbose mode" },
    { "-vb", "1TC", "specifies fairly verbose mode" },

    /* Options not allowed in checker */
    { "-J+$", "AUJ-L$1", "specifies a TDF library directory" },
    { "-M", "1MC", "causes all .j files to be merged" },
    { "-MA", "1MC|1MP", "as -M, but with hiding" },
    { "-ch", "1CH", "invokes checker mode" },
    { "-disp", "1PP", "causes all .j files to be pretty printed" },
    { "-disp_t", "2PP", "causes all .t files to be pretty printed" },
    { "-i", "Hj", "halts compilation after creating .j files" },
    { "-im", "1CS", "enables intermodular checks" },
    { "-j+$", "AUj-l$1", "specifies a TDF library" },
    { "-prod", "1AR", "causes a TDF archive to be produced" },

    /* Less common options */
    { "-A+-", "AOC$0", "unasserts all built-in predicates" },
    { "-A+$", "D#pragma$saccept$sdirective$sassert$n|D#assert$s$1$n|AOC$0",
	      "asserts a predicate" },
    { "-B+$", "1ON|Io$0", "passed to the system linker" },
    { "-C", "AOC$0", "preserves comments when preprocessing" },
    { "-E", "1PR", "causes C source files to be preprocessed" },
    { "-E?:+$", "LE$1$2", "specifies an executable to be used" },
    { "-H", "1PI", "causes included files to be printed" },
    { "-S?,+$,+*", "I$1$2", "specifies input files" },
    { "-S?:+$", "I$1$2", "specifies input files" },
    { "-V", "EVersions|1CR", "causes all tools to print their version numbers" },
    { "-cc", "1CC", "forces the system compiler to be used" },
    { "-cc_only", "2CC", "forces only the system compiler to be used" },
    { "-do?+$", "SN$1$2", "sets a default output file name" },
    { "-dump", "CDS", "dumps the current status" },
    { "-ignore_case", "1LC", "ignores case in file names" },
    { "-im0", "2CS", "disables intermodular checks" },
    { "-info", "1SA", "causes API information to be printed" },
    { "-keep_errors", "1KE", "causes files to be preserved on errors" },
    { "-make_up_names", "1MN", "makes up names for intermediate files" },
    { "-message+$", "@X$1", "causes %s to print a message" },
    { "-p", "1PF", "causes profiling information to be produced" },
    { "-q", "0VB", "specifies quiet mode" },
    { "-quiet", "0VB", "equivalent to -q" },
    { "-query", "Q", "causes a list of options to be printed" },
    { "-s?:+$", "SS$1$2|1SO", "specifies a suffix override" },
    { "-show_errors", "1SE", "causes error producing commands to be shown" },
    { "-show_env", "CSE", "causes the environment path to be printed" },
    { "-special+$", "SXX$1|CSP", "allows various internal options" },
    { "-startup+$", "@D$1$n", "specifies a start-up option" },
    { "-target+$", "AOC-target|AOC$1", "provided for cc compatibility" },
    { "-temp+$", "STD$1", "specifies the temporary directory" },
    { "-tidy", "1TU", "causes %s to tidy up as it goes along" },
    { "-time", "1TI|1VB", "causes all commands to be timed" },
    { "-verbose", "1VB", "equivalent to -v" },
    { "-version", "CPV", "causes %s to print its version number" },
    { "-w", "0WA", "suppresses %s warnings" },
    { "-work+$", "SWD$1", "specifies the work directory" },

    /* Options not allowed in checker */
    { "-G", "EGoption", "provided for cc compatibility" },
    { "-K+$,+*", "EK-$1", "provided for cc compatibility" },
    { "-Z$", "EZ-$1", "provided for cc compatibility" },
    { "-b", "LSc", "suppresses -lc in system linking" },
    { "-dn", "AOl$0", "passed to the system linker" },
    { "-dy", "AOl$0", "passed to the system linker" },
    { "-h+$", "AOl$0", "passed to the system linker" },
    { "-no_startup_options", "0ST", "suppresses start-up options" },
    { "-s", "1SR", "passed to the system linker" },
    { "-u+$", "AOl$0", "passed to the system linker" },
    { "-wsl", "Ewsl", "causes string literals to be made writable" },
    { "-z+$", "AOl$0", "passed to the system linker" },
    { "-#", "1VB", "equivalent to -v" },
    { "-##", "1VB", "equivalent to -v" },
    { "-###", "1VB|1DR", "equivalent to -dry" },

    /* Default options */
    { "--+$,+*", "$1", "communicates directly with the option interpreter" },
    { "$", "XUnknown option,$s$0|AXO$0", "unknown option" },

    /* End marker */
    { null, null, null }
} ;


/*
    THE ENVIRONMENT OPTION MAP

    This table gives all the environment options.  It needs to be kept
    in line with Table 4.
*/

optmap environ_optmap [] = {
    /* Options */
    { "\\+FLAG $", "=$1", null },
    { "\\+FLAG_TDFC $", "AOc$1", null },
    { "\\+FLAG_TDFCPP $", "AOp$1", null },
    { "\\+FLAG_TCPPLUS $", "AOx$1", null },
    { "\\+FLAG_TCPPLUSPP $", "AOg$1", null },
    { "\\+FLAG_TOT_CAT $", "", null },
    { "\\+FLAG_TLD $", "AOL$1", null },
    { "\\+FLAG_TRANS $", "AOt$1", null },
    { "\\+FLAG_AS $", "AOa$1", null },
    { "\\+FLAG_DYN_LINK $", "AOD$1", null },
    { "\\+FLAG_LD $", "AOl$1", null },
    { "\\+FLAG_DISP $", "AOd$1", null },
    { "\\+FLAG_TNC $", "AOn$1", null },
    { "\\+FLAG_PL_TDF $", "AOP$1", null },
    { "\\+FLAG_AS1 $", "AOA$1", null },
    { "\\+FLAG_TDFOPT $", "", null },
    { "\\+FLAG_SPEC_LINK $", "AOs$1", null },
    { "\\+FLAG_CPP_SPEC_LINK $", "AOS$1", null },
    { "\\+FLAG_DUMP_ANAL $", "AOe$1", null },
    { "\\+FLAG_DUMP_LINK $", "AOu$1", null },
    { "\\+FLAG_CC $", "AOC$1", null },
    { "\\+FLAG_INSTALL $", "AOI$1", null },

    /* Additional filename suffixes */
    { "\\+SUFFIX_CPP $", "SSC$1|1SO", null },

    /* Executables */
    { "?AS $", "$1Ea$2", null },
    { "?AS1 $", "$1EA$2", null },
    { "?BUILD_ARCH $", "$1BB$2", null },
    { "?CAT $", "$1BC$2", null },
    { "?CC $", "$1EC$2", null },
    { "?CPP_SPEC_LINK $", "$1ES$2", null },
    { "?DISP $", "$1Ed$2", null },
    { "?DUMP_ANAL $", "$1Ee$2", null },
    { "?DUMP_LINK $", "$1Eu$2", null },
    { "?DYN_LINK $", "$1ED$2", null },
    { "?LD $", "$1El$2", null },
    { "?MKDIR $", "$1BD$2", null },
    { "?MOVE $", "$1BM$2", null },
    { "?PL_TDF $", "$1EP$2", null },
    { "?REMOVE $", "$1BR$2", null },
    { "?SPEC_LINK $", "$1Es$2", null },
    { "?SPLIT_ARCH $", "$1BS$2", null },
    { "?TCPPLUS $", "$1Ex$2", null },
    { "?TCPPLUSPP $", "$1Eg$2", null },
    { "?TDFC $", "$1Ec$2", null },
    { "?TDFCPP $", "$1Ep$2", null },
    { "?TDFOPT $", "", null },
    { "?TLD $", "$1EL$2", null },
    { "?TNC $", "$1En$2", null },
    { "?TOUCH $", "$1BT$2", null },
    { "?TRANS $", "$1Et$2", null },

    /* Flags */
    { "?API $", "", null },
    { "?API_NAME $", "", null },
    { "?INCL $", "$1SI$2", null },
    { "?INCL_CPP $", "$1Si$2", null },
    { "?STARTUP_DIR $", "$1Sd$2", null },
    { "?STARTUP $", "$1Ss$2", null },
    { "?STARTUP_CPP_DIR $", "$1SD$2", null },
    { "?STARTUP_CPP $", "$1SS$2", null },
    { "?PORTABILITY $", "$1SP$2", null },
    { "?LINK $", "$1SJ$2", null },
    { "?LIB $", "$1Sj$2", null },
    { "?CRT0 $", "$1S0$2", null },
    { "?CRT1 $", "$1S1$2", null },
    { "?CRTN $", "$1S2$2", null },
    { "?CRTP_N $", "$1S3$2", null },
    { "?SYS_LINK $", "$1SL$2", null },
    { "?SYS_LIB $", "$1Sl$2", null },
    { "?SYS_LIBC $", "$1Sc$2", null },
    { "?LINK_ENTRY $", "$1Se$2", null },

    /* Startup and endup lines */
    { "\\+COMP_OPTION $", "@CAP:$1", null },
    { "\\+LINE_START $", "@D$1$n", null },
    { "\\+LINE_END $", "@F$1$n", null },

    /* Miscellaneous */
    { "\\+INFO $", "@SAI$1", null },
    { ">INFO $", "@SAI$SAI@plus@$1", null },
    { "<INFO $", "@SAI$1@plus@$SAI", null },
    { "\\+ENVDIR $", "SED$1|CFE", null },
    { "\\?ENVDIR $", "?:ED$1", null },
    { "\\+MACHINE $", "SMN$1|CSM", null },
    { "\\?MACHINE $", "?:MN$1", null },
    { "\\+SUFFIX $", "STD$1", null },	/* this MUST be wrong !!! */
    { "\\+TEMP $", "STD$1", null },
    { "\\?TEMP $", "?:TD$1", null },
    { "\\+VERSION $", "SVF$1", null },
    { "\\?VERSION $", "?:VF$1", null },

    /* Errors */
    { "\\+E$ $", "X+E$soptions$sno$slonger$ssupported", null },
    { "$ $", "XUnknown$senvironmental$svariable,$s$1", null },
    { "$", "XIllegal$senvironmental$soption,$s$0", null },

    /* End marker */
    { null, null, null }
} ;


/*
    OPTION INTERPRETER DEBUGGING FLAG

    This flag indicates whether option interpreter debugging information
    should be printed.
*/

static boolean debug_options = 0 ;


/*
    LOCAL FLAGS

    These values may be used for temporary storage by the option
    interpreter.
*/

static boolean xx_bool = 0 ;
static list *xx_list = null ;
static char *xx_string = null ;


/*
    ROUTINE IMPLEMENTING THE -SPECIAL OPTION

    This routine enables certain internal options depending on the
    value of the string held in xx_string.
*/

static void special_option
    PROTO_Z ()
{
    boolean b = 1 ;
    char *s = xx_string ;
    if ( strneq ( s, "no_", 3 ) ) {
	b = 0 ;
	s += 3 ;
    }
    if ( streq ( s, "cpp" ) ) {
	allow_cpp = b ;
    } else if ( streq ( s, "tnc" ) && !checker ) {
	allow_notation = b ;
    } else if ( streq ( s, "pl_tdf" ) && !checker ) {
	allow_pl_tdf = b ;
    } else if ( streq ( s, "c_spec" ) || streq ( s, "cpp_spec" ) ) {
	allow_specs = b ;
    } else if ( streq ( s, "dump" ) || streq ( s, "cpp_dump" ) ) {
	allow_specs = b ;
	if ( dump_opts == null ) dump_opts = "-d=" ;
    } else {
	error ( WARNING, "Unknown special option, '%s'", s ) ;
    }
    return ;
}


/*
    CONVERT A TWO LETTER CODE INTO A BOOLEAN

    This routine takes a two letter code, s, and returns a pointer to
    the corresponding boolean variable.
*/

static boolean *lookup_bool
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char a = s [0] ;
    char b = 0 ;
    if ( a ) b = s [1] ;
    switch ( a ) {
	case 'A' : {
  	    if ( b == 'A' ) return ( &use_alpha_assembler ) ;
	    if ( b == 'C' ) return ( &api_checks ) ;
	    if ( b == 'R' ) return ( &make_archive ) ;
	    if ( b == 'S' ) return ( &use_assembler ) ;
	    break ;
	}
	case 'C' : {
	    if ( b == 'C' ) return ( &use_system_cc ) ;
	    if ( b == 'H' ) return ( &checker ) ;
	    if ( b == 'R' ) return ( &copyright ) ;
	    if ( b == 'S' ) return ( &allow_specs ) ;
	    break ;
	}
	case 'D' : {
	    if ( b == 'B' ) return ( &debug_options ) ;
	    if ( b == 'G' ) return ( &flag_diag ) ;
	    if ( b == 'L' ) return ( &use_dynlink ) ;
	    if ( b == 'R' ) return ( &dry_run ) ;
	    break ;
	}
	case 'H' : {
	    if ( b == 'L' ) return ( &use_hp_linker ) ;
	    break ;
	}
	case 'K' : {
	    if ( b == 'E' ) return ( &flag_keep_err ) ;
	    break ;
	}
	case 'L' : {
	    if ( b == 'C' ) return ( &case_insensitive ) ;
	    if ( b == 'S' ) return ( &link_specs ) ;
	    break ;
	}
	case 'M' : {
	    if ( b == 'A' ) return ( &use_mips_assembler ) ;
	    if ( b == 'C' ) return ( &make_complex ) ;
	    if ( b == 'N' ) return ( &make_up_names ) ;
	    if ( b == 'P' ) return ( &flag_merge_all ) ;
	    break ;
	}
	case 'N' : {
	    if ( b == 'E' ) return ( &flag_nepc ) ;
	    break ;
	}
	case 'O' : {
	    if ( b == 'N' ) return ( &option_next ) ;
	    if ( b == 'P' ) return ( &flag_optim ) ;
	    break ;
	}
	case 'P' : {
	    if ( b == 'F' ) return ( &flag_prof ) ;
	    if ( b == 'I' ) return ( &flag_incl ) ;
	    if ( b == 'L' ) return ( &allow_pl_tdf ) ;
	    if ( b == 'P' ) return ( &make_pretty ) ;
	    if ( b == 'R' ) return ( &make_preproc ) ;
	    break ;
	}
	case 'S' : {
	    if ( b == 'A' ) return ( &show_api ) ;
	    if ( b == 'C' ) return ( &use_sparc_cc ) ;
	    if ( b == 'E' ) return ( &show_errors ) ;
	    if ( b == 'O' ) return ( &suffix_overrides ) ;
	    if ( b == 'R' ) return ( &flag_strip ) ;
	    if ( b == 'T' ) return ( &flag_startup ) ;
	    break ;
	}
	case 'T' : {
	    if ( b == 'C' ) return ( &taciturn ) ;
	    if ( b == 'I' ) return ( &time_commands ) ;
	    if ( b == 'N' ) return ( &allow_notation ) ;
	    if ( b == 'S' ) return ( &make_tspec ) ;
	    if ( b == 'U' ) return ( &tidy_up ) ;
	    break ;
	}
	case 'V' : {
	    if ( b == 'B' ) return ( &verbose ) ;
	    break ;
	}
	case 'W' : {
	    if ( b == 'A' ) return ( &warnings ) ;
	    break ;
	}
	case 'X' : {
	    if ( b == 'X' ) return ( &xx_bool ) ;
	    break ;
	}
    }
    error ( OPTION, "Unknown boolean identifier, '%c%c'", a, b ) ;
    return ( null ) ;
}


/*
    CONVERT A TWO LETTER CODE INTO A LIST

    This routine takes a two letter code, s, and returns a pointer to
    the corresponding list variable.  This routine needs to be kept in
    step with Table 4.
*/

static list **lookup_list
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char a = s [0] ;
    char b = 0 ;
    if ( a ) b = s [1] ;
    switch ( a ) {
	case 'B' : {
	    switch ( b ) {
		case 'B' : return ( &exec_build_arch ) ;
		case 'C' : return ( &exec_cat ) ;
		case 'D' : return ( &exec_mkdir ) ;
		case 'M' : return ( &exec_move ) ;
		case 'R' : return ( &exec_remove ) ;
		case 'S' : return ( &exec_split_arch ) ;
		case 'T' : return ( &exec_touch ) ;
	    }
	    break ;
	}
	case 'E' : {
	    switch ( b ) {
		case PRODUCE_ID : return ( &exec_produce ) ;
		case PREPROC_ID : return ( &exec_preproc ) ;
		case CPP_PRODUCE_ID : return ( &exec_cpp_produce ) ;
		case CPP_PREPROC_ID : return ( &exec_cpp_preproc ) ;
		case TDF_LINK_ID : return ( &exec_tdf_link ) ;
		case TRANSLATE_ID : return ( &exec_translate ) ;
		case ASSEMBLE_ID : return ( &exec_assemble ) ;
		case LINK_ID : return ( &exec_link ) ;
		case PRETTY_ID : return ( &exec_pretty ) ;
		case NOTATION_ID : return ( &exec_notation ) ;
		case PL_TDF_ID : return ( &exec_pl_tdf ) ;
		case ASSEMBLE_MIPS_ID : return ( &exec_assemble_mips ) ;
		case SPEC_LINK_ID : return ( &exec_spec_link ) ;
		case CPP_SPEC_LINK_ID : return ( &exec_cpp_spec_link ) ;
		case CC_ID : return ( &exec_cc ) ;
	        case DYNLINK_ID : return ( &exec_dynlink );
	        case DUMP_ANAL_ID : return ( &exec_dump_anal );
	        case DUMP_LINK_ID : return ( &exec_dump_link );
	    }
	    error ( OPTION, "Unknown compilation stage, '%c'", b ) ;
	    return ( null ) ;
	}
	case 'Q' : {
	    if ( checker ) {
		switch ( b ) {
		    case PRODUCE_ID : return ( &opt_produce ) ;
		    case CPP_PRODUCE_ID : return ( &opt_cpp_produce ) ;
		    case SPEC_LINK_ID : return ( &opt_spec_link ) ;
		    case CPP_SPEC_LINK_ID : return ( &opt_cpp_spec_link ) ;
		    case ARCHIVER_ID : return ( &opt_joiner ) ;
		    case CC_ID : return ( &opt_cc ) ;
		}
		error ( OPTION, "Unknown compilation stage, '%c'", b ) ;
		return ( null ) ;
	    }
	    goto case_O ;
	}
	case 'O' :
	case_O :{
	    switch ( b ) {
		case PRODUCE_ID : return ( &opt_produce ) ;
		case PREPROC_ID : return ( &opt_preproc ) ;
		case CPP_PRODUCE_ID : return ( &opt_cpp_produce ) ;
		case CPP_PREPROC_ID : return ( &opt_cpp_preproc ) ;
		case TDF_LINK_ID : return ( &opt_tdf_link ) ;
		case TRANSLATE_ID : return ( &opt_translate ) ;
		case ASSEMBLE_ID : return ( &opt_assemble ) ;
		case DYNLINK_ID : return ( &opt_dynlink ) ;
		case LINK_ID : return ( &opt_link ) ;
		case PRETTY_ID : return ( &opt_pretty ) ;
		case NOTATION_ID : return ( &opt_notation ) ;
		case PL_TDF_ID : return ( &opt_pl_tdf ) ;
		case ASSEMBLE_MIPS_ID : return ( &opt_assemble_mips ) ;
		case SPEC_LINK_ID : return ( &opt_spec_link ) ;
		case CPP_SPEC_LINK_ID : return ( &opt_cpp_spec_link ) ;
		case INSTALL_ID : return ( &opt_archive ) ;
		case ARCHIVER_ID : return ( &opt_joiner ) ;
		case CC_ID : return ( &opt_cc ) ;
	        case DUMP_ANAL_ID : return ( &opt_dump_anal );
	        case DUMP_LINK_ID : return ( &opt_dump_link );
	    }
	    error ( OPTION, "Unknown compilation stage, '%c'", b ) ;
	    return ( null ) ;
	}
	case 'S' : {
	    switch ( b ) {
		case 'I' : return ( &std_prod_incldirs ) ;
		case 'P' : return ( &std_prod_portfile ) ;
		case 'd' : return ( &std_prod_startdirs ) ;
		case 's' : return ( &std_prod_startup ) ;
		case 'i' : return ( &std_cpp_prod_incldirs ) ;
		case 'D' : return ( &std_cpp_prod_startdirs ) ;
		case 'S' : return ( &std_cpp_prod_startup ) ;
		case 'J' : return ( &std_tdf_link_libdirs ) ;
		case 'j' : return ( &std_tdf_link_libs ) ;
		case '0' : return ( &std_link_crt0 ) ;
		case '1' : return ( &std_link_crt1 ) ;
		case '2' : return ( &std_link_crtn ) ;
		case '3' : return ( &std_link_crtp_n ) ;
		case 'L' : return ( &std_link_libdirs ) ;
		case 'l' : return ( &std_link_libs ) ;
		case 'c' : return ( &std_link_c_libs ) ;
		case 'e' : return ( &std_link_entry ) ;
	    }
	    break ;
	}
	case 'U' : {
	    switch ( b ) {
		case 'I' : return ( &usr_prod_incldirs ) ;
		case 's' : return ( &usr_prod_startup ) ;
		case 'e' : return ( &usr_prod_eoptions ) ;
		case 'f' : return ( &usr_prod_foptions ) ;
		case 'P' : return ( &usr_pl_tdf_incldirs ) ;
		case 'J' : return ( &usr_tdf_link_libdirs ) ;
		case 'j' : return ( &usr_tdf_link_libs ) ;
		case 'L' : return ( &usr_link_libdirs ) ;
		case 'l' : return ( &usr_link_libs ) ;
	    }
	    break ;
	}
	case 'X' : {
	    switch ( b ) {
		case 'O' : return ( &opt_unknown ) ;
		case 'X' : return ( &xx_list ) ;
	    }
	    break ;
	}
    }
    error ( OPTION, "Unknown list identifier, '%c%c'", a, b ) ;
    return ( null ) ;
}


/*
    CONVERT A TWO LETTER CODE INTO A STRING

    This routine takes a two letter code, s, and returns a pointer to
    the corresponding string variable.
*/

static char **lookup_string
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char a = s [0] ;
    char b = 0 ;
    if ( a ) b = s [1] ;
    if ( a == 'N' ) {
	switch ( b ) {
	    case INDEP_TDF_KEY : return ( &name_j_file ) ;
	    case C_SPEC_KEY : return ( &name_k_file ) ;
	    case CPP_SPEC_KEY : return ( &name_K_file ) ;
	    case STARTUP_FILE_KEY : return ( &name_h_file ) ;
	    case PRETTY_TDF_KEY : return ( &name_p_file ) ;
	}
	error ( OPTION, "Unknown output file specifier, '%c'", b ) ;
	return ( null ) ;
    }
    if ( a == 'S' ) {
	int t = find_type ( b, 0 ) ;
	return ( suffixes + t ) ;
    }
    if ( a == 'A' && b == 'I' ) return ( &api_info ) ;
    if ( a == 'A' && b == 'O' ) return ( &api_output ) ;
    if ( a == 'D' && b == 'O' ) return ( &dump_opts ) ;
    if ( a == 'E' && b == 'D' ) return ( &environ_dir ) ;
    if ( a == 'F' && b == 'N' ) return ( &final_name ) ;
    if ( a == 'M' && b == 'N' ) return ( &machine_name ) ;
    if ( a == 'P' && b == 'N' ) return ( &progname ) ;
    if ( a == 'T' && b == 'D' ) return ( &temporary_dir ) ;
    if ( a == 'V' && b == 'F' ) return ( &version_flag ) ;
    if ( a == 'W' && b == 'D' ) return ( &workdir ) ;
    if ( a == 'X' && b == 'X' ) return ( &xx_string ) ;
    error ( OPTION, "Unknown string identifier, '%c%c'", a, b ) ;
    return ( null ) ;
}


/*
    DUMMY ARGUMENT FOR PROCEDURE

    This variable is used to hold any argument passed to one of the procedures
    in lookup_proc.
*/

static char *lookup_proc_arg = null ;


/*
    DUMMY WRAPPER PROCEDURES

    These routine(s) are used to call procedures with an argument using
    lookup_proc.
*/

static void add_pragma_aux
    PROTO_Z ()
{
    add_pragma ( lookup_proc_arg ) ;
    return ;
}

static void add_token_aux
    PROTO_Z ()
{
    add_token ( lookup_proc_arg ) ;
    return ;
}


/*
    CONVERT A TWO LETTER CODE INTO A PROCEDURE

    This routine takes a two letter code, s, and returns a pointer to
    the corresponding procedure.
*/

typedef void ( *proc ) PROTO_Z () ;

static proc lookup_proc
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char a = s [0] ;
    char b = 0 ;
    if ( a ) b = s [1] ;
    if ( a == 'A' && b == 'P' ) return ( add_pragma_aux ) ;
    if ( a == 'A' && b == 'T' ) return ( add_token_aux ) ;
    if ( a == 'F' && b == 'E' ) return ( find_envpath ) ;
    if ( a == 'P' && b == 'V' ) return ( print_version ) ;
    if ( a == 'S' && b == 'E' ) return ( show_envpath ) ;
    if ( a == 'S' && b == 'M' ) return ( set_machine ) ;
    if ( a == 'S' && b == 'P' ) return ( special_option ) ;
    error ( OPTION, "Unknown procedure identifier, '%c%c'", a, b ) ;
    return ( null ) ;
}


/*
    RETURN VALUES FOR MATCH_OPTION

    These values are returned by match_option.  MATCH_OK means that the
    option matches, MATCH_MORE means that it may match with an additional
    option, MATCH_FAILED means it does not match, and the other values
    indicate errors of some kind.
*/

#define MATCH_OK		0
#define MATCH_MORE		1
#define MATCH_FAILED		2
#define MATCH_IN_ERR		3
#define MATCH_OUT_ERR		4
#define MATCH_OPT_ERR		5


/*
    MATCH AN OPTION
*/

static int match_option
    PROTO_N ( ( in, out, opt, res ) )
    PROTO_T ( char *in X char *out X char *opt X args_out *res )
{
    char *p = in ;
    char *q = opt ;

    int i, a, v = 1 ;
    int go = 1, loop = 1, loopv = -1 ;
    struct { char *txt ; int len ; } var [ max_var ] ;

    /* Process input */
    while ( *p && go ) {
	if ( *p == '$' ) {
	    char c = p [1] ;
	    if ( c ) {
		int wraps = 0 ;
		if ( p [2] == '+' && p [3] == '*' ) {
		    /* List of strings with breaks : $c+* */
		    wraps = 1 ;
		    p++ ;
		}
		if ( p [2] == '*' ) {
		    /* List of strings : $c* */
		    loop = 0 ;
		    loopv = v ;
		    if ( p [3] ) return ( MATCH_IN_ERR ) ;
		    while ( *q ) {
			int l = 0 ;
			var [v].txt = q ;
			while ( *q && *q != c ) {
			    l++ ;
			    q++ ;
			}
			var [v].len = l ;
			if ( *q ) {
			    /* Found c */
			    q++ ;
			    if ( *q == 0 && wraps ) return ( MATCH_MORE ) ;
			}
			if ( ++v >= max_var ) return ( MATCH_OPT_ERR ) ;
			loop++ ;
		    }
		    go = 0 ;
		} else {
		    /* Terminated string : $c */
		    int l = 0 ;
		    var [v].txt = q ;
		    while ( *q != c ) {
			if ( *q == 0 ) return ( MATCH_FAILED ) ;
			l++ ;
			q++ ;
		    }
		    var [v].len = l ;
		    if ( ++v >= max_var ) return ( MATCH_OPT_ERR ) ;
		}
	    } else {
		/* Simple string : $ */
		int l = ( int ) strlen ( q ) ;
		var [v].txt = q ;
		var [v].len = l ;
		if ( ++v >= max_var ) return ( MATCH_OPT_ERR ) ;
		go = 0 ;
	    }
	} else if ( *p == '?' ) {
	    if ( p [1] == '*' ) {
		/* List of characters : ?* */
		if ( p [2] ) return ( MATCH_IN_ERR ) ;
		loop = 0 ;
		loopv = v ;
		while ( *q ) {
		    var [v].txt = q ;
		    var [v].len = 1 ;
		    if ( ++v >= max_var ) return ( MATCH_OPT_ERR ) ;
		    q++ ;
		    loop++ ;
		}
		go = 0 ;
	    } else {
		/* Simple character : ? */
		if ( *q == 0 ) return ( MATCH_FAILED ) ;
		var [v].txt = q ;
		var [v].len = 1 ;
		if ( ++v >= max_var ) return ( MATCH_OPT_ERR ) ;
		q++ ;
	    }
	} else if ( *p == '+' ) {
	    /* Potential break : + */
	    if ( *q == 0 ) return ( MATCH_MORE ) ;
	} else if ( *p == '^' ) {
	    /* Negated letter */
	    p++ ;
	    if ( *p == 0 ) return ( MATCH_IN_ERR ) ;
	    if ( *p == *q ) return ( MATCH_FAILED ) ;
	    q++ ;
	} else if ( *p == '\\' ) {
	    /* Escaped letter : \c */
	    p++ ;
	    if ( *p == 0 ) return ( MATCH_IN_ERR ) ;
	    if ( *p != *q ) return ( MATCH_FAILED ) ;
	    q++ ;
	} else {
	    /* Letter : c */
	    if ( *p != *q ) return ( MATCH_FAILED ) ;
	    q++ ;
	}
	p++ ;
    }

    /* Check end of option */
    if ( go && *q ) return ( MATCH_FAILED ) ;

    /* The first variable is the whole option */
    var [0].txt = opt ;
    var [0].len = ( int ) strlen ( opt ) ;

    /* Print output */
    a = 0 ;
    for ( i = 0 ; i < loop ; i++ ) {
	char buff [1000] ;
	q = buff ;
	for ( p = out ; *p ; p++ ) {
	    if ( *p == '$' ) {
		/* Variable */
		int n ;
		char c = *( ++p ) ;
		if ( c == 's' ) {
		    /* $s expands to a space */
		    *( q++ ) = ' ' ;
		} else if ( c == 'n' ) {
		    /* $n expands to a newline */
		    *( q++ ) = '\n' ;
		} else if ( c >= '0' && c <= '9' ) {
		    n = ( c - '0' ) ;
		    if ( n == loopv ) n += i ;
		    if ( n < v ) {
			int l = var [n].len ;
			IGNORE strncpy ( q, var [n].txt, ( size_t ) l ) ;
			q += l ;
		    }
		} else if ( c == 'B' ) {
		    boolean *b = lookup_bool ( p + 1 ) ;
		    if ( b == null ) return ( MATCH_OUT_ERR ) ;
		    IGNORE sprintf ( q, "%d", ( int ) *b ) ;
		    while ( *q ) q++ ;
		    p += 2 ;
		} else if ( c == 'L' ) {
		    list *pt ;
		    list **sp = lookup_list ( p + 1 ) ;
		    if ( sp == null ) return ( MATCH_OUT_ERR ) ;
		    for ( pt = *sp ; pt ; pt = pt->next ) {
			int l = ( int ) strlen ( pt->item ) ;
			IGNORE strncpy ( q, pt->item, ( size_t ) l ) ;
			q += l ;
			*( q++ ) = ' ' ;
		    }
		    p += 2 ;
		} else if ( c == 'S' ) {
		    int l ;
		    char **sp = lookup_string ( p + 1 ) ;
		    if ( sp == null ) return ( MATCH_OUT_ERR ) ;
		    if ( *sp ) {
			l = ( int ) strlen ( *sp ) ;
			IGNORE strncpy ( q, *sp, ( size_t ) l ) ;
			q += l ;
		    }
		    p += 2 ;
		} else {
		    return ( MATCH_OUT_ERR ) ;
		}
	    } else if ( *p == '|' ) {
		/* Multiple output */
		*q = 0 ;
		res->argv [a] = string_copy ( buff ) ;
		if ( ++a >= max_var ) return ( MATCH_OPT_ERR ) ;
		q = buff ;
	    } else if ( *p == '\\' ) {
		/* Escaped output character */
		if ( *( ++p ) == 0 ) return ( MATCH_OUT_ERR ) ;
		*( q++ ) = *p ;
	    } else {
		/* Simple output character */
		*( q++ ) = *p ;
	    }
	}
	*q = 0 ;
	res->argv [a] = string_copy ( buff ) ;
	if ( ++a >= max_var ) return ( MATCH_OPT_ERR ) ;
    }
    res->argc = a ;
    return ( MATCH_OK ) ;
}


/*
    INTERPRET AN OPTION COMMAND
*/

static void interpret_cmd
    PROTO_N ( ( cmd ) )
    PROTO_T ( char *cmd )
{
    char c = *cmd ;

    /* Debugging */
    if ( debug_options ) error ( OPTION, "Interpreting '%s'", cmd ) ;

    /* Deal with at-hack */
    if ( c == '@' ) {
	char *p = string_copy ( cmd + 1 ), *q ;
	for ( q = p ; *q ; q++ ) {
	    if ( *q == '@' ) *q = ' ' ;
	}
	cmd = p ;
	c = *p ;
    }

    /* Deal with empty strings */
    if ( c == 0 ) return ;

    /* Digits set values */
    if ( c >= '0' && c <= '9' ) {
	boolean *b = lookup_bool ( cmd + 1 ) ;
	if ( b == null ) return ;
	*b = ( boolean ) ( c - '0' ) ;
	return ;
    }

    /* Translations */
    if ( c == '>' ) c = 'A' ;
    if ( c == '<' ) c = 'B' ;
    if ( c == '+' ) c = 'L' ;

    /* Deal with list query */
    if ( c == '?' ) {
	if ( cmd [1] == ':' ) {
	    char **sp = lookup_string ( cmd + 2 ) ;
	    if ( sp == null ) return ;
	    comment ( 1, "%s=\"%s\"\n", cmd + 4, *sp ) ;
	} else {
	    list *p ;
	    list **sp = lookup_list ( cmd + 1 ) ;
	    if ( sp == null ) return ;
	    comment ( 1, "%s=\"", cmd + 3 ) ;
	    for ( p = *sp ; p != null ; p = p->next ) {
		comment ( 1, "%s", p->item ) ;
		if ( p->next ) comment ( 1, " " ) ;
	    }
	    comment ( 1, "\"\n" ) ;
	}
	return ;
    }

    /* Deal with equivalences */
    if ( c == '=' ) {
	list *p = make_list ( cmd + 1 ) ;
	process_options ( p, main_optmap ) ;
	free_list ( p ) ;
	return ;
    }

    /* Deal with primitives */
    switch ( c ) {

	case 'A' : {
	    /* Change list */
	    list **sp = lookup_list ( cmd + 1 ) ;
	    if ( sp == null ) return ;
	    *sp = add_list ( *sp, make_list ( cmd + 3 ) ) ;
	    return ;
	}

	case 'B' : {
	    /* Change list */
	    list **sp = lookup_list ( cmd + 1 ) ;
	    if ( sp == null ) return ;
	    *sp = add_list ( make_list ( cmd + 3 ), *sp ) ;
	    return ;
	}

	case 'L' : {
	    /* Change list */
	    list **sp = lookup_list ( cmd + 1 ) ;
	    if ( sp == null ) return ;
	    free_list ( *sp ) ;
	    *sp = make_list ( cmd + 3 ) ;
	    return ;
	}

	case 'C' : {
	    /* Call */
	    proc p = lookup_proc ( cmd + 1 ) ;
	    if ( p == null ) return ;
	    if ( cmd [3] == ':' ) {
		lookup_proc_arg = cmd + 4 ;
	    } else {
		lookup_proc_arg = null ;
	    }
	    ( *p ) () ;
	    return ;
	}

	case 'D' : {
	    /* Startup options */
	    add_to_startup ( cmd + 1 ) ;
	    return ;
	}

	case 'E' : {
	    /* Environment */
	    read_env ( cmd + 1 ) ;
	    return ;
	}

	case 'F' : {
	    /* Endup options */
	    add_to_endup ( cmd + 1 ) ;
	    return ;
	}

	case 'H' : {
	    /* Halt */
	    char stage = cmd [1] ;
	    set_stage ( find_type ( stage, 0 ), STOP_STAGE ) ;
	    return ;
	}

	case 'I' : {
	    /* Input file */
	    int t ;
	    filename *f ;
	    char stage = cmd [1] ;
	    char *name = cmd + 2 ;
	    if ( stage == '?' ) {
		t = UNKNOWN_TYPE ;
	    } else {
		t = find_type ( stage, 0 ) ;
	    }
	    f = find_filename ( name, t ) ;
	    input_files = add_filename ( input_files, f ) ;
	    return ;
	}

	case 'K' : {
	    /* Keep */
	    static int k = KEEP_STAGE ;
	    char stage = cmd [1] ;
	    if ( stage == '-' ) {
		k = DONT_KEEP_STAGE ;
	    } else {
		set_stage ( find_type ( stage, 0 ), k ) ;
		k = KEEP_STAGE ;
	    }
	    return ;
	}

	case 'Q' : {
	    /* Query */
	    char *s ;
	    optmap *t = main_optmap ;
	    error ( INFO, "List of recognised options" ) ;
	    while ( s = t->in, s != null ) {
		if ( *s == '-' ) {
		    char d ;
		    comment ( 0, " " ) ;
		    while ( d = *( s++ ), d != 0 ) {
			switch ( d ) {
			    case '$' : {
				IGNORE fputs ( "<string>", stderr ) ;
				break ;
			    }
			    case '?' : {
				IGNORE fputs ( "<letter>", stderr ) ;
				break ;
			    }
			    case '*' : {
				IGNORE fputs ( "...", stderr ) ;
				break ;
			    }
			    case '+' : {
				IGNORE fputc ( ' ', stderr ) ;
				break ;
			    }
			    case '\\' : {
				IGNORE fputc ( *( s++ ), stderr ) ;
				break ;
			    }
			    default : {
				IGNORE fputc ( d, stderr ) ;
				break ;
			    }
			}
		    }
		    s = t->explain ;
		    if ( s == null ) s = "not documented" ;
		    comment ( 0, " : " ) ;
		    comment ( 0, s, progname ) ;
		    comment ( 0, ".\n" ) ;
		}
		t++ ;
	    }
	    return ;
	}

	case 'S' : {
	    /* String */
	    char **s = lookup_string ( cmd + 1 ) ;
	    if ( s == null ) return ;
	    *s = cmd + 3 ;
	    return ;
	}

	case 'V' : {
	    if ( cmd [1] == 'B' ) {
		boolean *b = lookup_bool ( cmd + 2 ) ;
		if ( b == null ) return ;
		comment ( 1, "%c%c = %d\n", cmd [2], cmd [3], *b ) ;
		return ;
	    } else if ( cmd [1] == 'L' ) {
		list **sp = lookup_list ( cmd + 2 ), *pt ;
		if ( sp == null ) return ;
		comment ( 1, "%c%c =", cmd [2], cmd [3] ) ;
		for ( pt = *sp ; pt != null ; pt = pt->next ) {
		    if ( pt->item ) {
			comment ( 1, " %s", pt->item ) ;
		    } else {
			comment ( 1, " (null)" ) ;
		    }
		}
		comment ( 1, "\n" ) ;
		return ;
	    } else if ( cmd [1] == 'S' ) {
		char **s = lookup_string ( cmd + 2 ) ;
		if ( s == null ) return ;
		if ( *s ) {
		    comment ( 1, "%c%c = %s\n", cmd [2], cmd [3], *s ) ;
		} else {
		    comment ( 1, "%c%c = (null)\n", cmd [2], cmd [3] ) ;
		}
		return ;
	    }
	    break ;
	}

	case 'X' : {
	    /* Error */
	    error ( WARNING, "%s", cmd + 1 ) ;
	    return ;
	}
    }
    error ( OPTION, "Syntax error, '%s'", cmd ) ;
    return ;
}


/*
    PROCESS A LIST OF OPTIONS

    This routine processes a list of options, opt, using the options
    from table tab.
*/

void process_options
    PROTO_N ( ( opt, tab ) )
    PROTO_T ( list *opt X optmap *tab )
{
    optmap *t ;
    list *p = opt ;
    char *arg = null ;
    int status = MATCH_OK ;

    /* Scan through the options */
    while ( p != null ) {
	if ( status == MATCH_MORE ) {
	    arg = string_concat ( arg, p->item ) ;
	} else {
	    arg = p->item ;
	}
	status = MATCH_FAILED ;
	for ( t = tab ; t->in != null ; t++ ) {
	    args_out res ;
	    status = match_option ( t->in, t->out, arg, &res ) ;
	    switch ( status ) {
		case MATCH_OK : {
		    /* Complete option - interpret result */
		    int a ;
		    for ( a = 0 ; a < res.argc ; a++ ) {
			interpret_cmd ( res.argv [a] ) ;
		    }
		    goto end_search ;
		}
		case MATCH_MORE : {
		    /* Incomplete option - move on to next option */
		    goto end_search ;
		}
		case MATCH_FAILED : {
		    /* Try again */
		    break ;
		}
		case MATCH_IN_ERR : {
		    /* Error in optmap input */
		    error ( OPTION, "Illegal input '%s'", t->in ) ;
		    status = MATCH_FAILED ;
		    break ;
		}
		case MATCH_OUT_ERR : {
		    /* Error in optmap output */
		    error ( OPTION, "Illegal option '%s'", t->out ) ;
		    status = MATCH_FAILED ;
		    break ;
		}
		case MATCH_OPT_ERR : {
		    /* Ran out of space for result */
		    error ( OPTION, "Too many components, '%s'", arg ) ;
		    status = MATCH_FAILED ;
		    break ;
		}
	    }
	}
	error ( OPTION, "Can't interpret '%s'", arg ) ;
	end_search : p = p->next ;
    }

    /* Check for incomplete options */
    if ( status == MATCH_MORE ) {
	error ( WARNING, "Option '%s' is incomplete", arg ) ;
    }

    return ;
}
