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

#include <stdlib.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"

#include "exptypes.h"
#include "inst_fmt.h"
#include "main.h"
#include "fail.h"
#include "reg_defs.h"
#include "cross.h"
#include "regexps.h"
#include "alpha_ins.h"
#include "bool.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "syms.h"
#include "fail.h"
#include "instypes.h"
#if DO_SCHEDULE
#include "scheduler.h"
#include "common.h"
#endif
#include "procrectypes.h"
#include "locate.h"
#include "getregs.h"
#include "code_here.h"
#include "maxminmacs.h"
#include "pseudo.h"

#if DO_SCHEDULE
static int instruction_number=0;
#endif

int andpeep = 0;
extern int extended_comments;
bool in_noat_block=FALSE;


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
instruction
trap_ins(instruction ins, bool *traps)
{
  *traps = TRUE;
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
  *traps = FALSE;
  return ins;
}

#if DO_SCHEDULE
Instruction
get_new_instruction(void)
{
  Instruction new_ins = getinst();
  if(in_noat_block) setuses(new_ins,resource_noat,class_null);
  return new_ins;
}
#endif

/*
  Construct a new statement from the two representations and send 
  to the scheduler.
*/
#if DO_SCHEDULE
void
output_instruction(Class cl, char *ins_text, char *ins_bindata)
{
  Instruction new_ins = getinst();
  Instruction_data ins_dat = get_new_ins_data();
  if(ins_text){
    if(!strcmp(ins_text,"\t.set\tat\n") || 
       !strcmp(ins_text,"\t.set\tnoat\n")){
      setsets(new_ins,resource_noat,class_null);
      setsets(new_ins,R28,class_null);
    }
  }
  setclass(new_ins,cl);
  set_instruction_text(ins_dat,ins_text);
  set_instruction_binasm(ins_dat,ins_bindata);
  setdata(new_ins,ins_dat);
  process_instruction(new_ins);
  return;
}

#if SEPARATE_DATA
void
output_data(char *data_txt, char * data_binasm)
{
  Instruction_data ins_d = get_new_ins_data();
  set_instruction_binasm(ins_d,data_binasm);
  set_instruction_text(ins_d,data_txt);
  out_code(ins_d);
  return;
}
#else
void
output_data(char *data_txt, char *data_binasm)
{
  output_instruction(class_null,data_txt,data_binasm);
  return;
}
#endif


#endif

#if DO_SCHEDULE
static String *
init_String(void)
{
  String *res = (String*)xcalloc(1,sizeof(String));
  res->head = res->tail = (StringData*)NULL;
  return res;
}

static void
add_char_to_string(char ch, String **dest)
{

  StringData *new = (StringData*)xcalloc(1,sizeof(StringData));
  new->data = ch;
  new->next = (StringData*)NULL;
  if((*dest)->head == (StringData*)NULL){
    (*dest)->head = new;
  }
  if((*dest)->tail != (StringData*)NULL){
    (*dest)->tail->next = new;
  }
  (*dest)->tail = new;
  return ;
}



static void
add_to_string(char *str, String **dest)
{
  int i = 0;
  if(*dest == (String*)NULL){
    *dest = (String*)xcalloc(1,sizeof(String));
    (*dest)->head = (*dest)->tail = (StringData*)NULL;
  }
  for(;i<strlen(str);++i){
    add_char_to_string(str[i],dest);
  }
  return;
}

static char *
copy_from_string(String *src)
{
  StringData *trav = src->head;
  int str_size=0,element=0;
  char * result;
  while(trav){
    ++str_size;
    trav = trav->next;
  }
  result = (char*)xcalloc(str_size+1,sizeof(char));
  trav = src->head;
  while(trav){
    result[element] = trav->data;
    trav = trav->next;
    element ++;
  }
  return result;
}

static void
free_string(String **str)
{
  StringData *trav = (*str)->head;
  StringData *old;
  while(trav){
    old = trav;
    trav = trav->next;
    free(old);
  }
  free(*str);
  return;
}

  
    

