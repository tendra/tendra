/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
$Author: release $
$Date: 1998/02/04 15:48:50 $
$Revision: 1.2 $
$Log: inst_fmt.c,v $
 * Revision 1.2  1998/02/04  15:48:50  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:01:25  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


/******************************************************************
		inst_formats.c

	Procs for outputting various POWER instruction formats to the
external file - as_file. Each procedure produces assembler for a family
of POWER operations, the actual member is passed as the string
understood by the assembler.

******************************************************************/

#include "config.h"
#include "geninst.h"

#include "proc.h"		
#include "myassert.h"
#include "flags.h"
#include "comment.h"
#include "translat.h"
#include "maxminmacs.h"		/* for absval() */
#include "stack.h"
#include "inst_fmt.h"
#include "macro.h"
#include "mask.h"
#define IS_POW2(c)		((c) != 0 && ((c) & ((c)-1)) == 0)

#define CHECKREG(r)		ASSERT(IS_FIXREG(r) && (!IS_SREG(r) || (r) >= p_sreg_first_save || (r == R_FP)) );
#define CHECKFREG(r)		ASSERT((!IS_FLT_SREG(r) || (r) >= p_sfreg_first_save));

extern FILE *as_file;
char * get_instruction PROTO_S ((Instruction_P));

char *ext_name PROTO_N ((id)) PROTO_T (long id)
{
  if (id < 0)
  {
    char *ext = main_globals[(-id) - 1]->dec_u.dec_val.dec_id;

    return ext;
  }
  else
  {
    static char sp[16];

    ASSERT(id > R_LAST);	/* not a confused register */

    sprintf(sp, "L.D%ld", id);
    return sp;
  }
}

/* +++ do better for offset to R_SP too big, trace reg or load extra base reg */

void ld_ro_ins PROTO_N ((ins,a,dest)) PROTO_T (Instruction_P ins X baseoff a X int dest)
{
  CHECKREG(dest); CHECKREG(a.base);

  clear_reg(dest);

  if (a.base == R_0)
  {
    /* base reg of R_0 is not normally allowed, special case 0 offset */
    if (a.offset != 0)
      fail("ld_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%sx\t%s,%s,%s",get_instruction(ins),reg_macro(dest),reg_macro(R_0),reg_macro(R_0));
#else
    fprintf(as_file, "\t%sx\t%d,%d,%d", get_instruction(ins), dest, R_0, R_0);
#endif
  }
  else if (IMM_SIZE(a.offset))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%d(%s)", get_instruction(ins), reg_macro(dest), (int)a.offset, reg_macro(a.base));
#else
    fprintf(as_file, "\t%s\t%d,%d(%d)", get_instruction(ins), dest, (int)a.offset, a.base);
#endif
  }
  else
  {
    /* offset too big, put in temp reg and used ld_rr_ins */
    /* +++ arrange stack variable to minimise this */
    ASSERT(a.base!=R_TMP0);
    ld_const_ins(a.offset, R_TMP0);
    ld_rr_ins(ins, a.base, R_TMP0, dest);
  }
}


void ld_rr_ins PROTO_N ((ins,reg1,reg2,dest)) PROTO_T (Instruction_P ins X int reg1 X int reg2 X int dest)
{
  CHECKREG(dest); CHECKREG(reg1); CHECKREG(reg2);
  ASSERT(reg1!=R_0);

  clear_reg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%sx\t%s,%s,%s\n", get_instruction(ins), reg_macro(dest), reg_macro(reg1), reg_macro(reg2));
#else
  fprintf(as_file, "\t%sx\t%d,%d,%d\n", get_instruction(ins), dest, reg1, reg2);
#endif
}


void set_ins PROTO_N ((a,dest)) PROTO_T (baseoff a X int dest)
{
  char *extname = ext_name(a.base);

  CHECKREG(dest);

  clear_reg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s,T.%s(%s)\n", get_instruction(i_l), reg_macro(dest), extname, reg_macro(R_TOC));
#else
  fprintf(as_file, "\t%s\t%d,T.%s(%d)\n", get_instruction(i_l), dest, extname, R_TOC);
#endif
  /* +++ offsets in TOC */
  if (a.offset != 0)
    rir_ins(i_a, dest, a.offset, dest);
}


