/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PD_CHUNKS_INCLUDED
#define PD_CHUNKS_INCLUDED

#define DATA_SIZE 256


typedef int Bool;

typedef struct chunk_struct
{ struct chunk_struct *next;
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

extern TDF *current_TDF;   	/* the current output stream */

extern Chunk *create_chunk(void);
extern void out_basic_int(unsigned long num, unsigned int bts);
extern void append_TDF(TDF *tdf, Bool free_it);
extern unsigned long bits_in_TDF(TDF *tdf);
extern void out_extendable_int(unsigned long num, unsigned int bts);
extern void out_tdfint32(unsigned long n);
extern void out_tdfbool(Bool b);
extern void out_tdfstring_bytes(char *s, unsigned int k, unsigned int n);
extern void out_tdfident_bytes(char *s);
extern void append_bytestream(TDF *tdf, Bool free_it);
extern void byte_align(void);

#include "errors.h"

/* NEW_STREAM creates a new output stream in ptrtoTDF (ie a non-void TDF *)
   for the extent of make_stream, re-instating the original stream after
   make_stream.
 */

#define NEW_STREAM(ptrtoTDF, make_stream)\
{ TDF *new_hold_;\
	new_hold_ = current_TDF;\
	current_TDF = ptrtoTDF;\
	current_TDF->first = current_TDF->last = create_chunk();\
	make_stream;\
	current_TDF = new_hold_;\
}


/* CONT_STREAM changes the output stream to an existing stream, ptrtoTDF, for
   the extent of make_stream, re-instating the original stream after
   make_stream.
*/

#define CONT_STREAM(ptrtoTDF, make_stream)\
{ TDF *cont_hold_ = current_TDF;\
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
{ TDF *list_hold_ = current_TDF;\
	TDF temp_;\
	temp_.last = temp_.first = create_chunk();\
	temp_.no = 0;\
	current_TDF = &temp_;\
	current_TDF->sort = sort_;\
	x; ASSERT_SORT_OR_EMPTY(sort_);\
	current_TDF = list_hold_;\
	out_basic_int(UL(0), UI(1));\
	out_tdfint32(UL(temp_.no));\
	append_TDF(&temp_, 1);\
}

#define TDF_SLIST(x, sort_)\
{ TDF *slist_hold_ = current_TDF;\
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
	current_TDF->no++;\
}

#define TDF_OPTION(x, sort_)\
{ TDF *opt_hold_ = current_TDF;\
	TDF temp_;\
	temp_.last = temp_.first = create_chunk();\
	temp_.no = 0;\
	current_TDF = &temp_;\
	x; ASSERT_SORT_OR_EMPTY(sort_);\
	current_TDF = opt_hold_;\
	Assert(temp_.no <= 1);\
	out_basic_int(UL(temp_.no), UI(1));\
	if (temp_.no != 0) append_TDF(&temp_, 1);\
}


#define OPTION(x)\
{ x; Assert(current_TDF->no == 0); current_TDF->no = 1; }

#define TOK_APP(num_, sort_, tok_, pars_)\
{ TDF new_;\
	num_; tok_; ASSERT_SORT(s_token);\
	NEW_STREAM(&new_, pars_)\
	out_tdfint32(bits_in_TDF(&new_));\
	append_TDF(&new_, 1);\
	SET_RSORT(sort_);\
}

#define o_token_def(p_result_sort, p_tok_params, p_body)\
{ TDF new_;\
	NEW_STREAM(& new_,\
		   { out_basic_int(UL(1), UI(1));\
		   p_result_sort; ASSERT_SORT(s_sortname);\
		   TDF_LIST(p_tok_params, s_tokformals);\
		   p_body;\
		   }\
		  )\
	out_tdfint32(bits_in_TDF(&new_));\
	append_TDF(&new_, 1);\
	SET_RSORT(s_bitstream);\
}


#endif
