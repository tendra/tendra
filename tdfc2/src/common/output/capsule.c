/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/capsule.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"

#include <utility/option.h>
#include <utility/ustring.h>
#include <utility/system.h>
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/xalloc.h>

#include <parse/char.h>
#include <parse/file.h>
#include <parse/hash.h>

#include <construct/basetype.h>
#include <construct/link.h>

#include <output/bitstream.h>
#include <output/tdf.h>
#include <output/capsule.h>
#include <output/compile.h>
#include <output/diag4.h>
#include <output/encode.h>
#include <output/mangle.h>
#include <output/struct.h>
#include <output/throw.h>
#include <output/tok.h>

#include "hashid_ops.h"
#include "id_ops.h"
#include "off_ops.h"
#include "type_ops.h"


/*
    This table gives the various TDF unit types (token definitions, tag
    declarations etc.).  These are called equations in the TDF linking
    routines.  Each entry consists of an equation name, a couple of
    flags indicating the unit structure, and a list of bitstreams giving
    the units of that type.  The entries correspond to the EQN macros
    defined in capsule.h.
*/

typedef struct {
	const char *name;
	int labels;
	int count;
	LIST(BITSTREAM_P)pres;
	LIST(BITSTREAM_P)units;
} EQN_INFO;

#define NO_EQNS		NULL_list(BITSTREAM_P)

static EQN_INFO eqns[EQN_no] = {
    { LINK_tld_props,       0, 0, NO_EQNS, NO_EQNS },	/* EQN_tld */
    { LINK_version_props,   0, 1, NO_EQNS, NO_EQNS },	/* EQN_versions */
    { LINK_tokdec_props,    0, 1, NO_EQNS, NO_EQNS },	/* EQN_tokdec */
    { LINK_tokdef_props,    1, 1, NO_EQNS, NO_EQNS },	/* EQN_tokdef */
    { LINK_al_tagdef_props, 1, 1, NO_EQNS, NO_EQNS },	/* EQN_aldef */
    { LINK_diag_type_unit,  1, 1, NO_EQNS, NO_EQNS },	/* EQN_diagtype */
    { LINK_tagdec_props,    1, 1, NO_EQNS, NO_EQNS },	/* EQN_tagdec */
    { LINK_diag_unit,       1, 1, NO_EQNS, NO_EQNS },	/* EQN_diagdef */
    { LINK_dg_comp_props,   1, 1, NO_EQNS, NO_EQNS },	/* EQN_dgcomp */
    { LINK_tagdef_props,    1, 1, NO_EQNS, NO_EQNS },	/* EQN_tagdef */
    { LINK_linkinfo_props,  1, 1, NO_EQNS, NO_EQNS }	/* EQN_linkinfo */
};


/*
    This table gives the various TDF linkable entities (tokens, tags etc.).
    These are called variables in the TDF linking routines.  Each entry
    consists of a variable name and a table of capsule level variables
    of that type (the label entry being a dummy).  The entries correspond
    to the VAR macros defined in capsule.h.
*/

typedef struct {
	const char *name;
	ulong no;
	ulong sz;
	int present;
	string *names;
	unsigned char *uses;
	ulong *diags;
} VAR_INFO;

static VAR_INFO vars[VAR_total] = {
	{ LINK_tag,      0, 0, 0, NULL, NULL, NULL },	/* VAR_tag */
	{ LINK_token,    0, 0, 0, NULL, NULL, NULL },	/* VAR_token */
	{ LINK_al_tag,   0, 0, 0, NULL, NULL, NULL },	/* VAR_alignment */
	{ LINK_diag_tag, 0, 0, 0, NULL, NULL, NULL },	/* VAR_diagtag */
	{ LINK_dg_tag,   0, 0, 0, NULL, NULL, NULL },	/* VAR_dgtag */
	{ LINK_label,    0, 0, 0, NULL, NULL, NULL }	/* VAR_label */
};


/*
    This type is used to represent the linkage for a unit.  It records the
    number of each variable type (plus labels) and the mapping of each of
    the external variables in this unit.  It also records a count value
    for the number of items in the unit when this is an explicitly
    created unit.
*/

