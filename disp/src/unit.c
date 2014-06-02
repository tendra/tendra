/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/xalloc.h>

#include "config.h"

#include "types.h"
#include "basic.h"
#include "binding.h"
#include "capsule.h"
#include "file.h"
#include "sort.h"
#include "tdf.h"
#include "tree.h"
#include "unit.h"
#include "utility.h"


/*
 * CURRENT MAXIMUM LABEL NUMBER
 *
 * This gives the number of labels in the current unit.
 */
long max_lab_no = 0;


/*
 * READ NUMBER OF LABELS
 *
 * This routine reads the number of labels in a unit.
 */
void
read_no_labs(void)
{
    long n = tdf_int();
    if (show_stuff) {
	word *w = new_word(HORIZ_NONE);
	out_string("label x ");
	out_int(n);
	end_word(w);
	blank_line();
    }
    max_lab_no = n;
    return;
}


/*
 * SET TOKEN SORTS, CHECKING FOR COMPATIBILITY
 *
 * The token t (with number n) is set to have result sort rs and
 * argument sorts args.  If t has already been initialized these values
 * are checked against the existing values.  This routine also sets
 * the foreign field of t.
 */
void
token_sort(object *t, sortname rs, char *args, long n)
{
    sortid s;
    s = find_sort(rs);
    if (s.decode == 'F')is_foreign(t) = 1;
    if (args) {
	char *p;
	for (p = args; *p; p++) {
	    if (*p == 'F')is_foreign(t) = 1;
	}
    }
    if (res_sort(t) == sort_unknown) {
	sortname is = implicit_sort(t);
	if (is != sort_unknown && is != rs) {
	    input_error("Token %s inconsistent with previous use",
			  object_name(var_token, n));
	}
    } else {
	int good = 1;
	if (res_sort(t)!= rs)good = 0;
	if (args) {
	    if (arg_sorts(t)) {
		good = streq(args, arg_sorts(t));
	    } else {
		good = 0;
	    }
	} else {
	    if (arg_sorts(t))good = 0;
	}
	if (!good) {
	    input_error("Token %s declared inconsistently",
			  object_name(var_token, n));
	}
    }
    res_sort(t) = rs;
    arg_sorts(t) = args;
    return;
}


/*
 * DECODE A TOKEN DECLARATION
 *
 * A single token declaration is decoded.
 */
static void
de_tokdec_aux(void)
{
    long t;
    sortid s;
    object *obj;
    char *args = null;
    word *w = new_word(HORIZ_NONE);

    /* Find declaration type */
    IGNORE de_tokdec();

    /* Find token number */
    t = tdf_int();
    obj = find_binding(crt_binding, var_token, t);
    if (obj == null) {
	obj = new_object(var_token);
	set_binding(crt_binding, var_token, t, obj);
    }
    out_object(t, obj, var_token);
    out(":");

    /* Deal with signature */
    out("[");
    decode("?[X]");
    out("] :");

    /* Decode token sort */
    s = de_sort_name(0);
    if (s.res == sort_token) {
	long i, m;
	s = de_sort_name(1);
	check_list();
	m = tdf_int();
	if (m == 0) {
	    out("()");
	    args = "";
	} else {
	    word *wp = new_word(HORIZ_BRACKETS);
	    args = xmalloc_nof(char, m + 1);
	    for (i = 0; i < m; i++) {
		sortid p;
		p = de_sort_name(1);
		args[i] = p.decode;
		out(p.name);
	    }
	    args[m] = 0;
	    end_word(wp);
	}
	out_string("->");
    }
    out(s.name);
    end_word(w);
    if (obj)token_sort(obj, s.res, args, t);
    return;
}


/*
 * DECODE A TOKEN DEFINITION
 *
 * A single token definition is decoded.  If skipping is true then only
 * the declaration information will be extracted.
 */