void ld_ins PROTO_N ((ins,a,dest)) PROTO_T (Instruction_P ins X baseoff a X int dest)
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

    FULLCOMMENT2("ld_ins ext: off=%#x -> r%d", a.offset, dest);
    ASSERT(a.offset==0 || dest!=R_TMP0);

    /* load base into dest reg, then let ld_ro_ins do offset (which may need R_TMP0) */
    tmp_off.base = a.base;
    tmp_off.offset = 0;

    set_ins(tmp_off, dest);

    tmp_off.base = dest;
    tmp_off.offset = a.offset;

    ld_ro_ins(ins, tmp_off, dest);comment(NIL);
  }
  else
  {
    ld_ro_ins(ins, a, dest);comment(NIL);
  }
}


void st_ro_ins PROTO_N ((ins,src,a)) PROTO_T (Instruction_P ins X int src X baseoff a)
{
  CHECKREG(src); CHECKREG(a.base);


  /* in general we cannot cope with store using temp reg, catch it always */
  if ((src == R_TMP0 || a.base == R_TMP0) && absval(a.offset) > (16 + 1 + 6) * 4)	/* leeway for mem_temp() */
    fail("st_ro_ins: store of temp reg to offset not allowed");	/* should not happen */

  if (a.base == R_0)
  {
    if (a.offset != 0)
      fail("st_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%sx\t%s,%s,%s", get_instruction(ins), reg_macro(src), reg_macro(R_0), reg_macro(R_0));
#else
    fprintf(as_file, "\t%sx\t%d,%d,%d", get_instruction(ins), src, R_0, R_0);
#endif
  }
  else if (IMM_SIZE(a.offset))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%d(%s)", get_instruction(ins), reg_macro(src), (int)a.offset, reg_macro(a.base));
#else
    fprintf(as_file, "\t%s\t%d,%d(%d)", get_instruction(ins), src, (int)a.offset, a.base);
#endif
  }
  else
  {
    /* offset too big, put in temp reg and used st_rr_ins */
    /* +++ arrange stack variable to minimise this */
    COMMENT("st_ro_ins: big offset, use temp reg and st_rr_ins");
    ASSERT(a.base!=R_TMP0);		/* otherwise we corrupt it */
    ld_const_ins(a.offset, R_TMP0);
    st_rr_ins(ins, src, a.base, R_TMP0);
  }
}


void st_rr_ins PROTO_N ((ins,src,reg1,reg2)) PROTO_T (Instruction_P ins X int src X int reg1 X int reg2)
{
  CHECKREG(src); CHECKREG(reg1); CHECKREG(reg2);
  ASSERT(reg1!=R_0);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%sx\t%s,%s,%s\n", get_instruction(ins), reg_macro(src), reg_macro(reg1), reg_macro(reg2));
#else
  fprintf(as_file, "\t%sx\t%d,%d,%d\n", get_instruction(ins), src, reg1, reg2);
#endif
}


void st_ins PROTO_N ((ins,src,a)) PROTO_T (Instruction_P ins X int src X baseoff a)
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
      fail("st_ins: store of temp reg to global not allowed");	/* should not happen */

    tmp_off.base = R_TMP0;
    tmp_off.offset = 0;

    set_ins(a, R_TMP0);
    st_ro_ins(ins, src, tmp_off);comment(NIL);
  }
  else
  {
    st_ro_ins(ins, src, a);comment(NIL);
  }
}


/* 3 register operand instructions, source1, source2, destination */
void rrr_ins PROTO_N ((ins,src1,src2,dest)) PROTO_T (Instruction_P ins X int src1 X int src2 X int dest)
{
  CHECKREG(dest); CHECKREG(src1); CHECKREG(src2);

  clear_reg(dest);

  /* i_s is a pseudo instruction, use i_sf with reversed ops */
  if (ins == i_s)
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,%s\n", get_instruction(i_sf), reg_macro(dest), reg_macro(src2), reg_macro(src1));
#else
    fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(i_sf), dest, src2, src1);
#endif
  }
  else
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,%s\n", get_instruction(ins), reg_macro(dest), reg_macro(src1), reg_macro(src2));
#else
    fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(ins), dest, src1, src2);
#endif
  }
  
}


/* source register, immediate, destination register instructions */

