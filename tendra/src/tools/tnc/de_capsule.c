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
#include "fmm.h"
#include "msgcat.h"

#include "types.h"
#include "de_types.h"
#include "de_unit.h"
#include "decode.h"
#include "fetch.h"
#include "names.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
 *    FLAG : DECODE STATUS
 *
 *    A value of 0 indicates that we are decoding the names at the start
 *    of the capsule, 1 that we are decoding the linkage information, and
 *    2 that we are decoding a main equation body.
 */

int decode_status = -1;


/*
 *    FLAG : ONLY DECODE TOKEN DECLARATIONS
 *
 *    This flag is true if we are only interested in the token
 *    declarations in a capsule.
 */

boolean extract_tokdecs = 0;


/*
 *    THE ARRAY OF ALL VARIABLE SORTS
 *
 *    The array vars of size no_var gives all variable sorts.  The
 *    indexes in this array of the alignment tags, tags and tokens are
 *    given by al_tag_var, tag_var, tok_var respectively.
 */

static long no_var;
static var_sort *vars;
long al_tag_var, tag_var, tok_var;


/*
 *    LIST OF UNUSED CONSTRUCTS
 *
 *    All unused constructs in a capsule are formed into a list for
 *    later reuse.
 */

static construct *garbage = null;


/*
 *    CURRENT BINDINGS
 *
 *    The current bindings are held in crt_binding.  spare_binding, if not
 *    null, contains a binding suitable for reuse.
 */

binding *crt_binding;
static binding *spare_binding = null;


/*
 *    CREATE A NEW BINDING
 *
 *    A new binding with space for no_var variable sorts is created and
 *    cleared.
 */

static binding
*new_binding()
{
    binding *b;
    long i, n = no_var;
    if (n == 0) return (null);
    if (spare_binding) {
		b = spare_binding;
		spare_binding = null;
		for (i = 0 ; i < n ; i++) b [i].max_no = 0;
		return (b);
    }
    b = xalloc (sizeof (*b) * n);
    for (i = 0 ; i < n ; i++) {
		b [i].max_no = 0;
		b [i].sz = 0;
		b [i].table = null;
    }
    return (b);
}


/*
 *    FREE A BINDING
 *
 *    The binding b is returned to free.
 */

static void
free_binding(binding *b)
{
    spare_binding = b;
    return;
}


/*
 *    SET THE SIZE OF AN ENTRY IN A BINDING
 *
 *    The size of the table of the vth variable sort in the binding bt
 *    is set to n.
 */

static void
set_binding_size(binding *bt, long v, long n)
{
    binding *b;
    construct **p;
    long i, m = n + 10;
    if (v < 0 || v >= no_var)
		MSG_FATAL_illegal_binding_sort ();
    b = bt + v;
    b->max_no = n;
    if (b->sz < m) {
		p = xrealloc (b->table, sizeof (construct *) * m);
		b->sz = m;
		b->table = p;
    } else {
		p = b->table;
    }
    for (i = 0 ; i < b->sz ; i++) p [i] = null;
    return;
}


/*
 *    COMPLETE A BINDING
 *
 *    The unused entries in the binding b are filled in.
 */

static void
complete_binding(binding *b)
{
    long v;
    for (v = 0 ; v < no_var ; v++) {
		long i;
		binding *bv = b + v;
		sortname s = vars [v].sortnum;
		for (i = 0 ; i < bv->max_no ; i++) {
			if (bv->table [i] == null) {
				construct *p = make_construct (s);
				if (extract_tokdecs) {
					/* This construct is unused - free it */
					(sort_count [s])--;
					p->next = garbage;
					garbage = p;
				} else {
					/* Make up an internal name */
					long n = p->encoding;
					char *nm = xalloc (32);
					IGNORE sprintf (nm, "~~%s_%ld", vars [v].name, n);
					p->name = nm;
					if (add_to_var_hash (p, s))
						MSG_FATAL_var_already_defined (nm);
				}
				bv->table [i] = p;
			}
		}
    }
    return;
}


/*
 *    SET AN ENTRY IN A BINDING
 *
 *    The nth entry of the vth variable sort of the binding bt is set to
 *    the construct p.
 */

