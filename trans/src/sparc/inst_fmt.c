/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    This file contains procedures for outputting various SPARC instruction
    formats to the external file - as_file.  Each procedure produces
    assembler instructions for a family of SPARC operations, the actual
    instruction being passed as the string understood by the assembler.
*/

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "addrtypes.h"
#include "regexps.h"
#include "regmacs.h"
#include "sparcins.h"
#include "maxminmacs.h"
#include "translate.h"
#include "inst_fmt.h"
#include "labels.h"


/*
     IS c A POWER OF 2?
*/

#define IS_POW2( c )	( ( c ) != 0 && ( ( c ) & ( ( c ) - 1 ) ) == 0 )


/*
    ARRAY OF REGISTER NAMES
*/

static const char reg_name_tab [66][5] = {
    "%g0", "%g1", "%g2", "%g3", "%g4", "%g5", "%g6", "%g7",
    "%o0", "%o1", "%o2", "%o3", "%o4", "%o5", "%sp", "%o7",
    "%l0", "%l1", "%l2", "%l3", "%l4", "%l5", "%l6", "%l7",
    "%i0", "%i1", "%i2", "%i3", "%i4", "%i5", "%fp", "%i7",
    "%f0", "%f1", "%f2", "%f3", "%f4", "%f5", "%f6", "%f7",
    "%f8", "%f9", "%f10","%f11","%f12","%f13","%f14","%f15",
    "%f16","%f17","%f18","%f19","%f20","%f21","%f22","%f23",
    "%f24","%f25","%f26","%f27","%f28","%f29","%f30","%f31",
    "%fsr","%y"
} ;


/*
    This converts a register number into the corresponding register
    name.
*/

#define RN( reg )	reg_name_tab [ reg ]
#define FRN( reg )	reg_name_tab [ reg + 32 ]

/*
    FIND AN EXTERNAL NAME
*/

char 
*ext_name ( int id )
{
    if ( id < 0 ) {
	/* Negative numbers refer to globals */
	char *ext = main_globals [ -id - 1 ]->dec_u.dec_val.dec_id ;
	return ext;
    } else {
	/* Positive numbers refer to labels */
	static char space [64] ;
	sprintf ( space, "%sD%d", lab_prefix, id ) ;
	return space;
    }
}


/*
    OUTPUT A LOAD REGISTER-OFFSET INSTRUCTION
*/

void 
ld_ro_ins ( ins_p ins, baseoff a, int dest )
{
    long off = a.offset ;
    assert ( IS_FIXREG ( a.base ) ) ;
    clear_reg ( dest ) ;
    if ( SIMM13_SIZE ( off ) ) {
	/* Small offset */
	const char *ra = RN ( a.base ) ;
	const char *rd = RN ( dest ) ;
	if ( off == 0 ) {
	    asm_printop("%s [%s],%s", ins, ra, rd ) ;
	} else if ( off > 0 ) {
	    asm_printop("%s [%s+%ld],%s", ins, ra, off, rd ) ;
	} else /* if ( off < 0 ) */ {
	    asm_printop("%s [%s-%ld],%s", ins, ra, -off, rd ) ;
	}
#ifdef DWARF2
	count_ins(1);
#endif
    } else {
	/* Large offset */
	if ( a.base != dest ) {
	    /* Is this really a saving? */
	    ir_ins ( i_set, off, dest ) ;
	    ld_rr_ins ( ins, a.base, dest, dest ) ;
	} else {
	    assert ( a.base != R_TMP ) ;
	    ir_ins ( i_set, off, R_TMP ) ;
	    ld_rr_ins ( ins, a.base, R_TMP, dest ) ;
	}
#ifdef DWARF2
	lost_count_ins();
#endif
    }
}


/*
    OUTPUT A LOAD REGISTER-REGISTER INSTRUCTION
*/

void 
ld_rr_ins ( ins_p ins, int reg1, int reg2, int dest )
{
    clear_reg ( dest ) ;
    asm_printop("%s [%s+%s],%s", ins,
	      RN ( reg1 ), RN ( reg2 ), RN ( dest ) ) ;
#ifdef DWARF2
    count_ins(1);
#endif
}


