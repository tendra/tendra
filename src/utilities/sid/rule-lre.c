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


/*** rule-lre.c --- Left recursion elimination routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID left recursion elimination routines.
 *
 * The generic cycle detection functions defined in the file ``rule.c'' are
 * used to find left cycles in the grammar (this is done by the function
 * ``grammar_remove_left_recursion'' in the file "grammar.c").  If the
 * functions find any such cycles, the function ``rule_remove_left_cycle'' is
 * called on the group of productions to remove the left recursion.  Left
 * recursion is transformed into right recursion in the manner described
 * below.
 *
 * Given a set of productions, expressed as
 *
 *	Ai = Aj Bji, Ci;
 *
 * this can be transformed into
 *
 *	Ai  = Cj Xji;
 *	Xij = Yij, Bik Xkj;
 *
 * Where the rules "Xij" are generated automatically, and Yij is the identity
 * operation if i = j, or an error otherwise.  The generated rule has the same
 * parameters and results, which are the results of "Ai" augmented with those
 * parameters of "Ai" that are used by "Bji".
 *
 * In order for the transform to work, all of the "Ai" must have the same
 * parameter and result types, and the same exception handler.  Also, the
 * initial call to "Aj" must take exactly the formals of "Ai" as parameters.
 * This is checked by the ``rule_check_cycle_types'' function, which also
 * ensures that names are consistent throughout all of the rules.  The
 * transform is performed by the function ``rule_left_cycle_general_case''.
 *
 * In addition to the general case, two special cases are looked for.  The
 * first of these transforms:
 *
 *	A = A B, $;
 *
 * into
 *
 *	A = B A, $;
 *
 * whilst the second transforms:
 *
 *	A = A C B, B;
 *
 * into
 *
 *	A = B X;
 *	X = C A;
 *
 * These special cases are handled by the ``rule_left_cycle_special_case''
 * function.
 *
 *** Change Log:
 * $Log: rule-lre.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/02/10  16:29:42  smf
 * Fixed bugs "CR95_111.sid-inline-no-var-check" and "CR95_112.sid-lre-var-call".
 *
 * Revision 1.2  1994/12/15  09:58:41  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:39  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "rule.h"
#include "dstring.h"
#include "gen-errors.h"

/*--------------------------------------------------------------------------*/

typedef struct MatrixEntryT {
    AltP			alt;
    BoolT			inited;
    TypeTupleT			param;
} MatrixEntryT, *MatrixEntryP;

typedef struct VectorEntryT {
    BoolT			empty_alt;
    AltP			alt;
    BoolT			inited;
    TypeTupleT			param;
} VectorEntryT, *VectorEntryP;

/*--------------------------------------------------------------------------*/

static MatrixEntryP
rule_left_cycle_matrix PROTO_N ((size))
		       PROTO_T (unsigned size)
{
    static MatrixEntryP array      = NIL (MatrixEntryP);
    static unsigned     array_size = 0;
    unsigned            i;

    if (size > array_size) {
	DEALLOCATE (array);
	array      = ALLOCATE_VECTOR (MatrixEntryT, size);
	array_size = size;
    }
    for (i = 0; i < size; i ++) {
	array [i].alt    = NIL (AltP);
	array [i].inited = FALSE;
    }
    return (array);
}

static VectorEntryP
rule_left_cycle_vector PROTO_N ((size))
		       PROTO_T (unsigned size)
{
    static VectorEntryP array      = NIL (VectorEntryP);
    static unsigned     array_size = 0;
    unsigned            i;

    if (size > array_size) {
	DEALLOCATE (array);
	array      = ALLOCATE_VECTOR (VectorEntryT, size);
	array_size = size;
    }
    for (i = 0; i < size; i ++) {
	array [i].empty_alt = FALSE;
	array [i].alt       = NIL (AltP);
	array [i].inited    = FALSE;
    }
    return (array);
}

static void
rule_destroy_cycle_matrix PROTO_N ((matrix, size))
			  PROTO_T (MatrixEntryP matrix X
				   unsigned     size)
{
    unsigned i;

    for (i = 0; i < size; i ++) {
	if (matrix [i].inited) {
	    AltP alt = matrix [i].alt;

	    while (alt) {
		alt = alt_deallocate (alt);
	    }
	    types_destroy (&(matrix [i].param));
	}
    }
}

