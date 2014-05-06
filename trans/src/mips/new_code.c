/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* new_code.c
	This is the principal code producing module
****************************************************************/

#include <stdio.h>
#include <string.h>

#include <shared/check.h>

#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>
#include <construct/f64.h>
#include <construct/flpt.h>

#include <diag/diag_fns.h>

#include <local/exptypes.h>
#include "addrtypes.h"
#include <local/expmacs.h>
#include "loc_signal.h"
#include "maxminmacs.h"
#include "procrectypes.h"
#include "eval.h"
#include "move.h"
#include "operators.h"
#include "psu_ops.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "mips_ins.h"
#include "handle_sregs.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "special.h"
#include "new_tags.h"
#include "out_ba.h"
#include "ibinasm.h"
#include "syms.h"
#include "main.h"
#include "dump_distr.h"
#include "extratags.h"
#include "diag_out.h"
#include "frames.h"
#include "regable.h"
#include "new_code.h"

extern  FILE * as_file;
extern int current_symno;
extern  procrec * procrecs;

long  fscopefile;

ans procans;
int   rscope_level;
int   rscope_label;
int   result_label = 0;
int   currentnop;
long max_args;

where nowhere;

static exp crt_proc;

bool NONEGSHIFTS = 1;

long aritherr_lab = 0;
long stackerr_lab = 0;
long allocaerr_lab = 0;

extern exp find_named_tg(char *, shape);
extern shape f_pointer(alignment);
extern alignment f_alignment(shape);
extern shape f_proc;

typedef struct{int dble; r2l r; instore ad;} rcache;
static rcache rca[16];
static int nca = 0;

void do_exception
(int e)
{
	baseoff b;
	b.base = 0; b.offset = e;
	ls_ins(i_li, 4,  b);
	b = boff(find_named_tg("__TDFhandler", f_pointer(f_alignment(f_proc))));
	ls_ins(i_lw, 25, b);
	br_ins(i_j, 25);
}

long trap_label
(exp e)
{
	if ((errhandle(e) &3) ==3) {
          	if (aritherr_lab==0)aritherr_lab = new_label();
          	return aritherr_lab;
        }
        else return no(son(pt(e)));
}

void dump_gp
(void)
{
	baseoff b;
	b.base = 29; b.offset = locals_offset>>3;
	ls_ins(i_sw, 28, b);
}

void reset_gp
(void)
{
	baseoff b;
	if (Has_vcallees) {
		b.base = local_reg;
		b.offset = (locals_offset - frame_size) >>3;
	}
	else
	if (Has_fp) {
		b.base = 30;
		b.offset = (locals_offset - frame_size - callee_size) >>3;
	}
	else {
		b.base = 29;
		b.offset = locals_offset>>3;
        }
	ls_ins(i_lw, 28, b);
}

bool unsafe
(exp e)
{		/*  usages of parameters which might be
				   vararg */
/*
  if (last (e))
    return name (bro (e)) != cont_tag && name (bro (e)) != par_tag;
  if (last (bro (e)) && name (bro (bro (e))) == ass_tag)
    return 0;
  if (name (father (e)) == par_tag)
    return 0;
  if (last (bro (e)) && name (bro (bro (e))) == ident_tag) {
    exp u;
    if (isvar (bro (bro (e))))
      return 1;
    for (u = pt (bro (bro (e))); u != nilexp; u = pt (u)) {
      if (unsafe (u))
	return 1;
    }
    return 0;
  }
  return 1;
*/ failer("unsafe");
   return 1;
}



void checknan
(exp e, space sp)
{
           long trap = trap_label(e);
           int r1 = getreg(sp.fixed);
           int r2 = getreg(guardreg(r1, sp).fixed);
           cop_ins(i_cfc1, r1, 31);
	   rri_ins(i_and, r2, r1, 0x70); /* not including underflo - my choice */
	   rrr_ins(i_xor, r1, r1, r2);
	   cop_ins(i_ctc1, r1, 31);
	   condri_ins(i_bne, r2, 0, trap);
}
/*
char *usbranches (i)
	int i;
{
  switch (i) {
    case  1:
            return i_bleu;
    case 2:
      return i_bltu;
    case 3:
      return i_bgeu;
    case 4:
      return i_bgtu;
    case 5:
      return i_bne;
    case 6:
      return i_beq;
  }
}
*/

void testsigned
(int r, long lower, long upper, long lab)
{
	condri_ins(i_blt, r, lower, lab);
	condri_ins(i_bgt, r, upper, lab);
}

void testusigned
(int r, long maxval, long lab)
{
     	condri_ins(i_bgtu, r, maxval, lab);
}

/*
char *sbranches(i)
	int i;
{
  switch (i) {
    case  1:
            return i_ble;
    case 2:
      return i_blt;
    case 3:
      return i_bge;
    case 4:
      return i_bgt;
    case 5:
      return i_bne;
    case 6:
      return i_beq;
  }
}
*/

char * branches
(shape s, int i)
{
	int n = name(s);
	if (n == scharhd || n == swordhd || n == slonghd
		|| n == offsethd) {
          switch (i) {
            case  1:
                    return i_ble;
            case 2:
              return i_blt;
            case 3:
              return i_bge;
            case 4:
              return i_bgt;
            case 5:
              return i_bne;
            case 6:
              return i_beq;
          }
        }
        else {
  		switch (i) {
		    case  1:
		            return i_bleu;
		    case 2:
		      return i_bltu;
		    case 3:
		      return i_bgeu;
		    case 4:
		      return i_bgtu;
		    case 5:
		      return i_bne;
		    case 6:
		      return i_beq;
		  }
	}
	return i_beq;
}

/*
char *
ussets(int i)
{
  switch (i) {
    case  1:
      return i_sgtu;
    case 2:
      return i_sgeu;
    case 3:
      return i_sltu;
    case 4:
      return i_sleu;
    case 5:
      return i_seq;
    case 6:
      return i_sne;
  }
}

char *
ssets(int i)
{
  switch (i) {
    case  1:
            return i_sgt;
    case 2:
      return i_sge;
    case 3:
      return i_slt;
    case 4:
      return i_sle;
    case 5:
      return i_seq;
    case 6:
      return i_sne;
  }
}
*/

char * sets
(shape s, int i)
{
	int n = name(s);
	if (n == scharhd || n == swordhd || n == slonghd
		|| n == offsethd) {
		  switch (i) {
		    case  1:
		            return i_sgt;
		    case 2:
		      return i_sge;
		    case 3:
		      return i_slt;
		    case 4:
		      return i_sle;
		    case 5:
		      return i_seq;
		    case 6:
		      return i_sne;
		  }
	}
	else {
		  switch (i) {
		    case  1:
		            return i_sgtu;
		    case 2:
		      return i_sgeu;
		    case 3:
		      return i_sltu;
		    case 4:
		      return i_sleu;
		    case 5:
		      return i_seq;
		    case 6:
		      return i_sne;
		  }
	}
	return i_seq;
}

char *fbranches
(int i)
{
  switch (i) {
    case  1:
            return i_c_le_s;
    case 2:
      return i_c_lt_s;
    case 3:
      return i_c_lt_s;
    case 4:
      return i_c_le_s;
    case 5:
      return i_c_eq_s;
    case 6:
      return i_c_eq_s;
  }
  return i_c_eq_s;
}

char *fdbranches
(int i)
{
  switch (i) {
    case  1:
            return i_c_le_d;
    case 2:
      return i_c_lt_d;
    case 3:
      return i_c_lt_d;
    case 4:
      return i_c_le_d;
    case 5:
      return i_c_eq_d;
    case 6:
      return i_c_eq_d;
  }
  return i_c_eq_d;
}

long  notbranch[6] = {
  4, 3, 2, 1, 6, 5
};
 /* used to invert TDF tests */

int   bitsin
(long b)
{		/* counts the bits in b */
  int   n = 0;
  long  mask = 1;
  for (; b != 0;) {
    n += ((b & mask)!= 0)? 1 : 0;
    b &= ~mask;
    mask = mask << 1;
  }
  return n;
}

void move_dlts
(int dr, int sr, int szr, int mr, int bytemove)
{
	/* move szr bytes to dr from sr (use mr)- either nooverlap or dr<=sr */
	baseoff b;
	int lin = new_label();

	b.offset =0;
 	set_label(lin);
 	b.base = sr;
 	ls_ins((bytemove)?i_lb:i_lw, mr, b);
 	rri_ins(i_addu, sr, sr,(bytemove)?1:4);
 	b.base = dr;
 	ls_ins((bytemove)?i_sb:i_sw, mr, b);
 	rri_ins(i_addu, dr, dr,(bytemove)?1:4);
 	rri_ins(i_subu, szr, szr,(bytemove)?1:4);
 	condrr_ins(i_bne, szr, 0, lin);
}

void move_dgts
(int dr, int sr, int szr, int mr, int bytemove)
{
	/* move szr bytes to dr from sr (use mr) with overlap and dr>sr */
	baseoff b;
	int lin = new_label();

	b.offset = (bytemove)?-1:-4;

	rrr_ins(i_addu, dr,dr, szr);
	rrr_ins(i_addu, sr,sr, szr);
 	set_label(lin);
 	b.base = sr;
 	ls_ins((bytemove)?i_lb:i_lw, mr, b);
 	rri_ins(i_subu, sr, sr,(bytemove)?1:4);
 	b.base = dr;
 	ls_ins((bytemove)?i_sb:i_sw, mr, b);
 	rri_ins(i_subu, dr, dr,(bytemove)?1:4);
 	rri_ins(i_subu, szr, szr,(bytemove)?1:4);
 	condrr_ins(i_bne, szr, 0, lin);
}

void reset_tos
(void)
{
    	if (Has_tos) {
    		baseoff b;
    		b.base = 30;
    		b.offset = -8;
    		ls_ins(i_sw, 29, b);
    	}
}

exp testlast
(exp e, exp second)
{
  /* finds the last test in sequence e which is a branch to second, if
     any, otherwise nil */
  if (name(e) == test_tag && pt(e) == second) {
    return e;
  }
  if (name(e) == seq_tag) {
    if (name(bro(son(e))) == test_tag && pt(bro(son(e))) == second) {
      return bro(son(e));
    }
    else
      if (name(bro(son(e))) == top_tag) {
	exp list = son(son(e));
	for (;;) {
	  if (last(list)) {
	    if (name(list) == test_tag && pt(list) == second) {
	      return list;
	    }
	    else {
	      return 0;
	    }
	  }
	  else {
	    list = bro(list);
	  }
	}
      }
  }
  return 0;
}



bool last_param
(exp e)
{
	if (!isparam(e)) return 0;
	e = bro(son(e));
    aa:	if (name(e) ==ident_tag && isparam(e)
		&& name(son(e))!= formal_callee_tag
		) return 0;
	if (name(e) == diagnose_tag) {
	    e = son(e); goto aa;
	}
	return 1;
}

int regfrmdest
(where * dest, space sp)
{
 	switch (dest->answhere.discrim) {
	  case inreg:
	    {
	      int r = regalt(dest->answhere);
	      if (r!=0) return r;

	    }
	  default:
	    {
	      return getreg(sp.fixed);
	    }
	}
}

space do_callers
(exp list, space sp)
{	int   disp =0;
	int   spar = 4;
	int   fpar = 6;
	bool hadfixed = 0;

	  for (;;) {		/* evaluate parameters in turn */
	    int   hd = name(sh(list));
	    instore is;
	    where w;
	    ash ap;
	    int paral;
	    int parsize;
	    exp par;
	    par = (name(list) ==caller_tag)?son(list):list;
	    ap = ashof(sh(list));
	    paral = (ap.ashalign < 32)?32:ap.ashalign;
	    parsize = ap.ashsize;
	    w.ashwhere = ap;
	    disp = rounder(disp,paral);
	    spar = 4+ (disp>>5);
	    is.b.base = 29;
	    is.b.offset = disp >> 3;
	    is.adval = 1;
	    if (disp>96) {spar =8; fpar = 8; }

	    if (is_floating(hd) && disp+parsize <= 128) {
	      freg frg;
	      ans ansfr;
	      frg.fr = fpar++;
	      frg.dble = (hd != shrealhd)? 1 : 0;
	      setfregalt(ansfr, frg);
	      w.answhere = ansfr;
	      code_here(par, sp, w);
	      /* eval parameter into floating parameter register */
	      sp = guardfreg(frg.fr, sp);
	      if (hadfixed) {
		  setregalt(w.answhere, spar);
		  move(ansfr, w, sp, 1);
		  sp = guardreg(spar, sp);
		  if (hd != shrealhd) { sp = guardreg(spar+1, sp); }
	      }
	    }
	    else
	    if (valregable(sh(list)) && disp+parsize <=128) {
		ans ansr;
		setregalt(ansr, spar);
		w.answhere = ansr;
		hadfixed = 1;
		code_here(par, sp, w);
		/* eval parameter into fixed parameter register */
		sp = guardreg(spar, sp);
	    }
	    else {
		setinsalt(w.answhere, is);
		code_here(par, sp, w);
		hadfixed = 1;
		/* eval parameter into argument space on stack */
		while (spar <= 7 && ap.ashsize >0) {
			/* copy (parts of) any struct results into parregs */
			ls_ins(i_lw, spar, is.b);
			sp =guardreg(spar++, sp);
			is.b.offset +=4;
			ap.ashsize-=32;
		}
	   }

	   if (name(list) == caller_tag) { no(list) = disp; }

	   disp+=parsize;
	   disp = rounder(disp, 32);


	   if (last(list)) return sp;
	   list = bro(list);
	  }			/* end for */

}



void load_reg
(exp e, int r, space sp)
{
	where w;
	w.ashwhere = ashof(sh(e));
	setregalt(w.answhere, r);
	code_here(e, sp, w);
}

static int diagPIClab;

typedef struct postl_ {exp pl; struct postl_ * outer; } postl_chain;
static postl_chain * old_pls;

void update_plc
(postl_chain * ch, int ma)
{
	while (ch != (postl_chain*)0) {
	  exp pl= ch->pl;
	  while (name(pl) ==ident_tag && name(son(pl)) ==caller_name_tag) {
		no(pl) += (ma<<1);
		pl = bro(son(pl));
	  }
	  ch = ch->outer;
	}
}

void do_callee_list
(exp e, space sp)
{
    	long x = ((no(e) >>3) +23) & ~7;
    	exp list = son(e);
    	instore is;
    	where w;
    	baseoff b;
    	long disp;
    	ash ap;
    	disp = 0;
    	rri_ins(i_subu, 29, 29, x);
    	b.base = 29; b.offset = x-4;
    	ls_ins(i_sw, 30, b);

	update_plc(old_pls, x<<3);

    	if (no(e)!= 0) {
    		for (;;) {
    			ap = ashof(sh(list));
    			disp = rounder(disp, ap.ashalign);
    			is.b.offset = disp>>3;
    			is.b.base = 29; is.adval = 1;
    			w.ashwhere = ap;
    			setinsalt(w.answhere, is);
    			code_here(list, sp, w);
    			disp = rounder(disp+ap.ashsize, 32);
    			if (last(list))break;
    			list = bro(list);
    		}
    	}
	update_plc(old_pls, - (x<<3));
}

exp find_ote
(exp e, int n)
{
	exp d = father(e);
	while (name(d)!=apply_general_tag)d = father(d);
	d = son(bro(son(d))); /* list otagexps */
	while (n !=0) { d = bro(d); n--;}
	Assert(name(d) ==caller_tag);
	return d;
}