/*
    OUTPUT A SET INSTRUCTION
*/

void 
set_ins ( baseoff a, int dest )
{
    char *extname = ext_name ( a.base ) ;
    long d = a.offset ;
    clear_reg ( dest ) ;

    if ( d == 0 || PIC_code ) {
	asm_printop("set %s,%s", extname, RN ( dest ) ) ;
    } else if ( d > 0 ) {
	asm_printop("set %s+%ld,%s", extname, d, RN ( dest ) ) ;
    } else {
	asm_printop("set %s-%ld,%s", extname, -d, RN ( dest ) ) ;
    }
#ifdef DWARF2
    lost_count_ins();
#endif

    if ( PIC_code ) {
	ld_rr_ins ( i_ld, R_L7, dest, dest ) ;
	if ( d ) rir_ins ( i_add, dest, d, dest ) ;
    }
}


/*
    If baseoff is a global this may be two instructions and involve
    a temporary register.
*/


void 
ld_ins ( ins_p ins, baseoff a, int dest )
{
    if ( !IS_FIXREG ( a.base ) ) {
	/* global */
	baseoff tmp_off ;
	tmp_off.base = R_TMP ;
	tmp_off.offset = 0 ;
	set_ins ( a, R_TMP ) ;
	ld_ro_ins ( ins, tmp_off, dest ) ;
    } else {
	ld_ro_ins ( ins, a, dest ) ;
    }
}


/*
    OUTPUT A STORE REGISTER-OFFSET INSTRUCTION
*/

void 
st_ro_ins ( ins_p ins, int src, baseoff a )
{
    long off = a.offset ;
    assert ( IS_FIXREG ( a.base ) ) ;

    /* in general we cannot cope with store using temp reg, catch it always */
    if ( ( src == R_TMP || a.base == R_TMP )
	 && ABS_OF ( off ) > ( 16 + 1 + 6 ) * 4 /* leeway for mem_temp */ ) {
	error(ERR_SERIOUS,  "Temporary register problem in st_ro_ins" ) ;
    }

    if ( SIMM13_SIZE ( off ) ) {
	/* Small offset */
	const char *rs = RN ( src ) ;
	const char *ra = RN ( a.base ) ;
	if ( off == 0 ) {
	    asm_printop("%s %s,[%s]", ins, rs, ra ) ;
	} else if ( off > 0 ) {
	    asm_printop("%s %s,[%s+%ld]", ins, rs, ra, off ) ;
	} else /* if ( off < 0 ) */ {
	    asm_printop("%s %s,[%s-%ld]", ins, rs, ra, -off ) ;
	}
#ifdef DWARF2
	count_ins(1);
#endif
    } else {
	/* Large offset */
	assert ( a.base != R_TMP ) ;
	ir_ins ( i_set, off, R_TMP ) ;
#ifdef DWARF2
	lost_count_ins();
#endif
	st_rr_ins ( ins, src, a.base, R_TMP ) ;
    }
}


/*
    OUTPUT A STORE REGISTER-REGISTER INSTRUCTION
*/

void 
st_rr_ins ( ins_p ins, int src, int reg1, int reg2 )
{
    asm_printop("%s %s,[%s+%s]", ins,
	      RN ( src ), RN ( reg1 ), RN ( reg2 ) ) ;
#ifdef DWARF2
    count_ins(1);
#endif
}


/*
    If baseoff is a global this may be two instructions and involve
    a temporary register.
*/

void 
st_ins ( ins_p ins, int src, baseoff a )
{
    if ( !IS_FIXREG ( a.base ) ) {
	/* global */
	baseoff tmp_off ;
	if ( src == R_TMP ) {
	    error(ERR_SERIOUS,  "Temporary register problem in st_ins" ) ;
	}
	tmp_off.base = R_TMP ;
	tmp_off.offset = 0 ;
	set_ins ( a, R_TMP ) ;
	st_ro_ins ( ins, src, tmp_off ) ;
    } else {
	st_ro_ins ( ins, src, a ) ;
    }
}


