/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  The procedure move produces code to move a value from a to the
  destination dest.  This takes the form of a switch test on the
  parameter a (type ans) which is either a reg, freg instore or
  bitad value.  In each of the three cases the ans field of the
  dest is similarly dealt with to determine the necessary
  instructions for the move.  Sizes and alignment are taken from
  the ash field of the destination.  The routine returns the
  register used if a single word destination is instore, and
  NOREG otherwise.
*/

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include <utility/max.h>

#include <main/flags.h>

#include "sparcins.h"
#include "inst_fmt.h"
#include "addrtypes.h"
#include "procrec.h"
#include "proc.h"
#include "getregs.h"
#include "labels.h"
#include "bitsmacs.h"
#include "reg.h"
#include "make_code.h"
#include "move.h"


/*
  MAXIMUM SIZE FOR INLINED MOVES
*/

#define MAX_STEPS_INLINE_MOVE	12


/*
  BITMASK : NBITMASK ( n ) GIVES n 1'S
*/

#define NBITMASK( n )  ((unsigned long)((n)==32 ?~0L:((1<<(n))-1)))


/*
  TYPE REPRESENTING INSTRUCTION PAIRS
  Unsigned version, signed version.
*/

typedef ins_p ins_sgn_pair [2] ;


/*
  ARRAY OF LOAD INSTRUCTIONS
*/

static const ins_sgn_pair ld_ins_sz [] = {
  { I_NIL, I_NIL },
  { i_ldub, i_ldsb },
  { i_lduh, i_ldsh },
  { I_NIL, I_NIL },
  { i_ld, i_ld },
  { I_NIL, I_NIL },
  { I_NIL, I_NIL },
  { I_NIL, I_NIL },
  { i_ldd, i_ldd }
} ;


/*
  ARRAY OF STORE INSTRUCTIONS
*/

static const ins_sgn_pair st_ins_sz [] = {
  { I_NIL, I_NIL },
  { i_stb, i_stb },
  { i_sth, i_sth },
  { I_NIL, I_NIL },
  { i_st, i_st },
  { I_NIL, I_NIL },
  { I_NIL, I_NIL },
  { I_NIL, I_NIL },
  { i_std, i_std }
} ;


/*
  FIND THE LOAD INSTRUCTION FOR SIZE bits, SIGNEDNESS sgned
*/

ins_p 
i_ld_sz ( int bits, int sgned ){
  return ld_ins_sz [ bits / 8 ] [ sgned ] ;
}


/*
  FIND THE STORE INSTRUCTION FOR SIZE bits (UNSIGNED)
*/

ins_p 
i_st_sz ( int bits ){
  return st_ins_sz [ bits / 8 ] [0] ;
}


/*
  LOAD THE ADDRESS REPRESENTED BY is INTO reg
*/

static void 
ld_addr ( instore is, int reg ){
  if ( is.adval ) {
    if ( IS_FIXREG ( is.b.base ) ) {
      rir_ins ( i_add, is.b.base, is.b.offset, reg ) ;
    } else {
      set_ins ( is.b, reg ) ;
    }
  } else {
    ld_ins ( i_ld, is.b, reg ) ;
  }
}


/*
  LOAD THE ADDRESS REPRESENTED BY is INTO A REGISTER
  The register number is returned.  regs gives the registers to 
  choose from.
*/
static int 
addr_reg ( instore is, long regs ){
  int r ;
  if ( is.adval && IS_FIXREG ( is.b.base ) && is.b.offset == 0 ) {
    return is.b.base ;
  }
  r = getreg ( regs ) ;
  ld_addr ( is, r ) ;
  return r;
}


/*
  MOVE a INTO dest
  regs gives the free registers, sgned gives the signedness.
*/