typedef struct link_tag {
	ulong no[VAR_total];
	ulong no_map[VAR_no];
	ulong *map[VAR_no];
	ulong count;
	int create;
	struct link_tag *next;
} LINKAGE;


/*
    A list of all unit linkages is maintained so that extending a list of
    external variables also extends all the unit linkage maps.
*/

static LINKAGE *all_links = NULL;


/*
    This routine starts a new bitstream ps and associates a linkage unit
    with it.
*/

static void
start_linkage(BITSTREAM **ps, int create)
{
	/* Allocate a linkage unit */
	int i;
	VAR_INFO *var = vars;
	LINKAGE *p = xmalloc(sizeof *p);
	for (i = 0; i < VAR_no; i++) {
		ulong j, n = var->sz;
		if (n) {
			ulong *q = xmalloc_nof(ulong, n);
			for (j = 0; j < n; j++) {
				q[j] = LINK_NONE;
			}
			p->map[i] = q;
		} else {
			p->map[i] = NULL;
		}
		p->no[i] = 0;
		p->no_map[i] = 0;
		var++;
	}
	p->no[VAR_label] = 0;
	p->count = 0;
	p->create = create;
	p->next = all_links;
	all_links = p;

	/* Start the bitstream */
	*ps = start_bitstream(NIL(FILE), p);
	return;
}


/*
    This routine extends the variable linkage table for variable type v.
*/

static void
extend_linkage(int v)
{
	ulong i;
	LINKAGE *q;
	VAR_INFO *var = vars + v;
	ulong m = var->sz;
	ulong n = m + 100;

	/* Extend global linkage table */
	string *s = var->names;
	unsigned char *u = var->uses;
	ulong *d = var->diags;
	s = xrealloc_nof(s, string, n);
	u = xrealloc_nof(u, unsigned char, n);
	if (output_diag && (v == VAR_tag || v == VAR_token)) {
		d = xrealloc_nof(d, ulong, n);
	}
	for (i = m; i < n; i++) {
		s[i] = NULL;
		u[i] = USAGE_NONE;
		if (d) {
			d[i] = LINK_NONE;
		}
	}
	var->sz = n;
	var->names = s;
	var->uses = u;
	var->diags = d;

	/* Extend each unit linkage table */
	for (q = all_links; q != NULL; q = q->next) {
		ulong *r = q->map[v];
		r = xrealloc_nof(r, ulong, n);
		for (i = m; i < n; i++) {
			r[i] = LINK_NONE;
		}
		q->map[v] = r;
	}
	return;
}


/*
    This routine allocates an external (capsule) linkage number for a
    variable of type v with external name s, returning the result.
*/

ulong
capsule_no(string s, int v)
{
	VAR_INFO *var = vars + v;
	ulong n = (var->no) ++;
	if (n >= var->sz) {
		extend_linkage(v);
	}
	var->uses[n] = USAGE_USE;
	var->names[n] = s;
	var->present = 1;
	return n | LINK_EXTERN;
}


/*
    This routine sets the external name for the variable of type v with
    external linkage number n to be the contents of ps, allocating a new
    variable if n is LINK_NONE.  It returns the value of n and assigns
    the old variable name to ps.
*/

ulong
capsule_name(ulong n, string *ps, int v)
{
	string s = *ps;
	if (n == LINK_NONE) {
		n = capsule_no(s, v);
	} else {
		VAR_INFO *var = vars + v;
		ulong m = (n & ~LINK_EXTERN);
		assert(n & LINK_EXTERN);
		*ps = var->names[m];
		var->names[m] = s;
	}
	return n;
}


/*
    This routine allocates an external (capsule) linkage number to the
    identifier id of variable type v.  It returns false if this number
    has already been allocated.  Note that id cannot be made external
    after it has been made internal.
*/

