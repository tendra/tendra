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
#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"

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
 *    READ AN EXTERNAL NAME
 *
 *    An external name representing an object of sort s is read from the
 *    input file.  If local is true this must just be an internal identifier.
 */

static construct
*read_external(sortname s, boolean local)
{
    construct *p;
    node *e = null;
    int estate = 0;
    position store;
    allow_multibyte = 0;

    /* Read identifier */
    store_position (&store);
    read_word ();

    /* Check for external name */
    if (func_input) {
		if (word_type == INPUT_WORD) {
			if (streq (word, MAKE_STRING_EXTERN)) {
				estate = 1;
			} else if (streq (word, MAKE_UNIQUE_EXTERN)) {
				estate = 2;
			} else if (streq (word, MAKE_CHAIN_EXTERN)) {
				estate = 3;
			}
			if (estate) {
				read_word ();
				if (word_type != INPUT_OPEN) {
					/* Go back and treat as identifier */
					estate = 0;
					set_position (&store);
					read_word ();
				}
			}
		}
    } else {
		if (word_type == INPUT_OPEN) {
			read_word ();
			if (word_type != INPUT_WORD)
				MSG_FATAL_external_expected ();
			if (streq (word, MAKE_STRING_EXTERN)) {
				estate = 1;
			} else if (streq (word, MAKE_UNIQUE_EXTERN)) {
				estate = 2;
			} else if (streq (word, MAKE_CHAIN_EXTERN)) {
				estate = 3;
			} else
				MSG_FATAL_illegal_external (word);
		}
    }

    if (estate) {
		/* There is an external name */
		if (local)
			MSG_cant_have_external_name_with_local ();
		e = new_node ();
		e->cons = &true_cons;
		if (estate == 1) {
			e->son = read_node ("$");
		} else if (estate == 2) {
			e->son = read_node ("*[$]");
		} else {
			e->son = read_node ("$i");
		}
		read_word ();
		if (word_type != INPUT_CLOSE) {
			MSG_end_of_external_construct_expected ();
			looked_ahead = 1;
		}
		read_word ();
		if (func_input) {
			if (word_type != INPUT_COMMA) {
				MSG_comma_expected ();
				looked_ahead = 1;
			}
			read_word ();
		}
    } else {
		/* There is no external name */
		if (is_local_name (word)) local = 1;
		if (!local) {
			e = new_node ();
			e->cons = &false_cons;
		}
    }

    /* Check internal name */
    if (word_type != INPUT_WORD) MSG_FATAL_identifier_expected ();
    p = search_var_hash (word, s);
    if (p == null) {
		/* New object */
		p = make_construct (s);
		p->name = string_copy (word);
		p->ename = e;
		IGNORE add_to_var_hash (p, s);
    } else {
		/* Existing object : check consistency */
		if (local) {
			if (p->ename)
				MSG_object_previously_declared_global (word);
		} else {
			if (p->ename) {
				if (e->son)
					MSG_external_name_of_object_given_twice (word);
			} else {
				MSG_object_previously_declared_local (word);
			}
		}
    }
    allow_multibyte = 1;
    return (p);
}


/*
 *    READ AN ALIGNMENT TAG DECLARATION
 *
 *    An alignment tag declaration is read from the input file.
 */

static void
read_aldec(boolean local)
{
    IGNORE read_external (SORT_al_tag, local);
    return;
}


/*
 *    READ AN ALIGNMENT TAG DEFINITION
 *
 *    An alignment tag definition is read from the input file.
 */

static void
read_aldef(boolean local)
{
    node *d;
    construct *p = read_external (SORT_al_tag, local);
    al_tag_info *info = get_al_tag_info (p);

    /* Check comma */
    if (func_input) {
		read_word ();
		if (word_type != INPUT_COMMA) {
			MSG_comma_expected ();
			looked_ahead = 1;
		}
    }

    /* Read the definition (an alignment) */
    d = completion (read_node ("a"));
    if (info->def) {
		if (!eq_node (info->def, d)) {
			MSG_alignment_tag_defined_inconsistently (p->name);
		}
		free_node (d);
    } else {
		info->def = d;
    }
    return;
}


