/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"

#include <utility/system.h>
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/debug.h>
#include <utility/option.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/predict.h>
#include <parse/preproc.h>
#include <parse/table.h>

#include <construct/basetype.h>
#include <construct/declare.h>
#include <construct/exception.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/inttype.h>
#include <construct/namespace.h>
#include <construct/operator.h>
#include <construct/overload.h>
#include <construct/printf.h>
#include <construct/redeclare.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/typeid.h>
#include <construct/variable.h>

#include <output/capsule.h>
#include <output/compile.h>
#include <output/dump.h>
#include <output/tok.h>
#include <output/unmangle.h>

#include <spec/load.h>


/**
 * DEFAULT MACHINE OPTION
 *
 * This macro is used to determine the machine dependent options to be used.
 */

#ifndef FS_MACHINE
#ifdef FS_DOS
#define FS_MACHINE		"dos"
#else
#define FS_MACHINE		"unix"
#endif
#endif


/*
 * COMMAND-LINE FLAGS
 *
 * These flags may be set by command-line options to indicate various actions
 * to the compiler.
 */

static int builtin_asserts = 1;
static int builtin_macros = 1;
static int check_level = 0;
static int complete_program = 0;
static int have_startup = 0;
static int spec_linker = 0;
static int started_scope = 0;
static int output_last = 1;
static int unmangle_names = 0;
static int quit_immediately = 0;
static string dump_name = NULL;
static string dump_opt = NULL;
static string spec_name = NULL;
static string table_name = NULL;


/*
 * TABLE OF COMMAND-LINE ARGUMENTS
 *
 * This table describes all the command-line options. Each is given by an
 * option letter, followed by a flag indicating whether the option can be
 * split into two components, and a description of the second option
 * component.
 */

typedef struct {
    char opt;
    char space;
    const char *arg;
    const char *desc;
} PROGRAM_ARG;

static PROGRAM_ARG prog_args[] = {
    { 'A', 1, "<pre>(<tok>)", "assert a predicate"                },
    { 'C', 1, "<file>",       "load a character set map"          },
    { 'D', 1, "<mac>=<def>",  "define a macro"                    },
    { 'E', 0, NULL,           "preprocess input file only"        },
    { 'F', 1, "<file>",       "read list of options from file"    },
    { 'H', 0, NULL,           "report file inclusions"            },
    { 'I', 1, "<dir>",        "specify an include directory"      },
    { 'M', 1, "<mach>",       "machine dependent options"         },
    { 'N', 1, "<name>:<dir>", "specify a named include directory" },
    { 'O', 0, NULL,           "optimise output capsule"           },
    { 'R', 0, NULL,           "reverse order of files"            },
    { 'S', 0, NULL,           "spec file linker action"           },
    { 'U', 1, "<mac>",        "undefine a macro"                  },
    { 'V', 0, NULL,           "enable verbose mode"               },
    { 'W', 1, "<opt>",        "enable warnings option"            },
    { 'X', 0, NULL,           "disable exception handling"        },
    { 'Z', 1, "<number>",     "set maximum number of errors"      },
    { 'a', 0, NULL,           "apply complete program checks"     },
    { 'c', 0, NULL,           "disable TDF output"                },
    { 'd', 1, "<opt>=<file>", "dump symbol table"                 },
    { 'e', 1, "<file>",       "add an end-up file"                },
    { 'f', 1, "<file>",       "add a start-up file"               },
    { 'g', 0, "<level>",      "enable diagnostics mode"           },
    { 'h', 0, NULL,           "print this help page"              },
    { 'i', 1, "<name>",       "specify machine for diagnostics"   },
    { 'j', 1, "<opts>",       "set TDF output options"            },
    { 'm', 1, "<opts>",       "set error printing options"        },
    { 'n', 1, "<file>",       "specify portability table"         },
    { 'o', 1, "<output>",     "specify output file"               },
    { 'q', 0, NULL,           "quit immediately"                  },
    { 'r', 1, "<file>",       "specify error marker"              },
    { 's', 1, "<file>",       "specify spec output file"          },
    { 't', 0, NULL,           "output TDF token declarations"     },
    { 'u', 0, NULL,           "unmangle identifier names"         },
    { 'v', 0, NULL,           "print version number"              },
    { 'w', 0, NULL,           "disable all warnings"              },
#ifndef NDE
    { 'x', 1, "<debug>",      "debugging options"                 },
#endif
    { 'z', 0, NULL,           "ignore compilation errors"         },
    { '?', 0, NULL,           "print this help page"              },
    { '-', 0, NULL,           "specify end of options"            }
};

