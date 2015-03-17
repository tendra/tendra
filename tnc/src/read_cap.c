/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <tdf/magic.h>

#include "config.h"
#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "check.h"
#include "de_types.h"
#include "de_capsule.h"
#include "file.h"
#include "high.h"
#include "names.h"
#include "node.h"
#include "read.h"
#include "read_cap.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    An external name representing an object of sort s is read from the
    input file.  If local is true this must just be an internal identifier.
*/

static construct *
read_external(sortname s, bool local)
{
    construct *p;
    node *e = NULL;
    int estate = 0;
    position store;
    allow_multibyte = 0;

    /* Read identifier */
    store_position(&store);
    read_word();

    /* Check for external name */
    if (func_input) {
	if (word_type == INPUT_WORD) {
	    if (streq(word, MAKE_STRING_EXTERN)) {
		estate = 1;
	    } else if (streq(word, MAKE_UNIQUE_EXTERN)) {
		estate = 2;
	    } else if (streq(word, MAKE_CHAIN_EXTERN)) {
		estate = 3;
	    }
	    if (estate) {
		read_word();
		if (word_type != INPUT_OPEN) {
		    /* Go back and treat as identifier */
		    estate = 0;
		    set_position(&store);
		    read_word();
		}
	    }
	}
    } else {
	if (word_type == INPUT_OPEN) {
	    read_word();
	    if (word_type != INPUT_WORD) {
		input_error("External expected");
		return NULL;
	    }
	    if (streq(word, MAKE_STRING_EXTERN)) {
		estate = 1;
	    } else if (streq(word, MAKE_UNIQUE_EXTERN)) {
		estate = 2;
	    } else if (streq(word, MAKE_CHAIN_EXTERN)) {
		estate = 3;
	    } else {
		input_error("Illegal external, %s", word);
		return NULL;
	    }
	}
    }

    if (estate) {
	/* There is an external name */
	if (local) {
	    is_fatal = 0;
	    input_error("Can't have external name with local");
	}
	e = new_node();
	e->cons = &true_cons;
	if (estate == 1) {
	    e->son = read_node("$");
	} else if (estate == 2) {
	    e->son = read_node("*[$]");
	} else {
	    e->son = read_node("$i");
	}
	read_word();
	if (word_type != INPUT_CLOSE) {
	    is_fatal = 0;
	    input_error("End of external construct expected");
	    looked_ahead = 1;
	}
	read_word();
	if (func_input) {
	    if (word_type != INPUT_COMMA) {
		is_fatal = 0;
		input_error("Comma expected");
		looked_ahead = 1;
	    }
	    read_word();
	}
    } else {
	/* There is no external name */
	if (is_local_name(word))local = 1;
	if (!local) {
	    e = new_node();
	    e->cons = &false_cons;
	}
    }

    /* Check internal name */
    if (word_type != INPUT_WORD)input_error("Identifier expected");
    p = search_var_hash(word, s);
    if (p == NULL) {
	/* New object */
	p = make_construct(s);
	p->name = string_copy_aux(word);
	p->ename = e;
	IGNORE add_to_var_hash(p, s);
    } else {
	/* Existing object : check consistency */
	if (local) {
	    if (p->ename) {
		is_fatal = 0;
		input_error("Object %s previously declared global", word);
	    }
	} else {
	    if (p->ename) {
		if (e->son) {
		    is_fatal = 0;
		    input_error("External name of object %s given twice",
				  word);
		}
	    } else {
		is_fatal = 0;
		input_error("Object %s previously declared local", word);
	    }
	}
    }
    allow_multibyte = 1;
    return p;
}


/*
    An alignment tag declaration is read from the input file.
*/

static void
read_aldec(bool local)
{
    IGNORE read_external(SORT_al_tag, local);
    return;
}


/*
    An alignment tag definition is read from the input file.
*/

static void
read_aldef(bool local)
{
    node *d;
    construct *p = read_external(SORT_al_tag, local);
    al_tag_info *info = get_al_tag_info(p);

    /* Check comma */
    if (func_input) {
	read_word();
	if (word_type != INPUT_COMMA) {
	    is_fatal = 0;
	    input_error("Comma expected");
	    looked_ahead = 1;
	}
    }

    /* Read the definition (an alignment) */
    d = completion(read_node("a"));
    if (info->def) {
	if (!eq_node(info->def, d)) {
	    is_fatal = 0;
	    input_error("Alignment tag %s defined inconsistently",
			  p->name);
	}
	free_node(d);
    } else {
	info->def = d;
    }
    return;
}