int
capsule_id(IDENTIFIER id, int v)
{
	int r;
	IDENTIFIER lid = DEREF_id(id_alias(id));
	ulong n = DEREF_ulong(id_no(lid));
	if (n == LINK_NONE) {
		/* Not yet given a number */
		string s = mangle_name(lid, v, 0);
		n = capsule_no(s, v);
		COPY_ulong(id_no(lid), n);
		COPY_ulong(id_no(id), n);
		r = 1;
	} else {
		assert(n & LINK_EXTERN);
		r = 0;
	}
	return r;
}


/*
    This routine allocates an internal (unit) linkage number in the unit
    corresponding to bs to the external (capsule) variable number n of
    type v.
*/

ulong
link_no(BITSTREAM *bs, ulong n, int v)
{
	LINKAGE *lnk = (LINKAGE *)bs->link;
	ulong m = (n & ~LINK_EXTERN);
	n = lnk->map[v][m];
	if (n == LINK_NONE) {
		/* Does not have unit number */
		n = (lnk->no[v]) ++;
		lnk->map[v][m] = n;
		(lnk->no_map[v]) ++;
		vars[v].present = 1;
	}
	return n;
}


/*
    This routine allocates an internal (unit) linkage number to the
    identifier id of variable type v within the unit corresponding to bs.
    v can denote a label.  The corresponding number is returned.  Note
    that unless id has previously been made external then it can be
    internal to at most one unit.
*/

ulong
unit_no(BITSTREAM *bs, IDENTIFIER id, int v, int def)
{
	ulong n;
	if (IS_NULL_id(id)) {
		/* Allow anonymous identifiers */
		LINKAGE *lnk = (LINKAGE *)bs->link;
		n = (lnk->no[v]) ++;
		vars[v].present = 1;
	} else {
		IDENTIFIER lid = DEREF_id(id_alias(id));
		n = DEREF_ulong(id_no(lid));
		if (n == LINK_NONE) {
			/* Not yet given a number */
			LINKAGE *lnk = (LINKAGE *)bs->link;
			n = (lnk->no[v]) ++;
			COPY_ulong(id_no(lid), n);
			COPY_ulong(id_no(id), n);
			vars[v].present = 1;
			if (!def) {
				/* Shouldn't happen */
				LOCATION loc;
				DEREF_loc(id_loc(id), loc);
				report(loc, ERR_token_scope(id));
			}
		} else {
			if (n == LINK_TOKDEF) {
				/* Recursively defined token */
				LOCATION loc;
				DEREF_loc(id_loc(id), loc);
				report(loc, ERR_token_recursive(id));
				n = last_params[DUMMY_token];
				COPY_ulong(id_no(id), n);
			}
			if (n & LINK_EXTERN) {
				/* Already has capsule number */
				n = link_no(bs, n, v);
			}
		}
	}
	return n;
}


/*
    This routine clears the identifier linkage for id.
*/

void
clear_no(IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		IDENTIFIER lid = DEREF_id(id_alias(id));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		COPY_dspec(id_storage(id), (ds & ~dspec_done));
		COPY_ulong(id_no(id), LINK_NONE);
		if (!EQ_id(lid, id)) {
			ds = DEREF_dspec(id_storage(lid));
			COPY_dspec(id_storage(lid), (ds & ~dspec_done));
			COPY_ulong(id_no(lid), LINK_NONE);
		}
	}
	return;
}


/*
    This routine sets the diagnostic tag associated with external identifier
    id of type v to be m.
*/

void
set_diag_tag(IDENTIFIER id, int v, ulong m)
{
	ulong n = DEREF_ulong(id_no(id));
	if (n == LINK_NONE) {
		IGNORE capsule_id(id, v);
		CONS_id(id, pending_funcs, pending_funcs);
		n = DEREF_ulong(id_no(id));
	}
	n &= ~LINK_EXTERN;
	assert(vars[v].diags);
	vars[v].diags[n] = m;
	return;
}


/*
    This routine gets the diagnostic tag associated with external identifier
    id of type v.
*/

ulong
get_diag_tag(IDENTIFIER id, int v)
{
	ulong n = DEREF_ulong(id_no(id));
	if (n == LINK_NONE) {
		return LINK_NONE;
	}
	n &= ~LINK_EXTERN;
	assert(vars[v].diags);
	return vars[v].diags[n];
}