int move 
    ( ans a, where dest, long regs, bool sgned ){
  int al = ( int ) dest.ashwhere.ashalign ;
  if ( dest.ashwhere.ashsize == 0 ) return NOREG;

  if ( PIC_code && discrim ( dest.answhere ) == notinreg ) {
    instore iss;
    iss = insalt ( dest.answhere ) ;
    if ( !IS_FIXREG (iss.b.base) && !SIMM13_SIZE (iss.b.offset) ) {
	/* global with large offset: we have to avoid double use of R_TMP */
      int ofs = iss.b.offset ;
      int r = getreg ( regs ) ;
      regs |= RMASK ( r ) ;
      iss.b.offset = 0;
      set_ins ( iss.b, r ) ;
      iss.b.offset = ofs;
      iss.b.base = r;
      setinsalt ( dest.answhere, iss ) ;
    }
  }

  start : switch ( discrim ( a ) ) {

  case insomereg :
  case insomefreg : {
    /* Source is in some register */
    error(ERR_SERIOUS,  "move : source register not specified" ) ;
    return NOREG;
  }
  case inreg : {
    /* Source in fixed point register */
    int r = regalt ( a ) ;

    switch ( discrim ( dest.answhere ) ) {

    case inreg : {
      /* Register to register move */
      int rd = regalt ( dest.answhere ) ;
      if ( rd != R_G0 && rd != r ) {
	rr_ins ( i_mov, r, rd ) ;
      }
      return NOREG;
    }

    case insomereg : {
      /* Register to some register move */
      int *sr = someregalt ( dest.answhere ) ;
      if ( *sr != -1 ) error(ERR_SERIOUS,  "Illegal register" ) ;
      *sr = r ;
      return NOREG;
    }

    case infreg : {
      /* Register to floating register move */
      freg fr ;
      fr = fregalt ( dest.answhere ) ;
      st_ro_ins ( i_st, r, mem_temp ( 0 ) ) ;
      ldf_ro_ins ( i_ld, mem_temp ( 0 ), fr.fr << 1 ) ;
      if ( fr.dble ) {
	st_ro_ins ( i_st, r + 1, mem_temp ( 4 ) ) ;
	ldf_ro_ins ( i_ld, mem_temp ( 4 ),
		     ( fr.fr << 1 ) + 1 ) ;
      }
      return NOREG;
    }

    case notinreg : {
      /* Register to store move */
      instore is ;
      ins_p st = i_st_sz ( al ) ;

      if ( al == 1 ) {
	st = i_st_sz ( ( int ) dest.ashwhere.ashsize ) ;
      } else {
	/*assert ( al == dest.ashwhere.ashsize ) ;*/
	st = i_st_sz ( al ) ;
      }

      is = insalt ( dest.answhere ) ;
      if ( is.adval ) {
	st_ins ( st, r, is.b ) ;
      } else {
	baseoff b ;
	b.base = R_TMP ;
	b.offset = 0 ;
	ld_ins ( i_ld, is.b, b.base ) ;
	st_ins ( st, r, b ) ;
      }
      return r;
    }
    default:
      error(ERR_SERIOUS, "fixed -> wrong dest");
    }
    UNREACHED;
  }
  case infreg : {
    /* Source in floating point register */
    freg fr ;
    fr = fregalt ( a ) ;

    switch ( discrim ( dest.answhere ) ) {
    case inreg : {
      /* Floating register to register move */
      int rd = regalt ( dest.answhere ) ;

      if ( rd != 0 ) {
	/* store and load to move to fixed reg */
	stf_ins ( i_st, fr.fr<<1, mem_temp ( 0 ) ) ;
	ld_ro_ins ( i_ld, mem_temp ( 0 ), rd ) ;
	if ( fr.dble ) {
	  stf_ins ( i_st, ( fr.fr << 1 ) + 1,
		    mem_temp ( 4 ) ) ;
	  ld_ro_ins ( i_ld, mem_temp ( 4 ), rd + 1 ) ;
	}
      }
      return NOREG;
    }
    case insomereg : {
      /* Floating register to some register move */
      int *sr = someregalt ( dest.answhere ) ;
      if ( *sr != -1 ) error(ERR_SERIOUS,  "Illegal register" ) ;
      *sr = getreg ( regs ) ;
      regs |= RMASK ( *sr ) ;
      setregalt ( dest.answhere, *sr ) ;
      goto start ;
    }
    case infreg : {
      /* Floating register to floating register move */
      freg frd ;
      frd = fregalt ( dest.answhere ) ;

      if ( fr.fr != frd.fr ) {
	rrf_ins ( i_fmovs, fr.fr << 1, frd.fr << 1 ) ;
	if ( frd.dble ) {
	  rrf_ins ( i_fmovs, ( fr.fr << 1 ) + 1,
		    ( frd.fr << 1 ) + 1 ) ;
	}
      }
      return NOREG;
    }
    case notinreg : {
      /* Floating register to store move */
      instore is ;
      ins_p st = ( fr.dble ? i_std : i_st ) ;

      if ( ( dest.ashwhere.ashsize == 64 && !fr.dble ) ||
	   ( dest.ashwhere.ashsize == 32 && fr.dble ) ) {
	error(ERR_SERIOUS,  "Inconsistent sizes in move" ) ;
      }

      is = insalt ( dest.answhere ) ;
      if ( is.adval ) {
	if ( fr.dble ) {
	  if (( ( is.b.offset & 7 ) == 0 ) && 
		((is.b.base == R_FP) || (is.b.base == R_SP))) {
	    /* double aligned */
	    stf_ins ( i_std, fr.fr << 1, is.b ) ;
	  } else {
				/* not double aligned */
	    stf_ins ( i_st, fr.fr << 1, is.b ) ;
	    is.b.offset += 4 ;
	    stf_ins ( i_st, ( fr.fr << 1 ) + 1, is.b ) ;
	  }
	} else {
	  stf_ins ( i_st, fr.fr << 1, is.b ) ;
	}
      } else {
	baseoff b ;
	b.base = getreg ( regs ) ;
	b.offset = 0 ;
	ld_ins ( i_ld, is.b, b.base ) ;
	stf_ro_ins ( st, fr.fr << 1, b ) ;
      }

      return fr.dble ? -( fr.fr + 32 ) : ( fr.fr + 32 ) ;
    }
    default:
      error(ERR_SERIOUS, "Float to wrong dest");
    }
    UNREACHED;
  }
  case notinreg : {
    /* Source in store */
    instore iss ;
    int size = dest.ashwhere.ashsize;
    iss = insalt ( a ) ;

    if ( PIC_code && !IS_FIXREG (iss.b.base) && !SIMM13_SIZE (iss.b.offset) ) {
	/* global with large offset: we have to avoid double use of R_TMP */
      int ofs = iss.b.offset ;
      int r = getreg ( regs ) ;
      regs |= RMASK ( r ) ;
      iss.b.offset = 0;
      set_ins ( iss.b, r ) ;
      iss.b.offset = ofs;
      iss.b.base = r;
    }
	    
    if ( iss.adval && iss.b.offset == 0 && IS_FIXREG ( iss.b.base ) ) {
      /* address of [ base_reg + 0 ] is base_reg */
      setregalt ( a, iss.b.base ) ;
      goto start ;
    }
    if (al == 1){
      al = (size<=8)?9: ((size<=16)?16:32);
    }
    if ( al == 64 ) al = 32 ;

    /* determine which load instruction to use from al and adval */
    switch ( discrim ( dest.answhere ) ) {
    case insomereg : {
      /* Move store to some register */
      int *sr = someregalt ( dest.answhere ) ;
      if ( *sr != -1 ) error(ERR_SERIOUS,  "Illegal register" ) ;
      *sr = getreg ( regs ) ;
      regs |= RMASK ( *sr ) ;
      setregalt ( dest.answhere, *sr ) ;
	  FALL_THROUGH;
    }
    case inreg : {
      /* Move store to register */
      int rd = regalt ( dest.answhere ) ;
      if ( rd != R_G0 ) {
	if ( iss.adval ) {
	  /* generate address of source */
	  if ( IS_FIXREG ( iss.b.base ) ) {
	    rir_ins ( i_add, iss.b.base,
		      iss.b.offset, rd ) ;
	  } else {
	    set_ins ( iss.b, rd ) ;
	  }
	} else {
	  /* load source */
	  ld_ins ( i_ld_sz ( al, sgned ), iss.b, rd ) ;
	}
      }
      return NOREG;
    }
    case infreg : {
      /* Move store to floating register */
      freg frd ;
      frd = fregalt ( dest.answhere ) ;
      assert ( !iss.adval ) ;
      if ( frd.dble ) {
	/* double precision */
	if (( ( iss.b.offset & 7 ) == 0 ) && ( iss.b.offset != -8 ) && 
		((iss.b.base == R_FP) || (iss.b.base == R_SP))) {
	  /* source is double aligned */
	  ldf_ins ( i_ldd, iss.b, frd.fr << 1 ) ;
	} else {
	  /* source is not double aligned */
	  ldf_ins ( i_ld, iss.b, frd.fr << 1 ) ;
	  iss.b.offset += 4 ;
	  ldf_ins ( i_ld, iss.b, ( frd.fr << 1 ) + 1 ) ;
	}
      } else {
	/* single precision */
	ldf_ins ( i_ld, iss.b, frd.fr << 1 ) ;
      }
      return NOREG;
    }
    case notinreg : {
      /* Move store to store address */
      int bits ;
      int no_steps ;
      int bits_per_step ;
      int bytes_per_step ;
      instore isd ;
      ins_p st, ld ;
      bool unalign = ( bool ) ( al < 32 ) ;

      /* we are limited by 32 bit regs */
      bits_per_step = MIN ( al, 32 ) ;
      bytes_per_step = bits_per_step / 8 ;

      /* round up number of bits to be moved */
      bits = ( int ) ( ( dest.ashwhere.ashsize +
			 bits_per_step - 1 ) &
		       ~( bits_per_step - 1 ) ) ;

      no_steps = ( bits + bits_per_step - 1 ) / bits_per_step ;

      if ( ( al % 8 ) != 0 || ( bits % 8 ) != 0 ) {
	error(ERR_SERIOUS,  "move : misaligned store" ) ;
	return NOREG;
      }
      assert ( ( bits % al ) == 0 ) ;
      assert ( bytes_per_step > 0 && bytes_per_step <= 4 ) ;
      assert ( no_steps > 0 ) ;
      assert ( ( no_steps * bytes_per_step ) == ( bits / 8 ) ) ;

      ld = i_ld_sz ( bits_per_step, sgned ) ;
      st = i_st_sz ( bits_per_step ) ;

      isd = insalt ( dest.answhere ) ;
      if ( no_steps <= MAX_STEPS_INLINE_MOVE ) {
	/* expand to a number of loads and stores */
	if ( no_steps == 1 ) {
	  /* move can be done in one step */
	  int r = getreg ( regs ) ;
	  regs |= RMASK ( r ) ;
	  if ( iss.adval ) {
				/* generate address of source */
	    if ( IS_FIXREG ( iss.b.base ) ) {
	      if ( iss.b.offset == 0 ) {
		r = iss.b.base ;
	      } else {
		rir_ins ( i_add, iss.b.base,
			  iss.b.offset, r ) ;
	      }
	    } else {
	      set_ins ( iss.b, r ) ;
	    }
	  } else {
				/* load source */
	    ld_ins ( ld, iss.b, r ) ;
	  }

	  if ( !isd.adval ) {
	    ld_ins ( i_ld, isd.b, R_TMP ) ;
	    isd.b.base = R_TMP ;
	    isd.b.offset = 0 ;
	  }
	  st_ins ( st, r, isd.b ) ;
	  return unalign ? NOREG : r ;
	} else {
	  /* use two registers, ensuring load delay
	     slot is not occupied */
	  int r1, r2 ;
	  int ld_steps = no_steps ;
	  int st_steps = no_steps ;

	  assert ( ld_steps >= 2 ) ;
	  /*assert ( !iss.adval ) ;*/
	  assert ( bits_per_step <= 32 ) ;

	  /* find the registers to be used */
	  r1 = getreg ( regs ) ;
	  regs |= RMASK ( r1 ) ;
	  r2 = getreg ( regs ) ;
	  regs |= RMASK ( r2 ) ;

	  if ( !IS_FIXREG ( iss.b.base ) ) {
				/* load source ptr in reg */
	    int pr = getreg ( regs ) ;
	    regs |= RMASK ( pr ) ;
	    set_ins ( iss.b, pr ) ;
	    iss.b.base = pr ;
	    iss.b.offset = 0 ;
	  }

	  if ( !isd.adval ) {
	    int pr = getreg ( regs ) ;
	    regs |= RMASK ( pr ) ;
	    ld_ins ( i_ld, isd.b, pr ) ;
	    isd.b.base = pr ;
	    isd.b.offset = 0 ;
	  } else if ( !IS_FIXREG ( isd.b.base ) ) {
	    int pr = getreg ( regs ) ;
	    regs |= RMASK ( pr ) ;
	    set_ins ( isd.b, pr ) ;
	    isd.b.base = pr ;
	    isd.b.offset = 0 ;
	  }

	  /* first pre-load both registers */
	  ld_ro_ins ( ld, iss.b, r1 ) ;
	  ld_steps-- ;
	  iss.b.offset += bytes_per_step ;

	  ld_ro_ins ( ld, iss.b, r2 ) ;
	  ld_steps-- ;
	  iss.b.offset += bytes_per_step ;

	  /* now generate a sequence of instructions
	     of the form :

	     st r1
	     ld r1
	     st r2
	     ld r2
	     */
	  while ( st_steps > 0 ) {
				/* st r1 */
	    st_ro_ins ( st, r1, isd.b ) ;
	    st_steps-- ;
	    isd.b.offset += bytes_per_step ;

				/* ld r1 */
	    if ( ld_steps > 0 ) {
	      ld_ro_ins ( ld, iss.b, r1 ) ;
	      ld_steps-- ;
	      iss.b.offset += bytes_per_step ;
	    }

				/* st r2 */
	    if ( st_steps > 0 ) {
	      st_ro_ins ( st, r2, isd.b ) ;
	      st_steps-- ;
	      isd.b.offset += bytes_per_step ;
	    }

				/* ld r2 */
	    if ( ld_steps > 0 ) {
	      ld_ro_ins ( ld, iss.b, r2 ) ;
	      ld_steps-- ;
	      iss.b.offset += bytes_per_step ;
	    }
	  }
	  assert ( ld_steps == 0 ) ;
	  return NOREG;
	}
      } else {
	/* large number of steps - use a loop */
	int cnt_reg ;
	int copy_reg ;
	int srcptr_reg ;
	int destptr_reg ;
	int loop = new_label () ;

	assert ( !iss.adval ) ;
	assert ( bytes_per_step <= 4 ) ;

	/* find control register */
	cnt_reg = getreg ( regs ) ;
	regs |= RMASK ( cnt_reg ) ;

	/* find source register */
	assert ( !iss.adval ) ;
	iss.adval = 1 ;
	srcptr_reg = addr_reg ( iss, regs ) ;
	regs |= RMASK ( srcptr_reg ) ;

	/* find destination register */
	destptr_reg = addr_reg ( isd, regs ) ;
	regs |= RMASK ( destptr_reg ) ;

	/* find copy register */
	copy_reg = R_TMP ;

	/* main loop */
	ir_ins ( i_mov, ( long ) ( bytes_per_step * no_steps ),
		 cnt_reg ) ;
	set_label ( loop ) ;
	rir_ins ( i_subcc, cnt_reg, ( long ) bytes_per_step,
		  cnt_reg ) ;
	ld_rr_ins ( ld, srcptr_reg, cnt_reg, copy_reg ) ;
	st_rr_ins ( st, copy_reg, destptr_reg, cnt_reg ) ;
	br_ins ( i_bne, loop ) ;
	return NOREG;
      }
    }
    default:
    {
      /* fall through to fail */
    }
    }
  }
  }
  error(ERR_SERIOUS,  "Illegal move" ) ;
  return NOREG;
}

