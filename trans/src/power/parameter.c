/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/aldefs.h>
#include <construct/dec.h>

#include <main/flags.h>
#include <main/print.h>

#include "procrec.h"
#include "geninst.h"
#include "translate.h"
#include "make_code.h"
#include "proc.h"
#include "stack.h"
#include "mem_copy.h"
#include "parameter.h"
#include "stack.h"
#include "scan.h"
#include "localexpmacs.h"
#include "locate.h"

bool suspected_varargs = 0;
int saved_varargs_register=0;
int saved_varargs_offset = 0;

typedef struct
{
  exp par;
  int dest;
  int copied;
} TREG;

static int spare_fixed;/* The spare t-reg used in case of looping copy i.e if 3-->4 and 4-->3
			  replace with 3-->spare_fixed 4-->3 spare_fixed-->4  */
static int spare_float;

static int copying_fixed;
static int copying_float;
static bool remember;
static long fixedfree;
static long floatfree;


static TREG fixed_array[13];
static TREG float_array[14];

static void do_fixed_params(void);
static void do_float_params(void);
static void copy_fixed(int);
static void copy_float(int);
static void clear_fixed(void);
static void clear_float(void);
static void set_fixed(exp,int,int);
static void set_float(exp,int,int);
static int getspare(long);
static void track_fixed(int,exp);
static void track_float(int,exp);
static int end_param;

void output_parameters(exp e)
{
  exp par;

  if (e->tag ==general_proc_tag)
  {
    end_param = GENERAL_PROC_PARAM_REGS + R_FIRST_PARAM - 1;
  }
  else
  {
    end_param = PROC_PARAM_REGS + R_FIRST_PARAM - 1;
  }

  /* Outputs the code for the parameters */
  fixedfree = PROC_TREGS;
  floatfree = PROC_FLT_TREGS;
  clear_fixed();
  clear_float();

  par = son(e);

  for (;;)
  {
    int param_reg;
    exp init_exp;
    int param_size;
    int param_align;
    int param_offset;
    bool is_float;
    bool src_in_reg;
    bool dest_in_reg;
    baseoff stackpos;
    where dest;

    if ((!isparam(par)) ||
	(par->tag!=ident_tag) ||
	(son(par)->tag ==formal_callee_tag))
      break;

    init_exp = son(par);
    is_float = is_floating(sh(init_exp)->tag);
    param_reg = props(init_exp);
    param_size = shape_size(sh(init_exp));
    param_align = shape_align(sh(init_exp));
    param_offset = no(init_exp) >>3;
    src_in_reg = param_reg !=0;
    dest_in_reg = (props(par) & inanyreg)!=0;


    if (src_in_reg==1)
    {
      if (is_float)
      {
	p_float_params++;
      }
      else
      {
	p_fixed_params++;
      }
    }

    stackpos=boff_location(ENCODE_FOR_BOFF(param_offset,INPUT_CALLER_PARAMETER));


    clearvarargparam(par);

    if (dest_in_reg==0
	&& !p_has_no_vcallers
	&& isvis(par)
	&& props(init_exp)!=0
	&& last_caller_param(par))
    {
      /* VARARGS */
      int last_size;
      int pr;
      baseoff v;
      v = stackpos;

      setvarargparam(par);

      if (param_size == 0)
      {
	/* void from <varargs.h> */
	param_size = 32;
	param_align = 32;
      }

      last_size = param_size;
      pr = R_FIRST_PARAM + ALIGNNEXT(no(init_exp) + last_size, 32) / 32;

      v.offset += ALIGNNEXT(last_size, 32) / 8;
      /* now word align to allow for non word aligned last param */
      v.offset &= ~3;
      suspected_varargs = 1;
      saved_varargs_offset = v.offset;
      saved_varargs_register = pr;
      while (pr <= end_param)
      {
	st_ro_ins(i_st, pr, v);asm_comment("varargs save all param regs");
	pr++;
	v.offset += 4;
      }
    }
    /* Set up dest */
    if (dest_in_reg==1)
    {
      setregalt(dest.answhere,no(par));
    }
    else
    {
      instore is;
      is.b = stackpos;
      is.adval = 1;
      setinsalt(dest.answhere,is);
    }
    dest.ashwhere.ashsize  = param_size;
    dest.ashwhere.ashalign = param_align;


    /* Work out how the parameter is passed and where it will live */
    if (src_in_reg==0 && dest_in_reg==1)
    {
      /* STACK  --->  REGISTER */
      /* Use move for consistency */
      ans a;
      instore is;
      is.b = stackpos;
      is.adval = 0;
      setinsalt(a,is);
      move(a, dest, PROC_TREGS | PARAM_TREGS, is_signed(sh(init_exp)));
    }
    else if (src_in_reg==1 && dest_in_reg ==0)
    {
      /* REGISTER  --->  STACK */
      bool is_aggregate =IS_AGGREGATE(sh(init_exp));
      if (is_aggregate)
      {
	/* Whole or part of struct passed in param t-regs */
	int last_st_reg;
	int r;

	last_st_reg = param_reg + (ALIGNNEXT(param_size, 32) /32) - 1;
	if (last_st_reg > end_param)
	{
	  last_st_reg = end_param;
	}
	for (r = param_reg; r <= last_st_reg; r++)
	{
	  st_ro_ins(i_st, r, stackpos);asm_comment("copy param struct onto stack");
	  stackpos.offset += 4;
	}
	p_fixed_params += (last_st_reg - param_reg);
      }
      else
      {
	ans a;
	freg fr;

	if (is_float)
	{
	  fr.dble = is_double_precision((sh(init_exp)));
	  fr.fr = param_reg;
	  setfregalt(a,fr);
	}
	else
	{
	  setregalt(a, param_reg);
	}
	move(a,dest,PROC_TREGS|PARAM_TREGS,0);
      }
    }
    else if (src_in_reg==1 && dest_in_reg==1)
    {
      /* REGISTER  --->  REGISTER */
      int dest_reg = no(par);
      assert(dest_reg!=0);/* This is now set up in scan.c */
      if ((props(par) & inreg_bits)!=0)
      {
	if (IS_SREG(dest_reg))
	{
	  /* FIXED REGISTER --> FIXED S-REG */
	  mov_rr_ins(param_reg , dest_reg);asm_comment("copy param into an s-reg");
	  track_fixed(param_reg,par);
	}
	else
	{
	  /* FIXED REGISTER --> FIXED T-REG */
	  set_fixed(par,param_reg ,  dest_reg);
	}
      }
      else
      {
	if (IS_FLT_SREG(dest_reg))
	{
	  /* FLOAT REGISTER --> FLOAT S-REG */
	  rrf_ins(i_fmr,param_reg , dest_reg);
	  track_float(param_reg,par);
	}
	else
	{
	  /* FLOAT REGISTER --> FLOAT T-REG */
	  set_float(par,param_reg , dest_reg);
	}
      }
    }
    else
    {
      /* LIVES IN PLACE ON STACK */
    }

    par = bro(son(par));
  }
  do_fixed_params();
  do_float_params();
}


