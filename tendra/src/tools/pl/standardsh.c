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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
#include "config.h"
#include "util.h"
#include "streams.h"
#include "units.h"
#include "encodings.h"
#include "enc_nos.h"
#include "defs.h"
#include "errors.h"
#include "standardsh.h"


static Name * intshtok = (Name*)0;
static Name * longshtok = (Name*)0;
static Name * shortshtok = (Name*)0;
static Name * charshtok = (Name*)0;
static Name * uintshtok = (Name*)0;
static Name * ulongshtok = (Name*)0;
static Name * ushortshtok = (Name*)0;
static Name * ucharshtok = (Name*)0;
static Name * floatshtok = (Name*)0;
static Name * doubleshtok = (Name*)0;

static TDFlist * extra_toks = (TDFlist *) 0;


void
select_tokdef_unit()
{
	/* can define a token while in a token definition in shapes */
	if (current_Unit != tokdef_unit) {
		SELECT_UNIT(tokdef_unit);
	}
	else {
		TDFlist * tl = MALLOC(TDFlist);
		tl->next = extra_toks;
		extra_toks = tl;
		current_TDF = &tl->t;
		INIT_TDF(current_TDF);
		current_Unit = tokdef_unit;
	}
}


void
add_extra_toks()
{
	SELECT_UNIT(tokdef_unit);
	while (extra_toks != (TDFlist *) 0) {
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
									out_tdfint32(UL((issigned)?MINSI:0)))
				  ,
				  o_make_signed_nat(out_tdfbool(0),
									out_tdfint32(UL((issigned)?MAXSI:MAXUSI)))
				  )
		);
}


static void
make_longsh(Bool issigned)
{
	o_integer(o_var_limits(
				  o_make_signed_nat(out_tdfbool(issigned),
									out_tdfint32(UL((issigned)?MINSL:0)))
				  ,
				  o_make_signed_nat(out_tdfbool(0),
									out_tdfint32(UL((issigned)?MAXSL:MAXUSL)))
				  )
		);
}


static void
make_shortsh(Bool issigned)
{
	o_integer(o_var_limits(
				  o_make_signed_nat(out_tdfbool(issigned),
									out_tdfint32(UL((issigned)?MINSS:0)))
				  ,
				  o_make_signed_nat(out_tdfbool(0),
									out_tdfint32(UL((issigned)?MAXSS:MAXUSS)))
				  )
		);
}


static void
make_charsh(Bool issigned)
{
	o_integer(o_var_limits(
				  o_make_signed_nat(out_tdfbool(issigned),
									out_tdfint32(UL((issigned)?MINSC:0)))
				  ,
				  o_make_signed_nat(out_tdfbool(0),
									out_tdfint32(UL((issigned)?MAXSC:MAXUSC)))
				  )
		);
}


static void
make_floatsh()
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
make_doublesh()
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
	TDF * place = current_TDF;
	int cu = current_Unit;
	Name ** t = (issigned)?&intshtok:&uintshtok;
	if ((*t) != (Name*)0) return (*t);
	(*t) = MALLOC(Name);
	select_tokdef_unit();
	* (*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
				  o_token_def(o_shape, {;}, make_intsh(issigned))
		);
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return (*t);
}


Name *
tokforlongsh(Bool issigned)
{
	TDF * place = current_TDF;
	int cu = current_Unit;
	Name ** t = (issigned)?&longshtok:&ulongshtok;
	if ((*t) != (Name*)0) return (*t);
	(*t) = MALLOC(Name);
	select_tokdef_unit();
	* (*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
				  o_token_def(o_shape, {;}, make_longsh(issigned))
		);
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return (*t);
}


Name *
tokforshortsh(Bool issigned)
{
	TDF * place = current_TDF;
	int cu = current_Unit;
	Name ** t = (issigned)?&shortshtok:&ushortshtok;
	if ((*t) != (Name*)0) return (*t);
	(*t) = MALLOC(Name);
	select_tokdef_unit();
	* (*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
				  o_token_def(o_shape, {;}, make_shortsh(issigned))
		);
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return (*t);
}


Name *
tokforcharsh(Bool issigned)
{
	TDF * place = current_TDF;
	int cu = current_Unit;
	Name ** t = (issigned)?&charshtok:&ucharshtok;
	if ((*t) != (Name*)0) return (*t);
	(*t) = MALLOC(Name);
	select_tokdef_unit();
	* (*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
				  o_token_def(o_shape, {;}, make_charsh(issigned))
		);
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return (*t);
}


Name *
tokforfloatsh()
{
	TDF * place = current_TDF;
	int cu = current_Unit;
	Name ** t = &floatshtok;
	if ((*t) != (Name*)0) return (*t);
	(*t) = MALLOC(Name);
	select_tokdef_unit();
	* (*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
				  o_token_def(o_shape, {;}, make_floatsh())
		);
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return (*t);
}


Name *
tokfordoublesh()
{
	TDF * place = current_TDF;
	int cu = current_Unit;
	Name ** t = &doubleshtok;
	if ((*t) != (Name*)0) return (*t);
	(*t) = MALLOC(Name);
	select_tokdef_unit();
	* (*t) = next_name(tok_ent);
	o_make_tokdef(out_tdfint32(UL((*t)->unit_name)), {},
				  o_token_def(o_shape, {;}, make_doublesh())
		);
	INC_LIST;
	current_Unit = cu;
	RESET_TDF(place);
	return (*t);
}