#define no_prog_args	array_size(prog_args)


/**
 * PRINT PROGRAM USAGE
 *
 * This routine prints the program usage to the file f.
 */

static void
report_usage(FILE *f)
{
    int i;
    fprintf_v(f, "Usage: %s [options] [input] [output]\n", progname);
    for (i = 0; i < no_prog_args; i++) {
	char opt = prog_args[i].opt;
	const char *arg = prog_args[i].arg;
	const char *desc = prog_args[i].desc;
	if (arg == NULL) arg = "\t";
	if (desc == NULL) desc = "(not documented)";
	fprintf_v(f, " -%c%s\t%s\n", opt, arg, desc);
    }
    fputc_v('\n', f);
    return;
}


/**
 * SET MACHINE DEPENDENT FLAGS
 *
 * This routine sets the machine dependent options for the machine described
 * by mach. The routine returns false for an unknown machine descriptor.
 */

static int
set_machine(const char *mach)
{
    if (streq(mach, "dos")) {
	allow_dos_newline = 1;
	good_fseek = 0;
	binary_mode = 1;
	file_sep = '\\';
	drive_sep = ':';
	return 1;
    }
    if (streq(mach, "unix")) {
	allow_dos_newline = 0;
	good_fseek = 1;
	binary_mode = 0;
	file_sep = '/';
	drive_sep = 0;
	return 1;
    }
    return 0;
}


/**
 * PRE-SET A COMPILE-TIME OPTION
 *
 * This routine pre-sets the value of option A to be B.
 */

#define preset(A, B)\
    OPT_CATALOG[A].def[0] = (B);\
    OPT_CATALOG[A].def[1] = (B)


/**
 * READ AN ARGUMENT FROM A FILE
 *
 * This routine reads a command-line argument from the file f into the buffer
 * s of length n, returning the result.
 */

static char *
read_arg(FILE *f, char *s, int n)
{
    char *p = fgets(s, n, f);
    if (p) {
	char c = *p;
	if (c == '#' || c == '\n') {
	    /* Ignore empty lines and comments */
	    p = read_arg(f, s, n);
	} else {
	    /* Remove terminal newline */
	    char *q = strrchr(p, '\n');
	    if (q) *q = 0;
	}
    }
    return p;
}


/**
 * PROCESS A LIST OF ARGUMENTS
 *
 * This routine is called by main to process the command-line arguments given
 * by argc and argv. It returns a list of strings giving the input and output
 * files.
 */