/*
    OUTPUT A THREE REGISTER INSTRUCTION
*/

void 
rrr_ins ( ins_p ins, int src1, int src2, int dest )
{
    clear_reg ( dest ) ;
    asm_printop("%s %s,%s,%s", ins,
	      RN ( src1 ), RN ( src2 ), RN ( dest ) ) ;
#ifdef DWARF2
    count_ins(1);
#endif
}


/*
    OUTPUT A REGISTER, IMMEDIATE, REGISTER INSTRUCTION
*/

void 
rir_ins ( ins_p ins, int src1, long imm, int dest )
{
    clear_reg ( dest ) ;

    if ( SIMM13_SIZE ( imm ) ) {
	/* Small data */
	asm_printop("%s %s,%ld,%s", ins,
		  RN ( src1 ), imm, RN ( dest ) ) ;
#ifdef DWARF2
	count_ins(1);
#endif
    } else if ( SIMM13_SIZE ( ~imm ) &&
		( ins == i_and || ins == i_or || ins == i_xor ) ) {
	/* Small data complemented */
	ins_p n_ins ;
	if ( ins == i_and ) {
	    n_ins = i_andn ;
	} else if ( ins == i_or ) {
	    n_ins = i_orn ;
	} else /* if ( ins == i_xor ) */ {
	    n_ins = i_xnor ;
	}
	asm_printop("%s %s,%ld,%s", n_ins,
		  RN ( src1 ), ~imm, RN ( dest ) ) ;
#ifdef DWARF2
	count_ins(1);
#endif
    } else if ( ins == i_and && IS_POW2 ( imm + 1 ) ) {
	/* Can be done by shift left, shift right */
	int nbits = 0, shift ;
	unsigned long uimm = ( unsigned long ) imm ;
	while ( uimm != 0 ) {
	    nbits++ ;
	    uimm = uimm >> 1 ;
	}
	shift = 32 - nbits ;
	rir_ins ( i_sll, src1, ( long ) shift, dest ) ;
	rir_ins ( i_srl, dest, ( long ) shift, dest ) ;
    } else if ( ( ins == i_add || ins == i_sub ) &&
		SIMM13_SIZE ( imm / 2 ) && dest != R_SP ) {
	if ( imm == 4096 ) {
	    /* add 4096 => sub -4096 etc */
	    rir_ins ( ( ins == i_add ? i_sub : i_add ), src1, -imm, dest ) ;
	} else {
	    /* use two adds or subs */
	    long half = imm / 2;
	    rir_ins ( ins, src1, half, dest ) ;
	    rir_ins ( ins, dest, ( long ) ( imm - half ), dest ) ;
	}
    } else {
	/* use temporary register for large constant */
	if ( src1 == R_TMP ) {
	    error(ERR_SERIOUS,  "Temporary register problem in rir_ins" ) ;
	} else {
	    asm_printop("set %ld,%s", imm, RN ( R_TMP ) ) ;
#ifdef DWARF2
	    lost_count_ins();
#endif
	    rrr_ins ( ins, src1, R_TMP, dest ) ;
	}
    }
}


/*
    OUTPUT A REGISTER TO REGISTER PSEUDO INSTRUCTION
*/

void 
rr_ins ( ins_p ins, int src, int dest )
{
    clear_reg ( dest ) ;
    asm_printop("%s %s,%s", ins, RN ( src ), RN ( dest ) ) ;
#ifdef DWARF2
    count_ins(1);
#endif
}


/*
    OUTPUT AN IMMEDIATE TO REGISTER PSEUDO INSTRUCTION
*/

void 
ir_ins ( ins_p ins, long imm, int dest )
{
    clear_reg ( dest ) ;

    if ( SIMM13_SIZE ( imm ) || ins == i_set ) {
	asm_printop("%s %ld,%s", ins, imm, RN ( dest ) ) ;
#ifdef DWARF2
	count_ins(1);
#endif
    } else if ( ins == i_mov ) {
	/* use a set instruction for move */
	asm_printop("set %ld,%s", imm, RN ( dest ) ) ;
#ifdef DWARF2
	lost_count_ins();
#endif
    } else {
	/* use temporary register for large constant */
	asm_printop("set %ld,%s", imm, RN ( R_TMP ) ) ;
#ifdef DWARF2
	lost_count_ins();
#endif
	rr_ins ( ins, R_TMP, dest ) ;
    }
}

