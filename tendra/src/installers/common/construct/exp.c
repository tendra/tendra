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
$Author: pwe $
$Date: 1998/03/11 11:03:24 $
$Revision: 1.3 $
$Log: exp.c,v $
 * Revision 1.3  1998/03/11  11:03:24  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:10  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1998/01/09  09:28:45  pwe
 * prep restructure
 *
 * Revision 1.6  1997/10/23  09:24:10  pwe
 * extra diags
 *
 * Revision 1.5  1997/02/18  12:56:23  currie
 * NEW DIAG STRUCTURE
 *
 * Revision 1.4  1996/07/23  12:28:37  currie
 * copying env_offsets
 *
Revision 1.3  1996/04/19 10:42:28  currie
Globals flags in copy

 * Revision 1.2  1995/10/11  17:10:00  currie
 * avs errors
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/




#include "config.h"
#include "common_types.h"
#include "externs.h"
#include "xalloc.h"
#include "installglob.h"
#include "expmacs.h"
#include "tags.h"
#include "table_fns.h"
#include "shapemacs.h"
#include "check.h"
#include "flpt.h"
#include "basicread.h"
#include "messages_c.h"
#include "install_fns.h"
#include "flags.h"
#ifdef NEWDIAGS
#include "readglob.h"
#include "dg_aux.h"
#endif
#include "exp.h"

/* VARIABLES */
/* All variables initialised */

int crt_labno = 0;	/* init by init_exp */
  /* the list of unused returned cells */
exp freelist;	/* init by init_exp */
  /* the number of unused cells in the block */
int exps_left;	/* init by init_exp */

  /* the next free pointer in the block which is used if the freelist
     is empty */
static exp next_exp_ptr;	/* no need to init */


  /* the types used to record a list of blocks for reuse, if
     separate_units is set */
struct expalloc_cell_t {struct expalloc_cell_t * tl; exp hd;};
typedef struct expalloc_cell_t expalloc_cell;

static expalloc_cell * alloc_list = (expalloc_cell *)0;
		/* good init for the whole run */
static expalloc_cell * alloc_freelist = (expalloc_cell *)0;
		/* good init for the whole run */


static char  ic_buff[21];	/* no init needed */

/* IDENTITY */

static int current_alloc_size = 20000;

/* PROCEDURES */

void altered PROTO_S ( ( exp, exp ) ) ;

exp next_exp
    PROTO_Z ()
{
  exp res;
  if (freelist != nilexp)
    {  /* first try to allocate fron the freelist */
      res = freelist;
      freelist = son(freelist);
      return res;
    };

    /* if the freelist is empty we allocate from a block of exps */
  if (exps_left == 0)
   {  /* if the block is empty we must allocate another */
     if (alloc_freelist)
       {  /* if there is anything in this list of blocks we can reuse
             it and we do not need to calloc */
         exps_left = current_alloc_size;
         next_exp_ptr = alloc_freelist -> hd;
         alloc_freelist = alloc_freelist -> tl;
       }
     else
       {  /* otherwise we must calloc a new block */
         exps_left = current_alloc_size;
         next_exp_ptr = (exp)xcalloc(exps_left, sizeof(struct exp_t));
          { /* and if we are after the start of tagdefs we put
               the block on to alloc_list so that it can be reused
               for the next unit */
            expalloc_cell * temp =
               (expalloc_cell *)xmalloc(sizeof(expalloc_cell));
            temp -> tl = alloc_list;
            temp -> hd = next_exp_ptr;
            alloc_list = temp;
          };
       };
   };

  --exps_left;
  res = next_exp_ptr++;
  return res;
}

void set_large_alloc
    PROTO_Z ()
{
  /* called at the start of tagdefs */
  alloc_freelist = alloc_list;
  freelist = nilexp;
  exps_left = 0;
  return;
}

   /* create a new exp */
