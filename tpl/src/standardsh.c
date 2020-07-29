/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/xalloc.h>

#include "streams.h"
#include "units.h"
#include "encodings.h"
#include "enc_nos.h"
#include "defs.h"
#include "errors.h"
#include "standardsh.h"

static Name *intshtok = (Name *)0;
static Name *longshtok = (Name *)0;
static Name *shortshtok = (Name *)0;
static Name *charshtok = (Name *)0;
static Name *uintshtok = (Name *)0;
static Name *ulongshtok = (Name *)0;
static Name *ushortshtok = (Name *)0;
static Name *ucharshtok = (Name *)0;
static Name *floatshtok = (Name *)0;
static Name *doubleshtok = (Name *)0;

static TDFlist *extra_toks = (TDFlist *)0;


void
select_tokdef_unit(void)
{
	/* can define a token while in a token definition in shapes */
	if (current_Unit != tokdef_unit) {
		SELECT_UNIT(tokdef_unit);
	} else {
		TDFlist *tl = xmalloc(sizeof *tl);
		tl->next = extra_toks;
		extra_toks = tl;
		current_TDF = &tl->t;
		INIT_TDF(current_TDF);
		current_Unit = tokdef_unit;
	}
}


void
add_extra_toks(void)
{
	SELECT_UNIT(tokdef_unit);
	while (extra_toks != (TDFlist *)0) {
		append_TDF(&extra_toks->t, 1);
		INC_LIST;
		extra_toks = extra_toks->next;
	}
}


static void
make_intsh(Bool issigned)
{
	o_integer(o_var_limits(
	    o_make_signed_nat(out_tdfbool(issigned),
			      out_tdfint32(UL((issigned) ? MINSI : 0))),
	    o_make_signed_nat(out_tdfbool(0),
			      out_tdfint32(UL((issigned) ? MAXSI : MAXUSI)))));
}


static void
make_longsh(Bool issigned)
{
	o_integer(o_var_limits(
	    o_make_signed_nat(out_tdfbool(issigned),
			      out_tdfint32(UL((issigned) ? MINSL : 0))),
	    o_make_signed_nat(out_tdfbool(0),
			      out_tdfint32(UL((issigned) ? MAXSL : MAXUSL)))));
}


static void
make_shortsh(Bool issigned)
{
	o_integer(o_var_limits(
	    o_make_signed_nat(out_tdfbool(issigned),
			      out_tdfint32(UL((issigned) ? MINSS : 0))),
	    o_make_signed_nat(out_tdfbool(0),
			      out_tdfint32(UL((issigned) ? MAXSS : MAXUSS)))));
}


static void
make_charsh(Bool issigned)
{
	o_integer(o_var_limits(
	    o_make_signed_nat(out_tdfbool(issigned),
			      out_tdfint32(UL((issigned) ? MINSC : 0))),
	    o_make_signed_nat(out_tdfbool(0),
			      out_tdfint32(UL((issigned) ? MAXSC : MAXUSC)))));
}


static void
make_floatsh(void)
{
	o_floating(o_flvar_parms(
		o_make_nat(out_tdfint32(UL(2))),
		o_make_nat(out_tdfint32(UL(MANT_FLOAT))),
		o_make_nat(out_tdfint32(UL(MINEXP_FLOAT))),
		o_make_nat(out_tdfint32(UL(MAXEXP_FLOAT)))
		  )
	)
}


static void
make_doublesh(void)
{
	o_floating(o_flvar_parms(
		o_make_nat(out_tdfint32(UL(2))),
		o_make_nat(out_tdfint32(UL(MANT_DOUBLE))),
		o_make_nat(out_tdfint32(UL(MINEXP_DOUBLE))),
		o_make_nat(out_tdfint32(UL(MAXEXP_DOUBLE)))
		  )
	)
}


Name *
tokforintsh(Bool issigned)
{
	TDF *place = current_TDF;
	int cu = current_Unit;
	Name **t = (issigned) ? &intshtok : &uintshtok;
	if ((*t) != (Name *)0) {
		return *t;
	}
	(*t) = xmalloc(sizeof **t);
	select_tokdef_unit();
	*(*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
		      o_token_def(o_shape, {;}, make_intsh(issigned))
		     );
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return *t;
}


Name *
tokforlongsh(Bool issigned)
{
	TDF *place = current_TDF;
	int cu = current_Unit;
	Name **t = (issigned) ? &longshtok : &ulongshtok;
	if ((*t) != (Name *)0) {
		return *t;
	}
	(*t) = xmalloc(sizeof **t);
	select_tokdef_unit();
	*(*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
		      o_token_def(o_shape, {;}, make_longsh(issigned))
		     );
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return *t;
}


Name *
tokforshortsh(Bool issigned)
{
	TDF *place = current_TDF;
	int cu = current_Unit;
	Name **t = (issigned) ? &shortshtok : &ushortshtok;
	if ((*t) != (Name *)0) {
		return *t;
	}
	(*t) = xmalloc(sizeof **t);
	select_tokdef_unit();
	*(*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
		      o_token_def(o_shape, {;}, make_shortsh(issigned))
		     );
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return *t;
}


Name *
tokforcharsh(Bool issigned)
{
	TDF *place = current_TDF;
	int cu = current_Unit;
	Name **t = (issigned) ? &charshtok : &ucharshtok;
	if ((*t) != (Name *)0) {
		return *t;
	}
	(*t) = xmalloc(sizeof **t);
	select_tokdef_unit();
	*(*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
		      o_token_def(o_shape, {;}, make_charsh(issigned))
		     );
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return *t;
}


Name *
tokforfloatsh(void)
{
	TDF *place = current_TDF;
	int cu = current_Unit;
	Name ** t = &floatshtok;
	if ((*t) != (Name *)0) {
		return *t;
	}
	(*t) = xmalloc(sizeof **t);
	select_tokdef_unit();
	*(*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
		      o_token_def(o_shape, {;}, make_floatsh())
		     );
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return *t;
}


Name *
tokfordoublesh(void)
{
	TDF *place = current_TDF;
	int cu = current_Unit;
	Name **t = &doubleshtok;
	if ((*t) != (Name *)0) {
		return *t;
	}
	(*t) = xmalloc(sizeof **t);
	select_tokdef_unit();
	*(*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
		      o_token_def(o_shape, {;}, make_doublesh())
		     );
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return *t;
}