/*
    This routine returns the number of labels in the unit corresponding
    to the bitstream bs.
*/

ulong
no_labels(BITSTREAM *bs)
{
	LINKAGE *lnk = (LINKAGE *)bs->link;
	return lnk->no[VAR_label];
}


/*
    This routine records the usage information u for the external variable
    of type v with number n.
*/

void
record_usage(ulong n, int v, unsigned u)
{
	ulong m = (n & ~LINK_EXTERN);
	unsigned char *pw = vars[v].uses + m;
	unsigned w = (unsigned)*pw;
	*pw = (unsigned char)(w | u);
	return;
}


/*
    This routine finds the usage information for the external variable of
    type v with number n.
*/

unsigned
find_usage(ulong n, int v)
{
	ulong m = (n & ~LINK_EXTERN);
	unsigned u = (unsigned)vars[v].uses[m];
	return u;
}


/*
    This routine clears the usage information for the external variable
    of type v with number n.
*/

void
clear_usage(ulong n, int v)
{
	ulong m = (n & ~LINK_EXTERN);
	vars[v].uses[m] = USAGE_NONE;
	return;
}


/*
    This routine increments the linkage counter associated with the
    bitstream bs.  This is used to keep track of the number of tag
    declarations, or similar, within a unit.
*/

void
count_item(BITSTREAM *bs)
{
	LINKAGE *lnk = (LINKAGE *)bs->link;
	(lnk->count)++;
	return;
}


/*
    This routine adds the unit given by the bitstream bs to the list of
    units of type u.  If the associate unit count is zero then the unit
    is not added.
*/

static void
add_unit(int u, BITSTREAM *bs, BITSTREAM *ps)
{
	if (bs) {
		LINKAGE *lnk = (LINKAGE *)bs->link;
		if (lnk == NULL || lnk->count || ps) {
			EQN_INFO *eqn = eqns + u;
			LIST(BITSTREAM_P)us = eqn->units;
			LIST(BITSTREAM_P)vs = eqn->pres;
			CONS_bits(bs, us, us);
			CONS_bits(ps, vs, vs);
			eqn->units = us;
			eqn->pres = vs;
		}
	}
	return;
}


/*
    These bitstreams represent standard units within the TDF capsule.
*/

BITSTREAM *tokdec_unit = NULL;
BITSTREAM *tokdef_unit = NULL;
BITSTREAM *aldef_unit = NULL;
BITSTREAM *tagdec_unit = NULL;
BITSTREAM *tagdef_unit = NULL;
BITSTREAM *linkinfo_unit = NULL;
BITSTREAM *diagdef_unit = NULL;
BITSTREAM *diagtype_unit = NULL;
BITSTREAM *diagcomp_unit = NULL;
static BITSTREAM *diagcomp_pre = NULL;
static int written_capsule = 0;


/*
    These bitstreams are used to build up the bodies of the dynamic
    initialisation and termination functions.  A count of the number
    of statements in each is maintained.
*/

BITSTREAM *init_func = NULL;
BITSTREAM *term_func = NULL;
BITSTREAM *term_static_func = NULL;
ulong init_no = 0;
ulong term_no = 0;


/*
    This routine creates a linker information unit containing just a tld
    version number.  The usage information for the external variables is
    added at a subsequent stage.
*/

static BITSTREAM *
make_tld_unit(void)
{
	BITSTREAM *bs = start_bitstream(NIL(FILE), NULL_gen_ptr);
	ENC_INT(bs, 1);
	return bs;
}


/*
    This routine creates a versions unit containing a single version
    which gives the TDF version number.
*/

static BITSTREAM *
make_version_unit(void)
{
	BITSTREAM *bs;
	start_linkage(&bs, 1);
	ENC_make_version(bs);
	bs = enc_version(bs);
	count_item(bs);
	if (output_all) {
		/* Output compiler version number */
		string vers = tdfc2_report_version(0);
		ENC_user_info(bs);
		ENC_make_string(bs);
		bs = enc_ustring(bs, vers);
		count_item(bs);
	}
	return bs;
}