static void
rule_destroy_cycle_vector PROTO_N ((vector, size))
			  PROTO_T (VectorEntryP vector X
				   unsigned     size)
{
    unsigned i;

    for (i = 0; i < size; i ++) {
	if (vector [i].inited) {
	    AltP alt = vector [i].alt;

	    while (alt) {
		alt = alt_deallocate (alt);
	    }
	    types_destroy (&(vector [i].param));
	}
    }
}

/*--------------------------------------------------------------------------*/

static ItemP
rule_find_suffix PROTO_N ((rec_item, non_rec_item))
		 PROTO_T (ItemP rec_item X
			  ItemP non_rec_item)
{
    ItemP    tmp_rec_item     = rec_item;
    ItemP    tmp_non_rec_item = non_rec_item;
    unsigned diff             = 0;

    while (tmp_rec_item && tmp_non_rec_item) {
	tmp_rec_item     = item_next (tmp_rec_item);
	tmp_non_rec_item = item_next (tmp_non_rec_item);
    }
    while (tmp_rec_item) {
	diff ++;
	tmp_rec_item = item_next (tmp_rec_item);
    }
    if (diff == 0) {
	return (NIL (ItemP));
    }
    do {
	rec_item = item_next (rec_item);
    } while (-- diff);
    tmp_rec_item     = rec_item;
    tmp_non_rec_item = non_rec_item;
    while (tmp_rec_item && tmp_non_rec_item) {
	if (item_entry (tmp_rec_item) != item_entry (tmp_non_rec_item)) {
	    return (NIL (ItemP));
	}
	tmp_rec_item     = item_next (tmp_rec_item);
	tmp_non_rec_item = item_next (tmp_non_rec_item);
    }
    ASSERT ((tmp_rec_item == NIL (ItemP)) &&
	    (tmp_non_rec_item == NIL (ItemP)));
    return (rec_item);
}

static void
rule_renumber_item_list PROTO_N ((item, translator))
			PROTO_T (ItemP       item X
				 TypeNTransP translator)
{
    ntrans_init (translator);
    for (; item; item = item_next (item)) {
	types_renumber (item_param (item), translator);
	types_renumber (item_result (item), translator);
    }
}

static BoolT
rule_compare_item_lists PROTO_N ((rec_suffix, non_rec_item))
			PROTO_T (ItemP rec_suffix X
				 ItemP non_rec_item)
{
    while (rec_suffix) {
	ASSERT (non_rec_item);
	if (!((types_equal_numbers (item_param (rec_suffix),
				    item_param (non_rec_item))) &&
	      (types_equal_numbers (item_result (rec_suffix),
				    item_result (non_rec_item))))) {
	    return (FALSE);
	}
	rec_suffix   = item_next (rec_suffix);
	non_rec_item = item_next (non_rec_item);
    }
    ASSERT (non_rec_item == NIL (ItemP));
    return (TRUE);
}