/*
    OUTPUT A LABEL TO REGISTER PSEUDO INSTRUCTION
*/

void 
lr_ins ( int imm, int dest )
{
    clear_reg ( dest ) ;

    /* use a set instruction to load the label */
    asm_printop("set %s%d,%s", lab_prefix, imm, RN ( dest ) ) ;
#ifdef DWARF2
    lost_count_ins();
#endif

    if ( PIC_code ) {
	ld_rr_ins ( i_ld, R_L7, dest, dest ) ;
    }
}


/*
    OUTPUT A ZEROADIC INSTRUCTION
*/

void z_ins ( ins_p ins )
{
    asm_printop("%s", ins ) ;
#ifdef DWARF2
    count_ins(1);
#endif
}


/*
    OUTPUT AN UNCONDITIONAL BRANCH
*/

void 
uncond_ins ( ins_p ins, int lab )
{
    asm_printop("%s %s%d", ins, lab_prefix, lab ) ;
    assert (lab > 100);
    asm_printop("nop") ;	/* delay slot */
#ifdef DWARF2
    count_ins(2);
#endif
}


/*
    OUTPUT A RETURN INSTRUCTION
*/

void 
ret_ins ( ins_p ins )
{
    asm_printop("%s", ins ) ;
    asm_printop("nop") ;	/* delay slot */
#ifdef DWARF2
    count_ins(2);
#endif
}


/*
    OUTPUT A RETURN AND RESTORE INSTRUCTION
*/

void 
ret_restore_ins ()
{
    asm_printop("%s", i_ret ) ;
    asm_printop("%s", i_restore ) ;	/* delay slot */
#ifdef DWARF2
    count_ins(2);
#endif
}

/*
   OUTPUT A LONGJMP (old sp, pc)
*/
				/* offset from fp to saved i6 in the 16 word
				 reg save area. See rw_fp in <machine/reg.h> */
#define FP_OFFSET_IN_FRAME (8*4 + 6*4)

void 
lngjmp ( int o_fp_reg, int pc_reg, int r_new_sp )
{
  int lab = new_label();
  baseoff frm;
  
  frm.offset = FP_OFFSET_IN_FRAME;
    
#ifdef NOT_SUN_BUGGY_ASM
  asm_printf("\tta\t3\n" );
#else
  asm_printf("\t.word\t0x91d02003\n" ) ; /* ta 3, but SunOS as may
						    get ta wrong I'm told */
#endif
#ifdef DWARF2
	lost_count_ins();
#endif
  rr_ins ( i_mov, R_SP, r_new_sp);
  rir_ins( i_sub, R_SP, 0x40, R_SP);

  frm.base = r_new_sp;
  
  set_label (lab);
  ld_ro_ins (i_ld, frm,   R_TMP);
  asm_printop("cmp %s,%s", RN (R_TMP ), RN(o_fp_reg));
  asm_printop("bne,a %s%d", lab_prefix, lab);
#ifdef DWARF2
  count_ins(2);
#endif
  rr_ins (i_mov, R_TMP, r_new_sp);
				/* now r_new_sp holds the sp to a reg
				 save area whose fp is the fp we want...*/
  rr_ins (i_mov, r_new_sp, R_FP);
  
  asm_printop("jmpl %s + 0, %%g0", RN(pc_reg)) ;
  asm_printop("%s", i_restore ) ;	/* delay slot */
#ifdef DWARF2
  count_ins(2);
#endif
}

/*
    See section D.4 of the SPARC architecture manual.
*/

void 
stret_restore_ins (void)
{
    asm_printf("\tjmp\t%%i7+12\n" ) ;
    asm_printop("%s", i_restore ) ;	/* delay slot */
#ifdef DWARF2
    count_ins(2);
#endif
}


