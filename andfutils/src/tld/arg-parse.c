/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/*
 * arg-parse.c - Command line argument parsing.
 *
 * This file implements the command line argument parsing routines specified
 * in "arg-parse.h".  See that file for more details.
 */

#include "arg-parse.h"
#include "gen-errors.h"

void
arg_parse_intern_descriptions(ArgListT *arg_list)
{
    while ((arg_list->name != NIL(char *)) ||
	  (arg_list->short_name != '\0')) {
	EStringT *estring = error_lookup_string(arg_list->u.name);

	ASSERT(estring != NIL(EStringT *));
	arg_list->u.message = estring;
	arg_list++;
    }
}

int
arg_parse_arguments(ArgListT *arg_list,			     EStringT *usage ,
			     int      argc ,
			     char   **argv)
{
    int       tmp_argc = argc;
    char    **tmp_argv = argv;
    ArgUsageT closure;

    closure.usage    = error_string_contents(usage);
    closure.arg_list = arg_list;
    while (tmp_argc) {
	char * option = (tmp_argv[0]);
	char     c      = (option[0]);

	if ((((c == '-') && (option[1] == '-')) ||
	    ((c == '+') && (option[1] == '+'))) && (option[2] == '\0')) {
	    return(argc - tmp_argc + 1);
	} else if (((c == '-') && (option[1] == '-')) ||
		  ((c == '+') && (option[1] == '+'))) {
	    ArgListT *tmp_list  = arg_list;
	    ArgListT *chosen    = NIL(ArgListT *);
	    unsigned matches   = 0;
	    char * immediate = NIL(char *);

	    while ((tmp_list->name != NIL(char *)) ||
		  (tmp_list->short_name != '\0')) {
		char * opt = (tmp_list->name);
		char * arg = (& (option[2]));

		if (opt != NIL(char *)) {
		    char optch;
		    char argch;

		    do {
			optch = (*opt++);
			argch = (*arg++);
		    } while (optch && argch && (optch == argch));
		    if (optch == argch) {
			chosen    = tmp_list;
			matches   = 1;
			immediate = (arg - 1);
			break;
		    } else if ((optch == '\0') &&
			      (((tmp_list->type) == AT_IMMEDIATE) ||
				((tmp_list->type) == AT_EITHER))) {
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
		E_arg_parse_unknown_option(option, &closure);
		UNREACHED;
	    } else if (matches > 1) {
		E_arg_parse_ambiguous_option(option, &closure);
		UNREACHED;
	    } else {
		switch (chosen->type)EXHAUSTIVE {
		  case AT_SWITCH:
		   (*((BoolT *)(chosen->closure))) = (c == '-');
		    break;
		  case AT_NEG_SWITCH:
		   (*((BoolT *)(chosen->closure))) = (c == '+');
		    break;
		  case AT_PROC_SWITCH:
		   (*(chosen->proc))(option, &closure, chosen->closure,
				       c == '-');
		    break;
		  case AT_IMMEDIATE:
		    if (immediate != NIL(char *)) {
			(*(chosen->proc))(option, &closure, chosen->closure,
					   immediate);
		    } else {
			E_arg_parse_unknown_option(option, &closure);
			UNREACHED;
		    }
		    break;
		  case AT_EITHER:
		    if (immediate != NIL(char *)) {
			if (immediate[0]!= '\0') {
			   (*(chosen->proc))(option, &closure,
					       chosen->closure, immediate);
			} else if (tmp_argc > 1) {
			    tmp_argv++;
			    tmp_argc--;
			   (*(chosen->proc))(option, &closure,
					       chosen->closure, tmp_argv[0]);
			} else {
			    E_arg_parse_missing_argument(option, &closure);
			    UNREACHED;
			}
		    } else {
			E_arg_parse_unknown_option(option, &closure);
			UNREACHED;
		    }
		    break;
		  case AT_FOLLOWING:
		    if (tmp_argc > 1) {
			tmp_argv++;
			tmp_argc--;
			(*(chosen->proc))(option, &closure, chosen->closure,
					   tmp_argv[0]);
		    } else {
			E_arg_parse_missing_argument(option, &closure);
			UNREACHED;
		    }
		    break;
		  case AT_EMPTY:
		   (*(chosen->proc))(option, &closure, chosen->closure);
		    break;
		  case AT_FOLLOWING2:
		    if (tmp_argc > 2) {
			tmp_argv += 2;
			tmp_argc -= 2;
			(*(chosen->proc))(option, &closure, chosen->closure,
					   tmp_argv[-1], tmp_argv[0]);
		    } else {
			E_arg_parse_missing_argument(option, &closure);
			UNREACHED;
		    }
		    break;
		  case AT_FOLLOWING3:
		    if (tmp_argc > 3) {
			tmp_argv += 3;
			tmp_argc -= 3;
			(*(chosen->proc))(option, &closure, chosen->closure,
					   tmp_argv[-2], tmp_argv[-1],
					   tmp_argv[0]);
		    } else {
			E_arg_parse_missing_argument(option, &closure);
			UNREACHED;
		    }
		    break;
		}
	    }
	} else if (((c == '-') && (option[1] == '+')) ||
		  ((c == '+') && (option[1] == '-')) ||
		  ((c == '-') && (option[1] == '\0')) ||
		  ((c == '+') && (option[1] == '\0'))) {
	    E_arg_parse_unknown_option(option, &closure);
	    UNREACHED;
	} else if ((c == '-') || (c == '+')) {
	    char * opt = & (option[1]);

	    while ((opt != NIL(char *)) && (*opt != '\0')) {
		ArgListT *tmp_list = arg_list;
		ArgListT *chosen   = NIL(ArgListT *);

		while ((tmp_list->name != NIL(char *)) ||
		      (tmp_list->short_name != '\0')) {
		    if (tmp_list->short_name == *opt) {
			chosen = tmp_list;
			break;
		    }
		    tmp_list++;
		}
		if (chosen) {
		    switch (chosen->type)EXHAUSTIVE {
		      case AT_SWITCH:
			(*((BoolT *)(chosen->closure))) = (c == '-');
			break;
		      case AT_NEG_SWITCH:
			(*((BoolT *)(chosen->closure))) = (c == '+');
			break;
		      case AT_PROC_SWITCH:
			(*(chosen->proc))(opt, &closure, chosen->closure,
					   c == '-');
			break;
		      case AT_IMMEDIATE:
			(*(chosen->proc))(opt, &closure, chosen->closure,
					   opt + 1);
			opt = NIL(char *);
			break;
		      case AT_EITHER:
			if (opt[1]!= '\0') {
			   (*(chosen->proc))(opt, &closure, chosen->closure,
					       opt + 1);
			} else if (tmp_argc > 1) {
			    tmp_argv++;
			    tmp_argc--;
			   (*(chosen->proc))(opt, &closure, chosen->closure,
					       tmp_argv[0]);
			} else {
			    E_arg_parse_missing_short_arg(option, opt,
							   &closure);
			    UNREACHED;
			}
			opt = NIL(char *);
			break;
		      case AT_FOLLOWING:
			if (tmp_argc > 1) {
			    tmp_argv++;
			    tmp_argc--;
			   (*(chosen->proc))(opt, &closure, chosen->closure,
					       tmp_argv[0]);
			} else {
			    E_arg_parse_missing_short_arg(option, opt,
							   &closure);
			    UNREACHED;
			}
			break;
		      case AT_EMPTY:
			(*(chosen->proc))(opt, &closure, chosen->closure);
			break;
		      case AT_FOLLOWING2:
			if (tmp_argc > 2) {
			    tmp_argv += 2;
			    tmp_argc -= 2;
			   (*(chosen->proc))(opt, &closure, chosen->closure,
					       tmp_argv[-1], tmp_argv[0]);
			} else {
			    E_arg_parse_missing_short_arg(option, opt,
							   &closure);
			    UNREACHED;
			}
			break;
		      case AT_FOLLOWING3:
			if (tmp_argc > 3) {
			    tmp_argv += 3;
			    tmp_argc -= 3;
			   (*(chosen->proc))(opt, &closure, chosen->closure,
					       tmp_argv[-2], tmp_argv[-1],
					       tmp_argv[0]);
			} else {
			    E_arg_parse_missing_short_arg(option, opt,
							   &closure);
			    UNREACHED;
			}
			break;
		    }
		} else {
		    E_arg_parse_unknown_short_opt(option, opt, &closure);
		    UNREACHED;
		}
		if (opt) {
		    opt++;
		}
	    }
	} else {
	    return(argc - tmp_argc);
	}
	tmp_argv++;
	tmp_argc--;
    }
    return(argc);
}

void
write_arg_usage(OStreamT * ostream,			 ArgUsageT *closure)
{
    char * usage    = (closure->usage);
    ArgListT *arg_list = (closure->arg_list);

    write_cstring(ostream, usage);
    while ((arg_list->name != NIL(char *)) ||
	  (arg_list->short_name != '\0')) {
	char * desc = error_string_contents(arg_list->u.message);

	if (arg_list->name) {
	    write_newline(ostream);
	    write_cstring(ostream, "    {--|++}");
	    write_cstring(ostream, arg_list->name);
	    write_cstring(ostream, desc);
	}
	if (arg_list->short_name != '\0') {
	    write_newline(ostream);
	    write_cstring(ostream, "    {-|+}");
	    write_char(ostream, arg_list->short_name);
	    write_cstring(ostream, desc);
	}
	arg_list++;
    }
}