/*
 *    READ A TAG DECLARATION
 *
 *    A tag declaration is read from the input file.  Whether it is a
 *    variable or an identity is indicated by the is_var flag.
 */

static void
read_tagdec(boolean local, int is_var)
{
    node *d;
    construct *p = read_external (SORT_tag, local);
    tag_info *info = get_tag_info (p);
    set_tag_type (p, is_var);

    /* Check comma */
    if (func_input) {
		read_word ();
		if (word_type != INPUT_COMMA) {
			MSG_comma_expected ();
			looked_ahead = 1;
		}
    }

    /* Declaration = optional access + optional string + shape from 4.0 */
    d = completion (read_node ("?[u]?[X]S"));
    info->var = (boolean) is_var;
    if (info->dec) {
		if (!eq_node (info->dec, d))
			MSG_tag_declared_inconsistently (p->name);
		free_node (d);
    } else {
		info->dec = d;
    }
    return;
}


/*
 *    READ A TAG DEFINITION
 *
 *    A tag definition is read from the input file.  Whether it is a
 *    variable or an identity is indicated by the is_var flag.
 */

static void
read_tagdef(boolean local, int is_var)
{
    node *d;
    construct *p = read_external (SORT_tag, local);
    tag_info *info = get_tag_info (p);

    /* Set the tag type */
    if (info->dec == null && !do_check)
		MSG_tag_defined_but_not_declared (word);
    set_tag_type (p, is_var);

    /* Check comma */
    if (func_input) {
		read_word ();
		if (word_type != INPUT_COMMA) {
			MSG_comma_expected ();
			looked_ahead = 1;
		}
    }

    /* Definition - signature added in 4.0 */
    d = completion (read_node (is_var ? "?[u]?[X]x" : "?[X]x"));
    info->var = (boolean) is_var;
    if (info->def) {
		if (is_var == 2) {
			node *dp = info->def;
			while (dp->bro) dp = dp->bro;
			dp->bro = d;
		} else {
			if (!eq_node (info->def, d))
				MSG_tag_defined_inconsistently (p->name);
			free_node (d);
		}
    } else {
		info->def = d;
		if (do_check) check_tagdef (p);
    }
    return;
}


/*
 *    READ A SORTNAME
 *
 *    A sortname is read from the input file.
 */

static sortname
read_sortname()
{
    sortname s;
    if (word_type != INPUT_WORD) {
		MSG_sort_name_expected ();
		return (SORT_unknown);
    }
    s = find_high_sort (word);
    if (s == SORT_unknown) {
		MSG_illegal_sort_name (word);
    } else {
		if (s > SORT_max && s < SORT_no) {
			MSG_bad_sort_name (word);
		}
    }
    return (s);
}


/*
 *    READ TOKEN SORT
 *
 *    A token sort is read and the information is stored in info.  This
 *    can be a definition (with formal parameters) or a declaration
 *    (without) depending on the value of def.
 */

