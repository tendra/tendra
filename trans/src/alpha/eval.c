/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  eval.c
  This file contains functions which output data to the assembler
  file.  The parameters are an exp and an index into the table of
  externals.
*/

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>
#include <local/fbase.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/flpttypes.h>
#include <construct/flpt.h>
#include <construct/f64.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <symtab/syms.h>

#include "addresstypes.h"
#include "maxminmacs.h"
#include "main.h"
#include "frames.h"
#include "reg_defs.h"
#include "cross.h"
#include "pseudo.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "shape_range.h"  /* provides definitions of 
			     scmm_max,scmm_min, etc. */
#include "inst_fmt.h"
#include "eval.h"
#include "procrecs.h"
#include "localexpmacs.h"

/*
  storage types
*/
char *s_byte="byte";
char *s_word="word";
char *s_long="long";
char *s_quad="quad";


/*
   The current alignment of the program
*/
int current_alignment=-1;


long  G_number = 64;		/* to give choice of .sdata or data */

int   data_lab = 33;

/* anonymous label in data space - $$n in assember o/p */
int
next_data_lab(void)
{
  return data_lab++;
}


/* as above-but also gives it a symno for .G output */
int
next_dlab_sym(void)
{	
  symnofordata (data_lab);
  return data_lab++;
}


/* various pieces of info for outputting data depending on shape */
mm scmm = {
  scmm_max, scmm_min, "\t.byte %ld :%ld\n"
};
mm uscmm = {
  uscmm_max,uscmm_min, "\t.byte %ld :%ld\n"
};
mm shmm = {
  shmm_max,shmm_min, "\t.word %ld :%ld\n"
};
mm ushmm = {
  ushmm_max,ushmm_min, "\t.word %ld :%ld\n"
};
mm swmm = {
  swmm_max,swmm_min, "\t.long %ld :%ld\n"
};
mm uswmm = {
  uswmm_max,uswmm_min,"\t.long %ld :%ld\n"
};

mm u64mm = {
  u64mm_max,u64mm_min,"\t.quad %ld :%ld\n"
};

mm s64mm = {
  s64mm_max,s64mm_min, "\t.quad %ld :%ld\n"
};



/*
   maxmin

   finds the data size from the range of an integer shape
*/
mm
maxmin(shape s)
{
  switch (name (s)) {
  case scharhd: return scmm;
  case ucharhd: return uscmm;
  case swordhd: return shmm;
  case uwordhd: return ushmm;
  case slonghd: return swmm;
  case ulonghd: return uswmm;
  case s64hd:   return s64mm;
  case u64hd:   return u64mm;
  default: 	return uswmm;
  }
}


/*
  outlab
  outputs the label parameter if non negative else interprets it
  to be an index into the externals and outputs the identifier.
*/

char *
outlab(int l)
{
  if (l >= 0) {
    asm_printf( "$$%d", l);
  }
  else {
    char *extname = main_globals[-l - 1] -> dec_u.dec_val.dec_id;
    asm_printf( "%s", extname);
  }
  return NULL;
}

char  fltrepr[120];

void
output_data_records(char *strng, char *str, int size)
{
  int pos = 0;
  assert(size>0);
  assert(!strng);
  while(size>0){
    out_data(str,min(size,binasm_record_length));
    pos += binasm_record_length;
    size -= binasm_record_length;
  }
  return;
}

      


/*
   This function outputs an IEEE format floating point number
*/
void
outfloat(exp e, int rep, ash a)
{
  INT64 val;
  int fv = name(sh(e)) - shrealhd;
  r2l ieeeflt;
  ieeeflt = real2longs_IEEE(&flptnos[no(e)],fv);
  switch(fv){
    case 0:
    if(as_file){
      asm_printop(".long 0x%08x : %d # .s floating",
		ieeeflt.i1, rep);
    }
    out_value(0,ilong,make_INT64(0,ieeeflt.i1),rep);
/*    out_value(0,ilong,ieeeflt.i1,rep);*/
    break;
    case 1:
    if(as_file){
      asm_printop(".quad 0x%08x%08x : %d # .t floating",
		ieeeflt.i2, ieeeflt.i1, rep);
    }
/*    val = ((long)ieeeflt.i2<<32) + (unsigned)ieeeflt.i1;*/
    val = make_INT64(ieeeflt.i2,(unsigned)ieeeflt.i1);
    out_value(0,iquad,val,rep);
    break;
    default:
    error(ERROR_INTERNAL, "invalid floating variety");
  }
  return;
}