/*
    This routine creates or completes all the units comprising the TDF
    capsule.
*/

static void
make_capsule_units(void)
{
	BITSTREAM *bs;
	init_diag();
	bs = make_version_unit();
	add_unit(EQN_versions, bs, NIL(BITSTREAM));
	enc_dynamic_init();
	add_unit(EQN_tokdec, tokdec_unit, NIL(BITSTREAM));
	add_unit(EQN_tokdef, tokdef_unit, NIL(BITSTREAM));
	add_unit(EQN_aldef, aldef_unit, NIL(BITSTREAM));
	add_unit(EQN_diagtype, diagtype_unit, NIL(BITSTREAM));
	add_unit(EQN_tagdec, tagdec_unit, NIL(BITSTREAM));
	add_unit(EQN_diagdef, diagdef_unit, NIL(BITSTREAM));
	add_unit(EQN_dgcomp, diagcomp_unit, diagcomp_pre);
	add_unit(EQN_tagdef, tagdef_unit, NIL(BITSTREAM));
	add_unit(EQN_linkinfo, linkinfo_unit, NIL(BITSTREAM));
	return;
}


/*
    This routine writes the external name s to the bitstream bs.  Spaces
    are used to designate the components of unique identifiers.
*/

static BITSTREAM *
enc_name(BITSTREAM *bs, string s, int v)
{
	string t = s;
	unsigned u = 0;
	unsigned long n;
	for (;;) {
		t = ustrchr(t, ' ');
		u++;
		if (t == NULL) {
			break;
		}
		t++;
	}
	if (u == 1) {
		/* Simple identifiers */
		n = (unsigned long)ustrlen(s);
		if (v == VAR_tag && n > mangle_length) {
			n = mangle_length;
		}
		ENC_string_extern(bs);
		ENC_ALIGN(bs);
		ENC_IDENT(bs, s, n);
	} else {
		/* Unique identifiers */
		ENC_unique_extern(bs);
		ENC_ALIGN(bs);
		ENC_SLIST(bs, u);
		for (;;) {
			t = ustrchr(s, ' ');
			if (t == NULL) {
				n = (unsigned long)ustrlen(s);
				ENC_IDENT(bs, s, n);
				break;
			}
			n = (unsigned long)(t - s);
			ENC_IDENT(bs, s, n);
			s = t + 1;
		}
	}
	return bs;
}


/*
    This routine writes the main body of the output TDF capsule to the
    bitstream bs.
*/

