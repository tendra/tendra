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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/ops_float.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: ops_float.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.3  1997/11/09 14:04:53  ma
round_with_mode rewritten.

Revision 1.2  1997/10/29 10:22:24  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:56  ma
First version.

Revision 1.4  1997/10/13 08:49:44  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.3  1997/09/25 06:45:23  ma
All general_proc tests passed

Revision 1.2  1997/06/18 12:04:55  ma
Merged with Input Baseline changes.

 * Revision 1.3  1997/06/06  14:36:26  john
 * Fixed rounding modes
 *
 * Revision 1.2  1997/06/05  10:55:48  john
 * Fix to unsigned conversion
 *
 * Revision 1.1.1.1  1997/04/25  12:32:40  john
 *
 * Revision 1.2  1996/07/05  14:23:53  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:15  john
 *
 * Revision 1.2  93/03/03  14:48:21  14:48:21  ra (Robert Andrews)
 * Started adding support for error treatments.
 *
 * Revision 1.1  93/02/22  17:16:17  17:16:17  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "basicread.h"
#include "check.h"
#include "exp.h"
#include "expmacs.h"
#include "externs.h"
#include "install_fns.h"
#include "fbase.h"
#include "flpt.h"
#include "flpttypes.h"
#include "shapemacs.h"
#include "tags.h"
#include "mach.h"
#include "mach_ins.h"
#include "where.h"
#include "mach_op.h"
#include "instr.h"
#include "codex.h"
#include "instrs.h"
#include "coder.h"
#include "tests.h"
#include "operations.h"
#include "evaluate.h"
#include "utility.h"
#include "translate.h"
#include "ops_shared.h"

/*
    GIVE PROTOTYPE FOR MFW
*/

#if ( FBASE == 10 )
extern where mfw PROTO_S ( ( int, char *, int ) ) ;
#define FBASE_10
#else
extern where mfw PROTO_S ( ( int, long *, int ) ) ;
#undef FBASE_10
#endif

extern int need_dummy_double;
/************************************************************************
  Test for overflow.

  freg is a Freg which is moved to a dummy memory location to force the
  overflow (if any) before the test.
 ************************************************************************/

void test_float_overflow_reg
    PROTO_N ( ( freg, sz ) )
    PROTO_T ( where freg X long sz )
{
   if (have_overflow()) {
      ins2 ( insf ( sz, ml_fmove ), sz, sz, freg, dummy_double_dest, 1 ) ;
      test_overflow(ON_FP_OVERFLOW) ;
      need_dummy_double = 1 ;
   }
}

/************************************************************************
  Test for overflow.

  If dest is zero, freg is moved to a memory location to force the
  overflow (if any) before the test.
  ************************************************************************/

void test_float_overflow
    PROTO_N ( ( freg, dest, sz ) )
    PROTO_T ( where freg X where dest X long sz )
{
   if (have_overflow()) {
      if (eq_where(dest, zero)) {
         ins2 ( insf ( sz, ml_fmove ), sz, sz, freg, dummy_double_dest, 1 ) ;
         need_dummy_double = 1 ;
      }
      test_overflow(ON_FP_OVERFLOW) ;
   }
}


/*
    GENERAL PURPOSE FLOATING POINT ROUTINE

    The values a1 and a2 of shape sha have the binary floating-point
    operation indicated by the tag t applied to them and the result is
    stored in dest.
*/

