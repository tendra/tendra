/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stddef.h>

#include <shared/bool.h>

#include <tdf/magic.h>

#include "types.h"
#include "enc_types.h"
#include "bitstream.h"
#include "encode.h"
#include "high.h"
#include "names.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


void
enc_bits_extn(bitstream *p, int b, long n)
{
    long m = ((1 << b) - 1);
    if (n == 0)fatal_error("Can't encode 0 as an extended value");
    while (n > m) {
	enc_bits(p, b,(long)0);
	n -= m;
    }
    enc_bits(p, b, n);
    return;
}


static void
enc_tdf_int_aux(bitstream *p, long n)
{
    unsigned long m = (unsigned long)n;
    if (m >= 8)enc_tdf_int_aux(p,(long)(m >> 3));
    enc_bits(p, 4,(long)(m & 7));
    return;
}


void
enc_tdf_int(bitstream *p, long n)
{
    unsigned long m = (unsigned long)n;
    if (m >= 8)enc_tdf_int_aux(p,(long)(m >> 3));
    enc_bits(p, 4,(long)((m & 7) | 8));
    return;
}


void
enc_aligned_string(bitstream *p, char *s, long n)
{
    long i;
    if (n == -1)n = (long)strlen(s);
    enc_tdf_int(p,(long)8);
    enc_tdf_int(p, n);
    align_bitstream(p);
    for (i = 0; i < n; i++) {
	long c = (long)s[i];
	enc_bits(p, 8, c);
    }
    return;
}


void
enc_external(bitstream *b, construct *p)
{
    node *e = p->ename;
    enc_tdf_int(b, p->encoding);
    if (e->cons->encoding) {
	node *q = e->child;
	if (q->cons->sortnum == SORT_tdfstring) {
	    node *r = q->next;
	    if (r == NULL) {
		enc_external_bits(b, ENC_string_extern);
		align_bitstream(b);
		enc_aligned_string(b, q->cons->name, q->cons->encoding);
	    } else {
		enc_external_bits(b, ENC_chain_extern);
		align_bitstream(b);
		enc_aligned_string(b, q->cons->name, q->cons->encoding);
		enc_node(b, r);
	    }
	} else {
	    enc_external_bits(b, ENC_unique_extern);
	    align_bitstream(b);
	    enc_tdf_int(b, q->cons->encoding);
	    for (q = e->child->child; q; q = q->next) {
		enc_aligned_string(b, q->cons->name, q->cons->encoding);
	    }
	}
    } else {
	enc_external_bits(b, ENC_string_extern);
	align_bitstream(b);
	enc_aligned_string(b, p->name,(long) -1);
    }
    return;
}


void
enc_node(bitstream *b, node *p)
{
    while (p) {
	construct *q = p->cons;
	switch (q->sortnum) {

	    case SORT_tdfbool: {
		/* Encode a bit */
		enc_bits(b, 1, q->encoding);
		break;
	    }

	    case SORT_bytestream: {
		/* Encode a bytestream */
		bitstream *c = new_bitstream();
		enc_node(c, p->child);
		enc_tdf_int(b, bitstream_length(c));
		join_bitstreams(b, c);
		break;
	    }

	    case SORT_completion: {
		/* Encode a completion */
		if (p->child)enc_node(b, p->child);
		break;
	    }

	    case SORT_small_tdfint: {
		/* Encode a small integer */
		enc_tdf_int(b, q->encoding);
		break;
	    }

	    case SORT_tdfint: {
		/* Encode a number */
		char *num = q->name;
		while (*num) {
		    long d = (long)(*num - '0');
		    num++;
		    if (*num == 0)d |= 8;
		    enc_bits(b, 4, d);
		}
		break;
	    }

	    case SORT_option: {
		/* Encode an optional argument */
		if (p->child) {
		    enc_bits(b, 1,(long)1);
		    enc_node(b, p->child);
		} else {
		    enc_bits(b, 1,(long)0);
		}
		break;
	    }

	    case SORT_repeat: {
		/* Encode a repeated argument */
		enc_list_start(b);
		enc_tdf_int(b, q->encoding);
		if (p->child)enc_node(b, p->child);
		break;
	    }

	    case SORT_tdfstring: {
		/* Encode a string */
		long i, n = q->encoding;
		if (n == -1) {
		    node *r = p->child;
		    long m = r->cons->encoding;
		    if (m < 0)m = -m;
		    r = r->next;
		    n = r->cons->encoding;
		    r = r->child;
		    enc_tdf_int(b, m);
		    enc_tdf_int(b, n);
		    for (i = 0; i < n; i++) {
			enc_bits(b,(int)m, r->cons->encoding);
			r = r->next;
		    }
		} else {
		    enc_tdf_int(b,(long)8);
		    enc_tdf_int(b, n);
		    for (i = 0; i < n; i++) {
			long c = (long)q->name[i];
			enc_bits(b, 8, c);
		    }
		}
		break;
	    }

	    case SORT_unknown: {
		/* Encode an unknown bitstream */
		fatal_error("Can't encode unknown bitstream");
		break;
	    }

	    case SORT_al_tag: {
		/* Encode an alignment tag */
		long e = q->encoding;
		enc_al_tag_bits(b,(int)e);
		if (e == ENC_make_al_tag) {
		    enc_tdf_int(b, p->child->cons->encoding);
		} else {
		    if (p->child)enc_node(b, p->child);
		}
		break;
	    }

	    case SORT_label: {
		/* Encode a label */
		long e = q->encoding;
		enc_label_bits(b,(int)e);
		if (e == ENC_make_label) {
		    enc_tdf_int(b, p->child->cons->encoding);
		} else {
		    if (p->child)enc_node(b, p->child);
		}
		break;
	    }

	    case SORT_tag: {
		/* Encode a tag */
		long e = q->encoding;
		enc_tag_bits(b,(int)e);
		if (e == ENC_make_tag) {
		    enc_tdf_int(b, p->child->cons->encoding);
		} else {
		    if (p->child)enc_node(b, p->child);
		}
		break;
	    }

	    case SORT_token: {
		/* Encode a token */
		tok_info *info = get_tok_info(q);
		if (is_high(info->res)) {
		    enc_token_bits(b, ENC_token_apply_token);
		    enc_token_bits(b, ENC_make_tok);
		    enc_tdf_int(b, q->encoding);
		    enc_tdf_int(b,(long)0);
		} else {
		    enc_token_bits(b, ENC_make_tok);
		    enc_tdf_int(b, q->encoding);
		}
		if (p->child) {
		    if (p->child->cons != &token_cons) {
			bitstream *c = new_bitstream();
			enc_node(c, p->child);
			enc_tdf_int(b, bitstream_length(c));
			join_bitstreams(b, c);
		    }
		} else {
		    enc_tdf_int(b,(long)0);
		}
		break;
	    }

	    default : {
		/* Encode a simple sort */
		int bits = sort_encoding[q->sortnum];
		int extn = sort_extension[q->sortnum];
		if (extn) {
		    enc_bits_extn(b, bits, q->encoding);
		} else {
		    enc_bits(b, bits, q->encoding);
		}
		if (p->child)enc_node(b, p->child);
		break;
	    }
	}
	p = p->next;
    }
    return;
}