/*
  evaluate the exp 'e' and return the resulting value
*/
INT64
evalexp(exp e)
{
  
  switch (name(e)) {
    case  val_tag : {
      if(al2(sh(e))>=8 && name(sh(e)) == offsethd) {
	return INT64_shift_right(flt64_to_INT64(exp_to_f64(e)),3,1);
      }
      return flt64_to_INT64(exp_to_f64(e));
    }
    case bitf_to_int_tag : {
      return evalexp (son (e));
    }
    case int_to_bitf_tag : {
      ash a;
      INT64  w = evalexp (son (e));
      a = ashof (sh (e));
      if (a.ashalign != 1) {
	error(ERROR_INTERNAL, "should be align 1");
      }	
      if(a.ashsize!=64){
	w = INT64_and(w,INT64_subtract(INT64_shift_left(make_INT64(0,1),
							a.ashsize,1),
				       make_INT64(0,1),1));
      }	
      return w;
    }

    case not_tag: return INT64_not(evalexp (son (e)));
    case and_tag: return INT64_and(evalexp(son(e)),evalexp(bro(son(e))));
    case or_tag:  return INT64_or(evalexp(son(e)),evalexp(bro(son(e))));
    case xor_tag: return INT64_xor(evalexp(son(e)),evalexp(bro(son(e))));
    case shr_tag: return INT64_shift_right(evalexp(son(e)),
			low_INT64(evalexp(bro(son(e)))),1);
    case shl_tag: return INT64_shift_left(evalexp(son(e)),
		       low_INT64(evalexp(bro(son(e)))),1);

    case concatnof_tag: {
      ash a;
      INT64 wd = evalexp (son (e));
      a = ashof (sh (son (e)));
      return INT64_or(wd,
		       INT64_shift_left(evalexp(bro(son(e))),a.ashsize,1));
    }
    case clear_tag: {
      ash a;
      a = ashof (sh (e));
      if (a.ashsize > REG_SIZE)
	error(ERROR_INTERNAL, "clearshape");
      return zero_int64;
    }	
    case general_env_offset_tag :
    case env_offset_tag : {
      return make_INT64(0,frame_offset(son(e)));
    }
    case env_size_tag : {
      exp tg = son(son(e));
      procrec *pr = &procrecs[no(son(tg))];
      return (pr->frame_size+pr->callee_size)>>3;
    }

    case offset_add_tag:        return evalexp(son(e)) + evalexp(bro(son(e)));
    case offset_max_tag:        return max(evalexp(son(e)),evalexp(bro(son(e))));
    case offset_pad_tag:        return rounder(evalexp(son(e)),shape_align(sh(e))>>3);
    case offset_mult_tag:       return evalexp(son(e))*evalexp(bro(son(e)));
    case offset_div_tag: 
    case offset_div_by_int_tag: return evalexp(son(e))/evalexp(bro(son(e)));
    case offset_subtract_tag:   return evalexp(son(e)) - evalexp(bro(son(e)));
    case offset_negate_tag:     return -evalexp(son(e));
    
    default: 
      error(ERROR_INTERNAL, "tag not in evalexp");
  }
  return zero_int64;
}


/*
  This function outputs values to the assembler file.  The 
  alignment of the last value to be output is retained and, 
  if it differs from the current one, a new alignment is set.
*/
void
oneval(INT64 val, int al, int rep)
{
  char *store_type;
  static int lastal = -1;
  unsigned int bval;
  if(al!=lastal){
    set_align(al);
    lastal=al;
  }
  switch(al){
  case  8: store_type=s_byte; bval = ibyte; break;
  case 16: store_type=s_word; bval = iword; break;
  case 32: store_type=s_long; bval = ilong; break;
  case 64: store_type=s_quad; bval = iquad; break;
  default: store_type=s_long; bval = ilong; break;
  }
  if(as_file){
    asm_printf("\t.%s ",store_type);
    out_INT64(val);
    asm_printf(" :%d\n",rep);
  }
  out_value(0,bval,val,rep);
  return;
}


