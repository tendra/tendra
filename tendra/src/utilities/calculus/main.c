/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "argparse.h"
#include "msgcat.h"
#include "ostream.h"
#include "tenapp.h"

#include "read.h"
#include "calculus.h"
#include "catstdn.h"
#include "check.h"
#include "code.h"
#include "common.h"
#include "disk.h"
#include "lex.h"
#include "output.h"
#include "pretty.h"
#include "print.h"
#include "template.h"
#include "token.h"
#include "write.h"


/*
 *    ACTIONS
 *
 *    These macros are used to describe the various actions which the
 *    program can perform.
 */

#define ACTION_C		0
#define ACTION_TOKEN		1
#define ACTION_DISK		2
#define ACTION_PRETTY		3
#define ACTION_PRINT		4
#define ACTION_WRITE		5
#define ACTION_LIST		6
#define ACTION_TEMPL		7

static char *input = NULL;
static char *alg_value = NULL;
static int need_alg = 1;
static int action = ACTION_C;
static BoolT text = 1;


/*
 *    LIST ACTION
 *
 *    This is the trivial action which just prints a list of all the types
 *    in the algebra.
 */

static void
list_action(char *nm)
{
    OStreamT outfile;

    if (streq (nm, ".")) {
		output_file = ostream_output;
    } else {
		output_file = &outfile;
		if (!ostream_open(output_file, nm)) {
			MSG_cant_open_output_file (nm);
			return;
		}
    }
    LOOP_TYPE output ("%TT ;\n", CRT_TYPE);
    flush_output ();
    if (output_file != ostream_output) ostream_close (output_file);
    return;
}


static void
opt_algebra(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	alg_value = value;
}

static void
opt_etypes(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	if (need_alg) new_algebra ();
	process_file (value, 0);
	need_alg = 0;
}

static void
opt_template(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	/* Template file */
	if (action == ACTION_TOKEN) token_cond = 1;
	input = value;
	action = ACTION_TEMPL;
}

static void
opt_action(char *option, void *closure)
{
	UNUSED(closure);

	/* Output flags */
	switch (option[0]) {
	case 'c': action = ACTION_C; break;
	case 'd': action = ACTION_DISK; break;
	case 'l': action = ACTION_LIST; break;
	case 'o': action = ACTION_PRETTY; break;
	case 'p': action = ACTION_PRINT; break;
	case 't': action = ACTION_TOKEN; break;
	case 'w': action = ACTION_WRITE; break;
	}
}


static void opt_help(char *option, void *closure);

static ArgListT cmdl_opts[] = {
	AP_OPT_EITHER	(algebra,	'A', NULL, opt_algebra),
	AP_OPT_EITHER	(etypes,	'E', NULL, opt_etypes),
	AP_OPT_EITHER	(template,	'T', NULL, opt_template),
	AP_OPT_EMPTY	(version, 	'V', NULL, arg_std_version),
	AP_OPT_SET		(assertions,'a', NULL, &extra_asserts),
	AP_OPT_EMPTY	(genc,		'c', NULL, &opt_action),
	AP_OPT_EMPTY	(gendisk,	'd', NULL, &opt_action),
	AP_OPT_SET		(extheaders,'e', NULL, &extra_headers),
	AP_OPT_EMPTY	(help,		'h', "help", opt_help),
	AP_OPT_SET		(intext,	'i', NULL, &text),
	AP_OPT_EMPTY	(genlist,	'l', NULL, &opt_action),
	AP_OPT_RESET	(nomproto,	'm', NULL, &map_proto),
	AP_OPT_RESET	(noconsttok,'n', NULL, &const_tokens),
	AP_OPT_EMPTY	(genpretty,	'o', NULL, &opt_action),
	AP_OPT_EMPTY	(genprint,	'p', NULL, &opt_action),
	AP_OPT_RESET	(inbin,		'r', NULL, &text),
	AP_OPT_EMPTY	(gentoken,	't', NULL, &opt_action),
	AP_OPT_RESET	(noverbose,	'v', NULL, &verbose_output),
	AP_OPT_EMPTY	(genwrite,	'w', NULL, &opt_action),
	AP_OPT_RESET	(novector,	'x', NULL, &allow_vec),
	AP_OPT_RESET	(nostack,	'z', NULL, &allow_stack),
	AP_OPT_EOL
};

static void
opt_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_usage ();
	arg_print_usage (cmdl_opts);
	msg_append_newline ();
}


/*
 *    MAIN ROUTINE
 *
 *    This is the main routine.  It processes the command-line options,
 *    reads the input file, and writes the output files.
 */

int
main(int argc, char **argv)
{
	char *out;
	int optcnt, had_alg;

    /* Scan arguments */
    tenapp_init(argc, argv, "Algebraic type system tool", "1.3");
	argc--;
	argv++;
	had_alg = 0;
	for (; argc > 0; argv++, argc--) {
		optcnt = arg_parse_arguments (cmdl_opts, argc, argv);
		argc -= optcnt;
		argv += optcnt;
		if (argc == 1 && had_alg)
			break;
		if (argc <= 0)
			MSG_getopt_not_enough_arguments ();
		if (need_alg)
			new_algebra ();
		if (text) {
			process_file (*argv, 1);
		} else {
			read_file (*argv);
		}
		check_types ();
		check_names (0);
		need_alg = 1;
		had_alg = 1;
	}
	if (argc > 1)
		MSG_getopt_too_many_arguments ();
	out = (argc == 1 ? *argv : ".");
    if (!need_alg) MSG_badly_placed_E_option ();

    /* Look up output algebra */
    if (alg_value) {
		ALGEBRA_DEFN *al = find_algebra (alg_value);
		if (al == NULL) {
			MSG_algebra_not_defined(alg_value);
		} else {
			algebra = al;
		}
    }

    /* Generate output */
    if (exit_status == EXIT_SUCCESS) {
		switch (action) {
	    case ACTION_C : main_action_c (out); break;
	    case ACTION_TOKEN : main_action_tok (out); break;
	    case ACTION_DISK : disk_action (out); break;
	    case ACTION_PRETTY : pretty_file (out); break;
	    case ACTION_PRINT : print_action (out); break;
	    case ACTION_WRITE : write_file (out); break;
	    case ACTION_LIST : list_action (out); break;
	    case ACTION_TEMPL : template_file (input, out); break;
		}
    } else {
		MSG_no_output_generated_due_errors ();
    }
    tenapp_exit();
    return (0);
}