void fl_binop
    PROTO_N ( ( t, sha, a1, a2, dest ) )
    PROTO_T ( int t X shape sha X where a1 X where a2 X where dest )
{
    int op, op1, op2 ;
    bool commutes = 0 ;
    int err = ON_FP_OVERFLOW ;
    long sz = shape_size ( sha ) ;

    switch ( t ) {
	case fplus_tag : {
	    commutes = 1 ;
	    op1 = insf ( sz, ml_fadd ) ;
	    op2 = m_faddx ;
	    break ;
	}
	case fminus_tag : {
	    op1 = insf ( sz, ml_fsub ) ;
	    op2 = m_fsubx ;
	    break ;
	}
	case fmult_tag : {
	    commutes = 1 ;
	    op1 = insf ( sz, ml_fmul ) ;
	    op2 = m_fmulx ;
	    break ;
	}
	case fdiv_tag : {
	    op1 = insf ( sz, ml_fdiv ) ;
	    op2 = m_fdivx ;
	    err = ON_FP_CARRY ;
	    break ;
	}
	default : {
	    error ( "Illegal floating operation" ) ;
	    return ;
	}
    }

    if ( whereis ( dest ) == Freg ) {
       if ( eq_where ( a1, dest ) ) {
          if ( commutes ) {
             op = ( whereis ( a2 ) == Freg ? op2 : op1 ) ;
             ins2 ( op, sz, sz, a2, dest, 1 ) ;
             if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
             test_float_overflow_reg(dest, sz) ;
          }
          else {
             move ( sha, a2, FP0 ) ;
             ins2 ( op2, sz, sz, a1, FP0, 1 ) ;
             if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
             move ( sha, FP0, dest ) ;
          }
       } else {
          move ( sha, a2, dest ) ;
          op = ( whereis ( a1 ) == Freg ? op2 : op1 ) ;
          ins2 ( op, sz, sz, a1, dest, 1 ) ;
          if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
          test_float_overflow_reg(dest, sz) ;
       }
    }
    else {
       move ( sha, a2, FP0 ) ;
       op = ( whereis ( a1 ) == Freg ? op2 : op1 ) ;
       ins2 ( op, sz, sz, a1, FP0, 1 ) ;
       if (t == fdiv_tag) test_overflow(ON_FP_OVERFLOW) ; /* divided by 0 ? */
       move ( sha, FP0, dest ) ;
       test_float_overflow(FP0, dest, sz) ;
    }
    have_cond = 0 ;
    return ;
}


/*
    NEGATE A FLOATING-POINT NUMBER

    The floating-point value a of shape sha is negated and stored in dest.
*/

void negate_float
    PROTO_N ( ( sha, a, dest ) )
    PROTO_T ( shape sha X where a X where dest )
{
   if ( whereis ( a ) == Freg ) {
      if ( whereis ( dest ) == Freg ) {
         ins2 ( m_fnegx, L64, L64, a, dest, 1 ) ;
         test_float_overflow_reg(dest, L64) ;
      } else {
         negate_float ( sha, a, FP0 ) ;
         move ( sha, FP0, dest ) ;
      }
   }
   else {
      move ( sha, a, FP0 ) ;
      negate_float ( sha, FP0, FP0 ) ;
      move ( sha, FP0, dest ) ;
      test_float_overflow(FP0, dest, shape_size(sha)) ;
   }
   have_cond = 0 ;
}


/*
    FIND THE ABSOLUTE VALUE OF A FLOATING-POINT NUMBER

    The floating-point value a of shape sha is has its absolute value
    stored in dest.
*/

void abs_float
    PROTO_N ( ( sha, a, dest ) )
    PROTO_T ( shape sha X where a X where dest )
{
    if ( whereis ( a ) == Freg ) {
	if ( whereis ( dest ) == Freg ) {
	    ins2 ( m_fabsx, L64, L64, a, dest, 1 ) ;
            test_float_overflow_reg(dest, L64) ;
	} else {
	    abs_float ( sha, a, FP0 ) ;
	    move ( sha, FP0, dest ) ;
	}
    } else {
	move ( sha, a, FP0 ) ;
	abs_float ( sha, FP0, FP0 ) ;
	move ( sha, FP0, dest ) ;
    }
    have_cond = 0 ;
}


/*
    CHANGE FLOATING VARIETY

    The floating-point value from is converted to a value of shape sha
    and stored in to.
*/

void change_flvar
    PROTO_N ( ( sha, from, to ) )
    PROTO_T ( shape sha X where from X where to )
{
    shape shf = sh ( from.wh_exp ) ;
    if ( whereis ( to ) == Freg ) {
	if ( whereis ( from ) == Freg ) {
	    move ( realsh, from, to ) ;
	    return ;
	}
	if ( shape_size ( shf ) > shape_size ( sha ) ) {
	    move ( shf, from, to ) ;
	    move ( sha, to, D0 ) ;
	    move ( sha, D0, to ) ;
	    return ;
	}
	move ( shf, from, to ) ;
	return ;
    }
    if ( whereis ( from ) == Freg ) {
	move ( sha, from, to ) ;
        test_float_overflow_reg(to, shape_size(sha)) ;
	return ;
    }
    move ( shf, from, FP0 ) ;
    move ( sha, FP0, to ) ;
    test_float_overflow(FP0, to, shape_size(sha)) ;
}


