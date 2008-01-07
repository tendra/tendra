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
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

#include "types.h"
#include "encode.h"
#include "high.h"
#include "names.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
 *    ENCODE AN ALIGNED STRING
 *
 *    The string s is encoded as an aligned string into the bitstream p.
 *    n is either the length of s, or -1, indicating that strlen should
 *    be used to find the length.
 */

void
enc_aligned_string(struct tdf_stream *p, char *s, long n)
{
    long i;
    if (n == -1) n = (long) strlen (s);
    tdf_en_tdfintl (p, 8);
    tdf_en_tdfintl (p, (unsigned long)n);
    tdf_en_align (p);
    for (i = 0 ; i < n ; i++) {
		tdf_en_bits (p, 8, (unsigned char)s[i]);
    }
    return;
}


/*
 *    ENCODE AN EXTERNAL NAME
 *
 *    The external name of the construct p is encoded into the bitstream b.
 */

void
enc_external(struct tdf_stream *b, construct *p)
{
    node *e = p->ename;
    tdf_en_tdfintl (b, (unsigned long)p->encoding);
    if (e->cons->encoding) {
		node *q = e->son;
		if (q->cons->sortnum == SORT_tdfstring) {
			node *r = q->bro;
			if (r == null) {
				enc_external_bits (b, ENC_string_extern);
				tdf_en_align (b);
				enc_aligned_string (b, q->cons->name, q->cons->encoding);
			} else {
				enc_external_bits (b, ENC_chain_extern);
				tdf_en_align (b);
				enc_aligned_string (b, q->cons->name, q->cons->encoding);
				enc_node (b, r);
			}
		} else {
			enc_external_bits (b, ENC_unique_extern);
			tdf_en_align (b);
			tdf_en_tdfintl (b, (unsigned long)q->cons->encoding);
			for (q = e->son->son ; q ; q = q->bro) {
				enc_aligned_string (b, q->cons->name, q->cons->encoding);
			}
		}
    } else {
		enc_external_bits (b, ENC_string_extern);
		tdf_en_align (b);
		enc_aligned_string (b, p->name, (long) -1);
    }
    return;
}


/*
 *    FIND THE VALUE OF A STRING OF OCTAL DIGITS
 *
 *    The value of the node p, which represents a number, is returned.
 */

static long
octval(node *p)
{
    long n = (long) octal_to_ulong (p->bro->cons->name);
    if (p->cons->encoding) n = -n;
    return (n);
}


/*
 *    ENCODE A NODE
 *
 *    The node p is encoded into the bitstream b.
 */

