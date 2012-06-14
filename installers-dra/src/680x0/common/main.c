/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/error.h>
#include <shared/getopt.h>

#include "config.h"

#include "assembler.h"
#include "basicread.h"
#include "flpt.h"
#include "main_reads.h"
#include "weights.h"
#include "instrs.h"
#include "installglob.h"
#include "exp.h"
#include "externs.h"
#include "flags.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "peephole.h"
#include "szs_als.h"
#include "tests.h"
#include "utility.h"
#include "version.h"
#include "reader_v.h"
#include "construct_v.h"
#include "where.h"

#if have_diagnostics
#include "xdb_basics.h"
#include "xdb_output.h"
#endif

extern int errors;
extern int max_errors;

extern char *optarg;


/*
    PROGRAM NAME AND VERSION NUMBER
*/

static char *version_str = "0.6";
static char *revision = REVISION_STRING;
#ifdef EBUG
static char *revdate = DATE_STRING;
#endif
int normal_version = 1;


/*
    EXTRA COMPILATION FLAGS
*/

int do_pic = 0;
static int do_quit = 0;
static int do_sep_units = 0;
static int ignore_errors = 0;
static int report_trans_version = 0;
static int report_tdf_versions = 0;

#ifdef EBUG

int seek_label = 0;
int seek_extern = 0;
int seek_label_no;
char *seek_extern_id;

int seek_line = 0;
int seek_line_no;
static char *seek_line_id;

#endif

int diag_override;
#if have_diagnostics
static int diag_stab_override = 0;
static int diag_xdb_new_override = 0;
static int diag_xdb_old_override = 0;
#endif



/*
    VARIABLE SIZES AND ALIGNMENTS
*/

alignment MAX_BF_SIZE;


/*
    MAXIMUM EXPONENT FOR FLOATING-POINT NUMBERS
*/

int target_dbl_maxexp = 1024;


/*
    MAIN ROUTINE

    This routine processes the command-line arguments, calls the
    initialization routines, and then calls the main processing
    routines.
*/

