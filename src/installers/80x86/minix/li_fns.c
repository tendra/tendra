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
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: li_fns.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:17  currie
 * Initial revision
 *
***********************************************************************/





#include "config.h"
#include "common_types.h"
#include "flags.h"
#include "messages_li.h"
#include "natmacs.h"
#include "main_reads.h"
#include "externs.h"

#if is80x86
#include "assembler.h"
#include "localflags.h"
#define use_link_stuff 0
#endif

#if use_link_stuff
extern weak_cell *weak_list;
#include "out.h"
#endif

#include "xalloc.h"
#include "readglob.h"
#include "basicread.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "machine.h"


/* PROCEDURES */

extern void out_rename PROTO_S ( ( char *, char * ) ) ;

static char * id_prefix
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  char * r;
  int l1, l2;
  l1 = (int)strlen(name_prefix);
  if (l1==0)
     return s;
  l2 = (int)strlen(s);
  r = (char *)xcalloc(l1+l2+1, sizeof(char));
  IGNORE strcpy(r, name_prefix);
  IGNORE strcpy(&r[l1], s);
  return r;
}

linkinfo f_make_weak_defn
    PROTO_N ( (e1, e2) )
    PROTO_T ( exp e1 X exp e2 )
{
#if use_link_stuff
  weak_cell * wc = (weak_cell *)xmalloc(sizeof(weak_cell));

  wc -> weak_id = brog(son(e1))-> dec_u.dec_val.dec_id;
  wc -> val_id = brog(son(e2))-> dec_u.dec_val.dec_id;
  brog(son(e2))-> dec_u.dec_val.isweak = 1;
  wc -> next = weak_list;
  weak_list = wc;

#endif
  kill_exp(e1, e1);
  kill_exp(e2, e2);
  return 0;
}


linkinfo f_make_weak_symbol
    PROTO_N ( (id, e) )
    PROTO_T ( tdfstring id X exp e )
{
#if use_link_stuff
  char * * lid = &brog(son(e))-> dec_u.dec_val.dec_id;
  char * nid = id_prefix(id.ints.chars);
  brog(son(e))-> dec_u.dec_val.isweak = 1;
  brog(son(e))-> dec_u.dec_val.extnamed = 1;
  outs(".weak ");
  outs(nid);
  outnl();
  out_rename(*lid, nid);
  *lid = nid;
#endif
  kill_exp(e, e);
  return 0;
}

linkinfo f_make_comment
    PROTO_N ( (id) )
    PROTO_T ( tdfstring id )
{
#if use_link_stuff
  outs(".ident \"");
  outs(id_prefix(id.ints.chars));
  outs("\"");
  outnl();
#endif
  return 0;
}

linkinfo f_static_name_def
    PROTO_N ( (e, id) )
    PROTO_T ( exp e X tdfstring id )
{
  char * * oldid = &brog(son(e))-> dec_u.dec_val.dec_id;
  char * newid = id_prefix(id.ints.chars);

  if (name(e) != name_tag || !isglob(son(e)))
    {
      failer(ILLEGAL_STATIC);
      kill_exp(e, e);
      return 0;
    };

  if (separate_units)
     failer(INCOMPATIBLE_U);
  else
     out_rename(*oldid, newid);

  *oldid = newid;
  kill_exp(e, e);
  return 0;
}

void init_linkinfo
    PROTO_Z ()
{
  return;
}

linkinfo f_dummy_linkinfo;

linkinfo_list new_linkinfo_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

linkinfo_list add_linkinfo_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( linkinfo_list list X linkinfo elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}


void start_make_linkinfo_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtypes) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtypes )
{
  int i;
  UNUSED(no_of_diagtypes);

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  return;
}

int f_make_linkinfo_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i)
   {
    if (unit_ind_tags[i] == (dec*)0)
      unit_ind_tags[i] = &unit_tagtab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i)
   {
    if (unit_ind_als[i] == (aldef*)0)
      unit_ind_als[i] = &unit_altab[j++];
   };
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_linkinfo_list();
  end_bytestream();

  xfree((void*)unit_ind_tokens);
  xfree((void*)unit_ind_tags);
  xfree((void*)unit_ind_als);
  xfree((void*)unit_labtab);
  xfree((void*)unit_toktab);
  xfree((void*)unit_tagtab);

  return 0;
}

linkinfo_props f_make_linkinfos
    PROTO_N ( (nl, tds) )
    PROTO_T ( tdfint nl X linkinfo_list tds )
{
  UNUSED(nl); UNUSED(tds);
  return 0;
}