void rir_ins PROTO_N ((ins,src,imm,dest)) PROTO_T (Instruction_P ins X int src X long imm X int dest)
{
  bool logical = ins == i_and || ins == i_or || ins == i_xor|| 
    ins ==i_and_cr|| ins==i_or_cr || ins==i_xor_cr;

  CHECKREG(dest); CHECKREG(src);
  ASSERT(ins!=i_divs&&ins!=i_div);	/* no divi, so we should not be called for div */

  /*
   * Check agaonst IBM assembler bug which we should avoid at higher levels:
   * IX25505 bosadt : SRI 30,29,0 DOES NOT ASSEMBLE CORRECTLY
   */
  ASSERT(!(ins==i_sr && imm==0));

  clear_reg(dest);

  if (!logical && IMM_SIZE(imm))
  {
    Instruction_P imins;
    if      (ins==i_a)       imins=i_ai;
    else if (ins==i_a_cr)    imins=i_ai_cr;
    else if (ins==i_sf)      imins=i_sfi;
    else if (ins==i_sl)      imins=i_sli;
    else if (ins==i_sl_cr)   imins=i_sli_cr;
    else if (ins==i_sr)      imins=i_sri;
    else if (ins==i_sr_cr)   imins=i_sri_cr;
    else if (ins==i_sra)     imins=i_srai;
    else if (ins==i_sra_cr)  imins=i_srai_cr;
    else if (ins==i_muls)    imins=i_muli;
    else
    {
      printf("Unknown immediate instruction for %s\n",get_instruction(ins));
      imins=ins;    
    }
    
#ifdef DO_ASSEMBLER_MACROS 
    fprintf(as_file,"\t%s\t%s,%s,%ld\n",get_instruction(imins), reg_macro(dest), reg_macro(src), imm);
#else
    fprintf(as_file,"\t%s\t%d,%d,%ld\n",get_instruction(imins), dest, src, imm);
#endif

    return;
  }

  if (ins == i_a && IMMLOGU_SIZE(imm))
  {
    unsigned long uimm = imm;
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,%ld\n", get_instruction(i_cau), reg_macro(dest), reg_macro(src), uimm >> 16);
#else
    fprintf(as_file, "\t%s\t%d,%d,%ld\n", get_instruction(i_cau), dest, src, uimm >> 16);
#endif
    return;
  }

  if ((ins == i_a || ins == i_s) && IMM_SIZE((imm/2)+1) && dest != R_SP)
  {
    COMMENT1("rir_ins: special casing add/sub of constant %ld", imm);
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

    ASSERT(x != 0);		/* should be handled above */
    if (is_a_mask(x) || is_a_mask(~x))
    {
      COMMENT1("rir_ins: special casing and of constant %#lx", imm);
#ifdef DO_ASSEMBLER_MACROS
      fprintf(as_file, "\t%s\t%s,%s,0,0x%lx\n", get_instruction(i_rlinm), reg_macro(dest), reg_macro(src), imm);
#else
      fprintf(as_file, "\t%s\t%d,%d,0,0x%lx\n", get_instruction(i_rlinm), dest, src, imm);
#endif
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

    ASSERT(x != 0);		/* should be handled above */
    if (is_a_mask(x) || is_a_mask(~x))
    {
      COMMENT1("rir_ins: special casing and of constant %#lx", imm);
#ifdef DO_ASSEMBLER_MACROS
      fprintf(as_file, "\t%s\t%s,%s,0,0x%lx\n", get_instruction(i_rlinm_cr), reg_macro(dest), reg_macro(src), imm);
#else
      fprintf(as_file, "\t%s\t%d,%d,0,0x%lx\n", get_instruction(i_rlinm_cr), dest, src, imm);
#endif
      return;
    }
  }
  

  if (logical && IMMLOGL_SIZE(imm))  /* Lower 16 bit load */
  {
    Instruction_P ilins;
    if      (ins==i_and)  ilins = i_andil_cr;
    else if (ins==i_or)   ilins = i_oril;
    else if (ins==i_xor)  ilins = i_xoril;
    else if (ins==i_and_cr) ilins = i_andil_cr;
    else fail("Should never reach here");
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,%ld\n", get_instruction(ilins), reg_macro(dest), reg_macro(src), imm);
#else
    fprintf(as_file, "\t%s\t%d,%d,%ld\n", get_instruction(ilins), dest, src, imm);
#endif
    return;
  }

  if (logical && IMMLOGU_SIZE(imm))  /* Upper 16 bit load */ 
  {
    unsigned long uimm = imm;
    Instruction_P iuins;
    if      (ins==i_and)  iuins = i_andiu_cr;
    else if (ins==i_or)   iuins = i_oriu;
    else if (ins==i_xor)  iuins = i_xoriu;
    else if (ins==i_and_cr) iuins = i_andiu_cr;
    else fail("Should never reach here");
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,%ld\n",get_instruction(iuins), reg_macro(dest), reg_macro(src), uimm >> 16);
#else
    fprintf(as_file, "\t%s\t%d,%d,%ld\n",get_instruction(iuins), dest, src, uimm >> 16);
#endif
    return;
  }

  if (ins == i_or)
  {
    /* or lower and then upper end */
    unsigned long uimm = imm;
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,0x%lx\n", get_instruction(i_oril), reg_macro(dest), reg_macro(src), uimm & 0xffff);
    fprintf(as_file, "\t%s\t%s,%s,0x%lx\n", get_instruction(i_oriu), reg_macro(dest), reg_macro(dest), uimm >> 16);
#else
    fprintf(as_file, "\t%s\t%d,%d,0x%lx\n", get_instruction(i_oril), dest, src, uimm & 0xffff);
    fprintf(as_file, "\t%s\t%d,%d,0x%lx\n", get_instruction(i_oriu), dest, dest, uimm >> 16);
#endif

    return;
  }

  /* default: use temp reg for large constant */
  COMMENT("rir_ins: large constant in R_TMP0");
  if (src == R_TMP0)
    fail("rir_ins: temp reg in use when needed for large constant");	/* should not happen */
  ld_const_ins(imm, R_TMP0);
  rrr_ins(ins, src, R_TMP0, dest);
}

/* register to register pseudo instruction */
void rr_ins PROTO_N ((ins,src,dest)) PROTO_T (Instruction_P ins X int src X int dest)
{
  CHECKREG(dest); CHECKREG(src);

  clear_reg(dest);
  if (ins == i_not)
    rir_ins(i_sf, src, -1, dest);		/* implements monadic not */
  else
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s\n", get_instruction(ins), reg_macro(dest), reg_macro(src));
#else
    fprintf(as_file, "\t%s\t%d,%d\n", get_instruction(ins), dest, src);
#endif
}



/* mov fixed point reg to another */
void mov_rr_ins PROTO_N ((src,dest)) PROTO_T (int src X int dest)
{
  CHECKREG(dest); CHECKREG(src);

  if (src != dest)
  {
    clear_reg(dest);
    /* move by i_oril of src with 0 to dest */
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%s,%d", get_instruction(i_oril), reg_macro(dest), reg_macro(src), 0);
#else
    fprintf(as_file, "\t%s\t%d,%d,%d", get_instruction(i_oril), dest, src, 0);
#endif
  }
}


/* load const into fixed point reg */
void ld_const_ins PROTO_N ((imm,dest)) PROTO_T (long imm X int dest)
{
  CHECKREG(dest);

  clear_reg(dest);

  if (IMM_SIZE(imm))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%ld\n", get_instruction(i_lil), reg_macro(dest), imm);
#else
    fprintf(as_file, "\t%s\t%d,%ld\n", get_instruction(i_lil), dest, imm);
#endif
  }
  else
  {
    unsigned long uimm = imm;
    unsigned long uimml = uimm & 0xffff;

    /* load upper 16 bits */
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,0x%lx\n",get_instruction(i_liu), reg_macro(dest), uimm >> 16);
#else
    fprintf(as_file, "\t%s\t%d,0x%lx\n",get_instruction(i_liu), dest, uimm >> 16);
#endif
    /* or in lower 16 bits if needed */
    if (uimml != 0)
    {
#ifdef DO_ASSEMBLER_MACROS
      fprintf(as_file, "\t%s\t%s,%s,0x%lx\n", get_instruction(i_oril), reg_macro(dest), reg_macro(dest), uimml);
#else
      fprintf(as_file, "\t%s\t%d,%d,0x%lx\n", get_instruction(i_oril), dest, dest, uimml);
#endif
    }
  }
}


