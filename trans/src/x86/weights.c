/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>
#include <limits.h>

#include <shared/check.h>

#include <reader/basicread.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>

#include <main/flags.h>

#include "localtypes.h"
#include "make_code.h"
#include "cproc.h"
#include "weights.h"
#include "localexpmacs.h"


/* MACROS */

#define max(x,y)((x>=y)?(x):(y))

#define wno 6
 /* number of available registers */
#define wfno 7
 /* number of available floating point registers */

/* IDENTITIES */

static float vzeros[wno + wfno] = {
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

/* for the move instruction */
static float vmoveregs[wno + wfno] = {
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

/* for the cmp instruction */
static float vcmpregs[wno + wfno] = {
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

/* for the div instruction */
static float vdivregs[wno + wfno] = {
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

/* for apply */
static float vapplyregs[wno + wfno] = {
  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};


struct wt {
  float  w_weights[wno + wfno];
  int  booked;
  int  flbooked;
};

typedef struct wt   weights;
				/* weights[i] is the value of putting a
				   declaration in a register if there are
				   i registers available. */

struct wpt {
  weights wp_weights;
  int  wp_break;		/* break is the number of registers that
				   must be available at this point for it
				   to be worthwhile putting this value in
				   a register */
};

typedef struct wpt  wp;

struct elt {
  exp wident;
  struct elt *etl;
};
typedef struct elt  explist;
				/* list of identity declarations in force
				   at this point */

static weights weightsv(exp, explist *);

/* VARIABLES */

/* init by init_weights */
static weights zeros, moveregs, cmpregs, divregs, applyregs;




/* PROCEDURES */

static int no_side_aux
(exp e)
{
  exp arg;
  if (name(e) ==name_tag || name(e) ==env_offset_tag || name(e) ==top_tag || son(e) ==NULL)
    return 1;
  for (arg=son(e);; arg=bro(arg))
  {
    if ((!is_a(name(arg)) && name(arg)!= ident_tag) || !no_side_aux(arg))
      return 0;
    if (last(arg))
      return 1;
  }
}


/* test for guaranteed no side effect */
/* simple assignment is permitted */
int no_side
(exp e)
{
  return (is_a(name(e)) || name(e) == test_tag || name(e) == ass_tag ||
	   name(e) == testbit_tag || name(e) == ident_tag)
	&& no_side_aux(e);
}

/* add two weight vectors */
static weights
add_weights(weights w1, weights w2)
{
  weights r;
  float  wa,
         wb;
  int i;
  for (i = 0; i < (wno + wfno); ++i) {
    wa = (w1.w_weights)[i];
    wb = (w2.w_weights)[i];
   (r.w_weights)[i] = wa + wb;
  }
  r.booked = max(w1.booked, w2.booked);
  r.flbooked = max(w1.flbooked, w2.flbooked);
  return r;
}

void init_weights
(void)
{
		/* initialisation of constants */
  int  i;
  for (i = 0; i < (wno + wfno); ++i) {
   (zeros.w_weights)[i] = vzeros[i];
   (moveregs.w_weights)[i] = vmoveregs[i];
   (cmpregs.w_weights)[i] = vcmpregs[i];
   (divregs.w_weights)[i] = vdivregs[i];
   (applyregs.w_weights)[i] = vapplyregs[i];
  }
  zeros.booked = -1;
  moveregs.booked = 1;
  cmpregs.booked = 1;
  divregs.booked = 1;
  applyregs.booked = 1;

  zeros.flbooked = -1;
  moveregs.flbooked = -1;
  cmpregs.flbooked = -1;
  divregs.flbooked = -1;
  applyregs.flbooked = 2;
}

static void
markcall(explist * el)
{
  explist * t = el;
  while (t != NULL) {
    set_intnl_call(t -> wident);
    t = t -> etl;
  }
}

/* mark all the declarations in the list
   of currently active declarations, to
   show that there is a call, movc3 etc.
   within their scope */
static void
markmove(explist * el)
{
  explist * t = el;
  while (t != NULL) {
    set_intnl_call(t -> wident);
    t = t -> etl;
  }
}

/* mark to show reg1 may be needed */
static void
markreg1(explist * el)
{
  explist * t = el;
  while (t != NULL) {
    set_intnl_call(t -> wident);
    t = t -> etl;
  }
}


/* work out weights for a declaration and
   set up the break point to put in the no
   field of the declaration */
static wp
max_weights(int size, float locp, weights ws, int isfl)
{
  int  k = (size + 31) / 32;
  int  bk = 11;
  int bkset = 0;
  int  q;
  int  i;
  float * w = & (ws.w_weights)[(isfl)? wno : 0];
  wp res;
  float *pw = & ((res.wp_weights).w_weights)[(isfl)? wno : 0];
  int  bkd = (isfl)? ws.flbooked : ws.booked;
  int  lwno = (isfl)? wfno : wno;
  res.wp_weights.booked = ws.booked;
  res.wp_weights.flbooked = ws.flbooked;

  for (i = 0; i < (wno + wfno); ++i)
   ((res.wp_weights).w_weights)[i] = (ws.w_weights)[i];

   {
    float  loc = locp * k;
    q = -1;
    for (i = 0; i < lwno; ++i) {
      {
	if (i < (k + q))
	  pw[i] = w[i];
	else {
	  if (i == (k + q)) {
	    if (loc >= w[i] && bkd <= q) {
	      pw[i] = loc;
	      bk = i + 1;
	      bkset = 1;
	    }
	    else
	      pw[i] = w[i];
	  }
	  else {
	    if ((loc + w[i - k]) >= w[i]) {
	      pw[i] = loc + w[i - k];
	      if (!bkset) {
		bk = i + 1;
		bkset = 1;
	      }
	    }
	    else
	      pw[i] = w[i];
	  }
	}
      }
    }
  }


  res.wp_break = bk;
  return res;
}


/* see if we must use movc3?? */
static weights
try_mc3(exp e, weights ws, explist * el)
{
  int  sz = shape_size(sh(e));

  if (sz <= 128)
    return ws;

  markmove(el);
  return add_weights(ws, moveregs);
}

/* work out the weights for a list of exp.
   usemc3 is 1 if movc3 may be used. */
static weights
add_wlist(exp re, int usemc3, explist * el)
{
  weights wl1, wl2;
  if (re == NULL)
    return zeros;

  wl1 = weightsv(re, el);
  if (usemc3)
    wl1 = try_mc3(re, wl1, el);

  while (!last(re)) {
    re = bro(re);
    wl2 = weightsv(re, el);
    if (usemc3)
      wl1 = add_weights(wl1, try_mc3(re, wl2, el));
    else
      wl1 = add_weights(wl1, wl2);
  }
  return wl1;
}



/* can the value defined by e be put in a register */
int regable
(exp e)
{
  unsigned char  n;
  shape sha = sh(son(e));
  n = name(sha);
  if (isvis(e) || n == cpdhd || n == nofhd || n == s64hd || n == u64hd)
    return 0;
  if (all_variables_visible && isvar(e))
    return 0;
  return 1;
}

static int
isflsh(shape s)
{
  unsigned char  n = name(s);
  return n >= shrealhd && n <= doublehd;
}


/* Work out weights and set break points
   scale is the expected number of times
   that this operation will be done.
   During the scan the expected number of
   times use is made of something declared
   is computed in the no of the
   declaration. After the scan the break
   point is put into the no of the
   declaration */
static weights
weightsv(exp e, explist * el)
{
  unsigned char  n = name(e);
  float old_scale;
  weights swl, bwl;

  switch (n) {
    case name_tag: {
	if (!isglob(son(e)))
	  fno (son (e)) += scale;/* add number of uses to the no field of
				   the declaration */
	return zeros;
      }
    case make_lv_tag:
        return zeros;
    case ident_tag:
       {
	explist nel;
	exp t = pt(e);
	nel.wident = e;
	nel.etl = el;
	while (isvar(e) && !isvis(e) && t != NULL) {
	  if (!(last(t) && name(bro(t)) == cont_tag) &&
              !(last(t) && name(bro(t)) == hold_tag) &&
	      !(last(bro(t)) && (name(bro(bro(t))) == ass_tag ||
		  name(bro(bro(t))) == assvol_tag
		)))
	    setvis(e);
	  t = pt(t);
	}

	if (son(e)!= NULL) {
	  weights wdef, wbody;
	  exp def = son(e);
	  exp body = bro(def);

	  if (name(sh(def)) == u64hd || name(sh(def)) == s64hd)
	    markreg1(el);

	  fno (e) = 0.0;	/* clear the accumulated value field */
	  wbody = weightsv(body, &nel);
	  /* do body (which will add to the accumulated value field */
	  if (regable(e)) {
	    wp p;
	    float  loc = fno(e);
            if (has_intnl_call(e))
               loc += 2.0;
	    p = max_weights(shape_size(sh(def)),
		(name(def) == name_tag && isusereg(e))? 1.0 : loc,
		wbody,
		isflsh(sh(def)));
	    if (name(def) == clear_tag)
	      wdef = zeros;
	    else {
	      float  sp_scale = scale;
	      if (!isvar(e) &&
		 ((name(def) == name_tag && !isvar(son(def)) &&
		     (!isglob(son(def))) && !isloadparam(def)
		   ) ||
		   (name(def) == cont_tag &&
		      name(son(def)) == name_tag &&
		      isvar(son(son(def))) &&
		     (!isglob(son(son(def)))) &&

		      no_side(body)))) {
		if (isusereg(e)) {
		  sp_scale = 8.0 * fno(e);
		}
		else
		  sp_scale = fno(e);
		p.wp_break = 0;
		p.wp_weights = wbody;
	      }
              old_scale = scale;
              scale = sp_scale;
	      wdef =
		weightsv(def, el);
	      wdef = try_mc3(def, wdef, el);
              scale = old_scale;
	    }
	    no (e) = p.wp_break;/* set the break point */
	    return add_weights(wdef, p.wp_weights);
	  }

	  if (name(sh(def)) == nofhd && ptno(sh(def)) == realhd &&
		shape_size(sh(def)) >= 640)
	    useful_double = 1;

	  if (name(def) == clear_tag)
	    wdef = zeros;
	  else {
	    wdef =
		weightsv(def, el);
	      wdef = try_mc3(def, wdef, el);
	  }
	  no(e) = 16;
	  return add_weights(wdef, wbody);
	}
	return zeros;
      }
    case labst_tag: {
	explist nel;
	weights wbody;
	nel.wident = e;
	nel.etl = el;
	old_scale = scale;
	wbody = weightsv(bro(son(e)), &nel);
	scale = old_scale;
	return wbody;
      }
    case rep_tag: {
	swl = weightsv(son(e), el);

        old_scale = scale;

        if (scale < 1e30)
		scale = 20*scale;

	bwl = weightsv(bro(son(e)), el);
        scale = old_scale;

	return add_weights(swl, bwl);
      }
    case cond_tag:  {
        old_scale = scale;

        scale = 0.5*scale;
        swl = weightsv(son(e), el);
	bwl = weightsv(bro(son(e)), el);

        scale = old_scale;

	return add_weights(swl, bwl);
      }
    case case_tag:
      return weightsv(son(e), el);

    case compound_tag:
      return add_wlist(son(e), 1, el);
      /* may use movc3 for component */

    case res_tag:
    case untidy_return_tag:
      return weightsv(son(e), el);

    case asm_tag:
    case apply_tag:
    case apply_general_tag:
    case tail_call_tag:
      {
        if (name(sh(e))!= bothd && !builtinproc(e))
	  markcall(el);
	return add_weights(add_wlist(son(e), 0, el),
	      applyregs);
      }

    case ass_tag:
    case assvol_tag: {
      /* may use movc3 for assigned value */
      unsigned char shn = name(sh(bro(son(e))));
      weights temp;
      temp = weightsv(bro(son(e)), el);
      if (shn == u64hd || shn == s64hd)
	markreg1(el);
      return add_weights(weightsv(son(e), el),
	    try_mc3(bro(son(e)), temp, el));
      }
    case proc_tag:
    case general_proc_tag: {
	IGNORE weightsv(son(e), NULL);
	return zeros;
      }
    case movecont_tag:
      if (isnooverlap(e))
        return add_weights(add_wlist(son(e), 0, el), moveregs);
      else {
        markcall(el);
        return add_wlist(son(e), 0, el);
      }
    case val_tag:
    case real_tag:
    case env_offset_tag:
      return zeros;

    case test_tag:
     {weights wlarg;
      if (name(sh(son(e))) == s64hd || name(sh(son(e))) == u64hd)
	markreg1 (el);				/* use of reg0 can include reg1 */
      wlarg = add_wlist(son(e), 0, el);
      return wlarg;
     }
    case prof_tag:
      scale = no(e);
      return zeros;

    case alloca_tag:
     {if (checkalloc(e))
	markreg1(el);
      return add_wlist(son(e), 0, el);
     }

    default:
      if (sh(e)!= NULL &&
		(name(sh(e)) == s64hd || name(sh(e)) == u64hd))
	markreg1 (el);				/* use of reg0 can include reg1 */
      return add_wlist(son(e), 1, el);
  }
}

void comp_weights
(exp e)
{
  scale = 1.0;
  IGNORE weightsv(e, NULL);
}