static void
rule_left_cycle_special_case_2 PROTO_N ((rule, table, non_rec_alt, rec_alt,
					 param, rec_suffix))
			       PROTO_T (RuleP      rule X
					TableP     table X
					AltP       non_rec_alt X
					AltP       rec_alt X
					TypeTupleP param X
					ItemP      rec_suffix)
{
    EntryP      entry    = table_add_generated_rule (table, TRUE);
    RuleP       new_rule = entry_get_rule (entry);
    ItemP       new_item = item_create (entry);
    ItemP       rec_item = alt_unlink_item_head (rec_alt);
    AltP        new_alt  = alt_create ();
    AltP        handler;
    ItemP       item;
    TypeBTransT tmp_trans;
    TypeTupleT  result;

    rule_reinit (rule);
    alt_set_next (non_rec_alt, NIL (AltP));
    btrans_init (&tmp_trans);
    types_copy (&result, rule_result (rule));
    btrans_generate_names (&tmp_trans, &result, table);
    types_translate (&result, &tmp_trans);
    if ((handler = rule_get_handler (rule)) != NIL (AltP)) {
	ItemP handler_items = alt_item_head (handler);

	item_translate_list (handler_items, &tmp_trans);
    }
    btrans_destroy (&tmp_trans);
    types_assign (item_param (new_item), rule_result (rule));
    types_copy (item_result (new_item), &result);
    types_copy (rule_result (rule), &result);
    alt_add_item (non_rec_alt, new_item);
    rule_add_alt (rule, non_rec_alt);
    types_copy (rule_param (new_rule), item_result (rec_item));
    types_copy (rule_result (new_rule), &result);
    (void) item_deallocate (rec_item);
    while (item = alt_item_head (rec_alt), item != rec_suffix) {
	alt_add_item (new_alt, alt_unlink_item_head (rec_alt));
    }
    (void) alt_deallocate (rec_alt);
    new_item = item_create (rule_entry (rule));
    if (param) {
	types_assign (item_param (new_item), param);
    } else {
	types_copy (item_param (new_item), rule_param (new_rule));
    }
    types_assign (item_result (new_item), &result);
    alt_add_item (new_alt, new_item);
    rule_add_alt (new_rule, new_alt);
    if (types_equal_zero_tuple (rule_param (new_rule))) {
	rule_add_empty_alt (new_rule);
    } else {
	new_alt  = alt_create ();
	new_item = item_create (table_add_rename (table));
	types_copy (item_param (new_item), rule_param (new_rule));
	types_copy (item_result (new_item), rule_result (new_rule));
	alt_add_item (new_alt, new_item);
	rule_add_alt (new_rule, new_alt);
    }
}

static BoolT
rule_left_cycle_special_case_1 PROTO_N ((rule, table))
			       PROTO_T (RuleP  rule X
					TableP table)
{
    AltP        rec_alt = rule_alt_head (rule);
    AltP        non_rec_alt;
    ItemP       rec_item;
    ItemP       rec_next;
    ItemP       rec_suffix;
    ItemP       non_rec_item;
    TypeTupleT  param;
    TypeNTransT rec_translator;
    TypeNTransT non_rec_translator;

    if (((non_rec_alt = alt_next (rec_alt)) == NIL (AltP)) ||
	(alt_next (non_rec_alt))) {
	return (FALSE);
    }
    if ((item_is_rule (non_rec_item = alt_item_head (non_rec_alt))) &&
	(entry_get_rule (item_entry (non_rec_item)) == rule)) {
	non_rec_alt  = rec_alt;
	rec_alt      = alt_next (rec_alt);
	non_rec_item = alt_item_head (non_rec_alt);
    }
    if ((item_is_rule (non_rec_item)) &&
	(entry_get_rule (item_entry (non_rec_item)) == rule)) {
	return (FALSE);
    }
    rec_item = alt_item_head (rec_alt);
    if (!((types_equal_names (rule_param (rule), item_param (rec_item))) &&
	  (types_equal (rule_param (rule), rule_result (rule))))) {
	return (FALSE);
    }
    rec_next = item_next (rec_item);
    if (item_names_used_in_list (rec_next, rule_param (rule))) {
	return (FALSE);
    }
    if ((rec_suffix = rule_find_suffix (rec_item, non_rec_item)) ==
	NIL (ItemP)) {
	return (FALSE);
    }
    if ((rec_suffix != rec_next) &&
	(item_names_used_in_list (rec_suffix, item_result (rec_item)))) {
	return (FALSE);
    }
    rule_renumber_item_list (non_rec_item, &non_rec_translator);
    rule_renumber_item_list (rec_suffix, &rec_translator);
    if (!rule_compare_item_lists (rec_suffix, non_rec_item)) {
	ntrans_destroy (&non_rec_translator);
	ntrans_destroy (&rec_translator);
	return (FALSE);
    }
    if (rec_suffix == rec_next) {
	ntrans_destroy (&non_rec_translator);
	ntrans_destroy (&rec_translator);
	rule_left_cycle_special_case_2 (rule, table, non_rec_alt, rec_alt,
					NIL (TypeTupleP), rec_suffix);
    } else {
	types_compute_param_from_trans (&param, &non_rec_translator,
					&rec_translator, rule_param (rule));
	ntrans_destroy (&non_rec_translator);
	ntrans_destroy (&rec_translator);
	rule_left_cycle_special_case_2 (rule, table, non_rec_alt, rec_alt,
					&param, rec_suffix);
    }
    return (TRUE);
}