static void
read_toksort(tok_info *info, boolean def)
{
    /* Check comma */
    if (func_input) {
		read_word ();
		if (word_type != INPUT_COMMA) {
			MSG_comma_expected ();
			looked_ahead = 1;
		}
    }

    /* Initialize values */
    info->res = SORT_unknown;
    info->args = null;
    info->pars = null;
    info->sig = null;

    /* Read signature */
    info->sig = read_node ("?[X]");

    /* Read argument sorts */
    read_word ();
    if (word_type == INPUT_OPEN) {
		int no_args = 0;
		char arg_buff [100];
		char *a = arg_buff;
		construct *cons_buff [100];
		construct **c = cons_buff;
		while (read_word (), word_type != INPUT_CLOSE) {
			sortname s = read_sortname ();
			if (is_high (s)) {
				sprint_high_sort (a, s);
				while (*a) a++;
			} else {
				*(a++) = sort_letters [s];
			}
			if (def) {
				/* Read formal argument */
				construct *q;
				read_word ();
				if (word_type != INPUT_WORD)
					MSG_FATAL_token_identifier_expected ();
				q = search_var_hash (word, SORT_token);
				if (q)
					MSG_FATAL_token_already_declared (word);
				q = make_construct (SORT_token);
				q->name = string_copy (word);
				IGNORE add_to_var_hash (q, SORT_token);
				set_token_sort (q, s, (char *) null, (node *) null);
				*(c++) = q;
			}
			/* Check comma */
			if (func_input) {
				read_word ();
				if (word_type == INPUT_CLOSE) {
					looked_ahead = 1;
				} else if (word_type != INPUT_COMMA) {
					MSG_comma_or_close_bracket_expected ();
					looked_ahead = 1;
				}
			}
			no_args++;
		}
		*a = 0;
		if (*arg_buff) {
			/* Store argument string */
			info->args = string_copy (arg_buff);
			if (def) {
				/* Store formal arguments */
				int i, n = no_args;
				info->pars = xalloc (sizeof (construct *) * (n + 1));
				for (i = 0 ; i < n ; i++) info->pars [i] = cons_buff [i];
				info->pars [n] = null;
			}
		}
		read_word ();
		if (func_input) {
			if (word_type != INPUT_ARROW) {
				MSG_arrow_expected ();
				looked_ahead = 1;
			}
			read_word ();
		}
    }

    /* Read result sort */
    info->res = read_sortname ();
    if (is_high (info->res)) {
		MSG_FATAL_tokens_cant_return_high_level_sorts ();
    }
    return;
}


/*
 *    READ A TOKEN DECLARATION
 *
 *    A token declaration is read from the input file.
 */

static void
read_tokdec(boolean local)
{
    tok_info store;
    construct *p = read_external (SORT_token, local);
    tok_info *info = get_tok_info (p);

    /* Get token sort */
    adjust_token (p);
    read_toksort (&store, 0);
    info->dec = 1;
    set_token_sort (p, store.res, store.args, store.sig);
    return;
}


/*
 *    READ A TOKEN DEFINITION
 *
 *    A token definition is read from the input file.
 */

static void
read_tokdef(boolean local)
{
    node *d;
    char buff [2];
    tok_info store;
    construct *p = read_external (SORT_token, local);
    tok_info *info = get_tok_info (p);
    construct **old_pars = info->pars;

    /* Get token sort */
    adjust_token (p);
    read_toksort (&store, 1);
    info->dec = 1;
    info->pars = store.pars;
    set_token_sort (p, store.res, store.args, store.sig);

    /* Check comma */
    if (func_input) {
		read_word ();
		if (word_type != INPUT_COMMA) {
			MSG_comma_expected ();
			looked_ahead = 1;
		}
    }

    /* Read the definition */
    buff [0] = sort_letters [ store.res ];
    buff [1] = 0;
    d = read_node (buff);

    /* Free formal parameters */
    if (info->pars) {
		construct **ps;
		for (ps = info->pars ; *ps ; ps++) {
			remove_var_hash ((*ps)->name, SORT_token);
		}
    }

    /* Check consistency */
    d = completion (d);
    if (info->def) {
		if (!eq_node (info->def, d)) {
			MSG_token_defined_inconsistently (p->name);
		}
		free_node (d);
		info->pars = old_pars;
    } else {
		info->def = d;
    }
    return;
}


/*
 *    READ A TOKEN SORT DEFINITION
 *
 *    A token sort defintion is read from the input file.
 */

static void
read_sortdef(boolean local)
{
    char *nm;
    tok_info store;

    /* The local quantifier should not be used */
    if (local)
		MSG_cant_have_local_here ();

    /* Read the sort name */
    read_word ();
    if (word_type != INPUT_WORD) MSG_FATAL_identifier_expected ();
    nm = string_copy (word);

    /* Get sort definition */
    read_toksort (&store, 0);
    set_high_sort (nm, &store);
    return;
}


/*
 *    READ A SUBFILE
 *
 *    A complete subfile is read.  ftype gives the type of the subfile :
 *    0 = text, 1 = capsule, 2 = library.  ex is true to indicate that
 *    only the tokens should be read.
 */

