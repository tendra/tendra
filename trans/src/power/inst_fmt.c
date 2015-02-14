/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Procs for outputting various POWER instruction formats to the
 * external file - as_file. Each procedure produces assembler for a family
 * of POWER operations, the actual member is passed as the string
 * understood by the assembler.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/error.h>

#include <local/cpu.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "geninst.h"
#include "proc.h"
#include "translate.h"
#include "maxminmacs.h"		/* for absval() */
#include "stack.h"
#include "inst_fmt.h"
#include "macro.h"
#include "mask.h"

#define IS_POW2(c)		((c)!= 0 && ((c) & ((c) -1)) == 0)

#define CHECKREG(r)		assert(IS_FIXREG(r) && (!IS_SREG(r) || (r) >= p_sreg_first_save || (r == R_FP)));
#define CHECKFREG(r)		assert((!IS_FLT_SREG(r) || (r) >= p_sfreg_first_save));

char * get_instruction(Instruction_P);

char *ext_name(long id)
{
  if (id < 0)
  {
    char *ext = main_globals[(-id) - 1] ->dec_u.dec_val.dec_id;

    return ext;
  }
  else
  {
    static char sp[16];

    assert(id > R_LAST);	/* not a confused register */

    sprintf(sp, "L.D%ld", id);
    return sp;
  }
}

/* +++ do better for offset to R_SP too big, trace reg or load extra base reg */