INT64
bits_list(int val)
{
  int loop;
  INT64 result=make_INT64(0,0);
/*  assert(val <=31);*/
  assert(val <=64);
  for(loop=0;loop<val;++loop){
    result = INT64_shift_left(result,1,1);
    result = INT64_or(result,make_INT64(0,1));
#if 0
    result <<=1;
    result |= 1;
#endif
  }
  return result;
}



/*
  Outputs the expression 'e', rep times.
*/
void
evalone(exp e, int rep)
{
  ash a;
  int overflow;
  if (e == NULL) return;
  a = ashof (sh (e));
  switch (name (e)) {
  case string_tag: {
    long char_size = props(e);
    long  strsize = shape_size(sh(e))/char_size;
    char *st = nostr(e);
    long  strs = shape_size(sh(e))>>3;
    int   i,j;
    int hex_output=0;
    if (rep != 1 && as_file){
      asm_printop(".repeat %d", rep);
    }
    set_align(a.ashalign);
    if(as_file){
      if(strsize<256 && (char_size ==8)){
	asm_printf("\t.ascii\t\"");
	for(j=0;j<strsize;++j){
	  if(st[j]>=32 && st[j]<0x7f && (!hex_output)){
	    if(st[j]=='\"'){
	      asm_printf("\\\"");
	    }
	    else if(st[j]=='\\'){
	      asm_printf("\\\\");
	    }
	    else{
	      asm_printf("%c",st[j]);
	    }
	  }	
	  else{
	    asm_printf("\\X%x",st[j]&0xff);
	    hex_output=1;
	  }
	 }
	asm_printf("\"\n");
      }
      else{
	for (j=0; j< strsize; ) {
	  switch(char_size) {
	  case  8: (void) asm_printf( "\t.byte "); break;
	  case 16: (void) asm_printf( "\t.word "); break;
	  case 32: (void) asm_printf( "\t.long "); break;
	  case 64: (void) asm_printf( "\t.quad "); break;
	  }
	  for (i = j; i < strsize && i-j < 8; i++) {
	    switch (char_size) { 
	    case 8:
	      asm_printf( "0x%x ", st[i]&0xff); 
	      break;
	    case 16:
	      asm_printf( "0x%x ", ((unsigned short *)st)[i]); 
	      break;
	    case 32:
	      asm_printf( "0x%x ", ((int *)st)[i]); 
	      break;
	    case 64:{
	      flt64 bigint;
	      bigint = flt_to_f64(((flpt*)st)[i],is_signed(sh(e)),&overflow);
	      out_INT64(flt64_to_INT64(bigint));asm_printf( " ");
	      break;
	    }		        	        
	    }
	  }
	  j =i;
	  asm_printf( "\n");
	}
      }
    }
    out_chars(0,iascii,strs,rep);
    if(char_size == 64){
      /* replace the float indexes used to represent the array */
      char * newst = (char*)xcalloc(strs,sizeof(char));
      int i;
      for(i=0;i<strsize;++i){
	((INT64*)newst)[i] = flt64_to_INT64(flt_to_f64(((flpt*)st)[i],
						       is_signed(sh(e)),
						       &overflow));
      }
      out_data(newst,strs);
    }
    else{
      out_data(st,strs);
    }
    return;
  }
  case real_tag: {
    outfloat(e,rep,a);
    return;
  }	
  case null_tag: 
    no (e) = 0;
    FALL_THROUGH
  case val_tag: {
    if(isbigval(e)){
      oneval(flt64_to_INT64(exp_to_f64(e)),a.ashalign,rep);
    }	
    else{
      if((al2(sh(e)) >= 8) && (name(sh(e)) == offsethd)){
	no(e) = no(e)>>3;
      }
      if(is_signed(sh(e))){
	oneval(make_INT64(0,no(e)),a.ashalign,rep);
      }
      else{
	oneval(make_INT64(0L,(unsigned)uno(e)),a.ashalign,rep);
      }	
    }
    return;
    }	
  case name_tag: {
    dec * globdec= brog(son (e));/* must be global name */
    char *nm = globdec -> dec_u.dec_val.dec_id;
    long symdef = globdec ->dec_u.dec_val.sym_number;
    char *storage_type;
    int storage_id;
    switch(a.ashalign){
      case  8: storage_type = s_byte; storage_id = ibyte; break;
      case 16: storage_type = s_word; storage_id = iword; break;
      case 32: storage_type = s_long; storage_id = ilong; break;
      case 64: storage_type = s_quad; storage_id = iquad; break;
    }	
    set_align(a.ashalign);	
    if (as_file) {
      if (no (e) == 0) {
	asm_printop(".%s %s : %d", storage_type,nm, rep);
      }		
    }
    out_value(symnos[symdef],storage_id,make_INT64(0,no(e)/8),rep);
    return;
   }
  case compound_tag:  {
    exp tup = son (e);
    INT64 val;
    bool first_bits=1;
    long bits_start =0;
    long offs =0;
    if (rep != 1)
      error(ERROR_INTERNAL, "CAN'T REP TUPLES");
    set_align(a.ashalign);
    for(;;) {
      ash ae;
      ae = ashof(sh(bro(tup)));
      offs = no(tup);
      if (ae.ashalign == 1) {
	INT64 vb = evalexp(bro(tup));			
	if (first_bits) {
	  val = INT64_and(vb,bits_list(ae.ashsize));
	  /*val = vb & bits_list(ae.ashsize);*/
	  bits_start =offs;
	  first_bits=0;
	}	
	else 
	  if (offs - bits_start +ae.ashsize <= REG_SIZE) {
	    val = INT64_or(val,
		      INT64_shift_left(
				       INT64_and(vb,bits_list(ae.ashsize)),
				       offs-bits_start,1)
			   );
	    /*val |= ((vb&bits_list(ae.ashsize)) <<(offs-bits_start));*/
	  }
	  else {
	    if (endian == ENDIAN_BIG) {
	      for(;;) {
		oneval(INT64_shift_right(val,24,1),8,1);
		/*oneval(val>>24, 8, 1);*/
		val = INT64_shift_left(val,8,1);
		/*val <<=8;*/
		bits_start+=8;
		if (offs-bits_start <= 0) break;
	      }	
	      break;
	    } else {
	      assert(endian == ENDIAN_LITTLE);
	      for(;;) {  
		oneval(INT64_and(val,make_INT64(0,255)),8,1);
		/*oneval(val &255, 8,1);*/
		/*val >>= 8;*/
		val = INT64_shift_right(val,8,1);
		bits_start += 8;
		if (offs - bits_start  <=0)
		  break;
	      }
	    }
	    val = vb;
	  }
      }
      else {
	if (!first_bits) {
	  first_bits=1;
	  if (endian == ENDIAN_BIG) {
	    for(;;) {
	      oneval(INT64_shift_right(val,24,1),8,1);
	      /*oneval(val>>24, 8, 1);*/
	      val = INT64_shift_left(val,8,1);
	      /*val <<=8;*/
	      bits_start+=8;
	      if (offs-bits_start <= 0) break;
	    }
	    break;
	  } else {
	    assert(endian == ENDIAN_LITTLE);
	    for(;;) {  
	      oneval(INT64_and(val,make_INT64(0,255)),8,1);
	      /*oneval(val &255, 8,1);*/
	      val = INT64_shift_right(val,8,1);
	      /*val >>=8;*/
	      bits_start += 8;
	      if ( offs - bits_start  <=0)
		break;
	    }
	  }
	}
	evalone(bro(tup),1);
      }
      if (last(bro(tup))) {
	offs += ae.ashsize;
	for(;!first_bits;) {
	  if (endian == ENDIAN_BIG) {
	    oneval(INT64_shift_right(val,24,1),8,1);
	    /*oneval(val>>24, 8, 1);*/
	    val = INT64_shift_left(val,8,1);
	    /*val <<=8;*/
	    bits_start+=8;
	    if (offs-bits_start<= 0) break;
	  } else {
	    assert(endian == ENDIAN_LITTLE);
	    oneval(INT64_and(val,make_INT64(0,255)),8,1);
	    /*oneval(val &255, 8,1);*/
	    val = INT64_shift_right(val,8,1);
	    /*val >>= 8;*/
	    bits_start +=8;
	    if ( offs - bits_start <=0)
	      break;
	  }
	}	
	while (a.ashsize > offs) { /* pad out unions etc */
	  oneval(make_INT64(0,0),8,1);
/*	  oneval(0,8,1);*/
	  offs+=8;
	}
	return;
      }
      tup = bro(bro(tup));
    }
  }	
  case nof_tag: {
    exp s = son(e);
    if (rep != 1)
      error(ERROR_INTERNAL, "CAN'T REP TUPLES");   	
    set_align(a.ashalign);
    if (s == NULL) return;
    for(;;) {
      evalone(s,1);
      if (last(s)) return;
      s = bro(s);
    }
  }		
  case ncopies_tag: {
    if (name(son(e)) == compound_tag || name(son(e)) == concatnof_tag ||
	name(son(e)) == nof_tag) {
      int n;
      for (n = rep*no(e); n > 0; n--) {
	evalone(son(e), 1);
      }
    }
    else evalone (son (e), rep * no (e));
    return;
  }
  case concatnof_tag: {
    if (a.ashalign == 1) {
      INT64 ee = evalexp(e);
      /*long  ee = evalexp (e);*/
      exp dad = father(e);
      ash abits;
      abits = ashof(sh(dad));
      oneval(ee, abits.ashalign, rep);
    }
    else {
      if (rep != 1)
	error(ERROR_INTERNAL, "CAN'T REP concat");
      evalone (son (e), 1);
      evalone (bro (son (e)), 1);
    }
    return;
  }
  case clear_tag: {
    if (as_file){
      asm_printop(".space %d",((a.ashsize+7)>>3) * rep);
    }
    out_value (0, ispace, make_INT64(0,((a.ashsize + 7) >> 3) * rep), 1);
    return;
  }
    case not_tag : 
    case and_tag : 
    case or_tag : 
    case shl_tag : 
    case shr_tag : 
    case bitf_to_int_tag : 
    case int_to_bitf_tag :
    case general_env_offset_tag :
    case env_offset_tag :
    case env_size_tag :
    case offset_add_tag :
    case offset_max_tag :
    case offset_pad_tag :
    case offset_mult_tag :
    case offset_div_tag :
    case offset_div_by_int_tag :
    case offset_subtract_tag :
    case offset_negate_tag : {
#if 1
      INT64 ee = evalexp (e);
      oneval(ee, a.ashalign, rep);
#endif
      return;
    }
#if 1
  case chvar_tag: {
    sh(son(e)) = sh(e);
    evalone(son(e),1);
    error(ERROR_WARNING, "Dubious change variety");
    return;
  }
#endif
  default: 
    error(ERROR_INTERNAL, "tag not in evaluated");
  }				/* end switch */
}	


