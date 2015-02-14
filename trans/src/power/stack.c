/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/error.h>

#include <main/flags.h>
#include <main/print.h>

#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translate.h"
#include "make_code.h"
#include "proc.h"
#include "stack.h"

/* All measurements in bytes */
long p_frame_size=0;		/* total size of frame */  
long p_locals_offset=0;	/* where the locals live  */
long p_maxargbytes=0;	/* the largest size of the param area */
long p_args_and_link_size=0;	/* used by alloca */
bool p_has_fp=0;

bool p_leaf=0;
bool p_has_back_chain=0;
bool p_save_all_sregs=0;
bool p_has_alloca=0;
bool p_has_vcallees=0;
bool p_has_no_vcallers=0;

long p_fixed_params=0;
long p_float_params=0;
long p_sreg_first_save=0;
long p_sfreg_first_save=0;

bool p_has_saved_sp=0;
long p_saved_sp_offset=0;
int p_return_label=0; /* the number of the label which contains the return */
ans p_result;
long p_callee_size;

bool p_has_tp;

exp p_current;
long p_no_of_returns =0;

/*
 * The function of this file is to keep a lot of the stack controlling 
 * functions in the same place, so that they can be easily and consistently
 * maintained. I have introduced several new variables to make things easier
 * to follow.
 *
	|              |
	|              |
------->|--------------|<======R_FP                v
	|   Saved      |                           |
	|    FPR       |                           |
	|              |                           |
	|--------------|                           |
	|   Saved      |                           |< p_frame_size(bytes)
	|    GPR       |                           |
	|              |                           |
	|--------------|                           |
	| Possible word|for 8 byte alignment       |
	|--------------|                           |
	|              |                           |
	|--------------|                           |
	|  Saved SP    |<-- If have saved_sp       |
	|--------------|  this is where it lives   |
	|              |                           | 
	|              |                           | 
	|              |                           | 
	|              |                           |
    >56 |--------------|         v                 | 
	|    Pn        |         |                 |                 
	|     .        |         |                 |       
	|     .        |         |                 |                 
	|     .        |         |                 |  
	|     .        |         |                 |     
	|    P1        |         |< PROC_ARGS_AND_ |                 
      24|--------------|         |     LINK_SIZE   |                 
	|   Saved TOC  |         |     (bytes)     |                 
      20|--------------|         |                 |                 
	|   Reserved2  |         |                 |                 
      16|--------------|         |                 |                 
	|   Reserved1  |         |                 |                 
      12|--------------|         |                 |                 
	|   Saved LR   |         |                 |                 
       8|--------------|         |                 |                 
	|   Saved CR   |         |                 |                 
       4|--------------|         |                 |                 
	|  Back Chain  |         |                 |                 
-----> 0|--------------|<=====R_SP                 ^
          STACK_TEMP
*/
void initialise_procedure(procrec *pr)
{
  p_sreg_first_save= pr->sreg_first_save;
  p_sfreg_first_save = pr->sfreg_first_save;
  p_has_alloca = pr->alloca_proc;
  p_save_all_sregs = pr->save_all_sregs;
  p_frame_size = pr->frame_size>>3; /* in bytes */
  p_locals_offset = pr->locals_offset>>3; /* in bytes */
  p_maxargbytes = pr->maxargs>>3; /* in bytes */
  p_has_fp = pr->has_fp;
  p_has_tp = pr->has_tp;
  p_has_saved_sp = pr->has_saved_sp;
  p_leaf = pr->leaf_proc;
  p_callee_size = pr->callee_size>>3;
  p_has_vcallees = pr->has_vcallees;
  p_has_no_vcallers = pr->has_no_vcallers;
  p_no_of_returns = pr->no_of_returns;
  
  p_fixed_params = 0;		/* Updated in make_ident_tag_code */
  p_float_params = 0;		/* Updated in make_ident_tag_code */
  p_has_back_chain = p_leaf ? 0 : diag != DIAG_NONE;
  p_args_and_link_size = p_leaf ? 0 : STACK_LINK_AREA_SIZE + p_maxargbytes;
  assert(pr->frame_size>=0 && (pr->frame_size&63) == 0);
  assert(pr->frame_size>=pr->maxargs);
}


