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
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a command line argument parsing
 * facility.  The facility has a standard behaviour, making it easier to have
 * a standard command line argument format.  The facility only parses command
 * line options, which it assumes precede the other arguments.  All options
 * must begin with an option character (either '+' or '-').  The facility
 * supports short (single character) options (should begin with '-' or '+')
 * and long (multiple character) options (should begin with '--' or '++').
 * Any arguments that begins with another character will terminate the parsing
 * without error (so that the program can deal with the remaining arguments).
 * In addition, the option '--' (or '++') will terminate the parse, so that a
 * user may specify non option arguments that begin with an option character.
 *
 * The parsing routines support a number of different option types, and deal
 * with shortest prefixes for non immediate options (an immediate option is
 * one where the data associated with it is part of the option string, and not
 * in a following word).
 *
 ***=== TYPES =================================================================

 ** Type:	ArgListT
 ** Repr:	<private>
 *
 * This is the type of an entry in an option list.  A vector of such entries
 * should be passed to the ``arg_parse_arguments'' function, with the last
 * entry being the ``AP_OPT_EOL'' macro.
 *
 * A typical argument list definition would be something like the following:
 *
 *	ArgListT arg_list [] = {
 *		AP_OPT_PROC_SW(option_name, 'p', NULL, "option name", arg_proc),
 *	    AP_OPT_EOL
 *	};
 *
 * If an option has only a short form, then the name should be NULL,
 * if it has only a long form, then the character should be '\0'.  It is
 * illegal for an option to have neither a long form or a short form.
 *
 ***=== MACROS ================================================================
 *
 * The following macros expand to entries for an ArgListT array as shown
 * above.  The description name is the identifier used in the message
 * catalogue to look up the option description, the short name is the
 * character used for a short option (eg. 'x' for -x), the long name is the
 * string used for long options (eg. "xyz" for --xyz), the handler function
 * is a function that is called if the specified option is matched and the
 * closure is an arbitrary user pointer which is passed as context to the
 * invoked handler function.
 *
 *
 *	AP_OPT_SWITCH
 *
 * This is an entry for a switch option.  It accepts a description name, a
 * short name, a long name and a pointer to a boolean.  If the option
 * character is a '-' then the boolean is set.  If the option character is
 * '+' then the boolean is reset.
 *
 *	AP_OPT_NEG_SW
 *
 * This is an entry for a negated switch option.  It accepts a description
 * name, a short name, a long name and a pointer to a boolean.  If the
 * option character is a '-' then the boolean is reset.  If the option
 * character is '+' then the boolean is set.
 *
 *	AP_OPT_PROC_SW
 *
 * This is an entry for a switch option that needs some extra work to be
 * performed.  It accepts a description name, a short name, a long name and
 * a handler function.  The type of the passed function must be void
 * (char *, void *, BoolT).  It will be called with the option that was
 * selected, the option closure, and a boolean (true if the option character
 * is '-', false otherwise).
 *
 *	AP_OPT_IMMEDIATE
 *
 * This is an entry for an option with one immediate argument.  It accepts a
 * description name, a short name, a long name and a handler function.  No
 * shortest prefix matching will be used for immediate arguments.  The type
 * of the passed function must be void (char *, void *, char *).  It will be
 * called with the option that was selected, the option closure, and the
 * argument to the option.  This type of argument should appear at the end
 * of the argument list that is passed to the ``arg_parse_arguments''
 * function, as it may cause problems with shortest prefix matching
 * otherwise.
 *
 *	AP_OPT_EITHER
 *
 * This is an entry for an option with one argument.  It accepts a
 * description name, a short name, a long name and a handler function.  If an
 * immediate argument exists, then that is used.  If no immediate argument
 * exists, then the following argument is used.  No shortest prefix matching
 * will be used for either arguments.  The type of the passed function must
 * be void (char *, void *, char *).  It will be called with the option that
 * was selected, the option closure, and the argument to the option.  This
 * type of argument should appear at the end of the argument list that is
 * passed to the ``arg_parse_arguments'' function, as it may cause problems
 * with shortest prefix matching otherwise.
 *
 *	AP_OPT_FOLLOWING
 *
 * This is an entry for an option with one following argument.  It accepts a
 * description name, a short name, a long name and a handler function.  The
 * type of the passed function must be void (char *, void *, char *).  It
 * will be called with the option that was selected, the option closure, and
 * the argument to the option.
 *
 *	AP_OPT_EMPTY
 *
 * This is an entry for an option with no argument.  It accepts a
 * description name, a short name, a long name and a handler function.  The
 * type of the passed function must be void (char *, void *).  It will be
 * called with the option that was selected and the option closure.
 *
 *	AP_OPT_FOLLOWING2
 *
 * This is an entry for an option with two following arguments.  It accepts
 * a description name, a short name, a long name and a handler function.
 * The type of the passed function must be void (char *, void *, char *,
 * char *).  It will be called with the option that was selected, the option
 * closure, and the arguments to the option.
 *
 *	AP_OPT_FOLLOWING3
 *
 * This is an entry for an option with three following arguments.  It
 * accepts a description name, a short name, a long name and a function
 * pointer.  The type of the passed function must be void (char *, void *,
 * char *, char *, char *).  It will be called with the option that was
 * selected, the option closure, and the arguments to the option.
 *
 * 	AP_OPT_SET
 *
 * This is an entry for an option with no argument.  It accepts a
 * description name, a short name, a long name and a pointer to a boolean.
 * The boolean variable will be set to true if the option is matched.
 *
 *	AP_OPT_RESET
 *
 * This is an entry for an option with no argument.  It accepts a
 * description name, a short name, a long name and a pointer to a boolean.
 * The boolean variable will be set to false if the option is matched.
 *
 *	AP_OPT_EOL
 *
 * This macro should be used to terminate an option list.
 *
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function: arg_parse_arguments
 *
 * This function does the argument parsing.  The first argument should
 * specify the valid options for the program.  The following two arguments
 * should specify the actual arguments passed to the program (argc and
 * argv).  The parsing starts from the first argument, so the first element
 * of the program's argument list (the program name) should not be passed to
 * this function.  The function returns the number of elements of the list
 * that it parsed.
 */