/*
    OUTPUT AN EXTERNAL JUMP OR CALL INSTRUCTION
*/

void 
extj_ins ( ins_p ins, baseoff b, int param_regs_used )
{
  char *ext = ext_name ( b.base ) ;
  if ( param_regs_used >= 0 ) {
    /* print number of parameter registers if known */
    assert ( param_regs_used <= 6 ) ;	/* %o0..%o5 */
    if(b.offset) {
      asm_printop("%s %s+%ld,%d",ins,ext,b.offset,param_regs_used);
    }
    else {
      asm_printop("%s %s,%d", ins, ext, param_regs_used ) ;
    }
    
  } 
  else {
    /* param_regs_used = -1 means it is not known */
    if (b.offset) {
      asm_printop("%s %s+%ld",ins,ext,b.offset);
    }
    else {
      asm_printop("%s %s", ins, ext ) ;
    }
  }
  asm_printop("nop") ;	/* delay slot */
#ifdef DWARF2
  count_ins(2);
#endif
}	

/* 
   don't fill up the delay slot: the caller of this functions must
   provide its own delay slot filler 
*/
void extj_ins_without_delay 
    ( ins_p ins, baseoff b, int param_regs_used ){
  char *ext = ext_name ( b.base ) ;
  if ( param_regs_used >= 0 ) {
    /* print number of parameter registers if known */
    assert ( param_regs_used <= 6 ) ;	/* %o0..%o5 */
    asm_printop("%s %s,%d", ins, ext, param_regs_used ) ;
  } 
  else {
    /* param_regs_used = -1 means it is not known */
    asm_printop("%s %s", ins, ext ) ;
  }
#ifdef DWARF2
  count_ins(1);
#endif
}



/*
  OUTPUT AN EXTERNAL JUMP OR CALL INSTRUCTION (SPECIAL CASE)
  
  This case is used to handle special calls like .muls where the
  name is given by a string.
*/

void 
extj_special_ins ( ins_p ins, const char * const ext, int param_regs_used ){
  if ( param_regs_used >= 0 ) {
    /* print number of parameter registers if known */
    assert ( param_regs_used <= 6 ) ;	/* %o0..%o5 */
    asm_printop("%s %s,%d", ins, ext, param_regs_used ) ;
  } 
  else {
    /* param_regs_used = -1 means it is not known */
    asm_printop("%s %s", ins, ext ) ;
  }
  asm_printop("nop") ;	/* delay slot */
#ifdef DWARF2
  count_ins(2);
#endif
}


/* as above, but with allowing the calling function to fill in the
   delay slot. */
void 
extj_special_ins_no_delay ( ins_p ins, const char * const ext, int param_regs_used ){
  if ( param_regs_used >= 0 ) {
    /* print number of parameter registers if known */
    assert ( param_regs_used <= 6 ) ;	/* %o0..%o5 */
    asm_printop("%s %s,%d", ins, ext, param_regs_used ) ;
  } 
  else {
    /* param_regs_used = -1 means it is not known */
    asm_printop("%s %s", ins, ext ) ;
  }
#ifdef DWARF2
  count_ins(1);
#endif
  	/* delay slot */
}




/*
  OUTPUT AN EXTERNAL JUMP TO REGISTER INSTRUCTION
*/

void 
extj_reg_ins ( ins_p ins, int reg, int param_regs_used ){
  assert ( IS_FIXREG ( reg ) ) ;
  if ( sysV_assembler ) {
    /* The SysV assembler likes reg to be R_G1 for calls */
    if ( ins == i_call && reg != R_G1 ) {
      rr_ins ( i_mov, reg, R_G1 ) ;
      reg = R_G1 ;
    }
  }	
  extj_special_ins ( ins, RN ( reg ), param_regs_used ) ;
}	


void 
extj_reg_ins_no_delay ( ins_p ins, int reg, int param_regs_used ){
  assert ( IS_FIXREG ( reg ) ) ;
  if ( sysV_assembler ) {
    /* The SysV assembler likes reg to be R_G1 for calls */
    if ( ins == i_call && reg != R_G1 ) {
      rr_ins ( i_mov, reg, R_G1 ) ;
      reg = R_G1 ;
    }
  }	
  extj_special_ins_no_delay ( ins, RN ( reg ), param_regs_used ) ;
}	



