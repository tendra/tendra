/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The procedure move produces code to move a value from a to the
 * destination dest. This takes the form of a switch test on the parameter
 * a (type ans) which is either a reg, freg instore or bitad value. In
 * each of the three cases the ans field of the dest is similarly dealt
 * with to determine the necessary instructions for the move. Sizes and
 * alignment are taken from the ash field of the destination.
 *
 * Delivers register used if 1-word destination is instore; otherwise NOREG.
 */

#include <assert.h>

#include <shared/error.h>

#include <local/ash.h>

#include "hppains.h"
#include "inst_fmt.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "proc.h"
#include "getregs.h"
#include "labels.h"
#include "comment.h"
#include "bitsmacs.h"
#include "regmacs.h"
#include "maxminmacs.h"
#include "make_code.h"
#include "move.h"

extern char reg_name_tab[32][5];
#define	MAX_STEPS_INLINE_MOVE	12	/* (was 8) 16 instructions */

#define NBITMASK(n)		((unsigned long)( (n)==32 ? 0L : ((1<<(n))-1) ))

/*
 * ins_sgn_pair[FALSE]		unsigned instruction
 * ins_sgn_pair[TRUE]		signed instruction
 */
typedef ins_p ins_sgn_pair[2 /* FALSE..TRUE */ ];


static const ins_sgn_pair st_ins_sz[] =
{
   /* 0 */ {I_NIL, I_NIL},
   /* 8 */ {i_stb, i_stb},
   /* 16 */ {i_sth, i_sth},
   /* 24 */ {I_NIL, I_NIL},
   /* 32 */ {i_stw, i_stw},
   /* 40 */ {I_NIL, I_NIL},
   /* 48 */ {I_NIL, I_NIL},
   /* 56 */ {I_NIL, I_NIL},
   /* 64 */ {I_NIL, I_NIL}
};

/* the st instruction for object sized bits */
ins_p
i_st_sz(int bits)
{
    return st_ins_sz[(bits) / 8][0];
}

/* load address represented by is into reg */
void
ld_addr(instore is, int reg)
{
  comment1("ld_addr: adval=%d", is.adval);

  if (is.adval)
  {
     if (IS_FIXREG(is.b.base))
	ld_ins(i_lo,0,is.b,reg);
     else
	set_ins("",is.b,reg);
  }
  else
     ld_ins(i_lw,1,is.b,reg);
}

/* get address represented by is */
int
addr_reg(instore is, long regs)
{
  int r;

  comment1("addr_reg: adval=%d", is.adval);

  if (is.adval && IS_FIXREG(is.b.base) && is.b.offset == 0)
  {
    /* simply return base reg */
    return is.b.base;
  }

  /* otherwise load address into reg */
  r = getreg(regs);
  ld_addr(is, r);
  return r;
}