void generate_procedure_prologue(void)
{
  int r;
  baseoff stackpos;

  stackpos.base = R_SP;
  stackpos.offset = 0;
  
  /* Get LR for non leaf */
  if( !p_leaf)
  {
    mf_ins(i_mflr,R_0);
  }
  /* 
   * Save floating point s-regs
   */
  if(p_sfreg_first_save != FR_NO_REG)
  {
    for(r = p_sfreg_first_save; r <= FR_LAST; r++)
    {
      if (IS_FLT_SREG(r))
      {
	stackpos.offset -= 8;
	stf_ro_ins(i_stfd, r, stackpos);
      }
    }
    assert(stackpos.offset >= -STACK_FLOAT_REG_DUMP_AREA_SIZE);
  }
  /*
   * Save fixed point s-regs
   */
  if (p_sreg_first_save != R_NO_REG)
  {
    if (p_sreg_first_save < R_28)
    {
      /* Use the stm instruction */
      stackpos.offset -= 4*(R_31+1-p_sreg_first_save);
      st_ro_ins(i_stm, p_sreg_first_save, stackpos);asm_comment("save fixed point s-regs");
    }
    else
    { 
      /* Less than or 4 stores so do individually */
      for (r=R_31;r>=p_sreg_first_save;r--)
      { 
	stackpos.offset -= 4;
	st_ro_ins(i_st,r,stackpos);asm_comment("save fixed point s-reg");
      }
    }
    assert(stackpos.offset >= -STACK_REG_DUMP_AREA_SIZE);
  }
  /* Align to next 8 byte boundary */
  stackpos.offset= -ALIGNNEXT(-stackpos.offset,8);
  /*
   * Make room for saved sp if we have one
   */
  if ( p_has_saved_sp )
  {
    stackpos.offset -= 8;
    p_saved_sp_offset = stackpos.offset;
  }
  /* 
   * Initialise the top pointer if needed 
   */
  if( p_has_tp )
  {
    baseoff a;
    
    /* This is where the backward pointing chain is held */
    a.base = R_SP;
    a.offset = 0;
    ld_ro_ins(i_l,a,R_TP);asm_comment("set up TP");
  }
  
  /* 
   * Initialize the frame pointer if needed
   */
  if ( p_has_fp )
  {
    mov_rr_ins( R_SP, R_FP );asm_comment("set up FP");
  }

  
  /*
   * Save the Link Register
   */
  if ( ! p_leaf )
  {
    if ( p_has_tp)
    {
      stackpos.base = R_TP;
    }
    else
    {
      stackpos.base = R_SP;
    }
    
    stackpos.offset = STACK_SAVED_LR;
    st_ro_ins(i_st, R_0, stackpos);asm_comment("save LR");
  }
  
  /* 
   * Decrease the stack pointer
   */
  
  stackpos.base = R_SP;
  
  if( p_has_back_chain )
  {
    stackpos.offset = - p_frame_size;
    st_ro_ins( i_stu , R_SP , stackpos );asm_comment("pull stack down with back chain");
  }
  else
  {
    if (p_frame_size !=0)
    {
      rir_ins(i_a, R_SP, -p_frame_size ,R_SP);
    }
  }
  /* Save sp on stack if necessary */
  if( p_has_saved_sp )
  {
    save_sp_on_stack();
  }
}


void generate_procedure_epilogue(void)
{
  baseoff saved_lr;
  
  if ( p_frame_size !=0 )
  {
    if ( p_has_fp )
    {
      /* Use frame pointer to collapse stack frame */
      mov_rr_ins( R_FP, R_SP );asm_comment("collapse frame using FP");
    }
    else if ( p_has_back_chain )
    {
	/* Use back chain to collapse stack frame */
      baseoff back_chain;
      back_chain.base=R_SP;
      back_chain.offset=0;
      ld_ro_ins(i_l, back_chain, R_SP);asm_comment("collapse stack frame");
    }
    else
    {
      /* Use frame size to collapse stack frame */
      rir_ins(i_a, R_SP, p_frame_size , R_SP );
    }
  }
  /* At this point the stack pointer is collapsed to where the s-regs 
     are stored */
  if(p_has_tp)
  {
    mov_rr_ins(R_TP,R_TEMP_TP);asm_comment("copy TP to TEMP_TP");
    restore_sregs(R_SP,0);
    mov_rr_ins(R_TEMP_TP,R_SP);asm_comment("collapse frame using TEMP_TP");
  }
  else
  {
    restore_sregs(R_SP,0);
  }
  /* At this point the stack pointer is in its return position */
  if (!p_leaf)
  {
    saved_lr.base = R_SP;
    saved_lr.offset = STACK_SAVED_LR;
    ld_ro_ins(i_l, saved_lr , R_TMP0);asm_comment("restore LR");
    mt_ins(i_mtlr, R_TMP0);
  }	
  z_ins(i_br);
}
void generate_untidy_procedure_epilogue(void)
{
  baseoff saved_lr;
  
  /* The stack pointer is not collapsed at all */
  if (p_has_tp && !p_leaf)/*We need R_TP later for the link */
  {
    mov_rr_ins(R_TP,R_TEMP_TP);asm_comment("copy TP to TEMP_TP");
  }
  /* load up R_TEMP_FP with the value of where the s-regs are stored */
  if(p_has_fp)
  {
    mov_rr_ins(R_FP,R_TEMP_FP);asm_comment("copy FP ro TEMP_FP");
    restore_sregs(R_TEMP_FP,0);
  }
  else if (p_has_back_chain)
  {
    baseoff back_chain;
    back_chain.base = R_SP;
    back_chain.offset = 0;
    ld_ro_ins(i_l,back_chain,R_TEMP_FP);
    restore_sregs(R_TEMP_FP,0);
  }
  else
  {
    restore_sregs(R_SP,p_frame_size);
  }
  /* s-regs are restored */
  if (!p_leaf)
  {
    if(p_has_tp)
    {
      saved_lr.base = R_TEMP_TP;
      saved_lr.offset = STACK_SAVED_LR;
    }
    else if(p_has_fp)
    {
      saved_lr.base = R_TEMP_FP;
      saved_lr.base = STACK_SAVED_LR;
    }
    else
    {
      saved_lr.base = R_SP;
      saved_lr.offset = STACK_SAVED_LR + p_frame_size;
    }
    ld_ro_ins(i_l,saved_lr,R_TMP0);asm_comment("restore LR");
    mt_ins(i_mtlr,R_TMP0);
  }
  z_ins(i_br);
}

	      
  