static void
sub_file(int ftype, int ex)
{
    position store;
    boolean old_func_input = func_input;
    char *old_name = input_file, *new_name;

    /* Read the file name */
    allow_multibyte = 0;
    read_word ();
    allow_multibyte = 1;
    if (word_type != INPUT_STRING) {
		MSG_file_name_expected ();
		return;
    }
    new_name = string_copy (word);

    /* Save the position in the existing file */
    store_position (&store);

    /* Read the subfile */
    text_input = (boolean) (ftype == 0 ? 1 : 0);
    open_input (new_name, 1);
    if (ftype == 0) {
		read_capsule ();
    } else {
		extract_tokdecs = (boolean) ex;
		if (ftype == 1) {
			de_capsule ();
		} else {
			de_library ();
		}
		extract_tokdecs = 0;
    }

    /* Restore the position in the old file */
    text_input = 1;
    open_input (old_name, 1);
    set_position (&store);
    func_input = old_func_input;
    return;
}


/*
 *    READ A CAPSULE
 *
 *    A complete capsule is read from the input file.
 */

void
read_capsule()
{
    int starter;
    read_word ();
    if (word_type == INPUT_OPEN) {
		if (func_input) MSG_switching_input_form ();
		func_input = 0;
		starter = INPUT_OPEN;
    } else {
		if (!func_input) MSG_switching_input_form ();
		func_input = 1;
		starter = INPUT_WORD;
    }
    looked_ahead = 1;

    while (read_word (), word_type == starter) {
		char *cmd;
		char *wtemp;
		boolean local = 0;
		if (!func_input) {
			read_word ();
			if (word_type != INPUT_WORD)
				MSG_FATAL_construct_name_expected ();
		}

		/* Check for the local qualifier */
		if (streq (word, LOCAL_DECL)) {
			local = 1;
			read_word ();
			if (word_type != INPUT_WORD)
				MSG_FATAL_construct_name_expected ();
		}

		/* For functional input, expect an open bracket */
		if (func_input) {
			wtemp = temp_copy (word);
			read_word ();
			if (word_type != INPUT_OPEN) {
				MSG_open_bracket_expected ();
				looked_ahead = 1;
			}
		} else {
			wtemp = word;
		}

		/* Macro to aid checking */
#define test_cmd(X, Y)\
	if (streq (wtemp, cmd = (X))) {\
	    Y ;\
	} else

		/* Check on the various possible constructs */
		test_cmd (MAKE_ALDEC, read_aldec (local))
			test_cmd (MAKE_ALDEF, read_aldef (local))
			test_cmd (MAKE_ID_TAGDEC, read_tagdec (local, 0))
			test_cmd (MAKE_VAR_TAGDEC, read_tagdec (local, 1))
			test_cmd (MAKE_ID_TAGDEF, read_tagdef (local, 0))
			test_cmd (MAKE_VAR_TAGDEF, read_tagdef (local, 1))
			test_cmd (MAKE_TOKDEC, read_tokdec (local))
			test_cmd (MAKE_TOKDEF, read_tokdef (local))
			test_cmd (COMMON_TAGDEC, read_tagdec (local, 2))
			test_cmd (COMMON_TAGDEF, read_tagdef (local, 2))
			test_cmd (MAKE_SORT, read_sortdef (local))

			{
				/* Include constructs */
				if (local)
					MSG_cant_have_local_here ();
				test_cmd (INCLUDE_TEXT, sub_file (0, 0))
					test_cmd (INCLUDE_CODE, sub_file (1, 0))
					test_cmd (USE_CODE, sub_file (1, 1))
					test_cmd (INCLUDE_LIB, sub_file (2, 0))
					test_cmd (USE_LIB, sub_file (2, 1))
					{
						/* Illegal construct */
						MSG_FATAL_illegal_construct_name (wtemp);
					}
			}

		/* End of construct */
		read_word ();
		if (word_type != INPUT_CLOSE) {
			MSG_end_of_construct_expected (cmd);
			looked_ahead = 1;
		}
		if (func_input) {
			read_word ();
			if (word_type != INPUT_SEMICOLON) {
				MSG_end_of_construct_expected (cmd);
				looked_ahead = 1;
			}
		}
    }
    if (word_type != INPUT_EOF)
		MSG_start_of_construct_expected ();
    return;
}