/*
    A tag declaration is read from the input file.  Whether it is a
    variable or an identity is indicated by the is_var flag.
*/

static void
read_tagdec(bool local, int is_var)
{
    node *d;
    construct *p = read_external(SORT_tag, local);
    tag_info *info = get_tag_info(p);
    set_tag_type(p, is_var);

    /* Check comma */
    if (func_input) {
	read_word();
	if (word_type != INPUT_COMMA) {
	    is_fatal = 0;
	    input_error("Comma expected");
	    looked_ahead = 1;
	}
    }

    /* Declaration = optional access + optional string + shape from 4.0 */
    d = completion(read_node("?[u]?[X]S"));
    info->var = (bool)is_var;
    if (info->dec) {
	if (!eq_node(info->dec, d)) {
	    is_fatal = 0;
	    input_error("Tag %s declared inconsistently", p->name);
	}
	free_node(d);
    } else {
	info->dec = d;
    }
    return;
}


/*
    A tag definition is read from the input file.  Whether it is a
    variable or an identity is indicated by the is_var flag.
*/

static void
read_tagdef(bool local, int is_var)
{
    node *d;
    construct *p = read_external(SORT_tag, local);
    tag_info *info = get_tag_info(p);

    /* Set the tag type */
    if (info->dec == NULL && !do_check) {
	is_fatal = 0;
	input_error("Tag %s defined but not declared", word);
    }
    set_tag_type(p, is_var);

    /* Check comma */
    if (func_input) {
	read_word();
	if (word_type != INPUT_COMMA) {
	    is_fatal = 0;
	    input_error("Comma expected");
	    looked_ahead = 1;
	}
    }

    /* Definition - signature added in 4.0 */
    d = completion(read_node(is_var ? "?[u]?[X]x" : "?[X]x"));
    info->var = (bool)is_var;
    if (info->def) {
	if (is_var == 2) {
	    node *dp = info->def;
	    while (dp->bro)dp = dp->bro;
	    dp->bro = d;
	} else {
	    if (!eq_node(info->def, d)) {
		is_fatal = 0;
		input_error("Tag %s defined inconsistently", p->name);
	    }
	    free_node(d);
	}
    } else {
	info->def = d;
	if (do_check)check_tagdef(p);
    }
    return;
}


/*
    A sortname is read from the input file.
*/

static sortname
read_sortname(void)
{
    sortname s;
    if (word_type != INPUT_WORD) {
	is_fatal = 0;
	input_error("Sort name expected");
	return SORT_unknown;
    }
    s = find_high_sort(word);
    if (s == SORT_unknown) {
	is_fatal = 0;
	input_error("Illegal sort name, %s", word);
    } else {
	if (s > SORT_max && s < SORT_no) {
	    is_fatal = 0;
	    input_error("Bad sort name, %s", word);
	}
    }
    return s;
}


/*
    A token sort is read and the information is stored in info.  This
    can be a definition (with formal parameters) or a declaration
    (without) depending on the value of def.
*/