/* move from branch unit to fixed point reg */
void mf_ins PROTO_N ((ins,dest)) PROTO_T (Instruction_P ins X int dest)
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
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s\n", get_instruction(ins), reg_macro(dest));
#else
  fprintf(as_file, "\t%s\t%d\n", get_instruction(ins), dest);
#endif
}

/* move to branch unit from fixed point reg */
void mt_ins PROTO_N ((ins,src)) PROTO_T (Instruction_P ins X int src)
{
  CHECKREG(src);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s\n", get_instruction(ins), reg_macro(src));
#else
  fprintf(as_file, "\t%s\t%d\n", get_instruction(ins), src);
#endif
}



/* zeroadic pseudo instruction */
void z_ins PROTO_N ((ins)) PROTO_T (Instruction_P ins)
{
  fprintf(as_file, "\t%s\n", get_instruction(ins));
}


/******************************************************************************
Branch instructions. These have labels as destination.
******************************************************************************/

/* unconditional branch */
void uncond_ins PROTO_N ((ins,lab)) PROTO_T (Instruction_P ins X int lab)
{
  fprintf(as_file, "\t%s\tL.%d\n", get_instruction(ins), lab);
}




/*
 * Call, and external jump instructions.
 */

/* jump/call to external identifier */
void extj_ins PROTO_N ((ins,b)) PROTO_T (Instruction_P ins X baseoff b)
{
  char *ext;

  FULLCOMMENT1("extj_ins: global proc no=%d", (-b.base) - 1);
  ASSERT(((-b.base)-1)>=0);

  ext = main_globals[(-b.base) - 1]->dec_u.dec_val.dec_id;

  fprintf(as_file, "\t%s\t.%s\n", get_instruction(ins), ext);

  /*
   * By convention a special no-op is generated after a call,
   * which the linker changes to reload our TOC reg (2) if the
   * call is inter-module.
   *
   * We optimise by omitting the no-op where we know the call is intra-module.
   */
  if (diagnose || !main_globals[(-b.base)-1]->dec_u.dec_val.have_def)
  {
    fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(i_cror), 15, 15, 15);	/* conventional nop */
  }
  
}