exp getexp
    PROTO_N ( (s, b, l, sn, px, pr, n, tg) )
    PROTO_T ( shape s X exp b X int l X exp sn X exp px X prop pr X int n X unsigned char tg )
{
  exp res = next_exp();
  sh(res) = s;
  bro(res) = b;
  if (l)
   setlast(res);
  else
   clearlast(res);
  son(res) = sn;
  pt(res) = px;
  props(res) = pr;
  no(res) = n;
  name(res) = tg;
  parked(res) = 0;
#ifdef NEWDIAGS
  dgf(res) = nildiag;
#endif
  return res;
}

exp copyexp
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  exp res = next_exp();
  *res = *e;
  return res;
}

  /* makes a new shape */
exp getshape
    PROTO_N ( (l, sn, px, pr, n, tg) )
    PROTO_T ( int l X alignment sn X alignment px X alignment pr X int n X unsigned char tg )
{
  exp res = next_exp();
  if (l)
   setlast(res);
  else
   clearlast(res);
  res ->sonf.ald = sn;
  res -> ptf.ald = px;
  res -> brof.ald = pr;
  no(res) = n;
  name(res) = tg;
  return res;
}

  /* return an exp cell to the freelist */
void retcell
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  son(e) = freelist;
  freelist = (e);
  return;
}


  /* true if part is inside whole */
int internal_to
    PROTO_N ( (whole, part) )
    PROTO_T ( exp whole X exp part )
{
  int f = 1;
  exp q = part;
  while (q != whole && q != nilexp &&
      !(name (q) == ident_tag && isglob (q))) {
    f = (int)(last (q));
    q = bro (q);
  };
  /* ascend from part until we reach either whole or top of tree */
  return (f && q == whole);
}

static void kill_el PROTO_S ((exp e, exp scope));

  /* kill an exp, return it and its components to the freelist,
     if necessary remove uses of tags and labels, and propagate
     changes to identity and variable declarations and to labels
     but not outside scope */
void kill_exp
    PROTO_N ( (e, scope) )
    PROTO_T ( exp e X exp scope )
{
  if (e != nilexp) {
    unsigned char n = name (e);


    if (n == name_tag) {
      exp q = son (e);
#ifdef NEWDIAGS
      if (!isdiaginfo(e))
	--no (son (e));		/* decrease usage count */
#else
      --no (son (e));		/* decrease usage count */
#endif
      while (pt (q) != e)
	q = pt (q);
      pt (q) = pt (e);		/* remove from usage list */
      if (
          no (son (e)) == 0 &&
	  son (son (e)) != nilexp &&
	  bro (son (son (e))) != nilexp &&
	  (scope == nilexp || internal_to (scope, son (e))))
	IGNORE check (son (e), scope);
      /* check the declaration if now no use */
      retcell (e);
      return;
    };

    if (n == solve_tag) {
      int looping;
      if (!last (son (e))) {
	exp t = bro (son (e));
	do {
	  no (son (t)) = 0;
	  looping = !last (t);
	  t = bro (t);
	}
	while (looping);
      };
      if (pt(e) != nilexp)
        son (pt (e)) = nilexp;
      kill_el (son (e), scope);
      retcell (e);
      return;
    };

    if (n == ident_tag) {
      ++no (e);
      kill_el (son (e), scope);
#ifdef NEWDIAGS
      if (diagnose && pt(e))	/* allow diags to hold on to id */
	diag_kill_id (e);
      else
#endif
      retcell (e);
      return;
    };


    if (n == labst_tag) {
      ++no (e);
      --proc_label_count;
      kill_el (bro (son (e)), scope);
      retcell (son (e));
      retcell (e);
      return;
    };

    if (n == case_tag) {
      exp b = bro(son(e));
      while (b != nilexp) {
	exp nextb = bro(b);
	int l = last(b);
	--no(son(pt(b)));
	if (son(b) != nilexp) retcell(son(b));
	retcell(b);
	if (l) break;
	b = nextb;
      }
      kill_exp (son (e), scope);
      retcell (e);
      return;
    };

    if (n == cond_tag) {
      no (son (bro (son (e)))) = 0;
      kill_el (son (e), scope);
      retcell (e);
      return;
    };

    if (n == rep_tag) {
      if (pt(e) != nilexp)
        son (pt (e)) = nilexp;
      no (son (bro (son (e)))) = 0;
      kill_el (son (e), scope);
      retcell (e);
      return;
    };

    if (n == real_tag || (n == val_tag && isbigval(e))) {
      flpt_ret (no (e));
      retcell (e);
      return;
    };

    if (n == val_tag) {
      retcell (e);
      return;
    };

    if (n == env_offset_tag || n == string_tag || n==general_env_offset_tag)
     {
      retcell (e);
      return;
     };

    {
      exp p = pt (e);
      if (p != nilexp && (props (son (p)) & 1) == 0) {
	/* decrease label usage count */
	--no (son (p));
	if (
            no (son (p)) == 0 && !is_loaded_lv(p) &&
	    bro (son (p)) != nilexp &&
	    (scope == nilexp || internal_to (scope, p)))
	  altered (p, scope);	/* process if now no use of label and not
				   doing deadvar */
      };
      kill_el (son (e), scope);
      retcell (e);
      return;
    };
  };
}