/*
  accumulate strings for output.  If the input is NULL then return 
  the current string and reset, otherwise return NULL.
*/
char *
outass(char *str)
{
  static String *res;
  char * tmp;
  static int str_size = 0;
  if(str){
    str_size += strlen(str);
    add_to_string(str,&res);
    /*strcat(res,str);*/
    return (char*)NULL;
  }
  str_size = 0;
  if ( res == (String*)NULL ){
    tmp = (char*)NULL;
  }
  else{
    tmp = copy_from_string(res);
    free_string(&res);
    res = init_String();
  }
  /*strcpy(res,"");*/
  return tmp;
}
#endif


  
/*
  Increment the current instruction number and, if enough 
  instructions have been output, call the scheduler and reset
  the count.
*/
#if DO_SCHEDULE
void
add_instruction(Instruction ins)
{
  process_instruction(ins);
  ++instruction_number;
  if(instruction_number >= (instruction_block_size+schedule_leniency)){
    instruction_number = 0;
    schedule_block();
  }
  return;
}

Instruction_data
get_new_ins_data(void)
{
  Instruction_data a;
  a.text = (char*)NULL;
  a.bindata = (char*)NULL;
  return a;
}

#endif


/*
  This function performs a load store operation.  
*/
void
load_store(instruction ins, int reg, baseoff a)
{
  char *reg_str,*base_reg_str;
  char *ins_name = ins_symbolic_name(ins);
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
#endif
  char *binasm_data;
#if DO_SCHEDULE
  int mem_size = is_32bit_load_store(ins)?4:8+
      (is_unaligned_access_instruction(ins)?UNALIGNED_ACCESS_SIZE_ADJUSTMENT
       :0);
  int offset = is_unaligned_access_instruction(ins)?
      a.offset+UNALIGNED_ACCESS_OFFSET_ADJUSTMENT : a.offset;
#endif
  
  int insid = ins_binid(ins);
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  if(ins_equal(ins,i_ldgp)) {
    setsets_pc(new_ins,true);
  }
  if(ins_class(ins) != class_store_data && ins_class(ins) != class_store_addr){
    setsets(new_ins,reg,ins_class(ins));
  }
  else{
    setuses(new_ins,reg,ins_class(ins));
  }
  if(ins_class(ins) == class_iarithmetic){
    if(a.base>=0 && a.base <32){
      setuses(new_ins,a.base,ins_class(ins));
    }
    if(a.base<0) setuses(new_ins,R29,ins_class(ins));
  }
  else{
    if(a.base < 0){
      if(ins_class(ins) == class_store_data){
	setuses(new_ins,R29,class_store_addr);
	setuses(new_ins,R28,ins_class(ins));
      }
      else{
	setuses(new_ins,R29,ins_class(ins));
      }
      setindex_global(new_ins,-a.base-1);
      setoffset_global(new_ins,offset);
      setsize_global(new_ins,mem_size);
    }
    else if(a.base >31){
      if(ins_class(ins) == class_store_data){
	setuses(new_ins,R29,class_store_addr);
	setuses(new_ins,R28,ins_class(ins));
      }
      else{
	setuses(new_ins,R29,ins_class(ins));
      }
      setbase_label(new_ins,a.base);
      setoffset_label(new_ins,offset);
      setsize_label(new_ins,mem_size);
    }
    else{
      setbase_stack(new_ins,a.base);
      setoffset_stack(new_ins,offset);
      setsize_stack(new_ins,mem_size);
    }
  }
#endif
  reg_str=reg_name[reg];
  if(a.base<0){
    char *extname=main_globals[-a.base-1]->dec_u.dec_val.dec_id;
    if(as_file){
      if(a.offset==0){
#if !DO_SCHEDULE
	(void)fprintf(as_file,"\t%s\t%s, %s\n",ins_name,reg_str,extname);
#else
	(void)sprintf(outline,"\t%s\t%s, %s\n",ins_name,reg_str,extname);
	set_instruction_text(ins_dat,outline);
#endif
      }
      else
	if(a.offset>0){
#if !DO_SCHEDULE
	  (void)fprintf(as_file,"\t%s\t%s,%s+%ld\n",ins_name,reg_str,
			extname,a.offset);
#else
	  (void)sprintf(outline,"\t%s\t%s,%s+%ld\n",ins_name,reg_str,
			extname,a.offset);
	  set_instruction_text(ins_dat,outline);
#endif
	}
	else{
	  if(a.offset<0){
#if !DO_SCHEDULE
	    (void)fprintf(as_file,"\t%s\t%s,%s%ld\n",ins_name,reg_str,
			  extname, a.offset);
#else
	    (void)sprintf(outline,"\t%s\t%s,%s%ld\n",ins_name,reg_str,
			  extname, a.offset);
	    set_instruction_text(ins_dat,outline);
#endif
	  }
	}
    }
    binasm_data = out_iinst(symnos[-a.base-1],insid,reg,xnoreg,FRA,0U,a.offset);
#if DO_SCHEDULE
    set_instruction_binasm(ins_dat,binasm_data);
    setdata(new_ins,ins_dat);
    (void)add_instruction(new_ins);
#endif
  }
  else{
    if(a.base > 31)	/* label */{
      if(as_file){
	if(a.offset==0){
#if !DO_SCHEDULE
	  (void)fprintf(as_file,"\t%s\t%s, $$%d\n",ins_name,reg_str,
			a.base);
#else
	  (void)sprintf(outline,"\t%s\t%s, $$%d\n",ins_name,reg_str,
			a.base);
	  set_instruction_text(ins_dat,outline);
#endif
	}
	else if(a.offset>0){
#if !DO_SCHEDULE
	  (void)fprintf(as_file,"\t%s\t%s, $$%d+%ld\n",ins_name,
			reg_str,a.base,a.offset);
#else
	  (void)sprintf(outline,"\t%s\t%s, $$%d+%ld\n",ins_name,
			reg_str,a.base,a.offset);
	  set_instruction_text(ins_dat,outline);
#endif
	}
	else if(a.offset<0){
#if !DO_SCHEDULE
	  (void)fprintf(as_file,"\t%s\t%s, $$%d-%ld\n",ins_name,
			reg_str,a.base,a.offset);
#else
	  (void)sprintf(outline,"\t%s\t%s, $$%d-%ld\n",ins_name,
			    reg_str,a.base,a.offset);
	  set_instruction_text(ins_dat,outline);
#endif
	}
      }
      binasm_data = 
	out_iinst(tempsnos[a.base-32],insid,reg,xnoreg,FROB,0,a.offset);
#if DO_SCHEDULE
      set_instruction_binasm(ins_dat,binasm_data);
      setdata(new_ins,ins_dat);
      (void)add_instruction(new_ins);
#endif
    }
    else{
#if DO_SCHEDULE
      if(ins_class(ins) == class_store_data){
	setuses(new_ins,a.base,class_store_addr);
      }
      else if(ins_class(ins) == class_load){
	setuses(new_ins,a.base,ins_class(ins));
      }
#endif
      base_reg_str=reg_name[a.base];
      if(as_file){
#if !DO_SCHEDULE
	(void)fprintf(as_file,"\t%s\t%s, %ld(%s)\n",ins_name,
		      reg_str,a.offset,base_reg_str);
#else
	(void)sprintf(outline,"\t%s\t%s, %ld(%s)\n",ins_name,
		      reg_str,a.offset,base_reg_str);
	set_instruction_text(ins_dat,outline);
#endif
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
#if DO_SCHEDULE
      set_instruction_binasm(ins_dat,binasm_data);
      setdata(new_ins,ins_dat);
      (void)add_instruction(new_ins);
#endif
    }
  }
  clear_reg(reg);
  return;
}



void
load_store_immediate(instruction ins, int reg, INT64 val)
{
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  char * outline = (char*)xcalloc(80,sizeof(char));
#endif
  char * binasm_data;
#if DO_SCHEDULE
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,reg,ins_class(ins));
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t%s,",ins_symbolic_name(ins),reg_name[reg]);
#else
    (void)sprintf(outline,"\t%s\t%s,%d\n",ins_symbolic_name(ins),
		  reg_name[reg],val);
    set_instruction_text(ins_dat,outline);
#endif
    /*setdata(new_ins,outline);*/
#if !DO_SCHEDULE
    out_INT64(val);
    (void)outstring("\n");
#endif
  }
  binasm_data = out_biinst(0,ins_binid(ins),reg,xnoreg,FRI,0,val);
