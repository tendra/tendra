/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"
#include <utility/option.h>

#include <parse/preproc.h>

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>
#include <utility/print.h>
#include <utility/ustring.h>

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/literal.h>
#include <parse/parse.h>
#include <parse/predict.h>

#include <construct/access.h>
#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <construct/destroy.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/field_iter.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/inttype.h>
#include <construct/namespace.h>
#include <construct/overload.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>

#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "str_ops.h"
#include "type_ops.h"

typedef struct _FieldIteratorBody_t {
	struct _FieldIteratorBody_t *parent;

	unsigned boff;

	FieldIteratorStage_t stage;

	TYPE t;
	unsigned tag;

	NAT n;
	TYPE array_element_type;
	TYPE parent_type;
	TYPE member_type;

	int m;
	int c;

	CV_SPEC cv;

	NAMESPACE ns;
	CLASS_TYPE ct;
	CLASS_TYPE cs;
	GRAPH gr;
	GRAPH gs;
	CV_SPEC cv_local;
	OFFSET off;
	LIST(GRAPH) br;

	MEMBER mem;
	IDENTIFIER sid;
	HASHID snm;
	DECL_SPEC ds;
} FieldIteratorBody_t;

static void field_iterator_body_free(FieldIteratorBody_t *sf_iter) {
	free(sf_iter);
}

int field_iterator_pop(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *this_body;

	if (!_sf_iter->body) { return BOOL_FALSE; }

	this_body = _sf_iter->body;
	_sf_iter->body = _sf_iter->body->parent;

	if (_sf_iter->bf->posn) {
		_sf_iter->bf->posn = _sf_iter->bf->start + this_body->boff;
		_sf_iter->bf->posn[0] = 0;
	}

	this_body->parent = NULL;
	field_iterator_body_free(this_body);

	return !!_sf_iter->body;
}

static void field_iterator_push_internal(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *body = calloc(1, sizeof(FieldIteratorBody_t));
	body->parent = _sf_iter->body;
	body->boff = (unsigned)(_sf_iter->bf->posn - _sf_iter->bf->start);
	_sf_iter->body = body;
}

void field_iterator_push(FieldIterator_t *_sf_iter, TYPE t, CV_SPEC cv) {
	field_iterator_push_internal(_sf_iter);

	_sf_iter->body->t = t;
	_sf_iter->body->cv = cv;
	_sf_iter->body->tag = TAG_type(t);
}

void field_iterator_init(FieldIterator_t *_sf_iter, TYPE t, CV_SPEC cv) {
	field_iterator_push_internal(_sf_iter);

	_sf_iter->body->t = t;
	_sf_iter->body->cv = cv;
	_sf_iter->body->tag = TAG_type(t);
}

FieldIteratorStage_t field_iterator_get_stage(FieldIterator_t *_sf_iter) {
	return _sf_iter->body->stage;
}

TYPE field_iterator_get_subtype(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	switch (sf_iter->stage) {
	case IS_Array: return sf_iter->array_element_type;
	case IS_AggregateBase: return sf_iter->parent_type;
	case IS_AggregateMembers: return sf_iter->member_type;
	default: return type_void;
	}
}

int field_iterator_get_decl_spec(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	if (sf_iter->stage == IS_AggregateMembers) {
		return sf_iter->ds;
	} else {
		DECL_SPEC ds = 0;
		return ds;
	}
}

OFFSET field_iterator_get_offset(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	if (sf_iter->stage == IS_AggregateMembers) {
		return sf_iter->off;
	} else {
		OFFSET off = 0;
		return off;
	}
}

int field_iterator_get_index(FieldIterator_t *_sf_iter) {
	return _sf_iter->body->c;
}

int field_iterator_get_overall_index(FieldIterator_t *_sf_iter) {
	return _sf_iter->overall_index;
}

void field_iterator_free(FieldIterator_t *_sf_iter) {
	while (_sf_iter->body) {
		field_iterator_pop(_sf_iter);
	}
}

static int field_iterator_next_member(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	if (!IS_NULL_member(sf_iter->mem)) {
		sf_iter->sid = DEREF_id(member_id(sf_iter->mem));
		sf_iter->member_type = DEREF_type(id_member_type(sf_iter->sid));
		sf_iter->ds = DEREF_dspec(id_storage(sf_iter->sid));
		sf_iter->off = DEREF_off(id_member_off(sf_iter->sid));

		/* Build up field name */
		sf_iter->snm = DEREF_hashid(id_name(sf_iter->sid));
		if (!IS_hashid_anon(sf_iter->snm)) {
			bfputc(_sf_iter->bf, '.');
			IGNORE print_hashid(sf_iter->snm, 1, 0, _sf_iter->bf, 0);
		}

		sf_iter->mem = DEREF_member(member_next(sf_iter->mem));
		sf_iter->mem = next_data_member(sf_iter->mem, 0);

		/* Adjust cv-qualifiers */
		if (sf_iter->ds & dspec_mutable) {
			sf_iter->cv_local = cv_none;
		} else {
			sf_iter->cv_local = sf_iter->cv;
		}

		sf_iter->c++;
		_sf_iter->overall_index++;

		return BOOL_TRUE;
	} else {
		return BOOL_FALSE;
	}
}

