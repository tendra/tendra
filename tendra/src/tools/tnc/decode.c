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
#include "tdf_types.h"
#include "tdf_stream.h"

#include "types.h"
#include "check.h"
#include "de_types.h"
#include "de_capsule.h"
#include "de_unit.h"
#include "decode.h"
#include "eval.h"
#include "file.h"
#include "high.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
 *    DECODE A TDF INTEGER
 *
 *    A TDF integer is decoded and returned as a long (no overflow checks).
 */

long
tdf_int(void)
{
	return (long)tdf_de_tdfintl (tdfr);
}


/*
 *    DECODE A TOKEN APPLICATION
 *
 *    A token application returning sort s is appended to p.  If s is
 *    SORT_unknown a simple token (rather than a token application) is
 *    read.
 */

construct *
de_token(node *p, sortname s)
{
    long bits;
    construct *t;
    tok_info *info;
    construct dummy;

    /* Find token type */
    long n = de_token_bits ();
    if (n == ENC_make_tok) {
		long m = tdf_int ();
		t = find_binding (crt_binding, tok_var, m);
		info = get_tok_info (t);
		p->son = new_node ();
		p->son->cons = t;
    } else if (n == ENC_use_tokdef) {
		char *nm;
		t = make_construct (SORT_token);
		nm = xalloc (32);
		IGNORE sprintf (nm, "~~token_%ld", t->encoding);
		t->name = nm;
		if (add_to_var_hash (t, SORT_token))
			MSG_FATAL_var_already_defined (nm);
		de_token_defn (t, (node *) null);
		info = get_tok_info (t);
		p->son = new_node ();
		p->son->cons = t;
    } else {
		high_sort *h;
		construct *tt;
		tt = de_token (p, SORT_token);
		info = get_tok_info (tt);
		h = high_sorts + high_no (info->res);
		dummy.name = "high level token";
		dummy.u.tok_u.res = h->res;
		dummy.u.tok_u.args = find_decode_string (h);
		t = &dummy;
		info = &dummy.u.tok_u;
    }

    /* Quit here if only reading token */
    if (s == SORT_unknown) {
		if (!text_output) {
			p->son->son = new_node ();
			p->son->son->cons = &token_cons;
		}
		return (null);
    }

    /* Find the length of the arguments */
    bits = tdf_int ();

    if (info->res == SORT_unknown) {
		/* Unknown token */
		if (bits) {
			/* Step over arguments */
			char *args;
			if (streq (t->name, "~dg_exp")) {
				args = "xFF";
			} else if (streq (t->name, "~exp_to_source")) {
				args = "xFF";
			} else if (streq (t->name, "~diag_id_scope")) {
				args = "x$xF";
			} else if (streq (t->name, "~diag_type_scope")) {
				args = "x$F";
			} else if (streq (t->name, "~diag_tag_scope")) {
				args = "x$F";
			} else {
				MSG_token_undeclared (t->name);
				args = "F";
			}
			bits += tdf_stream_tell (tdfr);
			p->son->son = de_node (args);
			bits -= tdf_stream_tell (tdfr);
			if (bits < 0)
				MSG_FATAL_token_arguments_length_wrong (t->name);
			tdf_skip_bits (tdfr, bits);
		} else {
			/* No argument - can deduce token sort */
			info->res = s;
			info->dec = 1;
		}
    } else {
		/* Known token */
		if (s == SORT_token) {
			/* Must be high level */
			if (!is_high (info->res))
				MSG_FATAL_sort_error_in_token (t->name);
		} else if (info->res != s) {
			/* Result sort must match */
			MSG_FATAL_sort_error_in_token (t->name);
		}
		if (info->args) {
			/* Decode arguments */
			tdf_pos end_posn = tdf_stream_tell (tdfr) + bits;
			p->son->son = de_node (info->args);
			if (tdf_stream_tell (tdfr) != end_posn)
				MSG_FATAL_token_arguments_length_wrong (t->name);
		} else {
			/* No arguments */
			if (bits)
				MSG_FATAL_token_arguments_length_wrong (t->name);
		}
		info->dec = 1;
    }

    /* Mark used tokens */
    if (info->dec) adjust_token (t);
    return (t);
}


/*
 *    DECODE A VARIABLE SORT
 *
 *    A construct of the vth variable sort is decoded.
 */

node *
de_var_sort(long v)
{
    long n = tdf_int ();
    node *p = new_node ();
    p->cons = find_binding (crt_binding, v, n);
    return (p);
}


/*
 *    DECODE A STRING OF DECODE CHARACTERS
 *
 *    The string of decode character str is decoded.
 */

