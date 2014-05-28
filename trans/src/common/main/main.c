/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/getopt.h>
#include <shared/error.h>

#include <main/driver.h>

#include <construct/flags.h>

#include <utility/version.h>

extern int report_versions; /* XXX */

#ifdef NEWDWARF
#include <construct/installtypes.h>
extern bool dump_abbrev;
#endif

static void
usage(FILE *f)
{
	fprintf(f, "usage: %s [-DMPQRVWY] [-%s]\n", progname, driver.opts);

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

int
main(int argc, char *argv[])
{
	int quit = 0;

	set_progname(argv[0], driver.version);
	argv[0] = (char *) progname;

	driver.init();

	{
		char opts[256];
		int c;

		sprintf(opts, "%s%s", "A:B:C:DE:F:G:H:K:MO:PQRS:VWX:YZ" "hv", driver.opts);

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

			case 'D': PIC_code         = 1; break;
			case 'M': strict_fl_div    = 1; break;
			case 'N': do_prom          = 1; break;
			case 'P': do_profile       = 1; break;
			case 'Q': quit             = 1; break;
			case 'R': round_after_flop = 1; break;
			case 'W': writable_strings = 1; break;
			case 'Y': dyn_init         = 1; break;
			case 'Z': report_versions  = 1; break;

			/* TODO: global options as lower case instead */
			case 'V':
			case 'v': trans_version(); return 0;
			case 'h': usage(stdout);   return 0;

#ifdef NEWDWARF
			case 'T':
				dump_abbrev = 1;
			case 'J':
				extra_diags = 1;
				diag = DIAG_DWARF2;
				break;
#endif

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
				usage(stderr);
				return 1;
			}
		}

		argc -= optind;
		argv += optind;
	}

	if (argc != 2) {
		error(ERROR_FATAL, "Input and output file expected");
		usage(stderr); /* XXX: ERROR_USAGE */
		return 1; /* XXX: unreached */
	}

	if (quit) {
		return 0;
	}

	/*
	 * Unset any options which are inappropriate for this particular driver,
	 * resolve options which conflict, and so on.
	 */
	driver.unhas();

	/*
	 * Open TDF capsule for input.
	 * This is typically target-dependant (.t), but could also be a .j file.
	 */
	if (!initreader(argv[0])) {
		error(ERROR_FATAL, "Cannot open input capsule %s", argv[0]);
		exit(EXIT_FAILURE); /* XXX: unreached */
	}

	argc--;

	/* TODO: open output */

	driver.main(argc, argv);

	if (number_errors != 0) {
		return 1;
	}

	return 0;
}