static LIST(string)
process_args(int argc, char **argv)
{
    char opt = 0;
    FILE *f = NULL;
    char buff[1000];
    int allow_opt = 1;
    string output = NULL;
    LIST(string)files = NULL_list(string);

    /* Set development default options */
#ifndef NDEBUG
    output_tokdec = 1;
#endif

    /* Scan through the arguments */
    for (; ;) {
	char *arg = NULL;
	if (f != NULL) {
	    /* Get next option from file */
	    arg = read_arg(f, buff,(int)sizeof(buff));
	    if (arg == NULL) {
		/* End of file reached */
		fclose_v(f);
		f = NULL;
	    }
	}
	if (arg == NULL && argc) {
	    /* Get next option from array */
	    arg = *(argv++);
	    argc--;
	}
	if (arg == NULL) {
	    /* No more options */
	    break;
	}
	if (opt == 0) {
	    /* Find option letter */
	    if (arg[0] == '-' && allow_opt) {
		opt = arg[1];
		if (opt) arg += 2;
	    }
	}
	if (opt == 0) {
	    /* Input or output file 'arg' */
	    string uarg = xustrcpy(ustrlit(arg));
	    CONS_string(uarg, files, files);

	} else {
	    /* Command-line options */
	    int i;
	    int known = 0;
	    char next_opt = 0;

	    /* Search through options */
	    for (i = 0; i < no_prog_args; i++) {
		if (opt == prog_args[i].opt) {
		    if (prog_args[i].arg) {
			/* Complex options */
			if (arg[0] == 0 && prog_args[i].space) {
			    next_opt = opt;
			    known = 1;
			} else {
			    known = 2;
			}
		    } else {
			/* Simple options */
			if (arg[0] == 0) {
			    known = 2;
			    break;
			}
		    }
		}
	    }

	    /* Deal with complete options */
	    if (known == 2) {
		string uarg = ustrlit(arg);
		switch (opt) {

		    case 'A': {
			/* Assertion */
			BUFFER *bf = &internal_buff;
			if (streq(arg, "-")) {
			    builtin_asserts = 0;
			    break;
			}
			bfprintf(bf, "#assert %x\n", arg);
			preset(OPT_ppdir_assert, OPTION_ALLOW);
			preset(OPT_ppdir_unassert, OPTION_ALLOW);
			preset(OPT_ppdir_assert_ignore, OPTION_OFF);
			preset(OPT_ppdir_unassert_ignore, OPTION_OFF);
			have_startup = 1;
			break;
		    }

		    case 'C':
			if (-1 == init_literal_map(arg)) {
			    const char *err = "Can't open charset map file '%s'";
			    error(ERR_FATAL, err, arg);
			}
			break;

		    case 'D': {
			/* Macro definition */
			char c;
			const char *def = "1";
			BUFFER *bf = &internal_buff;
			bfprintf(bf, "#define ");
			while (c = *(arg++), c != 0) {
			    if (c == '=') {
				def = arg;
				break;
			    }
			    bfputc(bf,(int)c);
			}
			bfprintf(bf, " %x\n", def);
			have_startup = 1;
			break;
		    }

		    case 'E': {
			/* Preprocessor option */
			preproc_only = 1;
			break;
		    }

		    case 'F': {
			/* Open option file */
			if (f != NULL) {
			    const char *err = "Nested option files";
			    error(ERR_WARN, err);
			    break;
			}
			f = fopen(arg, "r");
			if (f == NULL) {
			    const char *err = "Can't open option file '%s'";
			    error(ERR_WARN, err, arg);
			}
			break;
		    }

		    case 'H': {
			/* Inclusion reporting option */
			preset(OPT_include_verbose, OPTION_WARN);
			break;
		    }

		    case 'I': {
			/* Include file search directory */
			uarg = xustrcpy(uarg);
			add_directory(uarg, NULL_string);
			break;
		    }

		    case 'M': {
			/* Machine dependent options */
			known = set_machine(arg);
			break;
		    }

		    case 'N': {
			/* Named include file search directory */
			string dir;
			uarg = xustrcpy(uarg);
			dir = ustrchr(uarg, ':');
			if (dir == NULL) {
			    const char *err = "Bad '-%c' option";
			    error(ERR_WARN, err, opt);
			    add_directory(uarg, NULL_string);
			} else {
			    *dir = 0;
			    add_directory(dir + 1, uarg);
			}
			break;
		    }

		    case 'O': {
			/* Optimisation mode */
			output_inline = 1;
			output_unused = 0;
			break;
		    }

		    case 'R': {
			/* Reverse order of files */
			output_last = 0;
			break;
		    }

		    case 'S': {
			/* Spec linker option */
			spec_linker = 1;
			break;
		    }

		    case 'U': {
			/* Macro undefinition */
			BUFFER *bf = &internal_buff;
			if (streq(arg, "-")) {
			    builtin_macros = 0;
			    break;
			}
			bfprintf(bf, "#undef %x\n", arg);
			have_startup = 1;
			break;
		    }

		    case 'V': {
			/* Switch on verbose mode */
			verbose = 1;
			break;
		    }

		    case 'W': {
			/* Switch on checks */
			char c;
			const char *sev = "warning";
			BUFFER *bf = &internal_buff;
			if (streq(arg, "all")) {
			    check_level = 1;
			    break;
			}
			if (!started_scope) {
			    bfprintf(bf, "#pragma TenDRA begin\n");
			    started_scope = 1;
			}
			bfprintf(bf, "#pragma TenDRA option \"");
			while (c = *(arg++), c != 0) {
			    if (c == '=') {
				sev = arg;
				break;
			    }
			    bfputc(bf,(int)c);
			}
			bfprintf(bf, "\" %x\n", sev);
			have_startup = 1;
			break;
		    }

		    case 'X': {
			/* Disable exception handling */
			output_except = 0;
			break;
		    }

		    case 'Z': {
			/* Set maximum number of errors */
			BUFFER *bf = &internal_buff;
			if (!started_scope) {
			    bfprintf(bf, "#pragma TenDRA begin\n");
			    started_scope = 1;
			}
			bfprintf(bf, "#pragma TenDRA set error limit");
			bfprintf(bf, " %x\n", uarg);
			have_startup = 1;
			break;
		    }

		    case 'a': {
			/* Complete program checks */
			complete_program = 1;
			break;
		    }

		    case 'c': {
			/* Disable TDF output */
			output_capsule = 0;
			break;
		    }

		    case 'd': {
			/* Dump file */
			string dump;
			uarg = xustrcpy(uarg);
			dump = ustrchr(uarg, '=');
			if (dump == NULL) {
			    const char *err = "Bad '-%c' option";
			    error(ERR_WARN, err, opt);
			    break;
			}
			if (dump_name) {
			    const char *err = "Multiple dump files";
			    error(ERR_WARN, err);
			}
			dump_opt = uarg;
			dump_name = dump + 1;
			break;
		    }

		    case 'e': {
			/* End-up file */
			LIST(string)p;
			uarg = xustrcpy(uarg);
			CONS_string(uarg, NULL_list(string), p);
			endup_files = APPEND_list(endup_files, p);
			have_startup = 1;
			break;
		    }

		    case 'f': {
			/* Start-up file */
			LIST(string)p;
			uarg = xustrcpy(uarg);
			CONS_string(uarg, NULL_list(string), p);
			startup_files = APPEND_list(startup_files, p);
			have_startup = 1;
			break;
		    }

		    case 'g': {
			/* Diagnostics mode */
			if (uarg[0] == 0) {
			    output_diag = DIAG_VERSION;
			} else if (uarg[1] == 0) {
			    switch (uarg[0]) {
				case '0': output_diag = 0; break;
				case '1': output_diag = 1; break;
				case '2': output_diag = 2; break;
				default : known = 0; break;
			    }
			} else {
			    known = 0;
			}
			break;
		    }

		    case 'h':
		    case '?': {
			/* Help option */
			report_usage(error_file);
			break;
		    }

		    case 'i': {
			/* Machine name */
			machine_name = strlit(xustrcpy(uarg));
			break;
		    }

		    case 'j': {
			/* Output options */
			output_option(uarg);
			break;
		    }

		    case 'm': {
			/* Error options */
			error_option(uarg);
			break;
		    }

		    case 'n': {
			/* Portability table */
			if (table_name) {
			    const char *err = "Multiple portability tables";
			    error(ERR_WARN, err);
			}
			table_name = xustrcpy(uarg);
			break;
		    }

		    case 'o': {
			/* Output file */
			if (output) {
			    const char *err = "Multiple output files";
			    error(ERR_WARN, err);
			}
			output = xustrcpy(uarg);
			break;
		    }

		    case 'q': {
			/* Quit immediately */
			quit_immediately = 1;
			break;
		    }

		    case 'r': {
			/* Error marker file */
			output_name[OUTPUT_ERROR] = xustrcpy(uarg);
			break;
		    }

		    case 's': {
			/* Spec output file */
			if (spec_name) {
			    const char *err = "Multiple spec output files";
			    error(ERR_WARN, err);
			}
			spec_name = xustrcpy(uarg);
			break;
		    }

		    case 't': {
			/* Output TDF token declarations */
			output_tokdec = 1;
			break;
		    }

		    case 'u': {
			/* Unmangle an identifier name */
			unmangle_names = 1;
			break;
		    }

		    case 'v': {
			/* Print version number */
			string v = report_version(1);
			fprintf_v(error_file, "%s\n\n", strlit(v));
			break;
		    }

		    case 'w': {
			/* Suppress all warnings */
			preset(OPT_warning, OPTION_OFF);
			check_level = 0;
			break;
		    }

		    case 'z': {
			/* Ignore compilation errors */
			preset(OPT_error, OPTION_WARN);
			max_errors = ULONG_MAX;
			break;
		    }

		    case '-': {
			/* Last option */
			allow_opt = 0;
			break;
		    }

#ifndef NDEBUG
		    case 'x': {
			/* Debug options */
			debug_option(arg);
			quit_immediately = 1;
			break;
		    }
#endif
		}
	    }

	    /* Deal with unknown options */
	    if (known == 0) {
		const char *err = "Unknown option, '-%c%s'";
		error(ERR_WARN, err, opt, arg);
	    }
	    opt = next_opt;
	}
    }
    if (opt) {
	const char *err = "Incomplete option, '-%c'";
	error(ERR_WARN, err, opt);
    }

    /* Examine list of files */
    if (IS_NULL_list(files)) {
	CONS_string(NULL, NULL_list(string), files);
    }
    if (output || IS_NULL_list(TAIL_list(files))) {
	CONS_string(output, files, files);
	output_last = 1;
    }
    files = REVERSE_list(files);
    return files;
}


