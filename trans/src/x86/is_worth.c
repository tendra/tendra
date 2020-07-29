/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/exp.h>
#include <construct/is_worth.h>

bool
is_worth(exp c)
{
	unsigned char cnam = c->tag;

	if (sh(c)->tag == realhd && cnam == cont_tag &&
	    son(c)->tag == name_tag && isvar(son(son(c))) &&
	    isglob(son(son(c))))
	{
		return 1;
	}

	if (cnam == cont_tag && son(c)->tag == name_tag && !isvar(son(son(c)))) {
		return 1;
	}

	return (!is_o(cnam) && cnam != clear_tag &&
	        cnam != int_to_bitf_tag && cnam != bitf_to_int_tag) ||
	       /* ignore simple things unless ... */
	       (cnam == cont_tag && son(c)->tag == cont_tag &&
	        son(son(c))->tag == name_tag)
	       || (cnam == name_tag &&
	           (isloadparam(son(c)) || isparam(son(c))) &&
	           !isvar(son(c)) &&
	           shape_size(sh(c)) <= 32

	           && sh(c)->tag != shrealhd

	          )
	       || (cnam == cont_tag && son(c)->tag == name_tag &&
	           isvar(son(son(c))) && isglob(son(son(c))) &&
	           ((c->last && bro(c) != NULL) ||
	           (!c->last && bro(c)->last && bro(bro(c)) != NULL)) &&
	           father(c)->tag == test_tag);
}

