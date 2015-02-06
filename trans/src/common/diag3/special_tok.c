/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/xalloc.h>

#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/sort.h>
#include <reader/main_reads.h>

#include <refactor/refactor.h>

#include "dg_fns.h"
#include "diag_fns.h"
#include "diaginfo1.h"
#include "special_tok.h"


diag_info *
read_exp_to_source(void)
{
	diag_info *new = (diag_info *)xcalloc(1, sizeof(diag_info));

	new->key = DIAG_INFO_SOURCE;
	new->data.source.beg = d_sourcemark();
	new->data.source.end = d_sourcemark();

	return new;
}


diag_info *
read_diag_id_scope(void)
{
	diag_info *new = (diag_info *)xcalloc(1, sizeof(diag_info));

	new->key = DIAG_INFO_ID;
	new->data.id_scope.nme = d_tdfstring();
	new->data.id_scope.access = hold_refactor(d_exp());
	IGNORE hold(hold(new->data.id_scope.access));
	new->data.id_scope.typ = d_diag_type();
	return new;
}


diag_info *
read_diag_type_scope(void)
{
	diag_info *new = (diag_info *)xcalloc(1, sizeof(diag_info));

	new->key = DIAG_INFO_TYPE;
	new->data.type_scope.nme = d_tdfstring();
	new->data.type_scope.typ = d_diag_type();
	return new;
}


diag_info *
read_diag_tag_scope(void)
{
	diag_info *new = (diag_info *)xcalloc(2, sizeof(diag_info));

	new->key = DIAG_INFO_TAG;
	new->data.tag_scope.nme = d_tdfstring();
	new->data.tag_scope.typ = d_diag_type();
	return new;
}

