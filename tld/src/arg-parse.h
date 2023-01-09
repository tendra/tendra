/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * arg-parse.h - Command line argument parsing.
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
 */

#ifndef H_ARG_PARSE
#define H_ARG_PARSE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/error.h>
#include <exds/ostream.h>

/*
 * This is the type of an option.  The constants have the following
 * meanings:
 *
 *	AT_SWITCH
 *
 * This is the type of a switch option.  The procedure value should be null.
 * The closure should be a pointer to a boolean.  If the option character is a
 * '-' then the boolean is set.  If the option character is '+' then the
 * boolean is reset.
 *
 *	AT_NEG_SWITCH
 *
 * This is the type of a negated switch option. The procedure value should be
 * null. The closure should be a pointer to a boolean.  If the option
 * character is a '-' then the boolean is reset.  If the option character is
 * '+' then the boolean is set.
 *
 *	AT_PROC_SWITCH
 *
 * This is the type of a switch option that needs some extra work to be
 * performed.  The procedure will be called with the option that was selected,
 * the error closure, the option closure, and a boolean (true if the option
 * character is '-', false otherwise).
 *
 *	AT_IMMEDIATE
 *
 * This is the type of an option with one immediate argument.  No shortest
 * prefix matching will be used for immediate arguments.  The procedure will
 * be called with the option that was selected, the error closure, the option
 * closure, and the argument to the option.  This type of argument should
 * appear at the end of the argument list that is passed to the
 * ``arg_parse_arguments'' function, as it may cause problems with shortest
 * prefix matching otherwise.
 *
 *	AT_EITHER
 *
 * This is the type of an option with one argument. If an immediate argument
 * exists, then that is used.  If no immediate argument exists, then the
 * following argument is used.  No shortest prefix matching will be used for
 * either arguments.  The procedure will be called with the option that was
 * selected, the error closure, the option closure, and the argument to the
 * option.  This type of argument should appear at the end of the argument
 * list that is passed to the ``arg_parse_arguments'' function, as it may
 * cause problems with shortest prefix matching otherwise.
 *
 *	AT_FOLLOWING
 *
 * This is the type of an option with one following argument.  The procedure
 * will be called with the option that was selected, the error closure, the
 * option closure, and the argument to the option.
 *
 *	AT_EMPTY
 *
 * This is the type of an option with no argument.  The procedure will be
 * called with the option that was selected, the error closure, and the option
 * closure.
 *
 *	AT_FOLLOWING2
 *
 * This is the type of an option with two following arguments.  The procedure
 * will be called with the option that was selected, the error closure, the
 * option closure, and the arguments to the option.
 *
 *	AT_FOLLOWING3
 *
 * This is the type of an option with three following arguments.  The
 * procedure will be called with the option that was selected, the error
 * closure, the option closure, and the arguments to the option.
 *
 * Note that if a matched option is a short option, then the current position
 * is passed to the option handling procedure as the option name.  For long
 * options, the entire option string is passed.  If the handler is interested
 * in the option name, it should check the start of this string: if it is '-'
 * or '+' it should be a long option; otherwise it should be a short option.
 */
typedef enum {
	AT_SWITCH,
	AT_NEG_SWITCH,
	AT_PROC_SWITCH,
	AT_IMMEDIATE,
	AT_EITHER,
	AT_FOLLOWING,
	AT_EMPTY,
	AT_FOLLOWING2,
	AT_FOLLOWING3
} ArgTypeT;

struct ArgListT;

/*
 * This is the type of argument to be passed to ``write_arg_usage''.
 */
typedef struct ArgUsageT {
    const char *			usage;
    struct ArgListT	       *arg_list;
} ArgUsageT;

/*
 * This is the type of a procedure to be called to parse a complex option.
 * Because of union initialisation problems, the latter arguments of this
 * function are untyped.
 */
typedef void(*ArgProcP)(char *, ArgUsageT *, void *, ...);

/*
 * This is the type of an entry in an option list.  A vector of such entries
 * should be passed to the ``arg_parse_arguments'' function, with the last
 * entry being the ``ARG_PARSE_END_LIST'' macro.  Each entry has the following
 * fields: a name field (the name of the option without the leading '--' or
 * '++'), a short name field (a character), a type field (the type of the
 * option), a procedure field (the procedure to handle the option), a closure
 * field (a pointer to some arbritary data used by the procedure), and a
 * description field (the name of a named string that describes how the option
 * is used - see the file "error.h" for more information on named strings).
 * The description field should be surrounded by braces for union initialisation.
 * The named strings used in the description fields
 * should themselves be interned before the ``arg_parse_arguments'' function
 * is called.  A typical argument list definition would be something like the
 * following:
 *
 *	static ArgListT arg_list [] = {
 *	    {
 *		"option name", 'o', AT_PROC_SWITCH, (ArgProcP) arg_proc,
 *		NULL,
 *		{ "option description name" }
 *	    }, ARG_PARSE_END_LIST
 *	};
 *
 * If an option has only a short form, then the name should be NULL;
 * if it has only a long form, then the character should be '\0'.  It is
 * illegal for an option to have neither a long form or a short form.
 */
typedef struct ArgListT {
    char *			name;
    char			short_name;
    ArgTypeT			type;
    ArgProcP			proc;
    void *			closure;
    union {
	char *		name;
	EStringT *	message;
    } u;
} ArgListT;

/*
 * Exceptions:	XX_dalloc_no_memory, XX_error_redefined_string
 *
 * This function should be called on all option lists that the program uses,
 * before they are passed to ``arg_parse_arguments''.  It replaces the
 * descrption name with the named string it represents.  It should only be
 * called once on each list.  The named strings used should be interned before
 * this function is called.
 */
extern void			arg_parse_intern_descriptions
(ArgListT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function does the argument parsing.  The arg_list argument should
 * specify the valid options for the program.  The usage estring should be a
 * named string, whose content is a summary of the program's usage.  The argc
 * and argv arguments should specify the actual arguments passed to the
 * program.  The parsing starts from the first argument, so the first element
 * of the program's argument list (the program name) should not be passed to
 * this function.  The function returns the number of elements of the list
 * that it parsed.
 */
extern int			arg_parse_arguments
(ArgListT *, EStringT *, int, char **);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function can be used to write out a usage message based upon the usage
 * information supplied.
 */
extern void			write_arg_usage
(OStreamT *, ArgUsageT *);

/*
 * This macro should be used to terminate an option list.
 */
#define ARG_PARSE_END_LIST \
{NULL, '\0',(ArgTypeT)0, NULL, NULL, \
 { NULL } }

#endif /* !defined (H_ARG_PARSE) */