static void do_fixed_params(void)
{
  int r;

  spare_fixed = getspare(fixedfree);
  copying_fixed = spare_fixed;
  copy_fixed(spare_fixed);

  for (r=R_FIRST_PARAM;r<=end_param;r++)
  {
    remember = 0;
    copying_fixed = r;
    copy_fixed(r);
    if (remember==1)
    {
      mov_rr_ins(spare_fixed , copying_fixed);asm_comment("move param to its new reg");
      track_fixed(spare_fixed , fixed_array[copying_fixed].par);
    }
  }
}
static void do_float_params(void)
{
  int r;

  spare_float = getspare(floatfree);
  copying_float = spare_float;
  copy_float(spare_float);

  for (r=FR_FIRST_PARAM;r<=FR_LAST_PARAM;r++)
  {
    remember = 0;
    copying_float = r;
    copy_float(r);
    if (remember==1)
    {
      rrf_ins(i_fmr,spare_float,copying_float);
      track_float(spare_float,float_array[copying_float].par);
    }
  }
}
static void copy_fixed(int reg)
{
  if (fixed_array[reg].copied==1)
  {
    return;
  }
  if (fixed_array[reg].dest==reg)
  {
    fixed_array[reg].copied=1;
    return;
  }
  if (fixed_array[reg].dest==copying_fixed)
  {
    /* We have gone round in a loop */
    remember = 1;
    mov_rr_ins(reg,spare_fixed);asm_comment("copy param reg to new location");
    fixed_array[reg].copied=1;
    return;
  }
  copy_fixed(fixed_array[reg].dest);
  mov_rr_ins(reg,fixed_array[reg].dest);asm_comment("copy param reg to new reg");
  track_fixed(reg,fixed_array[reg].par);
  fixed_array[reg].copied=1;
}
static void copy_float(int reg)
{
  if (float_array[reg].copied==1)
  {
    return;
  }
  if (float_array[reg].dest==reg)
  {
    float_array[reg].copied=1;
    return;
  }
  if (float_array[reg].dest==copying_float)
  {
    /* We have gone round in a loop */
    remember = 1;
    rrf_ins(i_fmr,reg,spare_float);
    float_array[reg].copied=1;
    return;
  }
  copy_float(float_array[reg].dest);
  rrf_ins(i_fmr,reg,float_array[reg].dest);
  track_float(reg,float_array[reg].par);
  float_array[reg].copied=1;
}



static void clear_fixed(void)
{
  int r;
  for (r=0;r<=12;r++)
  {
    fixed_array[r].par = NULL;
    fixed_array[r].dest = 0;
    fixed_array[r].copied = 1;
  }
}
static void clear_float(void)
{
  int r;
  for (r=0;r<=13;r++)
  {
    float_array[r].par = NULL;
    float_array[r].dest = 0;
    float_array[r].copied = 1;
  }
}

static void set_fixed(exp p, int from, int to)
{
  assert(IS_PARAM_REG(from));
  assert(IS_TREG(to));
  assert(to!=R_TMP0);
  fixed_array[from].par = p;
  fixed_array[from].dest = to;
  fixed_array[from].copied = 0;
  fixedfree |= RMASK(to);
}
static void set_float(exp p, int from, int to)
{
  assert(IS_FLT_PARAM_REG(from));
  assert(IS_FLT_TREG(to));
  float_array[from].par = p;
  float_array[from].dest = to;
  float_array[from].copied = 0;
  floatfree |= RMASK(to);
}
static int getspare(long s)
{
  int r;
  for (r=0;r<=31;r++)
  {
    if ((s & RMASK(r)) ==0)
    {
      return r;
    }
  }
  error(ERR_SERIOUS, "getspare failed");
  return 100;
}

static void
track_fixed(int reg, exp id)
{
  exp def = son(id);

  if (pt(id)!=NULL && keep_eq_size(sh(def),sh(pt(id))))
  {
    if (isvar(id))
    {
      keepcont(pt(id),reg);
    }
    else
    {
      keepreg(pt(id),reg);
    }
  }
}

static void
track_float(int reg, exp id)
{
	UNUSED(reg);
	UNUSED(id);
}