static void
de_tokdef_aux(void)
{
    long t;
    sortid s;
    char *args;
    object *obj;
    long end, m;
    word *w = new_word(HORIZ_NONE);

    /* Find definition type */
    IGNORE de_tokdef();

    /* Find token number */
    t = tdf_int();
    obj = find_binding(crt_binding, var_token, t);
    if (obj == null) {
	obj = new_object(var_token);
	set_binding(crt_binding, var_token, t, obj);
    }
    out_object(t, obj, var_token);
    out(":");

    /* Deal with signature */
    out("[");
    decode("?[X]");
    out("] :");

    /* Read definition length and work out end */
    end = tdf_int();
    end += posn(here);

    /* Find definition type */
    IGNORE de_token_defn();

    /* Decode token sort */
    s = de_sort_name(1);
    check_list();
    m = tdf_int();
    if (m == 0) {
	out("()");
	args = "";
    } else {
	long i;
	word *wp = new_word(HORIZ_BRACKETS);
	args = xmalloc_nof(char, m + 1);
	for (i = 0; i < m; i++) {
	    long pn;
	    sortid p;
	    object *tp;
	    p = de_sort_name(1);
	    pn = tdf_int();
	    tp = find_binding(crt_binding, var_token, pn);
	    if (tp == null) {
		tp = new_object(var_token);
		set_binding(crt_binding, var_token, pn, tp);
	    }
	    res_sort(tp) = p.res;
	    arg_sorts(tp) = null;
	    if (p.res == sort_token) {
		object *tpa = xmalloc_nof(object, 1);
		*tpa = *tp;
		res_sort(tpa) = p.res;
		arg_sorts(tpa) = p.args;
		tp->aux = tpa;
	    }
	    args[i] = p.decode;
	    if (!dumb_mode && !(tp->named)) {
		tp->named = 1;
		tp->name.simple = 1;
		tp->name.val.str = xmalloc_nof(char, 10);
		IGNORE sprintf(tp->name.val.str, "~par_%ld", i);
	    }
	    out_string(p.name);
	    out_string(" ");
	    out_object(pn, tp, var_token);
	}
	args[m] = 0;
	end_word(wp);
    }
    out_string("->");

    /* Set result sort */
    out(s.name);
    end_word(w);
    token_sort(obj, s.res, args, t);

    /* Main definition body */
    out("Definition :");
    if (skipping || is_foreign(obj)) {
	long bits = end - posn(here);
	out("....");
	if (bits < 0) {
	    input_error("Token definition size wrong");
	} else {
	    skip_bits(bits);
	}
    } else {
	char buff[2];
	buff[0] = s.decode;
	buff[1] = 0;
	decode(buff);
	if (posn(here)!= end) {
	    input_error("Token definition size wrong");
	}
    }
    return;
}


/*
 * DECODE A TAG DECLARATION
 *
 * A single tag declaration is decoded.
 */
static void
de_tagdec_aux(void)
{
    long t;
    char m;
    word *wa;
    object *obj;
    word *w = new_word(HORIZ_NONE);

    /* Find declaration type */
    long n = de_tagdec();

    /* Get tag number */
    t = tdf_int();
    obj = find_binding(crt_binding, var_tag, t);
    if (obj == null) {
	obj = new_object(var_tag);
	set_binding(crt_binding, var_tag, t, obj);
    }
    out_object(t, obj, var_tag);

    /* Check consistency */
    switch (n) {
	case tagdec_make_var_tagdec: out("(variable)"); m = 0; break;
	case tagdec_make_id_tagdec: out("(identity)"); m = 1; break;
	default : out("(common)"); m = 2; break;
    }
    if (obj) {
	if (var(obj)!= m && var(obj)!= 3) {
	    string s = object_name(var_tag, t);
	    input_error("Tag %s declared inconsistently", s);
	}
	var(obj) = m;
    }

    /* Decode declaration body */
    wa = new_word(VERT_NONE);
    format(HORIZ_NONE, "has access : ", "?[u]");
    format(HORIZ_NONE, " and signature : ", "?[X]");
    format(HORIZ_NONE, " and shape : ", "S");
    end_word(wa);
    end_word(w);
    return;
}


/*
 * DECODE A TAG DEFINITION
 *
 * A single tag definition is decoded.
 */
static void
de_tagdef_aux(void)
{
    long t;
    char m;
    object *obj;
    word *w = new_word(HORIZ_NONE);

    /* Find definition type */
    long n = de_tagdef();

    /* Get tag number */
    t = tdf_int();
    obj = find_binding(crt_binding, var_tag, t);
    if (obj == null) {
	input_error("Tag %s defined but not declared",
		      object_name(var_tag, t));
	obj = new_object(var_tag);
	set_binding(crt_binding, var_tag, t, obj);
    }
    out_object(t, obj, var_tag);

    /* Check consistency */
    switch (n) {
	case tagdef_make_var_tagdef: out("(variable)"); m = 0; break;
	case tagdef_make_id_tagdef: out("(identity)"); m = 1; break;
	default : out("(common)"); m = 2; break;
    }
    if (obj) {
	if (var(obj)!= m && var(obj)!= 3) {
	    input_error("Tag %s declared inconsistently",
			  object_name(var_tag, t));
	}
	var(obj) = m;
    }

    /* Decode definition body */
    out("is :");
    end_word(w);
    if (m != 1) format(HORIZ_NONE, "access : ", "?[u]");
    format(HORIZ_NONE, "signature : ", "?[X]");
    IGNORE de_exp();
    return;
}