#if DO_SCHEDULE
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  clear_reg(reg);
}


void
load_store_label(instruction ins, int reg, int lab)
{
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  char *outline = (char*)xcalloc(80,sizeof(char));
#endif
  char *binasm_data;
#if DO_SCHEDULE
  setclass(new_ins,ins_class(ins));
  if(ins_class(ins) == class_load){
    setsets(new_ins,reg,ins_class(ins));
  }
  else{
    setuses(new_ins,reg,ins_class(ins));
  }
  setlabel(new_ins,lab);
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t%s, $%d\n",ins_symbolic_name(ins),
		  reg_name[reg],lab);
#else
    (void)sprintf(outline,"\t%s\t%s, $%d\n",ins_symbolic_name(ins),
		  reg_name[reg],lab);
    set_instruction_text(ins_dat,outline);
#endif
    /*setdata(new_ins,outline);*/
  }	
  binasm_data = out_linst(-lab,ins_binid(ins),reg,xnoreg,FRL,0);
#if DO_SCHEDULE
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  return;
}


/*
   These functions output assembler for integer control instructions
*/
void
integer_branch(instruction ins, int reg, int dest)
{
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  char *outline = (char*)xcalloc(80,sizeof(char));
#endif
  char *binasm_data = (char*)xcalloc(binasm_record_length+1,sizeof(char));
#if DO_SCHEDULE
  setclass(new_ins,ins_class(ins));
  if(ins_equal(ins,i_br)){
    setsets(new_ins,reg,ins_class(ins));
  }
  else{
    setuses(new_ins,reg,ins_class(ins));
  }
  setsets_pc(new_ins,true);
  setlabel(new_ins,dest);
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t%s,$%d\n",ins_symbolic_name(ins),
		  reg_name[reg],dest);
