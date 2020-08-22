/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/dw2_config.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <main/driver.h>
#include <main/print.h>

#ifdef TDF_DIAG3
#include <diag3/dg_types.h>
#include <diag3/dg_aux.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/dg_types.h>
#include <diag4/dg_aux.h>
#endif

#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_locdata.h>


/* Location list information is collected for each object, held via
   fields of the 'obtain_value' exp (which is a hold_tag). last is set if the
   object is master of a new location. next is used to hold references to other
   objects that share this location (as a next list).  no is label for shared
   location set.  pt holds other more temporary uses (via ll_item).
*/



#define	LOp_Non_Current 1
#define	LOp_Locked	2
#define	LOp_Const	3
#define	LOp_Shared	4
#define	LOp_Portion	5


typedef enum {
	LL_OPTLOCK = 1,
	LL_CONST,
	LL_RET,
	LL_REGSHARE,
	LL_MASTERSHARE
} loclist_key;

typedef struct rs_s {
	long		start;
	long		end;
	long		share;
	dg_name		name;
	int		reg;
	struct rs_s	*next_share;
	struct rs_s	*next_loc;
} *regshare_item;

typedef struct rsl_s {
	dg_name		alloc;
	int		reg;
	regshare_item	items;
	struct rsl_s	*next;
} *regshare_list;

typedef struct ll_s {
	unsigned int	key:8;
	bool open:1;
	bool has_inner:1;
	union {
		dg_info		d;
		retrec		*r;
		regshare_item	l;
	} u;
	struct ll_s	*next;
	struct ll_s	*inner;
} *ll_item;

static ll_item *
ll_root(dg_name name)
{
	exp x = name->data.n_obj.obtain_val;
	exp * ref = & (pt(x));
	return (ll_item *)((void *)ref);
}

static ll_item
new_ll_item(loclist_key k, int o)
{
	ll_item ans = (ll_item)xmalloc(sizeof(struct ll_s));
	ans->key = k;
	ans->open = ans->has_inner = o;
	ans->next = (ll_item)0;
	ans->inner = (ll_item)0;
	return ans;
}


static regshare_list all_regshares = (regshare_list)0;

void *
dw_new_regshare(dg_name name, int reg)
{
	regshare_list ans = (regshare_list)xmalloc(sizeof(struct rsl_s));
	ans->alloc = name;
	ans->reg = reg;
	ans->items = (regshare_item)0;
	ans->next = all_regshares;
	all_regshares = ans;
	return (void *) ans;		/* actual type local to this file */
}


void
dw_add_regshare(void * w, dg_name name, long start, long end)
{
	regshare_list holder = (regshare_list)w;
	regshare_item item = (regshare_item)xmalloc(sizeof(struct rs_s));
	item->start = start;
	item->end = end;
	item->share = 0;
	item->name = name;
	item->next_share = holder->items;
	item->next_loc = (regshare_item)0;
	holder->items = item;
}


obj_list *local_objects = NULL;

static void
check_taggable(dg_name name)
{
	if (!name->more || !name->more->this_tag) {
		IGNORE f_dg_tag_name(gen_dg_tag(), name);
	}
}


void
set_locdata(obj_list this_obl)
{
	dg_name this_name = this_obl.obj;
	while (this_name) {
		if (this_name->key == DGN_OBJECT) {
			exp x = this_name->data.n_obj.obtain_val;
			exp id;
			if (x && (id = dw_has_location(son(x)), id)) {
				if (isglob(id)) {
					dg_name master =
					    brog(id)->dg_name;
					if (!master) {
						master = brog(id)->dg_name = this_name;
					}
					if (master == this_name) {
						x->last = true;
						no(x) = next_dwarf_label();
					} else {
						exp y = master->data.n_obj.obtain_val;
						setbro(x, next(y));
						setbro(y,
						       (exp)((void *)this_name));
						no(x) = no(y);
						check_taggable(master);
						check_taggable(this_name);
					}
				} else {
					int found = 0;
					obj_list * obl = local_objects;
					while (obl && !found) {
						dg_name name = obl->obj;
						while (name) {
							if (name->key == DGN_OBJECT) {
								exp y = name->data.n_obj.obtain_val;
								if (y && y->last && dw_has_location(son(y)) == id) {
									setbro(x, next(y));
									setbro(y, (exp)((void *)this_name));
									no(x) = no(y);
									check_taggable(name);
									check_taggable(this_name);
									found = 1;
									break;
								}
							}
							if (!obl->islist) {
								break;
							}
							name = name->next;
						}
						obl = obl->next;
					}
					if (!found) {
						x->last = true;
						no(x) = next_dwarf_label();
						dw_allocated(this_name, id);
					}
				}
			} else {
				no(x) = 0;
			}
		}
		if (!this_obl.islist) {
			break;
		}
		this_name = this_name->next;
	}
}