/**
 * INITIALISE FILE LOCATIONS
 *
 * This routine initialises the standard file locations.
 */

static void
init_loc(void)
{
    IGNORE set_crt_loc(ustrlit("<builtin-in>"), 1);
    builtin_loc = crt_loc;
    IGNORE set_crt_loc(ustrlit("<command-line>"), 1);
    preproc_loc = crt_loc;
    decl_loc = crt_loc;
    stmt_loc = crt_loc;
    return;
}


/**
 * PERFORM LANGUAGE DEPENDENT INITIALISATION
 *
 * This routine performs any language dependent initialisation not covered in
 * the main initialisation routines. Note that the default language is C++.
 */

static void
init_lang(int c)
{
    if (c) {
	crt_linkage = dspec_c;
	set_std_namespace(NULL_id);
    }
    init_tok(c);
    return;
}


/**
 * CALL MAIN INITIALISATION ROUTINES
 *
 * This routine calls all the initialisation routines.
 */

static void
init_main(void)
{
    /* Set file locations */
    crt_loc = builtin_loc;
    decl_loc = builtin_loc;
    stmt_loc = builtin_loc;
    preproc_loc = builtin_loc;

    /* Initialise errors and options */
    init_hash();
    init_lang(LANGUAGE_C);
    init_catalog();
    init_option(check_level);
    if (output_diag) record_location = 1;
    init_dump(dump_name, dump_opt);
    if (do_header) dump_start(&crt_loc, NIL(INCL_DIR));

    /* Initialise macros and keywords */
    init_char();
    init_constant();
    init_keywords();
    init_macros(builtin_macros, builtin_asserts);

    /* Read the portability table */
    read_table(table_name);

    /* Initialise types and namespaces */
    init_namespace();
    push_namespace(global_namespace);
    init_types();
    init_literal();
    init_exception();
    init_printf();
    init_initialise();
    init_token_args();
    init_templates();
    if (do_header) dump_end(&crt_loc);
    return;
}