static void
read_toksort(tok_info *info, bool def)
{
    /* Check comma */
    if (func_input) {
	read_word();
	if (word_type != INPUT_COMMA) {
	    is_fatal = 0;
	    input_error("Comma expected");
	    looked_ahead = 1;
	}
    }

    /* Initialize values */
    info->res = SORT_unknown;
    info->args = NULL;
    info->pars = NULL;
    info->sig = NULL;

    /* Read signature */
    info->sig = read_node("?[X]");

    /* Read argument sorts */
    read_word();
    if (word_type == INPUT_OPEN) {
	int no_args = 0;
	char arg_buff[100];
	char *a = arg_buff;
	construct *cons_buff[100];
	construct **c = cons_buff;
	while (read_word(), word_type != INPUT_CLOSE) {
	    sortname s = read_sortname();
	    if (is_high(s)) {
		sprint_high_sort(a, s);
		while (*a)a++;
	    } else {
		*(a++) = sort_letters[s];
	    }
	    if (def) {
		/* Read formal argument */
		construct *q;
		read_word();
		if (word_type != INPUT_WORD) {
		    input_error("Token identifier expected");
		}
		q = search_var_hash(word, SORT_token);
		if (q) {
		    input_error("Token %s already declared", word);
		}
		q = make_construct(SORT_token);
		q->name = string_copy_aux(word);
		IGNORE add_to_var_hash(q, SORT_token);
		set_token_sort(q, s, NULL, NULL);
		*(c++) = q;
	    }
	    /* Check comma */
	    if (func_input) {
		read_word();
		if (word_type == INPUT_CLOSE) {
		    looked_ahead = 1;
		} else if (word_type != INPUT_COMMA) {
		    is_fatal = 0;
		    input_error("Comma or close bracket expected");
		    looked_ahead = 1;
		}
	    }
	    no_args++;
	}
	*a = 0;
	if (*arg_buff) {
	    /* Store argument string */
	    info->args = string_copy_aux(arg_buff);
	    if (def) {
		/* Store formal arguments */
		int i, n = no_args;
		info->pars = xmalloc_nof(construct *, n + 1);
		for (i = 0; i < n; i++)info->pars[i] = cons_buff[i];
		info->pars[n] = NULL;
	    }
	}
	read_word();
	if (func_input) {
	    if (word_type != INPUT_ARROW) {
		is_fatal = 0;
		input_error("Arrow (->) expected");
		looked_ahead = 1;
	    }
	    read_word();
	}
    }

    /* Read result sort */
    info->res = read_sortname();
    if (is_high(info->res)) {
	input_error("Tokens cannot return high-level sorts");
    }
    return;
}


/*
    A token declaration is read from the input file.
*/

static void
read_tokdec(bool local)
{
    tok_info store;
    construct *p = read_external(SORT_token, local);
    tok_info *info = get_tok_info(p);

    /* Get token sort */
    adjust_token(p);
    read_toksort(&store, 0);
    info->dec = 1;
    set_token_sort(p, store.res, store.args, store.sig);
    return;
}


/*
    A token definition is read from the input file.
*/

static void
read_tokdef(bool local)
{
    node *d;
    char buff[2];
    tok_info store;
    construct *p = read_external(SORT_token, local);
    tok_info *info = get_tok_info(p);
    construct **old_pars = info->pars;

    /* Get token sort */
    adjust_token(p);
    read_toksort(&store, 1);
    info->dec = 1;
    info->pars = store.pars;
    set_token_sort(p, store.res, store.args, store.sig);

    /* Check comma */
    if (func_input) {
	read_word();
	if (word_type != INPUT_COMMA) {
	    is_fatal = 0;
	    input_error("Comma expected");
	    looked_ahead = 1;
	}
    }

    /* Read the definition */
    buff[0] = sort_letters[store.res];
    buff[1] = 0;
    d = read_node(buff);

    /* Free formal parameters */
    if (info->pars) {
	construct **ps;
	for (ps = info->pars; *ps; ps++) {
	    remove_var_hash((*ps) ->name, SORT_token);
	}
    }

    /* Check consistency */
    d = completion(d);
    if (info->def) {
	if (!eq_node(info->def, d)) {
	    is_fatal = 0;
	    input_error("Token %s defined inconsistently", p->name);
	}
	free_node(d);
	info->pars = old_pars;
    } else {
	info->def = d;
    }
    return;
}


/*
    A token sort defintion is read from the input file.
*/

static void
read_sortdef(bool local)
{
    char *nm;
    tok_info store;

    /* The local quantifier should not be used */
    if (local) {
	is_fatal = 0;
	input_error("Can't have local here");
    }

    /* Read the sort name */
    read_word();
    if (word_type != INPUT_WORD)input_error("Identifier expected");
    nm = string_copy_aux(word);

    /* Get sort definition */
    read_toksort(&store, 0);
    set_high_sort(nm, &store);
    return;
}


/*
    A complete subfile is read.  ftype gives the type of the subfile :
    0 = text, 1 = capsule, 2 = library.  ex is true to indicate that
    only the tokens should be read.
*/

