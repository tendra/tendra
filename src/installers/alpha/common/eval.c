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


/* 	$Id: eval.c,v 1.1.1.1 1998/01/17 15:55:59 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: eval.c,v 1.1.1.1 1998/01/17 15:55:59 release Exp $";
#endif /* lint */

/*
$Log: eval.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:59  release
 * First version to be checked into rolling release.
 *
 * Revision 1.11  1996/02/15  09:52:38  john
 * Added offset constructions
 *
 * Revision 1.10  1995/08/30  16:14:28  john
 * Fix for new string_tag
 *
 * Revision 1.9  1995/08/21  08:44:13  john
 * Changed include files
 *
 * Revision 1.8  1995/07/27  09:36:52  john
 * Reformatting & changes for spec 4.0
 *
 * Revision 1.7  1995/05/23  10:56:11  john
 * Changes for 64 bit support
 *
 * Revision 1.6  1995/05/16  10:47:33  john
 * Changes for spec 3.1
 *
 * Revision 1.5  1995/04/10  14:12:57  john
 * Minor changes
 *
 * Revision 1.4  1995/04/07  11:02:02  john
 * Re-arranged the assembler output routines
 *
 * Revision 1.3  1995/04/04  08:17:46  john
 * Fixed evaluation of compounds containing bitfields
 *
 * Revision 1.2  1995/03/29  14:01:22  john
 * Changes to keep tcheck happy
 *
 * Revision 1.1.1.1  1995/03/23  10:39:06  john
 * Entered into CVS
 *
 * Revision 1.16  1995/03/23  10:03:54  john
 * Added support for scheduler + fixes for AVS
 *
 * Revision 1.15  1995/01/31  14:21:53  john
 * Minor change
 *
 * Revision 1.14  1995/01/26  13:39:07  john
 * Various portability improvements
 *
 * Revision 1.13  1995/01/20  13:43:12  john
 * Added default case to oneval
 *
 * Revision 1.12  1995/01/12  15:14:43  john
 * Removed dead code
 *
*/

/*
  eval.c
  This file contains functions which output data to the assembler
  file.  The parameters are an exp and an index into the table of
  externals.
*/

#include "config.h"
#include "xalloc.h"
#include "addresstypes.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "exptypes.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "flpttypes.h"
#include "flpt.h"
#include "main.h"
#include "frames.h"
#include "reg_defs.h"
#include "output.h"
#include "fbase.h"
#include "f64.h"
#include "cross.h"
#include "pseudo.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "syms.h"
#include "shape_range.h"  /* provides definitions of 
			     scmm_max,scmm_min, etc. */
#include "inst_fmt.h"
#include "eval.h"
#include "fail.h"

#if DO_SCHEDULE
#include "scheduler.h"
#endif
#include "procrecs.h"

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
int next_data_lab
    PROTO_Z ()
{
  return data_lab++;
}


/* as above-but also gives it a symno for .G output */
int next_dlab_sym
    PROTO_Z ()
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
mm maxmin
    PROTO_N ( ( s ) )
    PROTO_T ( shape s )
{
  switch (name (s)) {
  case scharhd: 
    return scmm;
  case ucharhd: 
    return uscmm;
  case swordhd: 
    return shmm;
  case uwordhd: 
    return ushmm;
  case slonghd: 
    return swmm;
  case ulonghd: 
    return uswmm;
  case s64hd:
    return s64mm;
  case u64hd:
    return u64mm;
  default: 	
    return uswmm;
  }
}


/*
  outlab
  outputs the label parameter if non negative else interprets it
  to be an index into the externals and outputs the identifier.
*/

