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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: find_id.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:11  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include "util.h"
#include "defs.h"
#include "find_id.h"
#include "syntax.h"


Tagdec * tagdecs;
Tagdec * localdecs;
Tokdec * tokdecs;
Labdec * labdecs;
Al_tagdec * al_tagdecs;


Tagdec * find_tag
    PROTO_N ( (n) )
    PROTO_T ( char * n )
{
    Tagdec * t = tagdecs;
    while (t != (Tagdec *)0) {
  	if (strcmp(n, t->idname.id) == 0) return t;
  	t = t->next;
    }
    t = localdecs;
    while (t != (Tagdec *)0) {
  	if (strcmp(n, t->idname.id) == 0) break;
  	t = t->next;
    }
    return t;
}

Tokdec * find_tok
    PROTO_N ( (n) )
    PROTO_T ( char * n )
{
    Tokdec * t = tokdecs;
    while (t != (Tokdec *)0) {
  	if (strcmp(n, t->idname.id) == 0) break;
  	t = t->next;
    }
    return t;
}

Labdec * find_lab
    PROTO_N ( (n) )
    PROTO_T ( char * n )
{
    Labdec * t = labdecs;
    while (t != (Labdec *)0) {
  	if (strcmp(n, t->idname.id) == 0) break;
  	t = t->next;
    }
    return t;
}

Al_tagdec * find_al_tag
    PROTO_N ( (n) )
    PROTO_T ( char * n )
{
    Al_tagdec * t = al_tagdecs;
    while (t != (Al_tagdec *)0) {
  	if (strcmp(n, t->idname.id) == 0) break;
  	t = t->next;
    }
    return t;
}

static int tok_kind
    PROTO_N ( (x) )
    PROTO_T ( Sort * x )
{
    switch(x->sort) {
	case access_sort: return access_tok;
	case al_tag_sort: return al_tag_tok;
	case bitfield_variety_sort:return bitfield_variety_tok;
	case error_treatment_sort: return error_treatment_tok;
	case exp_sort: return exp_tok;
	case floating_variety_sort: return floating_variety_tok;
	case label_sort: return label_tok;
	case nat_sort: return nat_tok;
	case ntest_sort: return ntest_tok;
	case rounding_mode_sort: return rounding_mode_tok;
	case shape_sort: return shape_tok;
	case signed_nat_sort: return signed_nat_tok;
	case tag_sort: return tag_tok;
	case token_sort: return tok_kind(&x->toksort->ressort);
	case variety_sort: return variety_tok;
    }
    fail("Not a sort - internal error");
    return 0;
}

void tidy_labels
    PROTO_N ( (old) )
    PROTO_T ( Labdec * old )
{
    Labdec ** rl = & labdecs;
    while (*rl != old) {
	if ((*rl)->declared) {
	    *rl = (*rl)->next;
	} else {
	    rl = &((*rl)->next);
	}
    }
}