static void
enc_sort(bitstream *b, sortname s)
{
    if (is_high(s)) {
	int i;
	high_sort *h = high_sorts + high_no(s);
	enc_sort(b, SORT_token);
	enc_sort(b, h->res);
	enc_list_start(b);
	enc_tdf_int(b,(long)h->no_args);
	for (i = 0; i < h->no_args; i++) {
	    enc_sort(b, h->args[i]);
	}
    } else {
	enc_sortname_bits(b, s);
    }
    return;
}


void
enc_aldef(bitstream *b, construct *p)
{
    al_tag_info *info = get_al_tag_info(p);
    enc_al_tagdef_bits(b, ENC_make_al_tagdef);
    enc_tdf_int(b, p->encoding);
    enc_node(b, info->def);
    return;
}


void
enc_tagdec(bitstream *b, construct *p)
{
    int m = 0;
    tag_info *info = get_tag_info(p);
    switch (info->var) {
	case 0: m = ENC_make_id_tagdec; break;
	case 1: m = ENC_make_var_tagdec; break;
	case 2: m = ENC_common_tagdec; break;
    }
    enc_tagdec_bits(b, m);
    enc_tdf_int(b, p->encoding);
    enc_node(b, info->dec);
    return;
}


int
enc_tagdef(bitstream *b, construct *p)
{
    int n = 0;
    int m = 0;
    tag_info *info = get_tag_info(p);
    node *d = info->def;
    switch (info->var) {
	case 0: m = ENC_make_id_tagdef; break;
	case 1: m = ENC_make_var_tagdef; break;
	case 2: m = ENC_common_tagdef; break;
    }
    while (d) {
	/* Can have multiple definitions */
	enc_tagdef_bits(b, m);
	enc_tdf_int(b, p->encoding);
	enc_node(b, d->child);
	d = d->next;
	n++;
    }
    return n;
}


static long
no_formals(char *args)
{
    long n = 0;
    while (*args) {
	args = find_sortname(args, NULL);
	args++;
	n = n + 1;
    }
    return n;
}


void
enc_tokdec(bitstream *b, construct *p)
{
    tok_info *info = get_tok_info(p);
    enc_tokdec_bits(b, ENC_make_tokdec);
    enc_tdf_int(b, p->encoding);

    /* Deal with signature */
    if (info->sig == NULL) {
	enc_bits(b, 1,(long)0);
    } else {
	enc_node(b, info->sig);
    }

    /* Encode token sort */
    enc_sort(b, SORT_token);

    /* Encode the token result sort */
    enc_sort(b, info->res);

    /* Encode the token argument sorts */
    enc_list_start(b);
    if (info->args) {
	char *q = info->args;
	enc_tdf_int(b, no_formals(q));
	while (*q) {
	    sortname s;
	    q = find_sortname(q, &s);
	    q++;
	    enc_sort(b, s);
	}
    } else {
	enc_tdf_int(b,(long)0);
    }
    return;
}


void
enc_tokdef(bitstream *b, construct *p)
{
    bitstream *c = new_bitstream();
    tok_info *info = get_tok_info(p);
    enc_tokdef_bits(b, ENC_make_tokdef);
    enc_tdf_int(b, p->encoding);

    /* Deal with signature */
    if (info->sig == NULL) {
	enc_bits(b, 1,(long)0);
    } else {
	enc_node(b, info->sig);
    }

    /* Encode token definition type */
    enc_token_defn_bits(c, ENC_token_definition);

    /* Encode the token result sort */
    enc_sort(c, info->res);

    /* Encode the token arguments */
    enc_list_start(c);
    if (info->args) {
	construct **q = info->pars;
	enc_tdf_int(c, no_formals(info->args));
	while (*q) {
	    tok_info *qinfo = get_tok_info(*q);
	    enc_sort(c, qinfo->res);
	    enc_tdf_int(c,(*q) ->encoding);
	    q++;
	}
    } else {
	enc_tdf_int(c,(long)0);
    }

    /* Encode the token definition */
    enc_node(c, info->def);
    enc_tdf_int(b, bitstream_length(c));
    join_bitstreams(b, c);
    return;
}