/* kill the arguments of a construction */
static void kill_el
    PROTO_N ( (e, scope) )
    PROTO_T ( exp e X exp scope )
{
  if (e != nilexp) {
    int l;
    exp next;
    do {
      l = (int)(last (e));
      next = bro (e);
      kill_exp (e, scope);
      e = next;
    }
    while (!l && e != nilexp);
  };
}

  /* return the shape delivered by a conditional (or similar construct)
     which delivers an a from one branch and a b from the other */
shape lub_shape
    PROTO_N ( (a, b) )
    PROTO_T ( shape a X shape b )
{
  int asz = shape_size(a);
  int bsz = shape_size(b);
  if (name(a) ==bothd)
   return b;
  if (name(b) == bothd)
   return a;
  if (asz == bsz && shape_align(a) == shape_align(b))
    return (a);
  return (f_top);
}

  /* true if the shapes are equal */
int eq_shape
    PROTO_N ( (a, b) )
    PROTO_T ( shape a X shape b )
{
  if (name(a) != name(b))
     return 0;
  if (shape_size(a)!=shape_size(b) ||
           is_signed(a)!=is_signed(b) ||
           shape_align(a)!=shape_align(b) ||
           al1(a)!=al1(b))
     return 0;
  if (name(a) == nofhd)
     return 1;
  else
     return (al2(a)==al2(b));
}

  /* source of numbers for local labels */
int next_lab
    PROTO_Z ()
{
  return crt_labno++;
}

char *intchars
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  int  r, d;
  char *ind;

  ind = &ic_buff[19];
  ic_buff[20] = 0;
  d = (n < 0) ? -n : n;

  do {
    r = d % 10;
    d = d / 10;
    *ind = (char)(r + 48); /* CAST:jmf: must be in 48:57 */
    --ind;
  }
  while (d != 0);
  if (n < 0) {
    *ind = '-';
    --ind;
  };

  return (ind + 1);
}