/* jump/call to compiler generated external identifier, eg .mul */
void extj_special_ins PROTO_N ((ins,nm)) PROTO_T (Instruction_P ins X char *nm)
{
  fprintf(as_file, "\t%s\t%s\n", get_instruction(ins), nm);
  fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(i_cror), 15, 15, 15);	/* conventional nop */
}


/*
 * Conditional instructions.
 */

/* branch conditional instruction */
void bc_ins PROTO_N ((ins,creg,lab,prediction)) PROTO_T (Instruction_P ins X int creg X int lab X int prediction)
{
  if(architecture == POWERPC_CODE)
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
      BO  = 4 ;
      BI += 0;
    } 
    else if (ins == i_bgt)
    {
      BO  = 12;
      BI += 1;
    }
    else if(ins == i_bne)
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
      fprintf(as_file,"\t%s\t%d,L.%d\n",get_instruction(ins),creg,lab);
      return;
    }
    if(prediction)
    {
      BO+=1;
    }
    fprintf(as_file,"\t%s\t%d,%d,L.%d\n",get_instruction(i_bc),BO,BI,lab);
  }
  else
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file,"\t%s\t%s,L.%d\n",get_instruction(ins),cr_macro(creg),lab);
#else
    fprintf(as_file,"\t%s\t%d,L.%d\n",get_instruction(ins),creg,lab);
#endif
  }
}
/* branch conditional instruction */
void long_bc_ins PROTO_N ((ins,creg,lab,prediction)) PROTO_T (Instruction_P ins X int creg X int lab X int prediction)
{
  /* same as bc_ins only the test is reversed so that the lab is called directly so that there is no chance of the branch being out of range */

  long new_lab = lab;
  lab = new_label();
  if      (ins==i_blt){ins = i_bge;}
  else if (ins==i_ble){ins = i_bgt;}
  else if (ins==i_bne){ins = i_beq;}
  else if (ins==i_beq){ins = i_bne;}
  else if (ins==i_bgt){ins = i_ble;}
  else if (ins==i_bge){ins = i_blt;}
  else if (ins==i_bso){ins = i_bns;}
  else if (ins==i_bns){ins = i_bso;}
  else
  {
    fail("Don't know how to reverse this test");
  }
  
  if(architecture == POWERPC_CODE)
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
      BO  = 4 ;
      BI += 0;
    } 
    else if (ins == i_bgt)
    {
      BO  = 12;
      BI += 1;
    }
    else if(ins == i_bne)
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
      fprintf(as_file,"\t%s\t%d,L.%d\n",get_instruction(ins),creg,lab);
      uncond_ins(i_b,new_lab);
      set_label(lab);
      return;
    }
    if(prediction)
    {
      BO+=1;
    }
    fprintf(as_file,"\t%s\t%d,%d,L.%d\n",get_instruction(i_bc),BO,BI,lab);
    uncond_ins(i_b,new_lab);
    set_label(lab);
    return;
  }
  else
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file,"\t%s\t%s,L.%d\n",get_instruction(ins),cr_macro(creg),lab);
#else
    fprintf(as_file,"\t%s\t%d,L.%d\n",get_instruction(ins),creg,lab);

