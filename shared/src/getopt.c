/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Public Domain, 1985, AT&T, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/getopt.h>
#include <shared/string.h>

#define ERR(szz, czz) if (opterr) { (void) fprintf(stderr, "%s%s%c\n", argv[0], szz, czz); }

int opterr = 1;
int optind = 1;
int optopt;
char *optarg;

int
getopt(int argc, char * const *argv, const char *opts)
{
	static int sp = 1;
	const char *cp;

	if (sp == 1) {
		if (optind >= argc) {
			return EOF;
		} else if (argv[optind][0] != '-' || argv[optind][1] == '\0') {
			return EOF;
		} else if (streq(argv[optind], "--")) {
			optind++;
			return EOF;
		}
	}

	optopt = argv[optind][sp];

	if (optopt == ':' || (cp = strchr(opts, optopt)) == NULL) {
		ERR(": illegal option -- ", optopt);

		if (argv[optind][++sp] == '\0') {
			optind++;
			sp = 1;
		}

		return '?';
	}

	if (*++cp == ':') {
		if (argv[optind][sp + 1] != '\0') {
			optarg = &argv[optind++][sp + 1];
		} else if (++optind >= argc) {
			ERR(": option requires an argument -- ", optopt);

			sp = 1;
			return '?';
		} else {
			optarg = argv[optind++];
		}

		sp = 1;
	} else {
		if (argv[optind][++sp] == '\0') {
			sp = 1;
			optind++;
		}
		optarg = NULL;
	}

	return optopt;
}