void
enc_node(struct tdf_stream *b, node *p)
{
    while (p) {
		construct *q = p->cons;
		switch (q->sortnum) {

	    case SORT_tdfbool : {
			/* Encode a bit */
			tdf_en_bits (b, 1, (unsigned long)q->encoding);
			break;
	    }

	    case SORT_bytestream : {
			/* Encode a bytestream */
			struct tdf_stream *c = tdf_bs_create (NULL, TDFS_MODE_WRITE, NULL);
			enc_node (c, p->son);
			(void)tdf_en_bitstream (b, c);
			break;
	    }

	    case SORT_completion : {
			/* Encode a completion */
			if (p->son) enc_node (b, p->son);
			break;
	    }

	    case SORT_small_tdfint : {
			/* Encode a small integer */
			tdf_en_tdfintl (b, (unsigned long)q->encoding);
			break;
	    }

	    case SORT_tdfint : {
			/* Encode a number */
			char *num = q->name;
			while (*num) {
				unsigned long d = (unsigned char) (*num - '0');
				num++;
				if (*num == 0) d |= 8;
				tdf_en_bits (b, 4, d);
			}
			break;
	    }

	    case SORT_option : {
			/* Encode an optional argument */
			if (p->son) {
				tdf_en_bits (b, 1, (unsigned long) 1);
				enc_node (b, p->son);
			} else {
				tdf_en_bits (b, 1, (unsigned long) 0);
			}
			break;
	    }

	    case SORT_repeat : {
			/* Encode a repeated argument */
			enc_list_start (b);
			tdf_en_tdfintl (b, (unsigned long)q->encoding);
			if (p->son) enc_node (b, p->son);
			break;
	    }

	    case SORT_tdfstring : {
			/* Encode a string */
			long i, n = q->encoding;
			if (n == -1) {
				node *r = p->son;
				long m = octval (r);
				if (m < 0) m = -m;
				r = r->bro->bro;
				n = r->cons->encoding;
				r = r->son;
				tdf_en_tdfintl (b, (unsigned long)m);
				tdf_en_tdfintl (b, (unsigned long)n);
				for (i = 0 ; i < n ; i++) {
					tdf_en_bits (b, (unsigned) m, (unsigned long)octval (r));
					r = r->bro->bro;
				}
			} else {
				tdf_en_cstringn (b, (size_t)n, q->name);
			}
			break;
	    }

	    case SORT_unknown : {
			/* Encode an unknown struct tdf_stream */
			MSG_FATAL_cant_encode_unknown_bitstream ();
			break;
	    }

	    case SORT_al_tag : {
			/* Encode an alignment tag */
			long e = q->encoding;
			enc_al_tag_bits (b, (int) e);
			if (e == ENC_make_al_tag) {
				tdf_en_tdfintl (b, (unsigned long)p->son->cons->encoding);
			} else {
				if (p->son) enc_node (b, p->son);
			}
			break;
	    }

	    case SORT_label : {
			/* Encode a label */
			long e = q->encoding;
			enc_label_bits (b, (int) e);
			if (e == ENC_make_label) {
				tdf_en_tdfintl (b, (unsigned long)p->son->cons->encoding);
			} else {
				if (p->son) enc_node (b, p->son);
			}
			break;
	    }

	    case SORT_tag : {
			/* Encode a tag */
			long e = q->encoding;
			enc_tag_bits (b, (int) e);
			if (e == ENC_make_tag) {
				tdf_en_tdfintl (b, (unsigned long)p->son->cons->encoding);
			} else {
				if (p->son) enc_node (b, p->son);
			}
			break;
	    }

	    case SORT_token : {
			/* Encode a token */
			tok_info *info = get_tok_info (q);
			if (is_high (info->res)) {
				enc_token_bits (b, ENC_token_apply_token);
				enc_token_bits (b, ENC_make_tok);
				tdf_en_tdfintl (b, (unsigned long)q->encoding);
				tdf_en_tdfintl (b, (long) 0);
			} else {
				enc_token_bits (b, ENC_make_tok);
				tdf_en_tdfintl (b, (unsigned long)q->encoding);
			}
			if (p->son) {
				if (p->son->cons != &token_cons) {
					struct tdf_stream *c = tdf_bs_create (NULL, TDFS_MODE_WRITE, NULL);
					enc_node (c, p->son);
					(void)tdf_en_bitstream (b, c);
				}
			} else {
				tdf_en_tdfintl (b, (long) 0);
			}
			break;
	    }

	    default : {
			/* Encode a simple sort */
			unsigned int bits = sort_encoding [ q->sortnum ];
			int extn = sort_extension [ q->sortnum ];
			if (extn) {
				tdf_en_tdfextint (b, bits, (unsigned long)q->encoding);
			} else {
				tdf_en_bits (b, bits, (unsigned long)q->encoding);
			}
			if (p->son) enc_node (b, p->son);
			break;
	    }
		}
		p = p->bro;
    }
    return;
}


/*
 *    ENCODE A SORT
 */

static void
enc_sort(struct tdf_stream *b, sortname s)
{
    if (is_high (s)) {
		int i;
		high_sort *h = high_sorts + high_no (s);
		enc_sort (b, SORT_token);
		enc_sort (b, h->res);
		enc_list_start (b);
		tdf_en_tdfintl (b, (unsigned long)h->no_args);
		for (i = 0 ; i < h->no_args ; i++) {
			enc_sort (b, h->args [i]);
		}
    } else {
		enc_sortname_bits (b, s);
    }
    return;
}


/*
 *    ALIGNMENT TAG DEFINITION AUXILIARY ENCODING ROUTINE
 *
 *    The definition of the alignment tag p is encoded into the bitstream p.
 */

void
enc_aldef(struct tdf_stream *b, construct *p)
{
    al_tag_info *info = get_al_tag_info (p);
    enc_al_tagdef_bits (b, ENC_make_al_tagdef);
    tdf_en_tdfintl (b, (unsigned long)p->encoding);
    enc_node (b, info->def);
    return;
}


/*
 *    TAG DECLARATION AUXILIARY ENCODING ROUTINE
 *
 *    The declaration of the tag p is encoded into the bitstream p.
 */