void save_sp_on_stack(void)
{
  baseoff saved_sp;
  
  /* Saves the value of the stack pointer on stack */
  assert(p_has_saved_sp);
  assert(p_has_fp);
  saved_sp.base = R_FP;
  saved_sp.offset = p_saved_sp_offset;
  st_ro_ins(i_st,R_SP,saved_sp);asm_comment("save sp on stack");
}
void get_sp_from_stack(void)
{
  baseoff saved_sp;
  
  /* Restores the stack pointer from the stack */
  assert(p_has_saved_sp);
  assert(p_has_fp);
  saved_sp.base = R_FP;
  saved_sp.offset = p_saved_sp_offset;
  ld_ro_ins(i_l,saved_sp,R_SP);asm_comment("get SP of stack");
}
void save_back_chain_using_frame_pointer(void)
{
  /* saves back chain using frame pointer */
  baseoff back_chain;
  back_chain.base = R_SP;
  back_chain.offset = 0;
  assert(p_has_fp);
  st_ro_ins(i_st,R_FP,back_chain);asm_comment("save back chain");
}

void restore_sregs(int start_base, int start_offset)
{
  baseoff stackpos;
  int r;
  
  assert(IS_TREG(start_base) || start_base == R_SP);
  assert(start_base!=R_TMP0);
  stackpos.base = start_base;
  stackpos.offset = start_offset;
  asm_comment("restore s-regs using %d offset %d bytes",start_base,start_offset);
  
  
  if (p_sfreg_first_save != FR_NO_REG)
  {
    for (r = p_sfreg_first_save; r <= FR_LAST; r++)
    {
      if (IS_FLT_SREG(r))
      {
	stackpos.offset -= 8;
	ldf_ro_ins(i_lfd, stackpos, r);
      }
    }
  }
  
  /* 
   * Restore fixed point s-regs 
   */
  if (p_sreg_first_save != R_NO_REG)
  {
    if (p_sreg_first_save < R_28)
    {
      /* Use lm instruction */
      stackpos.offset -= 4*(R_31+1-p_sreg_first_save);
      ld_ro_ins(i_lm, stackpos, p_sreg_first_save);asm_comment("restore fixed s-regs");
    }
    else
    {
      /* Less than or 4 loads so do individually */ 
      for (r=R_31;r>=p_sreg_first_save;r--)
      {
	stackpos.offset -=4;
	ld_ro_ins(i_l,stackpos,r);asm_comment("restore fixed s-reg");
      }
    }
  }
}
void restore_link_register(void)
{
  /* this function is only used by tail_call */
  baseoff saved_lr;
  asm_comment("restore link register");
  if (!p_leaf)
  {
    if (p_has_tp)
    {
      saved_lr.base = R_TP;
      saved_lr.offset = STACK_SAVED_LR;
    }
    else if(p_has_fp)
    {
      saved_lr.base = R_FP;
      saved_lr.offset = STACK_SAVED_LR;
    }
    else 
    {
      /* XXX: assert instead? */
      error(ERROR_SERIOUS, "Shouldn't be calling this function without R_TP or R_FP");
    }
    ld_ro_ins(i_l,saved_lr,R_TMP0);asm_comment("restore LR");
    mt_ins(i_mtlr,R_TMP0);
  }
}