/*
 * DECODE AN ALIGNMENT TAG DEFINITION
 *
 * A single alignment tag definition is decoded.
 */
static void
de_al_tagdef_aux(void)
{
    long t;
    object *obj;
    word *w = new_word(HORIZ_NONE);

    /* Find definition type */
    IGNORE de_al_tagdef();

    /* Get alignment tag number */
    t = tdf_int();
    obj = find_binding(crt_binding, var_al_tag, t);
    if (obj == null) {
	obj = new_object(var_al_tag);
	set_binding(crt_binding, var_al_tag, t, obj);
    }
    out_object(t, obj, var_al_tag);

    /* Decode alignment body */
    out("is :");
    end_word(w);
    IGNORE de_alignment();
    return;
}


/*
 * DECODE A TOKEN DECLARATION UNIT
 *
 * This routine decodes a list of token declarations.
 */
void
de_tokdec_props(void)
{
    long i;
    long n = tdf_int();
    for (i = 0; i < n; i++) {
	de_tokdec_aux();
	blank_lines = 0;
    }
    total += n;
    return;
}


/*
 * DECODE A TOKEN DEFINITION UNIT
 *
 * This routine decodes a list of token definitions.
 */
void
de_tokdef_props(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	de_tokdef_aux();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}


/*
 * DECODE A TAG DECLARATION UNIT
 *
 * This routine decodes a list of tag declarations.
 */
void
de_tagdec_props(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	de_tagdec_aux();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}


/*
 * DECODE A TAG DEFINITION UNIT
 *
 * This routine decodes a list of tag definitions.
 */
void
de_tagdef_props(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	de_tagdef_aux();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}


/*
 * DECODE AN ALIGNMENT TAG DEFINITION UNIT
 *
 * This routine decodes a list of alignment tag definitions.
 */
void
de_al_tagdef_props(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	de_al_tagdef_aux();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}


/*
 * FLAGS FOR LINKER INFORMATION AND DIAGNOSTICS
 *
 * These flags control the output of the various non-core units.
 */
int show_usage = 0;
int diagnostics = 0;
int versions = 1;


/*
 * OUTPUT USAGE INFORMATION
 *
 * Given a usage n this routine outputs the corresponding usage
 * information.
 */
static void
out_usage(long n)
{
    static char *usage_info[] = {
	"used", "declared", "defined", "multiply-defined"
    };
    int i;
    int used = 0;
    word *w = new_word(HORIZ_BRACKETS);
    for (i = 0; i < 4; i++) {
	if (n & (1 << i)) {
	    out(usage_info[i]);
	    used = 1;
	}
    }
    if (!used)out("unused");
    end_word(w);
    return;
}


/*
 * DECODE USAGE INFORMATION
 *
 * This routine decodes the usage information for the external variables
 * of type v.  This consists of a set of usage values in 1-1 correspondence
 * with the externally named objects of this type.
 */
static void
de_usage(long v)
{
    object **p;
    long i, n;
    binding *b;
    long total_ext = 0, max_ext = -1;
    if (v < 0 || v >= no_variables) return;
    b = crt_binding + v;
    n = b->sz;
    if (n == 0) return;
    p = xmalloc_nof(object *, n);
    for (i = 0; i < n; i++) {
	object *q = b->table[i];
	long rank = (q ? q->order : -1);
	if (rank != -1 && b->table[i]->named) {
	    p[rank] = b->table[i];
	    if (rank >= max_ext)max_ext = rank;
	    total_ext++;
	}
    }
    if (total_ext != max_ext + 1) {
	input_error("Usage information wrong");
	return;
    }
    if (total_ext) {
	out_string(var_types[v]);
	out(" Usage Information");
	blank_line();
	for (i = 0; i < total_ext; i++) {
	    long use = tdf_int();
	    word *w = new_word(HORIZ_NONE);
	    if (p[i]->name.simple) {
		out(p[i]->name.val.str);
	    } else {
		out_unique(p[i]->name.val.uniq);
	    }
	    out_usage(use);
	    end_word(w);
	}
	blank_line();
	blank_line();
	blank_lines = 2;
	total += total_ext;
    }
    free(p);
    return;
}


/*
 * DECODE LINKER INFORMATION
 *
 * This routine decodes the linker information (tld2) units.  These are
 * used to give the linker information on the usage of tokens and tags.
 */
void
de_tld2_unit(void)
{
    de_usage(var_token);
    de_usage(var_tag);
    return;
}