#endif
    uncond_ins(i_b,new_lab);
    set_label(lab);
    return;
  }
}


/* cmp or cmpl instruction */
void cmp_rr_ins PROTO_N ((ins,reg1,reg2,cr_dest)) PROTO_T (Instruction_P ins X int reg1 X int reg2 X int cr_dest)
{
  CHECKREG(reg1); CHECKREG(reg2);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s,%s,%s\n", get_instruction(ins), cr_macro(cr_dest), reg_macro(reg1), reg_macro(reg2));
#else
  fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(ins), cr_dest, reg1, reg2);
#endif
}


/* for cmpi or cmpli instruction */
void cmp_ri_ins PROTO_N ((ins,reg,imm,cr_dest)) PROTO_T (Instruction_P ins X int reg X long imm X int cr_dest)
{
  CHECKREG(reg);

  /* +++ for equality can use cmpi or cmpli for larger constant range */
  if (ins == i_cmp && IMM_SIZE(imm))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%si\t%s,%s,%ld\n", get_instruction(ins), cr_macro(cr_dest), reg_macro(reg), imm);
#else
    fprintf(as_file, "\t%si\t%d,%d,%ld\n", get_instruction(ins), cr_dest, reg, imm);
#endif
  }
  else if (ins == i_cmpl && IMMLOGL_SIZE(imm))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%si\t%s,%s,%ld\n", get_instruction(ins), cr_macro(cr_dest), reg_macro(reg), imm);
#else
    fprintf(as_file, "\t%si\t%d,%d,%ld\n", get_instruction(ins), cr_dest, reg, imm);
#endif
  }
  else
  {
    /* use temp reg for large constant */
    COMMENT("condri_ins: large constant in R_TMP0");
    if (reg == R_TMP0)
      fail("cmp_ri_ins: temp reg in use when needed for large constant");	/* should not happen */
    ld_const_ins(imm, R_TMP0);
    cmp_rr_ins(ins, reg, R_TMP0, cr_dest);
  }
}




/*
 * Floating point instructions.
 */

void ldf_ro_ins PROTO_N ((ins,a,dest)) PROTO_T (Instruction_P ins X baseoff a X int dest)
{
  CHECKREG(a.base); CHECKFREG(dest);

  clear_freg(dest);

  if (a.base == R_0)
  {
    if (a.offset != 0)
      fail("ldf_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%sx\t%s,%s,%s\n", get_instruction(ins), freg_macro(dest), reg_macro(R_0), reg_macro(R_0));
#else
    fprintf(as_file, "\t%sx\t%d,%d,%d\n", get_instruction(ins), dest, R_0, R_0);
#endif
  }
  else
  if (IMM_SIZE(a.offset))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%d(%s)\n", get_instruction(ins), freg_macro(dest), (int)a.offset, reg_macro(a.base));
#else
    fprintf(as_file, "\t%s\t%d,%d(%d)\n", get_instruction(ins), dest, (int)a.offset, a.base);
#endif
  }
  else
  {
    /* offset too big, put in temp reg and used ld_rr_ins */
    /* +++ arrange stack variable to minimise this */
    COMMENT("ldf_ro_ins: big offset, use R_TMP0 and ldf_rr_ins");
    ASSERT(a.base!=R_TMP0);		/* otherwise we corrupt it */
    ld_const_ins(a.offset, R_TMP0);
    ldf_rr_ins(ins, a.base, R_TMP0, dest);
  }
}


