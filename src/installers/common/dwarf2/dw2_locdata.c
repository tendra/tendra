/*
    		 Crown Copyright (c) 1998

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
$Author: pwe $
$Date: 1998/03/15 16:00:36 $
$Revision: 1.2 $
$Log: dw2_locdata.c,v $
 * Revision 1.2  1998/03/15  16:00:36  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.1  1998/03/11  11:03:46  pwe
 * DWARF optimisation info
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "dg_types.h"
#include "dw2_config.h"
#include "dw2_basic.h"
#include "dw2_codes.h"
#include "dw2_iface.h"
#include "dw2_info.h"
#include "expmacs.h"
#include "tags.h"
#include "basicread.h"
#include "xalloc.h"
#include "externs.h"
#include "dg_aux.h"
#include "dw2_locdata.h"


/*	Location list information is collected for each object, held via
	fields of the 'obtain_value' exp (which is a hold_tag). last is set
	if the object is master of a new location. bro is used to hold 
	references to other objects that share this location (as a bro list).
	no is label for shared location set.
		pt holds other more temporary uses (via ll_item).
*/



#define	LOp_Non_Current 1
#define	LOp_Locked	2
#define	LOp_Const	3
#define	LOp_Shared	4
#define	LOp_Portion	5


typedef enum
{
  LL_OPTLOCK = 1,
  LL_CONST,
  LL_RET,
  LL_REGSHARE,
  LL_MASTERSHARE
} loclist_key;

typedef struct rs_s
{
  long			start;
  long			end;
  long			share;
  dg_name		nm;
  int			reg;
  struct rs_s *		next_share;
  struct rs_s *		next_loc;
} * regshare_item;

typedef struct rsl_s
{
  dg_name		alloc;
  int			reg;
  regshare_item		items;
  struct rsl_s *	next;
} * regshare_list;

typedef struct ll_s
{
  int			key	: 8;
  int			open	: 1;
  int			has_inner : 1;
  union
  {
    dg_info		d;
    retrec *		r;
    regshare_item	l;
  } u;
  struct ll_s *		next;
  struct ll_s *		inner;
} * ll_item;

static ll_item * ll_root
    PROTO_N ( (nm) )
    PROTO_T ( dg_name nm )
{
  exp x = nm->data.n_obj.obtain_val;
  exp * ref = &(pt(x));
  return (ll_item *)((void *)ref);
}

static ll_item new_ll_item
    PROTO_N ( (k, o) )
    PROTO_T ( loclist_key k X int o )
{
  ll_item ans = (ll_item) xmalloc (sizeof (struct ll_s));
  ans->key = k;
  ans->open = ans->has_inner = o;
  ans->next = (ll_item)0;
  ans->inner = (ll_item)0;
  return ans;
}

static regshare_list all_regshares = (regshare_list)0;

void * dw_new_regshare
    PROTO_N ( (nm, reg) )
    PROTO_T ( dg_name nm X int reg )
{
  regshare_list ans = (regshare_list) xmalloc (sizeof (struct rsl_s));
  ans->alloc = nm;
  ans->reg = reg;
  ans->items = (regshare_item)0;
  ans->next = all_regshares;
  all_regshares = ans;
  return (void *)ans;		/* actual type local to this file */
}

void dw_add_regshare
    PROTO_N ( (w, nm, start, end) )
    PROTO_T ( void * w X dg_name nm X long start X long end )
{
  regshare_list holder = (regshare_list)w;
  regshare_item item = (regshare_item) xmalloc (sizeof (struct rs_s));
  item->start = start;
  item->end = end;
  item->share = 0;
  item->nm = nm;
  item->next_share = holder->items;
  item->next_loc = (regshare_item)0;
  holder->items = item;
  return;
}


obj_list * local_objects = (obj_list *)0;

static void check_taggable
    PROTO_N ( (nm) )
    PROTO_T ( dg_name nm )
{
  if (!nm->mor || !nm->mor->this_tag)
    IGNORE f_dg_tag_name (gen_tg_tag (), nm);
  return;
}