/*
 * DECODE LINKER INFORMATION - NEW VERSION
 *
 * This routine decodes the linker information (tld) units.  These are
 * used to give the linker information on the usage of the externally
 * named objects.
 */
void
de_tld_unit(void)
{
    long n = tdf_int();
    switch (n) {
	case 0: {
	    de_tld2_unit();
	    break;
	}
	case 1: {
	    long v;
	    for (v = 0; v < no_variables; v++)de_usage(v);
	    break;
	}
	default : {
	    input_error("Illegal TLD version number %ld", n);
	    break;
	}
    }
    return;
}


#ifdef HAVE_diag_type_unit

/*
 * DECODE A DIAGNOSTIC TAG DEFINITION
 *
 * This routine decodes a single diagnostic tag definition.
 */
static void
de_diag_tagdef_aux(void)
{
    long t;
    object *obj;
    word *w = new_word(HORIZ_NONE);
    IGNORE de_diag_tagdef();

    /* Get alignment tag number */
    t = tdf_int();
    obj = find_binding(crt_binding, var_diag_tag, t);
    if (obj == null) {
	obj = new_object(var_diag_tag);
	set_binding(crt_binding, var_diag_tag, t, obj);
    }
    out_object(t, obj, var_diag_tag);

    /* Decode body */
    out("is :");
    end_word(w);
    IGNORE de_diag_type();
    return;
}

#endif


#ifdef HAVE_diag_type_unit

/*
 * DECODE DIAGNOSTIC TYPE INFORMATION
 *
 * This routine decodes a diagnostic type unit.
 */
void
de_diag_type_unit(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	de_diag_tagdef_aux();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}

#endif


#ifdef HAVE_diag_unit

/*
 * DECODE DIAGNOSTIC INFORMATION
 *
 * This routine decodes a diagnostic unit.
 */
void
de_diag_unit(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	IGNORE de_diag_descriptor();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}

#endif


#ifdef HAVE_dg_comp_props

/*
 * DECODE NEW DIAGNOSTIC INFORMATION
 *
 * This routine decodes a new diagnostic unit.
 */
void
de_dg_comp_props(void)
{
    long i, n;
    read_no_labs();
    IGNORE de_dg_compilation();
    blank_line();
    blank_lines = 1;
    n = tdf_int();
    for (i = 0; i < n; i++) {
	IGNORE de_dg_append();
	blank_line();
	blank_lines = 1;
    }
    total += (n + 1);
    return;
}

#endif


#ifdef HAVE_linkinfo_props

/*
 * DECODE LINKING INFORMATION
 *
 * This routine decode a linkage information unit.
 */
void
de_linkinfo_props(void)
{
    long i, n;
    read_no_labs();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	IGNORE de_linkinfo();
	blank_line();
	blank_lines = 1;
    }
    total += n;
    return;
}

#endif


/*
 * PREVIOUS VERSION NUMBER
 *
 * These variables are used to store the last version number read so
 * that duplicate version numbers can be suppressed.
 */
static long last_major = -1;
static long last_minor = -1;


/*
 * DECODE A VERSION NUMBER
 *
 * This routine decodes a version number for an s construct.
 */
void
de_make_version(char *s)
{
    long v1 = tdf_int();
    long v2 = tdf_int();
    if (v1 != last_major || v2 != last_minor || dumb_mode) {
	word *w;
	out_string(s);
	w = new_word(HORIZ_BRACKETS);
	out_int(v1);
	out_int(v2);
	end_word(w);
	last_major = v1;
	last_minor = v2;
    }
    if (v1 != version_major || v2 > version_minor) {
	input_error(
	    "Illegal version number, %ld.%ld (supported version is %d.%d)",
	    v1, v2, version_major, version_minor);
    }
    return;
}


#ifdef HAVE_version_props

/*
 * DECODE A VERSION UNIT
 *
 * This routine decodes a list of version numbers.
 */
void
de_version_props(void)
{
    long i, n;
    n = tdf_int();
    for (i = 0; i < n; i++) {
	IGNORE de_version();
	blank_lines = 0;
    }
    total += n;
    return;
}

#endif


/*
 * DECODE A MAGIC NUMBER
 *
 * This routine reads the magic number s.
 */
void
de_magic(char *s)
{
    int i, n = (int)strlen(s);
    for (i = 0; i < n; i++) {
	long c = fetch(8);
	if (c != (long)s[i]) {
	    input_error("Bad magic number, %s expected", s);
	    exit(EXIT_FAILURE);
	}
    }
    de_make_version(s);
    last_major = -1;
    last_minor = -1;
    byte_align();
    return;
}