static int field_iterator_next_base(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	/* Loop through base classes */
	if (!IS_NULL_list(sf_iter->br)) {
		sf_iter->gs = DEREF_graph(HEAD_list(sf_iter->br));
		sf_iter->off = DEREF_off(graph_off(sf_iter->gs));
		sf_iter->cs = DEREF_ctype(graph_head(sf_iter->gs));
		sf_iter->parent_type = make_class_type(sf_iter->cs);

		/* Build up field name */
		sf_iter->sid = DEREF_id(ctype_name(sf_iter->cs));
		sf_iter->snm = DEREF_hashid(id_name(sf_iter->sid));
		if (!IS_hashid_anon(sf_iter->snm)) {
			bfputc(_sf_iter->bf, '.');
			IGNORE print_hashid(sf_iter->snm, 1, 0, _sf_iter->bf, 0);
		}
		sf_iter->br = TAIL_list(sf_iter->br);
		return BOOL_TRUE;
	} else {
		return BOOL_FALSE;
	}
}

CV_SPEC field_iterator_get_effective_cv_spec(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	if (sf_iter->stage == IS_AggregateMembers) {
		return sf_iter->cv_local;
	} else {
		CV_SPEC result = 0;
		return result;
	}
}

int field_iterator_next(FieldIterator_t *_sf_iter) {
	FieldIteratorBody_t *sf_iter = _sf_iter->body;

	switch (sf_iter->stage) {
	case IS_Unstarted:
		switch (sf_iter->tag) {
		case type_array_tag: {
			/* Array types */
			NAT nc;
			sf_iter->array_element_type = DEREF_type(type_array_sub(sf_iter->t));
			sf_iter->boff = (unsigned)(_sf_iter->bf->posn - _sf_iter->bf->start);

			/* Find the array size */
			sf_iter->n = DEREF_nat(type_array_size(sf_iter->t));
			sf_iter->m = get_nat_value(sf_iter->n);

			if (sf_iter->c == sf_iter->m) {
				return BOOL_FALSE;
			}

			sf_iter->stage = IS_Array;
			return field_iterator_next(_sf_iter);
		}
		case type_compound_tag: {
			/* Compound types */
			sf_iter->stage = IS_AggregateBase;
			sf_iter->ct = DEREF_ctype(type_compound_defn(sf_iter->t));
			sf_iter->gr = DEREF_graph(ctype_base(sf_iter->ct));
			sf_iter->br = DEREF_list(graph_tails(sf_iter->gr));
			sf_iter->cv_local = (DEREF_cv(type_qual(sf_iter->t)) | sf_iter->cv);
			sf_iter->boff = (unsigned)(_sf_iter->bf->posn - _sf_iter->bf->start);
			return field_iterator_next(_sf_iter);
		}
		}
	case IS_Array:
		if (_sf_iter->bf->posn) {
			_sf_iter->bf->posn = _sf_iter->bf->start + sf_iter->boff;
			_sf_iter->bf->posn[0] = 0;
		}

		if (sf_iter->c == sf_iter->m) {
			return BOOL_FALSE;
		}

		/* Build up the field name */
		bfprintf(_sf_iter->bf, "[%lu]", sf_iter->c);

		sf_iter->c++;
		_sf_iter->overall_index++;
		return BOOL_TRUE;

	case IS_AggregateBase:
		{
			int result;

			/* Restore field name */
			if (_sf_iter->bf->posn) {
				_sf_iter->bf->posn = _sf_iter->bf->start + sf_iter->boff;
				_sf_iter->bf->posn[0] = 0;
			}

			result = field_iterator_next_base(_sf_iter);
			if (result) {
				sf_iter->c++;
				_sf_iter->overall_index++;
				return BOOL_TRUE;
			} else {
				sf_iter->stage = IS_AggregateMembers;

				/* Find list of class members */
				sf_iter->ns = DEREF_nspace(ctype_member(sf_iter->ct));
				sf_iter->mem = DEREF_member(nspace_ctype_first(sf_iter->ns));
				sf_iter->mem = next_data_member(sf_iter->mem, 0);

				return field_iterator_next_member(_sf_iter);
			}
		}

	case IS_AggregateMembers:
		/* Restore field name */
		if (_sf_iter->bf->posn) {
			_sf_iter->bf->posn = _sf_iter->bf->start + sf_iter->boff;
			_sf_iter->bf->posn[0] = 0;
		}

		return field_iterator_next_member(_sf_iter);
	}
}
