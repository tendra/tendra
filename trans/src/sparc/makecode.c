/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/szs_als.h>
#include <local/ash.h>
#include <local/out.h>

#ifdef NEWDWARF
#include <local/dw2_config.h>
#endif

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/exp.h>
#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/tags.h>
#include <construct/installtypes.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/install_fns.h>
#include <construct/flpt.h>
#include <construct/f64.h>

#include <main/driver.h>
#include <main/flags.h>

#include "addrtypes.h"
#include "extra_tags.h"
#include "maxminmacs.h"
#include "proctypes.h"
#include "eval.h"
#include "move.h"
#include "oprators.h"
#include "comment.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "sparcins.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "regmacs.h"
#include "regable.h"
#include "muldvrem.h"
#include "proc.h"
#include "special.h"
#include "diag_out.h"
#include "translate.h"
#include "makecode.h"
#include "new_tags.h"
#include "localexpmacs.h"

#ifdef NEWDIAGS
#include <newdiag/dg_aux.h>
#include <newdiag/dg_globs.h>
#endif

#ifdef NEWDWARF
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_basic.h>
#endif

#include "local_reform.h"


/* 
  Check for parameter access via add_to_ptr ( env, off ) 
*/
#define param_aligned(off) (al1_of(sh(off))->al.al_val.al_frame & 6)


/*
  THE NIL WHERE
*/
where nowhere ;


/*
  CHECK FOR NOT-A-NUMBER
*/
void 
checknan ( exp e, int fr )
{
#if 0
  long trap = no ( son ( pt ( e ) ) ) ;
  int t = ( ABS_OF ( fr ) - 32 ) << 1 ;
#endif
  error(ERROR_SERIOUS,  "checknan not implemented" ) ;
  return ;
}


/*
  START OF VOLATILE USE
  Not available until SunOS 5.0.
*/

void 
setvolatile (void)
{
  outs ( "!\t.volatile\n" ) ;
  return ;
}


/*
  END OF VOLATILE USE
  Not available until SunOS 5.0.
*/

void 
setnovolatile (void)
{
  outs ( "!\t.nonvolatile\n" ) ;
  return ;
}




/*
  Jump to the exception handler
*/
void 
do_exception ( int ex )
{
  baseoff b;
  ir_ins(i_mov,ex,R_O0);
  b = find_tag(TDF_HANDLER);
  ld_ins(i_ld,b,R_TMP);
  extj_reg_ins(i_call,R_TMP,1);
  /*extj_ins(i_call,b,1);*/
}


/*
  Check whether or not an exception condition has occured and,
  if so, jump to the label given in no(son(pt(e))).  
*/
static 
void check_integer_exception ( exp e )
{

  if(!error_treatment_is_trap(e)){
    int trap = no(son(pt(e)));
    uncond_ins(i_bvs,trap);
  }
  else{
#if 1
    int lab = new_label();
    uncond_ins(i_bvc,lab);
    do_exception(f_overflow);
    set_label(lab);
#endif
  }
  return;
}


/*
  Settings of exception bits in FSR.
*/

#define FSR_INVALID_FOP 0x200
#define FSR_OVERFLOW 0x100
#define FSR_UNDERFLOW 0x080
#define FSR_DIV_BY_0 0x040
#define FSR_INEXACT 0x020
#define FSR_ANY FSR_INVALID_FOP | FSR_OVERFLOW | FSR_DIV_BY_0 | FSR_UNDERFLOW 

/*
  Examine the accumulated exception bits (5:9) of the floating point status
  register to see if an exception has been raised.  If so, output a jump
  to the error label for the exp, otherwise return.
*/
static 
void check_floating_exception ( exp e, space sp, int except )
{
  freg fr;
  ans aa;
  where assdest;
  int rt = getreg(sp.fixed);
  int rt2;
  space nsp;
  nsp = guardreg(rt,sp);
  rt2 = getreg(nsp.fixed);
  fr.fr = FSR>>1;
  fr.dble = 0;
  discrim(assdest.answhere) = inreg;
  assdest.answhere.val.regans = rt;
  assdest.ashwhere.ashsize = assdest.ashwhere.ashalign = 32;
  setfregalt(aa,fr);
  move(aa,assdest,guardreg(rt2,nsp).fixed,1);
  rir_ins(i_and,rt,except,rt2);
  rir_ins(i_and,rt,~except,rt);
  discrim(assdest.answhere) = infreg;
  assdest.answhere.val.fregans = fr;
  assdest.ashwhere.ashalign = assdest.ashwhere.ashsize = 32;
  setregalt(aa,rt);
  move(aa,assdest,guardreg(rt2,nsp).fixed,1);
  if(!error_treatment_is_trap(e)){
    condrr_ins(i_bne,rt2,R_G0,no(son(pt(e))));
  }
  else{
    int new_lab = new_label();
    condrr_ins(i_be,rt2,R_G0,new_lab);
    do_exception(f_overflow);
    set_label(new_lab);
  }
  
  /*
  rir_ins(i_sll,rt,17,rt);
  condrr_ins(i_blt,rt,0,trap);*/
  return;
}


/*
  Setup the FSR to turn off traps in the event of an 
  IEEE_754 exception.  Hopefully this still sets the 
  exception bit in the FSR.
*/
static void 
turn_off_trap_on_exceptions ( space sp )
{
  freg fr;
  ans aa;
  where assdest;
  int rt = getreg(sp.fixed);
  fr.fr = FSR>>1;
  fr.dble = 0;
  discrim(assdest.answhere) = inreg;
  assdest.answhere.val.regans = rt;
  assdest.ashwhere.ashsize = assdest.ashwhere.ashalign = 32;
  setfregalt(aa,fr);
  move(aa,assdest,guardreg(rt,sp).fixed,1);
  rir_ins(i_and,rt,0xf07fffffL,rt);	/* clear trap mask */
  assdest.answhere = aa;
  setregalt(aa,rt);
  move(aa,assdest,guardreg(rt,sp).fixed,1);
  return;
}

  

/*
  Integer multiply instructions do not set the overflow flag
  in the condition codes register.  Overflow is detected by 
  looking at the top 32 bits of the result, which are held in
  the Y register.
*/
static void 
check_integer_multiply_exception ( exp e, space sp, int result )
{
  space nsp;
  int yreg;
  nsp = guardreg(result,sp);
  yreg = getreg(nsp.fixed);
  if(optim_level != 0){
    optim_level = 0;
    fprintf(as_file,"\t.optim\t\"-O0\"\n");
  }
  rr_ins(i_rd,YREG,yreg);
  if(is_signed(sh(son(e)))){
    int result_shift = getreg(guardreg(yreg,nsp).fixed);
    rir_ins(i_sra,result,31,result_shift);
    if(!error_treatment_is_trap(e)){
      condrr_ins(i_bne,result_shift,yreg,no(son(pt(e))));
    }
    else{
      int new_lab = new_label();
      condrr_ins(i_be,result_shift,yreg,new_lab);
      do_exception(f_overflow);
      set_label(new_lab);
    }
  }
  else{
    if(!error_treatment_is_trap(e)){
      condrr_ins(i_bne,yreg,R_G0,no(son(pt(e))));
    }
    else{
      int new_lab = new_label();
      condrr_ins(i_be,yreg,R_G0,new_lab);
      do_exception(f_overflow);
      set_label(new_lab);
    }
  }
  return;
}

/*
  If the value in register reg does not lie between the limits, then
  go to label trap.
*/
void 
test_unsigned ( int reg, int upper, int trap )
{
  condri_ins(i_bgu,reg,upper,trap);
  return;
}

void 
test_signed( int reg, int lower, int upper, int trap )
{
  condri_ins(i_blt,reg,lower,trap);
  condri_ins(i_bgt,reg,upper,trap);
  return;
}

void 
test_signed_and_trap ( int reg, int lower, int upper, int except )
{
  int ok_lab = new_label();
  int jump_label = new_label();
    
  condri_ins(i_blt,reg,lower,jump_label);
  condri_ins(i_bgt,reg,upper,jump_label);
  uncond_ins(i_b,ok_lab);
  set_label(jump_label);
  do_exception(except);
  set_label(ok_lab);
  return;
}

void 
test_unsigned_and_trap ( int reg, long upper, int except )
{
  int ok_lab = new_label();
  condri_ins(i_bleu,reg,upper,ok_lab);
  do_exception(except);
  set_label(ok_lab);
  return;
}

int 
regfrmdest ( where * dest, space sp )
{
  if(dest->answhere.d == inreg){
    return regalt(dest->answhere);
  }
  else{
    return getreg(sp.fixed);
  }
}


void 
load_reg ( exp e, int reg, space sp )
{
  where w;
  w.ashwhere = ashof(sh(e));
  setregalt(w.answhere,reg);
  code_here(e,sp,w);
  return;
}


/*
  TABLE OF UNSIGNED JUMPS

  The key to the test numbers is as follows :

  1 = "<="		8 = "!>="
  2 = "<"			9 = "!<"
  3 = ">="		A = "!<="
  4 = ">"			B = "<>"
  5 = "!="		C = "!<>"
  6 = "=="		D = "comp"
  7 = "!>"		E = "!comp"
*/

static const ins_p usbranch_tab [] = {
    /* 0 */ I_NIL,
    /* 1 */ i_bleu,
    /* 2 */ i_blu,
    /* 3 */ i_bgeu,
    /* 4 */ i_bgu,
    /* 5 */ i_bne,
    /* 6 */ i_be,
    /* 7 */ i_bleu,
    /* 8 */ i_blu,
    /* 9 */ i_bgeu,
    /* A */ i_bgu,
    /* B */ i_bne,
    /* C */ i_be,
    /* D */ i_ba,
    /* E */ i_bn
} ;

#define usbranches( i )	( usbranch_tab [i] )


/*	
    TABLE OF SIGNED JUMPS
*/

static const ins_p sbranch_tab [] = {
    /* 0 */ I_NIL,
    /* 1 */ i_ble,
    /* 2 */ i_bl,
    /* 3 */ i_bge,
    /* 4 */ i_bg,
    /* 5 */ i_bne,
    /* 6 */ i_be,
    /* 7 */ i_ble,
    /* 8 */ i_bl,
    /* 9 */ i_bge,
    /* A */ i_bg,
    /* B */ i_bne,
    /* C */ i_be,
    /* D */ i_ba,
    /* E */ i_bn
} ;

#define sbranches( i )	( sbranch_tab [i] )


/*
  TABLE OF FLOATING JUMPS
*/

static const ins_p fbranch_tab [] = {
    /* 0 */ I_NIL,
    /* 1 */ i_fble,
    /* 2 */ i_fbl,
    /* 3 */ i_fbge,
    /* 4 */ i_fbg,
    /* 5 */ i_fbne,
    /* 6 */ i_fbe,
    /* 7 */ i_fbule,
    /* 8 */ i_fbul,
    /* 9 */ i_fbuge,
    /* A */ i_fbug,
    /* B */ i_fblg,
    /* C */ i_fbue,
    /* D */ i_fbo,
    /* E */ i_fbu
} ;

#define fbranches( i )	( fbranch_tab [i] )


/*
  TABLE OF INVERTED JUMPS

  Are these right?
*/

prop notbranch [] = {
    /* 0 */ 0x0,
    /* 1 */ 0x4,
    /* 2 */ 0x3,
    /* 3 */ 0x2,
    /* 4 */ 0x1,
    /* 5 */ 0x6,
    /* 6 */ 0x5,
    /* 7 */ 0xa,
    /* 8 */ 0x9,
    /* 9 */ 0x8,
    /* A */ 0x7,
    /* B */ 0xc,
    /* C */ 0xb,
    /* D */ 0xe,
    /* E */ 0xd
} ;

#define obranch( i )	( notbranch [i] )


#define is_char_variety(v) ((name(v) == scharhd) || (name(v) == ucharhd))
#define is_short_variety(v) ((name(v) == swordhd) || (name(v) == uwordhd))

/*
  MOVE A FLOATING POINT CONSTANT INTO A REGISTER
*/
static void 
fconst ( int f, long hi, long lo )
{
  baseoff b ;
  int dlab = next_data_lab () ;
  insection ( rodata_section ) ;
  outs ( "\t.align\t8\n" ) ;
  outlab ( dlab ) ;
  outs ( ":\n\t.word\t" ) ;
  switch (endian) {
  case ENDIAN_LITTLE: outn(lo); outc(','); outn(hi); break;
  case ENDIAN_BIG:    outn(hi); outc(','); outn(lo); break;
  }
  outs ( "\n\t.align\t8\n" ) ;
  insection ( text_section ) ;
  b.base = dlab ;
  b.offset = 0 ;
  ldf_ins ( i_ldd, b, f << 1 ) ;
  return ;
}

#if 0
/*
  MOVE A FLOATING POINT CONSTANT INTO A REGISTER
*/
static void 
ldconst ( int r, long hi, long word2, long word3, long lo )
{
  baseoff b ;
  int dlab = next_data_lab () ;
  insection ( rodata_section ) ;
  outs ( "\t.align\t8\n" ) ;
  outlab ( dlab ) ;
  outs ( ":\n\t.word\t" ) ;
  switch (endian) {
  case ENDIAN_LITTLE: outn(lo); outc(','); outn(word3); outc(','); outn(word2); outc(','); outn(hi); break;
  case ENDIAN_BIG:    outn(hi); outc(','); outn(word2); outc(','); outn(word3); outc(','); outn(lo); break;
  }
  outs ( "\n\t.align\t8\n" ) ;
  insection ( text_section ) ;
  b.base = dlab ;
  b.offset = 0 ;
  ld_ins(i_set,b,r);
#ifdef NEWDWARF
  lost_count_ins();
#endif
  /*ldf_ins ( i_ldd, b, f << 1 ) ;*/
  return ;
}
#endif

/*
  FIND THE LAST TEST IN e WHICH IS A BRANCH TO second
*/
static exp 
testlast ( exp e, exp second )
{
  if ( name ( e ) == test_tag && pt ( e ) == second ) return e;
  if ( name ( e ) == seq_tag ) {
    exp b = bro ( son ( e ) ) ;
    if ( name ( b ) == test_tag && pt ( b ) == second ) {
      return b;
    } else if ( name ( b ) == top_tag ) {
      exp list = son ( son ( e ) ) ;
      for ( ; ; ) {
	if ( last ( list ) ) {
	  if ( name ( list ) == test_tag &&
	       pt ( list ) == second ) {
	    return list;
	  } else {
	    return NULL;
	  }
	} else {
	  list = bro ( list ) ;
	}
      }
    }
  }
  return NULL;
}

/*
  IS e THE LAST PROCEDURE ARGUMENT?
*/
bool 
last_param ( exp e )
{
  if ( !isparam ( e ) ) return 0;
  e = bro ( son ( e ) ) ;
#ifndef NEWDIAGS
  aa :
#endif
  {
    if ( (name ( e ) == ident_tag && name(son(e)) != formal_callee_tag) && 
	 isparam ( e ) ) return 0;
#ifndef NEWDIAGS
    if ( name ( e ) == diagnose_tag ) {
      e = son ( e ) ;
      goto aa ;
    }
#endif
  }
  return 1;
}


/*
  DOES e OR ONE OF ITS COMPONENTS CONTAIN A BITFIELD?
  Should really detect this once and for all at an earlier stage and
  record in props ( e ).
*/
static int 
has_bitfield ( exp e )
{
  if ( e == NULL ) return 0;
  switch ( name ( e ) ) {
    case compound_tag : {
      e = bro ( son ( e ) ) ;
      while ( 1 ) {
	if ( has_bitfield ( e ) ) return 1;
	if ( last ( e ) ) return 0;
	e = bro ( bro ( e ) ) ; 
      }
      /* NOT REACHED */
    }
    
    default : {
      return shape_align ( sh ( e ) ) == 1 ;
    }
  }
  /* NOT REACHED */
}


/*
  CONVERT ALL NON-BITFIELDS FROM BYTE OFFSETS TO BIT OFFSETS
  This must be done exactly once.  The problem arises because of the
  val_tag case in needscan.c.
*/

static void 
fix_nonbitfield ( exp e )
{
  if ( name ( e ) == compound_tag ) {
    e = son ( e ) ;
    while ( 1 ) {
      if ( name ( e ) == val_tag && name ( sh ( e ) ) == offsethd
	   && al2 ( sh ( e ) ) >= 8 ) {
	no ( e ) = no ( e ) << 3 ;
      }
      fix_nonbitfield ( bro ( e ) ) ;
      if ( last ( bro ( e ) ) ) return ;
      e = bro ( bro ( e ) ) ;
    }
    /* NOT REACHED */
  }
  return ;
}


/*
  USEFUL MACROS
*/

#define issgn( s )	is_signed ( s )

#define isdbl( s )	( ( bool ) ( name ( s ) != shrealhd ) )

#define is_long_double(s) ((bool) (name(s) == doublehd))

#define fregno( d, f )	( ( d ) ? -( ( f ) + 32 ) : ( ( f ) + 32 ) )

#define GETREG( d, s )	( discrim ( ( d ).answhere ) == inreg ?\
			  regalt ( ( d ).answhere ) :\
			  getreg ( ( s ).fixed ) )

#define GETFREG( d, s )	( discrim ( ( d ).answhere ) == infreg ?\
			  regalt ( ( d ).answhere ) :\
			  getfreg ( ( s ).flt ) )



/*
  This function finds the caller_tag corresponding to a caller_name tag
*/
exp 
find_ote ( exp nom, int n ) 
{
  exp dad = father(nom);
  while(name(dad) != apply_general_tag) {
    dad = father(dad);
  }
  dad = son(bro(son(dad)));
  while(n) {
    dad = bro(dad);
    n -- ;
  }
  assert(name(dad) == caller_tag);
  return dad;
}