int
move(ans a, where dest, long regs, bool sgned)
{
  int al = dest.ashwhere.ashalign;
  if ( dest.ashwhere.ashsize == 0 )
     return NOREG ;

  FULLCOMMENT4("move: %s -> %s, dest ashsize,ashalign = %d,%d",
	       (int)ANSDISCRIM_NAME(discrim ( a )),
	       (int)ANSDISCRIM_NAME(discrim ( dest.answhere )),
	       dest.ashwhere.ashsize, dest.ashwhere.ashalign);
  assert((discrim ( dest.answhere ) == inreg && dest.answhere.val.regans == GR0)	/* nowhere */
	 || dest.ashwhere.ashsize > 0);	/* unitialised dest.ashwhere */

start:

  switch (discrim ( a ))
  {
  case insomereg:
  case insomefreg:
    {
      error(ERROR_SERIOUS, "move: source somereg not specified");
      return NOREG;
    }
#if USE_BITAD
  case bitad:
    /* source is bit address */
    {
      instore iss;
      int bpos;
      int bsize;
      int bshift;
      baseoff word_base;
      int reg;
      bool reg_is_dest;

      /* +++ bitad to bitad move, minimise shifts and masks */

      comment("move: source bit address");

      if (discrim ( dest.answhere ) == inreg)
      {
	reg = dest.answhere.val.regans;
	if (reg == 0)
	{
	  /* dest is nowhere, do nothing */
	  return NOREG;		/* nowhere */
	}
	reg_is_dest = 1;
      }
      else
      {
	reg = getreg(regs);
	reg_is_dest = 0;
      }

      iss = bitadalt(a);

      /* word_base is bit address of word containing source */
      word_base.base = iss.b.base;
      word_base.offset = iss.b.offset & ~31;

      /*
       * Set bpos, bsize, bshift to number of bits in a 32 bit word as in
       * following picture:
       *
       *		   < FIELD  >
       *	00000000000111111111100000000000
       *	<  bpos   >< bsize  >< bshift  >
       */
      bpos = iss.b.offset - word_base.offset;
      bsize = dest.ashwhere.ashsize;
      bshift = 32 - bpos - bsize;

      comment4("	dest ashsize,ashalign = %d,%d, iss.b.offset=%d (%%32=%d)",
	       dest.ashwhere.ashsize, dest.ashwhere.ashalign, iss.b.offset, iss.b.offset % 32);
      comment3("	bpos=%d, bsize=%d, bshift=%d", bpos, bsize, bshift);

      if (bpos + bsize > 32)
	error(ERROR_SERIOUS, "bit load > 32 ");

      {
	int tmp = bpos;
	bpos = bshift;
	bshift  = tmp;
      }

      /* now adjust word_base to be a byte address */
      word_base.offset /= 8;

#if 1
      /* optimise when word, half or byte loads are possible */
      if (!iss.adval && bsize == 8 && (bpos & 7) == 0)
      {
	/* byte load */
	word_base.offset += bpos / 8;
	ld_ins(i_lb,sgned,word_base,reg);
	bsize = 32;
      }
      else if (!iss.adval && bsize == 16 && (bpos & 15) == 0)
      {
	/* half load */
	word_base.offset += bpos / 8;
	ld_ins(i_lh,sgned,word_base,reg);
	bsize = 32;
      }
      else if (bsize == 32)
      {
	/* word load */
	ld_ins(i_lw,1,word_base,reg);
	bsize = 32;
      }
      else
#endif
	 ld_ins(i_lw,1,word_base,reg);

      if (bsize == 32)
      {
	/* field is entire word, nothing to do */
	;
      }
      else if (!sgned && bshift == 0)
	 /*
	  * Field is at right of word, and no need to propagate sign bit,
	  * simply mask.
	  */
	 riir_ins(i_dep,c_,0,31-bsize,32-bsize,reg);
      else
      {
 	 /* shift left than right, propagating sign if signed field */
	 if (sgned)
	    riir_ins(i_extrs,c_,reg,31-bshift,32-bpos-bshift,reg);
	 else 
	    riir_ins(i_extru,c_,reg,31-bshift,32-bpos-bshift,reg);
      }

      if (reg_is_dest)
      {
	/* already in its destination */
	return NOREG;
      }

      setregalt(a, reg);

      comment("move: source bit address now inreg");

      /*
       * Source 'a' adjusted into fixed point reg. Fall through to 'inreg'
       * code to process destination.
       */

    }				/* end bitad source */

    /* FALLTHROUGH */
#endif

  case inreg:
    /* source in fixed point register */
    {
      int r = regalt(a);

      switch (discrim ( dest.answhere ))
      {
      case inreg:
	/* source and dest in fixed register */
	{
	  int rd = regalt(dest.answhere);

	  if (rd != GR0 /* nowhere */ && rd != r)
 	     /* move reg r to reg rd */
	     rr_ins(i_copy,r,rd);
	  return NOREG;
	}			/* end inreg dest */

      case insomereg:
	/* source and dest in fixed register */
	{
	  int *sr = someregalt(dest.answhere);

	  if (*sr != -1)
	  {
	    error(ERROR_SERIOUS, "move: somereg already set");
	  }
	  *sr = r;
	  return NOREG;
	}

      case infreg:
	/* dest in floating point register */
	{
	  freg fr;
	  fr = fregalt(dest.answhere);
	  st_ins(i_sw, r, mem_temp(0));
	  ldf_ins(i_fldw, mem_temp(0), 3*fr.fr);
	  if (fr.dble)
	  {
	    /* +++ i_std when aligned wfs 27/1/94 change this */
	    st_ins(i_sw,r+1,mem_temp(4));
	    ldf_ins(i_fldw, mem_temp(4), 3*(fr.fr)+2);
	  }
	  return NOREG;
	}			/* end infreg dest */

      case notinreg:
	/* dest instore */
	{
	  int sz;
	  instore is;

#if USE_BITAD
	  if (al == 1)
  	     sz = dest.ashwhere.ashsize;
	  else
	  {
	     assert(al == dest.ashwhere.ashsize);
	     sz = al;
	  }
#else
	  sz = dest.ashwhere.ashsize;
	  if (al == 1)
	  {
	     if (sz<=8)
		al = 8;
	     else
	     if (sz<=16)
		al = 16;
	     else
		al = 32;
	  }
	  if ( al == 64 ) al = 32 ;
#endif
	  is = insalt(dest.answhere);
	  if (is.adval)		/* is the value an address? */
 	     st_ins( (sz==8 ? i_sb : (sz==16 ? i_sh : i_sw)), r, is.b );
	  else
	  {
 	     ld_ins(i_lw,1,is.b,GR1);
	     st_ir_ins( (sz==8 ? i_stbs : (sz==16 ? i_sths : i_stws)), cmplt_, r, fs_, empty_ltrl, 0, GR1);
	  }

	  return r;
	}			/* end notinreg dest */
#if USE_BITAD
      case bitad:
	/* source in fix reg, dest is bit address */
	{
	  instore is ;
	  int rsrc = r;
	  int rtmp;
	  int bpos;
	  int bsize;
	  int bshift;
	  baseoff word_base;
	  unsigned long mask_left;
	  unsigned long mask_right;
	  unsigned long mask;
	  is = bitadalt(dest.answhere);

	  /* +++ const to bit address */

	  comment("move: dest bit address");

	  if (!is.adval)
	  {
	    error(ERROR_SERIOUS, "no move to var bits");
	  }

	  /* word_base is bit address of word containing source */
	  word_base.base = is.b.base;
	  word_base.offset = is.b.offset & ~31;

	  /*
	   * Set bpos, bsize, bshift to number of bits in a 32 bit word as in
	   * following picture:
	   */
	  bpos = is.b.offset - word_base.offset;
	  bsize = dest.ashwhere.ashsize;
	  bshift = 32 - bpos - bsize;

	  comment4("	dest ashsize,ashalign = %d,%d, is.b.offset=%d (%%32=%d)",
		   dest.ashwhere.ashsize, dest.ashwhere.ashalign, is.b.offset, is.b.offset % 32);
	  comment3("	bpos=%d, bsize=%d, bshift=%d", bpos, bsize, bshift);

	  if (bpos + bsize > 32)
	    error(ERROR_SERIOUS, "store bits over w-boundary");

	  {
	    int tmp = bpos;
	    bpos = bshift;
	    bshift  = tmp;
	  }

	  /* mask_left is all 1s to cover 'bpos' bits */
	  if (bpos == 0)
	    mask_left = 0;
	  else
	    mask_left = NBITMASK(bpos) << (32 - bpos);

	  /* mask_right is all 1s to cover 'bshift' bits */
	  if (bshift == 0)
	    mask_right = 0;
	  else
	    mask_right = NBITMASK(bshift);

	  mask = mask_left | mask_right;

	  comment2("	mask_left=%#x, mask_right=%#x", mask_left, mask_right);


	  /* now adjust word_base to be a byte address */
	  word_base.offset /= 8;

#if 1
	  /* optimise when word, half or byte stores are possible */
	  if (bsize == 32)
	  {
	    /* word store */
	    st_ins(i_sw, rsrc,word_base);
	    return NOREG;
	  }
	  else if (bsize == 16 && (bpos & 15) == 0)
	  {
	    /* half store */
	    word_base.offset += bpos / 8;
	    st_ins(i_sh, rsrc, word_base);
	    return NOREG;
	  }
	  else if (bsize == 16 && bpos == 8)
	  {
	    /* half store by two byte stores */
	    word_base.offset += bpos / 8 + 1;
	    st_ins(i_sb, rsrc, word_base);
	    word_base.offset -= 1;
	    /* cannot use GR1 as GR1 may be needed by st_ins() */
	    rtmp = getreg(regs);
	    rrir_ins(i_shd,c_,0,rsrc,8,rtmp);
	    st_ins(i_sb, rtmp, word_base);
	    return NOREG;
	  }
	  else if (bsize == 8 && (bpos & 7) == 0)
	  {
	    /* byte store */
	    word_base.offset += bpos / 8;
	    st_ins(i_sb, rsrc, word_base);
	    return NOREG;
	  }
#endif

	  /*
	   * cannot use GR1 as GR1 may be needed by st_ins() or for big
	   * mask
	   */
	  rtmp = getreg(regs);
	  regs |= RMASK(rtmp);

	  /* load dest word and mask out field */
	  ld_ins(i_lw,1,word_base,rtmp);
	  if (mask != ~0)
	  {
	     int l,p;
	     if (bshift==0 || bshift==32)
		p=31;
	     else
		p=31-bshift;
	     if (bpos==0 || bpos==32)
		l=p+1;
	     else
		l=p+1-bpos;
	     riir_ins(i_dep,c_,0,p,l,rtmp);
	  }
	  /* shift source to dest field position */
	  if (bshift != 0)
	  {
	     rrir_ins(i_shd,c_,rsrc,0,32-bshift,GR1);
 	     rsrc = GR1;
 	     /* safe to use GR1 as not needed for the st_ins() */
	  }

	  /* or source and dest and store out */
	  rrr_ins(i_or,c_,rsrc,rtmp,rtmp);
	  st_ins(i_sw, rtmp, word_base);

	  return NOREG;
	}
#endif
		default:
 		 error(ERROR_SERIOUS, "fixed -> wrong dest");

      }				/* end switch dest */
      /* NOTREACHED */
    }				/* end inreg a */

  case infreg:
    /* source in floating point register */
    {
      freg fr;

      fr = fregalt(a);
      switch (discrim ( dest.answhere ))
      {
      case inreg:
	/* dest in fixed point register */
	{
	  int rd = regalt(dest.answhere);

	  if (rd != 0)
	  {
	    /* store and load to move to fixed reg */
	    stf_ins(i_fstw, 3*fr.fr, mem_temp(0));
	    ld_ins(i_lw,1,mem_temp(0),rd);
	    if (fr.dble)
	    {
	       /* +++ i_std when aligned wfs, 27/1/94 must correect this */
	       stf_ins(i_fstw, (3*fr.fr)+2, mem_temp(4));
	       ld_ins(i_lw,1,mem_temp(4),rd+1);
	    }
	  }
	  return NOREG;
	}			/* end inreg dest */

      case insomereg:
	/* source in flt reg, can choose dest reg */
	{
	  int *sr = someregalt(dest.answhere);

	  if (*sr != -1)
	  {
	    error(ERROR_SERIOUS, "move: somereg already set");
	  }
	  *sr = getreg(regs);
	  setregalt(dest.answhere, *sr);
	  goto start;
	}

      case infreg:
	/* source and dest in floating point registers */
	{
	  freg frd;

	  frd = fregalt(dest.answhere);
	  if (fr.fr != frd.fr)
	  {
	      if (frd.dble)
		 rrf_ins(i_fcpy,f_dbl,"",3*(fr.fr)+1,3*(frd.fr)+1);
	      else
		 rrf_ins(i_fcpy,f_sgl,"",3*(fr.fr),3*(frd.fr));
	  };
	  return NOREG;
	}			/* end infreg dest */

      case notinreg:
	/* source in flt reg, dest instore */
	{
	  ins_p st = (fr.dble) ? i_fstd : i_fstw;
	  instore is;

	  if ((dest.ashwhere.ashsize == 64 && !fr.dble) ||
	      (dest.ashwhere.ashsize == 32 && fr.dble) )
	  {
	    error(ERROR_SERIOUS, "inconsistent sizes");
	  }
	  is = insalt(dest.answhere);
	  if (is.adval)
	  {
	    /* allow doubles not to be double aligned in mem, ie param */
	    /* wfs 27/1/94 must change */
	    if (fr.dble)
	    {
	      if ((is.b.offset & 7) == 0)	/* double aligned in mem */
		 stf_ins(i_fstd,(3*fr.fr)+1,is.b);
	      else
	      {
		/* not double aligned in mem, ie parameter */
		stf_ins(i_fstw, 3*fr.fr, is.b);
		is.b.offset += 4;
		stf_ins(i_fstw, (3*fr.fr)+2, is.b);
	      }
	    }
	    else
	       /* single */
	       stf_ins(i_fstw, 3*fr.fr, is.b);
	  }
	  else
	  {
	    baseoff b;

	    b.base = getreg(regs);
	    b.offset = 0;
	    ld_ins(i_lw,1,is.b,b.base);
	    if (st==i_fstw)
	       stf_ins(i_fstw,3*fr.fr,b);
	    else
	       stf_ins(i_fstd,(3*fr.fr)+1,b);
	  };

	  return fr.dble ? -(fr.fr + 32) : (fr.fr + 32);
	}			/* end notinreg dest */
      default:{}
      }				/* end switch dest */
      /* NOTREACHED */
    }				/* end infreg a */

  case notinreg:
    /* source instore */
    {
      /* get into register and repeat */
      instore iss;
      int size = dest.ashwhere.ashsize;
      iss = insalt(a);

      if (iss.adval && iss.b.offset == 0 && IS_FIXREG(iss.b.base))
      {
	/* address of [base_reg+0] is base_reg */
	setregalt(a, iss.b.base);
	goto start;
      }
#if USE_BITAD
      if (al == 1)
      {
	iss.b.offset *= 8;
	setbitadalt(a, iss);
	goto start;
      }
#else
      if( al==1 )
      {
 	 if ( size<=8 )
	    al = 8;
	 else
	 if ( size<=16 )
 	    al = 16;
 	 else
 	   al = 32;
      }
      if (al == 64)
	al = 32;       /* +++ we cannot manage 64 bit int regs yet */
#endif

      /* determine which load instruction to use from al and adval */

      switch (discrim ( dest.answhere ))
      {
      case insomereg:
	/* source instore, can choose dest reg */
	{
	  int *sr = someregalt(dest.answhere);

	  if (*sr != -1)
	  {
	    error(ERROR_SERIOUS, "move: somereg already set");
	  }
	  *sr = getreg(regs);
	  setregalt(dest.answhere, *sr);
	  /* and continue to next case */
	}

	/* FALLTHROUGH */

      case inreg:
	/* source and dest in fixpnt reg */
	{
	  int rd = regalt(dest.answhere);
	  if (rd != GR0 /* nowhere */ )
	  {
	    if (iss.adval)
	    {
	       /* generate address of source */
	       if (IS_FIXREG(iss.b.base))
		  ld_ins(i_lo,0,iss.b,rd);
	       else
		  set_ins("",iss.b, rd);
	    }
	    else
	    {
	      /* load source */
		 ld_ins(al==8 ? i_lb : (al==16 ? i_lh : i_lw),sgned,iss.b,rd);
	    }
	  };
	  return NOREG;
	}			/* end inreg dest */

      case infreg:
	/* source instore, dest in floating pnt reg */
	{
	  freg frd ;
	  frd = fregalt(dest.answhere);

	  assert(!iss.adval);	/* address should never go to float reg */
	  /* allow doubles not to be double aligned in mem, ie param */
	  if (frd.dble)
	  {
	    if ((iss.b.offset & 7) == 0)	/* double aligned in mem */
	    {
	       ldf_ins(i_fldd, iss.b,(3*frd.fr)+1);
	    }
	    else
	    {
	       /* not double aligned in mem, ie parameter */
	       ldf_ins(i_fldw, iss.b, 3*frd.fr);
	       iss.b.offset += 4;
	       ldf_ins(i_fldw, iss.b, (3*frd.fr)+2);
	    }
	  }
	  else
	  {
	    /* single */
	    ldf_ins(i_fldw, iss.b, 3*frd.fr);
	  }
	  return NOREG;
	}			/* end infreg dest */

#if USE_BITAD
      case bitad:
	/* source instore, dest bitadd should be coped with elsewhere */
	{
	  error(ERROR_SERIOUS, "mem to mem bit move");
	  /* NOTREACHED */
	}
#endif

      case notinreg:
	/* source and dest instore */
	{
	  int bits;
	  int bits_per_step;
	  int bytes_per_step;
	  int no_steps;
	  ins_p i_l=I_NIL, i_s=I_NIL;
	  instore isd;
	  bool unalign = al < 32;

	  /* we are limited by 32 bit regs */
	  bits_per_step = MIN_OF(al, 32);

	  bytes_per_step = bits_per_step / 8;

	  /*
	   * .ashsize gives precise size in bits, not as rounded up as if
	   * object is an array element. So we round up bits to convenient
	   * size, less than alignement.
	   */
	  bits = (dest.ashwhere.ashsize + bits_per_step - 1) & ~(bits_per_step - 1);

	  no_steps = (bits + bits_per_step - 1) / bits_per_step;

	  comment2("move: mem to mem dest.ashwhere.ashsize,ashalign=%d,%d",
		   dest.ashwhere.ashsize, dest.ashwhere.ashalign);
	  comment4("move: mem to mem bits=%d align=%d, bytes_per_step=%d no_steps=%d",
		   bits, al, bytes_per_step, no_steps);
	  if ((al % 8) != 0 || (bits % 8) != 0)
	  {
	    error(ERROR_SERIOUS, "move: bits mem to mem move");
	    return NOREG;
	  }

	  /*
	   * we are assuming the following, eg 8 bit object cannot have 32 bit
	   * alignment
	   */
	  assert((bits % al) == 0);

	  assert(bytes_per_step > 0 && bytes_per_step <= 4);
	  assert(no_steps > 0);
	  assert((no_steps * bytes_per_step) == (bits / 8));

	  if (bits_per_step==8)
	  {
	     i_l=i_lb;
	     i_s=i_sb;
	  }
	  else if (bits_per_step==16)
	  {
	     i_l=i_lh;
	     i_s=i_sh;
	  }
	  else if (bits_per_step==32)
	  {
	     i_l=i_lw;
	     i_s=i_sw;
	  }

	  /* +++ use fp reg for float, except not passed free fp regs */
	  /* +++ use lss/std where poss */

	  /*
	   * +++ use actual alignment which may be better than nominal
	   * alignment
	   */

	  isd = insalt(dest.answhere);

	  if (no_steps <= MAX_STEPS_INLINE_MOVE)
	  {
	    /* move in line */

	    if (no_steps == 1)
	    {
	      int r = getreg(regs);	/* register for holding values
					 * transferred */

	      if (iss.adval)
	      {
		/* generate address of source */
		if (IS_FIXREG(iss.b.base))
		{
		  if (iss.b.offset == 0)
		  {
		    comment("move: using adval base reg directly");
		    r = iss.b.base;
		  }
		  else
		     ld_ins(i_lo,0,iss.b,r);
		}
		else
		  set_ins("",iss.b, r);
	      }
	      else
	      {
		 /* load source */
		 ld_ins(i_l,0,iss.b,r);
	      }

	      if (!isd.adval)
	      {
		/* +++ move away from use below, but care for GR1 */
		comment("move: !adval dest, using GR1");
		ld_ins(i_lw,1,isd.b,GR1);
		isd.b.base = GR1;
		isd.b.offset = 0;
	      }

	      st_ins(i_s, r, isd.b);

	      return (unalign) ? NOREG : r;
	    }
	    else
	    {

	      /*
	       * Move using 2 regs ensuring load delay slot not occupied.
	       */
	      int ld_steps = no_steps;
	      int st_steps = no_steps;

	      int r1, r2;	/* regs used to copy object */

	      comment("move: inline move");

	      assert(ld_steps >= 2);

	      /* moves of addresses not handled by this long move */
	      assert(!iss.adval);

	      assert(bits_per_step <= 32);	/* only using byte regs */

	      r1 = getreg(regs);
	      regs |= RMASK(r1);

	      r2 = getreg(regs);
	      regs |= RMASK(r2);

	      if (!IS_FIXREG(iss.b.base))
	      {
		/* load source ptr in reg, note GR1 possibly in use for dest */

		int pr = getreg(regs);

		
regs |= RMASK(pr);

		comment("move: load ptr to source");

		set_ins("",iss.b, pr);
		iss.b.base = pr;
		iss.b.offset = 0;
	      }

	      if (!isd.adval)
	      {
		int pr = getreg(regs);

		regs |= RMASK(pr);

		comment("move: dest !adval");
		ld_ins(i_lw,1,isd.b,pr);
		isd.b.base = pr;
		isd.b.offset = 0;
	      }
	      else if (!IS_FIXREG(isd.b.base))
	      {
		int pr = getreg(regs);

		regs |= RMASK(pr);

		comment("move: load ptr to dest");

		set_ins("",isd.b, pr);
		isd.b.base = pr;
		isd.b.offset = 0;
	      }

	      /* first, pre-load both regs */
	      ld_ins(i_l,0,iss.b,r1);/* wfs 8/12/94 Changed sgned to 0 */ 
	      ld_steps--;               
	      iss.b.offset += bytes_per_step;

	      ld_ins(i_l,0,iss.b,r2);/* wfs 8/12/94 Changed sgned to 0 */ 
	      ld_steps--;
	      iss.b.offset += bytes_per_step;

	      /*
	       * now generate overlapping sequence with ld rX seperated from
	       * following st rX
	       *
	       *	st	r1
	       *	ld	r1
	       *	st	r2
	       *	ld	r2
	       *
	       * while there's still data
	       */
	      while (st_steps > 0)
	      {
		/* st r1 */
		st_ins(i_s,r1,isd.b);
		st_steps--;
		isd.b.offset += bytes_per_step;

		/* ld r1 */
		if (ld_steps > 0)
		{
		  ld_ins(i_l,0,iss.b,r1);/* wfs 8/12/94 Changed sgned to 0 */
		  ld_steps--;
		  iss.b.offset += bytes_per_step;
		}

		/* st r2 */
		if (st_steps > 0)
		{
		  st_ins(i_s,r2,isd.b);
		  st_steps--;
		  isd.b.offset += bytes_per_step;
		}

		/* ld r2 */
		if (ld_steps > 0)
		{
		  ld_ins(i_l,0,iss.b,r2);/* wfs 8/12/94 Changed sgned to 0 */
		  ld_steps--;
		  iss.b.offset += bytes_per_step;
		}
	      }

	      comment("move: end inline move");

	      assert(ld_steps == 0);

	      return NOREG;
	    }
	  }			/* inline end */
	  else
	  {

	    /*
	     * Copy with loop.
	     *
	     * Currently generate:
	     *
	     * !%srcptr and %destptr set mov	bytes,%cnt loop: subc
	     * %cnt,bytes_per_step,%cnt ldX	%tmp,[%srcptr+%cnt] stX
	     * %tmp,[%destptr+%cnt] bne	loop
	     *
	     * +++ unroll, and use two copy regs to seperate ld and st using same
	     * reg
	     */


	    int srcptr;
	    int destptr;
	    int count;
	    int copy_reg;
	    int loop = new_label();
	    int blocksz;

	    comment("move: loop move");

	    /* moves of addresses not handled by this long move */
	    assert(!iss.adval);

	    assert(bytes_per_step <= 4);	/* only using 1 word regs */

	    count = getreg(regs);
	    regs |= RMASK(count);

	    assert(!iss.adval);
	    iss.adval = 1;	/* we want address of value */
	    srcptr = addr_reg(iss, regs);
	    regs |= RMASK(srcptr);

	    destptr = addr_reg(isd, regs);
	    regs |= RMASK(destptr);

	    copy_reg = GR1;
	    blocksz = bytes_per_step*no_steps;
	    if (SIMM14(blocksz))
	    {
	       ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,blocksz,srcptr,count);
	       ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,blocksz,destptr,destptr);
	    }
	    else
	    {
	       imm_to_r(blocksz,GR1);
	       rrr_ins(i_add,c_,GR1,srcptr,count);
	       rrr_ins(i_add,c_,GR1,destptr,destptr);
	    }
	    outlab("L$$",loop);
	    if (bytes_per_step==1)
	    {
	       ld_ir_ins(i_ldbs,cmplt_MB,fs_,empty_ltrl,-1,count,copy_reg);
	       comb_ins(c_neq,count,srcptr,loop);
	       st_ir_ins(i_stbs,cmplt_MB,copy_reg,fs_,empty_ltrl,-1,destptr);
	    }
	    else if (bytes_per_step==2)
	    {
	       ld_ir_ins(i_ldhs,cmplt_MB,fs_,empty_ltrl,-2,count,copy_reg);
	       comb_ins(c_neq,count,srcptr,loop);
	       st_ir_ins(i_sths,cmplt_MB,copy_reg,fs_,empty_ltrl,-2,destptr);
	    }
	    else if (bytes_per_step==4)
	    {
	       ld_ir_ins(i_ldwm,cmplt_,fs_,empty_ltrl,-4,count,copy_reg);
	       comb_ins(c_neq,count,srcptr,loop);
	       st_ir_ins(i_stwm,cmplt_,copy_reg,fs_,empty_ltrl,-4,destptr);
	    }
	    return NOREG;
	  }			/* loop assign */
	}			/* end notinreg dest */
	default:{}
      }				/* end switch dest */
    }				/* end notinreg a */
    default:{}
  }				/* end switch a */

  error(ERROR_SERIOUS, "move not handled");
  return 0;  /* NOTREACHED */
}