void ld_ro_ins(Instruction_P ins, baseoff a, int dest)
{
  CHECKREG(dest); CHECKREG(a.base);

  clear_reg(dest);

  if (a.base == R_0)
  {
    /* base reg of R_0 is not normally allowed, special case 0 offset */
    if (a.offset != 0)
      error(ERROR_SERIOUS, "ld_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
	if (do_macros) {
 	   asm_printf( "\t%sx\t%s,%s,%s",get_instruction(ins),reg_macro(dest),reg_macro(R_0),reg_macro(R_0));
	} else {
	    asm_printf( "\t%sx\t%d,%d,%d", get_instruction(ins), dest, R_0, R_0);
	}
  }
  else if (IMM_SIZE(a.offset))
  {
	if (do_macros) {
	    asm_printf( "\t%s\t%s,%d(%s)", get_instruction(ins), reg_macro(dest), (int)a.offset, reg_macro(a.base));
	} else {
	    asm_printf( "\t%s\t%d,%d(%d)", get_instruction(ins), dest,(int)a.offset, a.base);
	}
  }
  else
  {
    /* offset too big, put in temp reg and used ld_rr_ins */
    /* +++ arrange stack variable to minimise this */
    assert(a.base!=R_TMP0);
    ld_const_ins(a.offset, R_TMP0);
    ld_rr_ins(ins, a.base, R_TMP0, dest);
  }
}


void ld_rr_ins(Instruction_P ins, int reg1, int reg2, int dest)
{
  CHECKREG(dest); CHECKREG(reg1); CHECKREG(reg2);
  assert(reg1!=R_0);

  clear_reg(dest);
	if (do_macros) {
  asm_printop("%sx %s,%s,%s", get_instruction(ins), reg_macro(dest), reg_macro(reg1), reg_macro(reg2));
	} else {
  asm_printop("%sx %d,%d,%d", get_instruction(ins), dest, reg1, reg2);
	}
}


void set_ins(baseoff a, int dest)
{
  char *extname = ext_name(a.base);

  CHECKREG(dest);

  clear_reg(dest);
	if (do_macros) {
  asm_printop("%s %s,T.%s(%s)", get_instruction(i_l), reg_macro(dest), extname, reg_macro(R_TOC));
	} else {
  asm_printop("%s %d,T.%s(%d)", get_instruction(i_l), dest, extname, R_TOC);
	}
  /* +++ offsets in TOC */
  if (a.offset != 0)
    rir_ins(i_a, dest, a.offset, dest);
}


void ld_ins(Instruction_P ins, baseoff a, int dest)
{
  /*
   * Not a single instruction. Load from baseoff, which may be a global
   * requiring a temporary reg.
   */

  CHECKREG(dest);

  if (!IS_FIXREG(a.base))
  {
    /* global */
    baseoff tmp_off;

    asm_comment("ld_ins ext: off=%#x -> r%d", a.offset, dest);
    assert(a.offset==0 || dest!=R_TMP0);

    /* load base into dest reg, then let ld_ro_ins do offset (which may need R_TMP0) */
    tmp_off.base = a.base;
    tmp_off.offset = 0;

    set_ins(tmp_off, dest);

    tmp_off.base = dest;
    tmp_off.offset = a.offset;

    ld_ro_ins(ins, tmp_off, dest);comment(NULL);
  }
  else
  {
    ld_ro_ins(ins, a, dest);comment(NULL);
  }
}


void st_ro_ins(Instruction_P ins, int src, baseoff a)
{
  CHECKREG(src); CHECKREG(a.base);


  /* in general we cannot cope with store using temp reg, catch it always */
  if ((src == R_TMP0 || a.base == R_TMP0) && absval(a.offset) > (16 + 1 + 6) * 4)	/* leeway for mem_temp() */
    error(ERROR_SERIOUS, "st_ro_ins: store of temp reg to offset not allowed");	/* should not happen */

  if (a.base == R_0)
  {
    if (a.offset != 0)
      error(ERROR_SERIOUS, "st_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
	if (do_macros) {
	    asm_printf( "\t%sx\t%s,%s,%s", get_instruction(ins), reg_macro(src), reg_macro(R_0), reg_macro(R_0));
	} else {
	    asm_printf( "\t%sx\t%d,%d,%d", get_instruction(ins), src, R_0, R_0);
	}
  }
  else if (IMM_SIZE(a.offset))
  {
	if (do_macros) {
	    asm_printf( "\t%s\t%s,%d(%s)", get_instruction(ins), reg_macro(src), (int)a.offset, reg_macro(a.base));
	} else {
	    asm_printf( "\t%s\t%d,%d(%d)", get_instruction(ins), src,(int)a.offset, a.base);
	}
  }
  else
  {
    /* offset too big, put in temp reg and used st_rr_ins */
    /* +++ arrange stack variable to minimise this */
    asm_comment("st_ro_ins: big offset, use temp reg and st_rr_ins");
    assert(a.base!=R_TMP0);		/* otherwise we corrupt it */
    ld_const_ins(a.offset, R_TMP0);
    st_rr_ins(ins, src, a.base, R_TMP0);
  }
}


void st_rr_ins(Instruction_P ins, int src, int reg1, int reg2)
{
  CHECKREG(src); CHECKREG(reg1); CHECKREG(reg2);
  assert(reg1!=R_0);
	if (do_macros) {
	  asm_printop("%sx %s,%s,%s", get_instruction(ins), reg_macro(src), reg_macro(reg1), reg_macro(reg2));
	} else {
	  asm_printop("%sx %d,%d,%d", get_instruction(ins), src, reg1, reg2);
	}
}


void st_ins(Instruction_P ins, int src, baseoff a)
{
  /*
   * Not a single instruction. Store into baseoff, which may be a global
   * requiring a temporary reg.
   */

  CHECKREG(src);

  if (!IS_FIXREG(a.base))
  {
    /* global */
    baseoff tmp_off;

    if (src == R_TMP0)
      error(ERROR_SERIOUS, "st_ins: store of temp reg to global not allowed");	/* should not happen */

    tmp_off.base = R_TMP0;
    tmp_off.offset = 0;

    set_ins(a, R_TMP0);
    st_ro_ins(ins, src, tmp_off);comment(NULL);
  }
  else
  {
    st_ro_ins(ins, src, a);comment(NULL);
  }
}


/* 3 register operand instructions, source1, source2, destination */
void rrr_ins(Instruction_P ins, int src1, int src2, int dest)
{
  CHECKREG(dest); CHECKREG(src1); CHECKREG(src2);

  clear_reg(dest);

  /* i_s is a pseudo instruction, use i_sf with reversed ops */
  if (ins == i_s)
  {
	if (do_macros) {
	    asm_printop("%s %s,%s,%s", get_instruction(i_sf), reg_macro(dest), reg_macro(src2), reg_macro(src1));
	} else {
	    asm_printop("%s %d,%d,%d", get_instruction(i_sf), dest, src2, src1);
	}
  }
  else
  {
	if (do_macros) {
	    asm_printop("%s %s,%s,%s", get_instruction(ins), reg_macro(dest), reg_macro(src1), reg_macro(src2));
	} else {
	    asm_printop("%s %d,%d,%d", get_instruction(ins), dest, src1, src2);
	}
  }

}


/* source register, immediate, destination register instructions */

void rir_ins(Instruction_P ins, int src, long imm, int dest)
{
  bool logical = ins == i_and || ins == i_or || ins == i_xor||
    ins ==i_and_cr|| ins==i_or_cr || ins==i_xor_cr;

  CHECKREG(dest); CHECKREG(src);
  assert(ins!=i_divs&&ins!=i_div);	/* no divi, so we should not be called for div */

  /*
   * Check agaonst IBM assembler bug which we should avoid at higher levels:
   * IX25505 bosadt: SRI 30,29,0 DOES NOT ASSEMBLE CORRECTLY
   */
  assert(!(ins==i_sr && imm==0));

  clear_reg(dest);

  if (!logical && IMM_SIZE(imm))
  {
    Instruction_P imins;
    if     (ins==i_a)      imins=i_ai;
    else if (ins==i_a_cr)   imins=i_ai_cr;
    else if (ins==i_sf)     imins=i_sfi;
    else if (ins==i_sl)     imins=i_sli;
    else if (ins==i_sl_cr)  imins=i_sli_cr;
    else if (ins==i_sr)     imins=i_sri;
    else if (ins==i_sr_cr)  imins=i_sri_cr;
    else if (ins==i_sra)    imins=i_srai;
    else if (ins==i_sra_cr) imins=i_srai_cr;
    else if (ins==i_muls)   imins=i_muli;
    else
    {
      printf("Unknown immediate instruction for %s\n",get_instruction(ins));
      imins=ins;
    }

	if (do_macros) {
	    asm_printop("%s %s,%s,%ld",get_instruction(imins), reg_macro(dest), reg_macro(src), imm);
	} else {
	    asm_printop("%s %d,%d,%ld",get_instruction(imins), dest, src, imm);
	}

    return;
  }

  if (ins == i_a && IMMLOGU_SIZE(imm))
  {
    unsigned long uimm = imm;
	if (do_macros) {
	    asm_printop("%s %s,%s,%ld", get_instruction(i_cau), reg_macro(dest), reg_macro(src), uimm >> 16);
	} else {
	    asm_printop("%s %d,%d,%ld", get_instruction(i_cau), dest, src, uimm >> 16);
	}
    return;
  }

  if ((ins == i_a || ins == i_s) && IMM_SIZE((imm/2) +1) && dest != R_SP)
  {
    asm_comment("rir_ins: special casing add/sub of constant %ld", imm);
    if (ins == i_s && imm == 0x8000)
    {
      /* use -0x8000 as imm, which is immediate */
      rir_ins(i_a, src, -imm, dest);
    }
    else
    {
      /* use 2 adds or subs */
      long half = imm / 2;

      rir_ins(ins, src, half, dest);
      rir_ins(ins, dest, imm - half, dest);
    }
    return;
  }

  if (ins == i_and)
  {
    /*
     * See if we can use rlinm instruction, ie a single series of one bits.
     * This is prefered to generating an andiX. below, which may cause
     * a CR delay.
     */
    unsigned long x = imm;

    assert(x != 0);		/* should be handled above */
    if (is_a_mask(x) || is_a_mask(~x))
    {
      asm_comment("rir_ins: special casing and of constant %#lx", imm);
	if (do_macros) {
      asm_printop("%s %s,%s,0,0x%lx", get_instruction(i_rlinm), reg_macro(dest), reg_macro(src), imm);
	} else {
      asm_printop("%s %d,%d,0,0x%lx", get_instruction(i_rlinm), dest, src, imm);
	}
      return;
    }
  }
  if (ins == i_and_cr)
  {
    /*
     * See if we can use rlinm instruction, ie a single series of one bits.
     * This is prefered to generating an andiX. below, which may cause
     * a CR delay.
     */
    unsigned long x = imm;

    assert(x != 0);		/* should be handled above */
    if (is_a_mask(x) || is_a_mask(~x))
    {
      asm_comment("rir_ins: special casing and of constant %#lx", imm);
	if (do_macros) {
      asm_printop("%s %s,%s,0,0x%lx", get_instruction(i_rlinm_cr), reg_macro(dest), reg_macro(src), imm);
	} else {
      asm_printop("%s %d,%d,0,0x%lx", get_instruction(i_rlinm_cr), dest, src, imm);
	}
      return;
    }
  }


  if (logical && IMMLOGL_SIZE(imm))  /* Lower 16 bit load */
  {
    Instruction_P ilins;
    if     (ins==i_and) ilins = i_andil_cr;
    else if (ins==i_or)  ilins = i_oril;
    else if (ins==i_xor) ilins = i_xoril;
    else if (ins==i_and_cr)ilins = i_andil_cr;
    else error(ERROR_SERIOUS, "Should never reach here");
	if (do_macros) {
	    asm_printop("%s %s,%s,%ld", get_instruction(ilins), reg_macro(dest), reg_macro(src), imm);
	} else {
	    asm_printop("%s %d,%d,%ld", get_instruction(ilins), dest, src, imm);
	}
    return;
  }

  if (logical && IMMLOGU_SIZE(imm))  /* Upper 16 bit load */
  {
    unsigned long uimm = imm;
    Instruction_P iuins;
    if     (ins==i_and) iuins = i_andiu_cr;
    else if (ins==i_or)  iuins = i_oriu;
    else if (ins==i_xor) iuins = i_xoriu;
    else if (ins==i_and_cr)iuins = i_andiu_cr;
    else error(ERROR_SERIOUS, "Should never reach here");
	if (do_macros) {
	    asm_printop("%s %s,%s,%ld",get_instruction(iuins), reg_macro(dest), reg_macro(src), uimm >> 16);
	} else {
	    asm_printop("%s %d,%d,%ld",get_instruction(iuins), dest, src, uimm >> 16);
	}
    return;
  }

  if (ins == i_or)
  {
    /* or lower and then upper end */
    unsigned long uimm = imm;
	if (do_macros) {
	    asm_printop("%s %s,%s,0x%lx", get_instruction(i_oril), reg_macro(dest), reg_macro(src), uimm & 0xffff);
	    asm_printop("%s %s,%s,0x%lx", get_instruction(i_oriu), reg_macro(dest), reg_macro(dest), uimm >> 16);
	} else {
	    asm_printop("%s %d,%d,0x%lx", get_instruction(i_oril), dest, src, uimm & 0xffff);
	    asm_printop("%s %d,%d,0x%lx", get_instruction(i_oriu), dest, dest, uimm >> 16);
	}

    return;
  }

  /* default: use temp reg for large constant */
  asm_comment("rir_ins: large constant in R_TMP0");
  if (src == R_TMP0)
    error(ERROR_SERIOUS, "rir_ins: temp reg in use when needed for large constant");	/* should not happen */
  ld_const_ins(imm, R_TMP0);
  rrr_ins(ins, src, R_TMP0, dest);
}

/* register to register pseudo instruction */
void rr_ins(Instruction_P ins, int src, int dest)
{
  CHECKREG(dest); CHECKREG(src);

  clear_reg(dest);
  if (ins == i_not)
    rir_ins(i_sf, src, -1, dest);		/* implements monadic not */
  else
	if (do_macros) {
	    asm_printop("%s %s,%s", get_instruction(ins), reg_macro(dest), reg_macro(src));
	} else {
	    asm_printop("%s %d,%d", get_instruction(ins), dest, src);
	}
}



/* mov fixed point reg to another */
void mov_rr_ins(int src, int dest)
{
  CHECKREG(dest); CHECKREG(src);

  if (src != dest)
  {
    clear_reg(dest);
    /* move by i_oril of src with 0 to dest */
	if (do_macros) {
	    asm_printf( "\t%s\t%s,%s,%d", get_instruction(i_oril), reg_macro(dest), reg_macro(src), 0);
	} else {
	    asm_printf( "\t%s\t%d,%d,%d", get_instruction(i_oril), dest, src, 0);
	}
  }
}


/* load const into fixed point reg */
void ld_const_ins(long imm, int dest)
{
  CHECKREG(dest);

  clear_reg(dest);

  if (IMM_SIZE(imm))
  {
	if (do_macros) {
	    asm_printop("%s %s,%ld", get_instruction(i_lil), reg_macro(dest), imm);
	} else {
	    asm_printop("%s %d,%ld", get_instruction(i_lil), dest, imm);
	}
  }
  else
  {
    unsigned long uimm = imm;
    unsigned long uimml = uimm & 0xffff;

    /* load upper 16 bits */
	if (do_macros) {
	    asm_printop("%s %s,0x%lx",get_instruction(i_liu), reg_macro(dest), uimm >> 16);
	} else {
	    asm_printop("%s %d,0x%lx",get_instruction(i_liu), dest, uimm >> 16);
	}
    /* or in lower 16 bits if needed */
    if (uimml != 0)
    {
		if (do_macros) {
	      asm_printop("%s %s,%s,0x%lx", get_instruction(i_oril), reg_macro(dest), reg_macro(dest), uimml);
		} else {
	      asm_printop("%s %d,%d,0x%lx", get_instruction(i_oril), dest, dest, uimml);
		}
    }
  }
}


/* move from branch unit to fixed point reg */
void mf_ins(Instruction_P ins, int dest)
{
  if (ins !=i_mffs)
  {
    CHECKREG(dest);
    clear_reg(dest);
  }
  else
  {
    CHECKFREG(dest);
    clear_freg(dest);
  }
	if (do_macros) {
	  asm_printop("%s %s", get_instruction(ins), reg_macro(dest));
	} else {
	  asm_printop("%s %d", get_instruction(ins), dest);
	}
}

/* move to branch unit from fixed point reg */
void mt_ins(Instruction_P ins, int src)
{
  CHECKREG(src);
	if (do_macros) {
	  asm_printop("%s %s", get_instruction(ins), reg_macro(src));
	} else {
	  asm_printop("%s %d", get_instruction(ins), src);
	}
}

/* zeroadic pseudo instruction */
void z_ins(Instruction_P ins)
{
  asm_printop("%s", get_instruction(ins));
}

/*
 * Branch instructions. These have labels as destination.
 */

/* unconditional branch */
void uncond_ins(Instruction_P ins, int lab)
{
  asm_printop("%s L.%d", get_instruction(ins), lab);
}


/*
 * Call, and external jump instructions.
 */

/* jump/call to external identifier */
void extj_ins(Instruction_P ins, baseoff b)
{
  char *ext;

  asm_comment("extj_ins: global proc no=%d",(-b.base) - 1);
  assert(((-b.base) -1) >=0);

  ext = main_globals[(-b.base) - 1] ->dec_u.dec_val.dec_id;

  asm_printop("%s .%s", get_instruction(ins), ext);

  /*
   * By convention a special no-op is generated after a call,
   * which the linker changes to reload our TOC reg (2) if the
   * call is inter-module.
   *
   * We optimise by omitting the no-op where we know the call is intra-module.
   */
  if (diag != DIAG_NONE || !main_globals[(-b.base) -1] ->dec_u.dec_val.have_def)
  {
    asm_printop("%s %d,%d,%d", get_instruction(i_cror), 15, 15, 15);	/* conventional nop */
  }

}

/* jump/call to compiler generated external identifier, eg .mul */
void extj_special_ins(Instruction_P ins, char *nm)
{
  asm_printop("%s %s", get_instruction(ins), nm);
  asm_printop("%s %d,%d,%d", get_instruction(i_cror), 15, 15, 15);	/* conventional nop */
}


/*
 * Conditional instructions.
 */

/* branch conditional instruction */
void bc_ins(Instruction_P ins, int creg, int lab, int prediction)
{
  if (cpu == CPU_POWERPC)
  {

    int BI;
    int BO;
    BI=creg*4;

    if (ins==i_ble)
    {
      BO  = 4;
      BI += 1;
    }
    else if (ins ==i_blt)
    {
      BO  = 12;
      BI += 0;
    }
    else if (ins == i_bge)
    {
      BO  = 4;
      BI += 0;
    }
    else if (ins == i_bgt)
    {
      BO  = 12;
      BI += 1;
    }
    else if (ins == i_bne)
    {
      BO  = 4;
      BI += 2;
    }
    else if (ins == i_beq)
    {
      BO  = 12;
      BI += 2;
    }
    else
    {
      asm_printop("%s %d,L.%d",get_instruction(ins),creg,lab);
      return;
    }
    if (prediction)
    {
      BO+=1;
    }
    asm_printop("%s %d,%d,L.%d",get_instruction(i_bc),BO,BI,lab);
  }
  else
  {
	if (do_macros) {
	    asm_printop("%s %s,L.%d",get_instruction(ins),cr_macro(creg),lab);
	} else {
	    asm_printop("%s %d,L.%d",get_instruction(ins),creg,lab);
	}
  }
}
/* branch conditional instruction */
void long_bc_ins(Instruction_P ins, int creg, int lab, int prediction)
{
	/*
	 * Same as bc_ins only the test is reversed so that the lab is called
	 * directly so that there is no chance of the branch being out of range.
	 */

  long new_lab = lab;
  lab = new_label();
  if     (ins==i_blt) {ins = i_bge;}
  else if (ins==i_ble) {ins = i_bgt;}
  else if (ins==i_bne) {ins = i_beq;}
  else if (ins==i_beq) {ins = i_bne;}
  else if (ins==i_bgt) {ins = i_ble;}
  else if (ins==i_bge) {ins = i_blt;}
  else if (ins==i_bso) {ins = i_bns;}
  else if (ins==i_bns) {ins = i_bso;}
  else
  {
    error(ERROR_SERIOUS, "Don't know how to reverse this test");
  }

  if (cpu == CPU_POWERPC)
  {

    int BI;
    int BO;
    BI=creg*4;

    if (ins==i_ble)
    {
      BO  = 4;
      BI += 1;
    }
    else if (ins ==i_blt)
    {
      BO  = 12;
      BI += 0;
    }
    else if (ins == i_bge)
    {
      BO  = 4;
      BI += 0;
    }
    else if (ins == i_bgt)
    {
      BO  = 12;
      BI += 1;
    }
    else if (ins == i_bne)
    {
      BO  = 4;
      BI += 2;
    }
    else if (ins == i_beq)
    {
      BO  = 12;
      BI += 2;
    }
    else
    {
      asm_printop("%s %d,L.%d",get_instruction(ins),creg,lab);
      uncond_ins(i_b,new_lab);
      set_label(lab);
      return;
    }
    if (prediction)
    {
      BO+=1;
    }
    asm_printop("%s %d,%d,L.%d",get_instruction(i_bc),BO,BI,lab);
    uncond_ins(i_b,new_lab);
    set_label(lab);
    return;
  }
  else
  {
	if (do_macros) {
	    asm_printop("%s %s,L.%d",get_instruction(ins),cr_macro(creg),lab);
	} else {
	    asm_printop("%s %d,L.%d",get_instruction(ins),creg,lab);
	}

    uncond_ins(i_b,new_lab);
    set_label(lab);
    return;
  }
}


/* cmp or cmpl instruction */
void cmp_rr_ins(Instruction_P ins, int reg1, int reg2, int cr_dest)
{
  CHECKREG(reg1); CHECKREG(reg2);
	if (do_macros) {
	  asm_printop("%s %s,%s,%s", get_instruction(ins), cr_macro(cr_dest), reg_macro(reg1), reg_macro(reg2));
	} else {
	  asm_printop("%s %d,%d,%d", get_instruction(ins), cr_dest, reg1, reg2);
	}
}


/* for cmpi or cmpli instruction */
void cmp_ri_ins(Instruction_P ins, int reg, long imm, int cr_dest)
{
  CHECKREG(reg);

  /* +++ for equality can use cmpi or cmpli for larger constant range */
  if (ins == i_cmp && IMM_SIZE(imm))
  {
	if (do_macros) {
	    asm_printop("%si %s,%s,%ld", get_instruction(ins), cr_macro(cr_dest), reg_macro(reg), imm);
	} else {
	    asm_printop("%si %d,%d,%ld", get_instruction(ins), cr_dest, reg, imm);
	}
  }
  else if (ins == i_cmpl && IMMLOGL_SIZE(imm))
  {
	if (do_macros) {
	    asm_printop("%si %s,%s,%ld", get_instruction(ins), cr_macro(cr_dest), reg_macro(reg), imm);
	} else {
	    asm_printop("%si %d,%d,%ld", get_instruction(ins), cr_dest, reg, imm);
	}
  }
  else
  {
    /* use temp reg for large constant */
    asm_comment("condri_ins: large constant in R_TMP0");
    if (reg == R_TMP0)
      error(ERROR_SERIOUS, "cmp_ri_ins: temp reg in use when needed for large constant");	/* should not happen */
    ld_const_ins(imm, R_TMP0);
    cmp_rr_ins(ins, reg, R_TMP0, cr_dest);
  }
}

/*
 * Floating point instructions.
 */

void ldf_ro_ins(Instruction_P ins, baseoff a, int dest)
{
  CHECKREG(a.base); CHECKFREG(dest);

  clear_freg(dest);

  if (a.base == R_0)
  {
    if (a.offset != 0)
      error(ERROR_SERIOUS, "ldf_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
	if (do_macros) {
	    asm_printop("%sx %s,%s,%s", get_instruction(ins), freg_macro(dest), reg_macro(R_0), reg_macro(R_0));
	} else {
	    asm_printop("%sx %d,%d,%d", get_instruction(ins), dest, R_0, R_0);
	}
  }
  else
  if (IMM_SIZE(a.offset))
  {
	if (do_macros) {
	    asm_printop("%s %s,%d(%s)", get_instruction(ins), freg_macro(dest), (int)a.offset, reg_macro(a.base));
	} else {
	    asm_printop("%s %d,%d(%d)", get_instruction(ins), dest,(int)a.offset, a.base);
	}
  }
  else
  {
    /* offset too big, put in temp reg and used ld_rr_ins */
    /* +++ arrange stack variable to minimise this */
    asm_comment("ldf_ro_ins: big offset, use R_TMP0 and ldf_rr_ins");
    assert(a.base!=R_TMP0);		/* otherwise we corrupt it */
    ld_const_ins(a.offset, R_TMP0);
    ldf_rr_ins(ins, a.base, R_TMP0, dest);
  }
}


void ldf_rr_ins(Instruction_P ins, int reg1, int reg2, int dest)
{
  CHECKREG(reg1); CHECKREG(reg2); CHECKFREG(dest);

  clear_freg(dest);
	if (do_macros) {
	  asm_printop("%sx %s,%s,%s", get_instruction(ins), freg_macro(dest), reg_macro(reg1), reg_macro(reg2));
	} else {
	  asm_printop("%sx %d,%d,%d", get_instruction(ins), dest, reg1, reg2);
	}
}


void ldf_ins(Instruction_P ins, baseoff a, int dest)
{
  /*
   * Not a single instruction. Load from baseoff, which may be a global
   * requiring a temporary reg.
   */

  CHECKFREG(dest);

  if (!IS_FIXREG(a.base))
  {
    /* global */
    baseoff tmp_off;

    tmp_off.base = R_TMP0;
    tmp_off.offset = 0;

    set_ins(a, R_TMP0);
    ldf_ro_ins(ins, tmp_off, dest);
  }
  else
  {
    ldf_ro_ins(ins, a, dest);
  }
}


void stf_ro_ins(Instruction_P ins, int src, baseoff a)
{
  CHECKREG(a.base); CHECKFREG(src);

  /* in general we cannot cope with store using temp reg, catch it always */
  if (a.base == R_TMP0 && absval(a.offset) > (16 + 1 + 6) * 4)	/* leeway for mem_temp() */
    error(ERROR_SERIOUS, "stf_ro_ins: store of temp reg to offset not allowed");	/* should not happen */

  if (a.base == R_0)
  {
    if (a.offset != 0)
      error(ERROR_SERIOUS, "stf_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
	if (do_macros) {
	    asm_printop("%sx %s,%s,%s", get_instruction(ins), freg_macro(src), reg_macro(R_0), reg_macro(R_0));
	} else {
	    asm_printop("%sx %d,%d,%d", get_instruction(ins), src, R_0, R_0);
	}
  }
  else
  if (IMM_SIZE(a.offset))
  {
	if (do_macros) {
	    asm_printop("%s %s,%d(%s)", get_instruction(ins), freg_macro(src), (int)a.offset, reg_macro(a.base));
	} else {
	    asm_printop("%s %d,%d(%d)", get_instruction(ins), src,(int)a.offset, a.base);
	}
  }
  else
  {
    /* offset too big, put in temp reg and used stf_rr_ins */
    /* +++ arrange stack variable to minimise this */
    asm_comment("stf_ro_ins: big offset, use temp reg and stf_rr_ins");
    assert(a.base!=R_TMP0);		/* otherwise we corrupt it */
    ld_const_ins(a.offset, R_TMP0);
    stf_rr_ins(ins, src, a.base, R_TMP0);
  }
}


void stf_rr_ins(Instruction_P ins, int src, int reg1, int reg2)
{
  CHECKREG(reg1); CHECKREG(reg2);
	if (do_macros) {
	  asm_printop("%sx %s,%s,%s", get_instruction(ins), freg_macro(src), reg_macro(reg1), reg_macro(reg2));
	} else {
	  asm_printop("%sx %d,%d,%d", get_instruction(ins), src, reg1, reg2);
	}
}


void stf_ins(Instruction_P ins, int src, baseoff a)
{
  /*
   * Not a single instruction. Store into baseoff, which may be a global
   * requiring a temporary reg.
   */

  CHECKFREG(src);

  if (!IS_FIXREG(a.base))
  {
    /* global */
    baseoff tmp_off;

    tmp_off.base = R_TMP0;
    tmp_off.offset = 0;

    set_ins(a, R_TMP0);
    stf_ro_ins(ins, src, tmp_off);
  }
  else
  {
    stf_ro_ins(ins, src, a);
  }
}


void rrf_cmp_ins(Instruction_P ins, int reg1, int reg2, int cr_dest)
{
  CHECKFREG(reg1); CHECKFREG(reg2);
	if (do_macros) {
	  asm_printop("%s %s,%s,%s", get_instruction(ins), cr_macro(cr_dest), freg_macro(reg1), freg_macro(reg2));
	} else {
	  asm_printop("%s %d,%d,%d", get_instruction(ins), cr_dest, reg1, reg2);
	}
}


void rrf_ins(Instruction_P ins, int src, int dest)
{
  CHECKFREG(dest); CHECKFREG(src);

  clear_freg(dest);
	if (do_macros) {
  asm_printop("%s %s,%s", get_instruction(ins), freg_macro(dest), freg_macro(src));
	} else {
  asm_printop("%s %d,%d", get_instruction(ins), dest, src);
	}
}


void rrrf_ins(Instruction_P ins, int src1, int src2, int dest)
{
  CHECKFREG(dest); CHECKFREG(src1); CHECKFREG(src2);

  clear_freg(dest);
	if (do_macros) {
	  asm_printop("%s %s,%s,%s", get_instruction(ins), freg_macro(dest), freg_macro(src1), freg_macro(src2));
	} else {
	  asm_printop("%s %d,%d,%d", get_instruction(ins), dest, src1, src2);
	}
}

void rrrrf_ins(Instruction_P ins, int src1, int src2, int src3, int dest)
{
  CHECKFREG(dest); CHECKFREG(src1); CHECKFREG(src2); CHECKFREG(src3);

  clear_freg(dest);
	if (do_macros) {
	  asm_printop("%s %s,%s,%s,%s",get_instruction(ins),freg_macro(dest),freg_macro(src1),freg_macro(src2),freg_macro(src3));
	} else {
	  asm_printop("%s %d,%d,%d,%d",get_instruction(ins),dest,src1,src2,src3);
	}
}
void rlinm_ins(Instruction_P ins, int src1, int sl, unsigned int mask, int dest)
{
  CHECKREG(dest);CHECKREG(src1);
  assert(ins==i_rlinm||ins==i_rlinm_cr);
  clear_reg(dest);
	if (do_macros) {
	  asm_printop("%s %s,%s,%d,0x%x",get_instruction(ins),reg_macro(dest),reg_macro(src1),sl,mask);
	} else {
	  asm_printop("%s %d,%d,%d,0x%x",get_instruction(ins),dest,src1,sl,mask);
	}
}

void mfspr_ins(int spr, int dest)
{
  CHECKREG(dest);
  clear_reg(dest);
	if (do_macros) {
	  asm_printop("%s %s,%s",get_instruction(i_mfspr),reg_macro(dest),spr_macro(spr));
	} else {
	  asm_printop("%s %d,%d",get_instruction(i_mfspr),dest,spr);
	}
}
void mtfsfi_ins(int fld, int imm)
{
  asm_printop("%s %d,%d",get_instruction(i_mtfsfi),fld,imm);
}
void mtfsb0_ins(int bit)
{
  assert(bit>=0 && bit<=31);
  asm_printop("%s %d",get_instruction(i_mtfsb0),bit);
}
void mtfsb1_ins(int bit)
{
  assert(bit>=0 && bit<=31);
  asm_printop("%s %d",get_instruction(i_mtfsb1),bit);
}
void mcrfs_ins(int a, int b)
{
  assert(a>=0 && a<=7);
  assert(b>=0 && b<=7);
	if (do_macros) {
	  asm_printop("%s %s,%d",get_instruction(i_mcrfs),cr_macro(a),b);
	} else {
	  asm_printop("%s %d,%d",get_instruction(i_mcrfs),a,b);
	}
}
void lsi_ins(int src, int dest, int nb)
{
  asm_printop("%s %d,%d,%d",get_instruction(i_lsi),dest,src,nb);
}
void stsi_ins(int src, int dest, int nb)
{
  asm_printop("%s %d,%d,%d",get_instruction(i_stsi),src,dest,nb);
}
void comment(char *p)
{
#ifndef NDEBUG
  if (p==NULL)
  {
    asm_printf("\n");
  }
  else
  {
    asm_printf("        # %s\n",p);
  }
#else
  asm_printf("\n");
#endif
  return;
}

char * get_instruction(Instruction_P ins)
{
  char *w;
  switch (cpu)
  {
   case CPU_COMMON:
    w=ins->com;
    break;
   case CPU_RS6000:
    w=ins->pwr;
    break;
   case CPU_POWERPC:
    w=ins->ppc;
    break;
  };
  return w;
}