/*
  If the floating point value held in register r will, when converted,
  fit into the integer variety rep_var then return, otherwise output
  a jump to label lab and return.  The conversion functions always perform a 
  round_towards zero, so the numbers used as the limits of the ranges are
  adjusted to account for this.
*/
void 
check_range_and_do_error_jump ( shape rep_var, int r, int lab, space sp, int rmode ) 
{
  int ftmp = getfreg(sp.flt);
  int to_small = (rmode == (int)f_toward_smaller);
  switch(name(rep_var)) {
    case ulonghd : {
      /* check    0 <= value <= (unsigned)-1 */
      /* fconst(ftmp,1106247679,-2097152); */

      if(to_small) {
	fconst(ftmp,1106247680,0);
      }
      else {
	fconst(ftmp,1106247679,-2097152);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbg,lab);
      if(to_small) {
	fconst(ftmp,0,0);
      }
      else {
	fconst(ftmp,-1074790400,0);
      }
      
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbl,lab);
      break;
    }
    case slonghd : {
      /* check -0x80000000 =< value <= 0x7fffffff */
      if(to_small) {
	fconst(ftmp,-1042284544,0);
      }
      else {
	fconst(ftmp,-1042284544,2097152);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbl,lab);
      /*fconst(ftmp,1105199104,0);*/
      if(to_small) {
	fconst(ftmp,1105199104,0);
      }
      else {
	fconst(ftmp,1105199103,-4194304);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbg,lab);
      break;
    }
    case uwordhd : {
      /* check 0 <= value <= 0xffff */
      if(to_small) {
	fconst(ftmp,0,0);
      }
      else {
	fconst(ftmp,-1074790400,0);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbl,lab);
      if(to_small) {
	fconst(ftmp,1089470464,0);
      }
      else {
	fconst(ftmp,1089470432,0);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbg,lab);
      break;
    }
    case swordhd : {
      /* check -0x8000 <= value <= 0x7fff */
      if(to_small) {
	fconst(ftmp,-1059061760,0);
      }
      else {
	fconst(ftmp,-1059061728,0);
      }
      
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbl,lab);
      if(to_small) {
	fconst(ftmp,1088421888,0);
      }
      else {
	fconst(ftmp,1088421824,0);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbg,lab);
      break;
    }
    case scharhd : {
      if(to_small) {
	fconst(ftmp,-1067450368,0);
      }
      else {
	fconst(ftmp,-1067442176,0);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbl,lab);
      if(to_small) {
	fconst(ftmp,1080033280,0);
      }
      else {
	fconst(ftmp,1080016896,0);
      }
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbg,lab);
      break;
    }
    case ucharhd : {
      if(to_small) {
	fconst(ftmp,0,0);
      }
      else {
	fconst(ftmp,-1074790400,0);
      }
      
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbl,lab);
      if(to_small) {
	fconst(ftmp,1081081856,0);
      }
      else {
	fconst(ftmp,1081073664,0);
      }
      
      rrf_ins(i_fcmpd,r<<1,ftmp<<1);
      fbr_ins(i_fbg,lab);
      break;
    }
    default : {
      error(ERROR_SERIOUS, "shape not covered in range check");
    }
  }
  return;
}


  
/*
  MAIN CODE PRODUCTION ROUTINE
  Produce for for the expression e, putting its result into dest 
  using the t-registers given by sp.  If exitlab is nonzero, it is 
  the label where the code is to continue.
*/

#ifdef NEWDIAGS
makeans 
make_code_1 ( exp e, space sp, where dest, int exitlab )
{
#else
makeans 
make_code ( exp e, space sp, where dest, int exitlab )
{
#endif
  makeans mka ;
  static int exceptions_initialised;
  mka.lab = exitlab ;
  mka.regmove = NOREG ;
  insection ( text_section ) ;

  switch ( name ( e ) ) {
    case general_proc_tag :
    case proc_tag : {
      /* Procedure body */
      static int inside_proc = 0 ;
      exceptions_initialised = 0;
      if ( inside_proc ) {
	error(ERROR_SERIOUS,  "Nested procedures not implemented" ) ;
      } else {
	inside_proc = 1 ;
	mka = make_proc_tag_code ( e, sp, dest, exitlab ) ;
	inside_proc = 0 ;
	exceptions_initialised = 0;
      }
      return mka;
    }
    case untidy_return_tag : 
    case res_tag : {
      /* Procedure result */
      return make_res_tag_code ( e, sp, dest, exitlab ) ;
    }
    case caller_tag : {
      return make_code(son(e),sp,dest,exitlab);
    }
    case apply_general_tag : {
      return make_apply_general_tag_code(e,sp,dest,exitlab);
    }
    case caller_name_tag : {
      return mka;
    }
    case make_callee_list_tag :  {
      return make_make_callee_list_tag(e,sp,dest,exitlab);
    }
    case same_callees_tag :  {
      return make_same_callees_tag(e,sp,dest,exitlab);
    }
    case make_dynamic_callee_tag :  {
      return make_make_dynamic_callee_tag(e,sp,dest,exitlab);
    }
    case tail_call_tag :  {
      return make_tail_call_tag(e,sp,dest,exitlab);
    }
    case return_to_label_tag : {
      int r = getreg(sp.fixed);
      where w;
      w.ashwhere.ashsize = 32;
      w.ashwhere.ashalign = 32;
      
      setregalt(w.answhere,r);
      code_here(son(e),sp,w);
      clear_all();
      rr_ins(i_mov,r,R_TMP);
      /*rir_ins(i_sub,R_FP,proc_state.callee_size>>3,R_FP);*/
#ifdef NEWDWARF
      if (current_dg_info) {
	current_dg_info->data.i_lj.brk = set_dw_text_label ();
	current_dg_info->data.i_lj.j.k = WH_REG;
	current_dg_info->data.i_lj.j.u.l = R_TMP;
      }
#endif
      extj_reg_ins_no_delay(i_jmp,R_TMP,-1);
      rir_ins(i_restore,R_FP,
	      0/*-(proc_state.frame_size)>>3*/,R_SP);
      clear_all();
      return mka;
    }


    case apply_tag : {
      /* Procedure application */
      mka = make_apply_tag_code ( e, sp, dest, exitlab ) ;
#if 0
      if(Has_vcallees){
	/* restore local_reg */
	baseoff b;
	b.base = R_FP;
	b.offset = -3 * PTR_SZ>>3;
	ld_ro_ins(i_ld,b,local_reg);
      }
#endif
      return mka;
    }
    case top_tag :
    case clear_tag : {
      /* Do nothing */
      if ( discrim ( dest.answhere ) == insomereg ) {
	int *sr = someregalt ( dest.answhere ) ;
	if ( *sr != -1 ) error(ERROR_SERIOUS,  "Illegal register" ) ;
	*sr = R_G0 ;
      }
      return mka;
    }

    case prof_tag : {
      return mka;
    }
    
    case seq_tag : {
      /* Sequences */
      exp t = son ( son ( e ) ) ;
      exp f = bro ( son ( e ) ) ;
      for ( ; ; ) {
	exp nt = ( last ( t ) ? f : bro ( t ) ) ;
	if ( name ( nt ) == goto_tag ) {
	  /* Gotos end sequences */
	  make_code ( t, sp, nowhere, no ( son ( pt ( nt ) ) ) ) ;
	} else {
	  ( void ) code_here ( t, sp, nowhere ) ;
	}
	if ( last ( t ) ) {
	  return make_code ( f, sp, dest, exitlab ) ;
	}
	t = nt ;
      }
      /* NOT REACHED */
    }

    case labst_tag : {
      /* Labelled statements */
      int lb = no ( son ( e ) ) ;
      if ( lb != 0 ) {
	clear_all () ;
	set_label ( lb ) ;
#ifdef NEWDWARF
        START_BB ();
#endif
      }
      return make_code ( bro ( son ( e ) ), sp, dest, exitlab ) ;
    }

    case rep_tag : {
      /* Repeats */
      exp first = son ( e ) ;
      exp second = bro ( first ) ;
      code_here(first,sp,nowhere);
      no ( son ( second ) ) = new_label () ;
	    
      return make_code ( second, sp, dest, exitlab ) ;
    }
	 
    case make_lv_tag :  {
      exp labst = pt(e);
      assert(name(labst) == labst_tag);
      {
	int lab = no(son(labst)); /* this is the asm lab no without
				     the prefix on it */
	/* Now the code is much like val_tag, save that the value is a string...
	 */
	int r ;
	switch ( discrim ( dest.answhere ) ){
	  case inreg : {
	    r = regalt ( dest.answhere ) ;
	    lr_ins ( lab, r ) ;
	    break ;
	  }
	  default : {
	    ans aa ;
	    r = getreg ( sp.fixed ) ;
	    lr_ins ( lab, r ) ;
	    setregalt ( aa, r ) ;
	    (void)move ( aa, dest, guardreg ( r, sp ).fixed, 1 ) ;
	  }
	}
	mka.regmove = r ;
	return mka;
      }
    }
	 
    case goto_lv_tag : {
      int ptr_reg;
      assert (last(son(e)));	  
      ptr_reg = reg_operand (son(e), sp ) ;
#ifdef NEWDWARF
      if (current_dg_info) {
	current_dg_info->data.i_lj.brk = set_dw_text_label ();
	current_dg_info->data.i_lj.j.k = WH_REG;
	current_dg_info->data.i_lj.j.u.l = ptr_reg;
      }
#endif
      extj_reg_ins( i_jmp, ptr_reg, -1); /* -1 means no params (not call)*/
      return mka;
    }

    case goto_tag : {
      /* Gotos */
      int lab = no ( son ( pt ( e ) ) ) ;
      assert ( lab >= 100 ) ;
      clear_all () ;
      /* needed if lab == exitlab ? */
#ifdef NEWDWARF
      if (current_dg_info) {
	current_dg_info->data.i_tst.brk = set_dw_text_label ();
	current_dg_info->data.i_tst.jlab.u.l = lab;
	current_dg_info->data.i_tst.jlab.k = LAB_CODE;
      }
#endif
      uncond_ins ( i_b, lab ) ;
      return mka;
    }

    case test_tag : {
      /* Tests */
      int lab ;
      ins_p branch ;
      exp l = son ( e ) ;
      exp r = bro ( l ) ;
      shape shl = sh ( l ) ;

      /* Find test number (mask out Rev bit) */
      int n = (int)test_number(e);
	    
#ifdef NEWDIAGS
      if (dgf(l))
	diag_arg (l, sp, dest);
      if (dgf(r))
	diag_arg (r, sp, dest);
#endif

      /* Find label - see cond_tag case */
      if ( ptno ( e ) < 0 ) {
	lab = -ptno ( e ) ;
      } else {
	lab = no ( son ( pt ( e ) ) ) ;
      }

     if (use_long_double) {
      if ( name ( sh ( l ) ) == doublehd ) {
	if ( IsRev ( e ) ) {
	  quad_op ( r, l, sp, dest, -n ) ;
        } 
	else {
	  quad_op ( l, r, sp, dest, -n ) ;
	}
#ifdef NEWDWARF
	if (current_dg_info) {
	  current_dg_info->data.i_tst.brk = set_dw_text_label ();
	  current_dg_info->data.i_tst.jlab.u.l = lab;
	  current_dg_info->data.i_tst.jlab.k = LAB_CODE;
	}
#endif
	condrr_ins ( i_bne, R_O0, R_G0, lab ) ;
#ifdef NEWDWARF
	START_BB ();
	if (current_dg_info)
	  current_dg_info->data.i_tst.cont = set_dw_text_label ();
#endif
	return mka;
      }
     }

      if ( is_floating ( name ( sh ( l ) ) ) ) {
	/* Floating tests */
	space nsp ;
	int a1, a2 ;
	bool dble = isdbl ( shl ) ;
	ins_p compare = ( dble ? i_fcmpd : i_fcmps ) ;

	branch = fbranches ( n ) ;
	if ( IsRev ( e ) ) {
	  a2 = freg_operand ( r, sp, getfreg ( sp.flt ) ) ;
	  nsp = guardfreg ( a2, sp ) ;
	  a1 = freg_operand ( l, nsp, getfreg ( nsp.flt ) ) ;
	} else {
	  a1 = freg_operand ( l, sp, getfreg ( sp.flt ) ) ;
	  nsp = guardfreg ( a1, sp ) ;
	  a2 = freg_operand ( r, nsp, getfreg ( nsp.flt ) ) ;
	}
	rrf_cmp_ins ( compare, a1 << 1, a2 << 1 ) ;
#ifdef NEWDWARF
	if (current_dg_info) {
	  current_dg_info->data.i_tst.brk = set_dw_text_label ();
	  current_dg_info->data.i_tst.jlab.u.l = lab;
	  current_dg_info->data.i_tst.jlab.k = LAB_CODE;
	}
#endif
	fbr_ins ( branch, lab ) ;
#ifdef NEWDWARF
	START_BB ();
	if (current_dg_info)
	  current_dg_info->data.i_tst.cont = set_dw_text_label ();
#endif
	return mka;
      } 
      else {
	/* Integer tests */
	int a1, a2 ;
	bool unsgn ;
	assert(name(l) != val_tag); /* now in common section */
	/* Choose branch instruction */
	unsgn = (bool)(!is_signed(shl) || name(shl)==ptrhd);
	branch = ( unsgn ? usbranches ( n ) : sbranches ( n ) ) ;
	a1 = reg_operand ( l, sp ) ;
	if ( name ( r ) == val_tag ) {
	  long v = no(r);
#ifdef NEWDWARF
	  if (current_dg_info)
	    current_dg_info->data.i_tst.brk = set_dw_text_label ();
#endif
	  if ( unsgn && v == 0 && ( n == 2 || n == 3 ) ) {
	    /* Do unsigned < 0 and unsigned >= 0 */
	    br_ins ( ( n == 2 ? i_bn : i_ba ), lab ) ;
	  } 
	  else
	    {
	      /* work round for using 0xffffffff as -1
		 unsigned <=0 becomes == 0
		 unsigned >0 becomes != 0 */
	      if ( unsgn && v == 0 && ( n == 1 || n == 4 ) ) 
		{
		  n = ((n==1) ? 6 : 5);
		  branch = usbranches ( n ) ;
		}
	      if ( v ) {
		condri_ins ( branch, a1, v, lab ) ;
	      } else {
		condrr_ins ( branch, a1, R_G0, lab ) ;
	      }
	    }
	} else {
	  space nsp ;
	  nsp = guardreg ( a1, sp ) ;
	  a2 = reg_operand ( r, nsp ) ;
#ifdef NEWDWARF
	  if (current_dg_info)
	    current_dg_info->data.i_tst.brk = set_dw_text_label ();
#endif
	  condrr_ins ( branch, a1, a2, lab ) ;
	}
#ifdef NEWDWARF
	START_BB ();
	if (current_dg_info) {
	  current_dg_info->data.i_tst.jlab.u.l = lab;
	  current_dg_info->data.i_tst.jlab.k = LAB_CODE;
	  current_dg_info->data.i_tst.cont = set_dw_text_label ();
	}
#endif
	return mka;
      }
      /* NOT REACHED */
    }

#ifndef NEWDIAGS
    case diagnose_tag : {
      /* Diagnostics */
      diag_info *d = dno ( e ) ;
#if DWARF
      output_diag ( d, 0, e ) ;
      mka = make_code ( son ( e ), sp, dest, exitlab ) ;
      output_end_scope ( d, e ) ;
#else
      stab_begin ( d, 0, e ) ;
      mka = make_code ( son ( e ), sp, dest, exitlab ) ;
      stab_end ( d, e ) ;
#endif
      return mka;
    }
#endif

    case solve_tag : {
      /* Labelled statements */
      exp m = bro ( son ( e ) ) ;
      int l = exitlab ;

      if ( discrim ( dest.answhere ) == insomereg ) {
	int *sr = someregalt ( dest.answhere ) ;
	if ( *sr != -1 ) error(ERROR_SERIOUS,  "Illegal register" ) ;
	*sr = getreg ( sp.fixed ) ;
	setregalt ( dest.answhere, *sr ) ;
      }
      /* Set up all the labels */
      for ( ; ; ) {
	no ( son ( m ) ) = new_label () ;
	if ( last ( m ) ) break ;
	m = bro ( m ) ;
      }
      m = son ( e ) ;
      /* Evaluate all the component statements */
      for ( ; ; ) {
	int fl = make_code ( m, sp, dest, l ).lab ;
	clear_all () ;
	if ( fl != 0 ) l = fl ;
	if ( !last ( m ) ) {
	  /* jump to end of solve */
	  if ( l == 0 ) l = new_label () ;
	  if ( name ( sh ( m ) ) != bothd ) uncond_ins ( i_b, l ) ;
	}
	if ( last ( m ) ) {
	  mka.lab = l ;
	  return mka;
	}
	m = bro ( m ) ;
      }
      /* NOT REACHED */
    }
    case chvar_tag : {
      /* Change integer variety */
      exp arg = son ( e ) ;
      int size_e = shape_size ( sh ( e ) ) ;
      int to = ( int ) name ( sh ( e ) ), from ;
      int sreg, dreg ;
      bool inmem_dest ;

      space nsp;
	    
    /* For a series of chvar_tags, do large to small in one go */
      while ( name ( arg ) == chvar_tag &&
	      shape_size ( sh ( arg ) ) >= size_e ) {
	arg = son ( arg ) ;
      }
      from = (int) name ( sh ( arg ) ) ;
#if 1	    
      if (from == bitfhd) {
	switch (shape_size(sh(arg))) {
	  case 8:
	  sh(arg) = is_signed(sh(arg)) ? scharsh : ucharsh;
	  from = name(sh(arg));
	  break;
	  case 16:
	  sh(arg) = is_signed(sh(arg)) ? swordsh : uwordsh;
	  from = name(sh(arg));
	  break;
	  case 32:
	  sh(arg) = is_signed(sh(arg)) ? slongsh : ulongsh;
	  from = name(sh(arg));
	  break;
	}
      }

      if (to == bitfhd){
	switch (shape_size(sh(e))){
	  case 8:
	  sh(e) = is_signed(sh(e)) ? scharsh : ucharsh;
	  to = name (sh(e));
	  break;
	  case 16:
	  sh(e) = is_signed(sh(e)) ? swordsh : uwordsh;
	  to = name (sh(e));
	  break;
	  case 32:
	  sh(e) = is_signed(sh(e)) ? slongsh : ulongsh;
	  to = name (sh(e));
	  break;
	}
      }
	
#endif
      /* Small to large conversions */
      if ( from == to || to == slonghd || to == ulonghd ||
	   ( to == uwordhd && from == ucharhd ) ||
	   ( to == swordhd && from == scharhd ) ||
	   ( to == swordhd && from == ucharhd ) ) {
	ans aa ;
	switch ( discrim ( dest.answhere ) ) {
	  case inreg : {
	    sreg = regalt ( dest.answhere ) ;
	    if(sreg == R_G0){
	      if(0 /*optop(e)*/){
		return mka;
	      }
	      else {
		sreg = getreg(sp.fixed);
	      }
	    }
	    sp = guardreg(sreg,sp);
	    reg_operand_here ( arg, sp, sreg ) ;
	    break ;
	  }
	  default : {
	    sreg = reg_operand ( arg, sp ) ;
	    break ;
	  }
	}
	if(!optop(e)){
	  switch ( to ) {
	    case ucharhd : {
	      if(is_signed(sh(son(e)))){
		if(error_treatment_is_trap(e)){
		  int oklab = new_label();
		  condrr_ins(i_bge,sreg,R_G0,oklab);
		  do_exception(f_overflow);
		  set_label(oklab);
		}
		else{
		  condrr_ins(i_blt,sreg,R_G0,no(son(pt(e))));
		}
	      }
	      break ;
	    }
	    case scharhd : {
	      if(!is_signed(sh(son(e)))){
		if(error_treatment_is_trap(e)){
		  int oklab = new_label();
		  condri_ins(i_bleu,sreg,0x7f,oklab);
		  do_exception(f_overflow);
		  set_label(oklab);
		}
		else{
		  condri_ins(i_bgtu,sreg,0x7f,no(son(pt(e))));
		}
	      }
	      break ;
	    }
	    case uwordhd : {
	      if(is_signed(sh(son(e)))){
		if(error_treatment_is_trap(e)){
		  int oklab = new_label();
		  condrr_ins(i_bge,sreg,R_G0,oklab);
		  do_exception(f_overflow);
		  set_label(oklab);
		}
		else{
		  condrr_ins(i_blt,sreg,R_G0,no(son(pt(e))));
		}
	      }
	      break ;
	    }
	    case swordhd : {
	      if(!is_signed(sh(son(e)))){
		if(error_treatment_is_trap(e)){
		  int oklab = new_label();
		  condri_ins(i_bleu,sreg,0x7fff,oklab);
		  do_exception(f_overflow);
		  set_label(oklab);
		}
		else{
		  condri_ins(i_bgtu,sreg,0x7fff,no(son(pt(e))));
		}
	      }
	      break ;
	    }
	    case ulonghd :{
	      if(is_signed(sh(son(e)))){
		if(error_treatment_is_trap(e)){
		  int oklab = new_label();
		  condrr_ins(i_bge,sreg,R_G0,oklab);
		  do_exception(f_overflow);
		  set_label(oklab);
		}
		else{
		  condrr_ins(i_blt,sreg,R_G0,no(son(pt(e))));
		}
	      }
	      break;
	    }
	    case slonghd :{
	      if(!is_signed(sh(son(e)))){
		if(error_treatment_is_trap(e)){
		  int oklab = new_label();
		  condri_ins(i_bleu,sreg,0x7fffffff,oklab);
		  do_exception(f_overflow);
		  set_label(oklab);
		}
		else{
		  condri_ins(i_bgtu,sreg,0x7fffffff,no(son(pt(e))));
		}
	      }
	      break;
	    }
	      
	    default :
	    break ;
	  }
	}
	setregalt ( aa, sreg ) ;
	mka.regmove = move ( aa, dest, sp.fixed, issgn ( sh ( e ) ) ) ;
	return mka;
      }

    switch ( discrim ( dest.answhere ) ) {
      case inreg : {
	sreg = reg_operand ( arg, sp ) ;
	nsp = guardreg(sreg, sp);
	dreg = regalt ( dest.answhere ) ;
	if(dreg == R_G0){
	  if(optop(e)){
	    return mka;
	  }
	  else { 
	    dreg = getreg(nsp.fixed);
	  }
	}
	inmem_dest = 0 ;
	break ;
      }
      case insomereg : {
	int *dr = someregalt ( dest.answhere ) ;
	sreg = reg_operand ( arg, sp ) ;
	nsp = guardreg(sreg, sp);
	dreg = getreg ( sp.fixed ) ;
	*dr = dreg ;
	inmem_dest = 0 ;
	break ;
      }
      default : {
	sreg = reg_operand ( arg, sp ) ;
	nsp = guardreg(sreg, sp);
	dreg = getreg ( sp.fixed ) ;
	inmem_dest = 1 ;
	break ;
      }
    }

    if ( inmem_dest && size_e <= shape_size ( sh ( arg ) ) ) {
      /* Going to smaller sized memory, store will truncate */
      ans aa ;
      setregalt ( aa, sreg ) ;
      ( void ) move ( aa, dest, nsp.fixed, 1 ) ;
      return mka;
    }

    /* Shorten type if needed */
    switch ( to ) {
      case ucharhd : {
	if(!optop(e)){
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(sreg,255,f_overflow);
	  }
	  else {
	    test_unsigned(sreg,255,no(son(pt(e))));
	  }
	}
	rir_ins ( i_and, sreg, 0xff, dreg ) ;
	break ;
      }
      case scharhd : {
	if(!optop(e)){
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(sreg,-128,127,f_overflow);
	  }
	  else{
	    test_signed(sreg,-128,127,no(son(pt(e))));
	  }
	}
	rir_ins ( i_sll, sreg, 24, dreg ) ;
	rir_ins ( i_sra, dreg, 24, dreg ) ;
	break ;
      }
      case uwordhd : {
	if(!optop(e)){
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(sreg,0xffff,f_overflow);
	  }
	  else{
	    test_unsigned(sreg,0xffff,no(son(pt(e))));
	  }
	}
	if ( from != ucharhd ) {
	  rir_ins ( i_and, sreg, 0xffff, dreg ) ;
	} else if ( sreg != dreg ) {
	  rr_ins ( i_mov, sreg, dreg ) ;
	}
	break ;
      }
      case swordhd : {
	if(!optop(e)){
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(sreg,-0x8000,0x7fff,f_overflow);
	  }
	  else{
	    test_signed(sreg,-0x8000,0x7fff,no(son(pt(e))));
	  }
	}
	if ( from != scharhd && from != ucharhd ) {
	  rir_ins ( i_sll, sreg, 16, dreg ) ;
	  rir_ins ( i_sra, dreg, 16, dreg ) ;
	  break ;
	}
	/* FALL THROUGH */
      }
      default : {
	if ( sreg != dreg ) rr_ins ( i_mov, sreg, dreg ) ;
	break ;
      }
    }

    if ( inmem_dest ) {
      ans aa ;
      setregalt ( aa, dreg ) ;
      ( void ) move ( aa, dest, nsp.fixed, 1 ) ;
    } else {
      mka.regmove = dreg ;
    }
    return mka;
    }

    case env_size_tag : {
      int constval = (proc_state.frame_size+proc_state.callee_size)>>3;
      ans aa;
      int rt = getreg(sp.fixed);
      ir_ins(i_mov,constval,rt);
      setregalt(aa,rt);
      (void)move(aa,dest,guardreg(rt,sp).fixed,1);
      mka.regmove = rt;
      return mka;
    }
    
      
    case plus_tag :
    case offset_add_tag : {
      /* Addition */
      if(optop(e)){
	mka.regmove = comm_op ( e, sp, dest,(optop(e))?i_add:i_addcc) ;
	return mka;
      }
#if 0
      if(error_treatment_is_trap(e)){
	int new_lab = new_label();
	mka.regmove = comm_op ( e, sp, dest,(optop(e))?i_add:i_addcc) ;
	uncond_ins(i_bvc,new_lab);
	do_exception(f_overflow);
	set_label(new_lab);
	return mka;
      }
#endif      
      if (!optop(e) /*&& !error_treatment_is_trap(e)*/){
       where newdest;
       ans aa;
       int res_reg = getreg(sp.fixed);
       space nsp;
       newdest.ashwhere = dest.ashwhere;
       newdest.answhere.d = inreg;

       newdest.answhere.val.regans = res_reg;
       nsp = guardreg(res_reg,sp);
       /*       if(name(sh(e)) != ulonghd && name(sh(e)) != slonghd)*/
       mka.regmove = comm_op ( e, sp, newdest,(optop(e))?i_add:i_addcc) ;
       switch(name(sh(e))){
	 case ulonghd: {
	   int l,r;
	   /*int newlab = new_label();*/
	   int rt;
	   rt = getreg(nsp.fixed);
	   l = reg_operand(son(e),nsp);
	   r = reg_operand(bro(son(e)),nsp);		

	   if(error_treatment_is_trap(e)){
	     int new_lab = new_label();
	     condrr_ins(i_bgeu,res_reg,l,new_lab);
	     do_exception(f_overflow);
	     set_label(new_lab);
	   }
	   else{
	     condrr_ins(i_bltu,res_reg,l,no(son(pt(e))));
	   }
	   break;
	 }

	  case slonghd: {
	    check_integer_exception(e);
	    break;
	  }
	  case swordhd:{
	    if(error_treatment_is_trap(e)){
	      test_signed_and_trap(res_reg,-0x8000,0x7fff,f_overflow);
	    }
	    else{
	      test_signed(res_reg,-0x8000,0x7fff,no(son(pt(e))));
	    }
	    break;
	  }
	  case uwordhd:{
	    if(error_treatment_is_trap(e)){
	      test_unsigned_and_trap(res_reg,0xffff,f_overflow);
	    }
	    else{
	      test_unsigned(res_reg,0xffff,no(son(pt(e))));
	    }
	    break;
	  }
	 case scharhd:{
	   if(error_treatment_is_trap(e)){
	     test_signed_and_trap(res_reg,-128,127,f_overflow);
	   }
	   else{
	     test_signed(res_reg,-128,127,no(son(pt(e))));
	   }
	   break;
	 }
	 case ucharhd:{
	   if(error_treatment_is_trap(e)){
	     test_unsigned_and_trap(res_reg,255,f_overflow);
	   }
	   else{
	     test_unsigned(res_reg,255,no(son(pt(e))));
	   }
	   break;
	 }
	 default:
	  error(ERROR_INTERNAL, "unimplemented shape");
       }
       setregalt(aa,res_reg);
       mka.regmove = move(aa,dest,sp.fixed,0);
       return mka;
     }
    }
	  
	  