static BoolT
rule_left_cycle_special_case PROTO_N ((rule, table))
			     PROTO_T (RuleP  rule X
				      TableP table)
{
    if (rule_has_empty_alt (rule)) {
	AltP  alt = rule_alt_head (rule);
	ItemP item;

	if ((alt == NIL (AltP)) || (alt_next (alt) != NIL (AltP))) {
	    return (FALSE);
	}
	item = alt_unlink_item_head (alt);
	alt_add_item (alt, item);
	return (TRUE);
    } else {
	return (rule_left_cycle_special_case_1 (rule, table));
    }
}

/*--------------------------------------------------------------------------*/

static BoolT
rule_check_non_locals PROTO_N ((this_rule, rule_list, real_size))
		      PROTO_T (RuleP    this_rule X
			       RuleP    rule_list X
			       unsigned real_size)
{
    NStringP scope  = rule_maximum_scope (this_rule);
    unsigned length = nstring_length (scope);
    RuleP    rule;

    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
	KeyP key = entry_key (rule_entry (rule));

	if ((rule != this_rule) && key_is_string (key)) {
	    NStringP string = key_get_string (key);

	    if (!(nstring_is_prefix (string, scope) ||
		  (nstring_is_prefix (scope, string) &&
		   ((nstring_length (string) + 2) == length)))) {
		E_out_of_scope_non_local (this_rule, rule, rule_list);
		return (FALSE);
	    }
	}
    }
    if (non_local_list_is_empty (rule_non_locals (this_rule)) ||
	(real_size == 1)) {
	return (TRUE);
    } else {
	E_left_recursion_nl_entry (this_rule, rule_list);
	return (FALSE);
    }
}

static BoolT
rule_check_alt_cycle_types PROTO_N ((rule, rule_list, alt, need_check,
				     translator1, translator2, table,
				     generate_ref))
			   PROTO_T (RuleP       rule X
				    RuleP       rule_list X
				    AltP        alt X
				    BoolT       need_check X
				    TypeBTransP translator1 X
				    TypeBTransP translator2 X
				    TableP      table X
				    BoolP       generate_ref)
{
    ItemP item = alt_item_head (alt);

    item_translate_list (item, translator1);
    if (item_is_rule (item)) {
	RuleP item_rule = entry_get_rule (item_entry (item));

	if (rule_get_cycle_index (item_rule) != 0) {
	    TypeTupleT result_intersect;

	    if (need_check && (!types_equal_names (rule_param (rule),
						   item_param (item)))) {
		btrans_destroy (translator1);
		btrans_destroy (translator2);
		E_left_recursion_name_mismatch (rule_list);
		return (FALSE);
	    }
/* If a result identifier is returned by the left recursive call, it is
 * necessary to rename that return value, and use an identity afterwards to
 * rename it.
 **/
	    types_init (&result_intersect);
	    types_compute_intersection (&result_intersect, rule_result (rule),
					item_result (item));
	    if (!types_equal_zero_tuple (&result_intersect)) {
		EntryP      new_entry = table_add_rename (table);
		ItemP       new_item  = item_create (new_entry);
		TypeBTransT tmp_trans;
		TypeTupleT  tmp_tuple;

		btrans_init (&tmp_trans);
		types_copy (&tmp_tuple, &result_intersect);
		btrans_generate_names (&tmp_trans, &tmp_tuple, table);
		types_translate (&tmp_tuple, &tmp_trans);
		types_translate (item_result (item), &tmp_trans);
		btrans_destroy (&tmp_trans);
		types_assign (item_param (new_item), &tmp_tuple);
		types_assign (item_result (new_item), &result_intersect);
		item_set_next (new_item, item_next (item));
		item_set_next (item, new_item);
	    } else {
		types_destroy (&result_intersect);
	    }
	    if (*generate_ref) {
		btrans_generate_names (translator2, item_result (item),
				       table);
		*generate_ref = FALSE;
	    } else {
		btrans_regenerate_names (translator2, item_result (item));
	    }
	    types_translate (item_result (item), translator2);
	    item_translate_list (item_next (item), translator2);
	}
    }
    return (TRUE);
}

