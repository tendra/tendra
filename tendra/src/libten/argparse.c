/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


/*
 * Command line argument parsing.
 *
 * original author: Steve Folkes <smf@hermes.mod.uk>
 */


#include "config.h"

#include "argparse.h"
#include "msgcat.h"

#define	AP_LEFT_MARGIN	28
#define	AP_RIGHT_MARGIN	80
#define	AP_TEXT_LEN		(AP_RIGHT_MARGIN - AP_LEFT_MARGIN)


int
arg_parse_arguments(ArgListT *arg_list, int argc, char **argv)
{
	int       tmp_argc = argc;
	char    **tmp_argv = argv;

	while (tmp_argc) {
		int is_long = 0;
		char *option = tmp_argv[0];
		char c = option[0];

		is_long = (c == '-' && option[1] == '-') ||
			(c == '+' && option[1] == '+');
		if (is_long && option[2] == '\0') {
			return (argc - tmp_argc + 1);
		}
		if (is_long) {
			ArgListT *tmp_list = arg_list;
			ArgListT *chosen = NULL;
			unsigned matches = 0;
			char *immediate = NULL;

			while (tmp_list->name != NULL || tmp_list->short_name != '\0') {
				const char *opt = tmp_list->name;
				char *arg = option + 2;

				if (opt != NULL) {
					char optch;
					char argch;

					do {
						optch = *opt++;
						argch = *arg++;
					} while (optch && argch && optch == argch);
					if (optch == argch) {
						chosen    = tmp_list;
						matches   = 1;
						immediate = arg - 1;
						break;
					} else if (optch == '\0' &&
							   (tmp_list->type == AT_IMMEDIATE ||
								tmp_list->type == AT_EITHER)) {
						chosen    = tmp_list;
						matches   = 1;
						immediate = arg - 1;
						break;
					} else if (argch == '\0') {
						chosen = tmp_list;
						matches++;
					}
				}
				tmp_list++;
			}
			if (matches == 0) {
				MSG_arg_parse_unknown_option (option);
				UNREACHED;
			} else if (matches > 1) {
				MSG_arg_parse_ambiguous_option (option);
				UNREACHED;
			} else {
				switch (chosen->type) EXHAUSTIVE {
				case AT_SWITCH:
					*((BoolP) chosen->closure) = c == '-';
					break;
				case AT_NEG_SWITCH:
					*((BoolP) chosen->closure) = c == '+';
					break;
				case AT_PROC_SWITCH:
					(*chosen->proc) (option, chosen->closure, c == '-');
					break;
				case AT_IMMEDIATE:
					if (immediate != NULL) {
						(*chosen->proc) (option, chosen->closure,
										   immediate);
					} else {
						MSG_arg_parse_unknown_option (option);
						UNREACHED;
					}
					break;
				case AT_EITHER:
					if (immediate != NULL) {
						if (immediate[0] != '\0') {
							(*chosen->proc) (option,
											   chosen->closure, immediate);
						} else if (tmp_argc > 1) {
							tmp_argv++;
							tmp_argc--;
							(*chosen->proc) (option,
											   chosen->closure, tmp_argv [0]);
						} else {
							MSG_arg_parse_missing_argument (option);
							UNREACHED;
						}
					} else {
						MSG_arg_parse_unknown_option (option);
						UNREACHED;
					}
					break;
				case AT_FOLLOWING:
					if (tmp_argc > 1) {
						tmp_argv++;
						tmp_argc--;
						(*chosen->proc) (option, chosen->closure,
										   tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_argument (option);
						UNREACHED;
					}
					break;
				case AT_EMPTY:
					(*chosen->proc) (option, chosen->closure);
					break;
				case AT_FOLLOWING2:
					if (tmp_argc > 2) {
						tmp_argv += 2;
						tmp_argc -= 2;
						(*chosen->proc) (option, chosen->closure,
										   tmp_argv[-1], tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_argument (option);
						UNREACHED;
					}
					break;
				case AT_FOLLOWING3:
					if (tmp_argc > 3) {
						tmp_argv += 3;
						tmp_argc -= 3;
						(*chosen->proc) (option, chosen->closure,
										   tmp_argv[-2], tmp_argv[-1],
										   tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_argument (option);
						UNREACHED;
					}
					break;
				}
			}
		} else if ((c == '-' && option[1] == '+') ||
				   (c == '+' && option[1] == '-') ||
				   (c == '-' && option[1] == '\0') ||
				   (c == '+' && option[1] == '\0')) {
			MSG_arg_parse_unknown_option (option);
			UNREACHED;
		} else if (c == '-' || c == '+') {
			char *opt = &(option [1]);

			while (opt != NULL && *opt != '\0') {
				ArgListT *tmp_list = arg_list;
				ArgListT *chosen = NULL;

				while (tmp_list->name != NULL ||
					   tmp_list->short_name != '\0') {
					if (tmp_list->short_name == *opt) {
						chosen = tmp_list;
						break;
					}
					tmp_list++;
				}
				if (chosen == NULL || (opt[1] &&
					chosen->type != AT_IMMEDIATE && chosen->type != AT_EITHER)) {
					MSG_arg_parse_unknown_short_opt (option, opt);
					UNREACHED;
				}
				switch (chosen->type) EXHAUSTIVE {
				case AT_SWITCH:
					*((BoolP) chosen->closure) = c == '-';
					break;
				case AT_NEG_SWITCH:
					*((BoolP) chosen->closure) = c == '+';
					break;
				case AT_PROC_SWITCH:
					(*chosen->proc) (opt, chosen->closure, c == '-');
					break;
				case AT_IMMEDIATE:
					(*chosen->proc) (opt, chosen->closure, opt + 1);
					opt = NULL;
					break;
				case AT_EITHER:
					if (opt[1] != '\0') {
						(*chosen->proc) (opt, chosen->closure, opt + 1);
					} else if (tmp_argc > 1) {
						tmp_argv++;
						tmp_argc--;
						(*chosen->proc) (opt, chosen->closure, tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_short_arg (option, opt);
						UNREACHED;
					}
					opt = NULL;
					break;
				case AT_FOLLOWING:
					if (tmp_argc > 1) {
						tmp_argv++;
						tmp_argc--;
						(*chosen->proc) (opt, chosen->closure, tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_short_arg (option, opt);
						UNREACHED;
					}
					break;
				case AT_EMPTY:
					(*chosen->proc) (opt, chosen->closure);
					break;
				case AT_FOLLOWING2:
					if (tmp_argc > 2) {
						tmp_argv += 2;
						tmp_argc -= 2;
						(*chosen->proc) (opt, chosen->closure,
										   tmp_argv[-1], tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_short_arg (option, opt);
						UNREACHED;
					}
					break;
				case AT_FOLLOWING3:
					if (tmp_argc > 3) {
						tmp_argv += 3;
						tmp_argc -= 3;
						(*chosen->proc) (opt, chosen->closure,
										   tmp_argv[-2], tmp_argv [-1],
										   tmp_argv[0]);
					} else {
						MSG_arg_parse_missing_short_arg (option, opt);
						UNREACHED;
					}
					break;
				}
				if (opt) {
					opt++;
				}
			}
		} else {
			return (argc - tmp_argc);
		}
		tmp_argv++;
		tmp_argc--;
	}
	return (argc);
}

/*
 * Pretty print specified options
 */
void
arg_print_usage(ArgListT *arg_list)
{
	const char *ae, *msg;
	int have_short, alen, slen;

	msg_append_newline();
	for (; arg_list->name != NULL || arg_list->short_name != '\0'; arg_list++) {
		have_short = 0;
		msg = msg_get_raw(arg_list->msgid);
		msg_append_string("  ");
		slen = 2;
		if (arg_list->short_name) {
			switch (arg_list->type) {
			case AT_SWITCH:
			case AT_NEG_SWITCH:
			case AT_PROC_SWITCH:
				msg_append_string("{+|-}");
				slen += 5;
				break;
			default:
				msg_append_char('-');
				slen++;
			}
			msg_append_char(arg_list->short_name);
			have_short = 1;
			slen++;
		}
		if (arg_list->name) {
			if (have_short) {
				msg_append_string("  [");
				slen += 5;
			}
			switch (arg_list->type) {
			case AT_SWITCH:
			case AT_NEG_SWITCH:
			case AT_PROC_SWITCH:
				msg_append_string("{++|--}");
				slen += 7;
				break;
			default:
				msg_append_string("--");
				slen += 2;
			}
			msg_append_string(arg_list->name);
			if (have_short)
				msg_append_string("] ");
			slen += strlen(arg_list->name);
		}
		ae = strchr (msg, ' ');
		alen = ae ? ae - msg + 1 : 0;
		switch (arg_list->type) {
		case AT_IMMEDIATE:
			if (alen) {
				msg_append_nstring(msg, alen);
				slen += alen;
				msg = ae + 1;
			} else {
				slen += 4;
				msg_append_string("ARG ");
			}
			break;
		case AT_EITHER:
		case AT_FOLLOWING:
		case AT_FOLLOWING2:
		case AT_FOLLOWING3:
			if (arg_list->name == NULL) {
				msg_append_char (' ');
				slen++;
			}
			if (alen) {
				msg_append_nstring(msg, alen);
				slen += alen;
				msg = ae + 1;
			} else {
				slen += 4;
				msg_append_string("ARG ");
			}
			break;
		}
		ae = strchr (msg, ' ');
		alen = ae ? ae - msg + 1 : 0;
		switch (arg_list->type) {
		case AT_FOLLOWING2:
		case AT_FOLLOWING3:
			if (alen) {
				msg_append_nstring(msg, alen);
				slen += alen;
				msg = ae + 1;
			} else {
				slen += 5;
				msg_append_string("ARG2 ");
			}
			break;
		}
		ae = strchr (msg, ' ');
		alen = ae ? ae - msg + 1 : 0;
		switch (arg_list->type) {
		case AT_FOLLOWING3:
			if (alen) {
				msg_append_nstring(msg, alen);
				slen += alen;
				msg = ae + 1;
			} else {
				slen += 5;
				msg_append_string("ARG3 ");
			}
			break;
		}

		if (slen >= AP_LEFT_MARGIN) {
			slen = 0;
			msg_append_newline();
		}
		/*
		 * Now print message with required alignment
		 */
		for (; *msg;) {
			while (++slen < AP_LEFT_MARGIN)
				msg_append_char(' ');
			ae = strchr (msg, '\n');
			if (ae) {
				slen = ae - msg;
				alen = slen + 1;
			} else
				slen = alen = strlen(msg);
			if (slen > AP_TEXT_LEN) {
				for (ae = msg + AP_TEXT_LEN + 1; *ae != ' ' && ae > msg; ae--)
					;
				slen = ae - msg;
				alen = slen + 1;
			}
			msg_append_nstring(msg, slen);
			msg += alen;
			msg_append_newline();
			slen = 0;
		}
	}
}

void
arg_std_version(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	tenapp_report_version();
}
