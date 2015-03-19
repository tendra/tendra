/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  inst_fmt_2.c

  This file contains a set of procedures to output assembler 
  instructions in both binary and symbolic formats and to call 
  the code scheduler at appropriate points.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <symtab/syms.h>

#include <reader/exp.h>

#include <main/driver.h>
#include <main/print.h>

#include "make_code.h"
#include "inst_fmt.h"
#include "main.h"
#include "reg_defs.h"
#include "cross.h"
#include "regexps.h"
#include "alpha_ins.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "instypes.h"
#include "procrectypes.h"
#include "locate.h"
#include "getregs.h"
#include "code_here.h"
#include "maxminmacs.h"
#include "pseudo.h"

bool trap_all_fops;

static int andpeep = 0;
extern int extended_comments;
bool in_noat_block=false;


static char *reg_name[]=
{"$0","$1","$2","$3","$4","$5","$6","$7","$8","$9","$10","$11","$12","$13"
 ,"$14","$fp","$16","$17","$18","$19","$20","$21","$22","$23","$24","$25"
 ,"$26","$27","$at","$gp","$sp","$31"
};

#define instruction_block_size	500
#define schedule_leniency	0


#define is_32bit_load_store(X) (ins_equal(X,i_ldl)||ins_equal(X,i_stl)\
				 || ins_equal(X,i_ldl_l)||ins_equal(X,i_stl_c))

#define is_32bit_fload_fstore(X) (ins_equal(X,i_lds)||ins_equal(X,i_sts)\
				  || ins_equal(X,i_ldf)||ins_equal(X,i_stf))

#define is_unaligned_access_instruction(X) (ins_equal(X,i_ldq_u) ||\
					    ins_equal(X,i_stq_u))

/*
  If the instruction ins has an equivalent which causes the OS to
  successfully handle a trap then return it, otherwise return ins.
*/
static instruction
trap_ins(instruction ins, bool *traps)
{
  *traps = true;
  if (ins_equal(ins,i_adds))
    return i_addssu;
  if (ins_equal(ins,i_addt))	
    return i_addtsu;
  if (ins_equal(ins,i_divs))	
    return i_divssu;
  if (ins_equal(ins,i_divt))	
    return i_divtsu;
  if (ins_equal(ins,i_muls))	
    return i_mulssu;
  if (ins_equal(ins,i_mult))	
    return i_multsu;
  if (ins_equal(ins,i_subs))	
    return i_subssu;
  if (ins_equal(ins,i_subt))	
    return i_subtsu;
  *traps = false;
  return ins;
}


/*
  This function performs a load store operation.  
*/
void
load_store(instruction ins, int reg, baseoff a)
{
  char *reg_str,*base_reg_str;
  char *ins_name = ins_symbolic_name(ins);
  char *binasm_data;
  
  int insid = ins_binid(ins);
  reg_str=reg_name[reg];
  if(a.base<0){
    char *extname=main_globals[-a.base-1]->dec_id;
    if(as_file){
      if(a.offset==0){
	asm_printop("%s %s, %s",ins_name,reg_str,extname);
      }
      else
	if(a.offset>0){
	  asm_printop("%s %s,%s+%ld",ins_name,reg_str,
			extname,a.offset);
	}
	else{
	  if(a.offset<0){
	    asm_printop("%s %s,%s%ld",ins_name,reg_str,
			  extname, a.offset);
	  }
	}
    }
    binasm_data = out_iinst(symnos[-a.base-1],insid,reg,xnoreg,FRA,0U,a.offset);
  }
  else{
    if(a.base > 31)	/* label */{
      if(as_file){
	if(a.offset==0){
	  asm_printop("%s %s, $$%d",ins_name,reg_str,
			a.base);
	}
	else if(a.offset>0){
	  asm_printop("%s %s, $$%d+%ld",ins_name,
			reg_str,a.base,a.offset);
	}
	else if(a.offset<0){
	  asm_printop("%s %s, $$%d-%ld",ins_name,
			reg_str,a.base,a.offset);
	}
      }
      binasm_data = 
	out_iinst(tempsnos[a.base-32],insid,reg,xnoreg,FROB,0,a.offset);
    }
    else{
      base_reg_str=reg_name[a.base];
      if(as_file){
	asm_printop("%s %s, %ld(%s)",ins_name,
		      reg_str,a.offset,base_reg_str);
      }
      if(ins_equal(ins,i_lda) || ins_equal(ins,i_ldq)){
	if((a.base == SP) || ((regexps[a.base].alignment == 8) && 
	   (a.offset%8 == 0))){
	  regexps[reg].alignment = 8;
	}
        else if((a.base == SP || regexps[a.base].alignment == 4) && (a.offset %4 == 0)){
	  regexps[reg].alignment = 4;
	}
	else{
	  regexps[reg].alignment = 0;
	}
      }
      binasm_data = out_iinst(0,insid,reg,a.base,FROB,0,a.offset);
    }
  }
  clear_reg(reg);
  UNUSED(binasm_data); /* XXX */
}