void case_item
    PROTO_N ( (i) )
    PROTO_T ( exp i )
{
  exp l = global_case;
  exp t = l;
  int go = 1;
  exp  newhigh = (son (i) == nilexp) ? i : son (i);
  exp  thigh;
  exp  nlow,
        nhigh;

  while (go && bro (t) != nilexp) {
    exp j = bro (t);
    exp  highj = (son (j) == nilexp) ? j : son (j);
    if (docmp_f((int)f_greater_than, i, highj))
      t = bro (t);
    else
      go = 0;
  };

  if (t != l) {
    thigh = (son (t) == nilexp) ? t : son (t);
  }
  else {
    SET(thigh);
  };

  if (bro (t) != nilexp) {
    nlow = bro (t);
    nhigh = (son (bro (t)) == nilexp) ? nlow : son (bro (t));
  }
  else {
    SET(nlow); SET(nhigh);
  };

  if (t != l && docmp_f((int)f_less_than_or_equal, i, thigh))
    failer (CASE_OVERLAP);
  if (bro (t) != nilexp &&
	 docmp_f((int)f_greater_than_or_equal, newhigh, nlow))
    failer (CASE_OVERLAP);

  if (isbigval(i) || isbigval(newhigh)) {
    bro (i) = bro (t);
    bro (t) = i;
    return;
  };

  if (t != l && (no(i)-1) == no(thigh) && pt (i) == pt (t)) {
    if (bro (t) != nilexp && (no(newhigh)+1) == no(nlow)
	&& pt (i) == pt (bro (t))) {
      if (son (bro (t)) != nilexp) {
	if (son (t) != nilexp)
	  retcell (son (t));
	son (t) = son (bro (t));
	bro (t) = bro (bro (t));
	return;
      };
      if (son (t) != nilexp) {
	no (son (t)) = no(nhigh);
	bro (t) = bro (bro (t));
	return;
      };
      setson (t, getexp (slongsh, nilexp, 1, nilexp, nilexp, 0,
			  no(nhigh), 0));
      bro (t) = bro (bro (t));
      return;
    };
    if (son (t) != nilexp) {
      no (son (t)) = no(newhigh);
      return;
    };
    setson (t, getexp (slongsh, nilexp, 1, nilexp,
			 nilexp, 0, no(newhigh), 0));
    return;
  };

  if (bro (t) != nilexp && (no(newhigh) + 1) == no(nlow)
      && pt (i) == pt (bro (t))) {
    if (son (bro (t)) != nilexp) {
      no (bro (t)) = no(i);
      return;
    };
    if (son (i) != nilexp) {
      no (son (i)) = no(nhigh);
      bro (i) = bro (bro (t));
      bro (t) = i;
      return;
    };
    son (i) = bro (t);
    bro (i) = bro (bro (t));
    bro (t) = i;
    return;
  };

  bro (i) = bro (t);
  bro (t) = i;
  return;
}


/*******************************************************************
  scan_solve is part of the process of reading a solve construction.
  It scans the exp e, to increment the count of labels used by e.
 *******************************************************************/
void scan_solve
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  unsigned char  n = name (e);
  switch (n) {
    case name_tag:
    case make_lv_tag:
    case env_offset_tag:
    case general_env_offset_tag:
      return;
    case clear_tag:
      return;
    case ident_tag: {
	scan_solve (son (e));
	scan_solve (bro (son (e)));
	return;
      };
    case case_tag:
      {
	exp t = son (e);
	while (!last (t)) {
	  exp s = son (pt (bro (t)));
	  if (isvar (s)) {
	    ++no (s);
	  };
	  t = bro (t);
	};
	scan_solve (son (e));
	return;
      };
    default:
      {
	if (pt (e) != nilexp) {
	  exp s = son (pt (e));
	  if (isvar (s)) {
	    ++no (s);
	  };
	};
	if (son (e) != nilexp) {
	  exp t = son (e);
	  while (scan_solve (t), !last (t))
	    t = bro (t);
	};
	return;
      };
  };
}
/*********************************************************************
  clean_labelled processes a labelled statement after it has been read.
  It places the labelled statements in a good order.
 *********************************************************************/

