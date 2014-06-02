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
#include "capsule.h"
#include "basic.h"
#include "binding.h"
#include "file.h"
#include "sort.h"
#include "tdf.h"
#include "tree.h"
#include "unit.h"
#include "utility.h"


/*
 * EXPANSION MODE
 *
 * The flag dumb_mode determines whether the pretty-printer will
 * attempt to rationalize its input, or whether it will just blindly
 * output what it reads.  If show_stuff is true information on the
 * number of tags and tokens etc will be output.
 */
int dumb_mode = 0;
int show_stuff = 0;


/*
    SKIP PASS FOR TOKEN DEFINITIONS FLAG

    Tokens may be defined recursively without the necessary previous
    declarations to make this simple.  Thus the token definitions are
    given a preliminary pass to extract the declaration information.
    This feature can be switch on and off using the skip_pass flag.
    If show_skip is true the information read on the skip pass is
    displayed.  skipping is true iff we are in the skip pass.
*/

int skip_pass = 1;
int show_skip = 0;
int skipping = 0;


/*
 * ARRAYS OF EQUATION AND VARIABLE NAMES
 *
 * These arrays store the names of the types of equations (e.g. tokdefs)
 * and the types of variables these equations are in (e.g. tags and tokens).
 * The number of types of variables is given by no_variables.
 */
string *eqn_types = null;
string *var_types = null;
char *var_letters = "";
long *var_count = null;
long no_variables = 0;


/*
 * CURRENT BINDINGS
 *
 * The current binding table is given by crt_binding.
 */
binding *crt_binding;


/*
 * DECODE AN EXTERNAL LINKAGE
 *
 * An external name is decoded and associated with a variable of type v.
 * r gives the order information.
 */
static void
de_linkextern(long v, long r)
{
    object *p;
    external ext;
    long n = tdf_int();
    ext = de_extern_name();
    p = new_object(v);
    set_binding(crt_binding, v, n, p);
    p->named = 1;
    p->name = ext;
    p->order = r;
    if (v == var_token && ext.simple) {
	/* Look for special tokens */
	char *nm = ext.val.str;
	if (nm[0] == '~' && diagnostics) {
	    if (streq(nm, "~dg_exp")) {
		token_sort(p, sort_exp, "xG", n);
	    } else if (streq(nm, "~exp_to_source")) {
		token_sort(p, sort_exp, "xMM", n);
	    } else if (streq(nm, "~diag_id_scope")) {
		token_sort(p, sort_exp, "x$xd", n);
	    } else if (streq(nm, "~diag_type_scope")) {
		token_sort(p, sort_exp, "x$d", n);
	    } else if (streq(nm, "~diag_tag_scope")) {
		token_sort(p, sort_exp, "x$d", n);
	    }
	}
    }
    if (dumb_mode) {
	word *w1, *w2;
	w1 = new_word(HORIZ_NONE);
	out_string(var_types[v]);
	w2 = new_word(HORIZ_BRACKETS);
	out_int(n);
	end_word(w2);
	out_string("represents ");
	if (ext.simple) {
	    out(ext.val.str);
	} else {
	    out_unique(ext.val.uniq);
	}
	end_word(w1);
    }
    return;
}


/*
 * COUNT OF TOTAL NUMBER OF EQUATIONS OF A PARTICULAR TYPE
 *
 * This should be increased appropriately by each unit decoding function.
 */
long total = 0;
long blank_lines = 0;


/*
 * DECODE A SET OF EQUATIONS
 *
 * A set of equations is decoded.  f gives the procedure which is to be
 * used to decode the equation body.
 */
static void
de_equation(equation_func f)
{
    long i, n;
    long no_var;
    int needs_it = 0;
    static long unitno = 1;

    /* Record old bindings */
    binding *old_binding = crt_binding;

    /* Read the number of each type of variable */
    no_var = tdf_int();
    if (no_var) {
	if (no_var != no_variables) {
	    input_error("Number of local variables wrong");
	}
	crt_binding = new_binding_table();
	for (i = 0; i < no_var; i++) {
	    long sz = tdf_int();
	    set_binding_size(crt_binding, i, sz);
	    if (show_stuff) {
		out_string(var_types[i]);
		out_string(" x ");
		out_int(sz);
	    }
	}
	if (show_stuff)blank_line();
    }

    /* Read linkage for each type of variable */
    n = tdf_int();
    if (n != no_var)input_error("Number of linkage units wrong");
    if (no_var) {
	if (dumb_mode) {
	    word *w = new_word(HORIZ_NONE);
	    out_string("Bindings for Unit ");
	    out_int(unitno);
	    out("(inner->outer)");
	    end_word(w);
	    blank_line();
	}
	for (i = 0; i < no_var; i++) {
	    long j, no_links = tdf_int();
	    for (j = 0; j < no_links; j++) {
		object *p;
		long inner = tdf_int();
		long outer = tdf_int();
		if (dumb_mode) {
		    /* Output the linkage information */
		    word *w1, *w2;
		    w1 = new_word(HORIZ_NONE);
		    out_string(var_types[i]);
		    w2 = new_word(HORIZ_BRACKETS);
		    out_int(inner);
		    end_word(w2);
		    out_string("is bound to ");
		    out_string(var_types[i]);
		    w2 = new_word(HORIZ_BRACKETS);
		    out_int(outer);
		    end_word(w2);
		    end_word(w1);
		    needs_it = 1;
		}
		p = find_binding(old_binding, i, outer);
		set_binding(crt_binding, i, inner, p);
	    }
	}
	if (dumb_mode) {
	    if (needs_it)blank_line();
	    blank_lines = 1;
	}

	/* Complete the bindings */
	complete_binding(crt_binding);
    }

    /* Read the unit body */
    n = BYTESIZE * tdf_int();
    byte_align();
    if (f == null) {
	skip_bits(n);
	if (dumb_mode) {
	    out("(skipped)");
	    blank_line();
	    blank_lines = 1;
	}
	total++;
    } else {
	long end = posn(here) + n;
	(*f)();
	byte_align();
	if (posn(here)!= end)input_error("Unit length wrong");
    }

    /* Restore old bindings */
    if (no_var) {
	free_binding_table(crt_binding);
	crt_binding = old_binding;
	if (dumb_mode) {
	    for (i = blank_lines; i < 2; i++)blank_line();
	    out_string("End of Bindings for Unit ");
	    out_int(unitno++);
	    blank_line();
	    blank_line();
	    blank_lines = 2;
	}
    }
    return;
}


