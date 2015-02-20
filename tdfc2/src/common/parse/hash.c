/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/option.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <syntax/syntax.h>

#include <parse/char.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/symbols.h>

#include <construct/basetype.h>
#include <construct/chktype.h>
#include <construct/namespace.h>
#include <construct/token.h>

#include "ctype_ops.h"
#include "etype_ops.h"
#include "ftype_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "type_ops.h"


/*
    The hash tables consist of an array of hash identifiers, one for each
    hash value.  All the hash table entries with the same hash value are
    chained into a list using their next field.  There are two hash tables,
    one for strings and one for types.
*/

HASHID *hash_table;
static HASHID *hash_type_table;


/*
    This routine calculates the hash value associated with the identifier
    name s.  The main parser routine, read_token, calculates the hash values
    of the identifiers it reads on the fly and stores them in token_hash.
    Therefore any changes to this routine should also be reflected in
    read_token.
*/

unsigned long
hash(string s)
{
	character c;
	unsigned long h = 0;
	while (c = *(s++), c != 0) {
		h = HASH_POWER * h + (unsigned long)c;
	}
	return h % HASH_SIZE;
}


/*
    This routine calculates the hash value associated with the type t.
    This is used in the look-up for the conversion function identifier
    'operator t'.
*/

static unsigned long
hash_type(TYPE t)
{
	unsigned long h = 0;
	while (!IS_NULL_type(t)) {
		unsigned long sub = 0;
		unsigned long tag = (unsigned long)TAG_type(t);
		CV_SPEC qual = DEREF_cv(type_qual(t));
		switch (tag) {
		case type_integer_tag: {
			INT_TYPE it = DEREF_itype(type_integer_rep(t));
			if (IS_itype_basic(it)) {
				BUILTIN_TYPE no =
				    DEREF_ntype(itype_basic_no(it));
				sub = (unsigned long)no;
			}
			t = NULL_type;
			break;
		}
		case type_floating_tag: {
			FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
			if (IS_ftype_basic(ft)) {
				BUILTIN_TYPE no =
				    DEREF_ntype(ftype_basic_no(ft));
				sub = (unsigned long)no;
			}
			t = NULL_type;
			break;
		}
		case type_ptr_tag:
		case type_ref_tag:
			t = DEREF_type(type_ptr_etc_sub(t));
			break;
		case type_ptr_mem_tag: {
			CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
			IDENTIFIER cid = DEREF_id(ctype_name(ct));
			HASHID cnm = DEREF_hashid(id_name(cid));
			sub = DEREF_ulong(hashid_hash(cnm));
			t = DEREF_type(type_ptr_mem_sub(t));
			break;
		}
		case type_func_tag: {
			LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
			sub = (unsigned long)LENGTH_list(p);
			t = DEREF_type(type_func_ret(t));
			break;
		}
		case type_array_tag:
			t = DEREF_type(type_array_sub(t));
			break;
		case type_bitfield_tag:
			t = find_bitfield_type(t);
			break;
		case type_compound_tag: {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			IDENTIFIER cid = DEREF_id(ctype_name(ct));
			HASHID cnm = DEREF_hashid(id_name(cid));
			sub = DEREF_ulong(hashid_hash(cnm));
			t = NULL_type;
			break;
		}
		case type_enumerate_tag: {
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			IDENTIFIER eid = DEREF_id(etype_name(et));
			HASHID enm = DEREF_hashid(id_name(eid));
			sub = DEREF_ulong(hashid_hash(enm));
			t = NULL_type;
			break;
		}
		default :
			t = NULL_type;
			break;
		}
		h += (64 * sub + 4 * tag + (unsigned long)qual);
	}
	return h % HASH_TYPE_SIZE;
}


/*
    This routine initialises the hash table entry nm by creating a dummy
    identifier with lexical token value tok for it to point to.
*/

static void
init_hashid(HASHID nm, int tok)
{
	IDENTIFIER id;
	MAKE_id_dummy(nm, dspec_none, NULL_nspace, crt_loc, id);
	COPY_ulong(id_no(id), (unsigned long)tok);
	COPY_id(hashid_id(nm), id);
	COPY_id(hashid_cache(nm), id);
	return;
}


/*
    This routine looks up the identifier name s in the hash table, creating
    it if it does not already exist.  h gives the value of hash ( s ) (which
    gets checked by an assertion).  The argument tok is set to lex_unknown to
    indicate that the identifier has just been read by read_token, otherwise
    it gives the underlying default lexical token.
*/