exp clean_labelled
    PROTO_N ( (main, placelabs) )
    PROTO_T ( exp main X label_list placelabs )
{
  int   i,
        crt_no;
  int go = 1;
  shape s;
  exp r, q;
  int n = placelabs.number;
  int  *ord;			/* records the order in which the
				   statemnts are to be placed */
  int   ord_no;
  for (i = 0; i < n; ++i) {	/* set up the labels */
    exp l = get_lab(placelabs.elems[i]);
    exp t = son (l);
    no (t) = is_loaded_lv(l);
    setcrtsolve (t);		/* defined in expmacs = props(t) = 1 */
  };
  crt_no = 0;
  ord = (int *) xcalloc (n, sizeof (int));
  ord_no = 0;
  scan_solve (main);		/* mark the labels used by the initiator
				*/
  while (go) {			/* continue as long as we have added a
				   statement */
    go = 0;
    for (i = 0; i < n; ++i) {	/* look for unprocessed but used sts */
      int   j = ((i + crt_no) % n);
      exp t = get_lab(placelabs.elems[j]);
      if ((props (son (t)) & 8) == 0 && no (son (t)) != 0) {
	/* we have found an unprocessed but used statement */
	go = 1;
	props (son (t)) = 5;
	scan_solve (t);		/* now scan it to mark the things it uses
				*/
	props (son (t)) = (prop)((props (son (t)) & 0xfb) | 8);
	ord[ord_no++] = j;
      };
    };
  };
  s = sh (main);
  for (i = 0; i < n; ++i) {
    exp lab = get_lab(placelabs.elems[i]);
    exp t = son (lab);
    if ((props (t) & 8) != 8) {
      kill_exp (bro (t), bro (t));/* remove unwanted statements */

    }
    else
      s = lub_shape (s, sh (lab));
    /* form the result shape of the whole */
  };
  r = getexp (s, nilexp, 0, main, crt_repeat, 0, 0, solve_tag);
  q = main;
  for (i = 0; i < ord_no; ++i) {/* set up the solve with the statements in
				   the order specified by ord */
    clearlast (q);
    bro (q) = get_lab(placelabs.elems[ord[i]]);
    q = bro (q);
    props (son (q)) = (prop)(props(son(q)) & 0xfe);
  };
  son (crt_repeat) = r;
  crt_repeat = bro(crt_repeat);
  setfather(r, q);
  return (r);
}

/* find the (unique) downward reference to e */
exp * refto
    PROTO_N ( (f, e) )
    PROTO_T ( exp f X exp e )
{
  exp * x = &son (f);
  while (*x != e)
    x = &bro (*x);
  return (x);
}

/* find the father of u */
exp father
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  if (e == nilexp)
    return (e);
  while (!last (e))
    e = bro (e);
  return (bro (e));
}

/* auxiliary routine for altered, looks up
   in the tree n levels, checking */
static void altaux
    PROTO_N ( (e, n, scope) )
    PROTO_T ( exp e X int n X exp scope )
{
  exp f;
  if (bro (e) == nilexp || e == scope ||
      (name (e) == ident_tag && isglob (e)))
    return;			/* ignore if top of tree */
  f = father (e);
  if (f == nilexp || bro (f) == nilexp ||
      (name (f) == ident_tag && isglob (f)))
    return;			/* ignore if top of tree */
  if (name (f) == 0) {
    altaux (f, n, scope);
    return;
  };
  if (!check (f, scope) && n > 1) {
    /* do check until n is exhausted */
    altaux (f, n - 1, scope);
    return;
  };
}

/* e has been altered. see if any exp
   higher up the tree can now recognise an
   optimisation (using check) */
void altered
    PROTO_N ( (e, scope) )
    PROTO_T ( exp e X exp scope )
{
  altaux (e, 1, scope);
}

/* replace old by e, and (if not doing
   deadvar) check whether any
   consequential optimisations are
   possible */
void replace
    PROTO_N ( (old, e, scope) )
    PROTO_T ( exp old X exp e X exp scope )
{
  exp f = father (old);
  exp * ref = refto (f, old);
  if (last (*ref))
    setlast (e);
  else
    clearlast (e);
  bro (e) = bro (*ref);
  *ref = e;
  if (scope == old)
    return;
  altered (e, scope);
}