#ifdef make_stack_limit_tag
    case make_stack_limit_tag :
#endif
    case minus_tag :
    case minptr_tag :
    case offset_subtract_tag : {
    /* Subtraction */
      if(optop(e)) {
	mka.regmove = non_comm_op ( e, sp, dest, optop(e)?i_sub:i_subcc) ;
	return mka;
      }
#if 0      
      if(error_treatment_is_trap(e)) {
      int new_lab = new_label();
      mka.regmove = non_comm_op ( e, sp, dest, optop(e)?i_sub:i_subcc) ;
      uncond_ins(i_bvc,new_lab);
      do_exception(f_overflow);
      set_label(new_lab);
      return mka;
      }
#endif 
      if(!optop(e) /*&& !error_treatment_is_trap(e)*/ ){
	where newdest;
	ans aa;
	int res_reg = getreg(sp.fixed);
	space nsp;
	newdest.ashwhere = dest.ashwhere;
	newdest.answhere.d = inreg;

	newdest.answhere.val.regans = res_reg;
	nsp = guardreg(res_reg,sp);
	mka.regmove = comm_op ( e, sp, newdest,(optop(e))?i_sub:i_subcc) ;

      switch(name(sh(e))){
	case ulonghd:{
	  int l,r;
	  l = reg_operand(son(e),nsp);
	  r = reg_operand(bro(son(e)),nsp);
	  if(!error_treatment_is_trap(e)){
	    condrr_ins(i_bgtu,r,l,no(son(pt(e))));
	  }
	  else{
	    int newlab = new_label();
	    condrr_ins(i_bleu,r,l,newlab);
	    do_exception(f_overflow);
	    set_label(newlab);
	  }
	  break;
	}
	case slonghd:{
	  check_integer_exception(e);
	  break;
	}
	case swordhd: {
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(res_reg,-0x8000,0x7fff,f_overflow);
	  }
	  else{
	    test_signed(res_reg,-0x8000,0x7fff,no(son(pt(e))));
	  }
	  break;
	}
	case uwordhd: {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(res_reg,0xffff,f_overflow);
	  }
	  else{
	    test_unsigned(res_reg,0xffff,no(son(pt(e))));
	  }
	  break;
	}
	case scharhd: {
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(res_reg,-128,127,f_overflow);
	  }
	  else{
	    test_signed(res_reg,-128,127,no(son(pt(e))));
	  }
	  break;
	}
	case ucharhd: {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(res_reg,255,f_overflow);
	  }
	  else{
	    test_unsigned(res_reg,255,no(son(pt(e))));
	  }
	  break;
	}
	default:
	error(ERROR_INTERNAL, "unimplemented shape");
      }	
      setregalt(aa,res_reg);
      mka.regmove = move(aa,dest,sp.fixed,0);
      }
      return mka;
    }

    case mult_tag :
    case offset_mult_tag : {
    /* Multiplication */
    bool sgned = issgn ( sh ( e ) ) ;
    if(optop(e)) {
      mka.regmove = do_mul_comm_op ( e, sp, dest, sgned ) ;
      return mka;
    }
#if 0
    if(error_treatment_is_trap(e)) {
      int new_lab = new_label();
      mka.regmove = do_mul_comm_op ( e, sp, dest, sgned ) ;
      uncond_ins(i_bvc,new_lab);
      do_exception(f_overflow);
      set_label(new_lab);
      return mka;
    }
#endif          
    if(!optop(e) /*&& !error_treatment_is_trap(e)*/ /* && is_signed(sh(e))*/ ){
     where newdest;
       ans aa;
       int res_reg = getreg(sp.fixed);
       space nsp;
       newdest.ashwhere = dest.ashwhere;
       newdest.answhere.d = inreg;
       newdest.ashwhere.ashsize = 32;
       newdest.ashwhere.ashalign = 32;
       newdest.answhere.val.regans = res_reg;
       nsp = guardreg(res_reg,sp);
       mka.regmove = do_mul_comm_op ( e, sp, newdest, sgned );
       
      switch(name(sh(e))){
	case ulonghd :
	case slonghd :{
	  check_integer_multiply_exception(e,sp,res_reg);
	  break;
	}
	case swordhd : {
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(res_reg,-0x8000,0x7fff,f_overflow);
	  }
	  else{
	    test_signed(res_reg,-0x8000,0x7fff,no(son(pt(e))));
	  }
	  break;
	}
	case uwordhd : {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(res_reg,0xffff,f_overflow);
	  }
	  else{
	    test_unsigned(res_reg,0xffff,no(son(pt(e))));
	  }
	  break;
	}
	case scharhd : {
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(res_reg,-128,127,f_overflow);
	  }
	  else{
	    test_signed(res_reg,-128,127,no(son(pt(e))));
	  }
	  break;
	}
	case ucharhd : {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(res_reg,255,f_overflow);
	  }
	  else{
	    test_unsigned(res_reg,255,no(son(pt(e))));
	  }
	  break;
	}
	default :
	error(ERROR_INTERNAL, "unimplemented shape");
      }	
      setregalt(aa,res_reg);
      mka.regmove = move(aa,dest,sp.fixed,0);
    }
    return mka;
    }
    case fmax_tag : {
    /* modelled on test code */
      ins_p branch ;
      exp l = son ( e ) ;
      exp r = bro ( l ) ;
      shape shl = sh ( l ) ;
      freg a1, a2, d;
      space nsp;
      ans aa;
	  
      int n = (name(e) == min_tag) ? 2 : 3; /* min -> lt, max -> ge */
	 
    bool unsgn ;
	  
    /*assert(name(l) != val_tag);*/ /* now in common section */
	  
	  
    /* Choose branch instruction */
    unsgn = ( bool ) ( name ( shl ) >= ptrhd || !issgn ( shl ) ) ;
    branch = fbranches (n);
    	  
    d.fr = GETFREG(dest, sp);
    nsp = guardfreg(d.fr, sp);
    a1.fr = freg_operand ( l, nsp,getfreg(sp.flt) ) ;
    nsp = guardfreg ( a1.fr, nsp ) ;
    a2.fr = freg_operand ( r, nsp,getfreg(sp.flt)) ;
    fmaxminrr_ins ( branch, a1.fr<<1, a2.fr<<1, d.fr<<1,name(sh(e))) ;
	  
    setfregalt (aa, d);
    move (aa, dest, guardfreg (d.fr, sp).fixed, 0);
    mka.regmove = d.fr<<1;
    return mka;
	  
  }
      

  case max_tag :
  case min_tag :
  case offset_max_tag : {
    /* modelled on test code */
    ins_p branch ;
    exp l = son ( e ) ;
    exp r = bro ( l ) ;
    shape shl = sh ( l ) ;
    int a1, a2, d;
    space nsp;
    ans aa;
	  
    int n = (name(e) == min_tag) ? 2 : 3; /* min -> lt, max -> ge */
	 
    bool unsgn ;
	  
    /*assert(name(l) != val_tag);*/ /* now in common section */
	  
	  
    /* Choose branch instruction */
    unsgn = ( bool ) ( name ( shl ) >= ptrhd || !issgn ( shl ) ) ;
    branch = ( unsgn ? usbranches ( n ) : sbranches ( n ) ) ;
	  
    d = GETREG(dest, sp);
    nsp = guardreg(d, sp);
    a1 = reg_operand ( l, nsp ) ;
	  
    if ( name ( r ) == val_tag ) {
      int v = no ( r ) ;
      maxminri_ins ( branch, a1, v,d ) ;
    }
    else {
      nsp = guardreg ( a1, nsp ) ;
      a2 = reg_operand ( r, nsp ) ;
      maxminrr_ins ( branch, a1, a2, d) ;
    }
	  
    setregalt (aa, d);
    move (aa, dest, guardreg (d, sp).fixed, 0);
    mka.regmove = d;
    return mka;
	  
  }
  case div0_tag :
  case div1_tag :
  case div2_tag :
  case offset_div_by_int_tag :
  case offset_div_tag : {
    /* Division */
    where newdest;
    int res_reg;
    ans aa;
    bool sgned = issgn ( sh ( e ) ) ;
    if(!optop(e) && !error_treatment_is_trap(e)){
      int reg_test = reg_operand(bro(son(e)),sp);
      condrr_ins(i_be,reg_test,0,no(son(pt(e))));
    }
    if(!optop(e) /*&& !error_treatment_is_trap(e)*/) {
      space nsp;
      res_reg = getreg(sp.fixed);
      newdest.ashwhere = dest.ashwhere;
      newdest.answhere.d = inreg;
      newdest.answhere.val.regans = res_reg;
      newdest.ashwhere.ashsize = 32;
      newdest.ashwhere.ashalign = 32;
      nsp = guardreg(res_reg,sp);
    }
    else newdest = dest;

    mka.regmove = do_div_op ( e, sp, newdest, sgned ) ;
    if(!optop(e)){
      /* note : mka.regmove should always be a valid register if the 
	 division has an error treatment */
      switch(name(sh(e))) {
	case slonghd :
	case ulonghd :{
	  break;
	}
	
	case swordhd :{
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(res_reg,-0x800,0x7fff,f_overflow);
	  }
	  else{
	    test_signed(res_reg,-0x8000,0x7fff,no(son(pt(e))));
	  }
	  break;
	}
	case uwordhd :{
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(res_reg,0xffff,f_overflow);
	  }
	  else{
	    test_unsigned(res_reg,0xffff,no(son(pt(e))));
	  }
	  break;
	}
	case scharhd : {
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(res_reg,-128,127,f_overflow);
	  }
	  else{
	    test_signed(res_reg,-128,127,no(son(pt(e))));
	  }
	  break;
	}
	case ucharhd : {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(res_reg,255,f_overflow);
	  }
	  else{
	    test_unsigned(res_reg,255,no(son(pt(e))));
	  }
	  break;
	}
	default: error(ERROR_INTERNAL, "unimplemented shape");
      }
      setregalt(aa,res_reg);
      mka.regmove = move(aa,dest,sp.fixed,0);
    }
    return mka;
  }

  case rem0_tag :
  case mod_tag :
  case rem2_tag : {
    /* Remainder */
    bool sgned = issgn ( sh ( e ) ) ;
    if(!optop(e) && !error_treatment_is_trap(e)){
      int reg_test = reg_operand(bro(son(e)),sp);
      condrr_ins(i_be,reg_test,0,no(son(pt(e))));
    }
    mka.regmove = do_rem_op ( e, sp, dest, sgned ) ;
    return mka;
  }

  case neg_tag :
  case offset_negate_tag : {
    /* Negation */
    ans aa;
    int rd = regfrmdest(&dest,sp);
    if(!optop(e)) {
      int rsrc = reg_operand(son(e),sp);
      if(rd == R_G0) rd = getreg(sp.fixed);
      rrr_ins(i_subcc,R_G0,rsrc,rd);
    }
    else {
      mka.regmove = monop ( e, sp, dest, i_neg ) ;
      return mka;
    }
    if(!optop(e) /* && !error_treatment_is_trap(e)*/) {
      switch(name(sh(e))) {
	case ulonghd : {
	  if(!error_treatment_is_trap(e)){
	    condrr_ins(i_blt,rd,R_G0,no(son(pt(e))));
	  }
	  else{
	    int lab = new_label();
	    condrr_ins(i_bge,rd,R_G0,lab);
	    do_exception(f_overflow);
	    set_label(lab);
	  }
	  break;
	}
	case slonghd : {
	  check_integer_exception(e);
	  break;
	}
	case uwordhd : {
	  if(!error_treatment_is_trap(e)){
	    condrr_ins(i_blt,rd,R_G0,no(son(pt(e))));
	  }
	  else{
	    int lab = new_label();
	    condrr_ins(i_bge,rd,R_G0,lab);
	    do_exception(f_overflow);
	    set_label(lab);
	  }
	  break;
	}
	case swordhd : {
	  if(error_treatment_is_trap(e)){
	    test_signed_and_trap(rd,-0x8000,0x7fff,f_overflow);
	  }
	  else{
	    test_signed(rd,-0x8000,0x7fff,no(son(pt(e))));
	  }
	  break;
	}	
	case ucharhd : {
	  if(!error_treatment_is_trap(e)){
	    condrr_ins(i_blt,rd,R_G0,no(son(pt(e))));
	  }
	  else{
	    int lab = new_label();
	    condrr_ins(i_bge,rd,R_G0,lab);
	    do_exception(f_overflow);
	    set_label(lab);
	  }

	  break;
	}
	case scharhd : {
	  if(!error_treatment_is_trap(e)){
	    test_signed(rd,-128,127,no(son(pt(e))));
	  }
	  else{
	    test_signed_and_trap(rd,-128,127,f_overflow);
	  }
	  break;
	}
	default: error(ERROR_INTERNAL, "unimplemented shape");
      }
    }
    setregalt(aa,rd);
    move(aa,dest,sp.fixed,0);
    return mka;
  }
  
  case abs_tag : {
    /* Negation */
    mka.regmove = absop ( e, sp, dest) ;
    if(!optop(e) && is_signed(sh(e))) {
      switch(name(sh(e))) {
	case slonghd : {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(mka.regmove,0x7fffffff,f_overflow);
	  }
	  else {
	    test_unsigned(mka.regmove,0x7fffffff,no(son(pt(e))));
	  }
	  break;
	}
	case swordhd : {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(mka.regmove,0x7fff,f_overflow);
	  }
	  else {
	    test_unsigned(mka.regmove,0x7fff,no(son(pt(e))));
	  }
	  break;
	}
	case scharhd : {
	  if(error_treatment_is_trap(e)){
	    test_unsigned_and_trap(mka.regmove,127,f_overflow);
	  }
	  else {
	    test_unsigned(mka.regmove,127,no(son(pt(e))));
	  }
	  break;
	}
	default: error(ERROR_INTERNAL, "unimplemented shape");
      }
    }
    return mka;
  }

  case shl_tag :
  case shr_tag : {
    /* Shifts */
    ans aa ;
    int d ;
    space nsp ;
    ins_p shnat ;
    exp s = son ( e ) ;
    exp b = bro ( s ) ;
    bool sgned = issgn ( sh ( e ) ) ;
    int a = reg_operand ( s, sp ) ;
    int sz = shape_size(sh(s));
    int norms = 0;
    bool lded = ((name(s) == name_tag && regofval(s) >=100) 
		 || (name(s) == cont_tag &&
		     (name(son(s))!=name_tag || regofval(son(s))>0)
		     ));
    bool signok = (sz == 32) || (name(s) == chvar_tag) || lded;
    if ( name ( e ) == shr_tag ) {
      shnat = ( sgned ? i_sra : i_srl ) ;
      if(!signok) rir_ins(i_sll,a,norms=32-sz,a);
    } else {
      shnat = i_sll ;
    }
    nsp = guardreg ( a, sp ) ;
    d = GETREG ( dest, nsp ) ;


    if ( name ( b ) == val_tag ) {
      /* Special cases? */
      if(((no(b) + norms) >= 32) && sysV_assembler){
	long shiftval = (long)no(b) + norms;
	rir_ins(shnat,a,31,d);
	rir_ins(shnat,d,shiftval-31,d);
      }
      else{
	rir_ins ( shnat, a, ( long ) no ( b )+norms, d ) ;
      }
    } 
    else {
      int ar = reg_operand ( b, nsp ) ;
      if(norms!=0) rir_ins(shnat,a,norms,a);
      rrr_ins ( shnat, a, ar, d ) ;
    }
    setregalt ( aa, d ) ;
    ( void ) move ( aa, dest, nsp.fixed, 1 ) ;
    mka.regmove = d ;
    return mka;
  }

  case fplus_tag : {
    /* Floating point addition */
    ins_p i = ( isdbl ( sh ( e ) ) ? i_faddd : i_fadds ) ;
    if(!optop(e) && !exceptions_initialised /*&& !error_treatment_is_trap(e)*/){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
	    	      
    mka.regmove = fop ( e, sp, dest, i ) ;
    if(!optop(e) /*&& !error_treatment_is_trap(e)*/){
      if(mka.regmove != NOREG){
	int fval = (mka.regmove>=0)? mka.regmove:-mka.regmove;
	stf_ins(i_st,(fval-32)<<1,mem_temp(0));
      }
      check_floating_exception(e,sp,FSR_ANY);
    }
    return mka;
  }

  case fminus_tag : {
    /* Floating point subtraction */
    ins_p i = ( isdbl ( sh ( e ) ) ? i_fsubd : i_fsubs ) ;
    if(!optop(e) && !exceptions_initialised/*&& !error_treatment_is_trap(e)*/){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
    mka.regmove = fop ( e, sp, dest, i ) ;
    if(!optop(e) /*&& !error_treatment_is_trap(e)*/){
      check_floating_exception(e,sp,FSR_ANY);
      if(mka.regmove != NOREG) {
	mka.regmove = (mka.regmove<0)?-mka.regmove:mka.regmove;
	if(error_treatment_is_trap(e)) {
	  rrf_ins((isdbl(sh(e)))?i_fcmped:i_fcmpes,(mka.regmove-32)<<1,(mka.regmove-32)<<1);
	}
	else {
	 rrf_ins((isdbl(sh(e)))?i_fcmpd:i_fcmps,(mka.regmove-32)<<1,(mka.regmove-32)<<1);
	 fbr_ins(i_fbu,no(son(pt(e))));
	}
      }
    }
    return mka;
  }
    

  case fmult_tag : {
    /* Floating point multiplication */
    ins_p i = ( isdbl ( sh ( e ) ) ? i_fmuld : i_fmuls ) ;
    if(!optop(e) && !exceptions_initialised && !error_treatment_is_trap(e)){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
    mka.regmove = fop ( e, sp, dest, i ) ;
    if(!optop(e) ){
      check_floating_exception(e,sp,FSR_ANY);
      if(mka.regmove != NOREG) {
	mka.regmove = (mka.regmove<0)?-mka.regmove:mka.regmove;
	if(error_treatment_is_trap(e)) {
	  rrf_ins((isdbl(sh(e)))?i_fcmped:i_fcmpes,(mka.regmove-32)<<1,(mka.regmove-32)<<1);
	}
	else {
	 rrf_ins((isdbl(sh(e)))?i_fcmpd:i_fcmps,(mka.regmove-32)<<1,(mka.regmove-32)<<1);
	 fbr_ins(i_fbu,no(son(pt(e))));
	}
      }

    }
    return mka;
  }

  case fdiv_tag : {
    /* Floating point division */
    ins_p i = ( isdbl ( sh ( e ) ) ? i_fdivd : i_fdivs ) ;
    if(!optop(e) && !error_treatment_is_trap(e)){
      if(is_long_double(sh(e))){
	where newdest;
	exp zero_exp = getexp(sh(e),NULL,1,NULL,NULL,0,fzero_no,
			  real_tag);
	setregalt(newdest.answhere,getreg(sp.fixed));
	newdest.ashwhere.ashsize = newdest.ashwhere.ashalign = 32;
	quad_op(bro(son(e)),zero_exp,sp,newdest,-5);  /* _Q_fne */
	condrr_ins(i_be,R_O0,R_G0,no(son(pt(e))));
      }
      else{
	int divr = freg_operand(bro(son(e)),sp,getfreg(sp.flt));
	int newfr = getfreg(guardfreg(divr,sp).flt);
	fconst(newfr,0,0);
	rrf_ins(isdbl(sh(e))? i_fcmpd : i_fcmps,divr<<1,newfr<<1);
	fbr_ins(i_fbe,no(son(pt(e))));
      }
      if(!exceptions_initialised) {
	exceptions_initialised = 1;
	turn_off_trap_on_exceptions(sp);
      }
    }
    mka.regmove = fop ( e, sp, dest, i ) ;
    if(!optop(e) /*&& !error_treatment_is_trap(e)*/){
      check_floating_exception(e,sp,FSR_ANY);
      if(mka.regmove != NOREG) {
	mka.regmove = (mka.regmove<0)?-mka.regmove:mka.regmove;
	if(error_treatment_is_trap(e)) {
	  rrf_ins((isdbl(sh(e)))?i_fcmped:i_fcmpes,(mka.regmove-32)<<1,(mka.regmove-32)<<1);
	}
	else {
	 rrf_ins((isdbl(sh(e)))?i_fcmpd:i_fcmps,(mka.regmove-32)<<1,(mka.regmove-32)<<1);
	 fbr_ins(i_fbu,no(son(pt(e))));
	}
      }


    }
    return mka;
  }

  case fneg_tag :
  case fabs_tag : {
    /* Floating point monadic operations */
    freg frg ;
    int r1, a1 ;
    bool dble ;
    ins_p i ;
    if(!optop(e) && !exceptions_initialised /*&& !error_treatment_is_trap(e)*/){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
	    
    if ( use_long_double && name ( sh ( e ) ) == doublehd ) {
      if(name(e) != fabs_tag){
	quad_op ( son ( e ), NULL, sp, dest, ( int ) name ( e ) ) ;
      }
      else{	/* would it be so hard to implement _Q_abs? */
	where newdest;
	exp zero_exp;
	int no_negate = new_label();
	int negate = new_label();
	int endlab = new_label();
	setregalt(newdest.answhere,getreg(sp.fixed));
	newdest.ashwhere.ashsize = newdest.ashwhere.ashalign=32;
	zero_exp = getexp(sh(e),NULL,1,NULL,NULL,0,fzero_no,
			  real_tag);
	quad_op(son(e),zero_exp,sp,newdest,-2);
	condrr_ins(i_be,R_O0,R_G0,no_negate);
	set_label(negate);
	quad_op(son(e),NULL,sp,dest,fneg_tag);
	uncond_ins(i_b,endlab);
	set_label(no_negate);
	code_here(son(e),sp,dest);
	set_label(endlab);
      }
      return mka;
    }

    r1 = getfreg ( sp.flt ) ;
    a1 = freg_operand ( son ( e ), sp, r1 ) ;
    dble = isdbl ( sh ( e ) ) ;
    i = ( name ( e ) == fneg_tag ? i_fnegs : i_fabss ) ;

    switch ( discrim ( dest.answhere ) ) {
      case infreg : {
	frg = fregalt ( dest.answhere ) ;
	rrf_ins ( i, a1 << 1, frg.fr << 1 ) ;
	if ( dble && frg.fr != a1 ) {
	  rrf_ins ( i_fmovs, ( a1 << 1 ) + 1,
		    ( frg.fr << 1 ) + 1 ) ;
	}
	break ;
      }
      default : {
	ans a ;
	frg.fr = r1 ;
	frg.dble = dble ;
	setfregalt ( a, frg ) ;
	rrf_ins ( i, a1 << 1, r1 << 1 ) ;
	if ( dble && r1 != a1 ) {
	  rrf_ins ( i_fmovs, ( a1 << 1 ) + 1,
		    ( r1 << 1 ) + 1 ) ;
	}
	( void ) move ( a, dest, sp.fixed, 1 ) ;
	break ;
      }
    }
    mka.regmove = fregno ( dble, frg.fr ) ;
    if ( !optop ( e ) && !error_treatment_is_trap(e)) {
    }
	    
    return mka;
  }

  case float_tag : {
    /* Integer to floating point conversion */
    ans aa ;
    where w ;
    freg frg ;
    int f = GETFREG ( dest, sp ) ;

    exp in = son ( e ) ;
    int from_sz = shape_size ( sh ( in ) ) ;
    bool from_sgned = issgn ( sh ( in ) ) ;

    ins_p fl_ins = ( isdbl ( sh ( e ) ) ? i_fitod : i_fitos ) ;
    if(!optop(e) && !exceptions_initialised && !error_treatment_is_trap(e)){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
	    
    if ( use_long_double && name ( sh ( e ) ) == doublehd ) {
      quad_op ( son ( e ), NULL, sp, dest, float_tag ) ;
      return mka;
    }

    frg.fr = f ;
    frg.dble = isdbl ( sh ( e ) ) ;

    if ( from_sz == 32 && !from_sgned ) {
      /* Unsigned word to floating is tricky */
      int r = reg_operand ( in, sp ) ;
      int f1 = getfreg ( guardfreg ( f, sp ).flt ) ;
      ins_p fadd_ins = ( isdbl ( sh ( e ) ) ? i_faddd : i_fadds ) ;

		/* Load r / 2 into f */
      rir_ins ( i_srl, r, 1, R_TMP ) ;
      st_ro_ins ( i_st, R_TMP, mem_temp ( 0 ) ) ;
      ldf_ro_ins ( i_ld, mem_temp ( 0 ), f << 1 ) ;
      rrf_ins ( fl_ins, f << 1, f << 1 ) ;

		/* Double f */
      rrrf_ins ( fadd_ins, f << 1, f << 1, f << 1 ) ;

      /* Load r % 2 into f1 */
      rir_ins ( i_and, r, 1, R_TMP ) ;
      st_ro_ins ( i_st, R_TMP, mem_temp ( 0 ) ) ;
      ldf_ro_ins ( i_ld, mem_temp ( 0 ), f1 << 1 ) ;
      rrf_ins ( fl_ins, f1 << 1, f1 << 1 ) ;

		/* Add f1 to f */
      rrrf_ins ( fadd_ins, f << 1, f1 << 1, f << 1 ) ;
    } else if ( from_sz == 32 ) {
      /* Signed word to floating is easy */
      freg fint ;
      fint.fr = f ;
      fint.dble = 0 ;
      setfregalt ( w.answhere, fint ) ;
      w.ashwhere = ashof ( sh ( in ) ) ;
      ( void ) code_here ( in, sp, w ) ;
      rrf_ins ( fl_ins, f << 1, f << 1 ) ;
    } else {
      /* All others */
      int r = reg_operand ( in, sp ) ;
      /* store and load to move to float reg */
      st_ro_ins ( i_st, r, mem_temp ( 0 ) ) ;
      ldf_ro_ins ( i_ld, mem_temp ( 0 ), f << 1 ) ;
      rrf_ins ( fl_ins, f << 1, f << 1 ) ;
    }
    if(!optop(e) && !error_treatment_is_trap(e)){
      check_floating_exception(e,sp,FSR_ANY);
    }
	    
    setfregalt ( aa, frg ) ;
    ( void ) move ( aa, dest, sp.fixed, 1 ) ;
    mka.regmove = fregno ( frg.dble, f ) ;
    return mka;
  }

  case chfl_tag : {
    /* Change floating variety */
    ans aa ;
    where w ;
    freg frg ;
    bool dto = isdbl ( sh ( e ) ) ;
    bool dfrom = isdbl ( sh ( son ( e ) ) ) ;
    if(!optop(e) && !exceptions_initialised /*&& !error_treatment_is_trap(e)*/){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
	    
   if (use_long_double) {
    if ( name ( sh ( e ) ) == doublehd ) {
      if ( name ( sh ( son ( e ) ) ) == doublehd ) {
	/* no change in representation */
	return make_code ( son ( e ), sp, dest, exitlab ) ;
      }
      quad_op ( son ( e ), NULL, sp, dest, chfl_tag ) ;
      return mka;
    } else if ( name ( sh ( son ( e ) ) ) == doublehd ) {
      int o = ( dto ? 100 : 101 ) ;
      quad_op ( son ( e ), NULL, sp, dest, o ) ;
      frg.fr = 0 ;
      frg.dble = dto ;
      setfregalt ( aa, frg ) ;
      ( void ) move ( aa, dest, sp.fixed, 1 ) ;
      if(!optop(e)){
	check_floating_exception(e,sp,FSR_ANY);
      }
      return mka;
    }
   }

    if ( !dto && !dfrom ) {
      /* no change in representation */
      return make_code ( son ( e ), sp, dest, exitlab ) ;
    } else {
      if ( discrim ( dest.answhere ) == infreg ) {
	frg = fregalt ( dest.answhere ) ;
      } else {
	frg.fr = getfreg ( sp.flt ) ;
      }
      frg.dble = dfrom ;
      setfregalt ( aa, frg ) ;
      w.answhere = aa ;
      w.ashwhere = ashof ( sh ( son ( e ) ) ) ;
      ( void ) code_here ( son ( e ), sp, w ) ;
      if (!dto || !dfrom){
	if(!sysV_assembler && !optop(e)) {
	  outs("\t.optim\t\"-O0\"\n");/*as -O2 removes fsto[ds] ??*/
	}
	rrf_ins ( ( dfrom ? i_fdtos : i_fstod ), frg.fr << 1,
		  frg.fr << 1 ) ;
      }
      frg.dble = dto ;
      setfregalt ( aa, frg ) ;
      ( void ) move ( aa, dest, sp.fixed, 1 ) ;
      mka.regmove = fregno ( frg.dble, frg.fr ) ;
      if(!optop(e)){
	check_floating_exception(e,sp,FSR_ANY);
      }
      return mka;
    }
  }

  case and_tag : {
    /* Bitwise and */
    mka.regmove = comm_op ( e, sp, dest, i_and ) ;
    return mka;
  }

  case or_tag : {
    /* Bitwise or */
    mka.regmove = comm_op ( e, sp, dest, i_or ) ;
    return mka;
  }

  case xor_tag : {
    /* Bitwise xor */
    mka.regmove = comm_op ( e, sp, dest, i_xor ) ;
    return mka;
  }

  case not_tag : {
    /* Bitwise not */
    mka.regmove = monop ( e, sp, dest, i_not ) ;
    return mka;
  }

  case locptr_tag :
  {
    int ptr = reg_operand(son(e),sp);
    int ansr = regfrmdest(&dest,sp);
    baseoff b;
    ans aa;
    b.base = ptr;
    b.offset = -3*PTR_SZ>>3;
    ld_ro_ins(i_ld,b,ansr);
    setregalt(aa,ansr);
    mka.regmove = move(aa,dest,guardreg(ansr,sp).fixed,0);
    return mka;
  }
  

  case real_tag :
  case string_tag : {
    /* Evaluated constants */
    ans aa ;
    instore isa ;
    bool sgned = issgn ( sh ( e ) ) ;
    if ( shape_size ( sh ( e ) ) >= 32 ) sgned = 1 ;
    isa = evaluated ( e, 0, 1 ) ;
    setinsalt ( aa, isa ) ;
    mka.regmove = move ( aa, dest, sp.fixed, sgned ) ;
    return mka;
  }

  case val_tag : {
    /* Load constant */
    int r ;
    space nsp ;
    if(name(sh(e)) == u64hd || name(sh(e)) == s64hd){
      instore is;
      flt64 bval;
      ans aa;
      where newdest;
      int rt = getreg(sp.fixed);
      nsp = guardreg (rt, sp);
      /*assert(discrim(dest.answhere) == notinreg);*/
      newdest = dest;
      if (discrim(dest.answhere) == notinreg &&
		(is = insalt (dest.answhere), !is.adval)) {
	/* destination is indirect */
	int r = getreg ( nsp.fixed ) ;
	ld_ins ( i_ld, is.b, r ) ;
	nsp = guardreg ( r, nsp ) ;
	is.adval = 1 ;
	is.b.base = r ;
	is.b.offset = 0 ;
	setinsalt ( newdest.answhere, is ) ;
      }
      bval = exp_to_f64(e);
      ir_ins(i_mov,bval.small,rt);
      setregalt(aa,rt);
      newdest.ashwhere.ashsize = newdest.ashwhere.ashalign = 32;
      (void)move(aa,newdest,nsp.fixed,1);
      newdest.answhere.val.instoreans.b.offset += 4;
      ir_ins(i_mov,bval.big,rt);
      (void)move(aa,newdest,nsp.fixed,1);
      return mka;
    }
    else{
      long v = no ( e ) ;
      if ( v == 0 ) goto null_tag_case ;
      if ( issgn ( sh ( e ) ) ) {
	long sz = shape_size ( sh ( e ) ) ;
	if ( sz == 8 ) {
	  v &= 0xff ;
	  v -= ( ( v & 0x80 ) << 1 ) ;
	} else if ( sz == 16 ) {
	  v &= 0xffff ;
	  v -= ( ( v & 0x8000 ) << 1 ) ;
	}
      }
      switch ( discrim ( dest.answhere ) ) {
	case inreg : {
	  r = regalt ( dest.answhere ) ;
	  ir_ins ( i_mov, v, r ) ;
	  break ;
	}
	default : {
	  ans aa ;
	  if ( v == 0 ) {
	    r = R_G0 ;
	  } else {
	    r = getreg ( sp.fixed ) ;
	    ir_ins ( i_mov, v, r ) ;
	  }
	  setregalt ( aa, r ) ;
	  ( void ) move ( aa, dest, guardreg ( r, sp ).fixed, 1 ) ;
	}
      }
      mka.regmove = r ;
      return mka;
    }
  }

  case null_tag :
    null_tag_case : {
      /* Load zero */
      ans aa ;
      setregalt ( aa, R_G0 ) ;
      mka.regmove = move ( aa, dest, sp.fixed, 1 ) ;
      return mka;
    }

  case round_tag : {
    /* Floating point to integer conversion */
    ans aa ;
    space nsp ;
    int li, ln = 1 ;
    int lab1, lab2, error_lab;
    int sfr = -1, dfr, tfr, error_set = 1;
    int r = GETREG ( dest, sp ) ;
    int s = shape_size ( sh ( son ( e ) ) ) ;

	    /* Rounding mode : 0 = to near, 1 = up, 2 = down, 3 = to zero */
    int rm = ( int ) round_number ( e ) ;
    bool check_ranges = !optop(e);
    if (r == R_G0) r = getreg(sp.fixed);

    if(!optop(e)) {
      if (error_treatment_is_trap(e)) {
	error_lab = new_label ();
	error_set = 0;
      }
      else
	error_lab = no(son(pt(e)));
    }
    if(!optop(e) && !exceptions_initialised /* && !error_treatment_is_trap(e) */){
      exceptions_initialised = 1;
      turn_off_trap_on_exceptions(sp);
    }
    /* Get two floating registers */
    if ( use_long_double && name ( sh ( son ( e ) ) ) == doublehd ) {
      quad_op ( son ( e ), NULL, sp, dest, 100 ) ;
      sfr = getfreg ( sp.flt ) ;
      rrf_ins ( i_fmovd, 0, sfr << 1 ) ;
    } else {
      sfr = freg_operand ( son ( e ), sp, getfreg ( sp.flt ) ) ;
    }
    nsp = guardfreg ( sfr, sp ) ;
    dfr = getfreg ( nsp.flt ) ;

    /* Apart from round signed to zero we need an extra register */
    if ( rm != f_toward_zero || name ( sh ( e ) ) == ulonghd ) {
      nsp = guardfreg ( dfr, nsp ) ;
      tfr = getfreg ( nsp.flt ) ;
      if ( s == 32 ) {
	rrf_ins ( i_fstod, sfr << 1, tfr << 1 ) ;
	s = 64 ;
      } else {
	rrf_ins ( i_fmovd, sfr << 1, tfr << 1 ) ;
      }
    } else {
      tfr = sfr ;
    }

    /*
      The default rounding mode is RND_ZERO.  If we let
      NOT_INT ( d ) be 0 if d is an integer and 1 otherwise
      then the other rounding modes may be expressed as :
      
      RND_NEAR ( d ) :
      d >= 0.0 ? RND_ZERO ( d + 0.5 ) : RND_ZERO ( d - 0.5 )
      
      RND_UP ( d ) :
      d >= 0.0 ? RND_ZERO ( d ) + NOT_INT ( d ) : RND_ZERO ( d )
      
      RND_DOWN ( d ) :
      d >= 0.0 ? RND_ZERO ( d ) : RND_ZERO ( d ) - NOT_INT ( d )
      */

	    /* The non-standard modes have two cases */
    if ( rm != f_toward_zero && rm != f_round_as_state) {
      lab1 = new_label () ;
      lab2 = new_label () ;
      /* Is tfr >= 0.0? */
      fconst ( dfr, 0, 0 ) ;
      rrf_ins ( i_fcmpd, tfr << 1, dfr << 1 ) ;
      fbr_ins ( i_fbge, lab1 ) ;
      if ( rm == f_to_nearest ) {
	/* For round to near add +/- 0.5 to tfr */
	fconst ( dfr, -1075838976, 0 ) ;	/* -0.5 */
	uncond_ins ( i_ba, lab2 ) ;
	set_label ( lab1 ) ;
	fconst ( dfr, 1071644672, 0 ) ;	/* 0.5 */
	set_label ( lab2 ) ;
	rrrf_ins ( i_faddd, tfr << 1, dfr << 1, tfr << 1 ) ;
      } else {
	/* The others genuinely have two cases */
	ln = 2 ;
      }
    }

    for ( li = 0 ; li < ln ; li++ ) {
      /* For each case ... */
      if ( name ( sh ( e ) ) == ulonghd ) {
	/* Floating to unsigned conversion is tricky */
	int ulab1 = new_label () ;
	int ulab2 = new_label () ;
	/* Compare tfr with	2147483648.0 ... */
	fconst ( dfr, 1105199104, 0 ) ;
	rrf_ins ( i_fcmpd, tfr << 1, dfr << 1 ) ;
	fbr_ins ( i_fbge, ulab1 ) ;
	/* ... if it is smaller */

	/* if it is less than zero, and mode is towards smaller */
	if(!optop(e) /* && !error_treatment_is_trap(e) */
	   && (rm == f_toward_zero || rm == f_toward_smaller)) {
	  if(rm == f_toward_smaller) {
	    /* check .lt. -0.5 */
	    fconst(dfr,-1075838976,0);
	  }
	  else {
	    /* check .le. -1.0 */
	    fconst(dfr,-1074790400,0);
	  }
	  rrf_ins(i_fcmpd,tfr<<1,dfr<<1);
	  fbr_ins(i_fbl,error_lab);
	}
	rrf_ins ( i_fdtoi, tfr << 1, dfr << 1 ) ;
	stf_ins ( i_st, dfr << 1, mem_temp ( 0 ) ) ;
	ld_ro_ins ( i_ld, mem_temp ( 0 ), r ) ;
	uncond_ins ( i_ba, ulab2 ) ;
	/* ... if it is bigger */
	set_label ( ulab1 ) ;
	rrrf_ins ( i_fsubd, tfr << 1, dfr << 1, tfr << 1 ) ;
	rrf_ins ( i_fdtoi, tfr << 1, dfr << 1 ) ;
	stf_ins ( i_st, dfr << 1, mem_temp ( 0 ) ) ;
	ld_ro_ins ( i_ld, mem_temp ( 0 ), r ) ;
	rir_ins ( i_xor, r, ( long ) ( 0x80000000L ), r ) ;
	set_label ( ulab2 ) ;
      } else {
	/* Floating to signed conversion is easy */
	ins_p ins = ( s == 32 ? i_fstoi : i_fdtoi ) ;
	if(check_ranges && (name(sh(e))==slonghd || name(sh(e))==ulonghd)) {
	  check_range_and_do_error_jump(sh(e),tfr,error_lab,
					guardfreg(tfr,sp),rm);
	}
	rrf_ins ( ins, tfr << 1, dfr << 1 ) ;
	stf_ins ( i_st, dfr << 1, mem_temp ( 0 ) ) ;
	ld_ro_ins ( i_ld, mem_temp ( 0 ), r ) ;
	
      }
      /* Deal with tricky rounding modes */
      if ( rm == f_toward_larger || rm == f_toward_smaller ) {
	/* Pick the right branch */
	if ( ( rm == f_toward_larger && li == 1 ) || 
	     ( rm == f_toward_smaller && li == 0 ) ) {
	  /* Get the integer into dfr */
	  rrf_ins ( i_fitod, dfr << 1, dfr << 1 ) ;
	  /* Is tfr equal to its integer part? */
	  rrf_ins ( i_fcmpd, tfr << 1, dfr << 1 ) ;
	  fbr_ins ( i_fbe, lab2 ) ;
	  /* If not adjust the result by one */
	  if(!optop(e) && name(sh(e)) == ulonghd) {
	    /* watch out for unwanted wrap on addition */
	    condri_ins(i_be,r,-1,error_lab);
	  }
	  rir_ins ( i_add, r, ( long ) ( rm == f_toward_larger?1:-1 ),r ) ;
	}
	/* Deal with the two cases */
	if ( li == 0 ) {
	  uncond_ins ( i_ba, lab2 ) ;
	  set_label ( lab1 ) ;
	} else {
	  set_label ( lab2 ) ;
	}
      }
    }

	
    /* Shorten to type if needed */
    switch ( name ( sh ( e ) ) ) {
      case ucharhd : {
	if (check_ranges){
	  test_unsigned(r,255,error_lab);
	}
	rir_ins ( i_and, r, 0xff, r ) ;
	break ;
      }
      case scharhd : {
	if (check_ranges){
	  test_signed(r,-128,127,error_lab);
	}
	rir_ins ( i_sll, r, 24, r ) ;
	rir_ins ( i_sra, r, 24, r ) ;
	break ;
      }
      case uwordhd : {
	if(check_ranges){
	  test_unsigned(r,0xffff,error_lab);
	}
	rir_ins ( i_and, r, 0xffff, r ) ;
	break ;
      }
      case swordhd : {
	if(check_ranges){
	  test_signed(r,-0x8000,0x7fff,error_lab);
	}
	rir_ins ( i_sll, r, 16, r ) ;
	rir_ins ( i_sra, r, 16, r ) ;
	break ;
      }
      default: {
	if(!optop(e))
	  uncond_ins(i_bvs,error_lab);
      }
    }
    if (!error_set) {
      int overlab = new_label ();
      uncond_ins (i_b, overlab);
      set_label (error_lab);
      assert (!optop(e) && error_treatment_is_trap(e));
      do_exception (f_overflow);
      set_label (overlab);
    }
    setregalt ( aa, r ) ;
    mka.regmove = move ( aa, dest, sp.fixed, 1 ) ;
    return mka;
  }

  case int_to_bitf_tag : {
    /* Integer to bitfield conversion */
    ans aa ;
    space nsp ;
    int size_res = shape_size ( sh ( e ) ) ;
    int size_op = shape_size ( sh ( son ( e ) ) ) ;
    int r = reg_operand ( son ( e ), sp ) ;
    assert(0);
	    
    if ( size_res != size_op && size_res != 32 ) {
      int destr = GETREG ( dest, sp ) ;
      rir_ins ( i_and, r, ( long ) ( ( 1 << size_res ) - 1 ),
		destr ) ;
      r = destr ;
    }
    /* r is appropriately truncated operand */
    nsp = guardreg ( r, sp ) ;
    setregalt ( aa, r ) ;
    ( void ) move ( aa, dest, nsp.fixed, 0 ) ;
    return mka;
  }

  case bitf_to_int_tag : {
    /* Bitfield to integer conversion */
    where w ;
    int r = GETREG ( dest, sp ) ;
    long sz = shape_size ( sh ( son ( e ) ) ) ;
    bool src_sgned = issgn ( sh ( son ( e ) ) ) ;
    bool target_sgned = issgn ( sh ( e ) ) ;
#if 0
    /* Some cases are simple moves */
    if ( ( name ( son ( e ) ) == cont_tag ||
	   name ( son ( e ) ) == name_tag ) &&
	 ( sz == 8 || sz == 16 || sz == 32 ) ) {
      where intreg ;
      int olds = sh ( son ( e ) ) ;
      setregalt ( intreg.answhere, r ) ;
      intreg.ashwhere.ashsize = sz ;
      intreg.ashwhere.ashalign = sz ;
      sh ( son ( e ) ) = sh ( e ) ;
      w = locate ( son ( e ), sp, sh ( e ), r ) ;
      ( void ) move ( w.answhere, intreg, guard ( w, sp ).fixed,
		      issgn ( sh ( e ) ) ) ;
      ( void ) move ( intreg.answhere, dest, sp.fixed, 1 ) ;
      sh ( son ( e ) ) = olds ;
      keepreg ( e, r ) ;
      return mka;
    }
#endif
    /* Do shift/and */
    setregalt ( w.answhere, r ) ;
    w.ashwhere = ashof ( sh ( son ( e ) ) ) ;
    ( void ) code_here ( son ( e ), sp, w ) ;

    if ( sz != 32 && src_sgned != target_sgned ) {
      /* Get correct sign */
      if ( target_sgned ) {
	long shift_by = ( long ) ( 32 - sz ) ;
	rir_ins ( i_sll, r, shift_by, r ) ;
	rir_ins ( i_sra, r, shift_by, r ) ;
      } else {
	long and_by = ( long ) ( ( 1 << sz ) - 1 ) ;
	rir_ins ( i_and, r, and_by, r ) ;
      }
    }
    ( void ) move ( w.answhere, dest, guardreg ( r, sp ).fixed, 0 ) ;
    keepreg ( e, r ) ;
    return mka;
  }
  case alloca_tag : {
    mka.lab = specialmake ( (checkalloc(e))?6:5,son(e), sp, dest, exitlab ) ;
    return mka;
  }

  case last_local_tag: {
    int r = regfrmdest(&dest,sp);
    ans aa;
    rir_ins(i_add,R_SP,proc_state.maxargs>>3,r);
    setregalt(aa,r);
    mka.regmove = move(aa,dest,sp.fixed,1);
    return mka;
  }
	   
  case local_free_tag: {
    exp s = son(e);
    int r = reg_operand(s,sp);
    exp off = bro(s);
    fprintf(as_file,"!local free tag \n");
    if(name(off) == val_tag){
      assert(name(sh(off)) == offsethd);
      rir_ins(i_add,r,((no(off)>>3)+7)&~7,r);
    }
    else{
      int rtmp = reg_operand(off,guardreg(r,sp));
      rir_ins(i_add,rtmp,7,rtmp);
      rir_ins(i_and,rtmp,~7,rtmp);
      rrr_ins(i_add,r,rtmp,r);
    }
    rir_ins(i_sub,r,proc_state.maxargs>>3,R_SP);
    return mka;
  }
  case local_free_all_tag: {
    rir_ins(i_sub,R_FP,proc_state.frame_size,R_SP);
    return mka;
  }
		       
  case compound_tag : {
    /* Compound values */
    int r ;
    space nsp ;
    instore str ;
    exp t = son ( e ) ;
    
    /* Initialse bitfield by constructing and appropriate constant */
    /* Must do it this way as SPARC has no bitfield instructions. */
    /* Other compounds are initialised from register values below */
    if ( has_bitfield ( e ) ) {
      ans aa ;
      instore isa ;

      /* word-align bitfields for ease of access */
      if ( dest.ashwhere.ashalign < 32 ) {
	dest.ashwhere.ashalign = 32 ;
      }

      /* generate constant value... */
      fix_nonbitfield ( e ) ;
      isa = evaluated ( e, 0, 1 ) ;
      /* ... and place it in dest */
      setinsalt ( aa, isa ) ;
      mka.regmove = move ( aa, dest, sp.fixed, 1 ) ;
      return mka;
    }

    nsp = sp ;
    switch ( discrim ( dest.answhere ) ) {

      case notinreg : {
	str = insalt ( dest.answhere ) ;
	if ( !str.adval ) {
	  int r2 = getreg ( sp.fixed ) ;
	  nsp = guardreg ( r2, sp ) ;
	  ld_ins ( i_ld, str.b, r2 ) ;
	  str.adval = 1 ;
	  str.b.base = r2 ;
	  str.b.offset = 0 ;
	}
	for ( ; ; ) {
	  where newdest ;
	  instore newis ;
	  newis = str ;
	  newis.b.offset += no ( t ) ;

	  setinsalt ( newdest.answhere, newis ) ;
	  newdest.ashwhere = ashof ( sh ( bro ( t ) ) ) ;
	  ( void ) code_here ( bro ( t ), nsp, newdest ) ;
	  if ( last ( bro ( t ) ) ) return mka;
	  t = bro ( bro ( t ) ) ;
	}
	/* NOT REACHED */
      }

      case insomereg : {
	int *sr = someregalt ( dest.answhere ) ;
	if ( *sr != -1 ) error(ERROR_SERIOUS,  "Illegal register" ) ;
	*sr = getreg ( sp.fixed ) ;
	setregalt ( dest.answhere, *sr ) ;
	/* FALL THROUGH */
      }

      case inreg : {
	long v ;
	int null_dest;
	int bits_used = 0;
		    
	( void ) code_here ( bro ( t ), sp, dest ) ;
	r = regalt ( dest.answhere ) ;
	null_dest = (r == R_G0);
	/* if the destination is G0, then don't
	   try to put out the compound, but do
	   evaluate the arguments 
	   Further, compounds > 32 bits into G0 are
	   valid, others are NOT */

	assert ( name ( t ) == val_tag ) ;
	v = no ( t ) ;
	if ( v != 0 ) {
	  if ( al2 ( sh ( t ) ) >= 8 ) v <<= 3 ;
	  if (!null_dest)
	    rir_ins ( i_sll, r, v, r ) ;
	}
	bits_used += (shape_size(sh(t)) + v);
	assert (null_dest || bits_used <= 32);
		    
	nsp = guardreg ( r, sp ) ;
	while ( !last ( bro ( t ) ) ) {
	  int z ;
	  t = bro ( bro ( t ) ) ;
	  assert ( name ( t ) == val_tag ) ;
	  z = reg_operand ( bro ( t ), nsp ) ;
	  v = no ( t ) ;
	  if ( v != 0 ) {
	    if ( al2 ( sh ( t ) ) >= 8 ) v <<= 3 ;
	    if (!null_dest)
	      rir_ins ( i_sll, z, v, z ) ;
	  }
	  bits_used += (shape_size(sh(t)) + v);
	  assert (null_dest || bits_used <= 32);

	  if (!null_dest)
	    rrr_ins ( i_or, r, z, r ) ;
	}
	return mka;
      }
      default:
      {
	/* fall through to fail */
      }
    }
    error(ERROR_SERIOUS,  "Illegal compound expression" ) ;
    return mka;
  }

  case nof_tag :
  case concatnof_tag : {
    /* Arrays */
    space nsp ;
    instore str ;
    int r, disp = 0 ;
    exp t = son ( e ) ;
	    
    nsp = sp ;
    switch ( discrim ( dest.answhere ) ) {
      case notinreg : {
	str = insalt ( dest.answhere ) ;
	if ( !str.adval ) {
	  int r2 = getreg ( sp.fixed ) ;
	  nsp = guardreg ( r2, sp ) ;
	  ld_ins ( i_ld, str.b, r2 ) ;
	  str.adval = 1 ;
	  str.b.base = r2 ;
	  str.b.offset = 0 ;
	}
	for ( ; ; ) {
	  where newdest ;
	  instore newis ;
	  if(t == NULL) return mka;
	  newis = str ;
	  newis.b.offset += disp ;
	  setinsalt ( newdest.answhere, newis ) ;
	  newdest.ashwhere = ashof ( sh ( t ) ) ;
	  ( void ) code_here ( t, nsp, newdest ) ;
	  if ( last ( t ) ) return mka;
	  disp += ( rounder ( shape_size ( sh ( t ) ),
			      shape_align ( sh ( bro ( t ) ) ) ) >> 3 ) ;
	  t = bro ( t ) ;
	}
	/* NOT REACHED */
      }

      case insomereg : {
	int *sr = someregalt ( dest.answhere ) ;
	if ( *sr != -1 ) error(ERROR_SERIOUS,  "Illegal register" ) ;
	*sr = getreg ( sp.fixed ) ;
	setregalt ( dest.answhere, *sr ) ;
	/* FALL THROUGH */
      }

      case inreg : {
	if (t == NULL) return mka;
	( void ) code_here ( t, sp, dest ) ;
	r = regalt ( dest.answhere ) ;
	nsp = guardreg ( r, sp ) ;
	while ( !last ( t ) ) {
	  int z ;
	  disp += rounder ( shape_size ( sh ( t ) ),
			    shape_align ( sh ( bro ( t ) ) ) ) ;
	  t = bro ( t ) ;
	  z = reg_operand ( t, nsp ) ;
	  rir_ins ( i_sll, z, ( long ) disp, z ) ;
	  rrr_ins ( i_or, r, z, r ) ;
	}
	return mka;
      }
      default: {
	/* fall through to fail */
      }
    }
    error(ERROR_SERIOUS,  "Illegal array expression" ) ;
    return mka;
  }

  case ncopies_tag : {
    space nsp ;
    instore str ;
    int i, r, disp = 0 ;
    exp t = son ( e ) ;

    nsp = sp ;
    switch ( discrim ( dest.answhere ) ) {

      case notinreg : {
	str = insalt ( dest.answhere ) ;
	if (!str.adval) {
	  int r2 = getreg ( sp.fixed ) ;
	  nsp = guardreg ( r2, sp ) ;
	  ld_ins ( i_ld, str.b, r2 ) ;
	  str.adval = 1 ;
	  str.b.base = r2 ;
	  str.b.offset = 0 ;
	}
	for ( i = 1 ; i <= no ( e ) ; i++ ) {
	  where newdest ;
	  instore newis ;
	  newis = str ;
	  newis.b.offset += disp ;
	  setinsalt ( newdest.answhere, newis ) ;
	  newdest.ashwhere = ashof ( sh ( t ) ) ;
	  (void)code_here ( t, nsp, newdest ) ;
	  disp += ( rounder ( shape_size ( sh ( t ) ),
			      shape_align ( sh ( t ) ) ) >> 3 ) ;
	}
	return mka;
      }

      case insomereg : {
	int *sr = someregalt ( dest.answhere ) ;
	if ( *sr != -1 ) error(ERROR_SERIOUS,  "Illegal register" ) ;
	*sr = getreg ( sp.fixed ) ;
	setregalt ( dest.answhere, *sr ) ;
	/* FALL THROUGH */
      }

      case inreg : {
	( void ) code_here ( t, sp, dest ) ;
	r = regalt ( dest.answhere ) ;
	nsp = guardreg ( r, sp ) ;
	for ( i = 1 ; i <= no ( e ) ; i++ ) {
	  int z ;
	  disp += rounder ( shape_size ( sh ( t ) ),
			    shape_align ( sh ( t ) ) ) ;
	  z = reg_operand ( t, nsp ) ;
	  rir_ins ( i_sll, z, ( long ) disp, z ) ;
	  rrr_ins ( i_or, r, z, r ) ;
	}
	return mka;
      }
      default:
      {
	/* fall through to fail */
      }
    }
    error(ERROR_SERIOUS,  "Illegal array expression" ) ;
    return mka;
  }

  case ident_tag : {
    where placew ;
    int r = NOREG ;
    bool remember = 0 ;

    if ( name ( sh ( son ( e ) ) ) == ptrhd &&
	 name ( son ( e ) ) != cont_tag ) {
      /* we should never be identifing a pointer to bits */
      if ( al1 ( sh ( son ( e ) ) ) == 1 ) {
	/* ??? changed al1 to al2 here */
	/* and back ???? */
#if 0
	error(ERROR_SERIOUS,  "ident ref bits" ) ;
#endif
      }
    }

    if ( props ( e ) & defer_bit ) {
      /* The tag of this declaration is transparently 
	 identified with its definition, without reserving 
	 more space. Skip it for code generation.  It may be
	 a renaming of a parameter though, so we can 
	 generate a .stab. */
      return make_code ( bro ( son ( e ) ), sp, dest, exitlab ) ;
    }

    if ( son ( e ) == NULL ) {
      /* historical - unused tags are now removed cleanly */
      placew = nowhere ;
    } 
    else if (name(son(e)) == caller_name_tag){
      /*      int disp = ((no(son(son(e)))>>3)<<4) +R_SP;*/
      exp ote = find_ote(e,no(son(e)));
      
      no(e) = ((no(ote)>>3)<<4) + R_SP;
      placew = nowhere;
    }
    else {
      int n = no ( e ) ;
      ash a ;
      a = ashof ( sh ( son ( e ) ) ) ;
      /* unlike mips, do this first as params in fixed regs
	 treated differently */
      if ( isparam ( e ) ) {
	if(name(son(e)) != formal_callee_tag){
	  instore is ;
	  /* bit disp of params */
	  int n2 = no ( son ( e ) ) ;

	  if ( props ( son ( e ) ) > 0 ) {
	    /* param in input reg given by props(son(e) ) */
	    int end = rounder ( no ( son ( e ) ) +
				shape_size ( sh ( son ( e ) ) ), 32 );

	    if ( no ( e ) == R_NO_REG ) {
	      /* store input regs used (may be more than one) */
	      int max_reg;
	      bool struct_par =
		!( is_floating ( name ( sh ( son ( e ) ) ) ) ||
		   valregable ( sh ( son ( e ) ) ) ) ;
	      if ((gencompat && May_have_callees) || (!gencompat && in_general_proc)) {
		if(Has_vcallees) {
		  max_reg = 4;
		}
		else {
		  max_reg = 5;
		}
	      }
	      else {
		max_reg = 6;
	      }

				/* once required !struct_par */
	      is.adval = 1 ;
	      is.b.base = R_FP ;
	      is.b.offset = n2 + proc_state.params_offset ;
	      setinsalt ( placew.answhere, is ) ;
	      no ( e ) = n2 * 2 + R_FP ;
	      if ( !struct_par ) {
		int i = n2 ;
		while ( ( i < end ) &&
			( i < ( 32 * ( max_reg) ) ) ) {
				/* round-down to word boundary */
		  i &= ~31 ;
		  is.b.offset =
		    ( i + proc_state.params_offset ) >> 3 ;
		  st_ins ( i_st, R_I0 + ( i >> 5 ), is.b ) ;
		  i += 32 ;
		}
	      } 
              else {
				/* should use SVR4 ABI */
				/* do not stack struct/unions */
	      }
	    } 
	    else {
	      /* use register */
	      if ( ( props ( e ) & infreg_bits ) != 0 ) {
		freg frg ;
		frg.fr = ( int ) props ( son ( e ) ) ;
		frg.dble = ( bool ) ( a.ashsize == 64 ) ;
		setfregalt ( placew.answhere, frg ) ;
	    } 
            else {
		setregalt ( placew.answhere,(int)props( son ( e ) ) ) ;
	      }
	    }

	    /* is last param a vararg in reg? */
	    if ( ((!Has_no_vcallers) || isvis ( e )) && props ( son ( e ) ) != 0 &&
		 /*pt ( e ) != NULL &&*/ 
		 last_param ( e ) ) {
	      /* dump *all* remaining input regs to stack
		 for varargs */
	      int r2 = end ;
	      int max_reg;
	      if ((gencompat && May_have_callees) || (!gencompat && in_general_proc)) {
		if(Has_vcallees) {
		  max_reg = 4;
		}
		else {
		  max_reg = 5;
		}
	      }
	      else {
		max_reg = 6;
	      }
	      is.adval = 1 ;
	      is.b.base = R_FP ;
	      while ( r2 < ( 32 * ( max_reg)) ) {
		is.b.offset =
		  ( r2 + proc_state.params_offset ) >> 3 ;
		st_ins ( i_st, R_I0 + ( r2 >> 5 ), is.b ) ;
		r2 += 32 ;
	      }
	    }
	  } 
	  else {
	    /* parameter on the stack - offset given by n2 */
	    is.adval = 1 ;
	    is.b.base = R_FP ;
	    is.b.offset = ( n2 + proc_state.params_offset ) >> 3 ;
	    setinsalt ( placew.answhere, is ) ;
	    no ( e ) = n2 * 2 + R_FP ;
	    remember = 1 ;
	  }
	}
	else{
	  no(e) = no(son(e)) +BITS2BYTES(-proc_state.locals_offset+ 
					 proc_state.frame_size)+
	    (/*Has_vcallees?local_reg:*/R_FP);
	  placew = nowhere;
	}
      }
      else if ( ( props ( e ) & inreg_bits ) != 0 ) {
	/* tag in some fixed pt reg */
	if ( n == 0 ) {
	  /* if it hasn't been already allocated into a s-reg
	     allocate tag into fixed t-reg */
	  long s = sp.fixed ;
	  if ( props ( e ) & notparreg ) {
	    s |= PARAM_TREGS ;
	  }
	  if ( props ( e ) & notresreg ) {
	    s |= RMASK ( R_O0 ) ;
	  }
 	  n = getreg ( s ) ;
	  no ( e ) = n ;
	} 
	else if ( n == R_O0 ) {
	  /* use result reg optimisation */
	  assert ( ! ( props ( e ) & notparreg ) ) ;
	  /* just as an error check */
	  ( void ) needreg ( R_O0, sp ) ;
	} 
	else {
	  assert ( IS_SREG ( n ) ) ;
	}
	setregalt ( placew.answhere, n ) ;
      } 
      else if ( ( props ( e ) & infreg_bits ) != 0 ) {
	/* tag in some float reg */
	freg frg ;

	if ( n == 0 ) {
	  /* if it hasn't been already allocated into a s-reg
	     allocate tag into float-reg ...  */
	  long s = sp.flt ;
	  if ( props ( e ) & notparreg ) {
	    s |= PARAM_FLT_TREGS ;	/* LINT */
	  }
	  n = getfreg ( s ) ;
	  no ( e ) = n ;
	} 
	else if ( n == R_DEFER_F0 ) {
	  n = R_F0 ;
	  no ( e ) = R_F0 ;
	} 
	else {
	  assert ( IS_FLT_SREG ( n ) ) ;	/* LINT */
	}
	frg.fr = n ;
	frg.dble = ( bool ) ( a.ashsize == 64 ) ;
	setfregalt ( placew.answhere, frg ) ;
      } 
      else {
	/* allocate on stack */
	instore is ;

	is.b = boff ( e ) ;
	is.adval = 1 ;
	setinsalt ( placew.answhere, is ) ;
	remember = 1 ;
      }
      placew.ashwhere = a ;
    }		
    /* evaluate the initialisation of tag, putting it into
       place allocated */
    if(isparam(e) && name(son(e)) == formal_callee_tag){
      exp se = son(e);
      exp d = e;
      if((props(d) & inanyreg)!=0){
	ans a;
	instore is;
	is.b.base = R_FP;
	is.b.offset = (no(e)-callee_size)>>3;
	is.adval = 0;
	setinsalt(a,is);
	(void)move(a,placew,sp.fixed,is_signed(sh(se)));
      }
    }
    else
      r = code_here ( son ( e ), sp, placew ) ;

    if ( remember && r != NOREG ) {
      /* if it was temporarily in a register, track it to
	 optimise future access */
      exp nm = pt(e);
      while (nm) {	/* find a name_tag of correct shape */
#ifdef NEWDIAGS
	if (isdiaginfo(nm))
	  ;
	else
#endif
	if ( isvar ( e ) && name(sh(nm)) == ptrhd && 
		al1(sh(nm)) == shape_align(sh(son(e)))) {
	  keepcont ( nm, r ) ;
	  break;
	} 
	else
	if ( !isvar ( e ) && eq_shape (sh(nm), sh(son(e)))) {
	  keepreg ( nm, r ) ;
	  break;
	}
	nm = pt(nm);
      }
    }

    /* and evaluate the body of the declaration */
    assert ( bro ( son ( e ) ) != e ) ;
    mka = make_code ( bro ( son ( e ) ), guard ( placew, sp ),
		      dest, exitlab ) ;
    return mka;
  }

  case cond_tag : {
    exp first = son ( e ) ;
    exp second = bro ( son ( e ) ) ;
    exp test ;

    if ( discrim ( dest.answhere ) == insomereg ) {
      /* must make choice of register to contain answer to cond */
      int *sr = someregalt ( dest.answhere ) ;
      if ( *sr != -1 ) error(ERROR_SERIOUS,  "somereg *2" ) ;
      *sr = getreg ( sp.fixed ) ;
      setregalt ( dest.answhere, *sr ) ;
    }

    if ( name ( first ) == goto_tag && pt ( first ) == second ) {
      /* first is goto second */
      no ( son ( second ) ) = 0 ;
      return make_code ( second, sp, dest, exitlab ) ;
    }
#if 0
    /* not correct, see email from Mark Brandreth DRA, 22 Jan 92 */
    else if ( name ( first ) == test_tag && pt ( first ) == second ) {
      /* nugatory test */
      no ( son ( second ) ) = 0 ;
      ( void ) code_here ( son ( first ), sp, nowhere ) ;
      ( void ) code_here ( bro ( son ( first ) ), sp, nowhere ) ;
      return make_code ( second, sp, dest, exitlab ) ;
    }
#endif
    else if ( name ( second ) == labst_tag &&
	      name ( bro ( son ( second ) ) ) == top_tag ) {
      /* second is empty */
      int endl = ( exitlab == 0 ) ? new_label () : exitlab ;
      no ( son ( second ) ) = endl ;
      make_code ( first, sp, dest, endl ) ;
      mka.lab = endl ;
      return mka;
    } 
    else if ( name ( second ) == labst_tag &&
		name ( bro ( son ( second ) ) ) == goto_tag ) {
      /* second is goto */
      exp g = bro ( son ( second ) ) ;
      no ( son ( second ) ) = no ( son ( pt ( g ) ) ) ;
      return make_code ( first, sp, dest, exitlab ) ;
    }

    if ( test = testlast ( first, second ), test != NULL ) {
      /* effectively an empty then part */
      int l = ( exitlab != 0 ) ? exitlab : new_label () ;
      exp orig = pt(test);	/* hold in case of extra_diags */

      /* make test jump to exitlab - see test_tag */
      ptno ( test ) = -l ;
      settest_number(test,  obranch(test_number(test))) ;
				/* settest_number preserves the Rev bit */
      no ( son ( second ) ) = new_label () ;
      make_code ( first, sp, dest, l ) ;
      make_code ( second, sp, dest, l ) ;
      mka.lab = l ;
      pt(test) = orig;	/* test no longer used, so restore for extra_diags */
      return mka;
    } 
    else {
      int fl ;
      no ( son ( second ) ) = new_label () ;
      fl = make_code ( first, sp, dest, exitlab ).lab ;
      {
	int l = ( fl != 0 ) ? fl :
	  ( ( exitlab != 0 ) ? exitlab : new_label () ) ;
	if(name(sh(first))!=bothd) uncond_ins ( i_b, l ) ;
	clear_all () ;
	make_code ( second, sp, dest, l ) ;
	mka.lab = l ;
	return mka;
      }
    }
  }

  case ass_tag :
  case assvol_tag : {
    exp lhs = son ( e ) ;
    exp rhs = bro ( lhs ) ;
    where assdest ;
    space nsp ;
    int contreg = NOREG ;
    int hdrhs = ( int ) name ( sh ( rhs ) ) ;
    bool is_float = ( bool ) is_floating ( hdrhs ) ;
#if use_long_double
    if ( hdrhs == doublehd ) is_float = 0 ;
#endif

    /* lose chvar_tag on rhs if no res, remember to invalidate reg */
    /* remove name ( e ) == ass_tag tests now assbits_tag has gone */

    if ( name ( e ) == assvol_tag ) {
      /* Assign to volatile location.  Disable register location
	 tracing.  Disable peephole optimisation (not possible
	 on SunOS 4.1.1 ) */
      clear_all () ;
      setvolatile () ;
    }

    if ( name ( e ) == ass_tag &&
	 ((name(rhs)==apply_tag || name(rhs)==apply_general_tag) 
	  || is_muldivrem_call ( rhs ) ) &&
	 ( ( is_float ) || valregable ( sh ( rhs ) ) ) ) {
      where apply_res ;

      /* set up apply_res */
      if ( is_float ) {
	freg frg ;
	frg.fr = 0 ;
	frg.dble = ( bool ) ( hdrhs != shrealhd ) ;
	setfregalt ( apply_res.answhere, frg ) ;
      } 
      else {
	setregalt ( apply_res.answhere, R_O0 ) ;
      }
      apply_res.ashwhere = ashof ( sh ( rhs ) ) ;

      ( void ) code_here ( rhs, sp, apply_res ) ;
      nsp = guard ( apply_res, sp ) ;

      assdest = locate ( lhs, nsp, sh ( rhs ), 0 ) ;
      ( void ) move ( apply_res.answhere, assdest, nsp.fixed, 1 ) ;
      ( void ) move ( apply_res.answhere, dest, nsp.fixed, 1 ) ;
      clear_dep_reg ( lhs ) ;
      return mka;
    }

#if 1
#ifndef NO_REGREG_ST
    /* see if we can use [ reg + reg ] addressing for this store */
    if ( name ( lhs ) == addptr_tag ) {
      exp addptr_sons = son ( lhs ) ;
      ash ashe ;
      int ashsize ;
      ashe = ashof ( sh ( rhs ) ) ;
      ashsize = ( int ) ( ashe.ashsize ) ;

      if ( last ( bro ( addptr_sons ) ) &&
	   ashe.ashalign == ashsize &&
	   ( ashsize == 8 || ashsize == 16 ||
	     ashsize == 32 || ( is_float && !param_aligned(bro(addptr_sons)) )
	   ) ) {
	int lhs_addptr_reg ;
	int rhs_addptr_reg ;
	ans aa ;

	lhs_addptr_reg = reg_operand ( addptr_sons, sp ) ;
	nsp = guardreg ( lhs_addptr_reg, sp ) ;
	rhs_addptr_reg = reg_operand ( bro ( addptr_sons ), nsp ) ;
	nsp = guardreg ( rhs_addptr_reg, nsp ) ;

	if ( is_float ) {
	  freg dfreg ;
	  dfreg.fr = freg_operand ( rhs, nsp,
				    getfreg ( nsp.flt ) ) ;
	  dfreg.dble = ( bool ) ( ashsize == 64 ) ;

	  stf_rr_ins ( i_st_sz ( ashsize ), dfreg.fr << 1,
		       lhs_addptr_reg, rhs_addptr_reg ) ;
	  setfregalt ( aa, dfreg ) ;
	} 
        else {
	  /* use dest reg if possible? */
	  int assreg = reg_operand ( rhs, nsp ) ;
	  st_rr_ins ( i_st_sz ( ashsize ), assreg,
		      lhs_addptr_reg, rhs_addptr_reg ) ;
	  setregalt ( aa, assreg ) ;
	}

	( void ) move ( aa, dest, sp.fixed, 1 ) ; /* nsp.fixed? */
	clear_dep_reg ( lhs ) ;
	return mka;
      }
    }
#endif
#endif
    assdest = locate ( lhs, sp, sh ( rhs ), 0 ) ;
    nsp = guard ( assdest, sp ) ;

    if ( assdest.ashwhere.ashalign == 1 ) {
      /* assignment of a bitfield, get address in proper form */
      instore is ;
      instore_bits isb;
		
      switch ( discrim ( assdest.answhere ) ) {

	case inreg : {
	  isb.b.base = regalt ( assdest.answhere ) ;
	  isb.b.offset_bits = 0 ;
	  isb.adval = 1 ;
	  break ;
	}

	case notinreg : {
	  is = insalt ( assdest.answhere ) ;
	  if ( !is.adval ) {
	    int r = getreg ( nsp.fixed ) ;
	    ld_ins ( i_ld, is.b, r ) ;
	    nsp = guardreg ( r, nsp ) ;
	    isb.adval = 1 ;
	    isb.b.base = r ;
	    isb.b.offset_bits = 0 ;
	  } else {
	    isb.adval = is.adval;
	    isb.b.base = is.b.base;
	    isb.b.offset_bits = BYTES2BITS(is.b.offset) ;
	  }
	  break ;
	}
#if 0
	case bitad : {
	  isb = bitadalt ( assdest.answhere ) ;
	  break ;
	}
#endif
	default : {
	  error(ERROR_SERIOUS,  "wrong assbits" ) ;
	  break ;
	}
      }
#if 0
      setbitadalt ( assdest.answhere, isb ) ;
#endif
    } else if ( name ( e ) == ass_tag &&
		discrim ( assdest.answhere ) == notinreg ) {
      instore is ;
      is = insalt ( assdest.answhere ) ;
      if ( !is.adval ) {
	/* this is an indirect assignment, so make it direct
	   by loading pointer into reg (and remember it) */
	int r = getreg ( nsp.fixed ) ;
	ld_ins ( i_ld, is.b, r ) ;
	nsp = guardreg ( r, nsp ) ;
	is.adval = 1 ;
	is.b.base = r ;
	is.b.offset = 0 ;
	setinsalt ( assdest.answhere, is ) ;
	keepexp ( lhs, assdest.answhere ) ;
      }
    }

#if 1
    if ( name ( e ) == ass_tag && is_float &&
	 discrim ( assdest.answhere ) == notinreg ) {
      /* Ensure floating point values assigned using floating
	 point regs so floating point reg tracking works better.
	 move () uses fixed regs for mem to mem, so must pre-load
	 to floating point reg */
      int f = freg_operand ( rhs, nsp, getfreg ( nsp.flt ) ) ;
      freg frg ;
      ans aa ;

      frg.fr = f ;
      frg.dble = ( bool ) ( hdrhs != shrealhd ) ;
      setfregalt ( aa, frg ) ;

      nsp = guardfreg ( f, nsp ) ;
      ( void ) move ( aa, assdest, nsp.fixed, 1 ) ;
      ( void ) move ( aa, dest, nsp.fixed, 1 ) ;

      clear_dep_reg ( lhs ) ;
      return mka;
    }
#endif

    /* evaluate source into assignment destination .... */
    contreg = code_here ( rhs, guard(assdest,nsp), assdest ) ;

    /* ... and move it into dest - could use assignment as value */

    switch ( discrim ( assdest.answhere ) ) {

      case inreg : {
	int a = regalt ( assdest.answhere ) ;
	/* remember that source has been evaluated into a */
	keepreg ( rhs, a ) ;
	/* forget register dependencies on destination */
	clear_dep_reg ( lhs ) ;
	( void ) move ( assdest.answhere, dest, nsp.fixed, 1 ) ;
	break ;
      }

      case infreg : {
	int r ;
	freg frg ;
	frg = fregalt ( assdest.answhere ) ;
	r = frg.fr + 32 ;
	if ( frg.dble ) r = -r ;
	/* remember that source has been evaluated into a */
	keepreg ( rhs, r ) ;
	/* forget register dependencies on destination */
	clear_dep_reg ( lhs ) ;
	( void ) move ( assdest.answhere, dest, nsp.fixed, 1 ) ;
	break ;
      }

      case notinreg :
#if 0
      case bitad : {
	if ( contreg != NOREG && name ( e ) == ass_tag ) {
	  ans aa ;
	  space nnsp ;

	  if ( contreg > 0 && contreg < 31 ) {
	    setregalt ( aa, contreg ) ;
	    nnsp = guardreg ( contreg, sp ) ;
	  } else {
	    freg frg ;
	    frg.fr = ABS_OF ( contreg ) - 32 ;
	    frg.dble = ( bool ) ( contreg < 0 ) ;
	    nnsp = nsp ;
	    setfregalt ( aa, frg ) ;
	  }
	  ( void ) move ( aa, dest, nnsp.fixed, 1 ) ;
	  /* forget register dependencies on destination */
	  clear_dep_reg ( lhs ) ;
	  /* remember that dest contains source, provided
	     that it is not dependent on it */
	  if ( name ( lhs ) == name_tag ) {
	    exp dc = son ( lhs ) ;
	    if ( son ( dc ) != NULL ) dc = son ( dc ) ;
	    if ( shape_size ( sh ( dc ) ) ==
		 shape_size ( sh ( rhs ) ) ) {
	      keepcont ( lhs, contreg ) ;
	    }
	  } else if ( !dependson ( lhs, 0, lhs ) ) {
	    keepcont ( lhs, contreg ) ;
	  }
	  return mka;
	}
	/* forget register dependencies on destination */
	clear_dep_reg ( lhs ) ;
	( void ) move ( assdest.answhere, dest, nsp.fixed, 1 ) ;
	break ;
      }
#endif
      case insomereg : {
	clear_dep_reg ( lhs ) ;
	/* forget register dependencies on destination */
	( void ) move ( assdest.answhere, dest,
			guard ( assdest, sp ).fixed, 1 ) ;
	break ;
      }
      case insomefreg:
      {
	error(ERROR_INTERNAL, "Insomefreg not expected here...");
      } 
    }

    if ( name ( e ) == assvol_tag ) setnovolatile () ;
    return mka;
  }

  case case_tag : {
    /* evaluate controlling integer into reg r */
    int r = reg_operand ( son ( e ), sp ) ;
    space nsp ;
    mm lims ;
    exp z = bro ( son ( e ) ) ;
    exp zt = z ;
    long n ;
    long l ;
    long u = 0x80000000 ;
    unsigned long approx_range ; 
    bool use_jump_vector ;
    nsp = guardreg ( r, sp ) ;

	    /* calculate crude criterion for using jump vector or branches */
    l = no ( zt ) ;
    for ( n = 1 ; ; n++ ) {
      if ( u + 1 != no ( zt ) && son ( zt ) != NULL ) {
	n++ ;
      }
      if ( last ( zt ) ) {
	u = ( son ( zt ) != NULL ) ? no ( son ( zt ) ) :
	  no ( zt ) ;
	break ;
      }
      if ( son ( zt ) != NULL ) {
	u = no ( son ( zt ) ) ;
      } else {
	if ( u + 1 == no ( zt ) ) u += 1 ;
      }

      zt = bro ( zt ) ;
    }

    /* now l is lowest controlling value, u is highest and n is
	       number of cases */

    if ( u - l < 0 ) {
      /* u - l overflowed into -ve, use huge */
      approx_range = 0x7fffffff ;
    } else {
      approx_range = ( unsigned long ) ( u - l ) ;
    }

    if ( approx_range < 16 ) {
      /* small jump vector needed, decide on instructions
	 executed only */
      unsigned jump_vector_cnt = ( ( l >= 0 && l <= 4 ) ? 8 : 9 ) ;
      unsigned cmp_jmp_step_cnt = 2 + ( !SIMM13_SIZE ( l ) ) +
	( !SIMM13_SIZE ( u ) ) ;
      /* cmp & jmp, delay slot filled plus possibly load of
		   large consts */
		/* assume default used as often as case, is this good? */
		/* likelyhood of default against single case */
      unsigned default_weight = 1 ;
      unsigned total_case_test_chain_cnt =
	( ( ( ( n + 1 ) * cmp_jmp_step_cnt ) * n ) / 2 ) + 1 ;
      /* unused delay slot on last case */
      unsigned default_test_chain_cnt =
	( n * cmp_jmp_step_cnt ) + 1 ;
      /* unused delay slot */
      unsigned average_test_chain_cnt =
	( total_case_test_chain_cnt + 
	  ( default_test_chain_cnt * default_weight ) ) /
	( n + default_weight ) ;
      use_jump_vector = jump_vector_cnt <= average_test_chain_cnt ;
    } else {
      /* space-time product criterion for jump vector instead
		   of tests and branches */
      unsigned long range_factor = approx_range + 9 ;
      unsigned long n_factor = ( ( unsigned long ) n * n ) / 2 ;
      use_jump_vector = range_factor <= n_factor ;	/* LINT */
    }

    if (is_signed(sh(son(e)))) {
      assert ( l <= u ) ;
    } else {
      assert ( (unsigned long) l <= (unsigned long) u ) ;
    }
    assert ( n >= 0 ) ;

    if ( use_jump_vector ) {
      /* use jump vector, 8/9 insts overhead */
      int endlab = new_label () ;
      int veclab = next_data_lab () ;
      baseoff zeroveclab ;
      int mr = getreg ( nsp.fixed ) ;
      nsp = guardreg ( mr, sp ) ;

      zeroveclab.offset = 0 ;
      zeroveclab.base = veclab ;

      if ( l >= 0 && l <= 4 ) {
	/* between 0 and 4 dummy table entries used to
	   avoid subtract */
	condri_ins ( i_bgeu, r, ( long ) ( u + 1 ), endlab ) ;
	rir_ins ( i_sll, r, 2, mr ) ;
	n = 0 ;
      } else {
	/* subtract to index jump vector */
	rir_ins ( i_sub, r, l, mr ) ;
	condri_ins ( i_bgeu, mr, ( long ) ( u - l + 1 ), endlab ) ;
	rir_ins ( i_sll, mr, 2, mr ) ;
	n = l ;
      }

      if ( PIC_code ) {
	char *rn = "%g1" ;
	assert ( (nsp.fixed & RMASK (R_O7)) == 0 ) ;
	fprintf ( as_file, "1:\n\tcall\t2f\n" ) ;
	fprintf ( as_file, "\tsethi\t%%hi(%sD%d-1b),%s\n",
		  lab_prefix, veclab, rn ) ;
	fprintf ( as_file, "2:\n\tor\t%s,%%lo(%sD%d-1b),%s\n",
		  rn, lab_prefix, veclab, rn ) ;
	rrr_ins ( i_add, R_TMP, mr, R_TMP ) ;
	ld_rr_ins ( i_ld, R_O7, R_TMP, R_TMP ) ;
	clear_reg(R_O7);
	clear_reg(R_TMP);
	fprintf ( as_file, "\tjmp\t%%o7+%s\n\tnop\n", rn ) ;
      } else {
	set_ins ( zeroveclab, R_TMP ) ;
	ld_rr_ins ( i_ld, mr, R_TMP, R_TMP ) ;
	extj_reg_ins ( i_jmp, R_TMP, -1 ) ;
      }

      /* build the jump vector, can be to .text or .data on SunOS
		   must be in .rodata for System V 
		   but must be .text if PIC_code */
      if ( sysV_assembler && !PIC_code )
	 insection ( rodata_section ) ;

      outs ( "\t.align\t4\n" ) ;
      outlab ( veclab ) ;
      outs ( ":\n" ) ;
      for ( ; ; ) {
	for ( ; no ( z ) != n ; n++ ) {
	  outs ( "\t.word\t" ) ;
	  outs ( lab_prefix ) ;
	  outn ( endlab ) ;
	  if ( PIC_code ) outs ( "-1b" ) ;
	  outnl () ;
	}
	u = ( son ( z ) == NULL ) ? n : no ( son ( z ) ) ;
	for ( ; n != u+1 ; n++ ) {	/* comparison independent of sign */
	  outs ( "\t.word\t" ) ;
	  outs ( lab_prefix ) ;
	  outn ( no ( son ( pt ( z ) ) ) ) ;
	  if ( PIC_code ) outs ( "-1b" ) ;
	  outnl () ;
	}
	if ( last ( z ) ) break ;
	z = bro ( z ) ;
      }

      if ( sysV_assembler && !PIC_code )
	 insection ( text_section ) ;

#ifdef NEWDWARF
      lost_count_ins();
#endif

      clear_all () ;
      set_label ( endlab ) ;
#ifdef NEWDWARF
      START_BB ();
#endif
      return mka;
    } else
    if (is_signed(sh(son(e)))) {
      /* use branches - tests are ordered */
      int over = 0 ;
      lims = maxmin ( sh ( son ( e ) ) ) ;
      for ( ; ; ) {
	int lab = no ( son ( pt ( z ) ) ) ;
	long l = no ( z ) ;
	if ( son ( z ) == NULL ) {
	  /* only single test required */
	  condri_ins ( i_be, r, l, lab ) ;
	  if ( l == lims.maxi ) {
	    lims.maxi -= 1 ;
	  } else if ( l == lims.mini ) {
	    lims.mini += 1 ;
	  }
	} else if ( u = no ( son ( z ) ), l > lims.mini ) {
	  if ( u >= lims.maxi ) {
	    /* have already tested lower */
	    condri_ins ( i_bge, r, l, lab ) ;
	    lims.maxi = l - 1 ;
	  } else {
	    if ( over == 0 ) {
	      over = new_label () ;
	    }
	    condri_ins ( i_bl, r, l, over ) ;
	    condri_ins ( i_ble, r, u, lab ) ;
	    lims.mini = u + 1 ;
	  }
	} else if ( u < lims.maxi ) {
	  /* lower is <= lower limit of shape */
	  condri_ins ( i_ble, r, u, lab ) ;
	  lims.mini = u + 1 ;
	} else {
	  /* upper is >= upper limit of shape */
	  uncond_ins ( i_b, lab ) ;
	}
	if ( last ( z ) ) {
	  if ( over != 0 ) {
	    clear_all () ;
	    set_label ( over ) ;
#ifdef NEWDWARF
	    START_BB ();
#endif
	  }
	  return mka;
	}
	z = bro ( z ) ;
      }
    }
    else {
      /* unsigned, use branches - tests are ordered */
      int over = 0 ;
      unsigned long maxi;
      unsigned long mini;
      lims = maxmin ( sh ( son ( e ) ) ) ;
      maxi = (unsigned)lims.maxi;
      mini = (unsigned)lims.mini;
      for ( ; ; ) {
	int lab = no ( son ( pt ( z ) ) ) ;
	unsigned long l = no ( z ) ;
	if ( son ( z ) == NULL ) {
	  /* only single test required */
	  condri_ins ( i_be, r, l, lab ) ;
	  if ( l == maxi ) {
	    maxi -= 1 ;
	  } else if ( l == mini ) {
	    mini += 1 ;
	  }
	} else if ( u = no ( son ( z ) ), l > mini ) {
	  if ( u >= maxi ) {
	    /* have already tested lower */
	    condri_ins ( i_bgeu, r, l, lab ) ;
	    maxi = l - 1 ;
	  } else {
	    if ( over == 0 ) {
	      over = new_label () ;
	    }
	    condri_ins ( i_blu, r, l, over ) ;
	    condri_ins ( i_bleu, r, u, lab ) ;
	    mini = u + 1 ;
	  }
	} else if ( u < maxi ) {
	  /* lower is <= lower limit of shape */
	  condri_ins ( i_bleu, r, u, lab ) ;
	  mini = u + 1 ;
	} else {
	  /* upper is >= upper limit of shape */
	  uncond_ins ( i_b, lab ) ;
	}
	if ( last ( z ) ) {
	  if ( over != 0 ) {
	    clear_all () ;
	    set_label ( over ) ;
#ifdef NEWDWARF
	    START_BB ();
#endif
	  }
	  return mka;
	}
	z = bro ( z ) ;
      }
    }
  }
  case movecont_tag:
  {
    exp frome = son(e);	/* names with a trailing e to avoid keywords */
    exp toe   = bro(frome);
    exp nbytes= bro(toe);
    int overlaps = !isnooverlap(e);
	   
    overlaps = 1;	/* for now use memmove always */
	   
    if (overlaps || (name(nbytes) != val_tag))
      {
	int param_reg = R_O0 ;	 /* next param reg to use */
	space nsp;
	nsp.fixed = sp.fixed;
	nsp.flt = sp.flt;
	     
	mka.lab = exitlab ;
	mka.regmove = NOREG ;

	{
	  /* evaluate parameters in turn */
	  /* the following is needed because the two different 
	     library function to be called require a different
	     ordering of parameters */
	  if(abi == ABI_SYSV){
	    nsp = guardreg(param_reg+1,nsp);
	    reg_operand_here(frome,nsp,param_reg+1);
	    nsp = guardreg(param_reg,nsp);
	    reg_operand_here(bro(frome),nsp,param_reg);
	  }
	  else{
	    nsp = guardreg(param_reg,nsp);
	    reg_operand_here(frome,nsp,param_reg);
	    nsp = guardreg(param_reg+1,nsp);
	    reg_operand_here(bro(frome),nsp,param_reg+1);
	  }
	  nsp = guardreg(param_reg+2,nsp);
	  reg_operand_here(bro(bro(frome)),nsp,param_reg+2);
#if 0	       
	  for ( argp=frome, arg_cnt = 0 ;
	       arg_cnt < 3 ;
	       arg_cnt++, argp = bro(argp) )
	    {
	      /* fixed point parameter in a single reg */
	      nsp = guardreg ( param_reg, nsp ) ;
	      reg_operand_here ( argp, nsp, param_reg ) ;
	      param_reg++ ;     
	    }
#endif
	}
	extj_special_ins ( i_call, abi == ABI_SYSV ? "memmove" : "_bcopy", 3);
	clear_all();
      }
#if 0
    /* IF YOU EVER COMPLETE THIS INLINE VERSION THEN FIX
       needscan, muldvrem AS WELL */
    else			/* inline block move in oprators.c */
      {
	lhsreg = reg_operand ( addptr_sons, sp ) ;
	rhsreg = reg_operand ( bro ( addptr_sons ),
			       guardreg ( lhsreg, sp ) ) ;
      }
#endif

    return mka;
  }
  case set_stack_limit_tag : {
    int r = reg_operand(son(e),sp);
    baseoff b;
    b = find_tag(TDF_STACKLIM);
    st_ins(i_st,r,b);
    return mka;
  }
  case give_stack_limit_tag : {
    ans aa;
    baseoff b;
    int r = regfrmdest(&dest,sp);
    b = find_tag(TDF_STACKLIM);
    ld_ins(i_ld,b,r);
    setregalt(aa,r);
    move(aa,dest,guardreg(r,sp).fixed,1);
    return mka;
  }

  case cont_tag :
  case contvol_tag : {
    if ( name ( e ) == contvol_tag ) {
      /* Load contents of volatile location.  Disable register
	 location tracing.  Disable peephole optimisation (not
	 possible with SPARC assembler ) */
      clear_all () ;
      setvolatile () ;
    }
#if 1
#ifndef NO_REGREG_LOADS
    /* see if we can use [ reg + reg ] addressing for this load */
    if ( name ( son ( e ) ) == addptr_tag ) {
      exp addptr_sons = son ( son ( e ) ) ;
      ash ashe ;
      int ashsize ;
      bool is_float = ( bool ) is_floating ( name ( sh ( e ) ) ) ;
      ashe = ashof ( sh ( e ) ) ;
      ashsize = ( int ) ashe.ashsize ;

      if ( last ( bro ( addptr_sons ) ) &&
	   ashe.ashalign == ashsize &&
	   ( ashsize == 8 || ashsize == 16 ||
	     ashsize == 32 || ( is_float && !param_aligned(bro(addptr_sons)) )
	   ) ) {
	int lhsreg ;
	int rhsreg ;
	bool sgned = ( bool ) ( ( ashsize >= 32 ) ||
				issgn ( sh ( e ) ) ) ;
	ans aa ;

	lhsreg = reg_operand ( addptr_sons, sp ) ;
	rhsreg = reg_operand ( bro ( addptr_sons ),
			       guardreg ( lhsreg, sp ) ) ;

	if ( is_float ) {
	  freg dfreg ;
	  if ( discrim ( dest.answhere ) == infreg ) {
	    dfreg = fregalt ( dest.answhere ) ;
	  } 
          else {
	    dfreg.fr = getfreg ( sp.flt ) ;
	  }
	  dfreg.dble = ( bool ) ( ashsize == 64 ) ;

	  ldf_rr_ins ( i_ld_sz ( ashsize, sgned ), lhsreg,
		       rhsreg, dfreg.fr << 1 ) ;
	  setfregalt ( aa, dfreg ) ;
	} else {
	  int dreg = ( ( discrim ( dest.answhere) == inreg ) ?
		       dest.answhere.val.regans :
		       getreg ( sp.fixed ) ) ;
	  ld_rr_ins ( i_ld_sz ( ashsize, sgned ), lhsreg,
		      rhsreg, dreg ) ;
	  setregalt ( aa, dreg ) ;
	}

	mka.regmove = move ( aa, dest, sp.fixed, sgned ) ;
	if ( name ( e ) == contvol_tag ) {
	  mka.regmove = NOREG ;
	  setnovolatile () ;
	}
	return mka;
      }
    }
#endif /* NO_REGREG_LOADS */
#endif
    /* FALL THROUGH */
  }

  case name_tag :
  case field_tag :
  case reff_tag :
  case addptr_tag :
  case subptr_tag : {
    where w ;
    bool sgned ;
    int dr = ( ( discrim ( dest.answhere ) == inreg ) ?
	       dest.answhere.val.regans : 0 ) ;
    if ( name ( e ) == contvol_tag ) {
      clear_all () ;
      setvolatile () ;
    }
    /* address of arg */
    w = locate ( e, sp, sh ( e ), dr ) ;
    sgned = ( bool ) ( ( ( w.ashwhere.ashsize >= 32 ) ||
			 ( issgn ( sh ( e ) )  ? 1 : 0 ) ) ) ;
    /* load real into float reg, move uses fixed reg */
    mka.regmove = move ( w.answhere, dest,
			 ( guard ( w, sp ) ).fixed, sgned ) ;
    if ( name ( e ) == contvol_tag ) {
      setnovolatile () ;
      mka.regmove = NOREG ;
    }
    return mka;
  }
  case current_env_tag : {
    int dreg ;
    ans aa ;
	  
    outs("\t.optim\t\"-O0\"\n");/*as -O2 replaces add to R_FP!*/
    dreg = ( ( discrim ( dest.answhere ) == inreg ) ?
	     regalt ( dest.answhere ) : getreg ( sp.fixed ) ) ;
    if(callee_offset(e)) {
      rir_ins(i_add,callee_start_reg,0,dreg);
    }
    else {
      rir_ins ( i_add, R_FP, 0, dreg ) ; 
    }
    setregalt ( aa, dreg ) ;
    ( void ) move ( aa, dest, guardreg ( dreg, sp ).fixed, 0 ) ;
    mka.regmove = dreg;
    return mka;
  }
  case env_offset_tag : {
    baseoff b;
    exp id = son(e);	/* as per tags.h, son is ident, not name */
    assert (name(id) == ident_tag);
    /* b = boff(id); */
    b.base = R_FP;
    if(name(son(id)) == formal_callee_tag) {
      b.base = callee_start_reg;
    }
    b.offset = boff_env_offset(id);
    /*assert(b.base == R_FP);*/	/* if not then can't index from current_env */
	   
    /* next part is lifted from val_tag code */
    {
      int r ;
      long v = b.offset ;
	     
      switch ( discrim ( dest.answhere ) ) {
	case inreg : {
	  r = regalt ( dest.answhere ) ;
	  ir_ins ( i_mov, v, r ) ;
	  break ;
	}
	default : {
	  ans aa ;
	  if ( v == 0 ) {
	    r = R_G0 ;
	  } else {
	    r = getreg ( sp.fixed ) ;
	    ir_ins ( i_mov, v, r ) ;
	  }
	  setregalt ( aa, r ) ;
	  ( void ) move ( aa, dest, guardreg ( r, sp ).fixed, 1 ) ;
	}
      }
      mka.regmove = r ;
      return mka;
    }
  }
  case long_jump_tag :  {
    exp l = son ( e ) ;
    exp r = bro ( l ) ;
    int a1 = reg_operand ( l, sp ), a2, r_spare ;
    space nsp ;

    nsp = guardreg ( a1, sp ) ;
    a2 = reg_operand ( r, nsp ) ;
    r_spare = getreg( guardreg(a2,nsp).fixed);
#ifdef NEWDWARF
    if (current_dg_info) {
	current_dg_info->data.i_lj.brk = set_dw_text_label ();
	current_dg_info->data.i_lj.j.k = WH_REG;
	current_dg_info->data.i_lj.j.u.l = a2;
    }
#endif
    outs("\t.optim\t\"-O0\"\n");
    lngjmp(a1,a2, r_spare);
    return mka;
  }
  case offset_pad_tag :   {
    int roff = reg_operand(son(e),sp);
    int rdest = regfrmdest(&dest,sp);
    ans aa;
    if(al2(sh(son(e))) >= al2(sh(e))){
      if (al2(sh(e))!=1 || al2(sh(son(e))) ==1){
	rr_ins(i_mov,roff,rdest);
      }
      else
	rir_ins(i_sll,roff,3,rdest);
    }
    else{
      int al = (al2(sh(son(e)))==1)?al2(sh(e)):(al2(sh(e))/8);
      rir_ins(i_add,roff,al-1,rdest);
      rir_ins(i_and,rdest,-al,rdest);
      if(al2(sh(son(e)))==1){
	rir_ins(i_sra,rdest,3,rdest);
      }
    }
    setregalt(aa,rdest);
    mka.regmove = move(aa,dest,guardreg(rdest,sp).fixed,0);
    return mka;
  }
#ifdef trap_tag
    case trap_tag : {
      if (no(e) == f_overflow) {
	do_exception(f_overflow);
      }
      else if (no(e) == f_nil_access) {
	do_exception(f_nil_access);
      }
      else {
	do_exception(f_stack_overflow);
      }
      return mka;
    }
#endif
    case special_tag :{
      if(no(e) == 0){
	/* output a floating point operation */
	int fr = getfreg(sp.flt);
	fconst(fr,0,0);
	rrrf_ins(i_fadds,fr<<1,fr<<1,fr<<1);
      }
      return mka;
    }
    case asm_tag : {
      if (props(e)) {
	if (name(son(e)) == string_tag)
	  outs (nostr(son(e)));
	else
	if (name(son(e)) == val_tag)
	  outn (no(son(e)));
	else
	if (asm_in(e)) {
	  exp s = son(e);
	  if (name(s)==name_tag && !isvar(son(s))) {
	    int r = regofval(s);
	    if (r != R_NO_REG)
	      out_asm_reg (r, 0);
	    else
	    if (r = fregofval(s), r != R_NO_REG)
	      out_asm_reg (r, 1);
	    else
	      out_asm_boff (boff(son(s)), no(s)/8);
	  }
	  else
	  if (name(s)==cont_tag && name(son(s))==name_tag && isvar(son(son(s)))) {
	    int r = regofval(son(s));
	    if (r != R_NO_REG)
	      out_asm_reg (-r, 0);
	    else
	    if (r = fregofval(son(s)), r != R_NO_REG)
	      out_asm_reg (r, 1);
	    else
	      out_asm_boff (boff(son(son(s))), no(son(s))/8);
	  }
	  else
	    error(ERROR_INTERNAL, "unsupported ASM operand");
	}
	else
	if (asm_var(e)) {
	  exp s = son(e);
	  if (name(s)==name_tag && isvar(son(s))) {
	    int r = regofval(s);
	    if (r != R_NO_REG)
	      out_asm_reg (-r, 0);
	    else
	    if (r = fregofval(s), r != R_NO_REG)
	      out_asm_reg (r, 1);
	    else
	      out_asm_boff (boff(son(s)), no(s)/8);
	  }
	  else
	    error(ERROR_INTERNAL, "unsupported ASM operand");
	}
	else
	  error(ERROR_INTERNAL, "illegal asm");
      }
      else {
	outs ("\n\t! ASM sequence start\n");
        code_here ( son(e), sp, nowhere ) ;
	outs ("\t! ASM sequence ends\n\n");
      }
      clear_all ();
#ifdef NEWDWARF
      lost_count_ins();
#endif
      return mka;
    }
  }
  /* Uncovered cases */
  error(ERROR_SERIOUS,  "TDF construct not done yet in make_code" ) ;
  return mka;
}


#ifdef NEWDIAGS
struct make_code_args {
	exp e;
	space sp;
	where dest;
	int exitlab;
	makeans res;
};

static 
void make_code_2 ( void * args )
{
  struct make_code_args * x = (struct make_code_args *) args;
  x->res = make_code_1 (x->e, x->sp, x->dest, x->exitlab);
  return;
}

dg_where 
find_diag_res ( void * args )
{
  struct make_code_args * x = (struct make_code_args *) args;
  dg_where w;
  switch (x->dest.answhere.d) {
    case inreg: {
      w.k = WH_REG;
      w.u.l = regalt(x->dest.answhere);
      break;
    }
    case infreg: {
      w.k = WH_REG;
      w.u.l = fregalt(x->dest.answhere).fr + 32;
      break;
    }
    case insomereg: {
      w.k = WH_REG;
      w.u.l = *someregalt(x->dest.answhere);
      break;
    }
    case insomefreg: {
      w.k = WH_REG;
      w.u.l = *somefregalt(x->dest.answhere).fr + 32;
      break;
    }
    case notinreg: {
      instore is;
      is = insalt(x->dest.answhere);
      w.k = (IS_FIXREG (is.b.base) ? WH_REGOFF : WH_CODELAB);
      w.u.l = is.b.base;
      w.o = is.b.offset;		/* is.adval ? */
      break;
    }
    default:
      error(ERROR_SERIOUS, "unexpected diag_res dest");
  }
  return w;
}


makeans 
make_code ( exp e, space sp, where dest, int exitlab )
{
  dg_info was_current = current_dg_info;
  current_dg_info = nildiag;
  if (extra_diags) {
    switch (name (e)) {
      case apply_tag:
      case apply_general_tag: {
	dg_info d = dgf(e);
	while (d && d->key != DGA_CALL)
	  d = d->more;
	if (!d) {
	  d = new_dg_info (DGA_CALL);
	  d->data.i_call.clnam = NULL;
	  d->data.i_call.pos = no_short_sourcepos;
	  d->data.i_call.ck = 0;
	  dgf(e) = combine_diaginfo (dgf(e), d);
	}
	break;
      }
      case test_tag: {
	dg_info d = dgf(e);
	if (dw_doing_branch_tests)
	  break;
	while (d && d->key != DGA_TEST)
	  d = d->more;
	if (!d) {
	  d = new_dg_info (DGA_TEST);
	  d->data.i_tst.pos = no_short_sourcepos;
	  d->data.i_tst.inv = 0;
	  dgf(e) = combine_diaginfo (dgf(e), d);
	}
	break;
      }
      case goto_tag: {
	short_sourcepos p;
	dg_info d = dgf(e);
	if (dw_doing_branch_tests)
	  break;
	p = no_short_sourcepos;
	while (d && d->key != DGA_JUMP) {
	  if (d->key == DGA_SRC)
	    p = d->data.i_src.startpos;
	  d = d->more;
	}
	if (!d) {
	  d = new_dg_info (DGA_JUMP);
	  d->data.i_tst.pos = p;
	  dgf(e) = combine_diaginfo (dgf(e), d);
	}
	break;
      }
      case goto_lv_tag:
      case return_to_label_tag:
      case long_jump_tag:
      case tail_call_tag: {
	short_sourcepos p;
	dg_info d = dgf(e);
	p = no_short_sourcepos;
	while (d && d->key != DGA_LJ) {
	  if (d->key == DGA_SRC)
	    p = d->data.i_src.startpos;
	  d = d->more;
	}
	if (!d) {
	  d = new_dg_info (DGA_LJ);
	  d->data.i_lj.pos = p;
	  dgf(e) = combine_diaginfo (dgf(e), d);
	}
	break;
      }
    }
  }
  if (dgf(e) != nildiag && name(e) != proc_tag && name(e) != general_proc_tag) {
    struct make_code_args args;
    current_dg_exp = args.e = e;
    args.sp = sp;
    args.dest = dest;
    args.exitlab = exitlab;
    CODE_DIAG_INFO (dgf(e), 0, &make_code_2, (void*)&args);
    current_dg_info = was_current;
    return args.res;
  }
  else {
    makeans a;
    a = make_code_1 (e, sp, dest, exitlab);
    current_dg_info = was_current;
    return a;
  }
}



static void 
done_arg ( void * args )
{
  UNUSED (args);
  return;
}

void 
diag_arg ( exp e, space sp, where dest )
{
  if (dgf(e)) {
    struct make_code_args args;
    current_dg_exp = args.e = e;
    args.sp = sp;
    args.dest = dest;
    args.exitlab = 0;
    CODE_DIAG_INFO (dgf(e), 0, &done_arg, (void*)&args);
  }
  return;
}
#endif