makeans make_code
(exp e, space sp, where dest, int exitlab)
{
  /* produce code for expression e, putting its result in dest using
     t-regs given by sp. If non-zero, exitlab is the label of where the
     code is to continue */
  long constval;
  makeans mka;

tailrecurse:
  mka.lab = exitlab;
  mka.regmove = NOREG;



  switch (name(e)) {
    case ident_tag:
      {
	where placew;
	int   r = NOREG;
	bool remember = 0;




	if (props (e) & defer_bit) {/* the tag of this declaration is
				   transparently identified with its
				   definition, without reserving more
				   space */
	  e = bro(son(e));
	  goto tailrecurse;

	}



	if (son (e) == nilexp) {/* I think this is historical - unused
				   tags are now removed cleanly */
	  placew = nowhere;
	}
        else
	if (name(son(e)) == caller_name_tag) {
		exp ote = find_ote(e,no(son(e)));
		long disp = no(ote);
		no(e) = (disp<<1) +29;
		placew = nowhere;
	}
	else {
	  ash a;
	  int   n = no(e);
	  a = ashof(sh(son(e)));
	  if ((props(e) & inreg_bits)!= 0) {
	    /* tag in some fixed pt reg */
	    if (n == 0) {	/* if it hasn't been already allocated
				   into a s-reg (or r2) allocate tag into
				   fixed t-reg ... */
	      int   s = sp.fixed;
	      if (props (e) & notparreg)/* ... but not a parameter reg */
		s |= 0xf0;
	      n = getreg(s);
	      no(e) = n;
	    }
	    setregalt(placew.answhere, n);
	  }
	  else
	    if ((props(e) & infreg_bits)!= 0) {
	      /* tag in some float reg */
	      freg frg;
	      if (n == 0) {	/* if it hasn't been already allocated
				   into a s-reg (or r0) allocate tag into
				   float-reg ... */
		int   s = sp.flt;
		if (props(e) & notparreg)
		  s |= 0xc0;
		n = getfreg(s);
		no(e) = n;
	      }
	      else
	      if (n == 16) {	/* result reg */
		  n = 0;
		  no(e) = 0;
	      }


	      frg.fr = n;
	      frg.dble = (a.ashsize == 64)? 1 : 0;
	      setfregalt(placew.answhere, frg);
	    }
	    else
	    if (isparam(e)) {
	      if (name(son(e))!=formal_callee_tag) {
	    	long n = (no(son(e)) + frame_size +callee_size)>>3 ; /* byte disp of params */
		instore is;
		is.adval =1;
		no(e) = ((no(son(e)) +frame_size+callee_size-locals_offset) <<1) +29+Has_fp;
		if ((!Has_no_vcallers ||
			(isvis(e) && props(son(e))!= 0)) && last_param(e)) {
		        /* vararg in reg ? */
			int r = rounder(no(son(e)) +shape_size(sh(son(e))), 32);
			while (r<=96) {
				is.b.offset = (r+ ((Has_fp)?0
						:frame_size+callee_size)) >>3;
				is.b.base = 29+Has_fp;
				ls_ins(i_sw, 4+ (r>>5), is.b);
				r+=32;
		        }
		}
		if (shape_size(sh(son(e))) ==0) {
			/* vararg ... param */
			e = bro(son(e));
			goto tailrecurse;
		}
		is.b.offset = (Has_fp)?(no(son(e)) >>3):n;
		is.b.base = 29 + Has_fp;
		if (endian == ENDIAN_BIG && props(son(e))!= 0 && shape_size(sh(son(e))) <32) {
			is.b.offset += (shape_size(sh(son(e))) ==8)?3:2;
			/* short promotions */
		}
		setinsalt(placew.answhere, is);
		remember =1;
	      }
	      else {
	      	no(e) = ((no(son(e)) +frame_size - locals_offset) <<1)
	      	        + ((Has_vcallees)?local_reg:30);
		placew = nowhere;
	      }
	    }
	    else {		/* allocate on stack */
	      int   base = n & 0x3f;
	      instore is;
	      is.b.base = base;
	      is.b.offset = (n - base) >> 4;
	      is.adval = 1;
	      if (base == 29) {
		is.b.offset += locals_offset >> 3;
	      }
	      else
	      if ((base==30 && Has_fp)) {
		is.b.offset += ((locals_offset-frame_size-callee_size) >> 3);
	      }
	      else
	      if ((base == local_reg && Has_vcallees)) {
		is.b.offset += ((locals_offset -frame_size) >> 3);
	      }
	      setinsalt(placew.answhere, is);
	      remember = 1;
	    }
	  placew.ashwhere = a;
	}
        if (isparam(e)
        	&& name(son(e))!=formal_callee_tag) {
          exp se = son(e);
          exp d = e;
	   /* parameter fiddles */
           if (props(se) == 0 && (props(d) & inanyreg)!=0) {
                /* not originally in required reg */
                ans a;
                instore is;
		is.b.base = 29 + Has_fp;
		is.b.offset = (no(se) +
                              ((Has_fp)?0:(frame_size+callee_size))) >>3;
                is.adval = 0;
		if (endian == ENDIAN_BIG && shape_size(sh(son(e))) <32) {
			is.b.offset += (shape_size(sh(son(e))) ==8)?3:2;
			/* short promotions */
		}
                setinsalt(a, is);
                IGNORE move(a, placew, sp, is_signed(sh(se)));
           }
           else
           if (props(se)!=0 && (props(d) & inanyreg) ==0) {
                /* originally in reg and required in store */
                ans a;
                if (is_floating(name(sh(se)))) {
                   freg fr;
                   fr.fr = props(se);
                   fr.dble = (name(sh(se))!= shrealhd);
                   setfregalt(a, fr);
                }
                else { setregalt(a, props(se)); }
                r = move(a, placew, sp, 0);
           }
           else
           if (props(se)!=0 && props(se)!= no(d)) {
                /* in wrong register */
                int sr = no(d);
                int tr = props(se);
                if (is_floating(name(sh(se)))) {
                   if ((fltdone & (3<< (sr<<1)))!= 0) {
                        rrfp_ins((name(sh(se))!= shrealhd)? i_mov_d: i_mov_s,
                                no(d) <<1, props(se) <<1);
                   }
                   else {
                       props(se) = sr; no(d) = tr;
                       sp = guardfreg(tr, sp);
                       /* !? swopped and moved in  dump_tag !? */
                   }
                }
                else {
                   if ((fixdone & (1<<sr))!=0) {
                        mon_ins(i_move, no(d), props(se));
                   }
                   else {
                       props(se) = sr; no(d) = tr;
                       sp = guardreg(tr,sp);
                        /* !? swopped for dump_tag !? */
                   }
                }
           }
           /* maybe more about promotions */

        }
        else
        if (isparam(e) && name(son(e)) ==formal_callee_tag) {
                exp se = son(e);
          	exp d = e;
        	if ((props(d) & inanyreg)!= 0) {
        		/* callee parameter assigned to reg */
        	ans a;
                instore is;
		if (Has_vcallees) {
			is.b.base = local_reg;
			is.b.offset = (no(se)) >>3;
		}
		else {
			is.b.base = 30;
                	is.b.offset = (no(se) - callee_size) >>3;
		}
                is.adval = 0;
                setinsalt(a, is);
                IGNORE move(a, placew, sp, is_signed(sh(se)));
               }
        }
        else
	  r = code_here(son(e), sp, placew);
		/* evaluate the initialisation of tag, putting it into place
	   		allocated ... */

	if (remember && r != NOREG && pt(e)!= nilexp && no(pt(e)) ==0
	    && eq_sze(sh(son(e)), sh(pt(e)))) {
	  /* ...if it was temporarily in a register, remember it */
	  if (isvar(e)) {
	    keepcont(pt(e), r);
	  }
	  else {
	    keepreg(pt(e), r);
	  }
	}


	sp =  guard(placew, sp);
        e = bro(son(e));
        goto tailrecurse;
	/* and evaluate the body of the declaration */
      }				/* end ident */

    case clear_tag: {

	return mka;
      }





    case seq_tag:
      {
	exp t = son(son(e));
	for (;;) {
	  exp next = (last(t))?(bro(son(e))): bro(t);
	  if (name (next) == goto_tag) {/* gotos end sequences */
	    make_code(t, sp, nowhere, no(son(pt(next))));
	  }
	  else {
	    code_here(t, sp, nowhere);
	  }
	  if (last(t)) {
	    e = bro(son(e));
	    goto tailrecurse;
	  }
	  t = bro(t);
	}
      }				/* end seq */

    case cond_tag:
      {
	exp first = son(e);
	exp second = bro(son(e));
	exp test;

	if (dest.answhere.discrim == insomereg) {
	  /* must make choice of register to contain answer to cond */
	  int  *sr = someregalt(dest.answhere);
	  if (*sr != -1) {
	    failer("Somereg *2");
	  }
	  *sr = getreg(sp.fixed);
	  setregalt(dest.answhere, *sr);
	}
	else
	if (dest.answhere.discrim == insomefreg) {
	       somefreg sfr;
	       freg fr;
   	       sfr = somefregalt(dest.answhere);
	       if (*sfr.fr != -1) { failer("Somefreg *2"); }
	       *sfr.fr = getfreg(sp.flt);
	       fr.fr = *sfr.fr;
	       fr.dble = sfr.dble;
	       setfregalt(dest.answhere, fr);
	}

	if (name(first) == goto_tag && pt(first) == second) {
	  /* first is goto second */
	  no(son(second)) = 0;
	  return make_code(second, sp, dest, exitlab);
	}
	else
	    if (name(second) == labst_tag &&
		name(bro(son(second))) == top_tag) {
	      /* second is empty */
	      int   endl = (exitlab == 0)? new_label(): exitlab;
	      no(son(second)) = endl;
	      make_code(first, sp, dest, endl);
	      mka.lab = endl;
	      return mka;
	    }
	    else
	      if (name(second) == labst_tag &&
		  name(bro(son(second))) == goto_tag) {
		/* second is goto */
		exp g = bro(son(second));
		no(son(second)) = no(son(pt(g)));
		return make_code(first, sp, dest, exitlab);
	      }
	if ((test = testlast (first, second)) /* I mean it */ ) {
	  /* effectively an empty then part */
	  int   l = (exitlab != 0)? exitlab : new_label();
	  bool rev = IsRev(test);
	  ptno(test) = -l;	/* make test jump to exitlab - see
				   test_tag: */
	  props(test) = notbranch[(props(test) &127) - 1];
	   if (rev) { SetRev(test); }
	  /* ... with inverse test */
	  no(son(second)) = new_label();
	  make_code(first, sp, dest, l);
	  make_code(second, sp, dest, l);
	  mka.lab = l;
	  return mka;
	}
	else {
	  int   fl;
	  no(son(second)) = new_label();
	  fl = make_code(first, sp, dest, exitlab).lab;

	  {
	    int   l = (fl != 0)? fl :((exitlab != 0)? exitlab : new_label());
/* Alteration 4 */
	    if (name(sh(first))!= bothd || l == rscope_label)uncond_ins(i_b, l);
	    make_code(second, sp, dest, l);
	    clear_all();
	    mka.lab = l;
	    return mka;
	  }
	}
      }				/* end cond */

    case labst_tag:
      {
	if (no(son(e))!= 0) {
	   set_label(no(son(e)));
	}
	if (is_loaded_lv(e) && No_S) { /* can be target of long_jump; reset sp */
		baseoff b;
		b.base = 30;
		if (Has_vcallees) {
			b.offset = -12;
			ls_ins(i_lw, local_reg, b);
		}
		if (Has_tos) {
			b.offset = -8;
			ls_ins(i_lw, 29, b);
		}
		else {
			rri_ins(i_subu, 29, 30,(frame_size+callee_size) >>3);
		}
	}
	e = bro(son(e));
	goto tailrecurse;

      }				/* end labst */

    case rep_tag:
      {
	exp first = son(e);
	exp second = bro(first);
/* Alteration 1: adds this line :- */
	code_here(first, sp, nowhere);
	no(son(second)) = new_label();
	e = second;
	goto tailrecurse;

      }				/* end rep */

    case goto_tag:
      {
	exp gotodest = pt(e);
	int   lab = no(son(gotodest));
	clear_all();
	if (!last(e) || name(bro(e))!=seq_tag || !last(bro(e)) ||
	      last(bro(bro(e))) || bro(bro(bro(e)))!= gotodest) {
	  uncond_ins(i_b, lab);
	} /* dest is next in sequence */

	return mka;
      }				/* end goto */

    case make_lv_tag: {
    	int r = regfrmdest(&dest,sp);
    	ans aa;
    	condr_ins(i_la, r, no(son(pt(e))) ); /*???? */
    	setregalt(aa,r);
    	move(aa,dest, guardreg(r,sp), 0);
    	mka.regmove = r;
    	return mka;
    }

    case long_jump_tag: {
    	int fp = reg_operand(son(e), sp);
    	int labval = reg_operand(bro(son(e)), sp);
    	mon_ins(i_move, 30, fp);
    	br_ins(i_j, labval);
    	return mka;
    }

    case max_tag: case min_tag: case offset_max_tag:
      {
	exp l = son(e);
	exp r = bro(l);
	shape shl = sh(l);
	int a1, a2, d;
	ans aa;
	space nsp;
	char * setins = sets(shl,3);
	int lab = new_label();

	a1 = reg_operand(l, nsp);
	nsp = guardreg(a1, sp);
	d = regfrmdest(&dest, nsp);
	if (d==a1)d = getreg(nsp.fixed);
	nsp = guardreg(d, nsp);
	if (name(r) == val_tag) {
		 rri_ins(setins, d, a1, no(r));
	}
	else {
	  	a2 = reg_operand(r, nsp);
		if (d==a2)d = getreg(guardreg(a2,nsp).fixed);
		rrr_ins(setins, d, a1, a2);
	}

	setnoreorder();
	condri_ins((name(e)!=min_tag)?i_beq:i_bne, d, 0, lab);
	rrr_ins(i_addu, d, a1, 0);
	if (name(r) ==val_tag) {
		baseoff b;
		b.base = 0;
		b.offset = no(r);
		ls_ins(i_li, d, b);
	}
	else rrr_ins(i_addu,d,a2, 0);
	set_label_no_clear(lab);
	setreorder();

	setregalt(aa, d);
        move(aa, dest, guardreg(d, sp), 0);
        mka.regmove = d;
        return mka;


      }


    case absbool_tag: case maxlike_tag: case minlike_tag: case abslike_tag:
      {
	exp l = son(son(e));
	exp r = bro(l);
	shape shl = sh(l);
	char *setins;
	int   n = props(son(e));
	int   d;
	int   a1;
	int   a2;
	bool xlike = (name(e)!= absbool_tag);
	ans aa;

	if (!xlike && name (l) == val_tag) {/* put literal operand on right */
	  exp temp = l;
	  l = r;
	  r = temp;
	  if (n <= 2) {
	    n += 2;
	  }
	  else
	    if (n <= 4) {
	      n -= 2;
	    }
	}

	setins = sets(shl, n);
	/* chose set instruction from test and shape */

	d = regfrmdest(&dest, sp);

	/* reg d will contain result of set (eventually) */

	a1 = reg_operand(l, sp);
	if (xlike && a1==d) {
		sp = guardreg(a1, sp);
		d = getreg(sp.fixed);
	}
	if (name(r) == val_tag) {
	  rri_ins(setins, d, a1, no(r));
	}
	else {
	  space nsp;
	  nsp = guardreg(a1, sp);
	  a2 = reg_operand(r, nsp);
	  if (xlike && a2==d) {
	  	nsp = guardreg(a2, nsp);
	  	d = getreg(nsp.fixed);
	  }
	  rrr_ins(setins, d, a1, a2);
	}
	if (name(e) ==maxlike_tag || name(e) ==minlike_tag) {
		int l = new_label();
		setnoreorder();
		condri_ins((name(e) ==maxlike_tag)?i_bne:i_beq, d, 0, l);
		rrr_ins(i_addu, d, a1, 0);
		if (name(r) ==val_tag) {
			baseoff b;
			b.base = 0;
			b.offset = no(r);
			ls_ins(i_li, d, b);
		}
		else rrr_ins(i_addu,d,a2, 0);
		set_label_no_clear(l);
		setreorder();
	}
	else
	if (name(e) ==abslike_tag) {
		int l = new_label();
		setnoreorder();
		condri_ins(i_bne, d, 0, l);
		rrr_ins(i_addu, d, a1, 0);
		rrr_ins(i_subu, d, 0, a1);
		set_label_no_clear(l);
		setreorder();
	}



        setregalt(aa, d);
        move(aa, dest, guardreg(d, sp), 0);
        mka.regmove = d;
        return mka;


      }				/* end absbool */


    case test_tag:
      {
	exp l = son(e);
	exp r = bro(l);
	int   lab = (ptno(e) < 0)? -ptno(e): no(son(pt(e)));
	/* see frig in cond_tag */
	shape shl = sh(l);
	char *branch;
	int   n = (props (e)) & 127; /* could have Rev bit in props*/

	if (is_floating(name(sh(l)))) {
	  bool dble = (name(shl)!= shrealhd)? 1 : 0;
	  int   a1;
	  char *branch = (n <= 2 || n == 6)? i_bc1t : i_bc1f;
	  char *compare = (dble)? fdbranches(n): fbranches(n);
	  /* choose branch and compare instructions */
	  int   a2;
	  space nsp;
	  if (IsRev(e)) {
		a2 = freg_operand(r, sp);
		nsp = guardfreg(a2, sp);
		a1 = freg_operand(l, nsp);
	  }
	  else {
		a1 = freg_operand(l, sp);
		nsp = guardfreg(a1, sp);
		a2 = freg_operand(r, nsp);
	  }

	  rrfpcond_ins(compare, a1 << 1, a2 << 1);
	  br_ins(branch, lab);
	  return mka;
	}			/* end float test */
	else {
	  int   a1;
	  int   a2;
	  if (name (l) == val_tag) {/* put literal operand on right */
	    exp temp = l;
	    l = r;
	    r = temp;
	    if (n <= 2) {
	      n += 2;
	    }
	    else
	      if (n <= 4) {
		n -= 2;
	      }
	  }
	  branch = branches(shl, n);
	  	/* choose branch instruction */
	  a1 = reg_operand(l, sp);
	  if (name(r) == val_tag) {
	    condri_ins(branch, a1, no(r), lab);
	  }
	  else {
	    space nsp;
	    nsp = guardreg(a1, sp);
	    a2 = reg_operand(r, nsp);
	    condrr_ins(branch, a1, a2, lab);
	  }

	  return mka;
	}			/* end int test */
      }				/* end test */


    case ass_tag:
    case assvol_tag:
      {
	exp lhs = son(e);
	exp rhs = bro(lhs);
	where assdest;
	space nsp;
	ash arhs;

	int   contreg = NOREG;
	if (name(e) == assvol_tag) {
	  clear_all();
	  setvolatile();
	}

	arhs = ashof(sh(rhs));


	if (name(e) == ass_tag && name(rhs) == apply_tag &&
	   (is_floating(name(sh(rhs))) || valregable(sh(rhs)))) {
	  /* if source is simple proc call, evaluate it first and do
	     assignment */
	  ans aa;
	  code_here(rhs, sp, nowhere);
	  if (is_floating(name(sh(rhs)))) {
	    freg frg;
	    frg.fr = 0;
	    frg.dble = (arhs.ashsize == 64)? 1 : 0;
	    setfregalt(aa, frg);
	  }
	  else {
	    setregalt(aa, 2);
	    sp = guardreg(2,sp);
	  }
	  assdest = locate(lhs, sp, sh(rhs), 0);
	  move(aa, assdest, sp, 1);
	  clear_dep_reg(lhs);
	  return mka;
	}


	assdest = locate(lhs, sp, sh(rhs), 0);
	nsp = guard(assdest, sp);
	/* evaluate 'address' of destination */

	if (name(e) == ass_tag
	      && assdest.answhere.discrim == notinreg) {
	    instore is;
	    is = insalt(assdest.answhere);
	    if (!is.adval) {	/* this is an indirect assignment, so make
				   it direct by loading pointer into reg
				   (and remember it) */
	      int   r = getreg(sp.fixed);
	      ls_ins(i_lw, r, is.b);
	      nsp = guardreg(r, sp);
	      is.adval = 1;
	      is.b.base = r;
	      is.b.offset = 0;
	      setinsalt(assdest.answhere, is);
	      keepexp(lhs, assdest.answhere);
	    }
	  }


	contreg = code_here(rhs, nsp, assdest);
	/* evaluate source into assignment destination .... */



	switch (assdest.answhere.discrim) {
	  case inreg:
	    {
	      int   a = regalt(assdest.answhere);
	      keepreg(rhs, a);
	      /* remember that source has been evaluated into a */
	      clear_dep_reg(lhs);
	      /* forget register dependencies on destination */
	      break;
	    }
	  case infreg:
	    {
	      freg frg;
	      int   r;
	      frg = fregalt(assdest.answhere);
	      r = frg.fr + 32;
	      if (frg.dble) {
		r = -r;
	      };
	      keepreg(rhs, r);
	      /* remember that source has been evaluated into a */
	      clear_dep_reg(lhs);
	      /* forget register dependencies on destination */
	      break;
	    }

	  case notinreg:
	    {
	      if (contreg != NOREG && name(e) == ass_tag) {
		clear_dep_reg(lhs);
		/* forget register dependencies on destination */

		if (name(lhs) == name_tag) {
			exp dc = son(lhs);
			exp u = pt(dc);
			while (u != nilexp) {
				/* loook through uses to find cont(name) */
			   if (last(u) && no(u) ==no(lhs) && bro(u)!=nilexp &&
				name(bro(u)) ==cont_tag &&
				shape_size(sh(bro(u))) == shape_size(sh(rhs))) {
				keepreg(bro(u), contreg);
				break;
			   }
			   u = pt(u);
			}
			/* remember cont of name as in contreg */

		}
		else
		if (!dependson(lhs, 0, lhs)) {
		  /* remember that dest contains source, provided that it
		     is not dependent on it */
		  keepcont(lhs, contreg);
		}
		return mka;
	      }
	      clear_dep_reg(lhs);
	      /* forget register dependencies on destination */
	      break;
	    }
	  case insomereg: case insomefreg:
	      {
		clear_dep_reg(lhs);
		/* forget register dependencies on destination */

	      }
	}			/* end sw on answhere */

	if (name(e) == assvol_tag)
	  setnovolatile();
	return mka;
      }				/* end ass */

    case compound_tag:
      {
	exp t = son(e);
	space nsp;
	instore str;
	int r;

	nsp = sp;
	switch (dest.answhere.discrim) {
	   case notinreg: {
            str = insalt (dest.answhere);/* it should be !! */
            if (!str.adval) {
              int   r = getreg(sp.fixed);
              nsp = guardreg(r, sp);
              ls_ins(i_lw, r, str.b);
              str.adval = 1;
              str.b.base = r;
              str.b.offset = 0;
            }
            for (;;) {
              where newdest;
              instore newis;
              newis = str;
              newis.b.offset += no(t);

              Assert(name(t) ==val_tag && al2(sh(t)) >= 8);


              setinsalt(newdest.answhere, newis);
              newdest.ashwhere = ashof(sh(bro(t)));
              code_here(bro(t), nsp, newdest);
              if (last(bro(t))) {
                return mka;
              }
              t = bro(bro(t));
            }
          }
          case insomereg: {
            int * sr = someregalt(dest.answhere);
            if (*sr != -1) {
              failer("Somereg *2");
            }
            *sr = getreg(sp.fixed);
            setregalt(dest.answhere, *sr);
 	    /* ,... */
          }
          case inreg: {
            code_here(bro(t), sp, dest);
            r = regalt(dest.answhere);
            Assert(name(t) ==val_tag);
            if (no(t)!=0) {
            	rri_ins(i_sll, r, r,(al2(sh(t)) >= 8)?(no(t) <<3):no(t));
            }
            nsp = guardreg(r, sp);
            while (!last(bro(t))) {
            	int z;
            	t = bro(bro(t));
            	Assert(name(t) ==val_tag);
            	z = reg_operand(bro(t), nsp);
            	if (no(t)!=0) {
            		rri_ins(i_sll, z,z,(al2(sh(t)) >= 8)?(no(t) <<3):no(t));
                }
                rrr_ins(i_or, r, r, z);
            }
            return mka;
          }
          case insomefreg: {
	       somefreg sfr;
	       freg fr;
   	       sfr = somefregalt(dest.answhere);
	       if (*sfr.fr != -1) { failer("Somefreg *2"); }
	       *sfr.fr = getfreg(sp.flt);
	       fr.fr = *sfr.fr;
	       fr.dble = sfr.dble;
	       setfregalt(dest.answhere, fr);
          }
	  case infreg:{
	    code_here(bro(t), sp, dest);
	    if (!last(bro(t)) || name(t)!=val_tag || no(t)!=0) {
	       failer("No Tuples in freg");
	    }
	    return mka;
	  }
        }

      }				/* end tup */

    case nof_tag: case concatnof_tag:
   {
	exp t = son(e);
	space nsp;
	instore str;
	int r, disp = 0;

	if (t == nilexp) return mka;

	nsp = sp;
	switch (dest.answhere.discrim) {
	   case notinreg: {
            str = insalt (dest.answhere);/* it should be !! */
            if (!str.adval) {
              int   r = getreg(sp.fixed);
              nsp = guardreg(r, sp);
              ls_ins(i_lw, r, str.b);
              str.adval = 1;
              str.b.base = r;
              str.b.offset = 0;
            }
            for (;;) {
              where newdest;
              instore newis;
              newis = str;
              newis.b.offset += disp;
              setinsalt(newdest.answhere, newis);
              newdest.ashwhere = ashof(sh(t));
              code_here(t, nsp, newdest);
              if (last(t)) {
                return mka;
              }
              disp+= (rounder(shape_size(sh(t)), shape_align(sh(bro(t)))) >>3);
              t =bro(t);
            }
          }
          case insomereg: {
            int * sr = someregalt(dest.answhere);
            if (*sr != -1) {
              failer("Somereg *2");
            }
            *sr = getreg(sp.fixed);
            setregalt(dest.answhere, *sr);
 	    /* ,... */
          }
          case inreg: {
            code_here(t, sp, dest);
            r = regalt(dest.answhere);
            nsp = guardreg(r, sp);
            while (!last(t)) {
            	int z;
            	disp+=rounder(shape_size(sh(t)), shape_align(sh(bro(t))));
            	t =bro(t);
            	z = reg_operand(t, nsp);
            	rri_ins(i_sll, z,z, disp);
                rrr_ins(i_or, r, r, z);
            }
            return mka;
          }
	  default: failer("No Tuples in freg");
        }

      }

      case ncopies_tag:
   {
	exp t = son(e);
	space nsp;
	instore str;
	int i, r, disp = 0;

	nsp = sp;
	switch (dest.answhere.discrim) {
	   case notinreg: {
            str = insalt (dest.answhere);/* it should be !! */
            if (!str.adval) {
              int   r = getreg(sp.fixed);
              nsp = guardreg(r, sp);
              ls_ins(i_lw, r, str.b);
              str.adval = 1;
              str.b.base = r;
              str.b.offset = 0;
            }
            for (i=1;i<=no(e); i++) {
              where newdest;
              instore newis;
              newis = str;
              newis.b.offset += disp;
              setinsalt(newdest.answhere, newis);
              newdest.ashwhere = ashof(sh(t));
              code_here(t, nsp, newdest);
              disp+= (rounder(shape_size(sh(t)), shape_align(sh(t))) >>3);
            }
            return mka;
          }
          case insomereg: {
            int * sr = someregalt(dest.answhere);
            if (*sr != -1) {
              failer("Somereg *2");
            }
            *sr = getreg(sp.fixed);
            setregalt(dest.answhere, *sr);
 	    /* ,... */
          }
          case inreg: {
            code_here(t, sp, dest);
            r = regalt(dest.answhere);
            nsp = guardreg(r, sp);
            for (i=1; i<=no(e); i++) {
            	int z;
            	disp+=rounder(shape_size(sh(t)), shape_align(sh(t)));
            	z = reg_operand(t, nsp);
            	rri_ins(i_sll, z,z, disp);
                rrr_ins(i_or, r, r, z);
            }
            return mka;
          }
	  default: failer("No Tuples in freg");
        }

      }

    case caller_tag: {
    	e = son(e); goto tailrecurse;
    }



    case apply_general_tag:
    	{
    	  exp fn = son(e);
    	  exp cers = bro(fn);
    	  exp cees = bro(cers);
    	  exp pl = bro(cees);
    	  space nsp;

    	  if (no(cers)!=0) { nsp = do_callers(son(cers),sp); }
	  else { nsp = sp; }

    	  IGNORE make_code(cees, nsp, nowhere, 0);

    	  if (name(fn) == name_tag && name(son(fn)) == ident_tag
	    && (son(son(fn)) == nilexp ||
	        name(son(son(fn))) == proc_tag ||
	     name(son(son(fn))) == general_proc_tag)) {
	  /* the procedure can be entered directly */
	  	extj_ins(i_jal, boff(son(fn)));
	  }
	  else
	  if (PIC_code) {
		/* have to get address of proc into r25 */
		where w;
		setregalt(w.answhere, 25);
		w.ashwhere = ashof(sh(fn));
		code_here(fn,sp,w);
		br_ins(i_jal, 25);
          }
    	  else {			/* the address of the proc is evaluated
				   and entered indirectly */
	  clear_reg(31); /* can't use 31 as temp reg for jal */
	  br_ins(i_jal, reg_operand(fn, guardreg(31,sp)));
	}
	if (PIC_code)reset_gp();
	clear_all ();		/* forget all register memories */
        { int hda = name(sh(e));
	  ans aa;
	  if (is_floating(hda)) {
	    freg frg;
	    frg.fr = 0;
	    frg.dble = (hda != shrealhd);
	    setfregalt(aa, frg);
	    move(aa, dest, sp, 1);
	    /* move floating point result of application to destination */
	  }
	  else {
	    setregalt(aa, 2);
	    mka.regmove = 2;
	    move(aa, dest, sp, 1);
	    /* move floating point result of application to destination */
	  }
	  /* else struct results are moved by body of proc */
	}

	if (call_is_untidy(cees)) {
		rri_ins(i_subu, 29, 29, max_args>>3);
		reset_tos();
		Assert(name(pl) ==top_tag);
	}
	else
	if (postlude_has_call(e)) {
		exp x = son(cers);
		postl_chain p;
		for (;x != nilexp ;) {
			if (name(x) ==caller_tag) {
				no(x) += max_args;
			}
			if (last(x))break;
			x = bro(x);
		}
		mka.regmove = NOREG;
		update_plc(old_pls, max_args);
		p.pl = pl;
		p.outer = old_pls;
		old_pls = &p;
		rri_ins(i_subu, 29, 29, max_args>>3);
 		IGNORE make_code(pl, sp, nowhere, 0);
		rri_ins(i_addu, 29, 29, max_args>>3);
		old_pls = p.outer;
		update_plc(old_pls, -max_args);
	}
	else
		IGNORE make_code(pl, sp, nowhere, 0);

	return mka;
    }

    case caller_name_tag: {
    	return mka;
    }

    case make_callee_list_tag: {

    	long x = ((no(e) >>3) +23) & ~7;
	do_callee_list(e, sp);
    	if (call_has_vcallees(e)) { rri_ins(i_addu, 30, 29, x);}
    	return mka;
/*
	| 1st callee par	|	= sf on entry
	| 2nd    "" 		|
		.....
  -16	| callers loc reg 23	| Has_vcallees	}
  -12	| callees loc reg 23	| Has_vcallees	}  4 overhd wds
  -8	| callees tos		| Has_tos	}
  -4	| caller's fp = $30	|		}
	 -----------------------
	| caller pars		|   	= top of callers env
	|			|		also $30 if var callees

*/
    }
    case same_callees_tag: {
        baseoff b;
        bool vc = call_has_vcallees(e);
        space nsp;
	exp bdy = son(crt_proc);

	while (name(bdy) ==dump_tag || name(bdy) ==diagnose_tag)bdy = son(bdy);
	while (name(bdy) ==ident_tag && isparam(bdy)) {
		/* make sure that current callees are in right place */
	   exp sbdy = son(bdy);
	   if (name(sbdy) ==formal_callee_tag && (props(bdy) &inanyreg)!=0
			&& isvar(bdy)) {
		baseoff b;
		if (Has_fp) {
			b.base = 30;
			b.offset = (no(sbdy) -callee_size) >>3;
		}
		else {
			b.base = 29;
			b.offset = (no(sbdy) +frame_size) >>3;
		}
		if (is_floating(name(sh(sbdy)))) {
			lsfp_ins((name(sh(sbdy))!=shrealhd)?i_s_d:i_s_s,
					  no(bdy) <<1, b);
		}
		else ls_ins(i_sw, no(bdy), b);
	    }
	    bdy = bro(sbdy);
	}

    	if (Has_vcallees) {
    		/*  move [fp+16..local_reg] -> top of stack */


    		int rsize = getreg(sp.fixed);
    		int rsrce; int rdest;
    		int t30;
    		int le = new_label(); int lb = new_label();
    		nsp = guardreg(rsize, sp);
    		t30 = getreg(nsp.fixed); nsp = guardreg(t30, nsp);
    		rsrce = getreg(nsp.fixed); nsp = guardreg(rsrce, nsp);
    		rdest = getreg(nsp.fixed); nsp = guardreg(rdest, nsp);

    		mon_ins(i_move, t30, 29);
    		rrr_ins(i_subu, rsize, 30, local_reg);
    		rrr_ins(i_subu, 29,29, rsize);
    		b.base = t30; b.offset = -4;
    		ls_ins(i_sw, 30, b);
    		rri_ins(i_subu, rsrce, 30, 16);
    		rri_ins(i_subu, rdest, t30, 16);
    		condrr_ins(i_beq, rdest, 29, le);
    		set_label(lb);
    		b.base = rsrce; b.offset = -4;
    		ls_ins(i_lw, rsize, b);
    		b.base = rdest;
    		ls_ins(i_sw, rsize, b);
    		rri_ins(i_subu, rsrce, rsrce, 4);
    		rri_ins(i_subu, rdest, rdest, 4);
    		condrr_ins(i_bne, rdest, 29, lb);
    		set_label(le);
    		if (vc) { mon_ins(i_move, 30, t30); }
    	}
    	else {
    		int cs = (callee_size>>3);
    		int i;
    		int tr = getreg(sp.fixed);
    		rri_ins(i_subu, 29,29, cs);
    		b.base = 29; b.offset = cs-4;
    		ls_ins(i_sw, 30, b);
    		for (i = cs-16; i>0; i-=4) {
    		        b.base = 30; b.offset = i-cs-4;
    			ls_ins(i_lw, tr, b);
    			b.base = 29; b.offset = i-4;
    			ls_ins(i_sw, tr, b);
    		}
    		if (vc) { rri_ins(i_addu, 30, 29, cs); }
    	}
    	return mka;
    }



    case make_dynamic_callee_tag: {
    	bool vc = call_has_vcallees(e);
    	int rptr;
    	int rsize;
    	int rdest;
    	int tempreg;
    	space nsp;
    	baseoff b;
    	int ls,le;
	rptr = getreg(sp.fixed);
	load_reg(son(e), rptr, sp);
	nsp = guardreg(rptr, sp);
	rsize = getreg(nsp.fixed);
	load_reg(bro(son(e)), rsize, sp);
	nsp = guardreg(rsize,nsp);
	rdest = getreg(nsp.fixed);
	nsp = guardreg(rdest,nsp);
	tempreg = getreg(nsp.fixed);
	rri_ins(i_addu, rdest, rsize, 7+16);
	rri_ins(i_and, rdest,rdest, ~7);
	b.base= 29; b.offset = -4;
	ls_ins(i_sw, 30, b);
	if (vc)mon_ins(i_move, 30, 29);
	rrr_ins(i_subu, 29, 29, rdest);
	rri_ins(i_addu, rdest, 29, 0);
	ls = new_label();
	le = new_label();
	condrr_ins(i_ble, rsize, 0, le);
	b.offset = 0;
	set_label(ls);
	b.base = rptr;
	ls_ins(i_lw, tempreg, b);
	b.base = rdest;
	ls_ins(i_sw, tempreg, b);
	rri_ins(i_addu, rdest, rdest, 4);
	rri_ins(i_addu, rptr, rptr, 4);
	rri_ins(i_subu, rsize, rsize, 4);
	condrr_ins(i_bgt, rsize, 0, ls);
	set_label(le);

        return mka;
    }

    case tail_call_tag: {
    	exp fn = son(e);
    	exp cees = bro(fn);
    	bool glob = (name(fn) == name_tag && name(son(fn)) == ident_tag
	    		&& (son(son(fn)) == nilexp ||
	        		name(son(son(fn))) == proc_tag ||
	     			name(son(son(fn))) ==
	     			general_proc_tag));
	exp bdy = son(crt_proc);
	int rptr; int rsz;
	space nsp;
	space xsp;
	int temp_fn_reg;

	nsp=sp;
	xsp=sp;
    	if (name(cees) ==make_callee_list_tag) {
    		do_callee_list(cees, sp);
    	}

	xsp.fixed = 0x800000f0;
	nsp.fixed |= 0x800000f0; /* don't use parregs or linkreg */
    	if (name(cees) ==make_dynamic_callee_tag) {
    		rptr = getreg(nsp.fixed);
    		load_reg(son(cees),rptr,nsp);
    		nsp = guardreg(rptr, nsp);
		xsp = guardreg(rptr, xsp);
    		rsz = getreg(nsp.fixed);
    		load_reg(bro(son(cees)),rsz,nsp);
    		nsp = guardreg(rsz, nsp);
		xsp = guardreg(rsz,nsp);
    	}
    	if (PIC_code) {
		temp_fn_reg = 25;
		load_reg(fn,temp_fn_reg,nsp);
	}
	else
    	if (!glob) {
    		temp_fn_reg = getreg(nsp.fixed);
    		load_reg(fn,temp_fn_reg,nsp);
		nsp = guardreg(temp_fn_reg,nsp);
		xsp = guardreg(temp_fn_reg,xsp);
    	}


	while (name(bdy) ==dump_tag || name(bdy) ==diagnose_tag)bdy = son(bdy);

	while (name(bdy) ==ident_tag && isparam(bdy)) {
		/* make sure that current callers and callees are in right place */
		exp sbdy = son(bdy);
		baseoff b;
		if (Has_fp) {
			b.base = 30;
			b.offset = no(sbdy) >>3;
		}
		else {
			b.base = 29;
			b.offset = (no(sbdy) +frame_size+callee_size) >>3;
		}
		if (name(sbdy) ==formal_callee_tag
			&& name(cees) == same_callees_tag) {
		   if ((props(bdy) &inanyreg)!=0) {
			b.offset -= (callee_size>>3);
			if (isvar(bdy)) {
			  if (is_floating(name(sh(sbdy)))) {
				lsfp_ins((name(sh(sbdy))!=shrealhd)?i_s_d:i_s_s,
					  no(bdy) <<1, b);
			  }
			  else ls_ins(i_sw, no(bdy), b);
			}
		   }
		}
		else
		if (props(sbdy) == 0 && (props(bdy) &inanyreg)!=0) {
			/* should be instore; is in reg */
			if (isvar(bdy)) {
			  if (is_floating(name(sh(sbdy)))) {
				lsfp_ins((name(sh(sbdy))!=shrealhd)?i_s_d:i_s_s,
					  no(bdy) <<1, b);
			  }
			  else ls_ins(i_sw, no(bdy), b);
			}
		}
		else
		if (props(sbdy)!=0 && (props(bdy) & inanyreg) ==0) {
		        /* should be in reg; is in store */
	               if (!Has_no_vcallers && isvis(bdy) && last_param(bdy)) {
				int i = no(sbdy) >>5;
				for (; i<4; i++) {
					ls_ins(i_lw, i+4, b);
					b.offset +=4;
				}
			}
			else
			if (is_floating(name(sh(sbdy)))) {
				lsfp_ins((name(sh(sbdy))!=shrealhd)?i_l_d:i_l_s,
					  props(sbdy) <<1, b);
			}
			else ls_ins(i_lw, props(sbdy), b);

		}
		else
		if (props(sbdy)!=0 && props(sbdy)!= no(bdy)) {
                	/* in wrong register */
                	if (is_floating(name(sh(sbdy)))) {
                		rrfp_ins((name(sh(sbdy))!=shrealhd)?i_mov_d:i_mov_s,
                		          props(sbdy) <<1, no(bdy) <<1);
                        }
                        else mon_ins(i_move, props(sbdy), no(bdy));
               }


               bdy = bro(sbdy);
        }

        restore_sregs(fixdone, fltdone);


       if (name(cees) ==make_callee_list_tag) {
       		/* copy from top of stack */
       		int x = ((no(cees) >>3) +23) & ~7;
       		int r = getreg(xsp.fixed);
		int r1 = getreg(guardreg(r,xsp).fixed);
       		int i;
       		baseoff b;
		int ncees = no(cees) >>3;
		int rnc = (ncees+7) &~7;
       		for (i= ncees; i > 0; i-=4) {
		   int x = r;
       		   b.base = 29; b.offset = i-4;
       		   ls_ins(i_lw, r, b);
       		   b.base = 30; b.offset = i-rnc-20;
       		   ls_ins(i_sw, r, b);
       		   r = r1; r1 = x;
       		}
    		/*

    		sp + 0: p1 ->   fp - 20: p1
    		sp + 4: p2      fp - 24: p2
    		sp + 8: p3      fp - 28: p3
    			....
    		*/

    		rri_ins(i_subu, 29, 30, x);

	}
	else
	if (name(cees) ==make_dynamic_callee_tag) {
		/* rdest = fp-16;
		   rsize = (rsize+23)&~7
		   rsource = rptr + rsize
		   while rsize>0
		      [rdest-4] = [rsource-4];
		      rdest-=4; rsource-=4; rsize-=4;
		   sp = rdest;
		*/
		int rdest; int rsize = rsz;
		int rsource = rptr; int tempr;
		int le, ls;
		baseoff b;
		rdest = getreg(xsp.fixed);
		nsp = guardreg(rdest, nsp);
		tempr = getreg(xsp.fixed);
		rri_ins(i_subu, rdest, 30, 16);
		rri_ins(i_addu, rsize, rsize, 7);
		rri_ins(i_and, rsize, rsize, ~7);
		rrr_ins(i_addu, rsource, rsource, rsize);
		le = new_label(); ls = new_label();
		condrr_ins(i_ble, rsize, 0, le);
		set_label(ls);
		b.base = rsource; b.offset = -4;
		ls_ins(i_lw, tempr, b);
		b.base = rdest;
		ls_ins(i_sw, tempr, b);
		rri_ins(i_subu, rdest, rdest, 4);
		rri_ins(i_subu, rsource, rsource, 4);
		rri_ins(i_subu, rsize, rsize, 4);
		condrr_ins(i_bgt, rsize, 0, ls);
		set_label(le);
		mon_ins(i_move, 29, rdest);


	}
	else {
		if (Has_vcallees) {
			mon_ins(i_move, 29, local_reg);
		}
		else
		if (Has_fp) {
			 rri_ins(i_subu, 29, 30, callee_size>>3);
		}
		else { /* this should only occur in initialisation procs */
			rri_ins(i_addu, 29, 29,(frame_size+callee_size) >>3);
		}

	}

        if (Has_vcallees) {
	  	baseoff b;
	  	b.base = 30;
	  	b.offset = -16;
	  	ls_ins(i_lw, local_reg, b); /* old l-reg in -16(30) */
	}
    	if (glob && !PIC_code) {
    		extj_ins(i_j, boff(son(fn)));
    	}
    	else {
    		br_ins(i_j, temp_fn_reg);

    	}
    	clear_all();
    	return mka;



    }

    case apply_tag:
      {
	exp fn = son(e);
	exp par = bro(fn);
	exp list = par;
	exp dad = father(e);
	bool tlrecurse = rscope_level == 0 && (name(dad) == res_tag) && props(dad);
	int   hda = name(sh(e));
	int disp;

	ash ansash;



	if ((disp = specialfn (fn)) > 0) {/* eg function is strlen */
	  mka.lab = specialmake(disp, list, sp, dest, exitlab);
	  return mka;
	}

	ansash = ashof(sh(e));

	if (!last(fn)) {
		sp = do_callers(list, sp);
	}


	if (name(fn) == name_tag && name(son(fn)) == ident_tag
	    && (son(son(fn)) == nilexp || name(son(son(fn))) == proc_tag)) {
	  /* the procedure can be entered directly */
	  if (! tlrecurse) {
	  	extj_ins(i_jal, boff(son(fn)));
		if (PIC_code)reset_gp();
	  }
	  else {
	  	if (Has_fp) {
	  		baseoff b;
	  		b.base = 30;
	  		b.offset = -4;
	  		restore_sregs(fixdone, fltdone);
	  		mon_ins(i_move, 29, 30);
	  		ls_ins(i_lw, 30, b);
	  	}
	  	else {
	  		restore_sregs(fixdone, fltdone);
	  		rri_ins(i_addu, 29, 29,(frame_size+callee_size) >>3);
	  	}
	  	extj_ins(i_j, boff(son(fn)));
	  	if (as_file)fprintf(as_file," # Tail recursion\n");
	  }

	}
	else
	if (PIC_code) {
		/* have to get address of proc into r25 */
		where w;
		setregalt(w.answhere, 25);
		w.ashwhere = ashof(sh(fn));
		code_here(fn,sp,w);
		br_ins(i_jal, 25);
		reset_gp();
        }
	else {			/* the address of the proc is evaluated
				   and entered indirectly */
	  clear_reg(31); /* can't use 31 as temp reg for jal */
	  br_ins(i_jal, reg_operand(fn, guardreg(31,sp)));
	}
	clear_all ();		/* forget all register memories */
        {
	  ans aa;
	  if (is_floating(hda)) {
	    freg frg;
	    frg.fr = 0;
	    frg.dble = (hda != shrealhd);
	    setfregalt(aa, frg);
	    move(aa, dest, sp, 1);
	    /* move floating point result of application to destination */
	  }
	  else {
	    setregalt(aa, 2);
	    mka.regmove = 2;
	    move(aa, dest, guardreg(2,sp), 1);
	    /* move fixed point result of application to destination */
	  }
	  /* else struct results are moved by body of proc */
	}
	return mka;
      }				/* end apply */

    case return_to_label_tag: {
	int r = getreg(sp.fixed);
	where w;
	setregalt(w.answhere, r);
	w.ashwhere = ashof(sh(son(e)));
	code_here(son(e), sp, w);
	clear_all();
	if (Has_fp) {
		baseoff b;
		b.base = 30;
		restore_sregs(fixdone, fltdone);
		if (Has_vcallees) {
			b.offset = -16;
			ls_ins(i_lw, local_reg, b);
		}
		b.offset = -4;
		mon_ins(i_move, 29, 30);
		ls_ins(i_lw, 30, b);
	}
	else
	if (frame_size !=0) {
		restore_sregs(fixdone, fltdone);
		/* restore dumped value of s-regs on entry */
		rri_ins(i_addu, 29, 29, frame_size >> 3);
		/* reset stack ptr */
	}
	uncond_ins(i_j, r);
	return mka;
    }



    case res_tag: case untidy_return_tag:
      {
	where w;
	w.answhere = procans;
	w.ashwhere = ashof(sh(son(e)));
	code_here(son(e), sp, w);
	/* evaluate result value */

	clear_all ();		/* clear all register memories */

	if (rscope_level == 0) {/* normal proc body */
	  if (name(son(e)) == apply_tag && props(e)) return mka;
	  				/* was a tail recursion */
	  if (frame_size == 0
		  && !Has_fp) {
	    uncond_ins(i_j, 31);
	  }
	  else
	  if (result_label != 0 && name(e) ==res_tag) {
	  	uncond_ins(i_b, result_label);
	  	if (as_file)fprintf(as_file, " # Return\n");
	  }
	  else{
	      	if ((fixdone|fltdone) ==0) {
	  		result_label = new_label();
	  		set_label(result_label);
	     	}
	  	if (Has_fp) {
	  		baseoff b;
	  		b.base = 30;
	  		restore_sregs(fixdone, fltdone);
	  		if (Has_vcallees) {
	  			b.offset = -16;
	  			ls_ins(i_lw, local_reg, b);
	  		}
			b.offset = -4;
	  		if (name(e) ==res_tag)mon_ins(i_move, 29, 30);
	  		ls_ins(i_lw, 30, b);
	  	}
	  	else {
                	restore_sregs(fixdone, fltdone);
                	/* restore dumped value of s-regs on entry */
                	if (frame_size != 0 && name(e) == res_tag) {
                		rri_ins(i_addu, 29, 29, frame_size >> 3);
                        }
                	/* reset stack ptr */
                }
	      if (diagPIClab != 0) {
		uncond_ins(i_b, diagPIClab);
	      }
	      else { uncond_ins(i_j, 31); }
	    }
	}
	else {			/* inlined result */
	  if (rscope_label == 0)rscope_label = new_label();
	  if (rscope_label != exitlab) {
	    uncond_ins(i_b, rscope_label);
	  }
	}
	return mka;
      }				/* end result */

    case diagnose_tag: {
    	output_diag(dno(e), 0,e);
    	mka = make_code(son(e), sp, dest, exitlab);
	output_end_scope(dno(e),e);
	return mka;
    }

    /*
	removed in version 3.0
     case rscope_tag:
      {

	  ans old_procans;
	  int   old_rscope_label = rscope_label;
	  if (dest.answhere.discrim == insomereg) {

	    int  *sr = someregalt (dest.answhere);
	    if (*sr != -1) {
	      failer ("Somereg *2");
	    }
	    *sr = getreg (sp.fixed);
	    setregalt (dest.answhere, *sr);
	  }
	  else
	  if (dest.answhere.discrim == insomefreg) {
	       somefreg sfr;
	       freg fr;
   	       sfr = somefregalt(dest.answhere);
	       if (*sfr.fr != -1) { failer ("Somefreg *2"); }
	       *sfr.fr = getfreg(sp.flt);
	       fr.fr = *sfr.fr;
	       fr.dble = sfr.dble;
	       setfregalt(dest.answhere, fr);
	  }
	  rscope_level++;
	  old_procans = procans;
	  procans = dest.answhere;
	  rscope_label =  exitlab;

	  if (as_file) fprintf(as_file, " # start inlined proc\n");
	  mka = make_code (son (e), sp, dest, rscope_label);
	  if (as_file) fprintf(as_file, " # end inlined proc\n");


	  if (mka.lab != 0 && mka.lab != rscope_label) {
	  	set_label(mka.lab);
	  }
	  mka.lab = rscope_label;
	  mka.regmove = NOREG;
	  rscope_level--;
	  procans = old_procans;
	  rscope_label = old_rscope_label;
	  return mka;
	}
*/

    case solve_tag:
      {
	exp m = bro(son(e));
	int   l = exitlab;
	if (dest.answhere.discrim == insomereg) {
	  /* choose register for result */
	  int  *sr = someregalt(dest.answhere);
	  if (*sr != -1) {
	    failer("Somereg *2");
	  }
	  *sr = getreg(sp.fixed);
	  setregalt(dest.answhere, *sr);
	}
	else
	if (dest.answhere.discrim == insomefreg) {
	       somefreg sfr;
	       freg fr;
   	       sfr = somefregalt(dest.answhere);
	       if (*sfr.fr != -1) { failer("Somefreg *2"); }
	       *sfr.fr = getfreg(sp.flt);
	       fr.fr = *sfr.fr;
	       fr.dble = sfr.dble;
	       setfregalt(dest.answhere, fr);
	}

	for (;;) {		/* set up all the labels in the component
				   labst_tags */
	  no(son(m)) = new_label();
	  if (last(m))
	    break;
	  m = bro(m);
	}

	m = son(e);
	for (;;) {		/* evaluate all the component statements
				*/
	  int   fl = make_code(m, sp, dest, l).lab;
	  clear_all();
	  if (fl != 0)
	    l = fl;
	  if (!last (m)) {	/* jump to end of solve */
	    if (l == 0)
	      l = new_label();
	    if (name(sh(m))!= bothd) {
	      uncond_ins(i_b, l);
	    }
	  }
	  if (last(m)) {
	    mka.lab = l;
	    return mka;
	  };
	  m = bro(m);
	}
      }				/* end solve */



    case case_tag:
      {
	int   r = reg_operand(son(e), sp);
	/* evaluate controlling integer into reg r */
	mm lims;
	exp z = bro(son(e));
	exp zt = z;
	long  n;
	long  l;
	long  u = 0x80000000;

	sp = guardreg(r,sp);
	l = no(zt);
	for (n = 1;; n++) {	/* calculate crude criterion for using
				   jump vector or branches */
	  if (u + 1 != no(zt) && son(zt)!= nilexp) {
	    n++;
	  }
	  if (last(zt)) {
	    u = (son(zt)!= nilexp)? no(son(zt)): no(zt);
	    break;
	  }
	  if (son(zt)!= nilexp) {
	    u = no(son(zt));
	  }
	  else {
	    if (u + 1 == no(zt))
	      u += 1;
	  }

	  zt = bro(zt);
	}

	/* now l is lowest controlling value and u is highest */

	if (is_signed(sh(son(e)))) { u = u/2 - l/2; }
	else { u = ((unsigned)u) /2 - ((unsigned)l) /2; }

	if ( u <= n * n / 4 -3 /* ware overflow! */) {
	  /* space-time product criterion for jump vector instead of tests
	     and branches *//* use jump vector */
	  int   endlab = new_label();
	  int   veclab = next_dlab_sym();
	  baseoff zeroveclab;
	  baseoff zero3;
	  int   mr = getreg(sp.fixed);
	  int r3 = getreg(guardreg(mr,sp).fixed);
	  zero3.base = r3;
	  zero3.offset = 0;
	  zeroveclab.offset = 0;
	  zeroveclab.base = veclab;
	  n = l;

	  if (as_file)
	    fprintf(as_file, "\t.rdata\n$$%d:\n", veclab);
	  out_common(0, irdata);
	  out_common(tempsnos[veclab - 32], ilabel);
	  for (;;) {
	    for (; no (z) > n; n++) {/* o/p jump vector */
	      if (as_file)
		fprintf(as_file,
			(PIC_code)?"\t.gpword\t$%d\n":"\t.word\t$%d\n", endlab);
	      out_value(-endlab,(PIC_code)?igpword:iword, 0, 1);
	    }
	    u = (son(z) == nilexp)? n : no(son(z));
	    for (; n <= u; n++) {
	      props(son(pt(z))) = 1; /* as bug - see labst_tag */
	      if (as_file)
		fprintf(as_file,
			(PIC_code)?"\t.gpword\t$%d\n":"\t.word\t$%d\n", no(son(pt(z))));
	      out_value(-no(son(pt(z))), (PIC_code)?igpword:iword, 0, 1);
	    }
	    if (last(z))
	      break;
	    z = bro(z);
	  }

	  if (as_file)
	    fprintf(as_file, "\t.text\n");
	  out_common(0, itext);

	  ls_ins(i_la, r3, zeroveclab);
	  if (l != 0) {
	    rri_ins(i_addu, mr, r, -l);
	    condri_ins(i_bgeu, mr, u - l + 1, endlab);
	    rri_ins(i_mul, mr, mr, 4);
	  }
	  else {
	    condri_ins(i_bgeu, r, u + 1, endlab);
	    rri_ins(i_mul, mr, r, 4);
	  }
	  rrr_ins(i_addu, r3, r3, mr);
	  ls_ins(i_lw, r3, zero3);
	  if (PIC_code) {  rrr_ins(i_addu, r3, r3, 28); }
	  uncond_ins(i_j, r3);
	  set_label(endlab);
	  return mka;
	}
	else
	if (is_signed(sh(son(e)))) {
	  int   over = 0;	/* use branches - tests are already
				   ordered */
	  lims = maxmin(sh(son(e)));
	  for (;;) {
	    int   lab = no(son(pt(z)));
	    long l = no(z);
	    if (son (z) == nilexp) {/* only single test required */
	      condri_ins(i_beq, r, l, lab);
	      if (l == lims.maxi)
		lims.maxi -= 1;
	      else
		if (l == lims.mini)
		  lims.mini += 1;
	    }
	    else
	      if (u = no(son(z)), l > lims.mini) {
		if (u >= lims.maxi)
		{/* have already tested lower */
		  condri_ins(i_bge, r, l, lab);
		  lims.maxi = l - 1;
		}
		else {
		  if (over == 0) {
		    over = new_label();
		  }
		  condri_ins(i_blt, r, l, over);
		  condri_ins(i_ble, r, u, lab);
		  lims.mini = u + 1;
		}
	      }
	      else		/* lower is <= lower limit of shape */
		if (u < lims.maxi) {
		  condri_ins(i_ble, r, u, lab);
		  lims.mini = u + 1;
		}
		else {		/* upper is >= upper limit of shape */
		  uncond_ins(i_b, lab);
		}
	    if (last(z)) {
	      if (over != 0) {
		set_label(over);
	      } return mka;
	    }
	    z = bro(z);
	  }
	}
	else {
	  int   over = 0;	/* use branches - tests are already
				   ordered */
	  unsigned long maxi;
	  unsigned long mini;
	  lims = maxmin(sh(son(e)));
	  maxi = (unsigned)lims.maxi;
	  mini = (unsigned)lims.mini;
	  for (;;) {
	    int   lab = no(son(pt(z)));
	    unsigned long l = no(z);
	    if (son (z) == nilexp) {/* only single test required */
	      condri_ins(i_beq, r, l, lab);
	      if (l == maxi)
		maxi -= 1;
	      else
		if (l == mini)
		  mini += 1;
	    }
	    else
	      if (u = no(son(z)), l > mini) {
		if (u >= maxi)
		{/* have already tested lower */
		  condri_ins(i_bgeu, r, l, lab);
		  maxi = l - 1;
		}
		else {
		  if (over == 0) {
		    over = new_label();
		  }
		  condri_ins(i_bltu, r, l, over);
		  condri_ins(i_bleu, r, u, lab);
		  mini = u + 1;
		}
	      }
	      else		/* lower is <= lower limit of shape */
		if (u < maxi) {
		  condri_ins(i_bleu, r, u, lab);
		  mini = u + 1;
		}
		else {		/* upper is >= upper limit of shape */
		  uncond_ins(i_b, lab);
		}
	    if (last(z)) {
	      if (over != 0) {
		set_label(over);
	      } return mka;
	    }
	    z = bro(z);
	  }
	}

      }				/* end case */

    case offset_add_tag: { /* byte offset + bit offset - see needs scan */
	exp l = son(e);
	exp r = bro(l);
	int r1 = reg_operand(l, sp);
	int tmp, d, r2;
	space nsp;
	ans aa;
	tmp = getreg(sp.fixed);
	rri_ins(i_sll, tmp, r1, 3);
	d = regfrmdest(&dest, sp);
	if (name(r) ==val_tag) {
		rri_ins(i_addu, d, tmp, no(r));
	}
	else {
		nsp = guardreg(tmp, sp);
		r2 = reg_operand(r, nsp);
		rrr_ins(i_addu, d, tmp, r2);
	}
	setregalt(aa, d);
	mka.regmove = move(aa, dest, guardreg(d, sp), 0);
	return mka;
    }

   case offset_subtract_tag: { /* bit offset - byte offset - see needs scan */
	exp l = son(e);
	exp r = bro(l);
	int r2 = reg_operand(r, sp);
	int tmp, d, r1;
	space nsp;
	ans aa;
	tmp = getreg(sp.fixed);
	rri_ins(i_sll, tmp, r2, 3);
	d = regfrmdest(&dest, sp);
	nsp = guardreg(tmp, sp);
	r1 = reg_operand(l, nsp);
	rrr_ins(i_subu, d, r1, tmp);

	setregalt(aa, d);
	mka.regmove = move(aa, dest, guardreg(d, sp), 0);
	return mka;
    }



    case plus_tag:
      {
        if (optop(e)) {
          mka.regmove =
            comm_op(e, sp, dest, i_addu);
          return mka;
        }
       if ((errhandle(e) &3) ==3 && is_signed(sh(e)) && shape_size(sh(e)) ==32) {
          mka.regmove =
            comm_op(e, sp, dest, i_add);
          return mka;
        }
        else {
          /* possible overflow - can optimised a bit fot lit. operand*/
          int r1 = reg_operand(son(e), sp);
          int r2, r3, r0;
          long over = new_label();
          long trap = trap_label(e);
          space nsp;
          ans aa;
          nsp = guardreg(r1, sp);
          r2 = reg_operand(bro(son(e)), nsp);
          nsp = guardreg(r2, nsp);
          r0 = getreg(nsp.fixed);
          nsp = guardreg(r0, nsp);
          rrr_ins(i_addu, r0, r1, r2);

          switch (name(sh(e))) {
             case slonghd: {
             	r3 = getreg(nsp.fixed);
          	rrr_ins(i_xor, r3, r1, r2);

          	condr_ins(i_bltz, r3, over);
          	rrr_ins(i_xor, r3, r0, r1);
          	condr_ins(i_bltz, r3, trap);

          	set_label(over);
          	break;
             }
             case ulonghd: {
             	r3 = getreg(nsp.fixed);
          	mon_ins(i_not, r3, r1);
          	rrr_ins(i_sltu, r3, r3, r2);
          	condrr_ins(i_bne, r3, 0, trap);
          	break;
             }
             case scharhd: {
                testsigned(r0, -128, 127, trap);
                break;
             }
             case ucharhd: {
                testusigned(r0, 255, trap);
                break;
             }
             case swordhd: {
                testsigned(r0, -0x8000, 0x7fff, trap);
                break;
             }
             case uwordhd: {
                testusigned(r0, 0xffff, trap);
                break;
             }
             default: failer("NOT integer in plus with o/f");
          }
          setregalt(aa, r0);
          mka.regmove = move(aa, dest, nsp, 0);
          return mka;
      }
    }				/* end plus */


    case chvar_tag:
      {
	int   a;
	int   d;
	ans aa;
	int   nsh = name(sh(e));
	if (!endian == ENDIAN_BIG && dest.answhere.discrim == inreg
		&& regalt(dest.answhere)!= 0) {
	      ash arga;
	      arga = ashof(sh(son(e)));
	      if (arga.ashsize <= dest.ashwhere.ashsize) {
		dest.ashwhere = arga;
	      }
	      a = regalt(dest.answhere);
	      code_here(son(e), sp, dest);
	      /* evaluate arguement into reg */
	}
	else {
	      a = reg_operand(son(e), sp);
	      /* evaluate arguement into a */
	}
	setregalt(aa, a);
	if (!optop(e)) {
		long trap = trap_label(e);
		bool sg = is_signed(sh(son(e)));
		switch (nsh) {
		case scharhd:
	           	if (sg) { testsigned(a, -128, 127, trap);}
			else { testusigned(a, 127, trap); }
			break;
		case ucharhd: testusigned(a, 255, trap); break;
		case swordhd:
			if (sg) { testsigned(a, -0x8000, 0x7fff, trap); }
			else { testusigned(a, 0x7fff, trap); }
			break;
		case uwordhd: testusigned(a, 0xffff, trap); break;
		case slonghd:
			if (!sg) { testusigned(a, 0x7fffffff, trap); }
			break;
		case ulonghd:
			if (sg) { testusigned(a, 0x7fffffff, trap); }
			break;
		}
		mka.regmove = move(aa, dest, sp, 1);
		return mka;
	}

	if (sh(son(e)) == sh(e) || nsh  >= slonghd) {
	  /* no changes required, so just move */
	  mka.regmove = move(aa, dest, sp, 1);
	  return mka;
	}

	switch (dest.answhere.discrim) {
	  case insomereg:
	    {
	      int  *dr = someregalt(dest.answhere);
	      d = getreg(sp.fixed);
	      *dr = d;
	      goto out;
	    }
	  case inreg:
	    {
	      d = regalt(dest.answhere);
	      goto out;
	    }
	  default:
	    /* representation in store will be same so just move */
	    {
	      move(aa, dest, sp, 1);
	      return mka;
	    }
	}

    out: 			/* d is destination register - do
				   appropriate ands etc */
	if (d==0) return mka;

	if (nsh == ucharhd) {
	  rri_ins(i_and, d, a, 255);
	}
	else
	  if (nsh == uwordhd) {
	    rri_ins(i_and, d, a,(1 << 16) - 1);
	  }
	  else
	    if (nsh == scharhd) {
	      rri_ins(i_sll, d, a, 24);
	      rri_ins(i_sra, d, d, 24);
	    }
	    else
	      if (nsh == swordhd) {
		rri_ins(i_sll, d, a, 16);
		rri_ins(i_sra, d, d, 16);
	      }
	mka.regmove = d;
	return mka;
      }				/* end chvar */

    case minus_tag:
      {
        if (optop(e)) {
          mka.regmove =
            non_comm_op(e, sp, dest, i_subu);
          return mka;
        }
        else
	if ((errhandle(e) &3) ==3 && is_signed(sh(e)) && shape_size(sh(e)) ==32) {
          mka.regmove =
            non_comm_op(e, sp, dest, i_sub);
          return mka;
        }
        else {
          /* possible overflow - can optimised a bit for lit. operand*/
          int r1 = reg_operand(son(e), sp);
          int r2, r3, r0;
          long over = new_label();
          long trap = trap_label(e);
          space nsp;
          ans aa;
          nsp = guardreg(r1, sp);
          r2 = reg_operand(bro(son(e)), nsp);
          nsp = guardreg(r2, nsp);
          r0 = getreg(nsp.fixed);
          nsp = guardreg(r0,nsp);
          rrr_ins(i_subu, r0, r1, r2);
          switch (name(sh(e))) {
             case slonghd: {
             	r3 = getreg(nsp.fixed);
             	rrr_ins(i_xor, r3, r1, r2);

             	condr_ins(i_bgez, r3, over);
             	rrr_ins(i_xor, r3, r0, r1);
             	condr_ins(i_bltz, r3, trap);

             	set_label(over);
/* Alteration 2 also in plus_tag */
             	break;
             }
             case ulonghd: {
             	r3 = getreg(nsp.fixed);
/* Alteration 3 */
             	rrr_ins(i_sltu, r3, r1, r2);
             	condrr_ins(i_bne, r3, 0, trap);
             	break;
             }
             case scharhd: {
                testsigned(r0, -128, 127, trap);
                break;
             }
             case ucharhd: {
                testusigned(r0, 255, trap);
                break;
             }
             case swordhd: {
                testsigned(r0, -0x8000, 0x7fff, trap);
                break;
             }
             case uwordhd: {
                testusigned(r0, 0xffff, trap);
                break;
             }
             default: failer("NOT integer in minus with o/f");
          }
          setregalt(aa, r0);
          mka.regmove = move(aa, dest, nsp, 0);
          return mka;
      }

    }				/* end minus */

    case mult_tag: case offset_mult_tag:
      {
	exp rop = bro(son(e));
	if (!optop(e)) {	/* test for overflo */
          int r1 = reg_operand(son(e), sp);
          int r2, r3, r0;
          long trap = trap_label(e);
          space nsp;
          ans aa;
          nsp = guardreg(r1, sp);
          r2 = reg_operand(bro(son(e)), nsp);
          nsp = guardreg(r2, nsp);
          r0 = getreg(nsp.fixed);
          nsp = guardreg(r0, nsp);
          r3 = getreg(nsp.fixed);
          switch (name(sh(e))) {
             case slonghd: {
                int r4;
		mon_ins(i_mult, r1, r2);
		hilo_ins(i_mflo, r0);
		hilo_ins(i_mfhi, r3);
		r4 = getreg(guardreg(r3, nsp).fixed);
		rri_ins(i_sra, r4, r0, 31);
		condrr_ins(i_bne, r4, r3, trap);
		break;
	     }
	     case ulonghd: {
	     	mon_ins(i_multu, r1, r2);
	     	hilo_ins(i_mflo, r0);
	     	hilo_ins(i_mfhi, r3);
	     	condrr_ins(i_bne, r3, 0, trap);
	     	break;
	     }
             case scharhd: {
             	rrr_ins(i_mul, r0, r1, r2);
                testsigned(r0, -128, 127, trap);
                break;
             }
             case ucharhd: {
                rrr_ins(i_mul, r0, r1, r2);
                testusigned(r0, 255, trap);
                break;
             }
             case swordhd: {
                rrr_ins(i_mul, r0, r1, r2);
                testsigned(r0, -0x8000, 0x7fff, trap);
                break;
             }
             case uwordhd: {
             	rrr_ins(i_mul, r0, r1, r2);
                testusigned(r0, 0xffff, trap);
                break;
             }
             default: failer("NOT integer in mult with o/f");
          }
          setregalt(aa, r0);
          mka.regmove = move(aa, dest, nsp, 0);
          return mka;
      }



	if (last(rop) && name(rop) == val_tag) {
	  /* multiplication by constant m */
	  int   m = no(rop);
	  int   p2;
	  if (m > 1 && (
		((p2 = m) & (m - 1)) == 0 ||
		(m & (p2 = m + 1)) == 0 ||
		((p2 = m - 1) & (m - 2)) == 0
	     )
	    ) {			/* m = 2^shleng   or  m = 2^(shleng +/- 1)
				*/
	    int   r = reg_operand(son(e), sp);
	    /* evaluate first arguement */
	    int   rr;
	    space nsp;
	    int   shleng;
	    ans aa;
	    for (shleng = 0; p2 != 1; shleng++)
	      p2 >>= 1;

	    switch (dest.answhere.discrim) {
	      case inreg:
		{
		  rr = regalt(dest.answhere);
		  if (rr != r || (m & (m - 1)) == 0) {
		    nsp = sp;
		    break;
		  }
		  /* else continue to next case */
		}
	      default:
		{
		 	if ((m & (m-1)) ==0) {
				rr = getreg(sp.fixed);
				nsp = sp;
			}
			else {
				nsp = guardreg(r, sp);
		  		rr = getreg(nsp.fixed);
			}
		}
	    }

	    rri_ins(i_sll, rr, r, shleng);

	    if ((m & (m - 1))!= 0)
	      rrr_ins(((m & (m + 1)) == 0)? i_subu : i_addu, rr, rr, r);
	    setregalt(aa, rr);
	    mka.regmove = move(aa, dest, guardreg(rr, sp), 1);
	    return mka;
	  }
	}			/* else do straightforward mult */

	mka.regmove = comm_op(e, sp, dest, i_mul);
	return mka;
      }				/* end mult */



    case div0_tag:case div2_tag: case offset_div_by_int_tag: case offset_div_tag:
      {
	exp rop = bro(son(e));
	exp lop = son(e);
	bool uns = !(is_signed(sh(e)));
	int trap;
	space nsp;
	int r0, r1, r2;
	ans aa;
	if (name(rop) == val_tag) {
	  /* division by constant */
	  int   m = no(rop);
	  if (m==1) {
		e = lop;
		goto tailrecurse;
	  }
	  if ((name(e) == div0_tag || uns) && m > 1 && (m & (m - 1)) == 0) {
	      int   r = reg_operand(son(e), sp);
	       /* replace div by 2^shleng by sh right shleng */
              int   shleng;
              int   rr;
              for (shleng = 0; m != 1; shleng++)
                m >>= 1;

              rr = regfrmdest(&dest, sp);
              rri_ins((uns)?i_srl:i_sra, rr, r, shleng);
              setregalt(aa, rr);
              mka.regmove = move(aa, dest, guardreg(rr, sp), 1);
              return mka;
          }
	}

	r1 = reg_operand(lop, sp);
	nsp = guardreg(r1, sp);
	r2 = reg_operand(rop, nsp);

	if (!optop(e)|| (errhandle(e)&3)==2) { /* test for (-inf)/-1 and /0 */
	   long over = new_label();
           trap = ((errhandle(e) &3) ==2)?new_label():trap_label(e);
	   condri_ins(i_beq, r2, 0, trap);
	   if (!uns) {
             condri_ins(i_bne, r2, -1, over);
             condri_ins(i_beq, r1, maxmin(sh(e)).mini, trap);
             set_label(over);
           }
	}
	r0 = regfrmdest(&dest,sp);
	rrr_ins((uns)?i_divu:i_div, r0, r1, r2);
	if ((errhandle(e) &3) ==2)set_label(trap);
	setregalt(aa, r0);
	mka.regmove = move(aa, dest, guardreg(r0,sp), 0);
	return mka;
      }

      case div1_tag:

      {  /* only applies to signed operands */
	exp rop = bro(son(e));
	exp lop = son(e);
	space nsp;
	int r0, r1, r2;
	int lab, treg, trap;
	ans aa;

	if (name (rop) == val_tag ) {/*  division by constant */
	  int   m = no(rop);
	  if (m > 1 && (m & (m - 1)) == 0) {
	      int   r = reg_operand(son(e), sp);
	       /* replace div by 2^shleng by arith sh right shleng */
              int   shleng;
              int   rr;
              for (shleng = 0; m != 1; shleng++)
                m >>= 1;

              rr = regfrmdest(&dest, sp);
              rri_ins(i_sra, rr, r, shleng);
              setregalt(aa, rr);
              mka.regmove = move(aa, dest, guardreg(rr, sp), 1);
              return mka;
          }
	}

	r1 = reg_operand(lop, sp);
	nsp = guardreg(r1, sp);
	r2 = reg_operand(rop, nsp);
	nsp = guardreg(r2, sp);


	if (!optop(e)|| (errhandle(e)&3)==2) { /* test for (-inf)/-1 and /0 */
	   long over = new_label();
           trap = ((errhandle(e) &3) ==2)?new_label():trap_label(e);
	   condri_ins(i_beq, r2, 0, trap);
           condri_ins(i_bne, r2, -1, over);
           condri_ins(i_beq, r1, maxmin(sh(e)).mini, trap);
           set_label(over);
	}
	r0 = regfrmdest(&dest,nsp);
        rrr_ins((is_signed(sh(e)))?i_div:i_divu, r0, r1, r2);
	treg = getreg(guardreg(r0,nsp).fixed);
	lab = new_label();
	hilo_ins(i_mfhi, treg);
	condri_ins(i_beq, treg, 0, lab);
	rrr_ins(i_xor, treg, treg, r2);
	rri_ins(i_sra, treg, treg, 31);
	rrr_ins(i_addu, r0, r0, treg);
	set_label(lab);
	if ((errhandle(e) &3) ==2)set_label(trap);
	setregalt(aa, r0);
	mka.regmove = move(aa, dest, guardreg(r0,sp), 0);
	return mka;
    }


    case abs_tag: {
	int r = reg_operand(son(e), sp);
	int d = regfrmdest(&dest, guardreg(r, sp));
	int l = new_label();
	ans aa;
	setnoreorder();
	condri_ins(i_bge,r, 0, l);
	rri_ins(i_addu, d, r, 0);
	rrr_ins(i_subu, d, 0, r);
	setreorder();
	if (!optop(e)) {
		condri_ins(i_ble, r, maxmin(sh(e)).mini, trap_label(e));
	}
        set_label_no_clear(l);
	setregalt(aa, d);
	mka.regmove = move(aa, dest, guardreg(d, sp), 0);
	return mka;
    }
    case neg_tag: case offset_negate_tag:
      {
	if (optop(e)) {
          mka.regmove = monop(e, sp, dest, i_negu);
          return mka;
        }
        if ((errhandle(e) &3) ==3 && shape_size(sh(e)) == 32) {
          mka.regmove = monop(e, sp, dest, i_neg);
          return mka;
        }
        else {
          int r1 = reg_operand(son(e), sp);
          long trap = trap_label(e);
          int r2;
          ans aa;
          condri_ins((is_signed(sh(e)))?i_ble:i_bne, r1, maxmin(sh(e)).mini, trap);
          r2 = getreg(sp.fixed);
          mon_ins(i_neg, r2, r1);
	  if (is_signed(sh(e)))condri_ins(i_ble, r2, maxmin(sh(e)).mini, trap);
	  setregalt(aa, r2);
	  mka.regmove = move(aa, dest, guardreg(r2, sp), 0);
	  return mka;
	}


      }				/* end neg */



    case goto_lv_tag: {
    	int r = reg_operand(son(e),sp);
    	uncond_ins(i_j, r);
    	clear_all();
    	return mka;
    }



    case shl_tag:
    case shr_tag:
      {
	exp s = son(e);
	exp b = bro(s);
	int   a;
	int   d;
	int sz = shape_size(sh(s));
        bool lded = ((name(s) == name_tag && regofval(s) >= 100)
	      		|| (name(s) == cont_tag &&
		   (name(son(s))!= name_tag || regofval(son(s)) > 0)
	      		   )
		   );
        bool signok = (sz == 32 || name(s) == chvar_tag || lded);
	ans aa;
	space nsp;
	bool sgned = is_signed(sh(e));
	char *shnat;
	char *shun;
	int norms = 0;
	if (lded && name(b) == val_tag && (no(b) == 16 || no(b) == 24)
	    && name(e) == shr_tag ) {
		/* can use short loads instead of shifts */
	  where w;
	  instore is;
	  w = locate(s, sp, sh(s), 0);
	  /* 'address' of  first operand with shape of result */

	  switch (w.answhere.discrim) {
	      /* if w is a register we still have to do shifts */
	    case inreg: {
		a = regalt(w.answhere);
		goto alreadythere;
	      }
	    case notinreg:
	      {
		is = insalt(w.answhere);
		if (!is.adval)
		  break;
		if (is.b.offset == 0 && (a = is.b.base) >= 0 && a <= 31) {
		  goto alreadythere;
		}
	      }
	    default: {	/* this shoudn't happen - shift of address or
	    		    perhaps float in reg */
	    	where temp;
		a = -1;
		setsomeregalt(temp.answhere, &a);
		temp.ashwhere = dest.ashwhere;
		move(w.answhere, temp, sp, 1);
		goto alreadythere;
	      }
	  }

	  d = regfrmdest(&dest,sp);

	  /* d is destination register */
	  if (endian == ENDIAN_LITTLE) {
            if (no(b) == 16) {
              is.b.offset += 2;
            }
            else {
              is.b.offset += 3;
            }
          }
	  ls_ins((no(b) == 16)?((sgned)? i_lh : i_lhu):((sgned)? i_lb : i_lbu),
	      d, is.b);
	  setregalt(aa, d);
	  move(aa, dest, guardreg(d, sp), 0);
	  mka.regmove = d;
	  return mka;

	}

	a = reg_operand(s, sp);
    alreadythere:
	/* choose which shift instruction */
	if (name(e) == shr_tag) {
	  shnat = (sgned)? i_sra : i_srl;
	  shun = i_sll;
	  if (!signok) {
		rri_ins(i_sll, a, a, norms = 32-sz);
	  }
	}
	else {
	  shnat = i_sll;
	  shun = (sgned)? i_sra : i_srl;
	}


	nsp = guardreg(a, sp);
	d = regfrmdest(&dest, nsp);


	if (name(b) == val_tag) {
	  /* if its a constant shift we dont have to choose shift
	     dynamically ... */
	  if (no(b) >= 0) {
	    rri_ins(shnat, d, a, no(b) +norms);
	  }
	  else {
	    rri_ins(shun, d, a, -no(b));
	  }
	}
	else {
	  int   sr = getreg(nsp.fixed);
	  int   ar = reg_operand(b, nsp);
	  if (norms != 0) {
		rri_ins(shnat, a, a, norms);
	  }
	  if (NONEGSHIFTS || !is_signed(sh(e))
	      || (name(b) == and_tag && name(bro(son(b))) == val_tag
		&& no(bro(son(b))) > 0 && no(bro(son(b))) <= 31)
	    ) {			/* ... similarly in these cases */
	    rrr_ins(shnat, d, a, ar);
	  }
	  else {		/* choose shift dynamically - is this
				   necessary for C? */
	    int   l = new_label();
	    int   endl = new_label();
	    condri_ins(i_bge, ar, 0, l);
	    mon_ins(i_neg, sr, ar);
	    rrr_ins(shun, d, a, sr);
	    uncond_ins(i_b, endl);
	    set_label(l);
	    rrr_ins(shnat, d, a, ar);
	    set_label(endl);
	  }
	}
	setregalt(aa, d);
	move(aa, dest, nsp, 1);
	mka.regmove = d;
	return mka;
      }				/* end shl */



    case mod_tag:
      {  /* only applies to signed operands */
	exp rop = bro(son(e));
	exp lop = son(e);
	space nsp;
	int r0, r1, r2;
	int lab, treg;
	ans aa;
	if (name (rop) == val_tag) {/* mod by constant */
	  int   m = no(rop);
	  if (m > 1 && (m & (m - 1)) == 0) {
	    /* mod by power of 2 replaced by and */
	    int   r = reg_operand(son(e), sp);
	    ans aa;
	    int   rr = regfrmdest(&dest,sp);
	    rri_ins(i_and, rr, r, no(rop) - 1);
	    setregalt(aa, rr);
	    mka.regmove = move(aa, dest, guardreg(rr, sp), 1);
	    return mka;
	  }
	}

	r1 = reg_operand(lop, sp);
	nsp = guardreg(r1, sp);
	r2 = reg_operand(rop, nsp);

	if (!optop(e)) { /* test for (-inf)/-1 and /0 */
	   long over = new_label();
           long trap = trap_label(e);
	   condri_ins(i_beq, r2, 0, trap);
           condri_ins(i_bne, r2, -1, over);
           condri_ins(i_beq, r1, maxmin(sh(e)).mini, trap);
           set_label(over);
	}
	r0 = regfrmdest(&dest, nsp);
	rrr_ins(i_rem, r0, r1, r2);
	treg= getreg(guardreg(r0, nsp).fixed);
	lab = new_label();
	condri_ins(i_beq, r0, 0, lab);
	rrr_ins(i_xor, treg, r0, r2);
	condri_ins(i_bge, treg, 0, lab);
	rrr_ins(i_addu, r0, r0, r2);
	set_label(lab);
	setregalt(aa, r0);
	mka.regmove = move(aa, dest, guardreg(r0,sp), 0);
	return mka;
    }

    case rem2_tag: case rem0_tag:
      {
	exp rop = bro(son(e));
	exp lop = son(e);
	bool uns = !is_signed(sh(e));
	space nsp;
	int r0, r1, r2;
	ans aa;
	if ((uns || name(e) ==rem0_tag) && name(rop) == val_tag) {
		/* mod by constant */
	  int   m = no(rop);
	  if (m > 1 && (m & (m - 1)) == 0) {
	    /* mod by power of 2 replaced by and */
	    int   r = reg_operand(son(e), sp);
	    ans aa;
	    int   rr = regfrmdest(&dest,sp);
	    rri_ins(i_and, rr, r, no(rop) - 1);
	    setregalt(aa, rr);
	    mka.regmove = move(aa, dest, guardreg(rr, sp), 1);
	    return mka;
	  }
	  if (m != 0 && (m!=-1 || uns)) {
	  	r1 = reg_operand(lop, sp);
	  	r0 = regfrmdest(&dest, sp);
		rri_ins((uns)?i_remu:i_rem, r0, r1, m);
		setregalt(aa, r0);
		mka.regmove = move(aa, dest, guardreg(r0,nsp), 0);
		return mka;
	  }
	}

	r1 = reg_operand(lop, sp);
	nsp = guardreg(r1, sp);
	r2 = reg_operand(rop, nsp);

	if (!optop(e)) { /* test for (-inf)/-1 and /0 */
	   long over = new_label();
           long trap = trap_label(e);
	   condri_ins(i_beq, r2, 0, trap);
	   if (!uns) {
             condri_ins(i_bne, r2, -1, over);
             condri_ins(i_beq, r1, maxmin(sh(e)).mini, trap);
             set_label(over);
           }
	}

	r0 = regfrmdest(&dest, sp);
	rrr_ins((uns)?i_remu:i_rem, r0, r1, r2);
	setregalt(aa, r0);
	mka.regmove = move(aa, dest, guardreg(r0,nsp), 0);
	return mka;

      }				/* end mod */


    case minptr_tag: case make_stack_limit_tag:
      {
	mka.regmove = non_comm_op(e, sp, dest, i_subu);
	return mka;
      }

    case fplus_tag:
      {
	mka.regmove =
	  fop(e, sp, dest,(name(sh(e))!= shrealhd)? i_add_d : i_add_s);
	if (!optop(e))checknan(e, sp);
	return mka;
      }

    case fminus_tag:
      {
	mka.regmove =
	  fop(e, sp, dest,(name(sh(e))!= shrealhd)? i_sub_d : i_sub_s);
	if (!optop(e))checknan(e, sp);
	return mka;
      }

    case fmult_tag:
      {
	mka.regmove =
	  fop(e, sp, dest,(name(sh(e))!= shrealhd)? i_mul_d : i_mul_s);
	if (!optop(e))checknan(e, sp);
	return mka;
      }

    case fdiv_tag:
      {
	mka.regmove =
	  fop(e, sp, dest,(name(sh(e))!= shrealhd)? i_div_d : i_div_s);
	if (!optop(e))checknan(e, sp);
	return mka;
      }

    case fneg_tag:
      {
	mka.regmove =
	  fmop(e, sp, dest,(name(sh(e))!= shrealhd)? i_neg_d : i_neg_s);
	if (!optop(e))checknan(e, sp);
	return mka;
      }

    case fabs_tag:
      {
	mka.regmove =
	  fmop(e, sp, dest,(name(sh(e))!= shrealhd)? i_abs_d : i_abs_s);
	if (!optop(e))checknan(e, sp);
	return mka;
      }

    case float_tag:
      {
	exp in = son(e);
	where w;
	int r;
	int   f
	=    (dest.answhere.discrim == infreg)? regalt(dest.answhere)
				/* cheat */
	:     getfreg(sp.flt);
	freg frg;
	ans aa;
	ash ain;
	ain = ashof(sh(in));
	frg.fr = f;
	frg.dble = 0;
	if (ain.ashsize == 32 && name(sh(in))!= ulonghd) {
	  setfregalt(w.answhere, frg);
	  w.ashwhere = ashof(sh(in));
	  code_here(in, sp, w);
	  /* evaluate fix pt arguement into float pt reg f */
	}
	else {			/* bytes and halfs must go through fixpt
				   regs */
	  r = reg_operand(in, sp);
	  cop_ins(i_mtc1, r, f << 1);
	}

	rrfp_ins((name(sh(e))!= shrealhd)? i_cvt_d_w : i_cvt_s_w,
	    f << 1, f << 1);
	if (name(sh(e))!= shrealhd) {
	  frg.dble = 1;
	}

	if (name(sh(in)) ==ulonghd) {
	     int tmp = getreg(sp.fixed);
	     int constf = getfreg(guardfreg(f,sp).flt);
	     rri_ins(i_and, tmp,r, 0x80000000);
	     cop_ins(i_mtc1, tmp, constf << 1);
	     rrfp_ins((frg.dble)? i_cvt_d_w : i_cvt_s_w,
	     		constf << 1, constf << 1);
	     rrrfp_ins((frg.dble)? i_sub_d: i_sub_s, f<<1, f<<1, constf<<1);
	     rrrfp_ins((frg.dble)? i_sub_d: i_sub_s, f<<1, f<<1, constf<<1);
	}
	setfregalt(aa, frg);
	move(aa, dest, sp, 1);
	mka.regmove = (frg.dble)? - (f + 32):(f + 32);
	return mka;
      }
    case chfl_tag:
      {
	int   to = name(sh(e));
	int   from = name(sh(son(e)));
	bool dto = (to != shrealhd)? 1 : 0;
	bool dfrom = (from != shrealhd)? 1 : 0;
	if (dto == dfrom) {	/* no change in representation */
	  return make_code(son(e), sp, dest, exitlab);
	}
	else {
	  freg frg;
	  ans aa;
	  where w;
	  if (dest.answhere.discrim == infreg) {
	    frg = fregalt(dest.answhere);
	  }
	  else {
	    frg.fr = getfreg(sp.flt);
	  }
	  frg.dble = dfrom;
	  setfregalt(aa, frg);
	  w.answhere = aa;
	  w.ashwhere = ashof(sh(son(e)));
	  code_here(son(e), sp, w);
	  if (!optop(e) && !dto)setnoreorder();
	  rrfp_ins((dfrom)? i_cvt_s_d : i_cvt_d_s, frg.fr << 1, frg.fr << 1);
	  frg.dble = dto;
	  setfregalt(aa, frg);
	  move(aa, dest, sp, 1);
	  mka.regmove = (frg.dble)? - (frg.fr + 32):(frg.fr + 32);
	  if (!optop(e) && !dto) {
		setreorder();
		checknan(e, sp);
	  }
	  return mka;
	}
      }

    case and_tag:
      {
	exp r = son(e);
	exp l = bro(son(e));
	ans aa;
	space nsp;
	where d1;
	if (last(l) && name(l) == val_tag && (no(l) == 255 || no(l) == 0xffff)
	    && ((name(r) == name_tag && regofval(r) == 100)
	      || (name(r) == cont_tag &&
		(name(son(r))!= name_tag
		  || regofval(son(r)) > 0
		)
	     )
	   )
	    && (aa = iskept(r), (aa.discrim == inreg && regalt(aa) == 0))
	  ) {			/* can use load short instructions */
	  where w;
	  int   dsize = dest.ashwhere.ashsize;
	  int   asize = (no(l) == 255)? 8 : 16;
	  w = locate(r, sp, sh(r), 0);
	  if (w.answhere.discrim == notinreg
	      && dest.answhere.discrim == notinreg && no(l) == 0xffff) {
	    instore isw;
	    instore isd;
	    isw = insalt(w.answhere);
	    isd = insalt(dest.answhere);
	    if (!isw.adval && isd.adval && isw.b.base == isd.b.base &&
		isd.b.offset == isw.b.offset) {
	      if (dsize > 16) {
		if (endian == ENDIAN_LITTLE)isd.b.offset += 2;
		/* just clear out top bits */
		ls_ins(i_sh, 0, isd.b);
	      }
	      return mka;
	    }			/* else drop through to load short case */
	  }
	  if (endian == ENDIAN_LITTLE) {
	  	nsp = guard(w,sp);
	  	setregalt(aa,getreg(nsp.fixed));
	  	d1.answhere = aa;
	  	d1.ashwhere.ashsize = d1.ashwhere.ashalign = asize;
	  	move(w.answhere, d1, nsp, 0);
	  	mka.regmove
	   	 = move (aa, dest, guard(d1,nsp), 0 /* unsigned */ );

            	return mka;
	  }
	}
	mka.regmove = comm_op(e, sp, dest, i_and);
	return mka;
      }
    case or_tag:
      {
	mka.regmove = comm_op(e, sp, dest, i_or);
	return mka;
      }

    case xor_tag:
      {
	mka.regmove = comm_op(e, sp, dest, i_xor);
	return mka;
      }

    case not_tag:
      {
	if (name(son(e)) == or_tag) {
		mka.regmove = comm_op(son(e), sp, dest, i_nor);
	}
	else {
		mka.regmove = monop(e, sp, dest, i_not);
	}
	return mka;
      }


    case offset_pad_tag: {
	int r, v;
	ans aa;
        if (al2(sh(son(e))) >= al2(sh(e))) {
	    if (al2(sh(e))!= 1 || al2(sh(son(e))) == 1) {
		/* is already aligned correctly, whether as bit or byte-offset*/
		e = son(e); goto tailrecurse;
	    }
  	    r = regfrmdest(&dest, sp);
	    v = reg_operand(son(e), sp);
	    rri_ins(i_sll, r, v, 3);
	}
	else {
		int al = (al2(sh(son(e))) ==1)?al2(sh(e)):(al2(sh(e)) /8);
		r = regfrmdest(&dest, sp);
		v = reg_operand(son(e), sp);
		rri_ins(i_addu, r, v, al-1);
		rri_ins(i_and, r, r, -al);
		if (al2(sh(son(e)))==1) { /* operand is bit-offset,
						byte-offset required */
			rri_ins(i_sra, r, r, 3);
		}
	}
	setregalt(aa,r);
	mka.regmove = move(aa, dest, guardreg(r,sp), 0);
        return mka;
    }

   case locptr_tag: {
    	int pr = reg_operand(son(e), sp);
    	int ansr = regfrmdest(&dest, sp);
    	baseoff b;
    	ans aa;
    	b.base = pr; b.offset = -12;
    	ls_ins(i_lw, ansr, b);
    	setregalt(aa,ansr);
    	mka.regmove = move(aa, dest, guardreg(ansr,sp), 0);
    	return mka;
    }

    case cont_tag:
    case name_tag:
    case field_tag:
    case reff_tag:
    case addptr_tag:
    case subptr_tag:
    case contvol_tag:
      {
	where w;
	bool sgned;
	ash desper;

	int   dr = (dest.answhere.discrim == inreg)? dest.answhere.val.regans : 0;
	desper = ashof(sh(e));

	if (name(e) == contvol_tag) {
	  clear_all();
	  setvolatile();
	}
	w = locate(e, sp, sh(e), dr);
	/* 'address of arguement */
	sgned = ((w.ashwhere.ashsize >= 32) || is_signed(sh(e)))? 1 : 0;
	mka.regmove = move(w.answhere, dest,(guard(w, sp)), sgned);
	if (name(e) == contvol_tag) {
	  mka.regmove = NOREG;
	  setnovolatile();
	}
	return mka;
      }				/* end cont */


    case real_tag: {
	int dble = shape_size(sh(e)) >32;
	r2l x;
	int i;
	ans aa;
        instore isa;
	int n = (nca<16)?nca:16;
	x = real2longs_IEEE(&flptnos[no(e)], dble);
	for (i=0; i< n; i++) {
	    rcache *r = &rca[i];
	    if (r->dble == dble && r->r.i1 == x.i1 && r-> r.i2 == x.i2)
		{isa = r->ad; goto found;}
	}
	isa = evaluated(e, 0,(dec*)0);
        rca[nca & 15].dble = dble; rca[nca & 15].r = x; rca[nca & 15].ad = isa;
	nca++;
	settext();
  found:setinsalt(aa, isa);
	mka.regmove = move(aa, dest, sp, 0);
	return mka;
    }
    case string_tag:
      {
	instore isa;
	ans aa;
	bool sgned = ((ashof(sh(e)).ashsize >= 32) || is_signed(sh(e)))? 1 : 0;
	isa = evaluated(e, 0,(dec*)0);
	/* place constant in appropriate data segment */
	settext();
	setinsalt(aa, isa);
	mka.regmove = move(aa, dest, sp, sgned);
	return mka;
      }				/* end eval */

    case val_tag:
      {
	if (shape_size(sh(e)) >32) {
		flt64 temp;
		int ov;
		int r = getreg(sp.fixed);
		space nsp;
		baseoff bc;
		ans aa;
		if (dest.answhere.discrim!=notinreg) return mka;
		if (isbigval(e)) {
			temp = flt_to_f64(no(e), 0, &ov);
		}
		else {
			temp.big = (is_signed(sh(e)) && no(e) <0)?-1:0;
			temp.small = no(e);
		}
		nsp = guardreg(r, sp);
		bc.base =0;
		bc.offset = temp.small;
		ls_ins(i_li, r, bc);
		setregalt(aa,r);
		dest.ashwhere.ashsize = 32;
		dest.ashwhere.ashalign = 32;
		move(aa,dest,nsp,1);
		bc.offset = temp.big;
		ls_ins(i_li, r, bc);
		dest.answhere.val.instoreans.b.offset+=4;
		move(aa,dest,nsp,1);
		return mka;
	}
	if (no(e) == 0) {
	  goto null_tag_case;
	}
	else {
	  ash a;
	  a = ashof(sh(e));
	  if (a.ashsize == 32 || !is_signed(sh(e))) {
	    constval = no(e);
	  }
	  else
	    if (a.ashsize == 8) {
	      constval = no(e) & 255;
	      constval -= (constval & 128) << 1;
	    }
	    else {
	      constval = no(e) & 65535;
	      constval -= (constval & 32768) << 1;
	    }
	  goto moveconst;
	}
      }

    case top_tag: {
	return mka;
      }

    case dump_tag: {
    	long fxd = no(e);
    	long fld = no(pt(e));
    	long old_fixdone = fixdone;
    	long old_fltdone = fltdone;
    	long old_result_label = result_label;
    	exp l;
    	result_label =0;
    	dump_sregs(fxd, fld);
    	if ((fxd &(1<<31))) sp.fixed &= ~(1<<31); /*release link reg */
    	for (l=son(crt_proc); name(l) ==ident_tag && isparam(l);) {
    		/* move any pars still in registers which go into dump regs */
    		int sr = props(son(l));
    		int tr = no(l);
    		if ((props(l) & inanyreg)!=0 && (tr !=sr) && sr != 0) {
    		    if ((props(l) & infreg_bits)!=0 &&
    		        (fld & (3<< (sr<<1)))!=0) {
    		       if (name(sh(son(l)))!= shrealhd) {
    		       	  rrfp_ins(i_mov_d, sr<<1, tr<<1);
    		       }
    		       else {
   		       	  rrfp_ins(i_mov_s, sr<<1, tr<<1);
    		       }
    		       sp.flt &= ~(1<<tr); /* release fpar reg */
    		       no(l) = sr; props(son(l)) = tr;
    		    }
    		    else
    		    if ((fxd & (1<<sr))!=0) {
    		    	mon_ins(i_move, sr, tr);
    		    	sp.fixed &= ~(1<<tr); /* release par reg */
    		    	no(l) =sr; props(son(l)) = tr;
    		    }
    		 }
    		 l = bro(son(l));
    		 if (name(l) ==dump_tag)l = son(l);
        }
        code_here(son(e), sp, dest);
    	for (l=son(crt_proc); name(l) ==ident_tag && isparam(l);) {
    		/* restore structure of moved pars */
    		int sr = props(son(l));
    		int tr = no(l);
    		if ((props(l) & inanyreg)!=0 && (tr !=sr) && sr != 0) {
    		    if ((props(l) & infreg_bits)!=0 &&
    		        (fld & (3<< (tr<<1)))!=0) {
    		       no(l) = sr; props(son(l)) = tr;
    		    }
    		    else
    		    if ((fxd & (1<<tr))!=0) {
    		    	no(l) =sr; props(son(l)) = tr;
    		    }
    		 }
    		 l = bro(son(l));
    		 if (name(l) ==dump_tag)l = son(l);
        }
        if (name(sh(e))!= bothd) {
        	restore_sregs(fxd, fld);
        }
        fixdone = old_fixdone;
        fltdone = old_fltdone;
        result_label = old_result_label;
        return mka;
    }

    case env_size_tag: {
	exp tg = son(son(e));
	procrec * pr = &procrecs[no(son(tg))];
	constval = (pr->frame_size+pr->callee_size) >> 3;
	goto moveconst;
   }

    case proc_tag: case general_proc_tag:
      {				/*
				 set up locals_offset, fixdump, floatdump, frame_size, dumpstart
				 dec stack  ; output frame and mask
				 code here;
				 */
	procrec * pr = & procrecs[no(e)];
	needs * ndpr = & pr->needsproc;
	long pprops = (ndpr->propsneeds);
	bool leaf = (pprops & anyproccall) == 0;
	space tbd;
	space pars;
	long st;
	exp l;

	crt_proc = e;
	old_pls = (postl_chain*)0;

	frame_size = pr->frame_size;
	locals_offset = pr->locals_offset;
	max_args = pr->max_args;
	fixdump = pr->fixdump;
	floatdump = pr->floatdump;
	dumpstart = pr->dumpstart;
	fldumpstart = pr->fldumpstart;
	callee_size = pr->callee_size;

        setframe_flags(e, leaf);

	st = (frame_size+callee_size) >> 3;

	fixdone = fltdone = 0;	/* no s-regs have been dumped yet */


	tbd.fixed = fixdump;
	tbd.flt = floatdump;

	pars.fixed = (leaf)?0:(1<<31);
	pars.flt = 0;

	for (l = son(e);
	     name(l) == ident_tag && isparam(l)
		&& name(son(l))	!= formal_callee_tag;
             l = bro(son(l))) {
		if ((props(l) & infreg_bits)!= 0) {
			int n = props(son(l));
			if (n != no(l) && n != 0) {
				pars.flt |= (3<< (no(l) <<1));
			}
		}
		else
		if ((props(l) & inreg_bits)!=0) {
			int n = props(son(l));
			if (n != no(l) && n != 0) {
				pars.fixed |= (1<<no(l));
			}
		}
	}

	dump_opt(e, &tbd, &pars);

	if (PIC_code) {
	    setnoreorder();
	    out_cpload(current_symno, 25);
	    if (as_file) {
	    	fprintf(as_file, "\t.cpload\t$25\n");
	    }
	    setreorder();
	}


	if (name(e) ==general_proc_tag) {
	  if (Has_vcallees) {
	  	baseoff b;
	  	b.base = 30;
	  	b.offset = -16;
	  	ls_ins(i_sw, local_reg, b); /* old l-reg in -16(30) */
		mon_ins(i_move, local_reg, 29);
		/* if(!leaf) */ {
			b.offset = -12; /* new l_reg in -12(30); */
			ls_ins(i_sw, local_reg, b);
		}
	  }
	  else
	  if (Has_fp && name(e) ==general_proc_tag) {
	 	rri_ins(i_addu, 30, 29, callee_size>>3);
	   }
	  if (frame_size !=0) {
		rri_ins(i_subu, 29, 29, frame_size>>3);
	  }
	}
	else {
	  if (st !=0) {
		rri_ins(i_subu, 29, 29, st);
	  }
	  if (Has_fp) {
		baseoff b;
		b.base = 29;
		b.offset = st-4;
		ls_ins(i_sw, 30, b);
		rri_ins(i_addu, 30, 29, st);
	  }
        }

	if (Has_tos) {
		baseoff b;
		b.base = 30;
		b.offset = -8;
		ls_ins(i_sw, 29, b);
	}

        diagPIClab = 0;
	if (PIC_code && !leaf) {
		dump_gp();
	        if (diag != DIAG_NONE && frame_size != 0) {
			diagPIClab = new_label();
		}
	}

	allocaerr_lab = 0;
	if (proc_has_checkstack(e)) {
		baseoff b;
		exp stl = find_named_tg("__TDFstacklim",
				f_pointer(f_alignment(f_proc)));
		setvar(stl);
		b = boff(stl);
		stackerr_lab = new_label();
		ls_ins(i_lw, 2, b);
		condrr_ins(i_bgt, 2, 29, stackerr_lab);
	}
	else stackerr_lab = 0;

	setframe(st);
	/* I'm not sure that this is the right order for these -
	   diagnostics ? */


	if (fixdump != 0) {
	  setmask(fixdump, dumpstart - st - 4);
	}
	if (floatdump != 0) {
	  setfmask(floatdump, fldumpstart - st - 4);
	}


	if ((pprops & realresult_bit)!= 0) {
	      /* proc has real result */
	      freg frg;
	      frg.fr = 0;
	      frg.dble = (pprops & longrealresult_bit)? 1 : 0;
	      setfregalt(procans, frg);
	}
	else
	if ((pprops & has_result_bit)!= 0) {
		/* proc has fixed pt result */
		setregalt(procans, 2);
	}
	else {		/* proc has no result */
		setregalt(procans, 0);
	}

	rscope_level = 0;
	result_label = 0;

        aritherr_lab = 0;

	code_here(son(e), guardreg(31,sp), nowhere);
	/* evaluate body of proc */
        if (stackerr_lab != 0 || allocaerr_lab != 0) {
	   if (stackerr_lab != 0) {
		set_label(stackerr_lab);
		rri_ins(i_addu, 29, 29, frame_size>>3);
	   }
	   if (allocaerr_lab != 0) { set_label(allocaerr_lab); }
	   do_exception(MIPS_SIGUSR1);
	}
	if (aritherr_lab != 0) {
		set_label(aritherr_lab);
		do_exception(MIPS_SIGFPE);
	}
	if (diagPIClab != 0) {
		set_label(diagPIClab);
		uncond_ins(i_j, 31);
	}

	return mka;

      }				/* end proc */

    case alloca_tag: {
    	exp s = son(e);
    	int r = regfrmdest(&dest, sp);
    	ans aa;
	if (checkalloc(e)) {
	    int tmp = getreg(guardreg(r,sp).fixed);
	    exp stl = find_named_tg("__TDFstacklim",
			f_pointer(f_alignment(f_proc)));
	    baseoff b;
	    setvar(stl);
	    if (name(s) ==val_tag) {
		    rri_ins(i_subu, r, 29,(no(s) +7) &~7);
	    }
	    else {
		    int rr = reg_operand(s, sp);
		    rri_ins(i_addu, tmp, rr, 7);
		    rri_ins(i_and, tmp,tmp, ~7);
		    rrr_ins(i_subu, r, 29, tmp);
	    }
	    b = boff(stl);
	    if (allocaerr_lab == 0)allocaerr_lab = new_label();
	    ls_ins(i_lw, tmp, b);
	    condrr_ins(i_bgt, tmp, r, allocaerr_lab);
	    rri_ins(i_addu, 29, r, 0);
	}
	else {
	    if (name(s) ==val_tag) {
		    rri_ins(i_subu, 29, 29,(no(s) +7) &~7);
	    }
	    else {  int tmp = getreg(sp.fixed);
		    int rr = reg_operand(s, sp);
		    rri_ins(i_addu, tmp, rr, 7);
		    rri_ins(i_and, tmp,tmp, ~7);
		    rrr_ins(i_subu, 29, 29, tmp);
	    }
	}
	reset_tos();
	rri_ins(i_addu, r, 29,(max_args>>3));
    	setregalt(aa, r);
    	mka.regmove = move(aa, dest, sp, 1);
    	return mka;
    }

    case last_local_tag: {
    	int r = regfrmdest(&dest, sp);
    	ans aa;
    	rri_ins(i_addu, r, 29, max_args>>3);
    	setregalt(aa, r);
    	mka.regmove = move(aa, dest, sp, 1);
    	return mka;
    }

    case local_free_tag: {
	exp p = son(e);
    	int r = reg_operand(p, sp);
	exp off = bro(p);
	if (name(off) ==val_tag) {
		rri_ins(i_addu, r, r,(no(off) +7) &~7);
	}
	else {
		int tmp = reg_operand(off, guardreg(r, sp));
		rri_ins(i_addu, tmp, tmp, 7);
		rri_ins(i_and, tmp,tmp, ~7);
		rrr_ins(i_addu, r, r, tmp);
	}

    	if (Has_fp) {
          rri_ins(i_subu, 29, r, max_args>>3);
          reset_tos();
        }
    	return mka;
    }

    case local_free_all_tag: {
    	if (Has_fp) {
          rri_ins(i_subu, 29, 30 ,(frame_size+callee_size) >>3);
          reset_tos();
        }
    	return mka;
    }

    case current_env_tag: {
    	int r = regfrmdest(&dest, sp);
    	ans aa;
    	if (Has_fp) {
    		mon_ins(i_move, r, 30);
    	}
    	else {
    		rri_ins(i_addu, r, 29,(frame_size+callee_size) >>3);
    	}
    	setregalt(aa, r);
    	mka.regmove = move(aa, dest, sp, 1);
    	return mka;
    }

    case env_offset_tag: case general_env_offset_tag:{
    	constval = frame_offset(son(e));
    	goto moveconst;
    }

    case null_tag:
  null_tag_case:
      {
	ans aa;
	setregalt(aa, 0);
	mka.regmove = move(aa, dest, sp, 1);
	return mka;
      }

    case round_tag:
   /* case trunc_tag: */
      {
	int   r = (dest.answhere.discrim == inreg)? regalt(dest.answhere)
	:     getreg(sp.fixed);
	int   sfr = freg_operand(son(e), sp);
	int   dfr = getfreg(guardfreg(sfr, sp).flt);
	ans aa;
	int   s = shape_size(sh(son(e)));
	int mr = (round_number(e) == f_to_nearest)? 3:
			(round_number(e) == f_toward_zero)? 2:
			(round_number(e) == f_toward_larger)? 1:
			(round_number(e) == f_toward_smaller)? 0:3;
	int r1;
	if (r==0)r = getreg(sp.fixed);
	sp = guardreg(r, sp);
	r1 = getreg(sp.fixed);
 	if (!optop(e))setnoreorder();

	cop_ins(i_cfc1, r, 31);
	rrr_ins(i_or, 0, 0, 0); /* nop */
	rri_ins(i_or, r1, r , 3);
	rri_ins(i_xor, r1, r1, mr);
	cop_ins(i_ctc1, r1, 31);
	rrr_ins(i_or, 0, 0, 0); /* nop */
	rrfp_ins((s==32)?i_cvt_w_s:i_cvt_w_d, dfr<<1, sfr<<1);

	if (!optop(e)) {
		setreorder();
		checknan(e, guardreg(r, sp));
	}
	cop_ins(i_ctc1, r, 31);
	cop_ins(i_mfc1, r, dfr << 1);


/*  cfc1    r,$31
  cfc1    r,$31
  ori     r1,dfr,0x3
  xori    r1,r1, to_n = 3, to_z = 2, to+i = 1, to-i = 0
  ctc1    r1,$31
  srl     r0,r0,0
  cvt.w.s $f6,$f0
	check
  ctc1    r,$31
	expansion of i_round_w_s etc
*/

	setregalt(aa, r);
	mka.regmove = move(aa, dest, sp, 1);
	return mka;
      }


    case int_to_bitf_tag:
      {
	int   r;
	where w;
	ash a;
	ash ai;
	ans aa;
	space nsp;
	a = ashof(sh(e));
	ai = ashof(sh(son(e)));
	r = regfrmdest(&dest, sp);

	setregalt(w.answhere, r);
	w.ashwhere = a;
	code_here(son(e), sp, w);
	if (a.ashsize != ai.ashsize) {
	  rri_ins(i_and, r, r,(1 << a.ashsize) - 1);
	}
	nsp = guardreg(r, sp);
	setregalt(aa, r);
	move(aa, dest, nsp, 0);
	return mka;
      }


    case bitf_to_int_tag:
      {
	ash a;
	int   r;
	where w;
	a = ashof(sh(son(e)));
	r = regfrmdest(&dest, sp);

	setregalt(w.answhere, r);
	w.ashwhere = a;
	code_here(son(e), sp, w);
	if (a.ashsize != 32) {
	  if (is_signed(sh(e))) {
	    rri_ins(i_sll, r, r, 32 - a.ashsize);
	    rri_ins(i_sra, r, r, 32 - a.ashsize);
	  }
	  else {
	    rri_ins(i_and, r, r,((1 << a.ashsize) - 1));
	  }
	}

	move(w.answhere, dest, guardreg(r, sp), 0);
	keepreg(e, r);
	return mka;
      }


    case movecont_tag: {
        exp szarg = bro(bro(son(e)));
    	int dr, sr, szr, mr;
 	int lout = new_label();
 	space nsp;
 	int bytemove;
 	where w;

 	sr = getreg(sp.fixed);
 	setregalt(w.answhere, sr);
 	w.ashwhere = ashof(sh(son(e)));
 	IGNORE make_code(son(e), sp, w , 0);
 	nsp = guardreg(sr, sp);
 	dr = getreg(nsp.fixed);
 	setregalt(w.answhere, dr);
 	IGNORE make_code(bro(son(e)), nsp, w, 0);
 	nsp = guardreg(dr, nsp);
 	w.ashwhere = ashof(sh(bro(bro(son(e)))));
 	szr = getreg(nsp.fixed);
 	setregalt(w.answhere, szr);
 	IGNORE make_code(szarg, nsp, w, 0);
 	nsp = guardreg(szr, nsp);
 	mr = getreg(nsp.fixed);
        bytemove = (al2(sh(szarg)) <= 8);


	if (name(szarg)!= val_tag || no(szarg) == 0) {
		condrr_ins(i_beq, szr, 0, lout);
	}
	if (isnooverlap(e)) {
		move_dlts(dr,sr,szr,mr, bytemove);
	}
	else {
		int gtlab = new_label();
		condrr_ins(i_bgt, dr, sr,gtlab);
		move_dlts(dr,sr,szr, mr, bytemove);
		uncond_ins(i_b, lout);
		set_label(gtlab);
		move_dgts(dr,sr,szr, mr, bytemove);
	}
 	set_label(lout);
 	return mka;
   }
    case set_stack_limit_tag: {
	baseoff b;
	int r = reg_operand(son(e), sp);
	exp stl = find_named_tg("__TDFstacklim",
				f_pointer(f_alignment(f_proc)));
	setvar(stl);
	b = boff(stl);
	ls_ins(i_sw, r, b);
	return mka;
    }
    case give_stack_limit_tag: {
    	baseoff b;
    	ans aa;
	int r = regfrmdest(&dest, sp);
	exp stl = find_named_tg("__TDFstacklim",
				f_pointer(f_alignment(f_proc)));
	setvar(stl);
	b = boff(stl);
	ls_ins(i_lw, r, b);
	setregalt(aa, r);
        move(aa, dest, guardreg(r, sp), 1);
	return mka;
    }
    case trap_tag: {
	if (no(e) == f_overflow) {
		do_exception(MIPS_SIGFPE);
	}
	else
	if (no(e) == f_nil_access) {
		do_exception(MIPS_SIGSEGV);
	}
	else do_exception(MIPS_SIGUSR1);

	return mka;
    }



    default:
      failer("not done yet");
  }				/* end outer switch */



moveconst:
  {
    int   r = regfrmdest(&dest, sp);
    baseoff b;
    ans aa;

    if (r != 0) {		/* somewhere! */
      b.base = 0;
      b.offset = constval;
      ls_ins(i_li, r, b);
      setregalt(aa, r);
      move(aa, dest, guardreg(r, sp), 1);
    }
    mka.regmove = r;
    return mka;
  }

}				/* end make_code */