static void
set_binding(binding *bt, long v, long n, construct *p)
{
    binding *b;
    if (v < 0 || v >= no_var)
		MSG_FATAL_illegal_binding_sort ();
    b = bt + v;
    if (n >= b->max_no || n < 0)
		MSG_FATAL_object_number_too_big (n, vars [v].name);
    if (b->table [n])
		MSG_FATAL_object_already_bound (n, vars [v].name);
    b->table [n] = p;
    return;
}


/*
 *    FIND AN ENTRY IN A BINDING
 *
 *    The nth entry of the vth variable sort of the binding bt is returned.
 */

construct
*find_binding(binding *bt, long v, long n)
{
    binding *b;
    if (v < 0 || v >= no_var)
		MSG_FATAL_illegal_binding_sort ();
    b = bt + v;
    if (n >= b->max_no || n < 0)
		MSG_FATAL_object_number_too_big (n, vars [v].name);
    return (b->table [n]);
}


/*
 *    DECODE AN ALIGNED STRING
 *
 *    An aligned string (in an external name) is decoded and returned
 *    as an array of characters.
 */

char
*de_aligned_string()
{
    char *p;
    long i, n = tdf_int ();
    if (n != 8) MSG_FATAL_only_8bit_strings_allowed ();
    n = tdf_int ();
    byte_align ();
    p = xalloc (n + 1);
    for (i = 0 ; i < n ; i++) p [i] = (char) fetch (8) /* LINT */;
    p [n] = 0;
    byte_align ();
    return (p);
}


/*
 *    FLAG INDICATING SKIP PASS
 *
 *    This flag is true if we are in the skip pass of a set of equations
 *    (primarily token definitions).
 */

boolean in_skip_pass = 0;


/*
 *    DECODE A SET OF EQUATIONS
 *
 *    A set of equations with decoding routine f is decoded.  If f is null
 *    the equations are stepped over, otherwise they are decoded.
 */

typedef void (*equation_func)(void) ;

static void
de_equation(equation_func f)
{
    long i, n;
    binding *old_binding = null;

    /* Read new bindings */
    n = tdf_int ();
    if (n) {
		if (n != no_var) MSG_FATAL_number_of_local_variables_wrong ();
		old_binding = crt_binding;
		crt_binding = new_binding ();
		for (i = 0 ; i < n ; i++) {
			long sz = tdf_int ();
			set_binding_size (crt_binding, i, sz);
		}
		n = tdf_int ();
		if (n != no_var) MSG_FATAL_number_of_linkage_units_wrong ();
		for (i = 0 ; i < n ; i++) {
			long j, no_links = tdf_int ();
			for (j = 0 ; j < no_links ; j++) {
				long inner = tdf_int ();
				long outer = tdf_int ();
				construct *p = find_binding (old_binding, i, outer);
				set_binding (crt_binding, i, inner, p);
			}
		}
		complete_binding (crt_binding);
    } else {
		n = tdf_int ();
		if (n) MSG_FATAL_number_of_linkage_units_wrong ();
    }

    /* Read the actual equation */
    n = BYTESIZE * tdf_int ();
    byte_align ();
    if (f == null) {
		input_skip (n);
    } else {
		long end_posn = input_posn () + n;
		decode_status = 2;
		(*f) ();
		byte_align ();
		decode_status = 1;
		if (input_posn () != end_posn) MSG_FATAL_unit_length_wrong ();
    }

    /* Restore the old bindings */
    if (old_binding) {
		free_binding (crt_binding);
		crt_binding = old_binding;
    }
    return;
}


/*
 *    DECODE A CAPSULE
 *
 *    An entire TDF capsule is decoded.
 */