void
close_locdata(obj_list this_obl)
{
	dg_name this_name = this_obl.obj;
	while (this_name) {
		if (this_name->key == DGN_OBJECT) {
			exp x = this_name->data.n_obj.obtain_val;
			if (x && x->last) {
				dw_deallocated(this_name);
			}
		}
		if (!this_obl.islist) {
			break;
		}
		this_name = this_name->next;
	}
}


dg_name
find_equiv_object(exp e, int isc)
{
	obj_list *obl = local_objects;
	while (obl) {
		dg_name name = obl->obj;
		while (name) {
			if (name->key == DGN_OBJECT) {
				exp x = name->data.n_obj.obtain_val;
				if (isc) {
					if (x && son(x)->tag == cont_tag &&
					    dw_loc_equivalence(e,
							       son(son(x)))) {
						return name;
					}
				} else {
					if (x && dw_loc_equivalence(e,
								    son(x))) {
						return name;
					}
				}
			}
			if (!obl->islist) {
				break;
			}
			name = name->next;
		}
		obl = obl->next;
	}
	return (dg_name) 0;
}


static dg_name
find_simple_object(exp e)
{
	/* e is name_tag for required object */
	obj_list *obl = local_objects;
	while (obl) {
		dg_name name = obl->obj;
		while (name) {
			if (name->key == DGN_OBJECT) {
				exp x = name->data.n_obj.obtain_val;
				while (x && (x->tag == hold_tag ||
					     x->tag == cont_tag ||
					     x->tag == reff_tag)) {
					x = son(x);
				}
				if ((x) && x->tag == name_tag &&
				    son(x) == son(e) &&
				    (no(x) <= no(e)) &&
				    (no(x) + shape_size(sh(x))) >=
				    (no(e) + shape_size(sh(e)))) {
					return name;
				}
			}
			if (!obl->islist) {
				break;
			}
			name = name->next;
		}
		obl = obl->next;
	}
	return (dg_name) 0;
}


void
set_optim_objects(dg_info optim, int start)
{
	objset *obj = optim->data.i_optim.objs;
	while (obj) {
		dg_name name = obj->tag->p.name;
		if (start) {
			ll_item *l = ll_root(name);
			while (*l) {
				if ((*l)->open) {
					l = & ((*l)->inner);
				} else {
					l = & ((*l)->next);
				}
			}
			*l = new_ll_item(LL_OPTLOCK, 1);
			(*l)->u.d = optim;
		} else {
			ll_item l = *ll_root(name);
			while (l->key != LL_OPTLOCK || l->u.d != optim) {
				if ((l)->open) {
					l = l->inner;
				} else {
					l = l->next;
				}
			}
			l->open = 0;
		}
		obj = obj->next;
	}
}


void
set_remval_object(dg_info rmv)
{
	dg_name name = find_simple_object(son(rmv->data.i_remval.var));
	if (name) {
		ll_item *l = ll_root(name);
		while (*l) {
			if ((*l)->open) {
				l = &((*l)->inner);
			} else {
				l = &((*l)->next);
			}
		}
		*l = new_ll_item(LL_CONST, 0);
		(*l)->u.d = rmv;
	}
}


void
set_obj_rets(retrec * rec)
{
	obj_list *obl = local_objects;
	while (obl) {
		dg_name name = obl->obj;
		while (name) {
			if (name->key == DGN_OBJECT) {
				exp x = name->data.n_obj.obtain_val;
				while (x && (x->tag == hold_tag ||
					     x->tag == cont_tag ||
					     x->tag == reff_tag)) {
					x = son(x);
				}
				if ((x) && x->tag == name_tag &&
				    !isdiscarded(x) &&
				    !isglob(son(x))) {
					ll_item *l = ll_root(name);
					while (*l) {
						if ((*l)->open) {
							l = &((*l)->inner);
						} else {
							l = &((*l)->next);
						}
					}
					*l = new_ll_item(LL_RET, 0);
					(*l)->u.r = rec;
				}
			}
			if (!obl->islist) {
				break;
			}
			name = name->next;
		}
		obl = obl->next;
	}
}