/**
 * CALL MAIN TERMINATION ROUTINES
 *
 * This routine frees any memory unneeded after the parsing routines.
 */

static void
term_main(void)
{
    free_candidates(&candidates);
    free_buffer(&field_buff);
    free_buffer(&token_buff);
    term_macros();
    term_input();
    term_catalog();
    term_itypes();
    return;
}


/**
 * CALL MAIN FILE PROCESSING ROUTINES
 *
 * This routine calls the main routines for processing the given list of
 * files. This will have at least two elements, the last of which is the
 * output file.
 */

static void
process_files(LIST(string)files)
{
    /* Find output file */
    int action;
    unsigned len;
    string output;
    PARSE_STATE st;
    unsigned max_len = 2;
    int mode = text_mode;
    LIST(string)input;

    /* Find output file */
    if (output_last) {
	LIST(string)end = END_list(files);
	output = DEREF_string(HEAD_list(end));
	input = files;
    } else {
	output = DEREF_string(HEAD_list(files));
	input = TAIL_list(files);
    }
    output_name[OUTPUT_TDF] = output;
    output_name[OUTPUT_SPEC] = spec_name;

    /* Find processing action */
    save_state(&st, 0);
    crt_state_depth = 0;
    if (spec_linker) {
	output_capsule = 0 ;	/* remove later */
	init_capsule();
	max_len = 0;
	action = 2;
    } else if (preproc_only) {
	output_name[OUTPUT_PREPROC] = output;
	output_tdf = 0;
	output_capsule = 0;
	action = 1;
    } else {
	init_capsule();
	action = 0;
    }

    /* Check number of input files */
    len = LENGTH_list(files);
    if (max_len && len > max_len) {
	const char *err = "Too many arguments (should have %u)";
	error(ERR_WARN, err, max_len);
	len = max_len;
    }

    /* Process start-up files in spec linker mode */
    if (action == 2) {
	if (have_startup) {
	    IGNORE open_input(mode);
	    crt_loc = builtin_loc;
	    input_name = NULL;
	    input_file = NULL;
	    process_file();
	    close_input();
	}
	mode = binary_mode;
    }

    /* Scan through input files */
    while (len >= 2) {
	/* Open input file */
	input_name = DEREF_string(HEAD_list(input));
	if (!open_input(mode)) {
	    fail(ERR_fail_input(input_name));
	    term_error(0);
	    return;
	}
	init_diag();

	/* Process input file */
	switch (action) {
	    case 0: {
		/* Parsing action */
		process_file();
		break;
	    }
	    case 1: {
		/* Preprocessing action */
		preprocess_file();
		break;
	    }
	    case 2: {
		/* Spec linker action */
		if (read_spec()) have_syntax_error = 1;
		no_declarations++;
		break;
	    }
	}

	/* Close input file */
	clear_decl_blocks();
	close_input();
	input = TAIL_list(input);
	len--;
    }

    /* Write output file */
    if (have_syntax_error) {
	suppress_variable = 2;
	no_declarations++;
    }
    init_diag();
    preproc_loc = crt_loc;
    restore_state(&st);
    if (action == 1) {
	/* Preprocessing action */
	term_option();
    } else {
	/* Compilation actions */
	external_declaration(NULL_exp, 0);
	clear_templates(2);
	term_main();
	IGNORE check_global(complete_program);
	term_option();
	compile_pending();
	write_capsule();
    }
    return;
}


/*
 * MAIN ROUTINE
 *
 * This is the main routine. It processes the command-line options, calls the
 * initialisation routines and calls the main processing routine.
 */

int
main(int argc, char **argv)
{
    LIST(string)files;
    set_progname(argv[0], PROG_VERSION);
    IGNORE set_machine(FS_MACHINE);
    init_loc();
    files = process_args(argc - 1, argv + 1);
    builtin_startup();
    if (!quit_immediately) {
	/* Process files */
	init_main();
	if (unmangle_names) {
	    unmangle_list(files, stdout, 1);
	} else {
	    process_files(files);
	    term_error(0);
	}
    }
    return exit_status;
}
