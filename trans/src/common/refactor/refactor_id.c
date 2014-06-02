/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * refactor_id tries to apply transformations to improve identity and
 * variable declarations.
 *
 * refactor_id delivers 1 if it makes any change, 0 otherwise.
 *
 * used_in delivers 0 if the identifier declared by vardec is unused in
 * the exp piece, 1 if it is used for contents operation only, 3 if it is
 * used otherwise.
 *
 * simple_const tests whether e is used as a simple constant in whole.
 * This is true in the following circumstances only:
 *
 *  1) e is a constant.
 *  2) e is an identity declaration(not a variable) and the declaration is
 *     external to whole.
 *  3) e is the contents of a variable, and the variable is not used
 *     in whole as the destination of an assignment, and the variable
 *     is only used (anywhere) as the destination of assignment or
 *     argument of contents (ie there is no alias for it).
 *
 * no_ass is true iff there are no assignments to things that might
 * be aliased during the evaluation of whole. (beware procedure calls!)
 */

#include <stddef.h>

#include <shared/check.h>

#include <reader/exptypes.h>
#include <reader/expmacs.h>

#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/tags.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/me_fns.h>

#include <main/flags.h>

#include <refactor/refactor.h>
#include <refactor/refactor_id.h>

#ifdef NEWDIAGS
#include <newdiag/dg_aux.h>
#endif

#if defined(TRANS_80x86) || defined(TRANS_HPPA)
#include "localexpmacs.h"
#endif

#if TRANS_680x0
extern int check_anyway(exp);
#endif

/*
 * make_onearg makes up an exp with the given tag (n), shape (sha)
 * and single argument (a).
 */
exp
hc(exp e, exp t)
{
	setlast(t);
	bro(t) = e;
	return hold_refactor(e);
}

static exp
make_onearg(unsigned char n, shape sha, exp a)
{
	exp r = getexp(sha, NULL, 0, a, NULL, 0, 0, n);
	return hc(r, a);
}

/*
 * make_twoarg makes up an exp with the given tag (n), shape (sha)
 * and two arguments (a,b) in that order.
 */
static exp
make_twoarg(unsigned char n, shape sha, exp a, exp b)
{
	exp r = getexp(sha, NULL, 0, a, NULL, 0, 0, n);
	bro(a) = b;
	clearlast(a);
	return hc(r, b);
}

/*
 * used_in delivers 0 if the identifier declared by vardec is unused in
 * the exp piece, 1 if it is used for contents operation only, 3 if it is
 * used otherwise.
 */
int
used_in(exp vardec, exp piece)
{
	int  res = 0;
	exp t = pt(vardec);
	exp q;
	exp upwards = t;
	/* test each use of the identifier */
	do {
		q = t;
		while (q != NULL && q != piece && q != vardec &&
		       !parked(q) && (name(q) != ident_tag || !isglob(q))) {
			upwards = q;
			q = bro(q);
		}
		/* ascend from the use until we reach either vardec or piece */
		if (last (upwards) && q == piece) {
			/* the use was in piece */
			res = 1;
			if ((last(t) || !last(bro(t)) ||
			     name(bro(bro(t))) != 0)) {
				/* the use was not contents or in diagnostics*/
				if (!last(t) || name(bro(t)) != cont_tag) {
					res = 3;
				}
			}
		}
		t = pt(t);
	} while (t != NULL && res != 3);
	return res;
}

/*
 * simple_const tests whether e is used as a simple constant in whole.
 * This is true in the following circumstances only:
 *
 *  1) e is a constant.
 *  2) e is an identity declaration(not a variable) and the declaration is
 *     external to whole.
 *  3) e is the contents of a variable, and the variable is not used
 *     in whole as the destination of an assignment, and the variable
 *     is only used (anywhere) as the destination of assignment or
 *     argument of contents (ie there is no alias for it).
 *
 * no_ass is true iff there are no assignements to things that might
 * be aliased during the evaluation of whole. (ware procedure calls!)
 */
int
simple_const(exp whole, exp e, int decl, int no_ass)
{
	if (name(e) == val_tag || name(e) == real_tag || name(e) == null_tag) {
		return 1;
	}
	if (name(e) == name_tag && !isvar(son(e)) &&
	    (decl || !internal_to(whole, son(e)))) {
		return 1;
	}
	if (name(e) == reff_tag) {
		e = son(e);
	}
	if (name(e) == cont_tag && name(son(e)) == name_tag &&
	    !isparam(son(son(e))) && isvar(son(son(e)))) {
		exp var = son(son(e));
		int  u = used_in(var, whole);
		if (u != 3 && (iscaonly(var) || no_ass)) {
			return 1;
		}
		return 0;
	}
	return 0;
}