static BITSTREAM *
write_capsule_body(BITSTREAM *bs)
{
	int i, j;
	EQN_INFO *eqn;
	VAR_INFO *var;
	ulong no_eqns = 0;
	ulong no_vars = 0;
	BITSTREAM *ts, *to;

	/* Call capsule construction routines */
	make_capsule_units();

	/* Count the number of variables */
	var = vars;
	for (i = 0; i < VAR_no; i++) {
		if (var->present) {
			no_vars++;
		}
		var++;
	}

	/* Construct linker information unit */
	if (no_vars) {
		ts = make_tld_unit();
		add_unit(EQN_tld, ts, NIL(BITSTREAM));
	} else {
		ts = NULL;
	}
	to = ts;

	/* Count the number of equations */
	eqn = eqns;
	for (i = 0; i < EQN_no; i++) {
		if (!IS_NULL_list(eqn->units)) {
			no_eqns++;
		}
		eqn++;
	}

	/* Output the equation names */
	eqn = eqns;
	ENC_SLIST(bs, no_eqns);
	for (i = 0; i < EQN_no; i++) {
		if (!IS_NULL_list(eqn->units)) {
			string s = ustrlit(eqn->name);
			ENC_IDENT(bs, s, ustrlen(s));
		}
		eqn++;
	}

	/* Output the variable names and numbers */
	var = vars;
	ENC_SLIST(bs, no_vars);
	for (i = 0; i < VAR_no; i++) {
		if (var->present) {
			string s = ustrlit(var->name);
			ENC_IDENT(bs, s, ustrlen(s));
			ENC_INT(bs, var->no);
		}
		var++;
	}

	/* Output the external variable identifiers */
	var = vars;
	ENC_SLIST(bs, no_vars);
	for (i = 0; i < VAR_no; i++) {
		if (var->present) {
			ulong no_ext = 0;
			ulong k, n = var->no;
			string *names = var->names;
			unsigned char *uses = var->uses;
			for (k = 0; k < n; k++) {
				string s = names[k];
				unsigned use = (unsigned)uses[k];
				if (use != USAGE_NONE) {
					const char *msg;
					if (s) {
						/* Count number of external
						 * names */
						no_ext++;
					} else {
						if (!(use & USAGE_DEFN)) {
							/* Undefined internal object */
							if ((use & USAGE_DECL) && i == VAR_dgtag) {
								/* Diagnostic tags can just be declared */
								use |= USAGE_DEFN;
							} else {
								msg = "'%s %lu' used but not defined";
								error(ERR_INTERNAL, msg, var->name, k);
								use |= USAGE_DECL;
								names[k] = mangle_anon();
								no_ext++;
							}
							uses[k] = (unsigned char)use;
						}
					}
					if (i == VAR_tag && !(use & USAGE_DECL)) {
						/* Undeclared tag */
						if (s) {
							msg = "'%s' used but not declared";
							error(ERR_INTERNAL, msg, strlit(s));
						} else {
							msg = "'%s %lu' used but not declared";
							error(ERR_INTERNAL, msg, var->name, k);
						}
					}
				} else {
					names[k] = NULL;
				}
			}
			ENC_SLIST(bs, no_ext);
			for (k = 0; k < n; k++) {
				string s = names[k];
				if (s) {
					unsigned use = (unsigned)uses[k];
					if (use & USAGE_COMMON) {
						/* Common subsumes defined */
						if (use & USAGE_DEFN) {
							use &= ~USAGE_DEFN;
						} else {
							use &= ~USAGE_COMMON;
						}
					}
					ENC_INT(ts, use);
					ENC_INT(bs, k);
					bs = enc_name(bs, s, i);
				}
			}
		}
		var++;
	}

	/* Update linker information unit */
	if (ts != to) {
		LIST(BITSTREAM_P)u = eqns[EQN_tld].units;
		u = END_list(u);
		COPY_bits(HEAD_list(u), ts);
	}

	/* Output the equation units */
	eqn = eqns;
	ENC_SLIST(bs, no_eqns);
	for (i = 0; i < EQN_no; i++) {
		int labels = eqn->labels;
		int count = eqn->count;
		LIST(BITSTREAM_P)u = eqn->units;
		if (!IS_NULL_list(u)) {
			/* Output list of units */
			LIST(BITSTREAM_P)v = eqn->pres;
			unsigned no_units = LENGTH_list(u);
			if (no_units > 1) {
				u = REVERSE_list(u);
				eqn->units = u;
			}
			ENC_SLIST(bs, no_units);
			while (!IS_NULL_list(u)) {
				unsigned ub;
				BITSTREAM *us = DEREF_bits(HEAD_list(u));
				BITSTREAM *vs = DEREF_bits(HEAD_list(v));
				void *plnk = us->link;

				/* Output linkage information */
				if (plnk) {
					/* Output numbers of local variables */
					LINKAGE *lnk = (LINKAGE *)plnk;
					var = vars;
					ENC_SLIST(bs, no_vars);
					for (j = 0; j < VAR_no; j++) {
						if (var->present) {
							ulong nj = lnk->no[j];
							ENC_INT(bs, nj);
						}
						var++;
					}

					/* Output links for local variables */
					ENC_SLIST(bs, no_vars);
					var = vars;
					for (j = 0; j < VAR_no; j++) {
						if (var->present) {
							ulong k, n = vars[j].no;
							ulong *map = lnk->map[j];
							ulong no_map = lnk->no_map[j];
							ENC_SLIST(bs, no_map);
							for (k = 0; k < n; k++) {
								ulong nk = map[k];
								if (nk != LINK_NONE) {
									ENC_INT(bs, nk);
									ENC_INT(bs, k);
								}
							}
						}
						var++;
					}

					/* Add extra information to unit */
					if (lnk->create && (labels || count || vs)) {
						BITSTREAM *ws;
						ws = start_bitstream(NIL(FILE), plnk);
						if (labels) {
							/* Number of labels */
							ulong no_labs = lnk->no[VAR_label];
							ENC_INT(ws, no_labs);
						}
						ws = join_bitstreams(ws, vs);
						if (count) {
							/* Number of items */
							ulong no_item = lnk->count;
							ENC_SLIST(ws, no_item);
						}
						us = join_bitstreams(ws, us);
					}

				} else {
					/* No linkage information */
					ENC_SLIST_SMALL(bs, 0);
					ENC_SLIST_SMALL(bs, 0);
				}

				/* Add unit bitstream to capsule */
				ENC_ALIGN(us);
				ub = length_bitstream(us);
				ENC_LENGTH(bs,(ub / BYTE_SIZE));
				ENC_ALIGN(bs);
				bs = join_bitstreams(bs, us);
				v = TAIL_list(v);
				u = TAIL_list(u);
			}
		}
		eqn++;
	}
	return bs;
}


