/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The procedure move produces code to move a value from a to the
 * destination dest. This takes the form of a switch test on the parameter a
 * (type ans) which is either a reg, freg or instore value.
 *
 * In each of the three cases the ans field of the dest is similarly dealt with
 * to determine the necessary instructions for the move. Sizes and alignment
 * are taken from the ash field of the destination.
 *
 * Delivers register used if 1-word destination is instore; otherwise NOREG.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include <reader/basicread.h>

#include <utility/max.h>

#include <main/flags.h>

#include "mips_ins.h"
#include "inst_fmt.h"
#include "addr.h"
#include "procrec.h"
#include "getregs.h"
#include "labels.h"
#include "pseudo.h"
#include "bits.h"
#include "main.h"
#include "guard.h"
#include "move.h"


int
move(ans a, where dest, space freeregs, bool sgned)
{
  long regs = freeregs.fixed;
  long fregs = freeregs.flt;
  int   al = dest.ashwhere.ashalign;
  int size = dest.ashwhere.ashsize;

  if (size==0) return NOREG;

start:
  switch (a.discrim) {
    case insomereg:
    case insomefreg: {
	error(ERR_INTERNAL, "Source reg not specified");
      }

    case inreg:
	/* source in fixed point register */
      {
	int   r = regalt (a);
	switch (dest.answhere.discrim) {
	  case inreg:
	    /* source and dest in fixed register */
	    {
	      int   rd = regalt (dest.answhere);
	      if (rd != 0 /* nowhere */ && rd != r) {
				/* move reg r to reg rd */
		mon_ins (i_move, rd, r);
	      }
	      return NOREG;
	    }			/* end inreg dest */

	  case insomereg:
	    /* can choose dest register to be source reg */
	    {
	      int  *sr = someregalt (dest.answhere);
	      if (*sr != -1) {
		error(ERR_INTERNAL, "Somereg *2");
	      }
	      *sr = r;
	      return NOREG;
	    }

	  case infreg:
	    /* source in fix reg, dest in floating point register */
	    {
	      freg fr;
	      fr = fregalt (dest.answhere);
	      cop_ins (i_mtc1, r, fr.fr << 1);
	      if (fr.dble) {
		cop_ins (i_mtc1, r + 1, (fr.fr << 1) + 1);
	      }
	      return NOREG;
	    }			/* end infreg dest */

    	   case insomefreg: {
	      /* source in fixed, can choose flt dest */
	       somefreg sfr;
	       freg fr;
   	       sfr = somefregalt(dest.answhere);
	       if (*sfr.fr != -1) { error(ERR_INTERNAL, "Somefreg *2"); }
	       *sfr.fr = getfreg(fregs);
	       fr.fr = *sfr.fr;
	       fr.dble = sfr.dble;
	       setfregalt(dest.answhere, fr);
	       goto start;
	  }
	  case notinreg:
	    /* source in fix reg, dest instore */
	    {
	      char *st = (size==al) ?(
	           	(size <= 8) ? i_sb : ((size <= 16) ? i_sh : i_sw)):
	           	((size<=8)? i_sb : ((size <= 16) ? i_ush : i_usw));
	      instore is;
	      is = insalt (dest.answhere);
	      if (is.adval) {
		ls_ins (st, r, is.b);
	      }			/* is the value an address? */
	      else {
		baseoff b;
		b.base = getreg(regs);
		b.offset = 0;
		ls_ins (i_lw, b.base, is.b);
		ls_ins (st, r, b);
	      }

	      return r;
	    }			/* end notinreg dest */


	}			/* end switch dest */
      }				/* end inreg a */
    case infreg:
	/* source in floating point register */
      {
	freg fr;
	fr = fregalt (a);
	switch (dest.answhere.discrim) {
	  case inreg:
	    /* source in float reg, dest in fixed point register */
	    {
	      int   rd = regalt (dest.answhere);
	      if (rd != 0) {
		switch (endian) {
		case ENDIAN_BIG:
			if (fr.dble) {
		  	  cop_ins (i_mfc1, rd, (fr.fr << 1) + 1);
			}
			cop_ins (i_mfc1, rd+1, fr.fr << 1);
			break;
		case ENDIAN_LITTLE:
			cop_ins (i_mfc1, rd, fr.fr << 1);
			if (fr.dble) {
		  	  cop_ins (i_mfc1, rd + 1, (fr.fr << 1) + 1);
			}
			break;
		}
	      }
	      return NOREG;
	    }			/* end inreg dest */
	  case insomereg:
	    /* source in flt reg, can choose dest reg */
	    {
	      int  *sr = someregalt (dest.answhere);
	      if (*sr != -1) {
		error(ERR_INTERNAL, "Somereg *2");
	      }
	      *sr = getreg (regs);
	      setregalt (dest.answhere, *sr);
	      goto start;
	    }
	   case insomefreg: {
		/* can choose dest reg to be source reg */
	       somefreg sfr;
	       sfr = somefregalt(dest.answhere);
	       if (*(sfr.fr) !=-1) error(ERR_INTERNAL, "some freg * 2");
	       *(sfr.fr) = fr.fr;
	        return NOREG;
	   }
	  case infreg:
	    /* source and dest in floating point registers */
	    {
	      freg frd;
	      frd = fregalt (dest.answhere);
	      if (fr.fr != frd.fr) {
		rrfp_ins ((frd.dble) ? i_mov_d : i_mov_s, frd.fr << 1, fr.fr << 1);
	      }
	      return NOREG;
	    }			/* end infreg dest */
	  case notinreg:
	    /* source in flt reg, dest instore */
	    {
	      char *st = (fr.dble) ? i_s_d : i_s_s;
	      instore is;

	      if ((dest.ashwhere.ashsize == 64 && !fr.dble) ||
		  (dest.ashwhere.ashsize == 32 && fr.dble)) {
		st = (dest.ashwhere.ashsize==64) ? i_s_d:i_s_s;
		/* error(ERR_INTERNAL, "INCONSISTENT SIZES"); */
	      }

	      is = insalt (dest.answhere);
	      if (is.adval) {
		lsfp_ins (st, fr.fr << 1, is.b);
	      }
	      else {
		baseoff b;
		b.base = getreg (regs);
		b.offset = 0;
		ls_ins (i_lw, b.base, is.b);
		lsfp_ins (st, fr.fr << 1, b);
	      }

	      return (fr.dble) ? -(fr.fr + 32) : (fr.fr + 32);
	    }			/* end notinreg dest */
	}			/* end switch dest */
      }				/* end infreg a */



    case notinreg:
	/* source instore */
      {
	instore iss;
	char *ld;
	iss = insalt (a);
	if (iss.adval && iss.b.offset == 0 && iss.b.base > 0 && iss.b.base <= 31) {
	  setregalt (a, iss.b.base);
	  goto start;
	}

	if (al==1) { /* contained size for naked bitfields */
		al = (size<=8)? 8: ((size<=16)? 16:32);
	}
	ld = (iss.adval) ? i_la : ((al <= 8) ? ((sgned) ? i_lb : i_lbu) :
	    ((al <= 16) ? ((sgned) ? i_lh : i_lhu) : i_lw));
	/* determine which load instruction to use from al and adval */

	switch (dest.answhere.discrim) {
	  case insomefreg: {
	     /* source in store can choose dest freg */
	       somefreg sfr;
	       freg fr;
   	       sfr = somefregalt(dest.answhere);
	       if (*sfr.fr != -1) { error(ERR_INTERNAL, "Somefreg *2"); }
	       *sfr.fr = getfreg(fregs);
	       fr.fr = *sfr.fr;
	       fr.dble = sfr.dble;
	       setfregalt(dest.answhere, fr);
	       goto start;
	  }
	  case insomereg:
	    /* source instore, can choose dest reg */
	    {
	      int  *sr = someregalt (dest.answhere);
	      if (*sr != -1) {
		error(ERR_INTERNAL, "Somereg *2");
	      }
	      *sr = getreg (regs);
	      setregalt (dest.answhere, *sr);
	      /* and continue to next case */
	    }
	  case inreg:
	    /* source and dest in fixpnt reg */
	    {
	      int   rd = regalt (dest.answhere);
	      if (rd != 0 /* nowhere */ ) {
		ls_ins (ld, rd, iss.b);
	      }
	      return NOREG;
	    }			/* end inreg dest */


	  case infreg:
	    /* source instore, dest in floating pnt reg */
	    {
	      freg frd;
	      frd = fregalt (dest.answhere);
	      if (iss.b.base == 0 && iss.b.offset == 0) {
		cop_ins (i_mtc1, 0, frd.fr << 1);
	        if (frd.dble) {
		cop_ins (i_mtc1, 0, (frd.fr << 1) + 1);
	        }
		return NOREG;
	      }
	      lsfp_ins ((frd.dble) ? i_l_d : i_l_s, frd.fr << 1, iss.b);
	      return NOREG;
	    }			/* end infreg dest */


	  case notinreg:
	    /* source and dest instore */
	    {
	      char *st = (al <= 8) ? i_sb : ((al <= 16) ? i_sh : i_sw);
	      /* determine which store instruction from al (align from dest) */
	      instore isd;
	      int   sunit = MIN(al, 32);
	      int   step = sunit >> 3;
	      int   s = (dest.ashwhere.ashsize + sunit - 1) / sunit;
	      bool unalign = 0;
	      isd = insalt (dest.answhere);
	      if (al == 8 && s >= 4) {
		int   r = getreg (regs);
		freeregs = guardreg(r,freeregs);
		/* register for holding values transferred */
		unalign = 1;
		if (s <= 16) {	/* in line unalligned move */
		  if (!isd.adval) {
		    int r3 = getreg(freeregs.fixed);
		    ls_ins (i_lw, r3, isd.b);
		    isd.b.base = r3;
		    isd.b.offset = 0;
		    isd.adval = 1;
		  }
		  for (; s >= 4; s -= 4) {
		    ls_ins (i_ulw, r, iss.b);
		    ls_ins (i_usw, r, isd.b);
		    iss.b.offset += 4;
		    isd.b.offset += 4;
		  }

		}
		else {
		/* unaligned loop move *//* copy with loop, length in r1, to in 2, from in 3 */
		  int   l = new_label ();
		  int   r1 = getreg (freeregs.fixed);
		  int r3, r2;
		  baseoff src;
		  baseoff dst;
		  freeregs = guardreg(r1,freeregs);
		  r3 = getreg(freeregs.fixed);
		  r2 = getreg(guardreg(r3,freeregs).fixed);

		  src.base = r3; src.offset = 0;
		  dst.base = r2; dst.offset = 0;

		  ls_ins ((isd.adval) ? i_la : i_lw, r2, isd.b);
		  isd.adval = 1;
		  ls_ins (i_la, r3, iss.b);


		  rri_ins (i_addu, r1, r3, (s & ~3));
		  /* output instruction to initialise counter */
		  set_label (l);
		  ls_ins (i_ulw, r, src);
		  rri_ins (i_addu, r3, r3, 4);
		  ls_ins (i_usw, r, dst);
		  rri_ins (i_addu, r2, r2, 4);
		  condrr_ins (i_bne, r1, r3, l);
		  /* instruction to test end of loop */

		  s = s & 3;
		  iss.b = src;
		  isd.b = dst;
		}

		for(; s>0; s--) {
			ls_ins(i_lb, r, iss.b);
			ls_ins(i_sb, r, isd.b);
			iss.b.offset += 1;
		    	isd.b.offset += 1;
		}
		return NOREG;
	      }

	      if (s <= inlineassign) {/* move in line */
		int   r = getreg (regs);
		/* register for holding values transferred */

		if (!isd.adval) {
		  int r3 = getreg(guardreg(r,freeregs).fixed);
		  freeregs = guardreg(r3,freeregs);
		  ls_ins (i_lw, r3, isd.b);
		  isd.b.base = r3;
		  isd.b.offset = 0;
		}
		if (s == 1) {
		  ls_ins (ld, r, iss.b);
		  ls_ins (st, r, isd.b);

		  return (unalign) ? NOREG : r;
		}
		else {
		  int   er = getreg (freeregs.fixed);
		  int   nr = r;
		  for (; s > 0; --s) {
		    ls_ins (ld, nr, iss.b);
		    ls_ins (st, nr, isd.b);
		    iss.b.offset += step;
		    isd.b.offset += step;
		    if (nr == r) {
		      nr = er;
		    }
		    else {
		      nr = r;
		    }
		  }
		  return NOREG;
		}
	      }			/* inline end */
	      else {		/* copy with loop, length in r1, to in r2, from in r3 */
		int   a = getreg (regs);
				/* get register for transferring values */
		int   l = new_label ();
		int   r1, r2, r3;
		baseoff src;
		baseoff dst;
		freeregs = guardreg(a,freeregs);
		r1 = getreg(freeregs.fixed);
		freeregs = guardreg(r1,freeregs);
		r2 = getreg(freeregs.fixed);
		freeregs = guardreg(r2,freeregs);
		r3 = getreg(freeregs.fixed);
		src.base = r3; src.offset = 0;
		dst.base = r2; dst.offset = 0;


		ls_ins ((isd.adval) ? i_la : i_lw, r2, isd.b);
		ls_ins (i_la, r3, iss.b);

		ri_ins (i_li, r1, s);
		/* output instruction to initialise counter */
		set_label (l);
		ls_ins (ld, a, src);
		rri_ins (i_addu, r3, r3, step);
		ls_ins (st, a, dst);
		rri_ins (i_addu, r2, r2, step);
		rri_ins (i_subu, r1, r1, 1);
		/* instruction to decrement counter */
		condr_ins (i_bgtz, r1, l);
		/* instruction to test end of loop */

		return NOREG;
	      }			/* loop assign */
	    }			/* end notinreg dest */
	}			/* end switch dest */
      }				/* end notinreg a */
  }				/* end switch a */

  UNREACHED;
  return NOREG;
}