static BoolT
rule_check_cycle_types PROTO_N ((rule_list, predicate_id, real_size, table))
		       PROTO_T (RuleP    rule_list X
				EntryP   predicate_id X
				unsigned real_size X
				TableP   table)
{
    TypeTupleP  param    = rule_param (rule_list);
    TypeTupleP  result   = rule_result (rule_list);
    AltP        handler  = rule_get_handler (rule_list);
    BoolT       generate = TRUE;
    RuleP       rule;
    TypeBTransT translator1;
    TypeBTransT translator2;

    rule_renumber (rule_list, TRUE, predicate_id);
    if (!rule_check_non_locals (rule_list, rule_list, real_size)) {
	return (FALSE);
    }
    for (rule = rule_get_next_in_reverse_dfs (rule_list); rule;
	 rule = rule_get_next_in_reverse_dfs (rule)) {
	if (!((types_equal (param, rule_param (rule))) &&
	      (types_equal (result, rule_result (rule))))) {
	    E_left_recursion_type_mismatch (rule_list);
	    return (FALSE);
	}
	rule_renumber (rule, TRUE, predicate_id);
	if (!alt_equal (handler, rule_get_handler (rule))) {
	    E_left_rec_handler_mismatch (rule_list);
	    return (FALSE);
	}
	if (!rule_check_non_locals (rule, rule_list, real_size)) {
	    return (FALSE);
	}
    }
    btrans_init (&translator1);
    btrans_init (&translator2);
    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
	AltP alt;

	if (rule == rule_list) {
	    btrans_generate_names (&translator1, rule_param (rule), table);
	} else {
	    btrans_regenerate_names (&translator1, rule_param (rule));
	}
	types_translate (rule_param (rule), &translator1);
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
	    (void) rule_check_alt_cycle_types (rule, rule_list, alt, FALSE,
					       &translator1, &translator2,
					       table, &generate);
	}
	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	    if (!rule_check_alt_cycle_types (rule, rule_list, alt, TRUE,
					     &translator1, &translator2, table,
					     &generate)) {
		return (FALSE);
	    }
	}
    }
    btrans_destroy (&translator1);
    btrans_destroy (&translator2);
    return (TRUE);
}

static void
rule_compute_param_subset PROTO_N ((rule_list, subset))
			  PROTO_T (RuleP      rule_list X
				   TypeTupleP subset)
{
    RuleP rule;

    types_init (subset);
    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
	TypeTupleP param = rule_param (rule);
	AltP       alt;

	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	    ItemP item = alt_item_head (alt);

	    if (item_is_rule (item)) {
		RuleP item_rule = entry_get_rule (item_entry (item));

		if (rule_get_cycle_index (item_rule) != 0) {
		    for (item = item_next (item); item;
			 item = item_next (item)) {
			types_compute_intersection (subset, param,
						    item_param (item));
		    }
		}
	    }
	}
    }
}