#else
    (void)sprintf(outline,"\t%s\t%s,$%d\n",ins_symbolic_name(ins),
		  reg_name[reg],dest);
    set_instruction_text(ins_dat,outline);
#endif
  }
  binasm_data = out_linst(-dest,ins_binid(ins),reg,xnoreg,FRL,0);
#if DO_SCHEDULE
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  return;
}


void
integer_jump(instruction ins, int dest_reg, int source_reg, int hint)
{
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  char *outline = (char*)xcalloc(80,sizeof(char));
#endif
  char *binasm_data;
#if DO_SCHEDULE
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,dest_reg,ins_class(ins));
  setuses(new_ins,source_reg,ins_class(ins));
  setsets_pc(new_ins,true);
#endif
  if(as_file){
    if(hint<0){
#if !DO_SCHEDULE
      (void)fprintf(as_file,"\t%s\t%s,(%s),$%d\n",
		    ins_symbolic_name(ins),reg_name[dest_reg],
		    reg_name[source_reg],-hint);
#else
      (void)sprintf(outline,"\t%s\t%s,(%s),$%d\n",
		    ins_symbolic_name(ins),reg_name[dest_reg],
		    reg_name[source_reg],-hint);
#endif
    }
    else{
#if !DO_SCHEDULE
      (void)fprintf(as_file,"\t%s\t%s,(%s),%d\n",ins_symbolic_name(ins),
		    reg_name[dest_reg],reg_name[source_reg],hint);
#else
      (void)sprintf(outline,"\t%s\t%s,(%s),%d\n",ins_symbolic_name(ins),
		    reg_name[dest_reg],reg_name[source_reg],hint);
#endif
    }
  }
  binasm_data = out_iinst(0,ins_binid(ins),dest_reg,source_reg,FRR,0,hint);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  process_instruction(new_ins);
  schedule_block();
  instruction_number = 0;