void ldf_rr_ins PROTO_N ((ins,reg1,reg2,dest)) PROTO_T (Instruction_P ins X int reg1 X int reg2 X int dest)
{
  CHECKREG(reg1); CHECKREG(reg2); CHECKFREG(dest);

  clear_freg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%sx\t%s,%s,%s\n", get_instruction(ins), freg_macro(dest), reg_macro(reg1), reg_macro(reg2));
#else
  fprintf(as_file, "\t%sx\t%d,%d,%d\n", get_instruction(ins), dest, reg1, reg2);
#endif
}


void ldf_ins PROTO_N ((ins,a,dest)) PROTO_T (Instruction_P ins X baseoff a X int dest)
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


void stf_ro_ins PROTO_N (( ins,src,a)) PROTO_T (Instruction_P ins X int src X baseoff a)
{
  CHECKREG(a.base); CHECKFREG(src);

  /* in general we cannot cope with store using temp reg, catch it always */
  if (a.base == R_TMP0 && absval(a.offset) > (16 + 1 + 6) * 4)	/* leeway for mem_temp() */
    fail("stf_ro_ins: store of temp reg to offset not allowed");	/* should not happen */

  if (a.base == R_0)
  {
    if (a.offset != 0)
      fail("stf_ro_ins: non zero offset to R_0");
    /* with XXXx (indexed instructions) RA of R_0 is taken as constant 0 */
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%sx\t%s,%s,%s\n", get_instruction(ins), freg_macro(src), reg_macro(R_0), reg_macro(R_0));
#else
    fprintf(as_file, "\t%sx\t%d,%d,%d\n", get_instruction(ins), src, R_0, R_0);
#endif
  }
  else
  if (IMM_SIZE(a.offset))
  {
#ifdef DO_ASSEMBLER_MACROS
    fprintf(as_file, "\t%s\t%s,%d(%s)\n", get_instruction(ins), freg_macro(src), (int)a.offset, reg_macro(a.base));
#else
    fprintf(as_file, "\t%s\t%d,%d(%d)\n", get_instruction(ins), src, (int)a.offset, a.base);
#endif
  }
  else
  {
    /* offset too big, put in temp reg and used stf_rr_ins */
    /* +++ arrange stack variable to minimise this */
    COMMENT("stf_ro_ins: big offset, use temp reg and stf_rr_ins");
    ASSERT(a.base!=R_TMP0);		/* otherwise we corrupt it */
    ld_const_ins(a.offset, R_TMP0);
    stf_rr_ins(ins, src, a.base, R_TMP0);
  }
}


void stf_rr_ins PROTO_N ((ins,src,reg1,reg2)) PROTO_T (Instruction_P ins X int src X int reg1 X int reg2)
{
  CHECKREG(reg1); CHECKREG(reg2);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%sx\t%s,%s,%s\n", get_instruction(ins), freg_macro(src), reg_macro(reg1), reg_macro(reg2));
#else
  fprintf(as_file, "\t%sx\t%d,%d,%d\n", get_instruction(ins), src, reg1, reg2);
#endif
}


void stf_ins PROTO_N ((ins,src,a)) PROTO_T (Instruction_P ins X int src X baseoff a)
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


void rrf_cmp_ins PROTO_N ((ins,reg1,reg2,cr_dest)) PROTO_T (Instruction_P ins X int reg1 X int reg2 X int cr_dest)
{
  CHECKFREG(reg1); CHECKFREG(reg2);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s,%s,%s\n", get_instruction(ins), cr_macro(cr_dest), freg_macro(reg1), freg_macro(reg2));
#else
  fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(ins), cr_dest, reg1, reg2);
#endif
}


void rrf_ins PROTO_N ((ins,src,dest)) PROTO_T (Instruction_P ins X int src X int dest)
{
  CHECKFREG(dest); CHECKFREG(src);

  clear_freg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s,%s\n", get_instruction(ins), freg_macro(dest), freg_macro(src));
#else
  fprintf(as_file, "\t%s\t%d,%d\n", get_instruction(ins), dest, src);
#endif
}


void rrrf_ins PROTO_N ((ins,src1,src2,dest)) PROTO_T(Instruction_P ins X int src1 X int src2 X int dest)
{
  CHECKFREG(dest); CHECKFREG(src1); CHECKFREG(src2);

  clear_freg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file, "\t%s\t%s,%s,%s\n", get_instruction(ins), freg_macro(dest), freg_macro(src1), freg_macro(src2));
