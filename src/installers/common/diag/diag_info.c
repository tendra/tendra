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
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: diag_info.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1998/01/11  18:45:07  pwe
 * consistent new/old diags
 *
 * Revision 1.8  1998/01/09  09:30:04  pwe
 * prep restructure
 *
 * Revision 1.7  1997/12/04  19:36:41  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.6  1997/11/06  09:17:56  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.5  1997/10/23  09:21:23  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.4  1997/08/23  13:27:06  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/03/20  17:04:52  currie
 * Dwarf2 diags
 *
Revision 1.2  1997/02/18 12:55:51  currie
NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "readglob.h"
#include "table_fns.h"
#include "basicread.h"
#include "sortmacs.h"
#include "xalloc.h"
#ifdef NEWDIAGS
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "externs.h"
#include "dg_aux.h"
#include "mark_scope.h"
#endif

#include "main_reads.h"
#include "check.h"
#include "dg_fns.h"
#include "diag_fns.h"


/* PROCEDURES */


#ifdef NEWDIAGS


exp diag_locate
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  /* need contents for var locations, old diags */
  exp id = son(e);
  if (isglob (id)) {
    if (brog(id)->dec_u.dec_val.dec_var)
      e = f_contents (brog(id)->dec_u.dec_val.dec_shape, e);
  }
  else {
    if (isvar (id))
      e = f_contents (sh(son(id)), e);
  }
  return e;
}



exp read_exp_to_source
    PROTO_N ( (body) )
    PROTO_T ( exp body )
{
  dg_sourcepos s1, s2;
  int was_within_diags = within_diags;
  within_diags = 1;
  s1 = d_sourcemark();
  s2 = d_sourcemark();
  within_diags = was_within_diags;
  if (s1.file == s2.file) {
    s2.sp_key = SP_SPAN;
    s2.to_file = s2.file;
    s2.to_line = s2.from_line;
    s2.to_column = s2.from_column;
    s2.from_line = s1.from_line;
    s2.from_column = s1.from_column;
  }
  if (name(body) == proc_tag || name(body) == general_proc_tag)
    return body;
  body = f_dg_exp (body, f_singlestep_dg (s1));
  body = f_dg_exp (body, f_sourcepos_dg (s2));
  return body;
}


exp read_diag_id_scope
    PROTO_N ( (body) )
    PROTO_T ( exp body )
{
  dg_idname nam;
  exp acc;
  dg_type typ;
  dg_name dgn;
  int was_within_diags = within_diags;
  within_diags = 1;
  nam = f_dg_sourcestring_idname (d_tdfstring());
  acc = hold_check (d_exp());
  typ = d_diag_type();
  within_diags = was_within_diags;
  dgn = f_dg_object_name (
	nam,
	f_dg_null_sourcepos,
	typ,
	yes_exp_option (diag_locate (acc)),
	no_dg_accessibility_option);

  if (isparam(son(acc)) || (son(son(acc)) != nilexp &&
		name(son(son(acc))) == chvar_tag &&
		shape_size(sh(son(son(acc)))) < 32 &&
		name(son(son(son(acc)))) == cont_tag &&
		name(son(son(son(son(acc))))) == name_tag &&
		isparam (son(son(son(son(son(acc)))))) )) {
    dg_info x = dgf(body);
    if (x && x->key == DGA_PARAMS) {
      dgn->next = x->data.i_param.args;
      x->data.i_param.args = dgn;
    }
    else {
      body = f_dg_exp (body, f_params_dg (dgn, no_exp_option));
    }
  }
  else {
    body = f_dg_exp (body, f_name_decl_dg (dgn));
    mark_scope (body);
  }
  return (body);
}


exp read_diag_type_scope
    PROTO_N ( (body) )
    PROTO_T ( exp body )
{
  dg_idname nam;
  dg_type typ;
  dg_name dgn;
  int was_within_diags = within_diags;
  within_diags = 1;
  nam = f_dg_sourcestring_idname (d_tdfstring());
  typ = d_diag_type();
  within_diags = was_within_diags;
  dgn = f_dg_type_name (
	nam,
	f_dg_null_sourcepos,
	no_dg_accessibility_option,
	typ,
	f_false,
	no_bool_option,
	no_dg_constraint_list_option);
  body = f_dg_exp (body, f_name_decl_dg (dgn));
  mark_scope2 (body);
  return body;
}


#else

diag_info * read_exp_to_source
    PROTO_Z ()
{
  diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));

  new->key = DIAG_INFO_SOURCE;
  new->data.source.beg 	= d_sourcemark();
  new->data.source.end 	= d_sourcemark();

  return new;
}

diag_info * read_diag_id_scope
    PROTO_Z ()
{
  diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));

  new->key 		= DIAG_INFO_ID;
  new->data.id_scope.nme = d_tdfstring();
  new->data.id_scope.access = hold_check(d_exp());
  IGNORE hold(hold(new->data.id_scope.access));
  new->data.id_scope.typ = d_diag_type();
  return (new);
}

diag_info * read_diag_type_scope
    PROTO_Z ()
{
  diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));

  new->key 		= DIAG_INFO_TYPE;
  new->data.type_scope.nme = d_tdfstring();
  new->data.type_scope.typ = d_diag_type();
  return (new);
}

diag_info * read_diag_tag_scope
    PROTO_Z ()
{
  diag_info * new = (diag_info *) xcalloc(1,sizeof(diag_info));

  new->key 		= DIAG_INFO_TAG;
  new->data.tag_scope.nme = d_tdfstring();
  new->data.tag_scope.typ = d_diag_type();
  return (new);
}


#endif