void set_locdata
    PROTO_N ( (this_obl) )
    PROTO_T ( obj_list this_obl )
{
  dg_name this_nm = this_obl.obj;
  while (this_nm) {
    if (this_nm->key == DGN_OBJECT) {
      exp x = this_nm->data.n_obj.obtain_val;
      exp id;
      if (x && (id = dw_has_location (son(x)), id)) {
	if (isglob(id)) {
	  dg_name master = brog(id)->dec_u.dec_val.diag_info;
	  if (!master)
	    master = brog(id)->dec_u.dec_val.diag_info = this_nm;
	  if (master == this_nm) {
	    setlast (x);
	    no(x) = next_dwarf_label ();
	  }
	  else {
	    exp y = master->data.n_obj.obtain_val;
	    setbro (x, bro(y));
	    setbro (y, (exp)((void *)this_nm));
	    no(x) = no(y);
	    check_taggable (master);
	    check_taggable (this_nm);
	  }
	}
	else {
	  int found = 0;
	  obj_list * obl = local_objects;
	  while (obl && !found) {
	    dg_name nm = obl->obj;
	    while (nm) {
	      if (nm->key == DGN_OBJECT) {
		exp y = nm->data.n_obj.obtain_val;
		if (y && last(y) && dw_has_location (son(y)) == id) {
		  setbro (x, bro(y));
		  setbro (y, (exp)((void *)this_nm));
		  no(x) = no(y);
		  check_taggable (nm);
		  check_taggable (this_nm);
		  found = 1;
		  break;
		}
	      }
	      if (!obl->islist)
		break;
	      nm = nm->next;
	    }
	    obl = obl->next;
	  }
	  if (!found) {
	    setlast (x);
	    no(x) = next_dwarf_label ();
	    dw_allocated (this_nm, id);
	  }
	}
      }
      else
	no(x) = 0;
    }
    if (!this_obl.islist)
      break;
    this_nm = this_nm->next;
  }
}


void close_locdata
    PROTO_N ( (this_obl) )
    PROTO_T ( obj_list this_obl )
{
  dg_name this_nm = this_obl.obj;
  while (this_nm) {
    if (this_nm->key == DGN_OBJECT) {
      exp x = this_nm->data.n_obj.obtain_val;
      if (x && last(x))
	dw_deallocated (this_nm);
    }
    if (!this_obl.islist)
      break;
    this_nm = this_nm->next;
  }
}


dg_name find_equiv_object
    PROTO_N ( (e, isc) )
    PROTO_T ( exp e X int isc )
{
  obj_list * obl = local_objects;
  while (obl) {
    dg_name nm = obl->obj;
    while (nm) {
      if (nm->key == DGN_OBJECT) {
	exp x = nm->data.n_obj.obtain_val;
	if (isc) {
	  if (x && name(son(x)) == cont_tag && 
		dw_loc_equivalence (e, son(son(x))))
	    return nm;
	}
	else {
	  if (x && dw_loc_equivalence (e, son(x)))
	    return nm;
	}
      }
      if (!obl->islist)
	break;
      nm = nm->next;
    }
    obl = obl->next;
  }
  return (dg_name)0;
}



static dg_name find_simple_object
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{				/* e is name_tag for required object */
  obj_list * obl = local_objects;
  while (obl) {
    dg_name nm = obl->obj;
    while (nm) {
      if (nm->key == DGN_OBJECT) {
	exp x = nm->data.n_obj.obtain_val;
	while (x && (name(x) == hold_tag || name(x) == cont_tag || 
		name(x) == reff_tag))
	  x = son(x);
	if ((x) && name(x) == name_tag && son(x) == son(e) &&
		(no(x) <= no(e)) && 
		(no(x) + shape_size(sh(x))) >= (no(e) + shape_size(sh(e)) ))
	  return nm;
      }
      if (!obl->islist)
	break;
      nm = nm->next;
    }
    obl = obl->next;
  }
  return (dg_name)0;
}


void set_optim_objects
    PROTO_N ( (optim, start) )
    PROTO_T ( dg_info optim X int start )
{
  objset * obj = optim->data.i_optim.objs;
  while (obj) {
    dg_name nm = obj->tg->p.nam;
    if (start) {
      ll_item * l = ll_root (nm);
      while (*l) {
	if ((*l)->open)
	  l = &((*l)->inner);
	else
	  l = &((*l)->next);
      }
      *l = new_ll_item (LL_OPTLOCK, 1);
      (*l)->u.d = optim;
    }
    else {
      ll_item l = * ll_root (nm);
      while (l->key != LL_OPTLOCK || l->u.d != optim) {
	if ((l)->open)
	  l = l->inner;
	else
	  l = l->next;
      }
      l->open = 0;
    }
    obj = obj->next;
  }
  return;
}


void set_remval_object
    PROTO_N ( (rmv) )
    PROTO_T ( dg_info rmv )
{
  dg_name nm = find_simple_object (son (rmv->data.i_remval.var));
  if (nm) {
    ll_item * l = ll_root (nm);
    while (*l) {
      if ((*l)->open)
	l = &((*l)->inner);
      else
	l = &((*l)->next);
    }
    *l = new_ll_item (LL_CONST, 0);
    (*l)->u.d = rmv;
  }
  return;
}