char *outlab
    PROTO_N ( ( l ) )
    PROTO_T ( int l )
{
#if DO_SCHEDULE
  char * res = (char*)xcalloc(20,sizeof(char));
#else
  char * res = (char*)NULL;
#endif
  if (l >= 0) {
#if !DO_SCHEDULE
    (void)fprintf (as_file, "$$%d", l);
#else
    (void)sprintf(res,"$$%d",l);
#endif
  }
  else {
    char *extname = main_globals[-l - 1] -> dec_u.dec_val.dec_id;
#if !DO_SCHEDULE
    (void)fprintf (as_file, "%s", extname);
#else
    (void)sprintf (res, "%s", extname);
#endif
  }
  return res;
}

char  fltrepr[120];

void output_data_records
    PROTO_N ( ( strng,str,size ) )
    PROTO_T ( char *strng X char *str X int size )
{
  int pos = 0;
  Assert(size>0);
  Assert(!strng);
  while(size>0){
    output_data((char*)NULL,
		out_data(str,min(size,binasm_record_length)));
    pos += binasm_record_length;
    size -= binasm_record_length;
  }
  return;
}

      


/*
   This function outputs an IEEE format floating point number
*/
void outfloat
    PROTO_N ( ( e,rep,a ) )
    PROTO_T ( exp e X int rep X ash a )
{
  INT64 val;
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
#endif
  int fv = name(sh(e)) - shrealhd;
  r2l ieeeflt;
  ieeeflt = real2longs_IEEE(&flptnos[no(e)],fv);
  switch(fv){
    case 0:
    if(as_file){
#if !DO_SCHEDULE
      outstring("\t.long ");
      outhex(ieeeflt.i1);	
      outstring(" : ");
      outint(rep);
      outstring("\t# .s floating");
      outstring("\n");
#else
      outass("\t.long ");
      sprintf(outline,"0x%08x",ieeeflt.i1);
      outass(outline);
      outass(" : ");
      sprintf(outline,"%d",rep);
      outass(outline);
      outass("\t# .s floating\n");
#endif
    }
#if DO_SCHEDULE
    output_data(outass((char*)NULL),out_value(0,ilong,ieeeflt.i1,rep));
#else
    out_value(0,ilong,make_INT64(0,ieeeflt.i1),rep);
/*    out_value(0,ilong,ieeeflt.i1,rep);*/
#endif
    break;
    case 1:
    if(as_file){
#if !DO_SCHEDULE
      outstring("\t.quad ");
      outhex(ieeeflt.i2);
      outhexlow(ieeeflt.i1);
      outstring(" : ");
      outint(rep);
      outstring("\t# .t floating");
      outstring("\n");
#else
      outass("\t.quad ");
      sprintf(outline,"0x%08x%08x",ieeeflt.i2,ieeeflt.i1);
      outass(outline);
      outass(" : ");
      sprintf(outline,"%d",rep);
      outass(outline);
      outass("\t# .t floating\n");
#endif
    }
/*    val = ((long)ieeeflt.i2<<32) + (unsigned)ieeeflt.i1;*/
    val = make_INT64(ieeeflt.i2,(unsigned)ieeeflt.i1);
#if !DO_SCHEDULE     
    out_value(0,iquad,val,rep);
#else
    output_data(outass((char*)NULL),out_value(0,iquad,val,rep));
#endif     
    break;
    default:
    failer("invalid floating variety\n");
  }
#if DO_SCHEDULE
  free(outline);
#endif
  return;
}