#endif
  return;
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
  return;
}



void
integer_jump_external(instruction ins, int ra, baseoff b)
{
  char *extname = main_globals[-b.base-1]->dec_u.dec_val.dec_id;
  char *binasm_data;
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,ra,ins_class(ins));
  setsets_pc(new_ins,true);
  if(b.base < 0){
/*    setindex_global(new_ins,-b.base-1);*/
/*    setoffset_global(new_ins,b.offset);
    setsize_global(new_ins,4);*/
  }
  else if (b.base>31){
/*    setbase_label(new_ins,b.base);
    setoffset_label(new_ins,b.offset);
    setsize_label(new_ins,4);*/
  }
  else{
    setbase_stack(new_ins,b.base);
    setoffset_stack(new_ins,b.offset);
    setsize_stack(new_ins,4);
  }
#endif
  clear_all();
  andpeep=0;
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t%s,%s\n",ins_symbolic_name(ins),
		  reg_name[ra],extname);
#else
    (void)sprintf(outline,"\t%s\t%s,%s\n",ins_symbolic_name(ins),
		  reg_name[ra],extname);
    set_instruction_text(ins_dat,outline);
#endif
  }
  binasm_data = out_iinst(symnos[-b.base-1],ins_binid(ins),ra,xnoreg,FRR,0,0);
#if DO_SCHEDULE
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  return;
}



/*
  3 register operations : instr $src1, [$src2|#src2], dest.
  integer arithmetic, logic and shift, byte manipulation.
*/
void
operate_fmt(instruction ins, int src1, int src2, int dest)
{
  char *binasm_data;
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,dest,ins_class(ins));
  setuses(new_ins,src1,ins_class(ins));
  if(src1 != src2){
    setuses(new_ins,src2,ins_class(ins));
  }
  if(ins_class(ins) == class_subroutine){
    setuses(new_ins,R28,ins_class(ins));
    setuses(new_ins,R28,ins_class(ins));
    setsets_pc(new_ins,true);
  }
#endif
  if(dest!=NO_REG){
    if(as_file){
#if !DO_SCHEDULE
      (void)fprintf(as_file,"\t%s\t%s,%s,%s\n",ins_symbolic_name(ins),
		    reg_name[src1],reg_name[src2],reg_name[dest]);
#else
      (void)sprintf(outline,"\t%s\t%s,%s,%s\n",ins_symbolic_name(ins),
		    reg_name[src1],reg_name[src2],reg_name[dest]);
#endif
    }
    clear_reg(dest);
    binasm_data = out_rinst(0,ins_binid(ins),src1,src2,FRRR,dest);
#if DO_SCHEDULE
    set_instruction_text(ins_dat,outline);
    set_instruction_binasm(ins_dat,binasm_data);
    setdata(new_ins,ins_dat);
    add_instruction(new_ins);
#endif
  }
  return;
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
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(40,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,(Register)dest,ins_class(ins));
  setuses(new_ins,(Register)src1,ins_class(ins));
  if(ins_class(ins) == class_subroutine){
    setuses(new_ins,R28,ins_class(ins));
    setsets_pc(new_ins,true);
  }
#endif
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
#if !DO_SCHEDULE
      (void)fprintf(as_file,"\t%s\t%s,%d,%s\n",ins_symbolic_name(ins),
		    reg_name[src1],src2,reg_name[dest]);