static ll_item
find_ll_item(dg_name name, loclist_key k, int force)
{
	ll_item *ll = ll_root(name);
	ll_item l = *ll;
	while (l && l->key != k) {
		l = l->next;
	}
	if (!l && force) {
		l = new_ll_item(k, 0);
		l->u.l = (regshare_item)0;
		l->next = *ll;
		*ll = l;
	}
	return l;
}


static void
out_regshare_set(regshare_item it)
{
	regshare_item this = it;
	while (this) {
		dg_name name = this->name;
		if (name) {
			regshare_item look = it;
			while (look->name != name) {
				/* avoid duplicates */
				look = look->next_share;
			}
			if (look == this) {
				dw_at_ext_address(name->more->this_tag);
			}
		}
		this = this->next_share;
	}
}


void
init_dw_locdata(void)
{
	all_regshares = NULL;
	local_objects = NULL;
	dw_all_deallocated();
}


void
complete_dw_locdata(void)
{
	regshare_list top_l = all_regshares;
	while (top_l) {
		dg_name master = top_l->alloc;
		int reg = top_l->reg;
		regshare_item regitem = top_l->items;
		dg_name name;
		if (master) {
			while (regitem) {
				name = master;
				do {
					if (regitem->name == name) {
						regitem->name = NULL;
						break;
					}
					name = (dg_name)((void *)next(name->data.n_obj.obtain_val));
				} while (name);
				if (!name) {
					/* regitem not in allocation shareset */
					ll_item l =
					    find_ll_item(master,
							 LL_MASTERSHARE, 1);
					if (!l->u.l) {
						/* start of extra share list
						 * for master */
						l->u.l = regitem;
					}
					regitem->share =
					    no(master->data.n_obj.obtain_val);
					regitem->reg = reg;
					l = find_ll_item(regitem->name,
							 LL_REGSHARE, 1);
					regitem->next_loc = l->u.l;
					l->u.l = regitem;
					check_taggable(regitem->name);
					check_taggable(master);
				}
				regitem = regitem->next_share;
			}
		} else {
			long share = 0;
			master = name = NULL;
			while (regitem) {
				if (!master) {
					master = regitem->name;
				}
				if (!name) {
					name = regitem->name;
				}
				if (name != master) {
					share = next_dwarf_label();
					break;
				}
				regitem = regitem->next_share;
			}
			regitem = top_l->items;
			while (regitem) {
				ll_item l = find_ll_item(regitem->name,
							 LL_REGSHARE, 1);
				regitem->share = share;
				if (share) {
					check_taggable(regitem->name);
				}
				regitem->reg = reg;
				regitem->next_loc = l->u.l;
				l->u.l = regitem;
				regitem = regitem->next_share;
			}
			if (share) {
				enter_section("debug_loc");
				out_dwf_label(share, 1);
				out_regshare_set(top_l->items);
				exit_section();
			}
		}
		top_l = top_l->next;
	}
}


static int
obj_decide(ll_item l)
{
	int ans = 0, x;
	while (l && ans < 2) {
		switch (l->key) {
		case LL_OPTLOCK:
		case LL_CONST:
		case LL_MASTERSHARE:
			return 2;
		case LL_RET:
			if (!ans) {
				ans = 1;
			}
			break;
		case LL_REGSHARE: {
			regshare_item rs = l->u.l;
			while (rs && ans<2) {
				if (rs->share) {
					ans = 2;
				} else if (!ans) {
					ans = 1;
				}
				rs = rs->next_loc;
			}
			break;
		}
		}
		if (l->has_inner && (x = obj_decide(l->inner), x > ans)) {
			ans = x;
		}
		l = l->next;
	}
	return ans;
}


int
decide_ll_type(exp x)
{
	/* 1 if need location list, 2 if extension list */
	ll_item l = (ll_item)((void *)(pt(x)));
	if ((x->last && next(x)) || (!x->last && no(x))) {
		/* main location is shared */
		return 2;
	} else {
		return obj_decide(l);
	}
}