/*
  evaluate the exp 'e' and return the resulting value
*/
INT64 evalexp
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
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
	failer ("should be align 1");
      }	
      if(a.ashsize!=64){
	w = INT64_and(w,INT64_subtract(INT64_shift_left(make_INT64(0,1),
							a.ashsize,1),
				       make_INT64(0,1),1));
      }	
      return w;
    }
    case not_tag: {
      return (INT64_not(evalexp (son (e))));
    }	
    case and_tag: {
      return (INT64_and(evalexp(son(e)),evalexp(bro(son(e)))));
    }
    case or_tag: {
      return (INT64_or(evalexp(son(e)),evalexp(bro(son(e)))));
    }
    case xor_tag: {
      return (INT64_xor(evalexp(son(e)),evalexp(bro(son(e)))));
    }
    case shr_tag: {
      return (INT64_shift_right(evalexp(son(e)),
				low_INT64(evalexp(bro(son(e)))),1));
    }
    case shl_tag: {
      return (INT64_shift_left(evalexp(son(e)),
			       low_INT64(evalexp(bro(son(e)))),1));
    }
    case concatnof_tag: {
      ash a;
      INT64 wd = evalexp (son (e));
      a = ashof (sh (son (e)));
      return (INT64_or(wd,
		       INT64_shift_left(evalexp(bro(son(e))),a.ashsize,1)));
    }
    case clear_tag: {
      ash a;
      a = ashof (sh (e));
      if (a.ashsize > REG_SIZE)
	failer ("clearshape");
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
    case offset_add_tag : {
      return (evalexp(son(e)) + evalexp(bro(son(e))));
    }
    case offset_max_tag : {
      return max(evalexp(son(e)),evalexp(bro(son(e))));
    }
    case offset_pad_tag : {
      return rounder(evalexp(son(e)),shape_align(sh(e))>>3);
    }
    case offset_mult_tag : {
      return evalexp(son(e))*evalexp(bro(son(e)));
    }
    case offset_div_tag : 
    case offset_div_by_int_tag : {
      return evalexp(son(e))/evalexp(bro(son(e)));
    }
    case offset_subtract_tag : {
      return evalexp(son(e)) - evalexp(bro(son(e)));
    }
    case offset_negate_tag : {
      return -evalexp(son(e));
    }
    
    default: 
    failer ("tag not in evalexp");
  }
  return zero_int64;
}


/*
  This function outputs values to the assembler file.  The 
  alignment of the last value to be output is retained and, 
  if it differs from the current one, a new alignment is set.
*/
void oneval
    PROTO_N ( ( val,al,rep ) )
    PROTO_T ( INT64 val X int al X int rep )
{
  char *store_type;
  char * outline = (char*)NULL;
  static int lastal = -1;
  unsigned int bval;
  if(al!=lastal){
    set_align(al);
    lastal=al;
  }
  switch(al){
  case 8:
    store_type=s_byte;
    bval = ibyte;
    break;
  case 16:
    store_type=s_word;
    bval = iword;
    break;
  case 32:
    store_type=s_long;
    bval = ilong;
    break;
  case 64:
    store_type=s_quad;
    bval = iquad;
    break;
  default:
    store_type=s_long;
    bval = ilong;
    break;
  }
  if(as_file){
#if !DO_SCHEDULE
    (void)fprintf(as_file,"\t.%s ",store_type);
    out_INT64(val);
    (void)fprintf(as_file," :%d\n",rep);
#else
    outline = (char*)xcalloc(30,sizeof(char));
    sprintf(outline,"\t.%s %ld :%d\n",store_type,val,rep);
#endif
  }
#if DO_SCHEDULE
  output_data(outline,out_value(0,bval,val,rep));
#else  
  out_value(0,bval,val,rep);
#endif
  return;
}