void
enc_tagdec(struct tdf_stream *b, construct *p)
{
    int m = 0;
    tag_info *info = get_tag_info (p);
    switch (info->var) {
	case 0 : m = ENC_make_id_tagdec ; break;
	case 1 : m = ENC_make_var_tagdec ; break;
	case 2 : m = ENC_common_tagdec ; break;
    }
    enc_tagdec_bits (b, m);
    tdf_en_tdfintl (b, (unsigned long)p->encoding);
    enc_node (b, info->dec);
    return;
}


/*
 *    TAG DEFINITION AUXILIARY ENCODING ROUTINE
 *
 *    The definition of the tag p is encoded into the bitstream p.  Because
 *    of common_tagdef, there may actually be more than one definition.
 *    The number of definitions is returned.
 */

int
enc_tagdef(struct tdf_stream *b, construct *p)
{
    int n = 0;
    int m = 0;
    tag_info *info = get_tag_info (p);
    node *d = info->def;
    switch (info->var) {
	case 0 : m = ENC_make_id_tagdef ; break;
	case 1 : m = ENC_make_var_tagdef ; break;
	case 2 : m = ENC_common_tagdef ; break;
    }
    while (d) {
		/* Can have multiple definitions */
		enc_tagdef_bits (b, m);
		tdf_en_tdfintl (b, (unsigned long)p->encoding);
		enc_node (b, d->son);
		d = d->bro;
		n++;
    }
    return (n);
}


/*
 *    WORK OUT THE NUMBER OF FORMAL ARGUMENTS GIVEN A STRING
 */

static unsigned long
no_formals(char *args)
{
    long n = 0;
    while (*args) {
		args = find_sortname (args, (sortname *) null);
		args++;
		n = n + 1;
    }
    return (n);
}


/*
 *    TOKEN DECLARATION AUXILIARY ENCODING ROUTINE
 *
 *    The declaration of the token p is encoded into the bitstream p.
 */

void
enc_tokdec(struct tdf_stream *b, construct *p)
{
    tok_info *info = get_tok_info (p);
    enc_tokdec_bits (b, ENC_make_tokdec);
    tdf_en_tdfintl (b, (unsigned long)p->encoding);

    /* Deal with signature */
    if (info->sig == null) {
		tdf_en_bits (b, 1, (long) 0);
    } else {
		enc_node (b, info->sig);
    }

    /* Encode token sort */
    enc_sort (b, SORT_token);

    /* Encode the token result sort */
    enc_sort (b, info->res);

    /* Encode the token argument sorts */
    enc_list_start (b);
    if (info->args) {
		char *q = info->args;
		tdf_en_tdfintl (b, no_formals (q));
		while (*q) {
			sortname s;
			q = find_sortname (q, &s);
			q++;
			enc_sort (b, s);
		}
    } else {
		tdf_en_tdfintl (b, (long) 0);
    }
    return;
}


/*
 *    TOKEN DEFINITION AUXILIARY ENCODING ROUTINE
 *
 *    The definition of the token p is encoded into the bitstream p.
 */

void
enc_tokdef(struct tdf_stream *b, construct *p)
{
    struct tdf_stream *c = tdf_bs_create (NULL, TDFS_MODE_WRITE, NULL);
    tok_info *info = get_tok_info (p);
    enc_tokdef_bits (b, ENC_make_tokdef);
    tdf_en_tdfintl (b, (unsigned long)p->encoding);

    /* Deal with signature */
    if (info->sig == null) {
		tdf_en_bits (b, 1, 0);
    } else {
		enc_node (b, info->sig);
    }

    /* Encode token definition type */
    enc_token_defn_bits (c, ENC_token_definition);

    /* Encode the token result sort */
    enc_sort (c, info->res);

    /* Encode the token arguments */
    enc_list_start (c);
    if (info->args) {
		construct **q = info->pars;
		tdf_en_tdfintl (c, no_formals (info->args));
		while (*q) {
			tok_info *qinfo = get_tok_info (*q);
			enc_sort (c, qinfo->res);
			tdf_en_tdfintl (c, (unsigned long)(*q)->encoding);
			q++;
		}
    } else {
		tdf_en_tdfintl (c, (long) 0);
    }

    /* Encode the token definition */
    enc_node (c, info->def);
    (void)tdf_en_bitstream (b, c);
    return;
}