static long startlab;
static int ll_ok;
static exp obval;

static void
loclist_portion(ll_item l)
{
	while (l) {
		switch (l->key) {
		case LL_CONST:
			ll_ok = 0;
			break;
		case LL_RET: {
			long endlab = l->u.r->lab;
			if (ll_ok && endlab != startlab) {
				out_loc_range(startlab, endlab, 0);
				dw2_locate_exp(obval, 0, 1);
			}
			startlab = l->u.r->over;
			break;
		}
		case LL_REGSHARE: {
			regshare_item rs = l->u.l;
			while (rs) {
				out_loc_range(rs->start, rs->end, 1);
				out16();
				if (rs->reg < 32) {
					asm_printf("%d\n", 1);
					out8();
					asm_printf("%d", DW_OP_reg0 + rs->reg);
				} else {
					asm_printf("%d\n", 1 + uleb128_length((unsigned long)rs->reg));
					out8();
					asm_printf("%d, ", DW_OP_regx);
					uleb128((unsigned long)rs->reg);
				}
				asm_printf("\n");
				rs = rs->next_loc;
			}
		}
		default:
			break;
		}
		if (l->has_inner) {
			loclist_portion(l->inner);
		}
		l = l->next;
	}
}


void
out_obj_loclist(long l1, long l2, exp x)
{
	ll_item l = (ll_item)((void *)(pt(x)));
	startlab = l1;
	ll_ok = 1;
	obval = son(x);
	loclist_portion(l);
	if (ll_ok && l2 != startlab) {
		out_loc_range(startlab, l2, 0);
		dw2_locate_exp(obval, 0, 1);
	}
}


static void
extlist_portion(ll_item l)
{
	while (l) {
		switch (l->key) {
		case LL_CONST: {
			long here = l->u.d->data.i_remval.lo_pc;
			if (ll_ok && here != startlab) {
				out_loc_range(startlab, here, 0);
				dw_at_data(1, LOp_Const);
				dw_out_const(obval);
			}
			startlab = here;
			ll_ok = 1;
			obval = l->u.d->data.i_remval.val;
			break;
		}
		case LL_OPTLOCK:
			out_loc_range(l->u.d->data.i_optim.lo_pc,
				      l->u.d->data.i_optim.hi_pc, 0);
			dw_at_data(1, LOp_Locked);
			dw_at_data(1, l->u.d->data.i_optim.reason);
			break;
		case LL_REGSHARE: {
			regshare_item rs = l->u.l;
			while (rs) {
				if (rs->share) {
					out_loc_range(rs->start, rs->end, 1);
					dw_at_data(1, LOp_Shared);
					dw_at_address(rs->share);
				}
				rs = rs->next_loc;
			}
		}
		default:
			break;
		}
		if (l->has_inner) {
			loclist_portion(l->inner);
		}
		l = l->next;
	}
}


void
out_obj_extloclist(long l1, long l2, exp x)
{
	ll_item l = (ll_item)((void *)(pt(x)));
	if ((x->last && next(x)) || (!x->last && no(x))) {
		/* main location is shared */
		out_loc_range(l1, l2, 0);
		dw_at_data(1, LOp_Shared);
		dw_at_address(no(x));
	}
	startlab = l1;
	ll_ok = 0;
	if (l) {
		extlist_portion(l);
	}
	if (ll_ok && l2 != startlab) {
		out_loc_range(startlab, l2, 0);
		dw_at_data(1, LOp_Const);
		dw_out_const(obval);
	}
}


void
out_obj_shared_set(dg_name dn)
{
	exp x = dn->data.n_obj.obtain_val;
	ll_item l = find_ll_item(dn, LL_MASTERSHARE, 0);
	if (x->last && (next(x) || l)) {
		out_dwf_label(no(x), 1);
		dw_at_ext_address(dn->more->this_tag);
		while (next(x)) {
			dg_name name = (dg_name)((void *)next(x));
			dw_at_ext_address(name->more->this_tag);
			x = name->data.n_obj.obtain_val;
		}
		if (l) {
			out_regshare_set(l->u.l);
		}
		out32();
		asm_printf("0");
		asm_comment("share list end");
	}
}