void set_obj_rets
    PROTO_N ( (rec) )
    PROTO_T ( retrec * rec )
{
  obj_list * obl = local_objects;
  while (obl) {
    dg_name nm = obl->obj;
    while (nm) {
      if (nm->key == DGN_OBJECT) {
	exp x = nm->data.n_obj.obtain_val;
	while (x && (name(x) == hold_tag || name(x) == cont_tag || 
		name(x) == reff_tag))
	  x = son(x);
	if ((x) && name(x) == name_tag && !isdiscarded(x) && 
					!isglob(son(x))) {
	  ll_item * l = ll_root (nm);
	  while (*l) {
	  if ((*l)->open)
	    l = &((*l)->inner);
	  else
	    l = &((*l)->next);
	  }
	  *l = new_ll_item (LL_RET, 0);
	  (*l)->u.r = rec;
	}
      }
      if (!obl->islist)
	break;
      nm = nm->next;
    }
    obl = obl->next;
  }
  return;
}


static ll_item find_ll_item
    PROTO_N ( (nm, k, force) )
    PROTO_T ( dg_name nm X loclist_key k X int force )
{
  ll_item * ll = ll_root (nm);
  ll_item l = *ll;
  while (l && l->key != k)
    l = l->next;
  if (!l && force) {
    l = new_ll_item (k, 0);
    l->u.l = (regshare_item)0;
    l->next = *ll;
    *ll = l;
  }
  return l;
}

static void out_regshare_set
    PROTO_N ( (it) )
    PROTO_T ( regshare_item it )
{
  regshare_item this = it;
  while (this) {
    dg_name nm = this->nm;
    if (nm) {
      regshare_item look = it;
      while (look->nm != nm)	/* avoid duplicates */
	look = look->next_share;
      if (look == this)
	dw_at_ext_address (nm->mor->this_tag);
    }
    this = this->next_share;  
  }
  return;
}



void init_dw_locdata
    PROTO_Z ()
{
  all_regshares = (regshare_list)0;
  local_objects = (obj_list *)0;
  dw_all_deallocated ();
  return;
}

void complete_dw_locdata
    PROTO_Z ()
{
  regshare_list top_l = all_regshares;
  while (top_l) {
    dg_name master = top_l->alloc;
    int reg = top_l->reg;
    regshare_item regitem = top_l->items;
    dg_name nm;
    if (master) {
      while (regitem) {
	nm = master;
	do {
	  if (regitem->nm == nm) {
	    regitem->nm = (dg_name)0;
	    break;
	  }
	  nm = (dg_name)((void *)bro(nm->data.n_obj.obtain_val));
	} while (nm);
	if (!nm) {	/* regitem not in allocation shareset */
	  ll_item l = find_ll_item (master, LL_MASTERSHARE, 1);
	  if (!l->u.l)
	    l->u.l = regitem;	/* start of extra share list for master */
	  regitem->share = no(master->data.n_obj.obtain_val);
	  regitem->reg = reg;
	  l = find_ll_item (regitem->nm, LL_REGSHARE, 1);
	  regitem->next_loc = l->u.l;
	  l->u.l = regitem;
	  check_taggable (regitem->nm);
	  check_taggable (master);
	}
	regitem = regitem->next_share;
      }
    }
    else {
      long share = 0;
      master = nm = (dg_name)0;
      while (regitem) {
	if (!master)
	  master = regitem->nm;
	if (!nm)
	  nm = regitem->nm;
	if (nm != master) {
	  share = next_dwarf_label ();
	  break;
	}
	regitem = regitem->next_share;
      }
      regitem = top_l->items;
      while (regitem) {
	ll_item l = find_ll_item (regitem->nm, LL_REGSHARE, 1);
	regitem->share = share;
	if (share)
	  check_taggable (regitem->nm);
	regitem->reg = reg;
	regitem->next_loc = l->u.l;
	l->u.l = regitem;
        regitem = regitem->next_share;
      }
      if (share) {
	enter_section ("debug_loc");
	out_dwf_label (share, 1);
	out_regshare_set (top_l->items);
	exit_section ();
      }
    }
    top_l = top_l->next;
  }
  return;
}



static int obj_decide
    PROTO_N ( (l) )
    PROTO_T ( ll_item l )
{
  int ans = 0, x;
  while (l && ans < 2) {
    switch (l->key) {
      case LL_OPTLOCK:
      case LL_CONST:
      case LL_MASTERSHARE:
	return 2;
      case LL_RET: {
	if (!ans)
	  ans = 1;
	break;
      }
      case LL_REGSHARE: {
	regshare_item rs = l->u.l;
	while (rs && ans<2) {
	  if (rs->share)
	    ans = 2;
	  else
	  if (!ans)
	    ans = 1;
	  rs = rs->next_loc;
	}
	break;
      }
    }
    if (l->has_inner && (x = obj_decide (l->inner), x > ans))
      ans = x;
    l = l->next;
  }
  return ans;
}
    