#else
  fprintf(as_file, "\t%s\t%d,%d,%d\n", get_instruction(ins), dest, src1, src2);
#endif
}

void rrrrf_ins PROTO_N ((ins,src1,src2,src3,dest)) PROTO_T (Instruction_P ins X int src1 X int src2 X int src3 X int dest )
{
  CHECKFREG(dest); CHECKFREG(src1); CHECKFREG(src2); CHECKFREG(src3);
  
  clear_freg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file,"\t%s\t%s,%s,%s,%s\n",get_instruction(ins),freg_macro(dest),freg_macro(src1),freg_macro(src2),freg_macro(src3));
#else
  fprintf(as_file,"\t%s\t%d,%d,%d,%d\n",get_instruction(ins),dest,src1,src2,src3);
#endif
}
void rlinm_ins PROTO_N ((ins,src1,sl,mask,dest)) PROTO_T (Instruction_P ins X int src1 X int sl X unsigned int mask X int dest )
{
  CHECKREG(dest);CHECKREG(src1);
  ASSERT(ins==i_rlinm||ins==i_rlinm_cr);
  clear_reg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file,"\t%s\t%s,%s,%d,0x%x\n",get_instruction(ins),reg_macro(dest),reg_macro(src1),sl,mask);
#else
  fprintf(as_file,"\t%s\t%d,%d,%d,0x%x\n",get_instruction(ins),dest,src1,sl,mask);
#endif
}

void mfspr_ins PROTO_N ((spr,dest)) PROTO_T (int spr X int dest )
{  
  CHECKREG(dest);
  clear_reg(dest);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file,"\t%s\t%s,%s\n",get_instruction(i_mfspr),reg_macro(dest),spr_macro(spr));
#else
  fprintf(as_file,"\t%s\t%d,%d\n",get_instruction(i_mfspr),dest,spr);
#endif
}
void mtfsfi_ins PROTO_N ((fld,imm)) PROTO_T (int fld X int imm )
{
  fprintf(as_file,"\t%s\t%d,%d\n",get_instruction(i_mtfsfi),fld,imm);
}
void mtfsb0_ins PROTO_N ((bit)) PROTO_T (int bit)
{
  ASSERT(bit>=0 && bit<=31);
  fprintf(as_file,"\t%s\t%d\n",get_instruction(i_mtfsb0),bit);
}
void mtfsb1_ins PROTO_N ((bit)) PROTO_T (int bit)
{
  ASSERT(bit>=0 && bit<=31);
  fprintf(as_file,"\t%s\t%d\n",get_instruction(i_mtfsb1),bit);
}
void mcrfs_ins PROTO_N ((a,b)) PROTO_T (int a X int b)
{
  ASSERT(a>=0 && a<=7);
  ASSERT(b>=0 && b<=7);
#ifdef DO_ASSEMBLER_MACROS
  fprintf(as_file,"\t%s\t%s,%d\n",get_instruction(i_mcrfs),cr_macro(a),b);
#else
  fprintf(as_file,"\t%s\t%d,%d\n",get_instruction(i_mcrfs),a,b);
#endif
}
void lsi_ins PROTO_N ((src,dest,nb)) PROTO_T (int src X int dest X int nb)
{
  fprintf(as_file,"\t%s\t%d,%d,%d\n",get_instruction(i_lsi),dest,src,nb);
}
void stsi_ins PROTO_N ((src,dest,nb)) PROTO_T (int src X int dest X int nb)
{
  fprintf(as_file,"\t%s\t%d,%d,%d\n",get_instruction(i_stsi),src,dest,nb);
}
void comment PROTO_N ((p)) PROTO_T (char *p)
{
#ifdef DEBUG_POWERTRANS
  if (p==NIL)
  {
    fprintf(as_file,"\n");
  }
  else
  {
    fprintf(as_file,"        # %s\n",p);
  }
#else
  fprintf(as_file,"\n");
#endif
  return;
}

char * get_instruction PROTO_N ((ins)) PROTO_T (Instruction_P ins)
{
  char *w;
  switch(architecture)
  {
   case COMMON_CODE:
    w=ins->com;
    break;
   case RS6000_CODE:
    w=ins->pwr;
    break;
   case POWERPC_CODE:
    w=ins->ppc;
    break;
  };
  return w;
}