/*
    CURRENT ROUNDING MODE

    This gives the rounding mode for round_float.
*/

int crt_rmode = R2NEAR ;


/* Make floating point representing range_min(sha) - adjustment
Where Adjustment(adj) is 0,1,0.5 when adj is 0,1,2
*/

where get_min_limit
    PROTO_N ( ( sha, adj ) )
    PROTO_T ( shape sha X int adj )
{
   long fmd[4], min;

   if (name(sha)==ulonghd) {
      switch (adj) {
      case 0:
         /* res = 0 */
         fmd[0] = 0;
         fmd[1] = -1;
         return mfw(0,fmd,0);
      case 1:
         /* res = -1 */
         fmd[0] = 1;
         fmd[1] = -1;
         return mfw(-1,fmd,1);
      case 2:
         /* res = - 0.5 */
         fmd[0] = 0x8000;
         fmd[1] = -1;
         return mfw(-1,fmd,-1);
      }
   }
   if (name(sha)==slonghd) {
      switch (adj) {
      case 0:
         break ;
      case 1:
         /* res = - 2**31 - 1 */
         fmd[0] = 0x8000;
         fmd[1] = 0x0001;
         fmd[2] = -1;
         return mfw(-1,fmd,1);

      case 2:
         /* res = - 2**31 - 0.5 */
         fmd[0] = 0x8000;
         fmd[1] = 0x0000;
         fmd[2] = 0x8000;
         fmd[3] = -1;
         return mfw(-1,fmd,-1);
      }
   }

   min = range_min(sha) ;
   switch (adj) {
   case 0:
   case 1:
      /* min - (0|1) */
      min -= adj ;
      fmd[0] = (min>>16) & 0xffff;
      fmd[1] = min & 0xffff;
      fmd[2] = -1;
      return mfw((is_signed(sha)||adj)? -1 : 0,fmd,1);
   case 2:
      /* min - 0.5 */
      min -= 1 ;
      fmd[0] = (min>>16) & 0xffff;
      fmd[1] = min & 0xffff;
      fmd[2] = 0x8000;
      fmd[3] = -1;
      return mfw(-1,fmd,-1);
   }

   /* Shouldn't happen */
   fmd[0] = 0;
   fmd[1] = -1;
   return mfw(0,fmd,0);
}

/* Make floating point representing range_max(sha) + adjustment
Where Adjustment(adj) is 0,1,0.5 when adj is 0,1,2
*/

where get_max_limit
    PROTO_N ( ( sha, adj ) )
    PROTO_T ( shape sha X int adj )
{
   long fmd[6];
   long max = range_max(sha) ;
   if (name(sha)==ulonghd) {
      switch (adj) {
      case 0:
         /* max */
         fmd[0] = 0xffff;
         fmd[1] = 0xffff;
         fmd[2] = -1;
         return mfw(1,fmd,1);
      case 1:
         /* max + 1 */
         fmd[0] = 1;
         fmd[1] = 0;
         fmd[2] = 0;
         fmd[3] = -1;
         return mfw(1,fmd,2);
      case 2:
         /* max + 0.5 */
         fmd[0] = 1;
         fmd[1] = 0;
         fmd[2] = 0;
         fmd[3] = 0;
         fmd[4] = 0x8000;
         fmd[5] = -1;
         return mfw(1,fmd,-1);
      }
   }
   else {
      switch (adj) {
      case 0:
      case 1:
         /* max + (0|1) */
         max += adj ;
         fmd[0] = (max>>16) & 0xffff;
         fmd[1] = max & 0xffff;
         fmd[2] = -1;
         return mfw(1,fmd,1);
      case 2:
         /* max + 0.5 */
         fmd[0] = (max>>16) & 0xffff;
         fmd[1] = max & 0xffff;
         fmd[2] = 0x8000;
         fmd[3] = -1;
         return mfw(1,fmd,-1);
      }
   }

   /* Shouldn't happen */
   fmd[0] = 0xffff;
   fmd[1] = 0xffff;
   fmd[2] = -1;
   return mfw(1,fmd,1);
}

/* Test number against limit */
void check_limit
    PROTO_N ( ( number, limit, tst ) )
    PROTO_T ( where number X where limit X int tst )
{
   int sw, instr ;
   move(realsh,limit,FP1);
   sw = cmp(realsh,number,FP1,tst);
   instr = branch_ins(tst,sw,1,1);
   test_overflow2(instr);
}