/*
    At the start of each function definition the associated class type
    and the identifier corresponding to the this parameter are recorded
    in these variables.
*/

CLASS_TYPE last_class = NULL_ctype;
ulong last_params[DUMMY_max];
int last_conts[DUMMY_max];


/*
    This routine clears the function information above.
*/

void
clear_params(void)
{
	int n;
	for (n = 0; n < DUMMY_max; n++) {
		last_params[n] = LINK_NONE;
		last_conts[n] = 0;
	}
	return;
}


/*
    This routine initialises the TDF capsule output routines.
*/

void
init_capsule(void)
{
	if (output_capsule) {
		/* Initialise capsule units */
		HASHID nm;
		void *lnk;
		if (output_tokdec || output_all) {
			start_linkage(&tokdec_unit, 1);
			output_tokdec = 1;
		}
		start_linkage(&tokdef_unit, 1);
		start_linkage(&aldef_unit, 1);
		start_linkage(&tagdec_unit, 1);
		start_linkage(&tagdef_unit, 1);
		start_linkage(&linkinfo_unit, 1);
		if (output_diag) {
			start_linkage(&diagdef_unit, 1);
			start_linkage(&diagtype_unit, 1);
			start_linkage(&diagcomp_unit, 1);
			output_inline = 0;
			output_unused = 1;
		}
		written_capsule = 0;

		/* Initialise special functions */
		clear_params();
		lnk = tagdef_unit->link;
		init_func = start_bitstream(NIL(FILE), lnk);
		term_func = start_bitstream(NIL(FILE), lnk);
		term_static_func = start_bitstream(NIL(FILE), lnk);
		init_no = 0;
		term_no = 0;

		/* Initialise dummy types */
		MAKE_type_compound(cv_none, NULL_ctype, dummy_class);
		MAKE_type_ptr(cv_none, dummy_class, ptr_dummy_class);
		MAKE_type_dummy(cv_none, TOK_destr_type, dummy_count);
		MAKE_type_dummy(cv_none, TOK_vtab_type, dummy_vtab);
		MAKE_type_ptr(cv_none, dummy_vtab, ptr_dummy_vtab);
		MAKE_type_func(cv_none, type_sint, NULL_list(TYPE), 0,
			       cv_lang, NULL_list(TYPE), NULL_nspace,
			       NULL_list(IDENTIFIER), NULL_list(TYPE),
			       dummy_func);
		MAKE_off_type(type_size_t, off_size_t);
		nm = lookup_anon();
		dummy_type_name = DEREF_id(hashid_id(nm));
	}
	return;
}


/*
    This routine is called at the start of each input file to initialise
    the diagnostic routines.
*/

void
init_diag(void)
{
#if TDF_DIAG4
	if (output_capsule && output_diag >= 2) {
		BITSTREAM *bs = diagcomp_pre;
		if (bs == NULL) {
			bs = start_bitstream(NIL(FILE), diagcomp_unit->link);
			bs = enc_dg_compilation(bs);
			diagcomp_pre = bs;
			output_new_diag = output_diag;
		}
	}
#endif
	return;
}