void
load_store_immediate(instruction ins, int reg, INT64 val)
{
  char * binasm_data;
  if(as_file){
    asm_printf("\t%s\t%s,",ins_symbolic_name(ins),reg_name[reg]);
    out_INT64(val);
    asm_printf( "\n");
  }
  binasm_data = out_biinst(0,ins_binid(ins),reg,xnoreg,FRI,0,val);
  clear_reg(reg);
  UNUSED(binasm_data); /* XXX */
}


void
load_store_label(instruction ins, int reg, int lab)
{
  char *binasm_data;
  if(as_file){
    asm_printop("%s %s, $%d",ins_symbolic_name(ins),
		  reg_name[reg],lab);
  }	
  binasm_data = out_linst(-lab,ins_binid(ins),reg,xnoreg,FRL,0);
  UNUSED(binasm_data); /* XXX */
}


/*
   These functions output assembler for integer control instructions
*/
void
integer_branch(instruction ins, int reg, int dest)
{
  char *binasm_data = (char*)xcalloc(binasm_record_length+1,sizeof(char));
  if(as_file){
    asm_printop("%s %s,$%d",ins_symbolic_name(ins),
		  reg_name[reg],dest);
  }
  binasm_data = out_linst(-dest,ins_binid(ins),reg,xnoreg,FRL,0);
  UNUSED(binasm_data); /* XXX */
}


void
integer_jump(instruction ins, int dest_reg, int source_reg, int hint)
{
  char *binasm_data;
  if(as_file){
    if(hint<0){
      asm_printop("%s %s,(%s),$%d",
		    ins_symbolic_name(ins),reg_name[dest_reg],
		    reg_name[source_reg],-hint);
    }
    else{
      asm_printop("%s %s,(%s),%d",ins_symbolic_name(ins),
		    reg_name[dest_reg],reg_name[source_reg],hint);
    }
  }
  binasm_data = out_iinst(0,ins_binid(ins),dest_reg,source_reg,FRR,0,hint);
  UNUSED(binasm_data); /* XXX */
}


void
integer_jump_fn(instruction ins, int ra, exp fn, space sp)
{
  baseoff b = boff(fn);
  if(b.base<0) {
    integer_jump_external(ins,ra,b);
  }
  else {
    int rt;
    if(ra != AT) {
      rt = AT;
    }
    else {
      rt = getreg(sp.fixed & 0x03f0000);/*leaves out parameter registers*/
    }
    rt = reg_operand(fn,sp);
    operate_fmt(i_bis,rt,rt,PV);
    integer_jump(i_jsr,26,rt,0);
  }
}



void
integer_jump_external(instruction ins, int ra, baseoff b)
{
  char *extname = main_globals[-b.base-1]->dec_id;
  char *binasm_data;
  clear_all();
  andpeep=0;
  if(as_file){
    asm_printop("%s %s,%s",ins_symbolic_name(ins),
		  reg_name[ra],extname);
  }
  binasm_data = out_iinst(symnos[-b.base-1],ins_binid(ins),ra,xnoreg,FRR,0,0);
  UNUSED(binasm_data); /* XXX */
}



/*
  3 register operations : instr $src1, [$src2|#src2], dest.
  integer arithmetic, logic and shift, byte manipulation.
*/
void
operate_fmt(instruction ins, int src1, int src2, int dest)
{
  char *binasm_data;
  if(dest!=NO_REG){
    if(as_file){
      asm_printop("%s %s,%s,%s",ins_symbolic_name(ins),
		    reg_name[src1],reg_name[src2],reg_name[dest]);
    }
    clear_reg(dest);
    binasm_data = out_rinst(0,ins_binid(ins),src1,src2,FRRR,dest);
  }
  UNUSED(binasm_data); /* XXX */
}


/*
  Output an operation where the second paramter is an immediate
  value.  If the immediate value is larger than 8 bits then it 
  needs to be loaded into a register 
*/
void
operate_fmt_immediate(instruction ins, int src1, int src2, int dest)
{
  char *binasm_data;
  if(abs(src2) > 255){
    bool block_status = in_noat_block;
    if (!block_status) setnoat();
    if(src2<0) {
      load_store_immediate(i_ldiq,AT,make_INT64(-1,(unsigned)src2));
    }
    else {      
      load_store_immediate(i_ldiq,AT,make_INT64(0,(unsigned)src2));
    }
    operate_fmt(ins,src1,AT,dest);
    if (!block_status) setat();
    return ;
  }
  
  if(dest!=NO_REG){
    if(as_file){
      asm_printop("%s %s,%d,%s",ins_symbolic_name(ins),
		    reg_name[src1],src2,reg_name[dest]);
    }
    clear_reg(dest);
    binasm_data = out_iinst(0,ins_binid(ins),src1,dest,FRIR,0,src2);
  }	
  UNUSED(binasm_data); /* XXX */
}

