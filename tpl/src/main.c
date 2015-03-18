/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdio.h>

#include <shared/check.h>

#include "namedecs.h"
#include "lex.h"
#include "includes.h"
#include "syntax.h"
#include "units.h"

static char *pl_version = "tpl 1.4, TDF %lu.%lu (tendra.org)\n";
static char *pl_usage = "tpl [-v] [-Ipath] [-g] [-V] infile.pl outfile.j";

int
main(int argc, char **argv)
{
	int i;
	int ok = 1;
	int diag = 0;
	char *in = NULL;
	char *out = NULL;
	init_includes();
	for (i = 1; i < argc; i++) {
		char *a = argv[i];
		if (a[0] == '-') {
			switch (a[1]) {
			case 'g': {
				if (a[2]) {
					ok = 0;
				}
				diag = 1;
				break;
			}
			case 'I': {
				add_include(a + 2);
				break;
			}
			case 'V': {
				if (a[2]) {
					ok = 0;
				}
				do_pp = 1;
				break;
			}
			case 'v': {
				unsigned long va = MAJOR_NO;
				unsigned long vb = MINOR_NO;
				if (a[2]) {
					ok = 0;
				}
				IGNORE fprintf(stderr, pl_version, va, vb);
				return 0;
			}
			default: {
				ok = 0;
				break;
			}
			}
		} else {
			if (in == NULL) {
				in = a;
			} else if (out == NULL) {
				out = a;
			} else {
				ok = 0;
			}
		}
	}
	if (in == NULL || out == NULL) {
		ok = 0;
	}
	if (!ok) {
		IGNORE fprintf(stderr, "Error: Usage = %s\n", pl_usage);
		exit(EXIT_FAILURE);
	}
	in_file = fopen(in, "r");
	file_name = in;
	if (in_file == NULL) {
		IGNORE fprintf(stderr, "Error: Can't open input file, %s.\n",
			       in);
		exit(EXIT_FAILURE);
	}
	out_file = fopen(out, "wb");
	if (out_file == NULL) {
		IGNORE fprintf(stderr, "Error: Can't open output file, %s.\n",
			       out);
		exit(EXIT_FAILURE);
	}
	lex_v = reader();
	init_units();
	if (diag) {
		line_no_tok = next_capsule_name(tok_ent);
	}
	read_program();
	IGNORE fclose(in_file);
	IGNORE fclose(out_file);
	return 0;
}
