/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef PD_CHUNKS_INCLUDED
#define PD_CHUNKS_INCLUDED

#define DATA_SIZE 256


typedef int Bool;

typedef struct chunk_struct {
	struct chunk_struct *next;
	short int usage;
	unsigned char offst;
	unsigned char aligned;
	unsigned char data[DATA_SIZE];
} Chunk;


typedef struct {
	Chunk *first;
	Chunk *last;
	unsigned int no;
	unsigned int sort;
} TDF;

extern TDF * current_TDF;   	/* the current output stream */

extern Chunk * create_chunk(void);
extern void out_basic_int(unsigned long num, unsigned int bts);
extern void append_TDF(TDF * tdf, Bool free_it);
extern unsigned long bits_in_TDF(TDF *tdf);
extern void out_extendable_int(unsigned long num, unsigned int bts);
extern void out_tdfint32(unsigned long n);
extern void out_tdfbool(Bool b);
extern void out_tdfstring_bytes(char * s, unsigned int k,
								unsigned int n);
extern void out_tdfident_bytes(char *s);
extern void append_bytestream(TDF *tdf, Bool free_it);
extern void byte_align(void);

#include "errors.h"

/* NEW_STREAM creates a new output stream in ptrtoTDF (ie a non-void TDF *)
 *   for the extent of make_stream, re-instating the original stream after
 *   make_stream.
 */

#if FS_TENDRA
#pragma TenDRA begin
#pragma TenDRA variable hiding analysis off
#endif


#define NEW_STREAM(ptrtoTDF, make_stream)\
{ TDF * new_hold_;\
  new_hold_ = current_TDF;\
  current_TDF = ptrtoTDF;\
  current_TDF->first = current_TDF->last = create_chunk();\
  make_stream;\
  current_TDF = new_hold_;\
}


/* CONT_STREAM changes the output stream to an existing stream, ptrtoTDF, for
 *   the extent of make_stream, re-instating the original stream after
 *   make_stream.
 */

#define CONT_STREAM(ptrtoTDF, make_stream)\
{ TDF * cont_hold_ = current_TDF;\
  current_TDF = ptrtoTDF;\
  make_stream;\
  current_TDF = cont_hold_;\
}


#define TDF_COND(code_, sort_, exp_, arg1, arg2)\
{ TDF new_;\
  code_; exp_; ASSERT_SORT(s_exp);\
  NEW_STREAM(&new_, arg1; ASSERT_SORT(sort_);)\
  out_tdfint32(bits_in_TDF(&new_));\
  append_TDF(&new_,1);\
  NEW_STREAM(&new_, arg2; ASSERT_SORT(sort_);)\
  out_tdfint32(bits_in_TDF(&new_));\
  append_TDF(&new_,1);\
  SET_RSORT(sort_);\
}

#define TDF_LIST(x, sort_)\
{ TDF * list_hold_ = current_TDF;\
  TDF temp_;\
  temp_.last = temp_.first = create_chunk();\
  temp_.no = 0;\
  current_TDF = &temp_;\
  current_TDF->sort = sort_;\
  x; ASSERT_SORT_OR_EMPTY(sort_);\
  current_TDF = list_hold_;\
  out_basic_int(UL(0),UI(1));\
  out_tdfint32(UL(temp_.no));\
  append_TDF(&temp_, 1);\
}

#define TDF_SLIST(x, sort_)\
{ TDF * slist_hold_ = current_TDF;\
  TDF temp_;\
  temp_.last = temp_.first = create_chunk();\
  temp_.no = 0;\
  current_TDF = &temp_;\
  current_TDF->sort = sort_;\
  x; ASSERT_SORT_OR_EMPTY(sort_);\
  current_TDF = slist_hold_;\
  out_tdfint32(UL(temp_.no));\
  append_TDF(&temp_, 1);\
}

#define LIST_ELEM(x)\
{ unsigned int sort_ = current_TDF->sort;\
  x; ASSERT_SORT(sort_);\
  current_TDF->no ++;\
 }

#define TDF_OPTION(x, sort_)\
{ TDF * opt_hold_ = current_TDF;\
  TDF temp_;\
  temp_.last = temp_.first = create_chunk();\
  temp_.no = 0;\
  current_TDF = &temp_;\
  x; ASSERT_SORT_OR_EMPTY(sort_);\
  current_TDF = opt_hold_;\
  Assert(temp_.no<=1);\
  out_basic_int(UL(temp_.no),UI(1));\
  if (temp_.no != 0) append_TDF(&temp_,1);\
}


#define OPTION(x)\
{ x; Assert(current_TDF->no==0); current_TDF->no = 1; }

#define TOK_APP(num_, sort_, tok_, pars_)\
{ TDF new_;\
  num_; tok_; ASSERT_SORT(s_token);\
  NEW_STREAM(&new_, pars_)\
  out_tdfint32(bits_in_TDF(&new_));\
  append_TDF(&new_,1);\
  SET_RSORT(sort_);\
}

#define o_token_def(p_result_sort, p_tok_params, p_body)\
{ TDF new_;\
  NEW_STREAM(& new_,\
	{ out_basic_int(UL(1),UI(1));\
	  p_result_sort; ASSERT_SORT(s_sortname);\
  	  TDF_LIST(p_tok_params, s_tokformals);\
  	  p_body;\
  	}\
 )\
  out_tdfint32(bits_in_TDF(&new_));\
  append_TDF(&new_,1);\
  SET_RSORT(s_bitstream);\
}

#if FS_TENDRA
#pragma TenDRA end
#endif


#endif
