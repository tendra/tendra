/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  move.c
  This file contains code to move a value from src to dest, 
  where src can be in a general purpose register, a floating 
  point register, or in store.  Delivers register used if dest 
  in store, otherwise NOREG.
*/

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include "alpha_ins.h"
#include "inst_fmt.h"
#include "addresstypes.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "main.h"
#include "reg_defs.h"
#include "guard.h"
#include "locate.h"
#include "regexps.h"
#include "guard.h"
#include "getregs.h"
#include "frames.h"
#include "pseudo.h"
#include "labels.h"
#include "move.h"
#include "localexpmacs.h"

/* bit masks */
#if BLDARCHBITS == 64

extern int stack_top;
INT64 word_mask=0xffffL;
INT64 long_mask=0xffffffffL;
INT64 one_64=1L;

#else

INT64 word_mask={
0  0,0xffff
};

INT64 long_mask={
  0,0xffffffff
};

INT64 one_64 = {0,1};

#endif

/*
  Returns true if the data is aligned properly, false otherwise.
*/
static bool
aligned(baseoff address, int al)
{
  if((address.base<0) || (address.base > 31))
    return 1;
  return ((regexps[address.base].alignment>=al || (address.base==SP)||
	   ((address.base == FP)&&Has_fp)) && ((address.offset%al)==0));
}

/*
  produces a unary representation for the number in
*/
static int
unary(int in)
{
  int result=0;
  int loop;
  assert(in<9);	/* in is a number of bytes */
  for(loop=0;loop<in;++loop){
    result <<= 1;
    result |= 1;
  }
  return result;
}
  

#define aligned_reg(X,al) (((X<0) || (X>31))?0:((regexps[X].alignment>=al)||(X==SP)||((X==FP)&&Has_fp)))

/* take account of adval here ? */
#if 1
#define address_equal(X,Y) ((X.b.base==Y.b.base) && (X.b.offset==Y.b.offset)\
			    && (((X.adval==Y.adval))||(Y.adval)))
#else
#define address_equal(X,Y) 0
#endif


int
choose_block_size(where dest, int al)
{
  int bsize;
  if(!(insalt(dest.answhere).b.offset%8)){
    bsize = (dest.ashwhere.ashsize%64==0)?64:min(al,64);
  }
  else if(!(insalt(dest.answhere).b.offset%4)){
    bsize = (dest.ashwhere.ashsize%32==0)?32:min(al,32);
  }
  else if(!(insalt(dest.answhere).b.offset%2)){
    bsize = (dest.ashwhere.ashsize%16==0)?16:min(al,16);
  }
  else{
    bsize=8;
  }
  return bsize;
}



