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
$Log: mark_scope.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1998/01/09  09:30:07  pwe
 * prep restructure
 *
 * Revision 1.7  1997/10/28  10:12:38  pwe
 * local location support
 *
 * Revision 1.6  1997/10/23  09:21:26  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.5  1997/08/23  13:27:24  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/02  12:55:05  currie
 * includes before ifdef
 *
Revision 1.3  1997/03/20 17:04:53  currie
Dwarf2 diags

Revision 1.2  1997/02/18 12:55:52  currie
NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "tags.h"
#include "xalloc.h"
#include "externs.h"
#include "dg_aux.h"
#include "mark_scope.h"


#ifdef NEWDIAGS

int doing_mark_scope = 0;

void mark_scope
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
	/* called by read_diag_id_scope; dgf(e) holds DIAG_INFO_ID */
  dg_info d = dgf(e);
  dg_info * ptr;
  exp id;
  if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_OBJECT)
    return;
  id = son(d->data.i_nam.dnam->data.n_obj.obtain_val);
  if (name(id) == cont_tag)
    id = son(id);
  if (name(id) != name_tag)
    return;
  id = son(id);
  if (isparam(id))
    return;
  ptr = &(d->more);
  d = nildiag;
  while (*ptr && (*ptr)->key != DGA_SCOPE)
    ptr = &((*ptr)->more);
  if (!*ptr && name(e) == seq_tag && name(son(son(e))) == ass_tag
		&& last(son(son(e))) && name(bro(son(e))) != ident_tag ) {
    ptr = &dgf(bro(son(e)));
    while (*ptr && (*ptr)->key != DGA_SCOPE)
      ptr = &((*ptr)->more);
  }
  if (*ptr) {
    d = *ptr;
    *ptr = d->more;
  }
  else {
    d = f_lexical_block_dg (no_dg_idname_option, no_dg_sourcepos_option);
    d->data.i_scope.begin_st = (long)(-1);
    doing_mark_scope = 1;
  }
  /* if (isglob(id)) */ {
    d->more = dgf(e);
    dgf(e) = d;
  }
#if 0
  else {
    exp def = son(id);
    if (dgf(def) && dgf(def)->key == DGA_SRC)
      dgf(e)->data.i_nam.dnam->whence = dgf(def)->data.i_src.startpos;
    d->more = dgf(id);
    dgf(id) = d;
  }
#endif
  return;
}

void mark_scope2
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
	/* called by read_diag_type_scope; dgf(e) holds DIAG_INFO_ID */
  dg_info d = dgf(e);
  dg_info * ptr;
  if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_TYPE)
    return;
  ptr = &(d->more);
  d = nildiag;
  while (*ptr && (*ptr)->key != DGA_SCOPE)
    ptr = &((*ptr)->more);
  if (*ptr) {
    d = *ptr;
    *ptr = d->more;
  }
  else {
    d = f_lexical_block_dg (no_dg_idname_option, no_dg_sourcepos_option);
    d->data.i_scope.begin_st = (long)(-1);
    doing_mark_scope = 1;
  }
  d->more = dgf(e);
  dgf(e) = d;
  return;
}

void correct_mark_scope
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  dg_info d = nildiag;
  dg_info * ptr = &(dgf(bro(son(e))));
  while (*ptr && (*ptr)->key != DGA_SCOPE)
    ptr = &((*ptr)->more);
  if (*ptr) {
    d = *ptr;
    *ptr = d->more;
  }
  if (d) {
    d->more = dgf(e);
    dgf(e) = d;
  }
  return;
}


#else


/* PROCEDURES */

static exp previous_scope
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  if (!last(e) || bro(e) == nilexp)
    return nilexp;

  if (name(bro(e)) == diagnose_tag && (props(bro(e)) & 0x7) == 1)
    return previous_scope(bro(e));

  if (name(bro(e)) == diagnose_tag)
    return bro(e);

  if (name(bro(e)) == ident_tag && last(bro(e)))
   {
     if (bro(bro(e)) == nilexp)
       return nilexp;

     if (name(bro(bro(e))) == diagnose_tag &&
           (props(bro(bro(e))) & 0x7) == 1)
       return previous_scope(bro(bro(e)));

     if (name(bro(bro(e))) == diagnose_tag)
       return bro(bro(e));

     return nilexp;
   };

  return nilexp;
}


static int param_scope
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  diag_info * d = dno(e);
  if (d -> key == DIAG_INFO_ID)
    return isparam(son(d -> data.id_scope.access));
  return 0;
}

static int needs_hiding
    PROTO_N ( (a, b) )
    PROTO_T ( exp a X exp b )
{
  diag_info * da = dno(a);
  diag_info * db = dno(b);

  if (da -> key != db -> key)
    return 0;

  switch (da -> key)
    {
      case DIAG_INFO_ID:
         return !strcmp(da -> data.id_scope.nme.ints.chars,
                        db -> data.id_scope.nme.ints.chars);
      case DIAG_INFO_TYPE:
         return !strcmp(da -> data.type_scope.nme.ints.chars,
                        db -> data.type_scope.nme.ints.chars);
      case DIAG_INFO_TAG:
         return !strcmp(da -> data.tag_scope.nme.ints.chars,
                        db -> data.tag_scope.nme.ints.chars);
      default: return 0;
    };
}

void mark_scope
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  exp scope = e;

  if (param_scope(e))
     return;

  while (1)
   {
      scope = previous_scope(scope);

      if (scope == nilexp || param_scope(scope) ||
             needs_hiding(e, scope))
       {
         props(e) = (prop)(props(e) | 0x80);
         return;
       };

      if (props(scope) & 0x80)
         return;

   };
}

#endif
