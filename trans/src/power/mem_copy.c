/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <main/print.h>

#include "inst_fmt.h"
#include "reg.h"
#include "mem_copy.h"
#include "labels.h"
#include "getregs.h"


#define MAX_BYTE_COPY 80

void static_memory_copy(int reg_from, int reg_to, int number_of_bytes)
{
  baseoff from;
  baseoff to;
  int bytes;
  int words;
  int i;
  asm_comment("memory copy of %d bytes from R_%d to R_%d",number_of_bytes,reg_from,reg_to);
  assert(number_of_bytes >=0);
  if(reg_from == reg_to || number_of_bytes==0 )
  {
    /* Nothing to do */
    return;
  }
  words = number_of_bytes/4;
  bytes = number_of_bytes - (words *4);
  
  from.base = reg_from;
  from.offset = 0;
  to.base = reg_to;
  to.offset = 0;  
  
  if(number_of_bytes <= MAX_BYTE_COPY)
  {
    /* copy the words */
    for(i=0;i<words;i++)
    {
      ld_ro_ins(i_l,from,R_TMP0);
      st_ro_ins(i_st,R_TMP0,to);
      from.offset += 4;
      to.offset += 4;
    }
    /* copy the bytes */
    for(i=0;i<bytes;i++)
    {
      ld_ro_ins(i_lbz,from,R_TMP0);
      st_ro_ins(i_stb,R_TMP0,to);
      from.offset +=1;
      to.offset +=1;
    }
  }
  else
  {
    if(words >0)
    {
      /* dynamically copy */
      int loop = new_label();
      from.base = reg_from;
      from.offset = 4;
      to.base = reg_to;
      to.offset = 4;
      rir_ins(i_a,reg_from,-4,reg_from);
      rir_ins(i_a,reg_to,-4,reg_to);
      ld_const_ins(words,R_TMP0);
      mt_ins(i_mtctr,R_TMP0);
      set_label(loop);
      ld_ro_ins(i_lu,from,R_TMP0);
      st_ro_ins(i_stu,R_TMP0,to);
      uncond_ins(i_bdn,loop);
      rir_ins(i_a,reg_from,4,reg_from);
      rir_ins(i_a,reg_to,4,reg_to);
    }
    from.base = reg_from;
    from.offset = 0;
    to.base = reg_to;
    to.offset =0;
    for(i=0;i<bytes;i++)
    {
      ld_ro_ins(i_lbz,from,R_TMP0);
      st_ro_ins(i_stb,R_TMP0,to);
      from.offset +=1;
      to.offset +=1;
    }
    
    /* restore the pointers to their initial values */
    if(words>0)
    {
      rir_ins(i_a,reg_from,-4 * words,reg_from);
      rir_ins(i_a,reg_to,-4 * words,reg_to);
    }
  }
}
void reverse_static_memory_copy(int reg_from, int reg_to, int number_of_bytes)
{
  int bytes;
  int words;
  int r;
  baseoff from;
  baseoff to;
  int offset;
  
  from.base = reg_from;
  to.base = reg_to;
  
  asm_comment("reverse static memory copy");
  
  words = number_of_bytes/4;
  bytes = number_of_bytes - (4*words);

  offset = number_of_bytes;
  for(r = 0;r<bytes;r++)
  {
    offset -=1;
    from.offset =offset;
    to.offset = offset;
    ld_ro_ins(i_lbz,from,R_TMP0);
    st_ro_ins(i_stb,R_TMP0,to);
  }
  for(r = 0;r<words;r++)
  {
    offset -=4;
    from.offset =offset;
    to.offset = offset;
    ld_ro_ins(i_l,from,R_TMP0);
    st_ro_ins(i_st,R_TMP0,to);
  }
  assert(offset ==0);
}

void dynamic_word_memory_copy(int reg_from, int reg_to, int reg_size)
{
  /* reg_size contains the number of bytes to copy */
  /* however in this case we do it word at a time */
  int zero = new_label();
  int loop = new_label();
  int creg = next_creg();
  baseoff from;
  baseoff to;
  asm_comment("dynamic copy (word at a time) from R_%d ro R_%d using no of bytes in R_%d",reg_from,reg_to,reg_size);
  cmp_ri_ins(i_cmp,reg_size,0,creg);
  bc_ins(i_beq,creg,zero,UNLIKELY_TO_JUMP);
  from.base = reg_from;
  from.offset =4;
  to.base = reg_to;
  to.offset =4;
  
  rir_ins(i_a,reg_from,-4,reg_from);
  rir_ins(i_a,reg_to,-4,reg_to);
  
  rir_ins(i_sr,reg_size,2,R_TMP0);
  mt_ins(i_mtctr,R_TMP0);
  
  set_label(loop);
  ld_ro_ins(i_lu,from,R_TMP0);
  st_ro_ins(i_stu,R_TMP0,to);
  uncond_ins(i_bdn,loop);
  
  rir_ins(i_a,reg_from,4,reg_from);
  rir_ins(i_a,reg_to,4,reg_to);
  set_label(zero);

  /* reg_from goes to reg_from + reg_size */
  /* reg_to goes to reg_to + reg_size */
}
void reverse_dynamic_word_memory_copy(int reg_from, int reg_to, int reg_size)
{
  int zero = new_label();
  int loop = new_label();
  int creg = next_creg();
  baseoff from;
  baseoff to;
  asm_comment("reverse dynamic copy (word at a time) from R_%d ro R_%d using no of bytes in R_%d",reg_from,reg_to,reg_size);
  cmp_ri_ins(i_cmp,reg_size,0,creg);
  bc_ins(i_beq,creg,zero,UNLIKELY_TO_JUMP);
  from.base = reg_from;
  from.offset = -4;
  to.base = reg_to;
  to.offset = -4;
  rrr_ins(i_a,reg_from,reg_size,reg_from);
  rrr_ins(i_a,reg_to,reg_size,reg_to);
  rir_ins(i_sr,reg_size,2,R_TMP0);
  mt_ins(i_mtctr,R_TMP0);
  
  set_label(loop);
  ld_ro_ins(i_lu,from,R_TMP0);
  st_ro_ins(i_stu,R_TMP0,to);
  uncond_ins(i_bdn,loop);
  
  set_label(zero);

  /* reg_from and reg_to are unchanged */
}