#else
      (void)sprintf(outline,"\t%s\t%s,%d,%s\n",ins_symbolic_name(ins),
		    reg_name[src1],src2,reg_name[dest]);
#endif
    }
    clear_reg(dest);
    binasm_data = out_iinst(0,ins_binid(ins),src1,dest,FRIR,0,src2);
#if DO_SCHEDULE
    set_instruction_text(ins_dat,outline);
    set_instruction_binasm(ins_dat,binasm_data);
    setdata(new_ins,ins_dat);
    add_instruction(new_ins);
#endif
  }	
  return;
}

void
operate_fmt_big_immediate(instruction ins, int src1, INT64 src2, int dest)
{
  char * binasm_data;
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,dest,ins_class(ins));
  setuses(new_ins,src1,ins_class(ins));
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t%s,",ins_symbolic_name(ins),reg_name[src1]);
    out_INT64(src2);
    (void)fprintf(as_file,",%s\n",reg_name[dest]);
#else
    (void)sprintf(outline,"\t%s\t%s,%d,%s\n",ins_symbolic_name(ins),
		  reg_name[src1],src2,reg_name[dest]);
#endif
  }
  clear_reg(dest);
  binasm_data = out_biinst(0,ins_binid(ins),src1,dest,FRIR,0,src2);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  /*setdata(new_ins,outline);*/
  add_instruction(new_ins);
#endif
  return;
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
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  if(ins_class(ins) == class_fload){
    setsets(new_ins,reg+float_register,ins_class(ins));
  }
  else{
    setuses(new_ins,reg+float_register,ins_class(ins));
  }
  if(a.base < 0){
    setoffset_global(new_ins,a.offset);
    setsize_global(new_ins,is_32bit_fload_fstore(ins)?4:8);
    setuses(new_ins,AT,ins_class(ins));
  }
  else if(a.base > 31){
    setbase_label(new_ins,a.base);
    setoffset_label(new_ins,a.offset);
    setsize_label(new_ins,is_32bit_fload_fstore(ins)?4:8);
    setuses(new_ins,AT,ins_class(ins));
  }
  else{
    setbase_stack(new_ins,a.base);
    setoffset_stack(new_ins,a.offset);
    setsize_stack(new_ins,is_32bit_fload_fstore(ins)?4:8);
  }
#endif

  if(a.base>=0 && a.base <=31){
    char *basereg=reg_name[a.base];
#if DO_SCHEDULE
    if(ins_class(ins) == class_fstore_data){
      setuses(new_ins,a.base,class_fstore_addr);
    }
    else{
      setuses(new_ins,a.base,ins_class(ins));
    }
#endif
    if(as_file){
#if !DO_SCHEDULE
      (void)fprintf(as_file,"\t%s\t$f%d,%ld(%s)\n",ins_name,reg,a.offset,
		    basereg);
#else
      (void)sprintf(outline,"\t%s\t$f%d,%ld(%s)\n",ins_name,reg,a.offset,
		    basereg);
#endif
    }
    binasm_data=out_iinst(0,ins_id,reg+float_register,a.base,FROB,0,a.offset);
  }
  else
    if(a.base<0){
      char *extname = main_globals[-a.base-1]->dec_u.dec_val.dec_id;
      if(as_file){
	if(a.offset==0){
#if !DO_SCHEDULE
	  (void)fprintf(as_file,"\t%s\t$f%d, %s\n",ins_name,reg,extname);
#else
	  (void)sprintf(outline,"\t%s\t$f%d, %s\n",ins_name,reg,extname);
#endif
	}
	else{
	  if(a.offset<0){
#if !DO_SCHEDULE
	      (void)fprintf(as_file,"\t%s\t$f%d, %s%ld\n",ins_name,reg,
			    extname,a.offset);
#else
	      (void)sprintf(outline,"\t%s\t$f%d, %s%ld\n",ins_name,reg,
			    extname,a.offset);
#endif
	    }
	  else{
#if !DO_SCHEDULE
	    (void)fprintf(as_file,"\t%s\t$f%d, %s+%ld\n",ins_name,reg,
			  extname,a.offset);
#else
	    (void)sprintf(outline,"\t%s\t$f%d, %s+%ld\n",ins_name,reg,
			  extname,a.offset);
#endif
	  }
	}
      }
      binasm_data = 
	  out_iinst(symnos[-a.base-1],ins_id,reg+float_register,xnoreg,FROB,0,
		a.offset);
    }
    else{
      if(as_file){
#if !DO_SCHEDULE
	(void)fprintf(as_file,"\t%s\t$f%d, $$%d\n",ins_name,reg,a.base);
#else
	(void)sprintf(outline,"\t%s\t$f%d, $$%d\n",ins_name,reg,a.base);
#endif
      }
      binasm_data = 
	  out_iinst(tempsnos[a.base-32],ins_id,reg+float_register,xnoreg,FROB,
		    0,0);
    }
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  clear_reg(reg);
  return;
}




