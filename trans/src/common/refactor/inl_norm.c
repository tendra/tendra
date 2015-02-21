/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * normalised_inlining chooses the order in which inlining is to be done.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>


#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shape.h>

#include <main/flags.h>

#include <refactor/const.h>
#include <refactor/optimise.h>

#ifdef TDF_DIAG4
#include <diag4/dg_aux.h>
#endif

int print_inlines = 0;

/*
 * test a declaration to see that the identifier is only used as an
 * applied procedure.
 */
int
apply_only(exp e)
{
	exp t = pt(e);
	int ao = 1;
	exp f;
	while (ao && t != NULL) {
#ifdef TDF_DIAG4
		if (isdiaginfo(t)) {
			t = pt(t);
		} else {
			f = father(t);
			if (name(f) == apply_tag && son(f) == t) {
				t = pt(t);
			} else {
				ao = 0;
			}
		}
#else
		f = father(t);
		if (name(f) == apply_tag && son(f) == t) {
			t = pt(t);
		} else {
			ao = 0;
		}
#endif
	}
	return ao;
}


void
normalised_inlining(void)
{
  int proc_count = 0;
  dec *my_def;
  dec **to_dec;
  exp def;
  int i;
  int j;
  char *consider;
  int *order;
  char *uses;
  int changed;
  int low;
  int high;
  int no_inlined =0;

  if (~optim & OPTIM_INLINE_PROCS) {
    return;
  }

  /* count the defined procedures */
  for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
    exp crt_exp = my_def -> dec_exp;

    def = son(crt_exp);
    if (def != NULL && !isvar(crt_exp) && name(def) == proc_tag &&
        !isrecursive(def) && apply_only(crt_exp) && !proc_has_setjmp(def) &&
        !proc_uses_crt_env(def) && !proc_has_alloca(def) && !proc_has_lv(def)) {
      proc_count++;
    }
  }

  /*
   * Allocate
   * a matrix, uses, to hold uses[i, j] - i calls j
   * a vector, to_dec, to hold dec* (number -> dec)
   * a vector, consider, 1 if still considering.
   * a vector, order, of the procedure numbers (+1) ordered
   */

  if (proc_count == 0) {
    uses     = NULL;
    to_dec   = NULL;
    consider = NULL;
    order    = NULL;
  } else {
    uses     = (char *)xcalloc(proc_count * proc_count, sizeof(char));
    to_dec   = (dec **)xcalloc(proc_count, sizeof(dec *));
    consider = (char *)xcalloc(proc_count, sizeof(char));
      /* assumes calloc clears consider */
    order    = (int *) xcalloc(proc_count, sizeof(int));
      /* assumes calloc clears order */
  }

  /*
   * Form the to_dec vector and set index in each proc dec.
   * set consider vector.
   */

  i = 0;
  for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
    exp crt_exp = my_def->dec_exp;

    def = son(crt_exp);
    if (def != NULL && !isvar(crt_exp) && name(def) == proc_tag &&
        !isrecursive(def) && apply_only(crt_exp) && !proc_has_setjmp(def) &&
        !proc_uses_crt_env(def) && !proc_has_alloca(def) && !proc_has_lv(def)) {
      to_dec[i] = my_def;
      my_def -> index = i;
      consider[i] = 1;
      i++;
    }
  }

  /* Form uses matrix: uses[i, j] implies i calls j */

  for (i = 0; i < proc_count; i++) {
    exp crt_exp = to_dec[i]->dec_exp;

    if (no(crt_exp) == 0 || son(crt_exp) == NULL) {
      consider[i] = 0;
    } else {
      exp t = pt(crt_exp);

      while (t != NULL) {
	exp k = t;
#ifdef TDF_DIAG4
	if (isdiaginfo(t)) {
	  t = pt(t);
	  continue;
	}
#endif
	while (k != NULL && name(k) != hold_tag && name(k) != 102 &&
	       name(k) != proc_tag && name(k) != general_proc_tag) {
	  k = bro(k);
	}
	if (k != NULL && name(k) == proc_tag) {
	  int up = brog(bro(k))->index;
	  if (up >=0 && up< proc_count) {
	  	uses[proc_count *up + i] = 1;
	  }
	}
	t = pt(t);
      }
    }
  }

  /* Form the order list from uses */

  low = 0;
  high = proc_count - 1;
  changed = 1;
  while (changed) {
    changed = 0;

    for (i = 0; i < proc_count; i++) {
      if (consider[i]) {
        int good = 1;
        for (j = 0; good && j < proc_count; j++) {
	  if (consider[j] && uses[i * proc_count + j] == 1)
	    good = 0;
        }
	if (good) {
	  consider[i] = 0;
	  order[low++] = i + 1;
	  changed = 1;
	}
      }
    }

    for (i = 0; i < proc_count; i++) {
      if (consider[i]) {
        int good = 1;
        for (j = 0; good && j < proc_count; j++) {
	  if (consider[j] && uses[j * proc_count + i] == 1)
	    good = 0;
        }
	if (good) {
	  consider[i] = 0;
	  order[high--] = i + 1;
	  changed = 1;
	}
      }
    }
  }

  /* Permit inlining of static recursive functions */

  for (i = 0; i < proc_count; i++) {
    if (consider[i]) {
      order[low++] = i + 1;
    }
  }

  /* Try to inline in given order */

  for (i = proc_count-1; i >= 0; i--) {
    if (order[i] > 0) {
      exp crt_exp;
      exp t;
      exp k;
      int total_uses;
      int crt_uses;
      int this_changed = 1;
      my_def = to_dec[order[i] - 1];
      crt_exp = my_def->dec_exp;
      def = son(crt_exp);
      total_uses = no(crt_exp);
#ifdef TDF_DIAG4
      if (diag != DIAG_NONE) {
	start_diag_inlining(def, my_def->dg_name);
      }
#endif

      while (this_changed) {
        this_changed = 0;
	t = pt(crt_exp);
	crt_uses = no(crt_exp);
        while (t != NULL) {
      	  exp nextt = pt(t);
	  exp dad;
#ifdef TDF_DIAG4
	  if (isdiaginfo(t)) {
	    t = pt(t);
	    continue;
	  }
#endif
	  dad = father(t);
	  if (istoinline(dad)) {
	    inline_exp(dad);

	    k = t;
	    while (k != NULL && name(k) != hold_tag && name(k) != proc_tag) {
	      k = bro(k);
	    }
	    if (print_inlines) {
	      IGNORE fprintf(stderr, "%s inlined in %s\n",
			     my_def->dec_id,
			     brog(bro(k))->dec_id);
	    }

	    this_changed = 1;
	    break;
	  } else if (no_inlined > 10000) {
	    break; /* Pathological expansion in AVS */
          } else {
	    int ch = inlinechoice(t, def, total_uses);
	    if (ch == 0) {
	      break;
	    }
	    if (ch == 2) {
	      inline_exp(dad);
	      no_inlined++;

	      k = t;
	      while (k != NULL && name(k) != hold_tag &&
		     name(k) != proc_tag) {
	        k = bro(k);
	      }
	      if (print_inlines) {
	        IGNORE fprintf(stderr, "%s inlined in %s\n",
			       my_def->dec_id,
			       brog(bro(k))->dec_id);
	      }

	      this_changed = 1;
	      break;
	    }
	  }
	  t = nextt;
        }
	if (crt_uses <= no(crt_exp)) {
	  break;
	}
      }
#ifdef TDF_DIAG4
      if (diag != DIAG_NONE) {
	end_diag_inlining(def, my_def->dg_name);
      }
#endif
    }
  }

  xfree((void *)to_dec);
  xfree((void *)uses);
  xfree((void *)consider);
  xfree((void *)order);
}