/* copy a labelled statement and put links
   into pt so that copies of uses of the
   original can refer to the copy */
void copy_labst
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  exp t = copyexp (e);
  exp d = copyexp (son (e));
  setcopy(e);
  no (t) = 0;
  no (d) = 0;
  pt (d) = pt (e);
  pt (t) = nilexp;
  pt (e) = t;
  son (t) = d;
  ++proc_label_count;
}

/* end the copy of a labelled statement
   and restore the original state */
exp undo_labst
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  exp r = pt (e);
  pt (e) = pt (son (r));
  clearcopy(e);
  return (r);
}

exp copy_res PROTO_S ( ( exp, exp, exp ) ) ;
exp copy PROTO_S ( ( exp ) ) ;

/* used to copy cond, repeat and solve so
   that copies of references to the
   labelled statements can refer to the
   copies of the labelled statements */
static exp copy_cpd
    PROTO_N ( (e, new_record, var, lab) )
    PROTO_T ( exp e X exp new_record X exp var X exp lab )
{
  exp t = copyexp (e);
  exp q;
  exp j, c, s, n, k;

  if (new_record != nilexp) {	/* record the construction */
    pt (t) = new_record;
    son (new_record) = t;
  };

  /* copy the labelled statements */
  q = bro (son (e));
  copy_labst (q);
  while (!last (q)) {
    q = bro (q);
    copy_labst (q);
  }

  /* copy the bodies of the labelled statments */
  q = bro (son (e));
  while (j = copy_res (bro (son (q)), var, lab),
      c = pt (q),
      bro (son (c)) = j,
      bro (j) = c,
      setlast (j),
      !last (q))
    q = bro (q);

  /* copy the lead statement */
  s = copy_res (son (e), var, lab);
  son (t) = s;
  clearlast (s);
  q = bro (son (e));
  n = s;

  /* restore the labelled statements */
  while (k = undo_labst (q),
      bro (n) = k,
      clearlast (n),
      !last (q)) {
    q = bro (q);
    n = bro (n);
  };

  n = bro (n);
  setlast (n);
  bro (n) = t;
  return (t);
}

/******************************************************************
  copy copies e and all its sub-cells recursively, amending usage
  counts as necessary. It sets up identifier usage lists for the
  declarations which it copies.
 ******************************************************************/