/*
  OUTPUT AN UNIMP INSTRUCTION
*/

void 
unimp_ins ( long imm ){
    asm_printop("unimp %ld", imm ) ;
#ifdef DWARF2
    count_ins(1);
#endif
}


/*
  OUTPUT A CONDITIONAL INTEGER TEST JUMP
*/

void 
br_ins ( ins_p ins, int dest ){
  asm_printop("%s %s%d", ins, lab_prefix, dest ) ;
  assert (dest > 100);
  asm_printop("nop") ;	/* delay slot */
#ifdef DWARF2
  count_ins(2);
#endif
}

/*
  OUTPUT int branch for abs
*/

void 
br_abs ( int lab ){
#ifdef NOT_SUN_BUGGY_ASM
  asm_printop("%s %s%s", "bpos,a", lab_prefix, lab);
#ifdef DWARF2
  count_ins(1);
#endif
  /* No nop, delay slot used!!! */
#else
  asm_printop("%s %s%d", "bneg", lab_prefix, lab);
  asm_printf("\tnop\n");
#ifdef DWARF2
  count_ins(2);
#endif
#endif
}


/*
  OUTPUT A CONDITIONAL FLOATING POINT TEST JUMP

  The instruction before a floating point test jump instruction 
  cannot be another floating point instruction.
*/

void 
fbr_ins ( ins_p ins, int dest ){
  asm_printop("nop") ;
  asm_printop("%s %s%d", ins, lab_prefix, dest ) ;
  assert (dest > 100);
  asm_printop("nop") ;	/* delay slot */
#ifdef DWARF2
  count_ins(2);
#endif
}


/*
  OUTPUT A REGISTER, REGISTER COMPARISON
*/

void 
condrr_ins ( ins_p ins, int src1, int src2, int lab ){
  if(src2 == R_G0){
    asm_printf("\ttst\t%s\n",RN(src1) );
  }
  else{
    asm_printop("cmp %s,%s", RN ( src1 ), RN ( src2 ) ) ;
  }
#ifdef DWARF2
  count_ins(1);
#endif
  br_ins ( ins, lab ) ;
}


/*
  OUTPUT A REGISTER, IMMEDIATE COMPARISON
*/

void 
condri_ins ( ins_p ins, int src1, long imm, int lab ){
  if ( SIMM13_SIZE(imm) ) {
    /* Small constant */
    asm_printop("cmp %s,%ld", RN ( src1 ), imm ) ;
#ifdef DWARF2
    count_ins(1);
#endif
    br_ins ( ins, lab ) ;
    } 
  else {
    /* Large constant */
    if ( src1 == R_TMP ) {
      error(ERR_SERIOUS,  "Temporary register problem in condri_ins" ) ;
    }
    asm_printop("set %ld,%s", imm, RN ( R_TMP ) ) ;
#ifdef DWARF2
    lost_count_ins();
#endif
    condrr_ins ( ins, src1, R_TMP, lab ) ;
  }
}

/*
    OUTPUT A REGISTER, REGISTER MAX/MIN
*/

void 
fmaxminrr_ins ( ins_p ins, int src1, int src2, int dest, int ftype ) {
  ins_p fcmp_ins;
  int lab = new_label() ;
  fcmp_ins = i_fcmps;

  UNUSED(ftype);

  asm_printop("%s %s,%s", fcmp_ins,RN ( src1 ), RN ( src2 ) ) ;
  asm_printop("%s %s%d", ins, lab_prefix, lab ) ;
  /* USE the delay slot */
  asm_printop("fmovs %s, %s", RN(src1), RN(dest));
  asm_printop("fmovs %s, %s", RN(src2), RN(dest));
#ifdef DWARF2
  count_ins(4);
#endif
  
  set_label(lab);
}

  