void
operate_fmt_big_immediate(instruction ins, int src1, INT64 src2, int dest)
{
  char * binasm_data;
  if(as_file){
    asm_printf("\t%s\t%s,",ins_symbolic_name(ins),reg_name[src1]);
    out_INT64(src2);
    asm_printf(",%s\n",reg_name[dest]);
  }
  clear_reg(dest);
  binasm_data = out_biinst(0,ins_binid(ins),src1,dest,FRIR,0,src2);
  UNUSED(binasm_data); /* XXX */
}



/*
   floating point load/store
*/
void
float_load_store(instruction ins, int reg, baseoff a)
{
  char * ins_name = ins_symbolic_name(ins);
  char * binasm_data;
  int ins_id = ins_binid(ins);

  if(a.base>=0 && a.base <=31){
    char *basereg=reg_name[a.base];
    if(as_file){
      asm_printop("%s $f%d,%ld(%s)",ins_name,reg,a.offset,
		    basereg);
    }
    binasm_data=out_iinst(0,ins_id,reg+float_register,a.base,FROB,0,a.offset);
  }
  else
    if(a.base<0){
      char *extname = main_globals[-a.base-1]->dec_id;
      if(as_file){
	if(a.offset==0){
	  asm_printop("%s $f%d, %s",ins_name,reg,extname);
	}
	else{
	  if(a.offset<0){
	      asm_printop("%s $f%d, %s%ld",ins_name,reg,
			    extname,a.offset);
	    }
	  else{
	    asm_printop("%s $f%d, %s+%ld",ins_name,reg,
			  extname,a.offset);
	  }
	}
      }
      binasm_data = 
	  out_iinst(symnos[-a.base-1],ins_id,reg+float_register,xnoreg,FROB,0,
		a.offset);
    }
    else{
      if(as_file){
	asm_printop("%s $f%d, $$%d",ins_name,reg,a.base);
      }
      binasm_data = 
	  out_iinst(tempsnos[a.base-32],ins_id,reg+float_register,xnoreg,FROB,
		    0,0);
    }
  clear_reg(reg);
  UNUSED(binasm_data); /* XXX */
}




/*
   floating point constants are passed as strings, with the 
   formatting being done elsewhere.
*/
static void
float_load_store_immediate(instruction ins, int reg, char* val)
{
  if(as_file){
    asm_printop("%s $f%d,%s",ins_symbolic_name(ins),reg,val);
  }
}


/*
   floating point branch
*/
void
float_branch(instruction ins, int reg, int dest)
{
  char * binasm_data;
  if(as_file){
    asm_printop("%s $f%d,$%d",ins_symbolic_name(ins),reg,
		  dest);
  }
  binasm_data=out_linst(-dest,ins_binid(ins),reg+float_register,xnoreg,FRL,0);
  UNUSED(binasm_data); /* XXX */
}



/*
  floating point operations (except conversions).
*/
void
float_op(instruction ins, int src1, int src2, int dest)
{
  char * binasm_data;
  bool special_trap_ins = false;
  instruction real_ins = trap_all_fops?trap_ins(ins,&special_trap_ins):ins;
  if(special_trap_ins) no_parameter_instructions(i_trapb);
  if(as_file){
    asm_printop("%s $f%d,$f%d,$f%d",
		  ins_symbolic_name(real_ins),src1,src2,dest);
  }
  binasm_data = out_rinst(0,ins_binid(real_ins),src1+float_register,
			  src2+float_register,FRRR,dest+float_register);
  if(special_trap_ins) no_parameter_instructions(i_trapb);
  clear_freg(dest);
  UNUSED(binasm_data); /* XXX */
}


#if 0
void
float_op_immediate(instruction ins, int src1, double imm, int dest)
{
  if(as_file){
    asm_printop("%s $f%d,%lf,$f%d",ins_symbolic_name(ins),
		  src1,imm,dest);
  }
  clear_freg(dest);
}
#endif


/*
  floating point conversions.
*/
void
float_convert(instruction ins, int src, int dest)
{
  char * binasm_data;
  if(as_file){
    asm_printop("%s $f%d,$f%d",ins_symbolic_name(ins),src,
		  dest);
  }
  binasm_data = out_rinst(0,ins_binid(ins),src+float_register,
			  dest+float_register,FRR,xnoreg);
  UNUSED(binasm_data); /* XXX */
}



/*
  miscellaneous instructions
*/

void
no_parameter_instructions(instruction ins)
{
  if(as_file){
    asm_printop("%s",ins_symbolic_name(ins));
  }
  IGNORE out_rinst(0,ins_binid(ins),xnoreg,xnoreg,xnoreg,xnoreg);
}