/*
 * replace declaration by sequence of definition and body.
 * Done if the identifier is not used.
 */
static void
repbyseq(exp e)
{
	exp def = son(e);
	exp body = hold_refactor(bro(def));
	exp seq, s;
#ifdef NEWDIAGS
	exp t = pt(e);
	while (t != NULL) {
		if (isdiaginfo(t))
			setdiscarded(t);
		t = pt(t);
	}
#endif
	if (son(def) == NULL) {
#ifdef NEWDIAGS
		if (diag != DIAG_NONE) {
			dg_whole_comp(e, body);
		}
#endif
		replace(e, body, e);
		retcell(def);
		return;
	}
	seq = getexp(f_bottom, NULL, 0, def, NULL, 0, 0, 0);
	bro(def) = seq;
	setlast(def);
	s = hold_refactor(make_twoarg(seq_tag, sh(body), seq, body));
#ifdef NEWDIAGS
	if (diag != DIAG_NONE) {
		dg_whole_comp(e, s);
	}
#endif
	replace(e, s, e);
	return;
}

/*
 * propagate looks right and upwards from plc through the tree, looking
 * for contents operations applied to the variable defined by vardec.
 *
 * The assumption is that plc made an assignment to the variable defined
 * by vardec, and this scan looks forward from this point, marking any
 * contents operations on that variable for later modification to use the
 * value assigned. The variable is previously checked to make sure there
 * is no alias for it.
 *
 * The scan terminates if ende is reached or when it is no longer safe
 * to propagate the value forward. 1 is delivered if ende was reached
 * while propagation was still safe, 0 otherwise.
 */
static int
propagate(exp vardec, exp ende, exp plc, int bfirst)
{
	exp p = plc;		/* starting place */
	int good = 1;		/* good is set to 0 when we find a place
				   where we must stop */
	int bb = bfirst;	/* if bb is 1, avoid the first up */


	/* up ascends the tree */
up:	if (bb) {
		bb = 0;
	} else {
		if (p == ende) {		/* finished */
			goto ex;
		} else {
			if (!last(p)) {
				p = bro(p);
				if (name(p) == labst_tag) {
					/* can't go further */
					good = 0;
					goto ex;
				}
			} else {
				if (name(bro(p)) == proc_tag ||
				    name(bro(p)) == labst_tag ||
				    name(bro(p)) == condassign_tag) {
					/* can't go further */
					good = 0;
					goto ex;
				} else {
					p = bro(p);
					if ((name(p) == ass_tag ||
					     name(p) == assvol_tag) &&
					    name(son(p)) == name_tag &&
					    son(son(p)) == vardec) {
						good = 0;
						goto ex;
					}
					goto up;
				}
			}
		}
	}

	/* rep processes an exp */
rep:	if (name(p) == ass_tag || name(p) == assvol_tag) {
		if (name(son(p)) == name_tag && son(son(p)) == vardec) {
			/* just process the value */
			p = bro(son(p));
			goto rep;
		} else {
			/* assignment to something else */
			p = son(p);
			goto rep;
		}
	}

	if (name(p) == cont_tag) {
		if (name(son(p)) == name_tag && son(son(p)) == vardec) {
			set_propagate(p);		/* mark it */
			goto up;
		} else {
			p = son(p);
			goto rep;
		}
	}

	if (name(p) == name_tag || name(p) == env_offset_tag) {
		goto up;
	}

	if (name(p) == apply_tag || name(p) == apply_general_tag) {
		if (isglob(vardec)) {
			/* vardec is global */
			good = 0;
			goto ex;
		} else {
			/* not aliased so OK */
			p = son(p);
			goto rep;
		}
	}

	if (name(p) == rep_tag) {
		good = 0;
		goto ex;
	}

	if (name(p) == cond_tag) {
		if (propagate(vardec, son(p), son(p), 1)) {
			good = propagate(vardec, bro(son(bro(son(p)))),
					 bro(son(bro(son(p)))), 1);
			/* if we can propagate right through the first of the
			 * cond we can go into the alt. This condition is
			 * stronger than needed. */
			if (good) {
				goto up;
			} else {
				goto ex;
			}
		} else {
			good = 0;
			goto ex;
		}
	}

	if (name(p) == solve_tag) {
		IGNORE propagate(vardec, son(p), son(p), 1);
		/* give up after trying the first element */
		good = 0;
		goto ex;
	}

	if (name(p) == case_tag) {
		if (propagate(vardec, son(p), son(p), 1)) {
			goto up;
		}
		good = 0;
		goto ex;
	}

	if (son(p) == NULL) {
		goto up;
	}

	p = son(p);
	goto rep;


ex:	return good;
}