/*
    The flag output_capsule can be set to false to suppress TDF output.
    The other flags inhibit the output of other optional features.
*/

int output_tdf      = 1;
int output_capsule  = 1;
int output_all      = 0;
int output_bugs     = 0;
int output_builtin  = 0;
int output_date     = 1;
int output_diag     = 0;
int output_except   = 1;
int output_init     = 0;
int output_inline   = 0;
int output_new_diag = 0;
int output_order    = 0;
int output_partial  = 1;
int output_rtti     = 1;
int output_shared   = 1;
int output_std      = 0;
int output_term     = 0;
int output_tokdec   = 0;
int output_unused   = 1;
int output_virtual  = 0;


/*
    This routine processes the TDF output options given by opt.  This
    corresponds to the command-line option '-jopt'.
*/

void
output_option(string opt)
{
	int out = 1;
	character c;
	while (c = *(opt++), c != 0) {
		switch (c) {
		case 'a': output_all       = out; break;
		case 'b': output_bugs      = out; break;
		case 'c': output_capsule   = out; break;
		case 'd': output_term      = out; break;
		case 'e': output_except    = out; break;
		case 'f': mangle_signature = out; break;
		case 'h': output_builtin   = out; break;
		case 'i': output_init      = out; break;
		case 'j': output_inline    = out; break;
		case 'l': output_std       = out; break;
		case 'm': output_date      = out; break;
		case 'n': mangle_objects   = out; break;
		case 'o': output_order     = out; break;
		case 'p': output_partial   = out; break;
		case 'r': output_rtti      = out; break;
		case 's': output_shared    = out; break;
		case 't': output_tokdec    = out; break;
		case 'u': output_unused    = out; break;
		case 'v': output_virtual   = out; break;

		case 'g': output_diag = (DIAG_VERSION * out); break;

		case '+': out = 1; break;
		case '-': out = 0; break;

		default:
			/* Unknown output options */
			error(ERR_WARN, "Unknown output option, '%c'", (int)c);
			break;
		}
	}
	return;
}


/*
    This routine adds the TDF version number to the bitstream bs, making
    adjustments to the minor version number if the extensions they
    represent are not used.
*/

BITSTREAM *
enc_version(BITSTREAM *bs)
{
	int v = TDF_minor;
#if (TDF_major == 4 && TDF_minor == 1)
	if (!output_new_diag) {
		v = 0;
	}
#endif
	ENC_INT(bs, TDF_major);
	ENC_INT(bs, v);
	return bs;
}


/*
    This routine outputs the TDF capsule built up by the parsing and
    construction routines.
*/

void
write_capsule(void)
{
	if (output_tdf && !written_capsule) {
		/* Open the output file */
		FILE *f;
		BITSTREAM *bs;
		written_capsule = 1;
		if (!open_output(OUTPUT_TDF, binary_mode)) {
			string nm = output_name[OUTPUT_TDF];
			fail(ERR_fail_output(nm));
			term_error(0);
			return;
		}
		f = output_file[OUTPUT_TDF];
		bs = start_bitstream(f, NULL_gen_ptr);

		/* Encode the magic number (4.0 and later) */
		assert(TDF_VERSION == 100 * TDF_major + TDF_minor);
#if (TDF_major >= 4)
		ENC_BITS(bs, 8, ascii_T);
		ENC_BITS(bs, 8, ascii_D);
		ENC_BITS(bs, 8, ascii_F);
		ENC_BITS(bs, 8, ascii_C);
		bs = enc_version(bs);
		ENC_ALIGN(bs);
#endif

		/* Encode the main capsule body */
		if (output_capsule) {
			bs = write_capsule_body(bs);
		} else {
			ENC_SLIST_SMALL(bs, 0);
			ENC_SLIST_SMALL(bs, 0);
			ENC_SLIST_SMALL(bs, 0);
			ENC_SLIST_SMALL(bs, 0);
		}
		end_bitstream(bs, 1);
		close_output(OUTPUT_TDF);
	}
	return;
}
