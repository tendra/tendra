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
$Date: 1998/02/04 15:49:02 $
$Revision: 1.2 $
$Log: parameter.c,v $
 * Revision 1.2  1998/02/04  15:49:02  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:18  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translat.h"
#include "makecode.h"
#include "machine.h"
#include "flags.h"
#include "myassert.h"
#include "comment.h"
#include "proc.h"
#include "stack.h"
#include "mem_copy.h"
#include "xalloc.h"
#include "parameter.h"
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
bool remember;
long fixedfree;
long floatfree;


TREG fixed_array[13];
TREG float_array[14];

static void do_fixed_params PROTO_S ((void));
static void do_float_params PROTO_S ((void));
static void copy_fixed PROTO_S ((int));
static void copy_float PROTO_S ((int));
static void clear_fixed PROTO_S ((void));
static void clear_float PROTO_S ((void));
static void set_fixed PROTO_S ((exp,int,int));
static void set_float PROTO_S ((exp,int,int));
static int getspare PROTO_S ((long));
void track_fixed PROTO_S ((int,exp));
void track_float PROTO_S ((int,exp));
static int end_param;

void output_parameters PROTO_N ((e)) PROTO_T (exp e)
{
  exp par;

  if (name(e)==general_proc_tag)
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
  
  for(;;)
  {
    int param_reg;
    exp init_exp;
    int param_size;
    int param_align;
    int param_offset;
    bool is_float ;
    bool src_in_reg;
    bool dest_in_reg;
    baseoff stackpos;
    where dest;
    
    if ((!isparam(par)) ||
	(name(par)!=ident_tag) ||
	(name(son(par))==formal_callee_tag))
      break;

    init_exp = son(par);
    is_float = is_floating(name(sh(init_exp)));
    param_reg = props(init_exp);
    param_size = shape_size(sh(init_exp));
    param_align = shape_align(sh(init_exp));
    param_offset = no(init_exp)>>3;
    src_in_reg = param_reg !=0;
    dest_in_reg = (props(par) & inanyreg)!=0;

    
    if (src_in_reg==1)
    {
      if(is_float)
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
	st_ro_ins(i_st, pr, v);comment("varargs save all param regs");
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

	last_st_reg = param_reg + (ALIGNNEXT(param_size, 32)/32) - 1;
	if (last_st_reg > end_param)
	{
	  last_st_reg = end_param;
	}
	for (r = param_reg; r <= last_st_reg; r++)
	{
	  st_ro_ins(i_st, r, stackpos);comment("copy param struct onto stack");
	  stackpos.offset += 4;
	}
	p_fixed_params +=(last_st_reg - param_reg);
      }
      else
      {
	ans a;
	freg fr;
	
	if(is_float)
	{
	  fr.dble = is_double_precision((sh(init_exp)));
	  fr.fr = param_reg;
	  setfregalt(a,fr);
	}
	else
	{
	  setregalt( a, param_reg);
	}
	move(a,dest,PROC_TREGS|PARAM_TREGS,0);
      }
    }
    else if(src_in_reg==1 && dest_in_reg==1)
    {
      /* REGISTER  --->  REGISTER */
      int dest_reg = no(par);
      ASSERT(dest_reg!=0);/* This is now set up in needscan*/
      if ((props(par) & inreg_bits)!=0)
      {
	if (IS_SREG(dest_reg))
	{
	  /* FIXED REGISTER --> FIXED S-REG */
	  mov_rr_ins(param_reg , dest_reg);comment("copy param into an s-reg");
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
	  rrf_ins(i_fmr,param_reg , dest_reg );
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
  return;
}


static void do_fixed_params PROTO_Z ()
{
  int r;

  spare_fixed = getspare(fixedfree) ;
  copying_fixed = spare_fixed;
  copy_fixed(spare_fixed);
  
  for(r=R_FIRST_PARAM;r<=end_param;r++)
  {
    remember = 0;
    copying_fixed = r;
    copy_fixed(r);
    if (remember==1)
    {
      mov_rr_ins( spare_fixed , copying_fixed );comment("move param to its new reg");
      track_fixed( spare_fixed , fixed_array[copying_fixed].par);
    }
  }
  return;
}  
static void do_float_params PROTO_Z ()
{
  int r;
  
  spare_float = getspare(floatfree);
  copying_float = spare_float;
  copy_float(spare_float);
  
  for(r=FR_FIRST_PARAM;r<=FR_LAST_PARAM;r++)
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
  return;
} 
static void copy_fixed PROTO_N ((reg)) PROTO_T (int reg)
{
  if(fixed_array[reg].copied==1)
  {
    return;
  }
  if(fixed_array[reg].dest==reg)
  {
    fixed_array[reg].copied=1;
    return;
  }
  if(fixed_array[reg].dest==copying_fixed)
  {
    /* We have gone round in a loop */
    remember = 1;
    mov_rr_ins(reg,spare_fixed);comment("copy param reg to new location");
    fixed_array[reg].copied=1;
    return;
  }
  copy_fixed(fixed_array[reg].dest);
  mov_rr_ins(reg,fixed_array[reg].dest);comment("copy param reg to new reg");
  track_fixed(reg,fixed_array[reg].par);
  fixed_array[reg].copied=1;
  return;
}
static void copy_float PROTO_N ((reg)) PROTO_T (int reg)
{
  if(float_array[reg].copied==1)
  {
    return;
  }
  if(float_array[reg].dest==reg)
  {
    float_array[reg].copied=1;
    return;
  }
  if(float_array[reg].dest==copying_float)
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
  return;
} 



static void clear_fixed PROTO_Z ()
{
  int r;
  for(r=0;r<=12;r++)
  {
    fixed_array[r].par = nilexp;
    fixed_array[r].dest = 0;
    fixed_array[r].copied = 1;
  }
  return;
}
static void clear_float PROTO_Z ()
{
  int r;
  for (r=0;r<=13;r++)
  {
    float_array[r].par = nilexp;
    float_array[r].dest = 0;
    float_array[r].copied = 1;
  }
  return;
}

static void set_fixed PROTO_N ((p,from,to)) PROTO_T (exp p X int from X int to )
{
  ASSERT(IS_PARAM_REG(from));
  ASSERT(IS_TREG(to));
  ASSERT(to!=R_TMP0);
  fixed_array[from].par = p;
  fixed_array[from].dest = to;
  fixed_array[from].copied = 0;
  fixedfree |= RMASK(to);
}
static void set_float PROTO_N ((p,from,to)) PROTO_T (exp p X int from X int to )
{
  ASSERT(IS_FLT_PARAM_REG(from));
  ASSERT(IS_FLT_TREG(to));
  float_array[from].par = p;
  float_array[from].dest = to;
  float_array[from].copied = 0;
  floatfree |= RMASK(to);
}
static int getspare PROTO_N ((s)) PROTO_T (long s)
{
  int r;
  for(r=0;r<=31;r++)
  {
    if ((s & RMASK(r))==0)
    {
      return r;
    }
  }
  fail("getspare failed");
  return 100;
}

void track_fixed PROTO_N ((reg,id)) PROTO_T (int reg X exp id)
{
  exp def = son(id);
  
  if(pt(id)!=nilexp && keep_eq_size(sh(def),sh(pt(id))))
  {
    if(isvar(id))
    {
      keepcont(pt(id),reg);
    } 
    else
    {
      keepreg(pt(id),reg);
    }
  }
  return;
}

void track_float PROTO_N ((reg,id)) PROTO_T (int reg X exp id)
{
  return;
}
