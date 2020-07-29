/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * arg-parse.c - Command line argument parsing.
 *
 * This file implements the command line argument parsing routines specified
 * in "arg-parse.h".  See that file for more details.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include "arg-parse.h"

void
arg_parse_intern_descriptions(ArgListT *arg_list)
{
	while (arg_list->name != NULL || arg_list->short_name != '\0') {
		EStringT *estring = error_lookup_string(arg_list->u.name);

		assert(estring != NULL);
		arg_list->u.message = estring;
		arg_list++;
	}
}

/* TODO: this function is ridiculous. could we drop long arguments and use getopt? */
int
arg_parse_arguments(ArgListT *arg_list, EStringT *usage, int argc, char **argv)
{
	int       tmp_argc = argc;
	char    **tmp_argv = argv;
	ArgUsageT closure;

	closure.usage    = error_string_contents(usage);
	closure.arg_list = arg_list;
	while (tmp_argc) {
		char *option = tmp_argv[0];
		char  c      = option[0];

		if (((c == '-' && option[1] == '-')
				|| (c == '+' && option[1] == '+'))
			&& option[2] == '\0') {
			return argc - tmp_argc + 1;
		} else if ((c == '-' && option[1] == '-')
			|| (c == '+' && option[1] == '+')) {

			ArgListT *tmp_list  = arg_list;
			ArgListT *chosen    = NULL;
			unsigned matches   = 0;
			char *immediate = NULL;

			while (tmp_list->name != NULL || tmp_list->short_name != '\0') {
				char *opt = tmp_list->name;
				char *arg = &option[2];

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
						immediate = (arg - 1);
						break;
					} else if (optch == '\0'
						&& (tmp_list->type == AT_IMMEDIATE
							|| tmp_list->type == AT_EITHER)) {
						chosen    = tmp_list;
						matches   = 1;
						immediate = (arg - 1);
						break;
					} else if (argch == '\0') {
						chosen = tmp_list;
						matches++;
					}
				}
				tmp_list++;
			}

			if (matches == 0) {
				error(ERR_FATAL, "unknown option '%s'", option);
				UNREACHED;
			} else if (matches > 1) {
				error(ERR_FATAL, "ambiguous option '%s'", option);
				UNREACHED;
			} else {
				switch (chosen->type)EXHAUSTIVE {
				case AT_SWITCH:
					*((bool *) (chosen->closure)) = (c == '-');	/* TODO cast? */
					break;

				case AT_NEG_SWITCH:
					*((bool *) (chosen->closure)) = (c == '+');
					break;

				case AT_PROC_SWITCH:
					chosen->proc(option, &closure, chosen->closure, c == '-');
					break;

				case AT_IMMEDIATE:
					if (immediate != NULL) {
						chosen->proc(option, &closure, chosen->closure, immediate);
					} else {
						error(ERR_FATAL, "unknown option '%s'", option);
						UNREACHED;
					}
					break;

				case AT_EITHER:
					if (immediate != NULL) {
						if (immediate[0]!= '\0') {
							chosen->proc(option, &closure,
							chosen->closure, immediate);
						} else if (tmp_argc > 1) {
							tmp_argv++;
							tmp_argc--;
							chosen->proc(option, &closure,
							chosen->closure, tmp_argv[0]);
						} else {
							error(ERR_FATAL, "missing argument for option '%s'", option);
							UNREACHED;
						}
					} else {
						error(ERR_FATAL, "unknown option '%s'", option);
						UNREACHED;
					}
					break;

				case AT_FOLLOWING:
					if (tmp_argc > 1) {
						tmp_argv++;
						tmp_argc--;
						chosen->proc(option, &closure, chosen->closure,
						tmp_argv[0]);
					} else {
						error(ERR_FATAL, "missing argument for option '%s'", option);
						UNREACHED;
					}
					break;

				case AT_EMPTY:
					chosen->proc(option, &closure, chosen->closure);
					break;

				case AT_FOLLOWING2:
					if (tmp_argc > 2) {
						tmp_argv += 2;
						tmp_argc -= 2;
						chosen->proc(option, &closure, chosen->closure,
						tmp_argv[-1], tmp_argv[0]);
					} else {
						error(ERR_FATAL, "missing argument for option '%s'", option);
						UNREACHED;
					}
					break;

				case AT_FOLLOWING3:
					if (tmp_argc > 3) {
						tmp_argv += 3;
						tmp_argc -= 3;
						chosen->proc(option, &closure, chosen->closure,
						tmp_argv[-2], tmp_argv[-1],
						tmp_argv[0]);
					} else {
						error(ERR_FATAL, "missing argument for option '%s'", option);
						UNREACHED;
					}
					break;
				}
			}
		} else if ((c == '-' && option[1] == '+')
			|| (c == '+' && option[1] == '-')
			|| (c == '-' && option[1] == '\0')
			|| (c == '+' && option[1] == '\0')) {
			error(ERR_FATAL, "unknown option '%s'", option);
			UNREACHED;
		} else if (c == '-' || c == '+') {
			char *opt = &option[1];

			while (opt != NULL && *opt != '\0') {
				ArgListT *tmp_list = arg_list;
				ArgListT *chosen   = NULL;

				while (tmp_list->name != NULL || tmp_list->short_name != '\0') {
					if (tmp_list->short_name == *opt) {
						chosen = tmp_list;
						break;
					}
					tmp_list++;
				}

				if (chosen) {
					switch (chosen->type)EXHAUSTIVE {
					case AT_SWITCH:
						*((bool *) chosen->closure) = (c == '-');
						break;

					case AT_NEG_SWITCH:
						*((bool *) chosen->closure) = (c == '+');
						break;

					case AT_PROC_SWITCH:
						chosen->proc(opt, &closure, chosen->closure, c == '-');
						break;

					case AT_IMMEDIATE:
						chosen->proc(opt, &closure, chosen->closure, opt + 1);
						opt = NULL;
						break;

					case AT_EITHER:
						if (opt[1]!= '\0') {
							chosen->proc(opt, &closure, chosen->closure, opt + 1);
						} else if (tmp_argc > 1) {
							tmp_argv++;
							tmp_argc--;
							chosen->proc(opt, &closure, chosen->closure, tmp_argv[0]);
						} else {
							error(ERR_FATAL, "missing argument for option '%s' at '%s'", option, opt);
							UNREACHED;
						}
						opt = NULL;
						break;

					case AT_FOLLOWING:
						if (tmp_argc > 1) {
							tmp_argv++;
							tmp_argc--;
							chosen->proc(opt, &closure, chosen->closure,
							tmp_argv[0]);
						} else {
							error(ERR_FATAL, "missing argument for option '%s' at '%s'", option, opt);
							UNREACHED;
						}
						break;

					case AT_EMPTY:
						chosen->proc(opt, &closure, chosen->closure);
						break;

					case AT_FOLLOWING2:
						if (tmp_argc > 2) {
							tmp_argv += 2;
							tmp_argc -= 2;
							chosen->proc(opt, &closure, chosen->closure,
							tmp_argv[-1], tmp_argv[0]);
						} else {
							error(ERR_FATAL, "missing argument for option '%s' at '%s'", option, opt);
							UNREACHED;
						}
						break;

					case AT_FOLLOWING3:
						if (tmp_argc > 3) {
							tmp_argv += 3;
							tmp_argc -= 3;
							chosen->proc(opt, &closure, chosen->closure,
								tmp_argv[-2], tmp_argv[-1], tmp_argv[0]);
						} else {
							error(ERR_FATAL, "missing argument for option '%s' at '%s'", option, opt);
							UNREACHED;
						}
						break;
					}
				} else {
					error(ERR_FATAL, "unknown short option '%s' at '%s'", option, opt);
					UNREACHED;
				}

				if (opt) {
					opt++;
				}
			}
		} else {
			return argc - tmp_argc;
		}
		tmp_argv++;
		tmp_argc--;
	}

	return argc;
}

void
write_arg_usage(OStreamT *ostream, ArgUsageT *closure)
{
	const char *usage        = closure->usage;
	ArgListT *arg_list = closure->arg_list;

	write_cstring(ostream, usage);
	while (arg_list->name != NULL || arg_list->short_name != '\0') {
		const char *desc = error_string_contents(arg_list->u.message);

		if (arg_list->name) {
			write_newline(ostream);
			write_cstring(ostream, "    {--|++}");
			write_cstring(ostream, arg_list->name);
		}

		if (arg_list->short_name != '\0') {
			write_newline(ostream);
			write_cstring(ostream, "    {-|+}");
			write_char(ostream, arg_list->short_name);
		}

		if (arg_list->short_name != '\0' || arg_list->name) {
			write_cstring(ostream, desc);
			write_newline(ostream);
		}
		arg_list++;
	}
}