static void
rule_left_cycle_general_case_1 PROTO_N ((rule_list, size, matrix, vector,
					 table, gen_param, gen_result))
			       PROTO_T (RuleP        rule_list X
					unsigned     size X
					MatrixEntryP matrix X
					VectorEntryP vector X
					TableP       table X
					TypeTupleP   gen_param X
					TypeTupleP   gen_result)
{
    unsigned    i               = 0;
    BoolT       generate        = TRUE;
    BoolT       generate_param  = TRUE;
    BoolT       generate_result = TRUE;
    RuleP       rule;
    TypeBTransT translator;
    TypeBTransT tmp_trans;
    TypeTupleT  dummy;
    TypeTupleT  param_subset;

    btrans_init (&translator);
    rule_compute_param_subset (rule_list, &param_subset);
    btrans_init (&tmp_trans);
    types_copy (&dummy, &param_subset);
    btrans_generate_names (&tmp_trans, &dummy, table);
    types_translate (&dummy, &tmp_trans);
    btrans_destroy (&tmp_trans);
    for (rule = rule_list; rule;
	 rule = rule_get_next_in_reverse_dfs (rule), i ++) {
	AltP       alt = rule_alt_head (rule);
	AltP       handler;
	TypeTupleT old_result;

	types_copy (&old_result, rule_result (rule));
	if (generate) {
	    btrans_generate_names (&translator, rule_result (rule), table);
	    generate = FALSE;
	} else {
	    btrans_regenerate_names (&translator, rule_result (rule));
	}
	types_translate (rule_result (rule), &translator);
	if ((handler = rule_get_handler (rule)) != NIL (AltP)) {
	    ItemP handler_items = alt_item_head (handler);

	    item_translate_list (handler_items, &translator);
	}
	if (rule_has_empty_alt (rule)) {
	    vector [i].empty_alt = TRUE;
	}
	while (alt) {
	    ItemP    item    = alt_item_head (alt);
	    AltP     tmp_alt = alt;
	    RuleP    item_rule;
	    unsigned item_index;

	    alt = alt_next (alt);
	    if ((item_is_rule (item)) &&
		((item_rule = entry_get_rule (item_entry (item))),
		 ((item_index = rule_get_cycle_index (item_rule)) != 0))) {
		unsigned matrix_index = (size * (item_index - 1) + i);

		if (!(matrix [matrix_index].inited)) {
		    TypeTupleP param = &(matrix [matrix_index].param);

		    types_copy (param, &param_subset);
		    types_append_copy (param, &old_result);
		    matrix [matrix_index].inited = TRUE;
		}
		if (generate_param) {
		    ItemP item_head = alt_item_head (tmp_alt);

		    types_copy (gen_param, &param_subset);
		    types_append_copy (gen_param, item_result (item_head));
		    generate_param = FALSE;
		}
		(void) item_deallocate (alt_unlink_item_head (tmp_alt));
		alt_set_next (tmp_alt, matrix [matrix_index].alt);
		matrix [matrix_index].alt = tmp_alt;
	    } else {
		if (!(vector [i].inited)) {
		    TypeTupleP param = &(vector [i].param);

		    types_copy (param, &param_subset);
		    types_append_copy (param, &old_result);
		    vector [i].inited = TRUE;
		}
		if (generate_result) {
		    types_copy (gen_result, &dummy);
		    types_append_copy (gen_result, rule_result (rule));
		    generate_result = FALSE;
		}
		alt_set_next (tmp_alt, vector [i].alt);
		vector [i].alt = tmp_alt;
	    }
	}
	rule_reinit (rule);
	types_destroy (&old_result);
    }
    types_destroy (&param_subset);
    btrans_destroy (&translator);
}

static BoolT
rule_left_cycle_general_case_2 PROTO_N ((rule_list, size, vector))
			       PROTO_T (RuleP        rule_list X
					unsigned     size X
					VectorEntryP vector)
{
    BoolT    not_found = TRUE;
    unsigned i;

    for (i = 0; i < size; i ++) {
	if ((vector [i].empty_alt) || (vector [i].alt)) {
	    not_found = FALSE;
	}
    }
    if (not_found) {
	E_cycle_no_terminator (rule_list);
	return (FALSE);
    }
    return (TRUE);
}

static void
rule_left_cycle_general_case_3 PROTO_N ((rule, size, vector, table,
					 new_rule_list_tail, param, result))
			       PROTO_T (RuleP        rule X
					unsigned     size X
					VectorEntryP vector X
					TableP       table X
					RuleP       *new_rule_list_tail X
					TypeTupleP   param X
					TypeTupleP   result)
{
    unsigned j;

    for (j = 0; j < size; j ++) {
	EntryP entry    = table_add_generated_rule (table, TRUE);
	RuleP  new_rule = entry_get_rule (entry);
	AltP   alt;

	types_copy (rule_param (new_rule), param);
	types_copy (rule_result (new_rule), result);
	*new_rule_list_tail = new_rule;
	new_rule_list_tail  = rule_next_in_reverse_dfs_ref (new_rule);
	if (vector [j].empty_alt) {
	    AltP  new_alt  = alt_create ();
	    ItemP new_item = item_create (entry);

	    types_copy (item_param (new_item), &(vector [j].param));
	    types_copy (item_result (new_item), result);
	    alt_add_item (new_alt, new_item);
	    rule_add_alt (rule, new_alt);
	}
	for (alt = vector [j].alt; alt; alt = alt_next (alt)) {
	    AltP  new_alt  = alt_duplicate (alt);
	    ItemP new_item = item_create (entry);

	    types_copy (item_param (new_item), &(vector [j].param));
	    types_copy (item_result (new_item), result);
	    alt_add_item (new_alt, new_item);
	    rule_add_alt (rule, new_alt);
	}
    }
}