void 
maxminrr_ins ( ins_p ins, int src1, int src2, int dest ){
  int lab = new_label() ;
  
  asm_printop("cmp %s,%s", RN ( src1 ), RN ( src2 ) ) ;
  asm_printop("%s %s%d", ins, lab_prefix, lab ) ;
  /* USE the delay slot */
  asm_printop("mov %s, %s", RN(src1), RN(dest));
  asm_printop("mov %s, %s", RN(src2), RN(dest));
#ifdef DWARF2
  count_ins(4);
#endif
  
  set_label(lab);
}

/*
  OUTPUT A REGISTER, IMMEDIATE MAX/MIN
*/

void 
maxminri_ins ( ins_p ins, int src1, long val, int dest ){
  int lab = new_label() ;
  
  if (!SIMM13_SIZE ( val ))  {
    asm_printop("set %ld,%s", val, RN ( R_TMP ) ) ;
    asm_printop("cmp %s,%s", RN ( src1 ), RN ( R_TMP) ) ;
    asm_printop("%s %s%d", ins, lab_prefix, lab ) ;
    /* USE the delay slot */
    asm_printop("mov %s, %s", RN(src1), RN(dest));
			/* note set is two instruction, and
	       	        must not go in the delay slot... */
    asm_printop("set %ld, %s", val, RN(dest));
#ifdef DWARF2
    lost_count_ins();
#endif
  } 
  else{
    asm_printop("cmp %s,%ld", RN ( src1 ), val ) ;
    asm_printop("%s %s%d", ins, lab_prefix, lab ) ;
    /* USE the delay slot */
    asm_printop("mov %s, %s", RN(src1), RN(dest));
    asm_printop("mov %ld, %s", val, RN(dest));
#ifdef DWARF2
    count_ins(4);
#endif
  
  }
  set_label(lab);
}


/*
  OUTPUT A LOAD FLOATING REGISTER-OFFSET INSTRUCTION
*/

void 
ldf_ro_ins ( ins_p ins, baseoff a, int dest ){
  long off = a.offset ;
  assert ( IS_FIXREG ( a.base ) ) ;
  clear_freg ( dest ) ;
  if ( SIMM13_SIZE ( off ) ) {
    /* Small offset */
    const char *rn = RN ( a.base ) ;
    if ( off == 0 ) {
      asm_printop("%s [%s],%s", ins, rn, FRN(dest) ) ;
    } 
    else if ( off > 0 ) {
      asm_printop("%s [%s+%ld],%s", ins, rn, off, FRN(dest) ) ;
    } 
    else /* if ( off < 0 ) */ {
      asm_printop("%s [%s-%ld],%s", ins, rn, -off, FRN(dest) ) ;
    }
#ifdef DWARF2
    count_ins(1);
#endif
  } 
  else {
    /* Large offset */
    assert ( a.base != R_TMP ) ;
    ir_ins ( i_set, off, R_TMP ) ;
#ifdef DWARF2
    lost_count_ins();
#endif
    ldf_rr_ins ( ins, a.base, R_TMP, dest ) ;
  }
}


/*
  OUTPUT A LOAD FLOATING REGISTER-REGISTER INSTRUCTION
*/

void 
ldf_rr_ins ( ins_p ins, int reg1, int reg2, int dest ){
  clear_freg ( dest ) ;
  asm_printop("%s [%s+%s],%s", ins,
	    RN ( reg1 ), RN ( reg2 ), FRN(dest) ) ;
#ifdef DWARF2
  count_ins(1);
#endif
}


/*
  OUTPUT A LOAD FLOATING INSTRUCTION

  If baseoff is a global this may be two instructions and involve
  a temporary register.
*/

void 
ldf_ins ( ins_p ins, baseoff a, int dest ){
  if ( !IS_FIXREG ( a.base ) ) {
    /* global */
    baseoff tmp_off ;
    tmp_off.base = R_TMP ;
    tmp_off.offset = 0 ;
    set_ins ( a, R_TMP ) ;
    ldf_ro_ins ( ins, tmp_off, dest ) ;
  } 
  else {
    ldf_ro_ins ( ins, a, dest ) ;
  }
}


/*
  OUTPUT A STORE FLOATING REGISTER-OFFSET INSTRUCTION
*/