void
de_capsule()
{
    long i, n;
    long no_eqn;
    char **eqns;

    /* Reset variables */
    al_tag_var = -1;
    tag_var = -2;
    tok_var = -3;
    spare_binding = null;
    have_version = 0;
    decode_status = 0;

    /* Read magic number */
    de_magic (MAGIC_NUMBER);

    /* Read equation names */
    no_eqn = tdf_int ();
    eqns = xalloc (sizeof (char *) * no_eqn);
    for (i = 0 ; i < no_eqn ; i++) eqns [i] = de_aligned_string ();

    /* Read variable sort names */
    no_var = tdf_int ();
    vars = xalloc (sizeof (var_sort) * no_var);
    crt_binding = new_binding ();
    for (i = 0 ; i < no_var ; i++) {
		char *s = de_aligned_string ();
		long sz = tdf_int ();
		vars [i].name = s;
		if (streq (s, LINK_al_tag)) {
			vars [i].sortnum = SORT_al_tag;
			al_tag_var = i;
		} else if (streq (s, LINK_tag)) {
			vars [i].sortnum = SORT_tag;
			tag_var = i;
		} else if (streq (s, LINK_token)) {
			vars [i].sortnum = SORT_token;
			tok_var = i;
		} else {
			vars [i].sortnum = SORT_unknown;
		}
		set_binding_size (crt_binding, i, sz);
    }

    /* Read external names */
    decode_status = 1;
    n = tdf_int ();
    if (n != no_var) MSG_FATAL_number_of_variable_sorts_wrong ();
    for (i = 0 ; i < no_var ; i++) {
		static int un = 0;
		sortname si = vars [i].sortnum;
		long j, no_links = tdf_int ();
		boolean reject = 0;
		if (extract_tokdecs && i != tok_var) reject = 1;
		for (j = 0 ; j < no_links ; j++) {
			construct *p, *q;
			long id = tdf_int ();
			n = de_external_bits ();
			byte_align ();
			p = make_construct (si);
			if (extract_tokdecs) {
				(sort_count [ si ])--;
				p->encoding = -1;
			}

			if (n == ENC_string_extern) {
				/* Simple external name */
				boolean name_ok = 1;
				node *ns = de_node ("=");
				if (reject) {
					free_node (ns);
				} else {
					/* Check that name is a valid identifier */
					char *nm = ns->cons->name;
					if (alpha (*nm)) {
						long k;
						for (k = 1 ; k < ns->cons->encoding ; k++) {
							char c = nm [k];
							if (!alphanum (c)) name_ok = 0;
						}
					} else {
						name_ok = 0;
					}
					if (name_ok) {
						/* Use external name as internal name */
						p->name = nm;
						if (!is_local_name (nm)) {
							p->ename = new_node ();
							p->ename->cons = &false_cons;
						}
					} else {
						/* Make up internal name */
						p->name = xalloc (32);
						IGNORE sprintf (p->name, "~~extern_%d", un++);
						if (!is_local_name (nm)) {
							p->ename = new_node ();
							p->ename->cons = &true_cons;
							p->ename->son = ns;
						}
					}
				}
			} else if (n == ENC_unique_extern) {
				/* Unique external name */
				node *nu = de_node ("%[=]");
				if (reject) {
					free_node (nu);
				} else {
					/* Make up internal name */
					p->name = xalloc (32);
					IGNORE sprintf (p->name, "~~extern_%d", un++);
					p->ename = new_node ();
					p->ename->cons = &true_cons;
					p->ename->son = nu;
				}
			} else if (n == ENC_chain_extern) {
				/* Chain external name */
				node *nc = de_node ("=i");
				if (reject) {
					free_node (nc);
				} else {
					/* Make up internal name */
					p->name = xalloc (32);
					IGNORE sprintf (p->name, "~~extern_%d", un++);
					p->ename = new_node ();
					p->ename->cons = &true_cons;
					p->ename->son = nc;
				}
			} else {
				MSG_FATAL_illegal_EXTERN_value (n);
			}

			/* Add construct to tables */
			if (reject) {
				set_binding (crt_binding, i, id, p);
				p->next = garbage;
				garbage = p;
			} else {
				q = add_to_var_hash (p, si);
				if (q) {
					if (!extract_tokdecs) {
						(sort_count [ si ])--;
						if (q->encoding == -1) {
							q->encoding = (sort_count [ si ])++;
						}
					}
					set_binding (crt_binding, i, id, q);
					p->next = garbage;
					garbage = p;
				} else {
					set_binding (crt_binding, i, id, p);
				}
			}
		}
    }

    /* Complete the bindings */
    complete_binding (crt_binding);

    /* Read the equations */
    n = tdf_int ();
    if (n != no_eqn) MSG_FATAL_number_of_equations_wrong ();
    for (i = 0 ; i < no_eqn ; i++) {
		char *eq = eqns [i];
		long j, no_units = tdf_int ();
		if (no_units) {
			boolean skip_pass = 0;
			equation_func f = null;

			/* Find equation decoding routine */
			if (extract_tokdecs) {
				if (streq (eq, LINK_tokdec_props)) {
					f = de_tokdec;
				} else if (streq (eq, LINK_tokdef_props)) {
					f = de_tokdef;
					in_skip_pass = 1;
				}
			} else {
				if (streq (eq, LINK_al_tagdef_props)) {
					f = de_aldef;
				} else if (streq (eq, LINK_tagdec_props)) {
					f = de_tagdec;
				} else if (streq (eq, LINK_tagdef_props)) {
					f = de_tagdef;
				} else if (streq (eq, LINK_tokdec_props)) {
					f = de_tokdec;
				} else if (streq (eq, LINK_tokdef_props)) {
					f = de_tokdef;
					skip_pass = 1;
				} else if (streq (eq, LINK_version_props)) {
					f = de_version;
				}
			}

			/* Skip pass */
			if (skip_pass) {
				long old_posn = input_posn ();
				in_skip_pass = 1;
				for (j = 0 ; j < no_units ; j++) de_equation (f);
				in_skip_pass = 0;
				input_goto (old_posn);
			}

			/* Main pass */
			for (j = 0 ; j < no_units ; j++) de_equation (f);
			in_skip_pass = 0;
		}
    }

    /* Free unused constructs */
    free_construct (&garbage);
    return;
}


