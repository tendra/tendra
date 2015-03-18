/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/magic.h>

#include "config.h"
#include "types.h"
#include "ascii.h"
#include "basic.h"
#include "binding.h"
#include "capsule.h"
#include "file.h"
#include "sort.h"
#include "tree.h"
#include "tdf.h"
#include "unit.h"
#include "utility.h"


/*
 * WARN ABOUT UNDECLARED TOKENS
 */
int warn_undeclared = 0;


/*
 * DECODING TOKENS
 *
 * Simple TOKENs are represented by TDF integers.  They may also be
 * tokenised themselves.
 */
object *
de_token_aux(sortname s, char *nm)
{
    word *w;
    long bits, t;
    object *obj = NULL;
    int ap = 1, simple = 1;
    int just_tok = (s == sort_unknown ? 1 : 0);

    /* Find the token number */
    long n = de_token();
    if (n == token_make_tok) {
	t = tdf_int();
    } else {
	simple = 0;
    }

    /* Look up simple tokens */
    if (simple) {
	SET(t);
	obj = find_binding(crt_binding, var_token, t);
	if (obj == NULL) {
	    obj = new_object(var_token);
	    set_binding(crt_binding, var_token, t, obj);
	}

	/* Check token sort */
	if (res_sort(obj) == sort_unknown) {
	    sortname is = implicit_sort(obj);
	    if (is == sort_unknown && warn_undeclared) {
		int old_recover = recover;
		int old_exit_status = exit_status;
		recover = 1;
		input_error("Warning : token %s used before it is declared",
			      object_name(var_token, t));
		recover = old_recover;
		exit_status = old_exit_status;
	    }
	    if (is != sort_unknown && is != s) {
		sortid es;
		out("<error>");
		es = find_sort(s);
		input_error("Implicit sort error, token %s, %s expected",
			      object_name(var_token, t), es.name);
	    }
	    implicit_sort(obj) = s;
	} else if (res_sort(obj)!= s && !just_tok) {
	    sortid es;
	    out("<error>");
	    es = find_sort(s);
	    input_error("Sort error, token %s, %s expected",
			  object_name(var_token, t), es.name);
	}

	/* Output token name if appropriate */
	if (!dumb_mode) {
	     if (obj->named) {
		if (obj->name.simple) {
		    out_string(obj->name.val.str);
		    ap = 0;
		}
	    } else {
		char buff[50];
		IGNORE sprintf(buff, "~token_%ld", obj->id);
		out_string(buff);
		ap = 0;
	    }
	}
    }

    /* Output "apply_token" if appropriate */
    if (ap) {
	if (just_tok) {
	    out_string("make_token");
	} else {
	    out_string("apply_");
	    out_string(nm);
	    out_string("_token");
	}
	w = new_word(VERT_BRACKETS);
	if (simple) {
	    SET(t);
	    out_object(t, obj, var_token);
	} else {
	    if (n == token_token_apply_token) {
		object *subobj = de_token_aux(sort_token, "token");
		if (subobj)obj = subobj->aux;
	    } else {
		/* use_tokdef */
		long len = tdf_int();
		skip_bits(len);
		out_string("use_tokdef(....)");
		IGNORE new_word(SIMPLE);
	    }
	}
    } else {
	/* Applications of named tokens are indicated by "*" */
	out_string("*");
    }

    /* Quit here if just reading token */
    if (just_tok) {
	if (ap) {
	    SET(w);
	    end_word(w);
	} else {
	    IGNORE new_word(SIMPLE);
	}
	return obj;
    }

    /* Read length of token arguments */
    bits = tdf_int();

    /* Deal with tokens without arguments */
    if (bits == 0) {
	if (obj && res_sort(obj)!= sort_unknown) {
	    char *ps = arg_sorts(obj);
	    if (ps && *ps) {
		if (simple) {
		    SET(t);
		    input_error("Token arguments missing, token %s",
				  object_name(var_token, t));
		} else {
		    input_error("Token arguments missing");
		}
	    }
	}
	if (ap) {
	    SET(w);
	    end_word(w);
	} else {
	    IGNORE new_word(SIMPLE);
	}
	return obj;
    }

    /* Deal with tokens with arguments */
    if (obj && res_sort(obj)!= sort_unknown && !is_foreign(obj)) {
	/* Known token - decode arguments */
	if (arg_sorts(obj)) {
	    long p = posn(here);
	    if (!ap)w = new_word(VERT_BRACKETS);
	    decode(arg_sorts(obj));
	    if (p + bits != posn(here)) {
		if (simple) {
		    SET(t);
		    input_error("Token arguments length wrong, token %s",
				  object_name(var_token, t));
		} else {
		    input_error("Token arguments length wrong");
		}
	    }
	} else {
	    if (ap) {
		SET(w);
		end_word(w);
	    } else {
		IGNORE new_word(SIMPLE);
	    }
	    return obj;
	}
    } else {
	/* Unknown token - step over arguments */
	if (!ap)w = new_word(VERT_BRACKETS);
	out("....");
	skip_bits(bits);
    }
    SET(w);
    end_word(w);
    return obj;
}


/*
 * DECODING SIMPLE LABELS
 */