/*
   floating point constants are passed as strings, with the 
   formatting being done elsewhere.
*/
void
float_load_store_immediate(instruction ins, int reg, char* val)
{
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,reg+float_register,ins_class(ins));
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t$f%d,%s\n",ins_symbolic_name(ins),reg,val);
#else
    (void)sprintf(outline,"\t%s\t$f%d,%s\n",ins_symbolic_name(ins),reg,val);
#endif
  }
#if DO_SCHEDULE
  add_instruction(new_ins);
#endif
  return;
}


/*
   floating point branch
*/
void
float_branch(instruction ins, int reg, int dest)
{
  char * binasm_data;
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  setsets_pc(new_ins,true);
  setlabel(new_ins,dest);
  setuses(new_ins,reg+float_register,ins_class(ins));
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t$f%d,$%d\n",ins_symbolic_name(ins),reg,
		  dest);
#else
    (void)sprintf(outline,"\t%s\t$f%d,$%d\n",ins_symbolic_name(ins),reg,
		  dest);
#endif
  }
  binasm_data=out_linst(-dest,ins_binid(ins),reg+float_register,xnoreg,FRL,0);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  return;
}



/*
  floating point operations (except conversions).
*/
void
float_op(instruction ins, int src1, int src2, int dest)
{
  char * binasm_data;
  bool special_trap_ins = FALSE;
  instruction real_ins = trap_all_fops?trap_ins(ins,&special_trap_ins):ins;
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(real_ins));
  setsets(new_ins,dest+float_register,ins_class(real_ins));
  setuses(new_ins,src1+float_register,ins_class(real_ins));
  if(src1 != src2){
    setuses(new_ins,src2+float_register,ins_class(real_ins));
  }
#endif  
  if(special_trap_ins) no_parameter_instructions(i_trapb);
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t$f%d,$f%d,$f%d\n",
		  ins_symbolic_name(real_ins),src1,src2,dest);
#else
    (void)sprintf(outline,"\t%s\t$f%d,$f%d,$f%d\n",
		  ins_symbolic_name(real_ins),src1,src2,dest);
#endif
  }
  binasm_data = out_rinst(0,ins_binid(real_ins),src1+float_register,
			  src2+float_register,FRRR,dest+float_register);
  if(special_trap_ins) no_parameter_instructions(i_trapb);
  clear_freg(dest);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  return;
}


#if 0
void
float_op_immediate(instruction ins, int src1, double imm, int dest)
{
  Instruction new_ins = get_new_instruction();
  char *outline = (char*)xcalloc(80,sizeof(char));
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,dest+float_register,ins_class(ins));
  setuses(new_ins,src1+float_register,ins_class(ins));
  if(as_file){
    (void)fprintf(as_file,"\t%s\t$f%d,%lf,$f%d\n",ins_symbolic_name(ins),
		  src1,imm,dest);
    (void)sprintf(outline,"\t%s\t$f%d,%lf,$f%d\n",ins_symbolic_name(ins),
		  src1,imm,dest);
  }
  clear_freg(dest);
  setdata(new_ins,outline);
  add_instruction(new_ins);
  return;
}
#endif