HASHID
lookup_name(string s, unsigned long h, int ext, int tok)
{
	unsigned tag;
	unsigned long len;
	HASHID prev = NULL_hashid;
	HASHID nm = hash_table[h];
	assert(h == hash(s));

	/* Search through existing entries */
	while (!IS_NULL_hashid(nm)) {
		string t = DEREF_string(hashid_name_etc_text(nm));
		int c = ustrcmp(t, s);
		if (c == 0) {
			/* Name matches */
			return nm;
		}
		if (c > 0) {
			break;
		}
		prev = nm;
		nm = DEREF_hashid(hashid_next(nm));
	}

	/* Create new hash table entry */
	len = (unsigned long)ustrlen(s);
	if (tok == lex_unknown) {
		s = xustrncpy(s, (gen_size)len);
		tok = lex_identifier;
	}
	tag = hashid_name_tag;
	if (ext) {
		/* Check for extended identifiers */
		string t = s;
		while (t = ustrchr(t, char_backslash), t != NULL) {
			t++;
			if (*t == char_u) {
				/* '\uxxxx' counts as one character */
				len -= 5;
			} else {
				/* '\Uxxxxxxxx' counts as one character */
				len -= 9;
			}
		}
		tag = hashid_ename_tag;
	}
	MAKE_hashid_name_etc(tag, nm, h, s, nm);
	if (IS_NULL_hashid(prev)) {
		hash_table[h] = nm;
	} else {
		COPY_hashid(hashid_next(prev), nm);
	}
	init_hashid(nm, tok);
	if (len >= max_id_length) {
		/* Check name length */
		IGNORE check_value(OPT_VAL_name_limit, len, nm);
	}
	return nm;
}


/*
    This routine creates a constructor, destructor or conversion function
    name (as indicated by tag) for the non-class type t named id.
*/

static HASHID
lookup_special(TYPE t, IDENTIFIER id, unsigned tag)
{
	unsigned long h = hash_type(t);
	HASHID prev = hash_type_table[h];
	HASHID nm = prev;

	/* Search through existing entries */
	while (!IS_NULL_hashid(nm)) {
		if (TAG_hashid(nm) == tag) {
			TYPE s = DEREF_type(hashid_constr_etc_type(nm));
			if (eq_type(s, t)) {
				COPY_id(hashid_constr_etc_tid(nm), id);
				return nm;
			}
		}
		nm = DEREF_hashid(hashid_next(nm));
	}

	/* Create new hash table entry */
	assert(h < HASH_SIZE);
	MAKE_hashid_constr_etc(tag, prev, h, t, id, nm);
	init_hashid(nm, lex_identifier);
	hash_type_table[h] = nm;
	return nm;
}


/*
    This routine creates the hash table entry for the constructor of type t
    and name id.
*/

HASHID
lookup_constr(TYPE t, IDENTIFIER id)
{
	HASHID nm;
	if (IS_type_compound(t)) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		IDENTIFIER cid = DEREF_id(ctype_constr(ct));
		if (IS_NULL_id(cid)) {
			/* Create class contructor */
			NAMESPACE ns = DEREF_nspace(ctype_member(ct));
			MAKE_hashid_constr(NULL_hashid, 0, t, id, nm);
			init_hashid(nm, lex_identifier);
			cid = DEREF_id(hashid_id(nm));
			COPY_nspace(id_parent(cid), ns);
			COPY_id(ctype_constr(ct), cid);
			IGNORE search_member(ns, nm, 1);
		} else {
			nm = DEREF_hashid(id_name(cid));
		}
	} else {
		nm = lookup_special(t, id, hashid_constr_tag);
	}
	return nm;
}


/*
    This routine creates the hash table entry for the destructor of type t
    and name id.
*/

HASHID
lookup_destr(TYPE t, IDENTIFIER id)
{
	HASHID nm;
	if (IS_type_compound(t)) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		IDENTIFIER cid = DEREF_id(ctype_destr(ct));
		if (IS_NULL_id(cid)) {
			/* Create class destructor */
			NAMESPACE ns = DEREF_nspace(ctype_member(ct));
			MAKE_hashid_destr(NULL_hashid, 1, t, id, nm);
			init_hashid(nm, lex_identifier);
			cid = DEREF_id(hashid_id(nm));
			COPY_nspace(id_parent(cid), ns);
			COPY_id(ctype_destr(ct), cid);
			IGNORE search_member(ns, nm, 1);
		} else {
			nm = DEREF_hashid(id_name(cid));
		}
	} else {
		nm = lookup_special(t, id, hashid_destr_tag);
	}
	return nm;
}