#ifndef H_ARG_PARSE
#define H_ARG_PARSE

typedef enum {
	AT_SWITCH,
	AT_NEG_SWITCH,
	AT_PROC_SWITCH,
	AT_IMMEDIATE,
	AT_EITHER,
	AT_FOLLOWING,
	AT_EMPTY,
	AT_FOLLOWING2,
	AT_FOLLOWING3,
	AT_SET,
	AT_RESET
} ArgTypeT;

typedef void (*ArgProcP)(char *, void *, ...);

typedef struct ArgListT {
	const char *		name;
	char				short_name;
	ArgTypeT			type;
	ArgProcP			proc;
	void *				closure;
	int					msgid;
} ArgListT;

/*--------------------------------------------------------------------------*/

int		arg_parse_arguments(ArgListT *, int, char **);
void	arg_print_usage(ArgListT *);
void	arg_std_version(char *, void *);

/*--------------------------------------------------------------------------*/

#define	AP_OPTION(snm, lnm, type, proc, closure, msgid) \
	{(lnm), (snm), (type), (ArgProcP)(proc), (closure), (msgid)}

#define	AP_OPT_SWITCH(name, snm, lnm, var) \
	AP_OPTION((snm), (lnm), AT_SWITCH, NULL, (var), MID_description_of_##name)

#define	AP_OPT_NEG_SW(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_NEG_SWITCH, NULL, (var), MID_description_of_##name)

#define	AP_OPT_EMPTY(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_EMPTY, (proc), NULL, MID_description_of_##name)

#define	AP_OPT_SET(name, snm, lnm, var) \
	AP_OPTION((snm), (lnm), AT_SET, NULL, (var), MID_description_of_##name)

#define	AP_OPT_RESET(name, snm, lnm, var) \
	AP_OPTION((snm), (lnm), AT_RESET, NULL, (var), MID_description_of_##name)

#define	AP_OPT_EITHER(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_EITHER, (proc), NULL, MID_description_of_##name)

#define	AP_OPT_FOLLOWING(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_FOLLOWING, (proc), NULL, MID_description_of_##name)

#define	AP_OPT_FOLLOWING2(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_FOLLOWING2, (proc), NULL, MID_description_of_##name)

#define	AP_OPT_FOLLOWING3(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_FOLLOWING3, (proc), NULL, MID_description_of_##name)

#define	AP_OPT_IMMEDIATE(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_IMMEDIATE, (proc), NULL, MID_description_of_##name)

#define	AP_OPT_PROC_SW(name, snm, lnm, proc) \
	AP_OPTION((snm), (lnm), AT_PROC_SWITCH, (proc), NULL, MID_description_of_##name)

#define AP_OPT_EOL \
	{NULL, '\0', (ArgTypeT)0, NULL, NULL, 0}

#endif /* !defined (H_ARG_PARSE) */