int decide_ll_type
    PROTO_N ( (x) )
    PROTO_T ( exp x )
{			/* 1 if need location list, 2 if extension list */
  ll_item l = (ll_item)((void *)(pt(x)));
  if ((last(x) && bro(x)) || (!last(x) && no(x)))
				/* main location is shared */
    return 2;
  else
    return obj_decide (l);
}


static long startlab;
static int ll_ok;
static exp obval;

static void loclist_portion
    PROTO_N ( (l) )
    PROTO_T ( ll_item l )
{
  while (l) {
    switch (l->key) {
      case LL_CONST: {
	ll_ok = 0;
	break;
      }
      case LL_RET: {
	long endlab = l->u.r->lab;
	if (ll_ok && endlab != startlab) {
	  out_loc_range (startlab, endlab, 0);
	  dw2_locate_exp (obval, 0, 1);
	}
	startlab = l->u.r->over;
	break;
      }
      case LL_REGSHARE: {
	regshare_item rs = l->u.l;
	while (rs) {
	  out_loc_range (rs->start, rs->end, 1);
	  out16 (); 
	  if (rs->reg < 32) {
	    outn ((long)1); outnl();
	    out8 (); outn ((long)(DW_OP_reg0 + rs->reg));
	  }
	  else {
	    outn ((long)(1 + uleb128_length((unsigned long)rs->reg)));
	    outnl(); out8 ();
	    outn ((long)DW_OP_regx); outs (", ");
	    uleb128((unsigned long)rs->reg);
	  }
	  outnl();
	  rs = rs->next_loc;
	}
      }
      default:
	break;
    }
    if (l->has_inner)
      loclist_portion (l->inner);
    l = l->next;
  }
  return;
}

void out_obj_loclist
    PROTO_N ( (l1, l2, x) )
    PROTO_T ( long l1 X long l2 X exp x )
{
  ll_item l = (ll_item)((void *)(pt(x)));
  startlab = l1;
  ll_ok = 1;
  obval = son(x);
  loclist_portion (l);
  if (ll_ok && l2 != startlab) {
    out_loc_range (startlab, l2, 0);
    dw2_locate_exp (obval, 0, 1);
  }
  return;
}


static void extlist_portion
    PROTO_N ( (l) )
    PROTO_T ( ll_item l )
{
  while (l) {
    switch (l->key) {
      case LL_CONST: {
	long here = l->u.d->data.i_remval.lo_pc;
	if (ll_ok && here != startlab) {
	  out_loc_range (startlab, here, 0);
	  dw_at_data (1, LOp_Const);
	  dw_out_const (obval);
	}
	startlab = here;
	ll_ok = 1;
	obval = l->u.d->data.i_remval.val;
	break;
      }
      case LL_OPTLOCK: {
	out_loc_range (l->u.d->data.i_optim.lo_pc,
			l->u.d->data.i_optim.hi_pc, 0);
	dw_at_data (1, LOp_Locked);
	dw_at_data (1, l->u.d->data.i_optim.reason);
	break;
      }
      case LL_REGSHARE: {
	regshare_item rs = l->u.l;
	while (rs) {
	  if (rs->share) {
	    out_loc_range (rs->start, rs->end, 1);
	    dw_at_data (1, LOp_Shared);
	    dw_at_address (rs->share);
	  }
	  rs = rs->next_loc;
	}
      }
      default:
	break;
    }
    if (l->has_inner)
      loclist_portion (l->inner);
    l = l->next;
  }
  return;
}

void out_obj_extloclist
    PROTO_N ( (l1, l2, x) )
    PROTO_T ( long l1 X long l2 X exp x )
{
  ll_item l = (ll_item)((void *)(pt(x)));
  if ((last(x) && bro(x)) || (!last(x) && no(x))) {
				/* main location is shared */
    out_loc_range (l1, l2, 0);
    dw_at_data (1, LOp_Shared);
    dw_at_address (no(x));
  }
  startlab = l1;
  ll_ok = 0;
  if (l)
    extlist_portion (l);
  if (ll_ok && l2 != startlab) {
    out_loc_range (startlab, l2, 0);
    dw_at_data (1, LOp_Const);
    dw_out_const (obval);
  }
  return;
}

void out_obj_shared_set
    PROTO_N ( (dn) )
    PROTO_T ( dg_name dn )
{
  exp x = dn->data.n_obj.obtain_val;
  ll_item l = find_ll_item (dn, LL_MASTERSHARE, 0);
  if (last(x) && (bro(x) || l)) {
    out_dwf_label (no(x), 1);
    dw_at_ext_address (dn->mor->this_tag);
    while (bro(x)) {
      dg_name nm = (dg_name)((void *)bro(x));
      dw_at_ext_address (nm->mor->this_tag);
      x = nm->data.n_obj.obtain_val;
    }
    if (l)
      out_regshare_set (l->u.l);
    out32(); outs("0"); outnl_comment ("share list end");
  }
  return;
}