/*
    This routine returns the hash table entry for the conversion function
    corresponding to the type t.
*/

HASHID
lookup_conv(TYPE t)
{
	HASHID nm = lookup_special(t, NULL_id, hashid_conv_tag);
	return nm;
}


/*
    This table gives the hash table entries for the overloaded operator
    function names, 'operator +' etc.  It gives a straight look-up depending
    on the lexical token number of the operator.  All ISO keyword and
    digraphs are represented in their primary form.
*/

HASHID *hash_ops_table;


/*
    This routine creates a hash table entry for 'operator op' when op has
    lexical token number t.
*/

static HASHID
make_op(int t)
{
	HASHID nm;
	unsigned long h = (unsigned long)t;
	MAKE_hashid_op(NULL_hashid, (h % HASH_SIZE), t, nm);
	init_hashid(nm, lex_identifier);
	return nm;
}


/*
    This routine creates a hash table entry for an anonymous identifier.
    Note that each anonymous identifier gives a distinct hash table entry.
*/

HASHID
lookup_anon(void)
{
	HASHID nm;
	static unsigned long anon_no = 0;
	unsigned long a = anon_no++;
	MAKE_hashid_anon(NULL_hashid, (a % HASH_SIZE), a, nm);
	init_hashid(nm, lex_identifier);
	return nm;
}


/*
    This routine expands the identifier name nm.  For example, if t is
    a tokenised type defined to be int, then 'operator t' expands to
    'operator int'.  ct gives the expansion type for constructors and
    destructors.
*/

HASHID
expand_name(HASHID nm, CLASS_TYPE ct)
{
	switch (TAG_hashid(nm)) {
	case hashid_constr_tag:
		/* Constructor names */
		if (!IS_NULL_ctype(ct)) {
			IDENTIFIER id = DEREF_id(ctype_constr(ct));
			nm = DEREF_hashid(id_name(id));
		} else {
			TYPE t = DEREF_type(hashid_constr_type(nm));
			TYPE s = expand_type(t, 1);
			if (!EQ_type(t, s)) {
				nm = lookup_constr(s, NULL_id);
			}
		}
		break;
	case hashid_destr_tag:
		/* Destructor names */
		if (!IS_NULL_ctype(ct)) {
			IDENTIFIER id = DEREF_id(ctype_destr(ct));
			nm = DEREF_hashid(id_name(id));
		} else {
			TYPE t = DEREF_type(hashid_destr_type(nm));
			TYPE s = expand_type(t, 1);
			if (!EQ_type(t, s)) {
				nm = lookup_destr(s, NULL_id);
			}
		}
		break;
	case hashid_conv_tag: {
		/* Conversion function names */
		TYPE t = DEREF_type(hashid_conv_type(nm));
		TYPE s = expand_type(t, 1);
		if (!EQ_type(t, s)) {
			nm = lookup_conv(s);
		}
		break;
	}
	}
	return nm;
}


/*
    There is a complication in the expansion of conversion function names
    in that when types are identified more than one name may refer to the
    same type.  This routine finds the next such possible name returning
    the null identifier name to indicate that there are no more.
*/

HASHID
next_expand_name(HASHID nm)
{
	if (IS_hashid_conv(nm)) {
		int started = 0;
		TYPE t = DEREF_type(hashid_conv_type(nm));
		unsigned long h = hash_type(t);
		HASHID pnm = hash_type_table[h];
		while (!IS_NULL_hashid(pnm)) {
			if (EQ_hashid(pnm, nm)) {
				started = 1;
			} else if (started && IS_hashid_conv(pnm)) {
				TYPE s = DEREF_type(hashid_conv_type(pnm));
				if (eq_type(s, t)) return pnm;
			}
			pnm = DEREF_hashid(hashid_next(pnm));
		}
	}
	return NULL_hashid;
}


/*
    This routine finds the lexical token number associated with the hash
    identifier nm.  For a keyword, whether active or not, this is the
    associated value from syntax.h, otherwise it is lex_identifier.
*/

int
find_hashid(HASHID nm)
{
	unsigned long lex;
	IDENTIFIER id = DEREF_id(hashid_id(nm));
	while (!IS_id_dummy(id)) {
		/* Scan to last hidden value */
		id = DEREF_id(id_alias(id));
	}
	lex = DEREF_ulong(id_no(id));
	return (int)lex;
}


/*
    This routine finds the dummy identifier underlying id.
*/

IDENTIFIER
underlying_id(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	id = DEREF_id(hashid_id(nm));
	while (!IS_id_dummy(id)) {
		/* Scan to last hidden value */
		id = DEREF_id(id_alias(id));
	}
	return id;
}


