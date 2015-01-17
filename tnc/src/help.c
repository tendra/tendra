/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "help.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


boolean func_help = 0;


static void
help_args(char *str, boolean num)
{
    char c;
    boolean started = 0;
    while (c = *str, c != 0 && c != ']') {
	if (func_help && started)IGNORE putchar(',');
	switch (c) {

	    case '[':
	    case '{':
	    case '}':
	    case '&':
	    case '^':
	    case '|': {
		/* Ignore these cases */
		break;
	    }

	    case 'i': {
		/* Numbers or identifiers */
		if (num) {
		    IGNORE printf(" number");
		} else {
		    IGNORE printf(" identifier");
		}
		break;
	    }

	    case 'j': {
		/* Ignore bits */
		break;
	    }

	    case '$': {
		/* Strings */
		IGNORE printf(" tdfstring");
		break;
	    }

	    case '*': {
		/* Repeated arguments */
		str += 2;
		help_args(str, 0);
		if (func_help) {
		    IGNORE printf(", ...,");
		} else {
		    IGNORE printf(" ...");
		}
		help_args(str, 0);
		str = skip_text(str);
		break;
	    }

	    case '?': {
		/* Optional arguments */
		str += 2;
		IGNORE printf(" [");
		help_args(str, 0);
		IGNORE printf(" ]");
		str = skip_text(str);
		break;
	    }

	    case '@': {
		/* Conditional arguments */
		str += 2;
		help_args(str, 0);
		str = skip_text(str);
		break;
	    }

	    case '!': {
		/* Token applications */
		if (func_help) {
		    IGNORE printf(" identifier ( arg, ..., arg )");
		} else {
		    IGNORE printf(" ( identifier arg ... arg )");
		}
		break;
	    }

	    case 'F': {
		is_fatal = 0;
		input_error("Foreign sorts not supported");
		break;
	    }

	    default : {
		sortname s = find_sort(c);
		IGNORE printf(" %s", sort_name(s));
		break;
	    }
	}
	if (c != 'j')started = 1;
	str++;
    }
    return;
}


static void
output_help(construct *p)
{
    char *args = get_char_info(p);
    IGNORE printf((func_help ? "%s" : "( %s"), p->name);
    if (args) {
	boolean num = 0;
	if ((p->sortnum == SORT_nat && p->encoding == ENC_make_nat) ||
	    (p->sortnum == SORT_signed_nat &&
	       p->encoding == ENC_make_signed_nat)) {
	    num = 1;
	}
	if (func_help)IGNORE printf(" (");
	help_args(args, num);
	if (func_help)IGNORE printf(" )");
    }
    if (!func_help)IGNORE printf(" )");
    IGNORE printf(" -> %s\n", sort_name(p->sortnum));
    return;
}


void
help(char *nm)
{
    sortname s;
    construct *p;
    static int sorted = 0;
    func_help = func_input;

    /* Check for "help all" */
    if (strcmp(nm, "all") == 0) {
	for (s = 0; s < SORT_no; s++) {
	    if (s != SORT_sortname) {
		sort_table(cons_hash_tables, s);
		sorted = 1;
		p = cons_hash_tables[hash_size * s];
		if (p) {
		    for (; p; p = p->next)output_help(p);
		    IGNORE printf("\n");
		}
	    }
	}
	return;
    }

    /* Check for "help construct" */
    for (s = 0; s < SORT_no; s++) {
	if (s != SORT_sortname) {
	    p = search_cons_hash(nm, s);
	    if (p) {
		output_help(p);
		return;
	    }
	    if (sorted) {
		p = cons_hash_tables[hash_size * s];
		for (; p; p = p->next) {
		    if (strcmp(nm, p->name) == 0) {
			output_help(p);
			return;
		    }
		}
	    }
	}
    }

    /* Check for "help sort" */
    if (strcmp(nm, "alignment_sort") == 0)
	    nm = "alignment";
    p = search_cons_hash(nm, SORT_sortname);
    if (p) {
	s = (sortname)p->encoding;
	sort_table(cons_hash_tables, s);
	sorted = 1;
	p = cons_hash_tables[hash_size * s];
	for (; p; p = p->next)output_help(p);
	return;
    }

    /* Unknown construct */
    is_fatal = 0;
    input_error("Unknown construct, %s", nm);
    return;
}