/*
 * change_cont looks at all the cont uses of the variable defined by
 * vardec. If they have been marked by propagate or if force is 1,
 * the cont(var) is replaced by val.
 */
static exp
change_shape(exp e, shape sha)
{
	if (name(e) == val_tag) {
		no(e) = dochvar(no(e), sha);
	}
	sh(e) = sha;
	return e;
}


static int
change_cont(exp vardec, exp val, int force)
{
	exp t;
	exp bh = hold(bro(son(vardec)));
	int ch = 0;
	int go = 1;
	int defsize = shape_size(sh(son(vardec)));
	while (go) {
		t = pt(vardec);
		go = 0;
		while (!go && t != NULL) {
			if (last(t) && name(bro(t)) == cont_tag &&
#ifdef NEWDIAGS
			    !isdiaginfo(t) &&
#endif
			    (to_propagate(bro(t)) || force)) {
				if (defsize == shape_size(sh(bro(t)))) {
					exp p = bro(t);
					exp c = change_shape(copy(val), sh(p));
					kill_exp(t, son(bh));
					replace(p, c, son(bh));
					retcell(p);
					t = pt(vardec);
					ch = 1;
					go = 1;
				} else {
					clear_propagate(bro(t));
				}
			} else {
				t = pt(t);
			}
		}
	}
	bro(son(vardec)) = son(bh);
	setlast(bro(son(vardec)));
	bro(bro(son(vardec))) = vardec;
	retcell(bh);
	return ch;
}

/*
 * checks identity and variable declarations.
 */