/*
    The precise location of the last use of a hash identifier is stored
    in the loc field of its associated dummy identifier.  For simple
    identifiers this is set in read_token, however for more complex
    cases this routine sets the location of id to be the location of pid.
*/

void
set_hashid_loc(IDENTIFIER id, IDENTIFIER pid)
{
	if (!IS_NULL_id(pid)) {
		LOCATION loc;
		if (!IS_id_dummy(id)) {
			id = underlying_id(id);
		}
		if (!IS_id_dummy(pid)) {
			pid = underlying_id(pid);
		}
		DEREF_loc(id_loc(pid), loc);
		COPY_loc(id_loc(id), loc);
	}
	return;
}


/*
    This routine modifies the name of the identifier id by adding a prime
    to it.  This is intended primarily for debugging purposes.
*/

void
prime_name(IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		HASHID nm = DEREF_hashid(id_name(id));
		if (IS_hashid_name(nm)) {
			string s = DEREF_string(hashid_name_text(nm));
			s = xustrcat(s, ustrlit("'"));
			nm = lookup_name(s, hash(s), 0, lex_identifier);
		}
		COPY_hashid(id_name(id), nm);
	}
	return;
}


/*
    The table hash_keyword gives the hash table entries for the keywords.
    These are numbered from LAST_KEYWORD to FIRST_KEYWORD.  The array
    should be accessed through the macro KEYWORD defined in hash.h, which
    includes the appropriate offset.
*/

HASHID hash_keyword[LAST_KEYWORD - FIRST_KEYWORD + 1];
IDENTIFIER underlying_op = NULL_id;


/*
    This routine allocates space for the hash table and sets all its entries
    to NULL.  It also sets up the operator look-up table.
*/

void
init_hash(void)
{
	int n;
	unsigned long i;

	/* Set up identifier hash table */
	hash_table = xmalloc_nof(HASHID, HASH_SIZE);
	for (i = 0; i < HASH_SIZE; i++) {
		hash_table[i] = NULL_hashid;
	}

	/* Set up type hash table */
	hash_type_table = xmalloc_nof(HASHID, HASH_TYPE_SIZE);
	for (i = 0; i < HASH_TYPE_SIZE; i++) {
		hash_type_table[i] = NULL_hashid;
	}

	/* Set up operator look-up table */
	hash_ops_table = xmalloc_nof(HASHID, LAST_TOKEN + 1);
	for (n = 0; n <= LAST_TOKEN; n++) {
		hash_ops_table[n] = NULL_hashid;
	}

	/* Allocate hash table entries for all symbols */
	for (n = FIRST_C_SYMBOL; n <= LAST_C_SYMBOL; n++) {
		hash_ops_table[n] = make_op(n);
	}
	for (n = FIRST_CPP_SYMBOL; n <= LAST_CPP_SYMBOL; n++) {
		hash_ops_table[n] = make_op(n);
	}
	for (n = FIRST_EXTRA_SYMBOL; n <= LAST_EXTRA_SYMBOL; n++) {
		hash_ops_table[n] = make_op(n);
	}
	hash_ops_table[lex_array_Hop] = make_op(lex_array_Hop);
	hash_ops_table[lex_cond_Hop] = make_op(lex_cond_Hop);
	hash_ops_table[lex_delete] = make_op(lex_delete);
	hash_ops_table[lex_delete_Harray] = make_op(lex_delete_Harray);
	hash_ops_table[lex_func_Hop] = make_op(lex_func_Hop);
	hash_ops_table[lex_new] = make_op(lex_new);
	hash_ops_table[lex_new_Harray] = make_op(lex_new_Harray);
	hash_ops_table[lex_alignof] = make_op(lex_alignof);
	hash_ops_table[lex_sizeof] = make_op(lex_sizeof);
	hash_ops_table[lex_typeid] = make_op(lex_typeid);
	hash_ops_table[lex_vtable] = make_op(lex_vtable);

	/* Map secondary representations to primary representations */
	for (n = FIRST_DIGRAPH; n <= LAST_DIGRAPH; n++) {
		int m = primary_form(n);
		hash_ops_table[n] = hash_ops_table[m];
	}
	for (n = FIRST_ISO_KEYWORD; n <= LAST_ISO_KEYWORD; n++) {
		int m = primary_form(n);
		hash_ops_table[n] = hash_ops_table[m];
	}

	/* This is necessary for the definition of KEYWORD */
	assert(FIRST_KEYWORD == lex_auto);
	return;
}