/*
  floating point conversions.
*/
void
float_convert(instruction ins, int src, int dest)
{
  char * binasm_data;
#if DO_SCHEDULE
  char *outline = (char*)xcalloc(80,sizeof(char));
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_dat = get_new_ins_data();
  setclass(new_ins,ins_class(ins));
  setsets(new_ins,dest+float_register,ins_class(ins));
  setuses(new_ins,src+float_register,ins_class(ins));
#endif
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t%s\t$f%d,$f%d\n",ins_symbolic_name(ins),src,
		  dest);
#else
    (void)sprintf(outline,"\t%s\t$f%d,$f%d\n",ins_symbolic_name(ins),src,
		  dest);
#endif
  }
  binasm_data = out_rinst(0,ins_binid(ins),src+float_register,
			  dest+float_register,FRR,xnoreg);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
  add_instruction(new_ins);
#endif
  return;
}



/*
  miscellaneous instructions
*/
void
call_pal(instruction ins, instruction pal_ins)
{
  if(as_file){
    (void)fprintf(as_file,"\t%s\t%s\n",ins_symbolic_name(ins),
		  ins_symbolic_name(pal_ins));
  }
  return;
}

void
fetch(instruction ins, baseoff a)
{
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  setclass(new_ins,ins_class(ins));
  setuses(new_ins,a.base,ins_class(ins));
#endif
/*  setmemory_base(new_ins,a.base);
  setmemory_offset(new_ins,a.offset);*/
  if(a.offset!=0)
    failer("fetch offset must be zero");
  if(as_file){
    (void)fprintf(as_file,"\t%s\t%ld($%d)\n",ins_symbolic_name(ins),
		  a.offset,a.base);
  }
#if DO_SCHEDULE
  add_instruction(new_ins);
#endif
  return;
}

void
no_parameter_instructions(instruction ins)
{
#if DO_SCHEDULE
  Instruction new_ins = get_new_instruction();
  Instruction_data ins_data = get_new_ins_data();
  char * outline = (char*)xcalloc(strlen(ins_symbolic_name((ins)))+1,sizeof(char));
  char * binasm_data;
  setclass(new_ins,ins_class(ins));
#endif
  if(as_file){
    (void)fprintf(as_file,"\t%s\n",ins_symbolic_name(ins));
#if DO_SCHEDULE
    (void)sprintf(outline,"\t%s\n",ins_symbolic_name(ins));
    set_instruction_text(ins_data,outline);
#endif
  }
#if DO_SCHEDULE
  binasm_data = out_rinst(0,ins_binid(ins),xnoreg,xnoreg,xnoreg,xnoreg);
  set_instruction_binasm(ins_data,binasm_data);
  setdata(new_ins,ins_data);
  add_instruction(new_ins);
#else
  (void)out_rinst(0,ins_binid(ins),xnoreg,xnoreg,xnoreg,xnoreg);
#endif
  return;

}

#if DO_SCHEDULE
static void
out_as_string(FILE *fp, char *str)
{
  int i;
  int slen = strlen(str);
  for(i=0;i<strlen(str);++i){
    outchar(str[i]);
  }
  return;
}
#endif
    
      
#if DO_SCHEDULE
void
out_code(Instruction_data ins_data)
{
  int i;
  char * bdata = instruction_binasm(ins_data);
  if(as_file && instruction_text(ins_data)){
    out_as_string(as_file,instruction_text(ins_data));
/*    fprintf(as_file,instruction_text(ins_data));*/
  }
  for(i=0;i<binasm_record_length;++i){
    putc(bdata[i],ba_file);
  }
  /*(void)out_one(instruction_binasm(ins_data));*/
  return;
}
#endif