void 
stf_ro_ins ( ins_p ins, int src, baseoff a ){
  long off = a.offset ;
  assert ( IS_FIXREG ( a.base ) ) ;
  if ( a.base == R_TMP && ABS_OF ( off )  > ( 16 + 1 + 6 ) * 4 ) {
    error(ERR_SERIOUS,  "Temporary register problem in stf_ro_ins" ) ;
  }
  if ( SIMM13_SIZE ( off ) ) {
    /* Small offset */
    const char *rn = RN ( a.base ) ;
    if ( off == 0 ) {
      asm_printop("%s %s,[%s]", ins, FRN(src), rn ) ;
    } 
    else if ( off > 0 ) {
      asm_printop("%s %s,[%s+%ld]", ins, FRN(src), rn, off ) ;
    } 
    else /* if ( off < 0 ) */ {
      asm_printop("%s %s,[%s-%ld]", ins, FRN(src), rn, -off ) ;
    }
#ifdef DWARF2
    count_ins(1);
#endif
   } 
  else {
    /* Large offset */
    assert ( a.base != R_TMP ) ;
    ir_ins ( i_set, off, R_TMP ) ;
#ifdef DWARF2
    lost_count_ins();
#endif
    stf_rr_ins ( ins, src, a.base, R_TMP ) ;
  }
}


/*
  OUTPUT A STORE FLOATING REGISTER-REGISTER INSTRUCTION
*/

void 
stf_rr_ins ( ins_p ins, int src, int reg1, int reg2 ){
  asm_printop("%s %s,[%s+%s]", ins, FRN(src), 
	    RN ( reg1 ), RN ( reg2 ) ) ;
#ifdef DWARF2
  count_ins(1);
#endif
}


/*
  OUTPUT A STORE FLOATING INSTRUCTION
  
  If baseoff is a global this may be two instructions and involve
  a temporary register.
*/

void 
stf_ins ( ins_p ins, int src, baseoff a ){
  if ( !IS_FIXREG ( a.base ) ) {
    /* global */
    baseoff tmp_off ;
    tmp_off.base = R_TMP ;
    tmp_off.offset = 0 ;
    set_ins ( a, R_TMP ) ;
    stf_ro_ins ( ins, src, tmp_off ) ;
  } 
  else {
    stf_ro_ins ( ins, src, a ) ;
  }
}


/*
  OUTPUT A FLOATING REGISTER, FLOATING REGISTER COMPARISON
*/

void 
rrf_cmp_ins ( ins_p ins, int src1, int src2 ){
  asm_printop("%s %s,%s", ins, FRN(src1), FRN(src2) ) ;
#ifdef DWARF2
  count_ins(1);
#endif
}


/*
  OUTPUT A FLOATING REGISTER, FLOATING REGISTER INSTRUCTION
*/

void 
rrf_ins ( ins_p ins, int src, int dest ){
  clear_freg ( dest ) ;
  asm_printop("%s %s,%s", ins, FRN(src), FRN(dest) ) ;
#ifdef DWARF2
  count_ins(1);
#endif
}


/*
  OUTPUT A THREE FLOATING REGISTER INSTRUCTION
*/

void 
rrrf_ins ( ins_p ins, int src1, int src2, int dest ){
  clear_freg ( dest ) ;
  asm_printop("%s %s,%s,%s", ins, FRN(src1), 
	    FRN(src2), FRN(dest) ) ;
#ifdef DWARF2
  count_ins(1);
#endif
}



/*
  OUTPUT AN OPERAND, AS PART OF AN ASM SEQUENCE
*/

void 
out_asm_reg ( int r, int fp ){
  asm_printf("%s", fp ? FRN(r) : RN(r));
}

void 
out_asm_boff ( baseoff b, long o2 ){
  long off = b.offset + o2;
  if ( off == 0 )
    asm_printf("[%s]", RN(b.base));
  else if ( off > 0 )
    asm_printf("[%s+%ld]", RN(b.base), off);
  else /* if ( off < 0 ) */
    asm_printf("[%s-%ld]", RN(b.base), -off);
}