/*
 * DECODE A CAPSULE
 *
 * A capsule consists of a number of equation types, a number of variable
 * sorts, a number of external names for variables and a number of
 * equations of certain types.
 */
void
de_capsule(void)
{
    long i, n;
    long no_eqn, no_var;
    if (dumb_mode)show_stuff = 1;

    /* Read the magic number */
    out("MAGIC NUMBER");
    blank_line();
    de_magic(version_magic);
    blank_line();
    blank_line();

    /* Read the equation types */
    no_eqn = tdf_int();
    if (no_eqn) {
	if (show_stuff) {
	    out("EQUATION TYPES");
	    blank_line();
	}
	eqn_types = xmalloc_nof(string, no_eqn);
	for (i = 0; i < no_eqn; i++) {
	    string s = de_tdfstring_align();
	    eqn_types[i] = s;
	    if (show_stuff)out(s);
	}
	if (show_stuff) {
	    blank_line();
	    blank_line();
	}
    }

    /* Read the variable types and initialize the bindings */
    no_var = tdf_int();
    no_variables = no_var;
    crt_binding = new_binding_table();
    if (no_var) {
	if (show_stuff) {
	    out("VARIABLE TYPES");
	    blank_line();
	}
	var_types = xmalloc_nof(string, no_var);
	var_letters = xmalloc_nof(char, no_var + 1);
	var_count = xmalloc_nof(long, no_var);
	var_letters[no_var] = 0;

	for (i = 0; i < no_var; i++) {
	    string sv = de_tdfstring_align();
	    long sz = tdf_int();
	    var_letters[i] = find_variable(sv, i);
	    var_types[i] = sv;
	    var_count[i] = 0;
	    set_binding_size(crt_binding, i, sz);
	    if (show_stuff) {
		out_string(sv);
		out_string(" x ");
		out_int(sz);
	    }
	}
	if (show_stuff) {
	    blank_line();
	    blank_line();
	}
    }

    /* Read the external variable names */
    n = tdf_int();
    if (n != no_var)input_error("Number of variables wrong");
    if (no_var) {
	if (dumb_mode) {
	    out("EXTERNAL NAMES");
	    blank_line();
	}
	for (i = 0; i < no_var; i++) {
	    long j, no_links = tdf_int();
	    for (j = 0; j < no_links; j++)de_linkextern(i, j);
	}
	if (dumb_mode) {
	    blank_line();
	    blank_line();
	}
    }

    /* Complete the bindings */
    complete_binding(crt_binding);

    /* Read the equations */
    n = tdf_int();
    if (n != no_eqn)input_error("Number of equations wrong");
    for (i = 0; i < no_eqn; i++) {
	int used = 0;
	char *title = null;
	long j, no_units = tdf_int();
	string se = eqn_types[i];
	equation_func f = find_equation(se, &title, &used);
	if (!used) {
	    title = null;
	    f = null;
	}
	total = 0;
	if (f == de_tokdef_props && no_units) {
	    /* Skip pass */
	    place pl;
	    int old_pf = printflag;
	    if (!show_skip)printflag = 0;
	    skipping = 1;
	    pl.byte = here.byte;
	    pl.bit = here.bit;
	    if (printflag && (dumb_mode || f)) {
		if (title && !show_stuff) {
		    out_string(title);
		} else {
		    out_string("EQUATIONS OF TYPE ");
		    out_string(se);
		}
		out(" (SKIP PASS)");
		blank_line();
		blank_lines = 1;
	    }
	    for (j = 0; j < no_units; j++)de_equation(f);
	    if (printflag && (dumb_mode || f)) {
		if (total == 0) {
		    out("(none)");
		    blank_lines = 0;
		}
		for (j = blank_lines; j < 2; j++)blank_line();
		blank_lines = 2;
	    }
	    total = 0;
	    set_place(&pl);
	    skipping = 0;
	    printflag = old_pf;
	}

	/* Main pass */
	if (dumb_mode || f) {
	    if (title && !show_stuff) {
		out(title);
	    } else {
		out_string("EQUATIONS OF TYPE ");
		out(se);
	    }
	    blank_line();
	    blank_lines = 1;
	}
	for (j = 0; j < no_units; j++)de_equation(f);
	if (dumb_mode || f) {
	    if (total == 0) {
		out("(none)");
		blank_lines = 0;
	    }
	    for (j = blank_lines; j < 2; j++)blank_line();
	    blank_lines = 2;
	}
    }
    return;
}
