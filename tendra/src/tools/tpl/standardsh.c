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
$Date: 1998/01/17 15:57:25 $
$Revision: 1.1.1.1 $
$Log: standardsh.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  16:00:58  currie
 * put <stdlib> at top of headers
 *
 * Revision 1.2  1995/06/08  09:13:54  currie
 * Added sigs to tokdecs/defs
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:36  currie
 * Added banner
 *
***********************************************************************/
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


void select_tokdef_unit
    PROTO_Z ()
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


void add_extra_toks
    PROTO_Z ()
{
	SELECT_UNIT(tokdef_unit);
	while (extra_toks != (TDFlist *) 0) {
		append_TDF(&extra_toks->t, 1);
		INC_LIST;
		extra_toks = extra_toks->next;
	}
}


static void make_intsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
{
	o_integer(o_var_limits(
		  o_make_signed_nat(out_tdfbool(issigned),
		   	out_tdfint32(UL((issigned)?MINSI:0)))
		   ,
		   o_make_signed_nat(out_tdfbool(0),
		   	out_tdfint32(UL((issigned)?MAXSI:MAXUSI)) )
		  )
	);
}


static void make_longsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
{
	o_integer(o_var_limits(
		   o_make_signed_nat(out_tdfbool(issigned),
		   	out_tdfint32(UL((issigned)?MINSL:0)))
		   ,
		   o_make_signed_nat(out_tdfbool(0),
		   	out_tdfint32(UL((issigned)?MAXSL:MAXUSL)) )
		  )
	);
}


static void make_shortsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
{
	o_integer(o_var_limits(
		   o_make_signed_nat(out_tdfbool(issigned),
		   	out_tdfint32(UL((issigned)?MINSS:0)))
		   ,
		   o_make_signed_nat(out_tdfbool(0),
		   	out_tdfint32(UL((issigned)?MAXSS:MAXUSS)) )
		  )
	);
}


static void make_charsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
{
	o_integer(o_var_limits(
		   o_make_signed_nat(out_tdfbool(issigned),
		   	out_tdfint32(UL((issigned)?MINSC:0)))
		   ,
		   o_make_signed_nat(out_tdfbool(0),
		   	out_tdfint32(UL((issigned)?MAXSC:MAXUSC)) )
		  )
	);
}


static void make_floatsh
    PROTO_Z ()
{
	o_floating(o_flvar_parms(
		o_make_nat(out_tdfint32(UL(2))),
		o_make_nat(out_tdfint32(UL(MANT_FLOAT))),
		o_make_nat(out_tdfint32(UL(MINEXP_FLOAT))),
		o_make_nat(out_tdfint32(UL(MAXEXP_FLOAT)))
		   )
	)
}


static void make_doublesh
    PROTO_Z ()
{
	o_floating(o_flvar_parms(
		o_make_nat(out_tdfint32(UL(2))),
		o_make_nat(out_tdfint32(UL(MANT_DOUBLE))),
		o_make_nat(out_tdfint32(UL(MINEXP_DOUBLE))),
		o_make_nat(out_tdfint32(UL(MAXEXP_DOUBLE)))
		   )
	)
}


Name * tokforintsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
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


Name * tokforlongsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
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


Name * tokforshortsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
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


Name * tokforcharsh
    PROTO_N ( (issigned) )
    PROTO_T ( Bool issigned )
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


Name * tokforfloatsh
    PROTO_Z ()
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


Name * tokfordoublesh
    PROTO_Z ()
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