/*
  This function moves a piece of data from one location to another.
  The parameters are as follows:
  src	: 	the location of the source
  dest	:	the destination
  freeregs:	registers available for use 
  sgned:	true if data is signed, false otherwise
*/
int
move(ans src, where dest, space freeregs, bool sgned)
{
  int al=dest.ashwhere.ashalign;
  int size=dest.ashwhere.ashsize;
  enum {
    BYTE,WORD,LONGWORD,QUADWORD
  } datatype;
  switch(src.discrim){
    case insomereg :
    case insomefreg :{
      error(ERR_INTERNAL, "Source reg not specified");
      break;
    }	
    case inreg :{
      int rsrc = regalt(src);
      freeregs = guardreg(rsrc,freeregs);
      switch(dest.answhere.discrim){
	case inreg:{
	  /* src & dest both in a general purpose register */
	  int rdest=regalt(dest.answhere);
	  if(rdest!=rsrc && rdest!=NO_REG){
	    operate_fmt(i_bis,rsrc,rsrc,rdest); /* dest = src OR src */
	  }  
	  return NOREG;
	}
	case insomereg:{
	  /* can choose dest register to be source register */
	  int *somereg = someregalt(dest.answhere);
	  if(*somereg!=-1) error(ERR_INTERNAL, "somereg!=-1");
	  *somereg=rsrc;
	  return NOREG;
	}
	case infreg:{
	  /* source in gen reg, dest in floating point */
	  /* must write onto stack, load into float register, convert*/
	  freg fr;
	  baseoff mem_loc;
	  mem_loc.base = SP;
	  /* should really check that space is available on stack */
	  mem_loc.offset = stack_top;		/* ? */
	  fr=fregalt(dest.answhere);
	  load_store((size==32)?i_stl:i_stq,rsrc,mem_loc);
	  float_load_store((size==32)?i_lds:i_ldt,fr.fr,mem_loc);
	  return NOREG;
	}
	case insomefreg:{
	  /* source in fixed, can choose flt dest */
	  somefreg sfr;
	  freg fr;
	  sfr = somefregalt(dest.answhere);
	  if(*sfr.fr != -1) error(ERR_INTERNAL, "Somfreg *2");
	  *sfr.fr = getfreg(freeregs.flt);
	  fr.fr = *sfr.fr;
	  fr.type = sfr.type;
	  setfregalt(dest.answhere,fr);
	  return move(src,dest,freeregs,sgned);
	}
	case notinreg:{
	  instore is;
	  instruction st;
	  is=insalt(dest.answhere);
	  size=(size==0)?64:(size<8)?8:size;
	  if(al == 1) al = size;
	  if(size==32){
	    st = i_stl;
	  }
	  else {
	    st = aligned(is.b,8)?i_stq:i_stq_u;
	    st = i_stq;
	  }	
      /* add locking, etc */
      if(is.adval){
	switch(al){	/* changed from switch(size) */
	  case 8:{
	    /* source in register -> byte in memory */
	    int byte_address = AT;
	    /* use the assembler temp register to store the address.
	     The system compiler uses this scheme, not sure why 
	     though. */
	    space gsp = guardreg(rsrc,freeregs);
	    int word_containing_byte;
	    int t1;
	    baseoff a;
	    gsp = guardreg(is.b.base,gsp);
	    if(aligned_reg(is.b.base,4) && ((is.b.offset%4)==0 && 
					    is.b.offset>0)/*aligned(is.b,4)*/){
	      /*
		if the target address is aligned on a 4 byte boundary
		then we can use an optimised load sequence, 
		eliminating the lda instruction and replacing the
		ldq_u and stq_u with ldl and stl.
	   */
	      int r1 = getreg(gsp.fixed);
	      int r2 = getreg(gsp.fixed);
	      baseoff newbo;
	      newbo.base = is.b.base;
	      newbo.offset = (is.b.offset/4)*4;
	      load_store(i_ldl,r1,newbo);
	      operate_fmt_immediate(i_insbl,rsrc,is.b.offset%4,r2);
	      operate_fmt_immediate(i_mskbl,r1,is.b.offset%4,r1);
	      operate_fmt(i_bis,r2,r1,r1);
	      load_store(i_stl,r1,newbo);
	    }
	    else{
	      word_containing_byte = getreg(gsp.fixed);
	      t1 = getreg(gsp.fixed);
	      a.base = byte_address;
	      a.offset = 0;
	      setnoat();
	      load_store(i_lda,byte_address,is.b);
	      load_store(i_ldq_u,word_containing_byte,a);
	      operate_fmt(i_insbl,rsrc,byte_address,t1);
	      operate_fmt(i_mskbl,word_containing_byte,byte_address,
			  word_containing_byte);
	      operate_fmt(i_bis,word_containing_byte,t1,word_containing_byte);
	      load_store(i_stq_u,word_containing_byte,a);
	      setat();
	    }
	    break;
	  }
	  case 16:{
	    /* source in register -> word in memory */
	    int word_address=AT;
	    space ssp = guardreg(is.b.base,freeregs);
	    int qw_containing_word,tmp1,tmp2,tmp3;
	    ssp = guardreg(rsrc,ssp);
	    qw_containing_word=getreg(ssp.fixed);
	    ssp=guardreg(qw_containing_word,ssp);
	    tmp1=getreg(ssp.fixed);
	    ssp=guardreg(tmp1,ssp);
	    tmp2=getreg(ssp.fixed);
	    ssp=guardreg(tmp2,ssp);
	    if(aligned_reg(is.b.base,4) && ((is.b.offset%4) == 0) &&
	       is.b.offset>0) {
	      /*
		see byte case above for details.
		*/
	      baseoff newbo;
	      newbo.base = is.b.base;
	      newbo.offset = (is.b.offset/4)*4;
	      load_store(i_ldl,tmp1,newbo);
	      operate_fmt_immediate(i_inswl,rsrc,is.b.offset%4,tmp2);
	      operate_fmt_immediate(i_mskwl,tmp1,is.b.offset%4,tmp1);
	      operate_fmt(i_bis,tmp2,tmp1,tmp1);
	      load_store(i_stl,tmp1,newbo);
	    }
	    else{
	      tmp3=getreg(ssp.fixed);
	      setnoat();
	      load_store(i_lda,word_address,is.b);
	      is.b.offset++;
	      load_store(i_ldq_u,qw_containing_word,is.b);
	      is.b.offset--;
	      load_store(i_ldq_u,tmp1,is.b);
	      operate_fmt(i_inswh,rsrc,word_address,tmp2);
	      operate_fmt(i_inswl,rsrc,word_address,tmp3);
	      operate_fmt(i_mskwh,qw_containing_word,word_address,
			  qw_containing_word);
	      operate_fmt(i_mskwl,tmp1,word_address,tmp1);
	      setat();
	      operate_fmt(i_bis,qw_containing_word,tmp2,qw_containing_word);
	      operate_fmt(i_bis,tmp1,tmp3,tmp1);
	      is.b.offset++;
	      load_store(i_stq_u,qw_containing_word,is.b);
	      is.b.offset--;
	      load_store(i_stq_u,tmp1,is.b);
	      setat();
	    }
	    break;
	  }
	  case 32:
	  case 64:
	  load_store(st,rsrc,is.b);
	  break;
	  default:
	  error(ERR_INTERNAL, "unsupported data size");
	}
      }
      else{
	ans newsrc;
	where newdest;
	baseoff tmploc;
	instore iss;
	tmploc.offset = 0;
	tmploc.base = getreg(freeregs.fixed);
	setinsalt(newsrc,is);
	setregalt(newdest.answhere,tmploc.base);
	newdest.ashwhere.ashsize=64;
	newdest.ashwhere.ashalign=64;
	(void)move(newsrc,newdest,guardreg(tmploc.base,freeregs),sgned);
	/* now src is evaluated into tmploc */
	iss.adval=1;
	iss.b = tmploc;
	newdest.ashwhere.ashsize=size;		/* ??? */
	newdest.ashwhere.ashalign=al;
	setinsalt(newdest.answhere,iss);
	setregalt(newsrc,rsrc);
	(void)move(newsrc,newdest,guardreg(tmploc.base,freeregs),sgned);
	return rsrc;
      }
      return NOREG;
    }
    }
    break;
  }
    case infreg:{
      freg fr;
      fr=fregalt(src);
      switch(dest.answhere.discrim){
	case inreg:{
	  /* source in floating point, dest in fixed */
	  int rdest = regalt(dest.answhere);
	  if(rdest != NO_REG){
	    freg fr=fregalt(src);
	    int r = regalt(dest.answhere);
	    baseoff mem_loc;
	    mem_loc.base = SP;
	    mem_loc.offset = stack_top;
	    float_load_store(i_stt,fr.fr,mem_loc);
	    load_store(i_ldq,r,mem_loc);
	  }
	  return NOREG;
	}
	case insomereg:{
	  somefreg sfr;
	  sfr = somefregalt(dest.answhere);
	  assert(*(sfr.fr)== -1);
	  *(sfr.fr) = fr.fr;
	  return NOREG;
	}
	case insomefreg:{
	  /* simple - can choose destination freg */
	  somefreg sfr;
	  int res;
	  sfr = somefregalt(dest.answhere);
	  *(sfr.fr) = fregalt(src).fr;
	  fr.fr = *sfr.fr;
	  fr.type = sfr.type;
	  setfregalt(dest.answhere,fr);
	  res=move(src,dest,freeregs,sgned);
	  return res;		/* ?? */
	}
	case infreg:{
	  /* simple copy from one freg to another */
	  freg frd;
	  frd=fregalt(dest.answhere);
	  if(fr.fr != frd.fr){
	    float_op(i_cpys,fr.fr,fr.fr,frd.fr);
	  }	
	  return NOREG;
	}
	case notinreg:{
	  /* forget VAX floats for the moment */
	  /* src in float, dest in store */
	  instruction st=(fr.type==IEEE_double)?i_stt:i_sts;
	  instore is;
	  if(((dest.ashwhere.ashsize==64)&&(fr.type == IEEE_single)) 
	     || ((dest.ashwhere.ashsize==32) && (fr.type == IEEE_double))){
	    st = (dest.ashwhere.ashsize==64)?i_stt:i_sts;
	    if(dest.ashwhere.ashsize==32){
	      /* .t floats must be explicitly converted to .s */
	      freg frtmp;
	      frtmp.fr=getfreg(freeregs.flt);
	      frtmp.type = IEEE_single;
	      float_convert(i_cvtts,fr.fr,frtmp.fr);
	      fr=frtmp;
	    }
	  }
	  is = insalt(dest.answhere);
	  if(is.adval)
	    float_load_store(st,fr.fr,is.b);
	  else {
	    baseoff bo;
	    bo.base = getreg(freeregs.fixed);
	    bo.offset = 0;
	    load_store(i_ldq,bo.base,is.b);
	    float_load_store(st,fr.fr,bo);
	  }
	  return (fr.type == IEEE_double)?-(fr.fr+32):(fr.fr+32);
	}
      }
      break;
    }
    case notinreg:{
      /* source instore */
      instore iss;
      instruction load;
      instruction store;
      iss=insalt(src);
      if(iss.adval && iss.b.offset==0 && iss.b.base>=0 && iss.b.base<31){
	setregalt(src,iss.b.base);
	return move(src,dest,freeregs,sgned); /* ?? */
      }	
      if((size==64)||(size%64==0)){
	load=(iss.adval)?i_lda:((aligned(iss.b,8))?i_ldq:i_ldq_u);
	load = (iss.adval)? i_lda:i_ldq;
	store=i_stq;
      }
      else{
	load = (iss.adval)?i_lda:((al==32)?i_ldl:i_ldq);
	store=(iss.adval)?i_stq:((al==32)?i_stl:i_stq);
      }
      switch(al){
	case 8:
	datatype = BYTE;
	break;
	case 16:
	datatype = WORD;
	break;
	case 32:
	datatype = LONGWORD;
	break;
	default:
	datatype = QUADWORD;
      }	
      switch(dest.answhere.discrim){
	case insomefreg:{
	  /* src in store, can choose freg for destination */
	  somefreg sfr;
	  freg fr;
	  sfr=somefregalt(dest.answhere);
	  if(*sfr.fr!=-1) error(ERR_INTERNAL, "instore->some freg");
	  *sfr.fr=getfreg(freeregs.flt);
	  fr.fr=*sfr.fr;
	  fr.type=sfr.type;
	  setfregalt(dest.answhere,fr);
	  return move(src,dest,freeregs,sgned);
	}
	case insomereg:{
	  /* source instore, can choose destination register */
	  int *sr=someregalt(dest.answhere);
	  if(*sr!=-1) error(ERR_INTERNAL, "somereg **");
	  *sr=getreg(freeregs.fixed);
	  setregalt(dest.answhere,*sr);
	  /* continue to next case */
	}
	FALL_THROUGH;
	case inreg:{
	  /* src instore, destination in general register */
	  int rdest=regalt(dest.answhere);
	  if(iss.b.base == rdest){
	    int newbase = getreg(guardreg(rdest,freeregs).fixed);
	    operate_fmt(i_bis,rdest,rdest,newbase);
	    iss.b.base = newbase;
	  }
	  if(rdest!=NO_REG){
	    if(((datatype == BYTE) || (datatype == WORD) 
	       ||((datatype == LONGWORD) && (iss.b.offset%4))
	       ||((datatype == QUADWORD) && (iss.b.offset%8)))
	       && !(iss.adval) ){
	      switch(datatype){
		case BYTE:{
		  space newspace=guardreg(rdest,freeregs);
		  int tmpreg;
		  newspace = guardreg(iss.b.base,newspace); /* error? */
		  tmpreg=getreg(newspace.fixed);
	    
		  if(aligned_reg(iss.b.base,4) &&( iss.b.offset%4==0) &&
		     (iss.b.offset >= 0)){
		    /* if its address is 32 bit aligned an optimised 
		       load can be performed.  
		       (This doesn't win us much on the 21064).
		       */
		    baseoff newbo;
		    newbo.base=iss.b.base;
		    newbo.offset = (iss.b.offset/4)*4;
		    load_store(i_ldl,rdest,newbo);
		    if(sgned){
		      operate_fmt_immediate(i_sll,rdest,56-8*(iss.b.offset%4),
					    rdest);
		      operate_fmt_immediate(i_sra,rdest,56,rdest);
		    }
		    else{
		      operate_fmt_immediate(i_extbl,rdest,(iss.b.offset%4),rdest);
		    }
		  }
		  else{
		    load_store(i_ldq_u,rdest,iss.b); /* should it be iss.b ? */
		    if(sgned){
		      iss.b.offset++;
		      load_store(i_lda,tmpreg,iss.b);
		      operate_fmt(i_extqh,rdest,tmpreg,rdest);
		      operate_fmt_immediate(i_sra,rdest,56,rdest);
		    }
		    else{
		      load_store(i_lda,tmpreg,iss.b);
		      operate_fmt(i_extbl,rdest,tmpreg,rdest);
		    }
		  }
		  clear_reg(tmpreg);
		  break;
		}
		case WORD:{
#if 0
		  space msp = guardreg(rdest,freeregs);
		  int tmpreg1=getreg(msp.fixed);
		  int tmpreg2;
		  msp = guardreg(tmpreg1,msp);
		  tmpreg2=getreg(msp.fixed);
#endif
		  if(aligned_reg(iss.b.base,4) && (iss.b.offset>=0)){
		    /* if the base address is aligned on a 32 bit boundary
		       we can use an optimised load sequence.
		       */
		    baseoff alboff;
		    alboff.base = iss.b.base;
		    alboff.offset = (iss.b.offset/4)*4;
		    load_store(i_ldl,rdest,alboff);
		    if(sgned){
		      operate_fmt_immediate(i_sll,rdest,
					    48-8*(iss.b.offset%4),rdest);
		      operate_fmt_immediate(i_sra,rdest,48,rdest);
		    }
		    else{
		      operate_fmt_immediate(i_extwl,rdest,iss.b.offset%4,rdest);
		    }
		  }		
		  else{
		    setnoat();
		    iss.b.offset += 2;
		    load_store(i_lda,AT,iss.b);
		    iss.b.offset -= 2;
		    load_store(i_ldq_u,rdest,iss.b);
		    operate_fmt(i_extqh,rdest,AT,rdest);
		    operate_fmt_immediate(i_sra,rdest,48,rdest);
		    /* sgned ? */
		    if(!sgned) operate_fmt_immediate(i_zapnot,rdest,3,rdest);
		    setat();
		  }
		  /*
		  clear_reg(tmpreg1);
		  clear_reg(tmpreg2);
		  */
		  break;
		}
		case LONGWORD:{
		  int r2,r3;
		  space newspace = guardreg(rdest,freeregs);
		  /* treat unaligned longword access here */
		  newspace = guardreg(iss.b.base,newspace);
		  r2 = getreg(newspace.fixed);
		  r3 = getreg(newspace.fixed);
		  load_store(i_ldq_u,rdest,iss.b);
		  iss.b.offset += 3;
		  load_store(i_ldq_u,r2,iss.b);
		  iss.b.offset -= 3;
		  load_store(i_lda,r3,iss.b);
		  operate_fmt(i_extll,rdest,r3,rdest);
		  operate_fmt(i_extlh,r2,r3,r2);
		  operate_fmt(i_bis,r2,rdest,rdest);
		  if(sgned){
		    operate_fmt_immediate(i_sll,rdest,32,rdest);
		    operate_fmt_immediate(i_sra,rdest,32,rdest);
		  }
		  clear_reg(r2);
		  clear_reg(r3);
		  break;
		}
		case QUADWORD:{
		  int r2,r3;
		  space newspace = guardreg(rdest,freeregs);
		  newspace = guardreg(iss.b.base,newspace);
		  r2 = getreg(newspace.fixed);
		  r3 = getreg(newspace.fixed);
		  load_store(i_ldq_u,rdest,iss.b);
		  iss.b.offset += 7;
		  load_store(i_ldq_u,r2,iss.b);
		  iss.b.offset -= 7;
		  load_store(i_lda,r3,iss.b);
		  operate_fmt(i_extql,rdest,r3,rdest);
		  operate_fmt(i_extqh,r2,r3,r2);
		  operate_fmt(i_bis,r2,rdest,rdest);
		  clear_reg(r2);
		  clear_reg(r3);
		  break;
		}
	      }
	    }
	    else if (iss.adval){
	      load_store(i_lda,rdest,iss.b);
	      switch(datatype){
		case BYTE:
		operate_fmt_immediate(i_zapnot,rdest,1,rdest);
		break;
		case WORD:
		operate_fmt_immediate(i_zapnot,rdest,2,rdest);
		break;
		case LONGWORD:
		operate_fmt_immediate(i_addl,rdest,0,rdest);
		break;
		default:;
	      }
	    }
	    else{
	      int rt=getreg(guardreg(iss.b.base,freeregs).fixed);
	      if((size>64)&&((rdest<FIRST_INT_ARG)||(rdest>LAST_INT_ARG))){
		error(ERR_INTERNAL, "Register allocation: Illegal block copy.");
	      }
	      if(size>64){/* this should only occur with parameter regs */
		ans newsrc;
		where newdest;
		instore dis;
		if(al<64){
		  al=64;
		  load=i_ldq;
		}
		for(;(rdest<=LAST_INT_ARG)&&(size>0);++rdest,
		      iss.b.offset+=(al>>3)){
		  load_store(load,rdest,iss.b);	
		  size-=al;
		}
		/* once the registers have been filled, it's 
		   time to use the stack for the remaining parameters.  
		   The function calling move() must allow for 
		   this space to be used.*/
		if(size>0){
		  /*dis.b.base=(Has_fp)?FP:SP;*/
		  dis.b.base = SP;
		  dis.b.offset=0;
		  dis.adval=1;
		  setinsalt(newsrc,iss);
		  newdest.ashwhere.ashsize=size;
		  newdest.ashwhere.ashalign=64;
		  setinsalt(newdest.answhere,dis);
		  return move(newsrc,newdest,freeregs,sgned);
		}
		else{
		  return NOREG;
		}
	      }
	      else{
		load_store(load,rdest,iss.b);
	      }
	      if(ins_equal(load,i_lda) /*|| !sgned*/)
		switch(size){
		  case 8:
		  operate_fmt_immediate(i_and,rdest,0xff,rdest);
		  break;
		  case 16:
		  load_store_immediate(i_ldiq,rt,word_mask);
		  operate_fmt(i_and,rdest,rt,rdest);
		  break;
		  case 32:
		  operate_fmt_immediate(i_addl,rdest,0,rdest);
		  break;
		  default:;
		}
	    }			
	  }
	  return NOREG;
	}
	case infreg:{
	  /* src instore, dest in floating point reg */
	  freg frdest;
	  frdest=fregalt(dest.answhere);
	  switch(frdest.type){
	    case IEEE_single:
	    if(size==32){
	      float_load_store(i_lds,frdest.fr,iss.b);
	    }
	    else{
	      float_load_store(i_ldt,frdest.fr,iss.b);
	      float_convert(i_cvtts,frdest.fr,frdest.fr);
	    }
	    break;
	    case IEEE_double:   
	    if(size==32)
	      float_load_store(i_lds,frdest.fr,iss.b);
	    else
	      float_load_store(i_ldt,frdest.fr,iss.b);
	    break;
	    default:
	    error(ERR_INTERNAL, "VAX floating point formats not supported");
	  }
	  return NOREG;
	}
	case notinreg:{
	  /* source and dest both instore */
	  instore isdest=insalt(dest.answhere);	  
	  int sunit = (size>64)?choose_block_size(dest,al):
	    ((dest.ashwhere.ashsize%64==0)?64:min(al,64));
	  /*int sunit= ((dest.ashwhere.ashsize%64==0)?64: min(al,64));*/
	  int step=sunit>>3;
	  int s=(dest.ashwhere.ashsize+sunit-1)/sunit;
	  bool unalign=0;
	  if(sunit>al) al=sunit;
	  if(al==8 && s>=8 && (aligned(isdest.b,8))){
	    int rtmp = getreg(freeregs.fixed);
	    unalign=1;
	    if(s<=32){
	      for(;s>=8;s -= 8){
		load_store(i_ldq,rtmp,iss.b);
		load_store(i_stq,rtmp,isdest.b);
		iss.b.offset += 8;
		isdest.b.offset += 8;
	      }
	      if(s){
		int rtmp2 = getreg(freeregs.fixed);
		load_store(i_ldq,rtmp,iss.b);
		load_store(i_ldq,rtmp2,isdest.b);
		operate_fmt_immediate(i_zap,rtmp2,unary(s),rtmp2);
		operate_fmt(i_bis,rtmp2,rtmp,rtmp2);
		load_store(i_stq,rtmp2,isdest.b);
	      }
		
	    }
	    else{
	      /* 
		 copy with loop, length in r1, to in2 from in r2 
		 if the data is aligned on 32/64 bit boundaries we can
		 do a fast copy. 
		 the code sequence produced is:

		 foreach complete 8 bytes of data
		   load/store quadword
		 foreach byte remaining
		   read bytes using ldq and zap 
		 */
	      int l=new_label();
	      int r1=getreg(freeregs.fixed | (1<<rtmp));
	      int r2=getreg(freeregs.fixed | (1<<rtmp)|(1<<r1));
	      int rd = getreg(freeregs.fixed|(1<<rtmp)|(1<<r1)|(1<<r2));
	      static baseoff src;
	      static baseoff dst;
	      int numberofquads;	/* number of quadwords in the data */
	      int numberofbytes;	/* number of remaining bytes */
	      load_store(i_lda,r1,iss.b);
	      numberofquads = size>>6;
	      load_store((isdest.adval)?i_lda:i_ldq,rd,isdest.b);
	      isdest.adval=1;
	      dst.base = rd;
	      dst.offset=0;
	      src.base = r1;
	      src.offset=0;	      
	      load_store_immediate(i_ldil,r2,numberofquads);
	      set_label(l);
	      operate_fmt_immediate(i_subq,r2,1,r2);
	      load_store(i_ldq,rtmp,src);
	      load_store(i_stq,rtmp,dst);
	      operate_fmt_immediate(i_addq,r1,8,r1);
	      operate_fmt_immediate(i_addq,rd,8,rd);
	      /*	     
			     dst.offset+=(8*numberofquads);
			     src.offset+=(8*numberofquads);
			     */
	      integer_branch(i_bne,r2,l);
	      /* now only single bytes remain */
	      numberofbytes = (size - (numberofquads<<6))>>3;
	      if(numberofbytes){
		/* we have trailing bytes. */
		load_store(i_ldq,r1,src);
		load_store(i_ldq,r2,dst);
		operate_fmt_immediate(i_zap,r2,unary(numberofbytes),r2);
		operate_fmt(i_bis,r2,r1,r2);
		load_store(i_stq,r2,dst);
	      }
	    }
	    return NOREG;
	  }
	  if(s<=inlineassign){
	    int r=getreg(freeregs.fixed);
	    if(!isdest.adval){
	      int rtmp = getreg(freeregs.fixed);
	      load_store(i_ldq,rtmp,isdest.b);/* fix: was load not i_ldq */
	      isdest.b.base=rtmp;
	      isdest.b.offset=0;
	      isdest.adval=1;		/* added (is this correct?) */
	    }
	    if(s==1){
	      ans newsrc;
	      where newdest;
	      setinsalt(newsrc,iss);
	      setregalt(newdest.answhere,r);
	      newdest.ashwhere.ashsize=size;
	      newdest.ashwhere.ashalign=al;
	      (void)move(newsrc,newdest,freeregs,sgned);
	      setregalt(newsrc,r);
	      setinsalt(newdest.answhere,isdest);
	      newdest.ashwhere.ashsize=size;
	      newdest.ashwhere.ashalign=al;
	      (void)move(newsrc,newdest,freeregs,sgned);
	      return (unalign)?NOREG:r;
	    }
	    else{
	      int er = getreg(freeregs.fixed|(1<<r));
	      int nr=r;
	      if(!address_equal(iss,isdest)){
		for(;s>0;--s){
		  ans newsrc;
		  where newdest;
		  setinsalt(newsrc,iss);
		  setregalt(newdest.answhere,r);
		  newdest.ashwhere.ashsize=sunit;	/* in 64 byte chunks */
		  newdest.ashwhere.ashalign=sunit;
		  /* put value into register r */
		  (void)move(newsrc,newdest,freeregs,sgned); 
		  setregalt(newsrc,r);
		  setinsalt(newdest.answhere,isdest);
		  (void)move(newsrc,newdest,freeregs,sgned);
		  /*load_store(load,nr,iss.b);
		    load_store(store,nr,isdest.b);*/
		  iss.b.offset += step;
		  isdest.b.offset += step;
		  if(nr == r){
		    nr = er;
		  }
		  else{
		    nr = r;
		  }
		}
	      }
	      return NOREG;
	    }
	  }	
	  else{
	    int a = getreg(freeregs.fixed);
	    int	address_reg = getreg(freeregs.fixed);
	    int rtmp = getreg(freeregs.fixed);
	    int l=new_label();
	    int r1=getreg(freeregs.fixed);
	    static baseoff src;
	    static baseoff dst;
	    INT64 loop_count;
	    src.base = address_reg;
	    src.offset = 0;
	    dst.base = rtmp;
	    dst.offset=0;
	    load_store((isdest.adval)?i_lda:i_ldq,rtmp,isdest.b);
	    load_store(i_lda,address_reg,iss.b);
	    loop_count=make_INT64((s&0x80000000)?0xffffffff:0,s);
	    load_store_immediate(i_ldiq,r1,loop_count);	/* loop counter */
	    set_label(l);
	    load_store(load,a,src);
	    operate_fmt_immediate(i_addq,address_reg,step,address_reg);
	    load_store(store,a,dst);
	    operate_fmt_immediate(i_addq,rtmp,step,rtmp);
	    operate_fmt_immediate(i_subq,r1,1,r1);
	    integer_branch(i_bgt,r1,l);
	    return NOREG;
	  }
	}
      }
    }
  }
  return NOREG;
}