exp copy_res
    PROTO_N ( (e, var, lab) )
    PROTO_T ( exp e X exp var X exp lab )
{
  if (e == nilexp)
    return (e);
#ifdef NEWDIAGS
  else
  if (dgf(e) != nildiag)
    return copy_res_diag (e, dgf(e), var, lab);
#endif
  else {
    unsigned char n = name (e);

    if (n == ident_tag) {
      exp t = copyexp (e);
      exp x = pt (e);		/* remember the usage list */
      exp s, bs;
      setcopy (e);		/* mark e as being copied */
      no (t) = 0;		/* clear the usage count */
      pt (e) = t;		/* record the copy in the pt field of the
				   original */
      pt (t) = nilexp;		/* set the new usage list to empty */
      s = copy_res (son (e), var, lab);	/* copy the definition */
      bs = copy_res (bro (son (e)), var, lab);/* copy the body */
      son (t) = s;
      bro (s) = bs;
      bro (bs) = t;
      clearlast (s);
      setlast (bs);
      pt (e) = x;		/* reset the remembered usage list */
      clearcopy (e);		/* remove the copying flag */
      if (n == ident_tag)
	sh (t) = sh (bro (son (t)));/* in case bro(son(t)) is a tuple */
      return (t);
    };

    if (n == name_tag) {
      /* see if the corresponding declaration is being copied and pick up
         the correct usage list */
      exp tp = (copying (son (e)) ? pt (son (e)) : son (e));
      exp r = copyexp (e);
      son (r) = tp;		/* add this use onto the correct usage
				   list */
      pt (r) = pt (tp);
      pt (tp) = r;
#ifdef NEWDIAGS
      if (!isdiaginfo(r))
#endif
      {
	++no (tp);		/* increment the correct usage count */
	if (isglob(tp)) proc_externs = 1;
      }
      return (r);
    };

    if (n == env_offset_tag || n == general_env_offset_tag) {
      /* see if the corresponding declaration is being copied and pick up
         the correct usage list */
      exp tp = (copying (son (e)) ? pt (son (e)) : son (e));
      exp r = copyexp (e);
      son (r) = tp;		/* add this use onto the correct usage
				   list */
      return (r);
    };

    if (n == cond_tag) {
      exp z = copy_cpd (e, nilexp, var, lab);
      return (z);
    };

    if (n == rep_tag || n == solve_tag) {
      /* we have to update the repeat records */
      exp record = pt (e);
      exp z;
      if (record != nilexp) {
        exp senior = bro (record);
        exp new_record = copyexp (record);
	if (senior == nilexp) { /* XX008 */
	  senior = crt_repeat;
	  bro(new_record) = senior;
	};
        set_copying_solve (record);/* mark as being copied */
        pt (record) = new_record;

        if (senior != nilexp) {	/* update repeat records */
	  if ((props (senior) & 1) == 1)
	    bro (new_record) = pt (senior);
	  else
	    ++no (senior);
        };
        z = copy_cpd (e, new_record, var, lab);
        clear_copying_solve(record);	/* unmark copying flag */
      }
      else {
	z = copy_cpd (e, nilexp, var, lab);
      };
      return (z);
    };

    if (n == case_tag) {
      exp t = copy_res (son (e), var, lab);
      exp z = copyexp (e);
      exp q = son (e);
      exp p = t;
      exp labloc, tp;
      son (z) = t;
      while (!last (q)) {
	setbro (p, copyexp (bro (q)));
	if (son (bro (q)) != nilexp)
	  setson (bro (p), copyexp (son (bro (q))));
	labloc = pt (bro (p));
	tp = (copying(labloc)) ? pt (labloc) : labloc;
	pt (bro (p)) = tp;
	no (son (tp))++;
	p = bro (p);
	q = bro (q);
      };
      bro (p) = z;
      if (PIC_code) proc_externs = 1;
      return (z);
    };

    if (n == real_tag || (n == val_tag && isbigval(e))) {
      exp z = copyexp (e);
      flpt f = new_flpt ();
      flt_copy (flptnos[no (e)], &flptnos[f]);
      no (z) = f;
      if (PIC_code) proc_externs =1;
      return (z);
    };

   if (n == string_tag)
    {
      exp r = copyexp(e);
      if (PIC_code) proc_externs =1;
      return (r);
    };

    if (n == res_tag) {
      if (lab != nilexp) {
	exp go = getexp(f_bottom, nilexp, 0, nilexp, lab,
			 0, 0, goto_tag);
	no(son(lab))++;

	if (name(son(e)) == clear_tag) {
#ifdef NEWDIAGS
	  if (extra_diags)
	    diag_inline_result (go);
#endif
	  return go;
	}
        else
        if (var == nilexp) {
	  exp_list el;
          exp c = copy(son(e));
	  exp s;
	  el.start = c;
	  el.end = c;
	  el.number = 1;
	  s = f_sequence(el, go);
#ifdef NEWDIAGS
	  if (extra_diags)
	    diag_inline_result (go);
	  return diag_hold_check (s);	/* not inlining */
#else
          return hold_check(s);
#endif
	}
	else {
	  exp ass;
	  exp_list el;
	  exp old_var;
	  exp ident;

	  old_var = copyexp(var);	/* careful - we must not use
					   copy on var because it belongs
					   in the other context recurse!
					*/
	  ident = (copying(son(var))) ? pt(son(var)) : son(var);
	  pt(old_var) = pt(ident);
	  pt(ident) = old_var;
	  ++no(ident);
	  ass = f_assign(old_var, copy(son(e)));
	  el.start = ass;
	  el.end = ass;
	  el.number = 1;
#if NEWDIAGS
	  if (extra_diags)
	    diag_inline_result (bro(son(ass)));
#endif
	  return f_sequence(el, go);
	};
      };

       /* FALL THROUGH if lab == nilexp */
     };
    {
      exp p = pt (e);
      exp z = copyexp (e);
      exp tp;
      switch (name(e)) {
	case alloca_tag: case apply_general_tag: has_alloca = 1; break;
	case tail_call_tag: has_alloca = 1; has_setjmp = 1; break;
	case current_env_tag: uses_crt_env = 1; uses_loc_address = 1;
		if (in_proc_def) sh(z) = f_pointer(frame_alignment);
		break;
        case untidy_return_tag: case local_free_all_tag: case long_jump_tag:
			has_setjmp = 1; break;
      }

      if (p != nilexp) {
	/* the pt field must be a label */
	/* look to see if label is being copied and pick up right
	   statement */
	tp = (copying(p)) ? pt (p) : p;
	pt (z) = tp;
	no (son (tp))++;	/* update label use count */
      };

      if (son (e) == nilexp) {
	return (z);
      };
      {
	exp t = son (e);
	exp q = copy_res (t, var, lab);
	exp ptt = q;
	while (!last (t)) {	/* copy the arguments */
	  setbro (ptt, copy_res (bro (t), var, lab));
	  clearlast (ptt);
	  t = bro (t);
	  ptt = bro (ptt);
	};
	son (z) = q;
	bro (ptt) = z;
	setlast (ptt);

	if (n == labst_tag || n == seq_tag)
	  sh (z) = sh (bro (son (z)));
	/* in case bro(son(z)) is a tuple */

	return (z);
      };
    };
  }
}