int main
(int argc, char **argv)
{
	int a;
	char *input = null;
	char *output = null;

	endian = ENDIAN_BIG;

	{
		int c;

		while ((c = getopt(argc, argv,
			"B:DE:G:HK:MO:PQRVWX:Z"
#ifdef EBUG
			"L:l:"
#endif
#if have_diagnostics
			"dnt"
#endif
			"cegiou")) != -1) {
			switch (c) {
			case 'E': endian = switch_endian(optarg, ENDIAN_BIG); break;

			case 'B': builtin = flags_builtin(optarg); break;
			case 'D': do_pic = 1;                      break;
			case 'G':                                  break;
			case 'H': diagnose = 1;                    break;
			case 'K':                                  break;
			case 'M': strict_fl_div = 1;               break;
			case 'O': optim = flags_optim(optarg);     break;
			case 'P': do_profile = 1;                  break;
			case 'Q': do_quit = 1;                     break;
			case 'R': round_after_flop = 1;            break;
			case 'V': report_trans_version = 1;        break;
			case 'W':                                  break;
			case 'X': check = flags_check(optarg);     break;
			case 'Z': report_tdf_versions = 1;         break;

			case 'c': cc_conventions = 1;              break;
			case 'e': ignore_errors = 1;               break;
			case 'g': cc_conventions = 0;              break;
			case 'i': output_immediately = 1;          break;
			case 'u': do_sep_units = 1;                break;

#if have_diagnostics
			case 'd': diag_xdb_old_override = 1;       break;
			case 'n': diag_xdb_new_override = 1;       break;
			case 't': diag_stab_override = 1;          break;
#endif

#ifdef EBUG
			case 'l': seek_line = 1;
			          seek_line_id = optarg;           break;
			case 'L': seek_extern = 1;
			          seek_extern_id = optarg;         break;
#endif

			case '?':
			default:
				error(ERROR_WARNING, "Unrecognised option, %s", "'unknown option'");
			}
		}

		argc -= optind;
		argv += optind;
	}

	if (argc != 2) {
		error(ERROR_FATAL, "Input and output file expected");
	}

	input  = argv[0];
	output = argv[1];

#ifdef EBUG
    /* Deal with debugging options */
    if (seek_extern) {
	if (is_local(seek_extern_id)) {
	    seek_label = 1;
	    seek_label_no = atoi(seek_extern_id + 1);
	}
    }
    if (seek_line)seek_line_no = atoi(seek_line_id);
#endif

    /* Report version if required */
    if (report_trans_version) {
#ifdef NEXT
	char *machine = "NeXT";
#else
#ifdef SUN
	char *machine = "Sun / 3";
#else
	char *machine = "HP";
#endif
#endif
	fprintf(stderr, "DRA TDF translator (TDF version %d.%d)\n",
		MAJOR_VERSION, MINOR_VERSION);
	fprintf(stderr, "reader %d.%d: ", reader_version,
		reader_revision);
	fprintf(stderr, "construct %d.%d: ", construct_version,
		construct_revision);
	fprintf(stderr, "target %d.%d.%d: \n", target_version,
		target_revision,target_patchlevel);
	fprintf(stderr, "system %s",machine);
#ifdef __DATE__
	fprintf(stderr," : installer compilation %s\n", __DATE__);
#endif
	fprintf(stderr, ".\n");
#ifdef EBUG
	fprintf(stderr, "Last revised %s.\n", revdate);
#endif
    }
    if (report_tdf_versions) {
	    report_versions = 1;
    }

    /* Check on diagnostics */
    if (!have_diagnostics && diagnose) {
	error(ERROR_SERIOUS, "Diagnostics not supported");
	diagnose = 0;
    }

#if have_diagnostics
    diag_override = DIAG_UNKNOWN;
    if (diag_stab_override) {
	    diag_override = DIAG_STAB;
    }
    if (diag_xdb_new_override) {
	    diag_override = DIAG_XDB_NEW;
    }
    if (diag_xdb_old_override) {
	    diag_override = DIAG_XDB_OLD;
    }
#endif

    /* Switch off optimizations if required */
    if (diagnose
#ifdef EBUG
    || 1
#endif
    ) {
	optim = 0;
    }

    /* Check on separate units */
    if (do_sep_units) {
	separate_units = 1;
#if 0
	current_alloc_size = first_alloc_size;
#endif
    }

    do_pic = 0 ; /* TODO */

    /* Other options */
    if (do_pic) {
	    PIC_code = 1;
    }
    
    if (~check & CHECK_EXTRA) {
	    target_dbl_maxexp = 16384;
    }

    if (do_quit) {
	    exit(EXIT_SUCCESS);
    }

    if (!initreader(input)) {
	exit(EXIT_FAILURE);
    }
    /* open_input(input);*/

    /* Set up alignment rules */
    double_align = DBL_ALIGN;
    param_align = PARAM_ALIGN;
    stack_align = STACK_ALIGN;

    MAX_BF_SIZE = (cc_conventions ? MAX_BF_SIZE_CC : MAX_BF_SIZE_GCC);

    /* Call initialization routines */
    top_def = null;
    init_flpt();
    init_instructions();
#include "inits.h"
    init_weights();
    init_wheres();

    /* Decode, optimize and process the input TDF */
    open_output(output);
    asm_comment;
    outs(" TDF to 680x0, ");
    outs("Version: ");
	outs(version_str);
    outs(", ");
    outs(revision);
    outnl();
    init_output();
    area(ptext);
#if have_diagnostics
    if (diagnose) {
	    diag_prologue();
    }
#endif
    d_capsule();
#if have_diagnostics
    if (diagnose) {
	    diag_epilogue();
    }
#endif
#ifdef asm_version
    if (normal_version) {
	asm_version;
    } else {
	asm_version_aux;
    }
    outnl();
#endif
    if (number_errors != 0 && !ignore_errors) {
	    exit(EXIT_FAILURE);
    }
    return 0;
}