/*
  evaluated
  
  This outputs data from the evaluated exp into either .sdata 
  or .data depending on size and labels this data either with 
  either id in main_globals or an anonymous label derived from l. 
  The result is the instore "address" of the constant. A negative 
  l implies that this is the initialisation of a global variable.
*/
instore
evaluated(exp e, int l)
{
  
  int   lab = (l == 0) ? next_dlab_sym () 
    : (l< 0)? l: -l;
  int   lab0 = lab;
  ash a;
  instore isa;
  exp z = e;

  isa.adval = 0;
  isa.b.offset = 0;
  isa.b.base = lab0;
  if (name (e) == clear_tag) {/* uninitialised global */
    int   size = (ashof (sh (e)).ashsize + 7) >> 3;
    bool temp = (l == 0 ||
		 (main_globals[-lab - 1] -> dec_u.dec_val.dec_id)[0] == '$');
    if (as_file) {
      asm_printf( (temp) ? "\t.lcomm\t" : "\t.comm\t");
      outlab(lab);
      asm_printf( " %d\n", size);
    }
    out_value((lab>=0)?tempsnos[lab-32]:symnos[-lab-1],(temp)?ilcomm:icomm,
	      make_INT64(0,size),1);
    return isa;
  }
  a = ashof (sh (z));
  if (a.ashsize <= G_number) {
    if (as_file){
      asm_printop(".sdata");
    }
    out_common(0,isdata);
  }
  else {
    if (as_file){
      asm_printop(".data");
    }
    out_common(0,idata);
  }
  if (as_file) {
    (void)outlab (lab);
    asm_printf( ":\n");
  }
  out_common((lab>0)?tempsnos[lab-32]:symnos[-lab-1],ilabel);
  if(as_file){
    asm_printop(".align 3");
    asm_printop(".align 0");
  }
  out_value(0,ialign,make_INT64(0,3),0);
  out_value(0,ialign,make_INT64(0,0),0);
  current_alignment=8;
  evalone (z, 1);
  return isa;
}