exp copy
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  return copy_res(e, nilexp, nilexp);
}

int is_comm
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    if (no_bss)
      return 0;
    switch ( name ( e ) ) {

	case val_tag : return ( no ( e ) ? 0 : 1 ) ;

	case int_to_bitf_tag :
	case chvar_tag : return ( is_comm ( son ( e ) ) ) ;

	case real_tag : {
	    flpt f = no ( e ) ;
	    return ( flptnos [f].sign ? 0 : 1 ) ;
	}

	case compound_tag : {
	    exp t = son ( e ) ;
	    if ( t == nilexp ) return ( 1 ) ;
	    while ( 1 ) {
		t = bro ( t ) ;
		if ( name ( sh ( t ) ) != bitfhd ) {
		    if ( !is_comm ( t ) ) return ( 0 ) ;
		} else {
		    if ( name ( t ) == val_tag ) {
			if ( no ( t ) ) return ( 0 ) ;
		    } else {
			if ( no ( son ( t ) ) ) return ( 0 ) ;
		    }
		}
		if ( last ( t ) ) return ( 1 ) ;
		t = bro ( t ) ;
	    }
	    /* Not reached */
	}

	case ncopies_tag : return ( is_comm ( son ( e ) ) ) ;

	case nof_tag : {
	    exp t = son ( e ) ;
	    if ( t == nilexp ) return 1;
	    while ( 1 ) {
		if ( !is_comm ( t ) ) return ( 0 ) ;
		if ( last ( t ) ) return ( 1 ) ;
		t = bro ( t ) ;
	    }
	    /* Not reached */
	}

	case concatnof_tag : {
	    exp t = son ( e ) ;
	    return ( is_comm ( t ) && is_comm ( bro ( t ) ) ) ;
	}

	case clear_tag :
	case res_tag :  return ( 1 ) ;

	case null_tag : return ( no(e) == 0 ) ;
    }
    return ( 0 ) ;
}
