/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>
#include <shared/string.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/version.h>
#include <main/print.h>

#include <reader/reader.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/readglob.h>

#include <construct/installglob.h>

#include <flpt/flpt.h>

extern bool report_versions; /* XXX */

FILE *tc_file; /* .t or .j: TDF capsule input */
FILE *as_file; /* .s: assembly text output    */
FILE *st_file; /* .T: symbol table output     */
FILE *ba_file; /* .G: binasm output           */

static FILE *
trans_fopen(const char *path, const char *mode)
{
	FILE *f;

	if (streq(path, "-")) {
		f = mode[0] == 'r' ? stdin : stdout;
	} else {
		f = fopen(path, mode);
		if (f == NULL) {
			error(ERR_FATAL, "Cannot open %s", path);
		}
	}

#ifndef NDEBUG
	setbuf(f, NULL);
#endif

	return f;
}

static void
trans_fclose(FILE *f, const char *name)
{
	if (ferror(f)) {
		perror(name);
		exit(EXIT_FAILURE);
	}

	if (EOF == fclose(f)) {
		perror(name);
		exit(EXIT_FAILURE);
	}
}

static void
trans_usage(FILE *f)
{
	fprintf(f, "usage: %s [-DMPQRVWY] [-%s] "
		"[capsule.t [text.s [symtab.T [binasm.G]]]]\n",
		progname, driver.opts);

	/* XXX: generate these... */

	/* switches */
	fprintf(f, "\t[-A hpux|next|sunos|sco|svr4|sysv|linux|solaris|osf1|icbs|mips|power]\n");
	fprintf(f, "\t[-C hp|gcc|sun|alpha|hppa|o32|xlc|sparc|aout]\n");
	fprintf(f, "\t[-E b|l]\n");
	fprintf(f, "\t[-F aout|elf|xcoff|som|macho]\n");
	fprintf(f, "\t[-G none|stabs|stabx|xdb_old|xdb_new|dwarf|dwarf2|gdb|xdb]\n");
	fprintf(f, "\t[-K cpu]\n");
	fprintf(f, "\t[-S gas|sun|ibm|sgi|ultrix|osf1|hp]\n");

	/* flags */
	fprintf(f, "\t[-B ajpvcfdlmt]\n");
	fprintf(f, "\t[-O acdefghijurstopqy]\n");
	fprintf(f, "\t[-H aorntmcdsiq]\n");
	fprintf(f, "\t[-C asef]\n");
}

static void
translate(FILE *f, const char *name)
{
	/*
	 * Open TDF capsule for reading.
	 * This is typically target-dependant (.t), but could also be a .j file.
	 */
	initreader(f, name);

	init_flpt();

/*
* Initialise the automatically generated reader modules with
* automatically generated inits.h
*/
#include <reader/inits.h>

	top_def = NULL;

	/*
	 * Start the TDF decoder, which calls back to translate_unit()
	 */
	IGNORE d_capsule();

	if (exit_status != 0) {
		exit(EXIT_FAILURE);
	}

	/*
	 * Output binary symbol table (.T file) if required.
	 */
	if (st_file != NULL) {
		driver.symtab();
	}

	/*
	 * Output binary assembly (.G file) if required.
	 */
	if (ba_file != NULL) {
		driver.binasm();
	}

	driver.cleanup();

	if (exit_status != 0) {
		exit(exit_status);
	}
}

int
main(int argc, char *argv[])
{
	bool quit = false;

	set_progname(argv[0], driver.version);
	argv[0] = (char *) progname;

	driver.init();

	{
		char opts[256];
		int c;

		sprintf(opts, "%s%s", "A:B:C:DE:F:G:H:IK:MO:PQRS:VWX:YZ" "TJ" "hv", driver.opts);

		while (c = getopt(argc, argv, opts), c != -1) {
			switch (c) {
			case 'A': abi       = switch_abi      (optarg, driver.abi);       break;
			case 'C': cconv     = switch_cconv    (optarg, driver.cconv);     break;
			case 'E': endian    = switch_endian   (optarg, driver.endian);    break;
			case 'F': format    = switch_format   (optarg, driver.format);    break;
			case 'G': diag      = switch_diag     (optarg, driver.diag);      break;
			case 'S': assembler = switch_assembler(optarg, driver.assembler); break;

			case 'B': builtin   = flags_builtin(builtin, optarg); break;
			case 'O': optim     = flags_optim  (optim,   optarg); break;
			case 'H': has       = flags_has    (has,     optarg); break;
			case 'X': check     = flags_check  (check,   optarg); break;

			case 'D': PIC_code         = true;  break;
			case 'M': strict_fl_div    = true;  break;
			case 'N': do_prom          = true;  break;
			case 'P': do_profile       = true;  break;
			case 'Q': quit             = true;  break;
			case 'R': round_after_flop = true;  break;
			case 'I': do_comment       = true;  break;
			case 'W': writable_strings = true;  break;
			case 'Y': dyn_init         = true;  break;
			case 'Z': report_versions  = true;  break;
#ifdef DWARF2
			case 'T': dump_abbrev      = false; break;
			case 'J': extra_diags      = false; break;
#endif

			/* TODO: global options as lower case instead */
			case 'V':
			case 'v': trans_version();     return 0;
			case 'h': trans_usage(stdout); return 0;

			case 'K':
				if (driver.cpu == NULL) {
					break;
				}

				/* XXX: really this should always have at least one type */
				if (-1 == driver.cpu(optarg)) {
					fprintf(stderr, "%s: %s -K %s\n",
						argv[0], "unrecognised cpu type", optarg);
					return 1;
				}

				break;

			default:
				if (0 == driver.option(c, optarg)) {
					break;
				}

				fprintf(stderr, "%s: %s%c\n",
					argv[0], "illegal option -- ", c);

			case '?':
				trans_usage(stderr);
				return 1;
			}
		}

		argc -= optind;
		argv += optind;
	}

	if (argc > 4) {
		error(ERR_FATAL, "Too many files");
		trans_usage(stderr); /* XXX: ERR_USAGE */
		return 1; /* XXX: unreached */
	}

	if (driver.binasm == NULL && argc >= 4) {
		error(ERR_FATAL, "binasm not provided for this trans");
	}

	if (driver.symtab == NULL && argc >= 3) {
		error(ERR_FATAL, "binary symbol table not provided for this trans");
	}

	if (quit) {
		return 0;
	}

	{
		size_t i;

		struct {
			FILE **f;
			const char *mode;
		} a[] = {
			{ &tc_file, "rb" },
			{ &as_file, "w"  },
			{ &st_file, "wb" },
			{ &ba_file, "wb" }
		};

		tc_file = stdin;
		as_file = stdout;

		for (i = 0; i < argc; i++) {
			*a[i].f = trans_fopen(argv[i], a[i].mode);
		}

		asm_file(as_file);

		if (diag != DIAG_NONE) {
			optim = 0;
			all_variables_visible = true;
		}

		/*
		 * Unset any options which are inappropriate for this particular driver,
		 * resolve options which conflict, and so on.
		 */
		driver.unhas();

		/*
		 * Read, decode and translate a TDF capsule.
		 */
		translate(tc_file, argc > 0 ? argv[0] : "stdin");

		for (i = 0; i < argc; i++) {
			if (*a[i].f != stdout) {
				trans_fclose(*a[i].f, argv[i]);
			}
		}
	}

	return 0;
}