int
refactor_id(exp e, exp scope)
{
  int is_var = isvar(e);
  int is_vis = (all_variables_visible || isvis(e));
  exp def = son(e);
  exp body = bro(def);
  int looping;
  exp t1;

  if (no(e) == 0) {
    if (!isvis(e) && !isenvoff(e) && !isglob(e) && !isparam(e)) {
      /* the variable is not used */
      repbyseq(e);
      return 1;
    } else {
      if (isparam(e)) {
	setcaonly(e);
      }
      return 0;
    }
  }


 if (load_ptr_pars) {
  if (!is_vis && is_var && isparam(e) && no(e) > 1 && name(sh(def)) == ptrhd
#if TRANS_680x0
      && check_anyway(e)
#endif
     ) {
    int ch_load = 1;
    int sz = shape_size(sh(def));
    t1 = pt(e);
    looping = 1;
    do {
#ifdef NEWDIAGS
      if (!isdiaginfo(t1)) {
#endif

	if (!last(t1) && last(bro(t1)) && name(bro(bro(t1))) == ass_tag &&
	    shape_size(sh(bro(t1))) == sz) {
	  ;
	} else if (!last(t1) || name(bro(t1)) != cont_tag ||
		   shape_size(sh(bro(t1))) != sz) {
	  ch_load = 0;
	}

#ifdef NEWDIAGS
      }
#endif
      if (pt(t1) == NULL) {
	looping = 0;
      } else {
	t1 = pt(t1);
      }
    } while (looping && ch_load);

    if (ch_load) {
      exp old_pt_list = pt(e);
      int old_uses = no(e);
      exp new_var;
      exp new_n;
      exp real_body;

      t1 = e;
      while (name(bro(son(t1))) == ident_tag && isparam(bro(son(t1)))) {
	t1 = bro(son(t1));
      }
      real_body = bro(son(t1));

      new_n = getexp(sh(def), real_body, 0, e, NULL, 0, 0, name_tag);
      new_var = getexp(sh(e), NULL, 0, new_n, old_pt_list, 1, old_uses,
		       ident_tag);
      setloadparam(new_n);
      setfather(new_var, real_body);
      pt(e) = new_n;
      no(e) = 1;
      clearvar(e);
      while (old_pt_list != NULL) {
	son(old_pt_list) = new_var;
	old_pt_list = pt(old_pt_list);
      }
      new_var = hold_refactor(new_var);

      bro(son(t1)) = new_var;
      setfather(t1, new_var);
      return 1;
    }
  }
 }

  if (!is_vis && !is_var &&
      (!load_ptr_pars || ((name(def) != name_tag || !isloadparam(def)))) &&
      (name(def) == val_tag ||
      (load_ptr_pars
	? ((name(def) == name_tag &&
	   (!isparam(son(def)) || name(sh(def)) == ptrhd)))
	: name(def) == name_tag )
       ||
#if TRANS_80x86
       (name(def) == name_tag && isparam(son(def)) && !isvar(son(def)) &&
	shape_size(sh(def)) < shape_size(sh(son(son(def)))) &&
	name(sh(def)) <= ulonghd) ||
#endif

	/*
	 * Substitute the definitions of identity declarations into body
	 * if it seems cheaper to do so.
	 */
       (name(def) == reff_tag && name(son(def)) == cont_tag &&
	name(son(son(def))) == name_tag && isvar(son(son(son(def)))) &&
	!isglob(son(son(son(def)))) &&
	used_in(son(son(son(def))), body) != 3) ||
       (name(def) == reff_tag && name(son(def)) == name_tag &&
	isvar(son(son(def))) && !isglob(son(son(def))) &&
	used_in(son(son(def)), body) != 3) || name(def) == null_tag ||
       name(def) == real_tag)) {
	 /* identifying a constant or named value */
    if (optim & OPTIM_SUBSTPARAMS || name(def) != name_tag || !isparam(son(def)) ||
	isvar(son(def))) {
      exp bh = hold(body);
#ifdef NEWDIAGS
      dg_info dgh = dgf(def);
      /* don't copy line info to all uses */
      dgf(def) = nildiag;
#endif
      while (pt(e) != NULL) {
	exp mem = pt(e);
	exp cp;
	pt(e) = pt(mem);
	cp = copy(def);
#ifdef NEWDIAGS
	if (isdiaginfo(mem)) {
	  IGNORE diaginfo_exp(cp);
	} else {
	  --no(e);
	}
#else
	--no(e);
#endif
	if (name(cp) == name_tag) {
	  no(cp) += no(mem);
	}
	if (sh(cp) != sh(mem)) {
	  if (name(sh(cp)) <= u64hd) {
	    cp = hold_refactor(me_u3(sh(mem), cp, chvar_tag));
	  } else {
	    sh(cp) = sh(mem);
	  }
	}
#ifdef NEWDIAGS
	if (diag != DIAG_NONE) {
	  dg_whole_comp(mem, cp);
	}
#endif
	replace(mem, cp, body);
      }
#ifdef NEWDIAGS
      dgf(def) = dgh;
#endif
      bro(def) = son(bh);
      bro(bro(def)) = e;
      setlast(bro(def));
      retcell(bh);
      IGNORE refactor(e, scope);
      return 1;
    }
  }

  if (!is_vis && !is_var && name(def) == reff_tag && al1(sh(def)) == 1) {
    /*
	 * Also substitute identity definitions which are references to bitfields.
	 */
    exp t = pt(e);
    int n = no(def);
    shape sha = sh(def);
    shape shb = sh(son(def));
    exp q, k;

#ifdef NEWDIAGS
    if (diag != DIAG_NONE) {
      dg_whole_comp(def, son(def));
    }
#endif
    replace(def, son(def), son(def));

    while (1) {
      k = pt(t);
      q = getexp(sha, NULL, 0, copy(t), NULL, 0, n, reff_tag);
      sh(son(q)) = shb;
      q = hc(q, son(q));
      replace(t, q, q);
      kill_exp(t, t);
      if (k == NULL) {
	return 1;
      }
      t = k;
    }
  }

  if (!is_vis && !is_var && name(def) == string_tag) {
    /* and substitute strings */
    exp t = pt(e);
    int all_chars = 1;
    while (1) {
      if (name(sh(t)) > ucharhd) {
	all_chars = 0;
	break;
      }
      if (last (t)) {
	/* Surely this is wrong ??? */
	break;
      }
      t = pt(t);
    }
    if (all_chars) {
      char *str = nostr(def);

      t = pt(e);
      while (1) {
	/* Surely this is wrong ??? */
	int l = (int)last (t);

	exp n = bro(t);
	int  v = str[no(t) / 8];
	exp c;
	if (name(sh(t)) == ucharhd) {
	  v = v & 0xff;
	}
	c = getexp(sh(t), NULL, 0, NULL, NULL, 0,
		   v, val_tag);
	replace(t, c, c);
	kill_exp(t, t);
	if (l) {
	  break;
	}
	t = n;
      }
      if (no(e) == 0) {
	replace(e, bro(son(e)), scope);
	return 1;
      }
      return 0;
    }
  }

  if (!is_vis && !is_var && name(body) == seq_tag &&
      name(son(son(body))) == ass_tag && name(bro(son(body))) == name_tag) {
    exp tb = bro(son(son(son(body))));
    if (name(tb) == name_tag && son(tb) == e &&
	son(bro(son(body))) == e && last(son(son(body))) &&
	sh(tb) == sh(def) && sh(tb) == sh(bro(son(body)))) {
	/* e=id(def, seq(ass(tz, n(e)), n(e)) -> seq(ass(tz, def), cont(tz)) */
      exp ass = son(son(body));
      exp tz = son(ass);
      exp r, s, c;
      exp cz = copy(tz);
      bro(tz) = def;
      ass = hc(ass, def);
      r = getexp(f_top, NULL, 0, ass, NULL, 0, 0, 0);
      setlast(ass);
      bro(ass) = r;
      s = getexp(sh(body), NULL, 0, r, NULL, 0, 0, seq_tag);
      c = getexp(sh(body), s, 1, cz, NULL, 0, 0, cont_tag);
      setbro(r, hc(c, cz));
      replace(e, hc(s, bro(son(s))), e);
      return 1;
    }
  }

	/*
	 * Look to see if we can replace variable definitions by identities.
	 * This can be done if there are only contents operations and no aliasing.
	 */
  if (!is_vis && is_var) {
    /* variable declaration */
    int all_c = 1;	/* every use is a contents operation */
    int all_a = 1;	/* every use is an assignment operation */
    int not_aliased = 1;
    int ca = 0;		/* there is an assignment of a constant */

	/* there is an assignment of a variable (not its contents) (lhvalue in C terms). */
	int vardecass = 0;

    exp assd_val;	/* the assigned value */
    int conversion = 0;
    int biggest_assigned_const = 0;
    exp tc = pt(e);
    int defsize = shape_size(sh(def));
    do {
      /* scan the uses of the variable */
      if (last(tc) && (name(bro(tc)) == hold_tag ||
		       name(bro(tc)) == hold2_tag)) {
#ifdef NEWDIAGS
	if (diag_visible) {
#else
	if (diag != DIAG_NONE) {
#endif
	  setvis(e);
	  return 0;
	}
      } else {
	if (last(tc) && name(bro(tc)) == cont_tag && no(tc) == 0 &&
#ifdef NEWDIAGS
	    !isdiaginfo(tc) &&
#endif
	    (name(sh(bro(tc))) <shrealhd || name(sh(bro(tc))) >doublehd ||
	     (name(sh(def)) >= shrealhd && name(sh(def)) <= doublehd))) {
	  int qq = shape_size(sh(bro(tc)));
	  /* contents op so not all assignments */
	  all_a = 0;

	  if (name(father(bro(tc))) != test_tag) {
	    conversion = -1;
	  }
	  if ((defsize != qq) && (name(sh(def)) < shrealhd)) {
#if TRANS_80x86
	    if (!isparam(e) || no(e) != 1) {
	      if (no(tc) == 0 && defsize <= 32) {
		if (qq == 8) {
		  setbyteuse(e);
		}
	      } else {
		all_c = 0;
		not_aliased = 0;
	      }
	    }
#else
	    all_c = 0;
	    not_aliased = 0;
#endif
	  }
	} else {
	  if (!last(tc) && last(bro(tc)) && no(tc) == 0 &&
#ifdef NEWDIAGS
	      !isdiaginfo(tc) &&
#endif
	      name(bro(bro(tc))) == ass_tag) {
	    /* assignment op */
	    all_c = 0;		/* not all contents */
	    assd_val = bro(tc);

	    if (name(assd_val) == val_tag) {
	      if (no(assd_val) < 0) {
		conversion = -1;
	      }
	      if (no(assd_val) > biggest_assigned_const) {
		biggest_assigned_const = no(assd_val);
	      }
	    } else if (name(assd_val) == chvar_tag &&
		       name(sh(son(assd_val))) <= uwordhd &&
		       is_signed(sh(son(assd_val)))) {
	      int sz1 = shape_size(sh(son(assd_val)));
	      if (conversion == 0) {
		conversion = sz1;
	      } else if (conversion != sz1) {
		conversion = -1;
	      }
	    } else {
	      conversion = -1;
	    }

	    if (defsize != shape_size(sh(assd_val))) {
#if TRANS_80x86
	      if (no(tc) == 0 && defsize <= 32) {
		if (shape_size(sh(bro(tc))) == 8) {
		  setbyteuse(e);
		}
	      } else {
		all_a = 0;
		not_aliased = 0;
	      }
#else
	      all_a = 0;
	      not_aliased = 0;
#endif
	    }
	    if (name(assd_val) == val_tag || name(assd_val) == real_tag ||
		name(assd_val) == null_tag ||
		(name(assd_val) == name_tag && isglob(son(assd_val)))) {
	      ca = 1;		/* assigning a constant */
	    } else {
	      if (name(assd_val) == ident_tag && isvar(assd_val)) {
		vardecass = 1;
	      }
	    }
	  } else
#ifdef NEWDIAGS
		  if (!isdiaginfo(tc))
#endif
		  {
		    if (isreallyass(tc)) {
		      all_c = 0;
		      all_a = 0; /* so that we dont remove the proc call */
		    } else {
		      /* something else */
		      exp dad = father(tc);
		      all_c = 0;
		      all_a = 0;
		      if (!((name(dad) == addptr_tag ||
			     name(dad) == subptr_tag) &&
			    ((!last(dad) && last(bro(dad)) &&
			      name(bro(bro(dad))) == ass_tag) ||
			     (last(dad) && name(bro(dad)) == cont_tag))) ||
			  (name(sh(def)) == realhd &&
			   name(sh(bro(dad))) != realhd) ||
			  (name(sh(def)) == doublehd &&
			   name(sh(bro(dad))) != doublehd)) {
			/* not an assignment to element of array */
			not_aliased = 0;
		      } else {
			setvis(e);
			uses_loc_address = 1;
		      }
		    }
		  }
	}
	}
	tc = pt(tc);
      } while (tc != NULL);

      if (not_aliased || iscaonly(e)) {
	/* set no alias flag if nothing but cont and ass */
	setcaonly (e);
      } else {
	/* set visible flag if there is an alias */
	setvis (e);
	uses_loc_address = 1;
      }

      if (all_c) {
	/*
	 * If only cont operations replace by an identity declaration and
	 * change the uses accordingly.
	 */
	exp bh = hold(body);
	int i, j;
	setid(e);
	tc = e;
	do {
	  tc = pt(tc);
	  if (name(bro(tc)) == cont_tag) {
	    sh(tc) = sh(bro(tc));
#ifdef NEWDIAGS
	    if (diag != DIAG_NONE) {
	      dg_whole_comp(bro(tc), tc);
	    }
#endif
	    replace(bro(tc), tc, tc);
	  }
	} while (pt(tc) != NULL);

	if (no(e) < 100) {
	  for (i = 0; i < no(e); ++i) {
	    tc = e;
	    for (j = 0; tc != NULL && j <= i; ++j) {
	      tc = pt(tc);
#ifdef NEWDIAGS
	      while (tc != NULL && isdiaginfo(tc))
		tc = pt(tc);
#endif
	    }
	    altered(tc, son(bh));
	  }
	}

	bro(def) = son(bh);
	bro(bro(def)) = e;
	setlast(bro(def));
	retcell(bh);
	IGNORE refactor(e, scope);
	return 1;
      }

#if TRANS_80x86 || TRANS_HPPA
      /* look for places where we can avoid sign extending */
      if (not_aliased && name(sh(def)) == slonghd &&
	  conversion == 16 && /* not 8 because of 80x86 regs */
	  (biggest_assigned_const & ((conversion == 8) ? (int)0xffffff80 :
				     (int)0xffff8000)) == 0 &&
	  name(def) == clear_tag) {
	exp temp = pt(e);
	shape ish = (conversion == 8) ? scharsh : swordsh;
	setse_opt(e);
	while (temp != NULL) {
	  exp next = pt(temp);
	  if (last(temp)) {
	    if ((last(bro(temp)) || name(bro(bro(temp))) != val_tag) &&
		name(bro(temp)) != hold_tag) {
	      exp x = me_u3(slongsh, copy(bro(temp)), chvar_tag);
	      sh(son(x)) = ish;
	      replace(bro(temp), x, x);
	      IGNORE refactor(father(x), father(x));
	      kill_exp(bro(temp), bro(temp));
	    }
	  } else {
	    if (name(bro(temp)) == val_tag) {
	      sh(bro(temp)) = ish;
	    } else {
	      bro(son(bro(temp))) = bro(bro(temp));
	      bro(temp) = son(bro(temp));
#if TRANS_HPPA
	      sh(bro(temp)) = (conversion == 8) ? ucharsh : uwordsh;
#endif
	    }
	  }
	  temp = next;
	}
	replace(def, me_shint(slongsh, 0), def);
      }
#endif

      if (not_aliased && no(e) < 1000 &&
	  (name(sh(def)) < shrealhd || name(sh(def)) > doublehd) &&
	  (ca || vardecass || name(def) == val_tag ||
	   name(son(e)) == real_tag || name(def) == null_tag)) {
	/* propagate constant assignment forward from the place where they occur */
	int  no_ass;
	int chv;
	if (name(def) == val_tag || name(son(e)) == real_tag ||
	    name(def) == null_tag
	    /*
	       ||
	       (name(def) == name_tag &&
	       isglob (son(def)))
	     */
	   ) {
	  do {
	    body = bro(def);
	    IGNORE propagate(e, e, body, 1);
	  } while (change_cont(e, def, 0));
	}
	body = bro(def);

	do {
	  chv = 0;
	  no_ass = 0;
	  tc = pt(e);
	  while (!chv && tc != NULL) {
	    if (!last(tc) &&
#ifdef NEWDIAGS
		!isdiaginfo(tc) &&
#endif
		sh(bro(tc)) == sh(son(son(tc))) && last(bro(tc)) &&
		name(bro(bro(tc))) == ass_tag) {
	      exp var = bro(tc);
	      exp va, df, bd;
	      if (eq_shape(sh(bro(tc)), sh(son(e))) &&
		  (name(bro(tc)) == val_tag || name(bro(tc)) == real_tag ||
		   name(bro(tc)) == null_tag
		   /*
		      ||
		      (name(bro(tc)) == name_tag &&
		      isglob (son(bro(tc))))
		    */
		  )) {
		IGNORE propagate(e, e, bro(bro(tc)), 0);
		chv = change_cont(e, bro(tc), 0);
		body = bro(def);
		++no_ass;
	      } else {
		va = son(tc);
		df = son(var);

		if (df != NULL && (bd = bro(df)) != NULL &&
		    !isinlined(e) && !isglob(va) && isvar(va) &&
		    name(bd) == seq_tag && name(bro(son(bd))) == cont_tag &&
		    name(son(bro(son(bd)))) == name_tag &&
		    son(son(bro(son(bd)))) == var &&
		    isvar(var) && used_in(va, bd) == 0) {
		  exp a = son(bro(var));
		  exp prev_uses, ass, seq_hold, s;
		  kill_exp(bro(son(bd)), body);
		  prev_uses = pt(va);
		  tc = var;
		  pt(va) = pt(var);
		  do {
		    son(pt(tc)) = va;
		    ++no(va);
		    tc = pt(tc);
		  } while (pt(tc) != NULL);
		  pt(tc) = prev_uses;

		  if (name(df) == clear_tag) {
		    ass = getexp(f_top, NULL, 0, NULL, NULL, 0, 0,
				 top_tag);
		  } else {
		    ass = getexp(f_top, NULL, 0, a, NULL, 0, 0, ass_tag);
		    bro(a) = df;
		    bro(df) = ass;
		    setlast(df);
		  }
		  seq_hold = make_onearg(0, f_bottom, ass);
		  s = make_twoarg(seq_tag, f_top, seq_hold, son(son(bd)));
		  replace(bro(var), s, body);
		  chv = 1;
		}
	      }
	    }
	    tc = pt(tc);
	  }
	} while (chv);

#ifdef NEWDIAGS
	if (no(e) == no_ass && !isparam(e)) {
	  int diagonly = 1;
	  tc = pt(e);
	  while (tc != NULL) {
	    if (!isdiaginfo(tc)) {
	      if (diag != DIAG_NONE) {
		dg_rem_ass(bro(bro(tc)));
	      }
	      replace(bro(bro(tc)), bro(tc), bro(def));
	      diagonly = 0;
	    }
	    tc = pt(tc);
	  }
	  if (!diagonly) {
	    repbyseq(e);
	  }
	}
#else
	if (no(e) == no_ass && pt(e) != NULL && !isparam(e)) {
	  tc = pt(e);
	  while (replace(bro(bro(tc)), bro(tc), bro(def)), pt(tc) != NULL) {
	    tc = pt(tc);
	  }
	  repbyseq(e);
	}
#endif
	return 1;
      }

      if (!isparam(e) && name(def) == clear_tag && name(body) == seq_tag &&
	  name(son(son(body))) == ass_tag &&
	  name(son(son(son(body)))) == name_tag &&
	  son(son(son(son(body)))) == e &&
	  eq_shape(sh(def), sh(bro(son(son(son(body))))))) {
	/* definition is clear and first assignment is to this variable */
	exp val = bro(son(son(son(body))));/* assigned value */
	if (!used_in(e, val)) {
	  son(e) = val;		/* put it in as initialisation */
	  clearlast(val);
	  bro(val) = body;
	  /* kill the use of var */
	  kill_exp(son(son(son(body))), son(son(son(body))));
	  /* replace assignment by void */
	  replace(son(son(body)), getexp(f_top, NULL, 0, NULL, NULL, 0,
					 0, top_tag), body);
	  return 1;
	}
      }

#ifdef NEWDIAGS
      if (all_a && !isparam(e) && !diag_visible) {
#else
      if (all_a && !isparam(e) && diag == DIAG_NONE) {
#endif
	/*
	 * If only assignments replace them by evaluating the value assigned
	 * and discarding it. Replace the declaration by a sequence of
	 * definition and body.
	 */
	tc = pt(e);

	while (1) {
	  if (!last(tc) && name(bro(bro(tc))) == ass_tag) {
#ifdef NEWDIAGS
	    if (diag != DIAG_NONE) {
	      dg_rem_ass(bro(bro(tc)));
	    }
#endif
	    replace(bro(bro(tc)), bro(tc), body);
	  }
	  tc = pt(tc);
	  if (tc == NULL) {
	    break;
	  }
	}

	repbyseq(e);
	return 1;
      }

      }

      if (!is_var && !is_vis && no(e) == 1 && !isparam(e) &&
	  name(body) == ident_tag && name(son(body)) == name_tag &&
	  son(son(body)) == e && shape_size(def) == shape_size(son(body))) {
#ifdef NEWDIAGS
	if (diag != DIAG_NONE) {
	  exp t = pt(e);
	  while (t) {
	    if (isdiaginfo(t)) {
	      setdiscarded(t);
	    }
	    t = pt(t);
	  }
	}
#endif
	replace(son(body), def, def);
#ifdef NEWDIAGS
	if (diag != DIAG_NONE) {
	  dg_whole_comp(e, body);
	}
#endif
	replace(e, body, scope);
	return 1;
      }

      if (!is_var && !is_vis && name(def) == compound_tag) {
	exp c = son(def);
	int nuses = no(e);
	int changed = 0;
	for (;;) {
	  int n = name(bro(c));
	  if (n == val_tag || n == real_tag || n == name_tag || n == null_tag) {
	    exp u = pt(e);
	    for (; nuses !=0 && u !=NULL;) {
	      exp nextu = pt(u);
#ifdef NEWDIAGS
	      if (!isdiaginfo(u) && no(u) ==no(c) &&
		  eq_shape(sh(u), sh(bro(c)))) {
#else
	      if (no(u) ==no(c) && eq_shape(sh(u), sh(bro(c)))) {
#endif
		replace(u, copy(bro(c)), bro(def));
		nextu = pt(u); /* it could have changed */
		kill_exp(u, bro(def));
		nuses--;
		changed = 1;
	      }
	      u = nextu;
	    }
	  }
	  if (nuses ==0 || last(bro(c))) {
	    break;
	  }
	  c = bro(bro(c));
	}
	if ((no(e) ==0 || pt(e) == NULL) && !isenvoff(e)) {
	  repbyseq(e);
	  return 1;
	}
	return changed;
      }
      if (!is_var && !is_vis && name(def) == nof_tag) {
	exp c = son(def);
	int changed = 0;
	int nuses = no(e);
	int sz = rounder(shape_size(sh(c)), shape_align(sh(c)));
	int nd = 0;
	for (;;) {
	  int n = name(c);
	  if (n == val_tag || n == real_tag || n == name_tag || n == null_tag) {
	    exp u = pt(e);
	    for (; nuses !=0 && u !=NULL;) {
	      exp nextu = pt(u);
#ifdef NEWDIAGS
	      if (!isdiaginfo(u) && no(u) ==nd && eq_shape(sh(u), sh(c))) {
#else
	      if (no(u) ==nd && eq_shape(sh(u), sh(c))) {
#endif
		replace(u, copy(c), bro(def));
		nextu = pt(u); /* it could have changed */
		kill_exp(u, bro(def));
		nuses--;
		changed = 1;
	      }
	      u = nextu;
	    }
	  }
	  if (nuses==0 || last(c)) {
	    break;
	  }
	  c = bro(c);
	  nd+=sz;
	}
	if ((no(e) ==0 || pt(e) == NULL) && !isenvoff(e)) {
	  repbyseq(e);
	  return 1;
	}
      return changed;
      }

  return 0;
}