/*
  Check that the floating point value in 'from' will, when rounded, fall
  within the range of the integer variety given by 'sha'.
*/
static void check_float_round_overflow
    PROTO_N ( (sha,from,mode) )
    PROTO_T ( shape sha X where from X int mode )
{
  if (overflow_jump == -1) {
     make_comment("error_teatment is trap");
     return;
  }

  make_comment("check_float_round_overflow ...");

  /* Setup min and max limits & decide tests */
  switch (mode) {
  case R2PINF:
     make_comment(" (toward larger) min-1 < x <= max");
     /* error if x <= min-1 or x > max */
     check_limit(from, get_min_limit(sha,1),tst_le) ;
     check_limit(from, get_max_limit(sha,0),tst_gr) ;
     break;
  case R2NINF:
     make_comment(" (toward smaller) min <= x < max+1");
     /* error if x < min or x >= max+1 */
     check_limit(from, get_min_limit(sha,0),tst_ls) ;
     check_limit(from, get_max_limit(sha,1),tst_ge) ;
     break;
  case R2ZERO:
     make_comment(" (toward zero) min-1 < x < max+1")  ;
     /* error if x <= min-1 or x >= max+1 */
     check_limit(from, get_min_limit(sha,1),tst_le) ;
     check_limit(from, get_max_limit(sha,1),tst_ge) ;
     break;
  case R2NEAR:
     make_comment(" (to nearest) min-0.5 <= x < max+0.5");
     /* error if x < min-0.5 or x >= max+0.5 */
     check_limit(from, get_min_limit(sha,2),tst_le) ;
     check_limit(from, get_max_limit(sha,2),tst_gr) ;
     break;
  case 4:
     make_comment(" (internal mode) min <= x <= max");
     /* error if x < min or x > max */
     check_limit(from, get_min_limit(sha,0),tst_ls) ;
     check_limit(from, get_max_limit(sha,0),tst_gr) ;
     break;
  default:
     error("check_float_round_overflow: wrong rounding mode");
  }

  make_comment("check_float_round_overflow done");
}


/*
   SET_ROUND_MODE

   Changes the default floating point rounding mode.
   Set bits 4 & 5 of fpcr (floating point control register)
   according to rounding mode.

   The global flag changed_round_mode is set to TRUE.
*/

bool changed_round_mode = 0 ;

void set_round_mode
    PROTO_N ( (mode) )
    PROTO_T ( int mode )
{
/*
   if (mode == f_to_nearest && ! changed_round_mode ) return ;
*/
   changed_round_mode = 1 ;

   ins2(m_fmovel,32,32,RW[REG_FPCR],D0,1);

   switch(mode){
   case R2NEAR:
      make_comment("round mode to nearest");
      /* to nearest => bit 4 = 0, bit 5 = 0 */
      ins2n(m_bclr,4,32,D0,1);
      ins2n(m_bclr,5,32,D0,1);
      break;
   case R2PINF:
      make_comment("round mode to larger");
      /* to + INF  => bit 4 =1, bit5 = 1 */
      ins2n(m_bset,4,32,D0,1);
      ins2n(m_bset,5,32,D0,1);
      break;
   case R2NINF:
      make_comment("round mode to smaller");
      /* to - INF => bit 4 = 0, bit 5 = 1 */
      ins2n(m_bclr,4,32,D0,1);
      ins2n(m_bset,5,32,D0,1);
      break;
   case R2ZERO:
      make_comment("round mode to zero");
      /* to zero => bit 4 = 1, bit 5 = 0
         This should never occur, as fintrz is always used
         for round to zero */
      ins2n(m_bset,4,32,D0,1);
      ins2n(m_bclr,5,32,D0,1);
      break;
   default:
      error("wrong rounding mode");
   }
   ins2(m_fmovel,32,32,D0,RW[REG_FPCR],1);
}

void reset_round_mode
    PROTO_Z ()
{
   if ( changed_round_mode ) {
      set_round_mode ( f_to_nearest ) ;
      changed_round_mode = 0;
   }
}


/*
    ROUND A FLOATING POINT NUMBER TO AN INTEGER

    The floating-point value from is rounded to an integer value of shape
    sha and stored in to.  The rounding mode is given by crt_rmode.
*/