static void
rule_left_cycle_general_case_4 PROTO_N ((new_rule_list, i, size, matrix,
					 table))
			       PROTO_T (RuleP        new_rule_list X
					unsigned     i X
					unsigned     size X
					MatrixEntryP matrix X
					TableP       table)
{
    unsigned j;
    RuleP    rule;

    for (rule = new_rule_list, j = 0; j < size;
	 rule = rule_get_next_in_reverse_dfs (rule), j ++) {
	RuleP    inner_rule;
	unsigned k = 0;

	if (i == j) {
	    if (types_equal_zero_tuple (rule_param (rule))) {
		rule_add_empty_alt (rule);
	    } else {
		AltP   new_alt  = alt_create ();
		EntryP entry    = table_add_rename (table);
		ItemP  new_item = item_create (entry);

		types_copy (item_param (new_item), rule_param (rule));
		types_copy (item_result (new_item), rule_result (rule));
		alt_add_item (new_alt, new_item);
		rule_add_alt (rule, new_alt);
	    }
	}
	for (inner_rule = new_rule_list; inner_rule;
	     inner_rule = rule_get_next_in_reverse_dfs (inner_rule), k ++) {
	    AltP alt;

	    for (alt = matrix [k].alt; alt; alt = alt_next (alt)) {
		AltP  new_alt  = alt_duplicate (alt);
		ItemP new_item = item_create (rule_entry (inner_rule));

		types_copy (item_param (new_item), &(matrix [k].param));
		types_copy (item_result (new_item), rule_result (rule));
		alt_add_item (new_alt, new_item);
		rule_add_alt (rule, new_alt);
	    }
	}
    }
}

static void
rule_left_cycle_general_case PROTO_N ((rule_list, size, table))
			     PROTO_T (RuleP    rule_list X
				      unsigned size X
				      TableP   table)
{
    unsigned     matrix_size = (size * size);
    MatrixEntryP matrix      = rule_left_cycle_matrix (matrix_size);
    VectorEntryP vector      = rule_left_cycle_vector (size);
    TypeTupleT   param;
    TypeTupleT   result;

    rule_left_cycle_general_case_1 (rule_list, size, matrix, vector, table,
				    &param, &result);
    if (rule_left_cycle_general_case_2 (rule_list, size, vector)) {
	unsigned i = 0;
	RuleP    rule;

	for (rule = rule_list; rule;
	     rule = rule_get_next_in_reverse_dfs (rule), i ++) {
	    RuleP new_rule_list;

	    rule_left_cycle_general_case_3 (rule, size, vector, table,
					    &new_rule_list, &param, &result);
	    rule_left_cycle_general_case_4 (new_rule_list, i, size, matrix,
					    table);
	}
    }
    types_destroy (&param);
    types_destroy (&result);
    rule_destroy_cycle_matrix (matrix, matrix_size);
    rule_destroy_cycle_vector (vector, size);
}

/*--------------------------------------------------------------------------*/

void
rule_remove_left_cycle PROTO_N ((rule_list, predicate_id, table))
		       PROTO_T (RuleP  rule_list X
				EntryP predicate_id X
				TableP table)
{
    unsigned size      = 0;
    unsigned real_size = 0;
    RuleP    rule;

    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
	size ++;
	if (key_is_string (entry_key (rule_entry (rule)))) {
	    real_size ++;
	}
	rule_set_cycle_index (rule, size);
    }
    if (((size != 1) || (!rule_left_cycle_special_case (rule_list, table))) &&
	(rule_check_cycle_types (rule_list, predicate_id, real_size, table))) {
	rule_left_cycle_general_case (rule_list, size, table);
    }
    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
	rule_reset_cycle_index (rule);
	rule_no_cycles (rule);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