static void
sub_file(int ftype, int ex)
{
    position store;
    bool old_func_input = func_input;
    char *old_name = input_file, *new_name;

    /* Read the file name */
    allow_multibyte = 0;
    read_word();
    allow_multibyte = 1;
    if (word_type != INPUT_STRING) {
	is_fatal = 0;
	input_error("File name expected");
	return;
    }
    new_name = string_copy_aux(word);

    /* Save the position in the existing file */
    store_position(&store);

    /* Read the subfile */
    text_input = (bool)(ftype == 0 ? 1 : 0);
    open_input(new_name, 1);
    if (ftype == 0) {
	read_capsule();
    } else {
	extract_tokdecs = (bool)ex;
	if (ftype == 1) {
	    de_capsule();
	} else {
	    de_library();
	}
	extract_tokdecs = 0;
    }

    /* Restore the position in the old file */
    text_input = 1;
    open_input(old_name, 1);
    set_position(&store);
    func_input = old_func_input;
    return;
}


/*
    A complete capsule is read from the input file.
*/

void
read_capsule(void)
{
    int starter;
    read_word();
    if (word_type == INPUT_OPEN) {
	if (func_input)warning("Switching input form");
	func_input = 0;
	starter = INPUT_OPEN;
    } else {
	if (!func_input)warning("Switching input form");
	func_input = 1;
	starter = INPUT_WORD;
    }
    looked_ahead = 1;

    while (read_word(), word_type == starter) {
	char *cmd;
	char *wtemp;
	bool local = 0;
	if (!func_input) {
	    read_word();
	    if (word_type != INPUT_WORD) {
		input_error("Construct name expected");
	    }
	}

	/* Check for the local qualifier */
	if (streq(word, LOCAL_DECL)) {
	    local = 1;
	    read_word();
	    if (word_type != INPUT_WORD) {
		input_error("Construct name expected");
	    }
	}

	/* For functional input, expect an open bracket */
	if (func_input) {
	    wtemp = temp_copy(word);
	    read_word();
	    if (word_type != INPUT_OPEN) {
		is_fatal = 0;
		input_error("Open bracket expected");
		looked_ahead = 1;
	    }
	} else {
	    wtemp = word;
	}

	/* Macro to aid checking */
#define test_cmd(X, Y)\
	if (streq(wtemp, cmd = (X))) {\
	    Y ;\
	} else

	/* Check on the various possible constructs */
	test_cmd(MAKE_ALDEC, read_aldec(local))
	test_cmd(MAKE_ALDEF, read_aldef(local))
	test_cmd(MAKE_ID_TAGDEC, read_tagdec(local, 0))
	test_cmd(MAKE_VAR_TAGDEC, read_tagdec(local, 1))
	test_cmd(MAKE_ID_TAGDEF, read_tagdef(local, 0))
	test_cmd(MAKE_VAR_TAGDEF, read_tagdef(local, 1))
	test_cmd(MAKE_TOKDEC, read_tokdec(local))
	test_cmd(MAKE_TOKDEF, read_tokdef(local))
	test_cmd(COMMON_TAGDEC, read_tagdec(local, 2))
	test_cmd(COMMON_TAGDEF, read_tagdef(local, 2))
	test_cmd(MAKE_SORT, read_sortdef(local))

	{
	    /* Include constructs */
	    if (local) {
		is_fatal = 0;
		input_error("Can't have local here");
	    }
	    test_cmd(INCLUDE_TEXT, sub_file(0, 0))
	    test_cmd(INCLUDE_CODE, sub_file(1, 0))
	    test_cmd(USE_CODE, sub_file(1, 1))
	    test_cmd(INCLUDE_LIB, sub_file(2, 0))
	    test_cmd(USE_LIB, sub_file(2, 1))
	    {
		/* Illegal construct */
		input_error("Illegal construct name, %s", wtemp);
	    }
	}

	/* End of construct */
	read_word();
	if (word_type != INPUT_CLOSE) {
	    is_fatal = 0;
	    input_error("End of %s construct expected", cmd);
	    looked_ahead = 1;
	}
	if (func_input) {
	    read_word();
	    if (word_type != INPUT_SEMICOLON) {
		is_fatal = 0;
		input_error("End of %s construct expected", cmd);
		looked_ahead = 1;
	    }
	}
    }
    if (word_type != INPUT_EOF) {
	is_fatal = 0;
	input_error("Start of construct expected");
    }
    return;
}