void round_float
    PROTO_N ( ( sha, from, to ) )
    PROTO_T ( shape sha X where from X where to )
{
    where fr ;
    where dest ;
    int mode = crt_rmode ;

    if ( name ( sha ) == ulonghd ) {
        if(have_overflow()) {
            /* This must be checked before a round operation is attempted
               because out-of-range values can cause an exception */
            check_float_round_overflow(sha,from,mode);
        }

	if ( mode == f_toward_zero|| mode == 4 ) {

#ifdef float_to_unsigned
	    change_flvar ( realsh, from, FP0 ) ;
	    push_float ( L64, FP0 ) ;
#ifdef float_to_unsigned_uses_fp1
	    if ( mode == 4 && eq_where ( from, FP1 ) {
		push_float ( L64, FP1 ) ;
		libcall ( float_to_unsigned ) ;
		pop_float ( L64, FP1 ) ;
	    } else
#endif
	    libcall ( float_to_unsigned ) ;
	    dec_stack ( -64 ) ;
	    have_cond = 0 ;
	    move ( ulongsh, D0, to ) ;
#else
	    where fm ;
	    long lab1 = next_lab () ;
	    long lab2 = next_lab () ;
	    exp jt = simple_exp ( 0 ) ;
	    ptno ( jt ) = lab1 ;
	    regsinproc |= regmsk ( REG_FP1 ) ;
#ifdef FBASE_10
	    fm = mfw ( 1, "2147483648", 9 ) ;
#else
	    {
		static long fmd [] = { 32768, 0, -1 } ;
		fm = mfw ( 1, fmd, 1 ) ;
	    }
#endif
	    change_flvar ( realsh, from, FP0 ) ;
	    move ( realsh, fm, FP1 ) ;
	    regsinproc |= regmsk ( REG_FP1 ) ;
	    ins2_cmp ( m_fcmpx, L64, L64, FP0, FP1, 0 ) ;
	    branch ( tst_gr, jt, 1, 1, 1 ) ;
	    ins2 ( m_fsubx, L64, L64, FP1, FP0, regmsk ( REG_FP0 ) ) ;
	    if ( whereis ( to ) == Dreg ) {
	      ins2 (m_fintrzx,L32,L32,FP0,FP0,1);
	      ins2 ( m_fmovel, L32, L32, FP0, to, 1 ) ;
	      or ( ulongsh, to, mnw ( (long)2147483648UL ), to ) ;
	    } else {
	       ins2 (m_fintrzx,L32,L32,FP0,FP0,1);
	       ins2 ( m_fmovel, L32, L32, FP0, D0, 1 ) ;
	       or ( ulongsh, D0, mnw ( (long)2147483648UL ), D0 ) ;
	       move ( ulongsh, D0, to ) ;
	    }
	    make_jump ( m_bra, lab2 ) ;
	    make_label ( lab1 ) ;
	    if ( whereis ( to ) == Dreg ) {
	      ins2 (m_fintrzx,L32,L32,FP0,FP0,1);
	      ins2 ( m_fmovel, L32, L32, FP0, to, 1 ) ;
	    } else {
	      ins2 (m_fintrzx,L32,L32,FP0,FP0,1);
	      ins2 ( m_fmovel, L32, L32, FP0, D0, 1 ) ;
	      move ( ulongsh, D0, to ) ;
	    }
	    make_label ( lab2 ) ;
	    have_cond = 0 ;
#endif
	    return ;
	}

    } else {


	if ( mode == 4 ) {
	    /* Special case - move FP0 into the register to */
	    ins2 ( m_fmovel, L32, L32, FP0, to, 1 ) ;

            /* This might generate operand error */
            test_overflow(ON_FP_OPERAND_ERROR);

	    have_cond = 0 ;
	    change_var_sh ( sha, slongsh, to, to ) ;
	    return ;
	}

	if(have_overflow()) {
	  /* This must be checked before a round operation is attempted
	     because out-of-range values can cause an exception */
	  check_float_round_overflow(sha,from,mode);
	}

	if ( mode == f_toward_zero || mode == f_to_nearest ) {
	    /* Rounding to nearest or towards zero are easy */
	    int instr ;
	    shape shf = sh ( from.wh_exp ) ;
	    long szf = shape_size ( shf ) ;
	    if ( mode == f_toward_zero ) {
		instr = m_fintrzx ;
		if ( whereis ( from ) != Freg ) {
		    instr = insf ( szf, ml_fint ) ;
		}
	    } else {
                set_round_mode(mode);
		instr = m_fintx ;
		if ( whereis ( from ) != Freg ) {
		    instr = insf ( szf, ml_fintrz ) ;
		}
	    }
	    ins2 ( instr, szf, szf, from, FP0, 1 ) ;
	    if ( whereis ( to ) == Dreg ) {
		dest = to ;
	    } else {
		dest = D0 ;
	    }
	    ins2 ( m_fmovel, L32, L32, FP0, dest, 1 ) ;
	    have_cond = 0 ;
	    change_var_sh ( sha, slongsh, dest, to ) ;
	    return ;
	}
    }

    /* Other modes : firstly find some registers */
    if ( whereis ( to ) == Dreg ) {
	dest = to ;
    } else {
	dest = D0 ;
    }
    if ( whereis ( from ) == Freg && !eq_where ( from, FP0 ) ) {
	fr = from ;
    } else {
	shape shf = sh ( from.wh_exp ) ;
	fr = FP1 ;
	regsinproc |= regmsk ( REG_FP1 ) ;
	move ( shf, from, fr ) ;
    }

    /* Round fr into FP0 */
    if ( mode == f_toward_zero ) {
       ins2 ( m_fintrzx, 64, 64, fr, FP0, 1 ) ;
    }
    else {
       set_round_mode(mode);
       ins2 ( m_fintx, 64, 64, fr, FP0, 1 ) ;
    }

    /* Move FP0 into dest */
    crt_rmode = 4 ;
    round_float ( sha, FP0, dest ) ;
    crt_rmode = mode ;

    /* Move result into place */
    have_cond = 0 ;
    move ( sha, dest, to ) ;
    return ;
}


/*
    CONVERT AN INTEGER TO A FLOATING POINT NUMBER

    The integer value from is converted to a floating-point value of
    shape sha and stored in to.  Unsigned longs are difficult.  Error
    treatments are ignored (they cannot occur at present).
*/

void int_to_float
    PROTO_N ( ( sha, from, to ) )
    PROTO_T ( shape sha X where from X where to )
{
    where fpr ;
    shape shf = sh ( from.wh_exp ) ;
#ifdef REJECT
    fpr = ( whereis ( to ) == Freg ? to : FP0 ) ;
#else
    fpr = FP0 ;
#endif
    if ( name ( shf ) == ulonghd ) {
#ifdef unsigned_to_float
	if ( whereis ( from ) == Dreg ) {
	    push ( slongsh, L32, from ) ;
	} else {
	    move ( shf, from, D0 ) ;
	    push ( slongsh, L32, D0 ) ;
	}
	libcall ( unsigned_to_float ) ;
	dec_stack ( -32 ) ;
	have_cond = 0 ;
	move ( realsh, D0_D1, fpr ) ;
	move ( sha, fpr, to ) ;
	return ;
#else
	where fm ;
	long lab = next_lab () ;
	exp jt = simple_exp ( 0 ) ;
	ptno ( jt ) = lab ;
#ifdef FBASE_10
	fm = mfw ( 1, "4294967296", 9 ) ;
#else
	{
	    static long fmd [] = { 1, 0, 0, -1 } ;
	    fm = mfw ( 1, fmd, 2 ) ;
	}
#endif
	if ( whereis ( from ) == Dreg ) {
	    ins2 ( m_fmovel, L32, L64, from, fpr, 1 ) ;
	} else {
	    move ( slongsh, from, D0 ) ;
	    ins2 ( m_fmovel, L32, L64, D0, fpr, 1 ) ;
	}
	branch ( tst_ge, jt, 1, 1, 1 ) ;
	add ( sha, fpr, fm, fpr ) ;
	make_label ( lab ) ;
	have_cond = 0 ;
	move ( sha, fpr, to ) ;
	return ;
#endif
    }
    if ( name ( shf ) == slonghd && whereis ( from ) == Dreg ) {
	ins2 ( m_fmovel, L32, L64, from, fpr, 1 ) ;
    } else {
	change_var_sh ( slongsh, shf, from, D0 ) ;
	ins2 ( m_fmovel, L32, L64, D0, fpr, 1 ) ;
    }
    move ( sha, fpr, to ) ;
    have_cond = 0 ;
    return ;
}