void
de_make_label(long lab_no)
{
    if (dumb_mode) {
	word *w;
	out_string("label");
	w = new_word(HORIZ_BRACKETS);
	out_int(lab_no);
	end_word(w);
    } else {
	out_string("~label_");
	out_int(lab_no);
    }
    if (lab_no < 0 || lab_no >= max_lab_no) {
	input_error("Label number %ld out of range", lab_no);
    }
    return;
}


/*
 * FORMATTING SIZE FOR TDF STRINGS
 *
 * A string will be split by de_format_string into sections of length
 * at most STRING_WIDTH.
 */
#define STRING_WIDTH		40


/*
 * DECODING FORMATTED STRINGS
 *
 * A TDF string is read and output in a formatted form.
 */
void
de_tdfstring_format(void)
{
    string s;
    word *ptr1;
    long sz = tdf_int();
    long n = tdf_int();
    if (sz != 8) {
	char sbuff[100];
	IGNORE sprintf(sbuff, "make_string_%ld", sz);
	out_string(sbuff);
	ptr1 = new_word(HORIZ_BRACKETS);
    }
    if (sz > 8) {
	long i;
	for (i = 0; i < n; i++) {
	    long v = fetch((int)sz);
	    out_int(v);
	}
    } else {
	s = get_string(n, sz);
	n = (long)strlen(s);
	if (n == 0) {
	    out("\"\"");
	    return;
	}
	while (n) {
	    long m = (n < STRING_WIDTH ? n : STRING_WIDTH);
	    char *w = xmalloc_nof(char, m + 3);
	    IGNORE memcpy(w + 1, s,(size_t)m);
	    w[0] = QUOTE;
	    w[m + 1] = QUOTE;
	    w[m + 2] = 0;
	    out(w);
	    n -= m;
	    s += m;
	}
    }
    if (sz != 8) {
	SET(ptr1);
	end_word(ptr1);
    }
    return;
}


/*
 * DECODING THE EXP "solve" (OR "labelled")
 *
 * This is tricky because it is encoded as:
 *
 *    A1, ..., An, B, C1, ..., Cn
 *
 * where n is a TDF integer, Ai is given by the decode string str1,
 * B is given by str2, and Ci is given by str3, but we want to print
 * it in the order :
 *
 *      B, A1, C1, ..., An, Cn
 *
 * so there is a certain amount of to-ing and fro-ing.
 */
void
de_solve_fn(char *nm, char *str1, char *str2, char *str3, int ntwice)
{
    long i, n;
    word *ptr1, *ptr2;
    place posn1, posn2;

    int tempflag = printflag;

    out_string(nm);
    ptr1 = new_word(VERT_BRACKETS);

    /* Read the number of statements A1, ..., An */
    check_list();
    n = tdf_int();

    /* Record the position of A1 */
    posn1.byte = here.byte;
    posn1.bit = here.bit;

    /* Step over A1, ..., An */
    printflag = 0;
    for (i = 0; i < n; i++)decode(str1);
    printflag = tempflag;

    /* Decode B */
    decode(str2);

    if (ntwice) {
	/* Read and check the number of statements C1, ..., Cn */
	long m;
	check_list();
	m = tdf_int();
	if (m != n)input_error("Illegal %s construct", nm);
    }

    for (i = 0; i < n; i++) {
	ptr2 = new_word(VERT_BRACKETS);

	/* Record the position of Ci */
	posn2.byte = here.byte;
	posn2.bit = here.bit;

	/* Go back and read Ai */
	set_place(&posn1);
	decode(str1);

	/* Record the position of A(i+1) */
	posn1.byte = here.byte;
	posn1.bit = here.bit;

	/* Go forward and read Ci */
	set_place(&posn2);
	decode(str3);

	end_word(ptr2);
    }
    end_word(ptr1);
    return;
}


/*
 * DECODING THE EXP "case"
 *
 * Only the layout makes this a special case.  The general form is:
 *
 *     A, L1, B1, ..., Ln, Bn
 *
 * where A is given by the decode string str1, Li is a label and Bi
 * is given by str2.
 */
void
de_case_fn(char *nm, char *str1, char *str2)
{
    long i, n;
    word *ptr1, *ptr2, *ptr3;

    out_string(nm);
    ptr1 = new_word(VERT_BRACKETS);
    decode(str1);
    ptr2 = new_word(VERT_BRACKETS);
    check_list();
    n = tdf_int();
    for (i = 0; i < n; i++) {
	ptr3 = new_word(HORIZ_NONE);
	IGNORE de_label();
	out(":");
	format(HORIZ_BRACKETS, "", str2);
	end_word(ptr3);
    }
    end_word(ptr2);
    end_word(ptr1);
    return;
}


/*
 * DECODING THE EXP "make_proc"
 *
 * The general form is:
 *
 *     A, B1, ..., Bn, C
 *
 * where A is given by the decode string str1, B by str2 and C by str3.
 * However each Bi is grouped as a "make_proc_arg".
 */
void
de_mk_proc_fn(char *nm, char *str1, char *str2, char *str3)
{
    long i, n;
    word *ptr;
    out_string(nm);
    ptr = new_word(VERT_BRACKETS);
    decode(str1);
    check_list();
    n = tdf_int();
    if (n == 0) {
	out("empty");
    } else {
	for (i = 0; i < n; i++) {
	    out_string(nm);
	    format(VERT_BRACKETS, "_arg", str2);
	}
    }
    decode(str3);
    end_word(ptr);
    return;
}