/*
 *    NAME OF CURRENT CAPSULE
 *
 *    The current capsule of a library is recorded to use in error messages.
 */

char *capname = null;


/*
 *    DECODE A TDF LIBRARY
 */

void
de_library()
{
    long old_posn;
    long i, no_cap;
    boolean old_extract = extract_tokdecs;

    de_magic (MAGIC_LINK_NUMBER);
    IGNORE tdf_int ();
    no_cap = tdf_int ();
    old_posn = input_posn ();

    /* First pass - extract all token declaration */
    extract_tokdecs = 1;
    for (i = 0 ; i < no_cap ; i++) {
		long end_posn;
		long j, n;
		decode_status = 0;
		n = tdf_int ();
		if (n != 8) MSG_FATAL_only_8bit_strings_allowed ();
		n = tdf_int ();
		byte_align ();
		capname = xalloc (n + 1);
		for (j = 0 ; j < n ; j++) {
			capname [j] = (char) fetch (8) ; /* LINT */
		}
		capname [n] = 0;
		n = BYTESIZE * tdf_int ();
		byte_align ();
		end_posn = input_posn () + n;
		de_capsule ();
		byte_align ();
		if (input_posn () != end_posn)
			MSG_FATAL_capsule_length_wrong ();
		capname = null;
    }

    /* Second pass - if the first pass didn't do everything */
    extract_tokdecs = old_extract;
    if (extract_tokdecs) return;
    input_goto (old_posn);
    for (i = 0 ; i < no_cap ; i++) {
		long end_posn;
		long j, n;
		decode_status = 0;
		n = tdf_int ();
		if (n != 8) MSG_FATAL_only_8bit_strings_allowed ();
		n = tdf_int ();
		byte_align ();
		capname = xalloc (n + 1);
		for (j = 0 ; j < n ; j++) {
			capname [j] = (char) fetch (8) ; /* LINT */
		}
		capname [n] = 0;
		n = BYTESIZE * tdf_int ();
		byte_align ();
		end_posn = input_posn () + n;
		de_capsule ();
		byte_align ();
		if (input_posn () != end_posn)
			MSG_FATAL_capsule_length_wrong ();
		capname = null;
    }
    return;
}