INT64 bits_list
    PROTO_N ( ( val ) )
    PROTO_T ( int val )
{
  int loop;
  INT64 result=make_INT64(0,0);
/*  Assert (val <=31);*/
  Assert (val <=64);
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
void evalone
    PROTO_N ( ( e,rep ) )
    PROTO_T ( exp e X int rep )
{
  ash a;
  int overflow;
  if (e == nilexp) return;
  a = ashof (sh (e));
  switch (name (e)) {
  case string_tag: {
    long char_size = props(e);
    long  strsize = shape_size(sh(e))/char_size;
    char *st = nostr(e);
    long  strs = shape_size(sh(e))>>3;
    int   i,j;
    int hex_output=0;
#if DO_SCHEDULE
    char * outline = (char*)xcalloc(80,sizeof(char));
#endif
    if (rep != 1 && as_file){
#if !DO_SCHEDULE
      (void)fprintf (as_file, "\t.repeat %d\n", rep);
#else
      (void)sprintf(outline,"\t.repeat %d\n",rep);
      outass(outline);
#endif
    }
    set_align(a.ashalign);
    if(as_file){
      if(strsize<256 && (char_size ==8)){
#if !DO_SCHEDULE
	(void)fprintf(as_file,"\t.ascii\t\"");
#else
	outass("\t.ascii\t\"");
#endif
	for(j=0;j<strsize;++j){
	  if(st[j]>=32 && st[j]<0x7f && (!hex_output)){
	    if(st[j]=='\"'){
#if !DO_SCHEDULE
	      (void)fprintf(as_file,"\\\"");
#else
	      outass("\\\"");
#endif
	    }
	    else if(st[j]=='\\'){
#if !DO_SCHEDULE
	      (void)fprintf(as_file,"\\\\");
#else
	      outass("\\\\");
#endif
	    }
	    else{
#if !DO_SCHEDULE
	      (void)fprintf(as_file,"%c",st[j]);
#else
	      (void)sprintf(outline,"%c",st[j]);
	      outass(outline);
#endif
	    }
	  }	
	  else{
#if !DO_SCHEDULE
	    (void)fprintf(as_file,"\\X%x",st[j]&0xff);
#else
	    (void)sprintf(outline,"\\X%x",st[j]&0xff);
	    outass(outline);
#endif
	    hex_output=1;
	  }
	 }
#if !DO_SCHEDULE
	(void)fprintf(as_file,"\"\n");
#else
	outass("\"\n");
#endif
      }
      else{
	for (j=0; j< strsize; ) {
	  switch(char_size) {
	  case 8:{
#if !DO_SCHEDULE
	    (void)fprintf (as_file, "\t.byte ");
#else	
	    outass("\t.byte ");
#endif	
	    break;
	  }
	  case 16:{
#if !DO_SCHEDULE
	    (void)fprintf (as_file, "\t.word ");
#else	
	    outass("\t.word ");
#endif
	    break;
	  }
	  case 32:{
#if !DO_SCHEDULE
	    (void)fprintf (as_file, "\t.long "); 
#else
	    outass("\t.long ");
#endif
	    break;
	  }
	  case 64:{
#if !DO_SCHEDULE
	    (void)fprintf (as_file, "\t.quad "); 
#else	
	    outass("\t.quad ");
#endif
	    break;
	  }
	  }
	  for (i = j; i < strsize && i-j < 8; i++) {
	    switch (char_size) { 
	    case 8:
#if !DO_SCHEDULE
	      (void)fprintf (as_file, "0x%x ", st[i]&0xff); 
#else
	      sprintf(outline,"0x%x ", st[i]&0xff); 
	      outass(outline);
#endif
	      break;
	    case 16:
#if !DO_SCHEDULE
	      (void)fprintf (as_file, "0x%x ", ((unsigned short *)st)[i]); 
#else
	      (void)sprintf (outline, "0x%x ", ((unsigned short *)st)[i]); 
	      outass(outline);
#endif
	      break;
	    case 32:
#if !DO_SCHEDULE
	      (void)fprintf (as_file, "0x%x ", ((int *)st)[i]); 
#else
	      (void)sprintf (outline, "0x%x ", ((int *)st)[i]); 
	      outass(outline);
#endif
	      break;
	    case 64:{
	      flt64 bigint;
	      bigint = flt_to_f64(((flpt*)st)[i],is_signed(sh(e)),&overflow);
#if !DO_SCHEDULE
	      out_INT64(flt64_to_INT64(bigint));outstring(" ");
#else
	      sprintf(outline,"%ld ",flt64_to_INT64(bigint));
	      outass(outline);
#endif	
	      break;
	    }		        	        
	    }
	  }
	  j =i;
#if DO_SCHEDULE
	  outass("\n");
#else
	  (void)fprintf (as_file, "\n");
#endif
	}
      }
    }
#if !DO_SCHEDULE
    out_chars(0,iascii,strs,rep);
#else
    output_data(outass((char*)NULL),out_chars(0,iascii,strs,rep));
#endif     
    if(char_size == 64){
      /* replace the float indexes used to represent the array */
      char * newst = (char*)xcalloc(strs,sizeof(char));
      int i;
      for(i=0;i<strsize;++i){
	((INT64*)newst)[i] = flt64_to_INT64(flt_to_f64(((flpt*)st)[i],
						       is_signed(sh(e)),
						       &overflow));
      }
#if DO_SCHEDULE
      output_data_records((char*)NULL,newst,strs);
#else
      out_data(newst,strs);
#endif
    }
    else{
#if DO_SCHEDULE
      output_data_records((char*)NULL,st,strs);
      output_data((char*)NULL,out_data(st,strs));
#else       
      out_data(st,strs);
#endif
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
    char * outline = (char*)NULL;
    switch(a.ashalign){
      case 8:
      storage_type = s_byte;
      storage_id = ibyte;
      break;
      case 16:
      storage_type = s_word;
      storage_id = iword;
      break;
      case 32:
      storage_type = s_long;
      storage_id = ilong;
      break;
      case 64:
      storage_type = s_quad;
      storage_id = iquad;
      break;
    }	
    set_align(a.ashalign);	
    if (as_file) {
#if DO_SCHEDULE
      outline = (char*)xcalloc(40,sizeof(char));
#endif
      if (no (e) == 0) {
#if !DO_SCHEDULE
	(void)fprintf (as_file, "\t.%s %s : %d\n", storage_type,nm, rep);
#else
	(void)sprintf (outline, "\t.%s %s : %d\n", storage_type,nm, rep);
#endif
      }		
      else {
#if !DO_SCHEDULE
	(void)fprintf (as_file, "\t.%s %s + %d :%d\n", storage_type,
			nm, no (e) / 8, rep);
#else
	(void)sprintf (outline, "\t.%s %s + %d :%d\n", storage_type,
			nm, no (e) / 8, rep);
#endif
      }
    }
#if DO_SCHEDULE
    output_data(outline,out_value(symnos[symdef],storage_id,no(e)/8,rep));
#else     
    out_value(symnos[symdef],storage_id,make_INT64(0,no(e)/8),rep);
#endif
    return;
   }
  case compound_tag:  {
    exp tup = son (e);
    INT64 val;
    bool first_bits=1;
    long bits_start =0;
    long offs =0;
    if (rep != 1)
      failer ("CAN'T REP TUPLES");
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
	    if (BIGEND) {
	      for(;;) {
		oneval(INT64_shift_right(val,24,1),8,1);
		/*oneval(val>>24, 8, 1);*/
		val = INT64_shift_left(val,8,1);
		/*val <<=8;*/
		bits_start+=8;
		if (offs-bits_start <= 0) break;
	      }	
	    }
	    else {                          
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
	  if (BIGEND) {
	    for(;;) {
	      oneval(INT64_shift_right(val,24,1),8,1);
	      /*oneval(val>>24, 8, 1);*/
	      val = INT64_shift_left(val,8,1);
	      /*val <<=8;*/
	      bits_start+=8;
	      if (offs-bits_start <= 0) break;
	    }
	  }
	  else {		    
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
	  if (BIGEND) {
	    oneval(INT64_shift_right(val,24,1),8,1);
	    /*oneval(val>>24, 8, 1);*/
	    val = INT64_shift_left(val,8,1);
	    /*val <<=8;*/
	    bits_start+=8;
	    if (offs-bits_start<= 0) break;
	  }
	  else {         
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
      failer ("CAN'T REP TUPLES");   	
    set_align(a.ashalign);
    if (s == nilexp) return;
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
	failer ("CAN'T REP concat");
      evalone (son (e), 1);
      evalone (bro (son (e)), 1);
    }
    return;
  }
  case clear_tag: {
    char * outline;
    if (as_file){
#if !DO_SCHEDULE
      (void)fprintf (as_file, "\t.space %d\n",((a.ashsize+7)>>3) * rep);
#else
      outline = (char*)xcalloc(20,sizeof(char));
      sprintf(outline,"\t.space %d\n",((a.ashsize+7)>>3) * rep);
#endif
    }
#if DO_SCHEDULE
    output_data(outline,out_value(0,ispace,((a.ashsize+7)>>3)+rep,1));
#else
    out_value (0, ispace, make_INT64(0,((a.ashsize + 7) >> 3) * rep), 1);
#endif
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
    alphawarn("Dubious change variety\n");
    return;
  }
#endif
  default: 
    failer ("tag not in evaluated");
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
instore evaluated
    PROTO_N ( ( e,l ) )
    PROTO_T ( exp e X int l )
{
  
  int   lab = (l == 0) ? next_dlab_sym () 
    : (l< 0)? l: -l;
  int   lab0 = lab;
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
#endif
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
#if !DO_SCHEDULE
      (void)fprintf (as_file, (temp) ? "\t.lcomm\t" : "\t.comm\t");
      outlab(lab);
#else
      outass((temp)?"\t.lcomm\t":"\t.comm\t");
      outass(outlab(lab));
#endif	
#if !DO_SCHEDULE
      (void)fprintf (as_file, " %d\n", size);
#else
      sprintf(outline," %d\n",size);
      outass(outline);
#endif
    }
#if DO_SCHEDULE
    output_data(outass((char*)NULL),out_value((lab>=0)?tempsnos[lab-32]:
				  symnos[-lab-1],(temp)?ilcomm:icomm,size,1));
    
#else
    out_value((lab>=0)?tempsnos[lab-32]:symnos[-lab-1],(temp)?ilcomm:icomm,
	      make_INT64(0,size),1);
#endif      
    return isa;
  }
  a = ashof (sh (z));
  if (a.ashsize <= G_number) {
    if (as_file){
#if DO_SCHEDULE
      outline = (char*)xcalloc(20,sizeof(char));
      (void)sprintf(outline, "\t.sdata\n");
#else
      (void)fprintf (as_file, "\t.sdata\n");
#endif
    }
#if DO_SCHEDULE
    output_data(outline,out_common(0,isdata));
#else
    out_common(0,isdata);
#endif
  }
  else {
    if (as_file){
#if DO_SCHEDULE
      outline = (char*)xcalloc(20,sizeof(char));
      (void)sprintf(outline, "\t.data\n");
#else	
      (void)fprintf (as_file, "\t.data\n");
#endif
    }
#if DO_SCHEDULE
    output_data(outline,out_common(0,idata));
#else      
    out_common(0,idata);
#endif
  }
  if (as_file) {
#if DO_SCHEDULE
    outline = outlab(lab);
    strcat(outline,":\n");
#else    
    (void)outlab (lab);
    (void)fprintf (as_file, ":\n");
#endif
  }
#if DO_SCHEDULE
  output_data(outline,out_common((lab>0)?tempsnos[lab-32]:symnos[-lab-1],
				 ilabel));
#else
  out_common((lab>0)?tempsnos[lab-32]:symnos[-lab-1],ilabel);
#endif
  if(as_file){
#if !DO_SCHEDULE
    fprintf(as_file,"\t.align 3\n");
    fprintf(as_file,"\t.align 0\n");
#endif
  }
#if DO_SCHEDULE
  output_instruction(class_null,"\t.align 3\n",out_value(0,ialign,3,0));
  output_instruction(class_null,"\t.align 0\n",out_value(0,ialign,0,0));
#else
  out_value(0,ialign,make_INT64(0,3),0);
  out_value(0,ialign,make_INT64(0,0),0);
#endif
  current_alignment=8;
  evalone (z, 1);
  return isa;
}