node *
de_node(char *str)
{
    char c;
    node *p, *q = null, *qe = null;
    while (c = *str, c != 0 && c != ']') {
		switch (c) {

	    case '[' :
	    case '{' :
	    case '}' :
	    case '&' :
	    case '^' : {
			/* Ignore these cases */
			p = null;
			break;
	    }

	    case '|' : {
			/* Align input stream */
			tdf_de_align (tdfr);
			p = null;
			break;
	    }

	    case 'i' : {
			/* Decode an integer as a string of octal digits */
			unsigned long d, n = 0;
			char buff [1000];
			do {
				d = tdf_de_bits (tdfr, 4);
				buff [n] = (char) ('0' + (d & 7));
				n++;
			} while (!(d & 8));
			buff [n] = 0;
			p = new_node ();
			p->cons = new_construct ();
			if (fits_ulong (buff, 1)) {
				p->cons->sortnum = SORT_small_tdfint;
				p->cons->encoding = (long) octal_to_ulong (buff);
			} else {
				p->cons->sortnum = SORT_tdfint;
				p->cons->name = string_copy (buff);
			}
			break;
	    }

	    case 'j' : {
			/* Decode a bit */
			p = new_node ();
			p->cons = (tdf_bool () ? &true_cons : &false_cons);
			break;
	    }

	    case '$' : {
			/* Decode a string */
			unsigned long i, n = tdf_de_tdfintl (tdfr);
			if (n == 8) {
				char *s;
				n = tdf_de_tdfintl (tdfr);
				s = xalloc (n + 1);
				p = new_node ();
				p->cons = new_construct ();
				p->cons->sortnum = SORT_tdfstring;
				p->cons->encoding = n;
				p->cons->name = s;
				p->cons->next = null;
				for (i = 0 ; i < n ; i++) {
					s [i] = (char) tdf_de_bits (tdfr, 8) ; /* LINT */
				}
				s [n] = 0;
			} else {
				unsigned long m;
				node *px;
				p = new_node ();
				p->cons = &string_cons;
				p->son = make_int (n);
				m = tdf_de_tdfintl (tdfr);
				px = new_node ();
				px->cons = new_construct ();
				px->cons->sortnum = SORT_repeat;
				px->cons->encoding = m;
				p->son->bro->bro = px;
				for (i = 0 ; i < m ; i++) {
					long v = tdf_de_bits (tdfr, n);
					if (i == 0) {
						px->son = make_int (v);
						px = px->son;
					} else {
						px->bro->bro = make_int (v);
						px = px->bro->bro;
					}
				}
			}
			break;
	    }

	    case '=' : {
			/* Decode an aligned string */
			char *s;
			unsigned long i, n = tdf_de_tdfintl (tdfr);
			if (n != 8) MSG_FATAL_only_8bit_strings_allowed ();
			n = tdf_de_tdfintl (tdfr);
			tdf_de_align (tdfr);
			s = xalloc (n + 1);
			p = new_node ();
			p->cons = new_construct ();
			p->cons->sortnum = SORT_tdfstring;
			p->cons->encoding = n;
			p->cons->name = s;
			p->cons->next = null;
			for (i = 0 ; i < n ; i++) {
				s [i] = (char) tdf_de_bits (tdfr, 8) ; /* LINT */
			}
			s [n] = 0;
			tdf_de_align (tdfr);
			break;
	    }

	    case '*' : {
			/* The following text is repeated n times */
			de_list_start ();
			goto percent_case;
	    }

	    case '%' :
			percent_case : {
				/* The following text is repeated n times */
				node *pe = null;
				long i, n = tdf_int ();
				p = new_node ();
				p->cons = new_construct ();
				p->cons->sortnum = SORT_repeat;
				p->cons->encoding = n;
				str += 2;
				for (i = 0 ; i < n ; i++) {
					node *pi = de_node (str);
					if (pe == null) {
						p->son = pi;
					} else {
						pe->bro = pi;
					}
					pe = pi;
					while (pe->bro) pe = pe->bro;
				}
				str = skip_text (str);
				break;
			}

	    case '?' : {
			/* The following text is optional */
			p = new_node ();
			p->cons = &optional_cons;
			str += 2;
			if (tdf_bool ()) {
				p->son = de_node (str);
				if (*str == '*' && p->son->cons->encoding == 0) {
					/* Get rid of optional empty lists */
					p->son = null;
				}
			}
			str = skip_text (str);
			break;
	    }

	    case '@' : {
			/* The following text is a bitstream */
			tdf_pos len, pos;
			str += 2;
			len = tdf_de_tdfintl (tdfr);
			pos = tdf_stream_tell (tdfr);
			p = new_node ();
			p->cons = &bytestream_cons;
			p->son = de_node (str);
			if (len + pos != tdf_stream_tell (tdfr))
				MSG_FATAL_conditional_length_wrong ();
			str = skip_text (str);
			break;
	    }

	    case 'T' : {
			node dummy;
			str = find_sortname (str, (sortname *) null);
			IGNORE de_token (&dummy, SORT_unknown);
			p = dummy.son;
			break;
	    }

	    case 'F' : {
			/* Unknown sort */
			p = new_node ();
			p->cons = &unknown_cons;
			break;
	    }

	    default : {
			/* Basic sorts */
			sortname s = find_sort (c);
			p = (sort_decode [s]) ();
			break;
	    }
		}
		if (p) {
			if (qe == null) {
				q = p;
			} else {
				qe->bro = p;
			}
			qe = p;
			while (qe->bro) qe = qe->bro;
		}
		str++;
    }
    return (q);
}
