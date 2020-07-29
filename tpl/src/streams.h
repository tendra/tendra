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


/*
 * Note that the initial Chunks of a stream may not be completely filled; ie
 * usage can less than DATA_SIZE (and offst need not be 0) for any Chunk in the
 * chain.
 * 
 * I have not provided any routines for compressing the Chunks into a contiguous
 * area of mainstore; however the routine make_tdf_file (units.c) will output a
 * TDF stream to a file. If the contents of the TDF stream is a CAPSULE then this
 * would be a .j file.
 */

typedef struct chunk_struct
{
	struct chunk_struct *next; 	/* This should be NULL when this chunk is TDF->last, and vice versa. */

	short int usage; 			/* Next char in .data to write to. It is <= DATA_SIZE. A new chunk will
								  be allocated when trying to write when .usage == DATA_SIZE. */

	unsigned char offst;		/* Next bit to write to within .usage'th char in .data, from the most
								   significan end of the char. */

	unsigned char aligned;		/* !0 means .data must start on a byte-boundary in final CAPSULE. */
	unsigned char data[DATA_SIZE];
} Chunk;


/* struct TDF represents a bitstream of TDF encodings. It is
   implemented as a linked list of struct chunk_struct. */
typedef struct {
	Chunk *first; /* First chunk of bitstream */
	Chunk *last;  /* The last chunk in the list, and where the next bits of output will go.
					 .last->next should be NULL. */

	/* The no and sort fields are used to provide the SORT checking mechanism. */
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


/*
 * It is usually necessary to have several streams of TDF being
 * produced at the same time. For example, tagdef and tagdec UNITs are
 * often conveniently constructed in parallel; for example, there
 * would usually be at least one for each UNIT being produced in the
 * CAPSULE being compiled. We simply change the stream in
 * current_TDF. For some constructions, the macros given below are
 * very convenient - in any case the same pattern should be used.
 *
 * To create a new stream of output in a variable of type TDF, use the
 * macro NEW_STREAM:
 */

#define NEW_STREAM(ptrtoTDF, make_stream) \
{ \
	TDF *new_hold_; \
	new_hold_ = current_TDF; \
	current_TDF = ptrtoTDF; \
	current_TDF->first = current_TDF->last = create_chunk(); \
	make_stream; \
	current_TDF = new_hold_; \
}

/*
 * Here ptrtoTDF is some TDF* where the new stream is to be produced and
 * make_stream is code to produce the bits of the stream. NEW_STREAM will park
 * the current stream while the new stream is being produced, re-instating it
 * after it is finished. For example:
 *
 * TDF new_stream;
 * NEW_STREAM( &new_stream, o_make_top)
 *
 * will produce a stream containing make_top in new_stream, leaving the
 * current stream unchanged. To add more to new_stream later, one would
 * use CONT_STREAM:
 */

#define CONT_STREAM(ptrtoTDF, make_stream) \
{ \
	TDF *cont_hold_ = current_TDF; \
	current_TDF = ptrtoTDF; \
	make_stream; \
	current_TDF = cont_hold_; \
}

/*
 * Notice that NEW_STREAM(x,y) is just the same as:
 *
 * CONT_STREAM(x,
 *             current_TDF->first = current_TDF->last = create_chunk(); y)
 *
 * Having constructed a new stream, it can be appended onto the current stream
 * using the procedure append_TDF, defined in streams.c.
 */



/*
 * Many of the TDF constructors have LIST parameters with special encoding
 * giving the number of elements in the LIST. The o_ macros take account of
 * these by invoking the macro TDF_LIST. With the use of the LIST_ELEM macro,
 * the number of elements are counted as they are output and used to provide
 * the prefix of the encoding of the LIST. For example, a sequence S1; S2; S3
 * would be encoded:
 *
 * o_sequence( {LIST_ELEM(S1); LIST_ELEM(S2)}, S3)
 *
 * The SORT checking is not foolproof here; in a LIST there must be no output
 * other than that in the parameter of a LIST_ELEM. In the above example, the
 * SORTS of S1 and S2 will be checked to see that they are EXPs, but there is
 * no check to see that nothing has been output between LIST_ELEM(S1) and
 * LIST_ELEM(S2).
 *
 * The mechanism for this is quite simple. The macro call of TDF_LIST in
 * o_sequence (for example) creates a new stream into which the list elements
 * will be output; each LIST_ELEM will increment the no field of the stream;
 * the final number will be output to the original stream and the new stream
 * appended to it.
 */

/* x will contain only LIST_ELEM(...)s */
#define TDF_LIST(x, sort_) \
{ \
	TDF *list_hold_ = current_TDF; \
	TDF temp_; \
	temp_.last = temp_.first = create_chunk(); \
	temp_.no = 0; \
	current_TDF = &temp_; \
	current_TDF->sort = sort_; \
	x; ASSERT_SORT_OR_EMPTY(sort_); \
	current_TDF = list_hold_; \
	out_basic_int(UL(0), UI(1)); \
	out_tdfint32(UL(temp_.no)); \
	append_TDF(&temp_, 1); \
}

#define TDF_SLIST(x, sort_) \
{ \
	TDF *slist_hold_ = current_TDF;				\
	TDF temp_; \
	temp_.last = temp_.first = create_chunk(); \
	temp_.no = 0; \
	current_TDF = &temp_; \
	current_TDF->sort = sort_; \
	x; ASSERT_SORT_OR_EMPTY(sort_); \
	current_TDF = slist_hold_; \
	out_tdfint32(UL(temp_.no)); \
	append_TDF(&temp_, 1); \
}

#define LIST_ELEM(x) \
{ \
	unsigned int sort_ = current_TDF->sort; \
	x; ASSERT_SORT(sort_); \
	current_TDF->no++; \
}

/*
 * A similar mechanism is used for OPTIONal parameters. This time the o_ macro
 * invokes TDF_OPTION and the actual parameter has the choice of either
 * outputing nothing or something of the correct SORT using the OPTION macro.
 * For example, a procedure application has an optional var_param parameter;
 * with a empty option we have:
 *
 * o_apply_proc(Shape, Proc, Pars, {})
 *
 * while with a real var_param V:
 *
 * o_apply_proc(Shape, Proc, Pars, OPTION(V))
 */

/* x will have no output or one OPTION(...) */
#define TDF_OPTION(x, sort_) \
{ \
	TDF *opt_hold_ = current_TDF; \
	TDF temp_; \
	temp_.last = temp_.first = create_chunk(); \
	temp_.no = 0; \
	current_TDF = &temp_; \
	x; ASSERT_SORT_OR_EMPTY(sort_); \
	current_TDF = opt_hold_; \
	Assert(temp_.no <= 1); \
	out_basic_int(UL(temp_.no), UI(1)); \
	if (temp_.no != 0) append_TDF(&temp_, 1); \
}


#define OPTION(x) \
{ \
	x; \
	Assert(current_TDF->no == 0); \
	current_TDF->no = 1; \
}



/*
 * Most of the constructors which use BITSTREAMs are handled transparently by
 * their o_ macros. For example, a shape_cond would be encoded:
 *
 * o_shape_cond(C, S1, S2)
 *
 * where S1 and S2 simply output SHAPEs normally. The _cond constructors all
 * invoke the macro TDF_COND which provides new streams for both E1 and E2.
 * The number of bits in each is computed using:
 *
 * unsigned long bits_in_TDF(TDF *tdf);
 *
 * and give the prefix TDFINT for the bitstreams required by the _cond
 * construction.
 */

#define TDF_COND(code_, sort_, exp_, arg1, arg2) \
{ TDF new_; \
	code_; exp_; ASSERT_SORT(s_exp); \
	NEW_STREAM(&new_, arg1; ASSERT_SORT(sort_);) \
	out_tdfint32(bits_in_TDF(&new_)); \
	append_TDF(&new_,1); \
	NEW_STREAM(&new_, arg2; ASSERT_SORT(sort_);) \
	out_tdfint32(bits_in_TDF(&new_)); \
	append_TDF(&new_,1); \
	SET_RSORT(sort_); \
}

/*
 * Similarly all the _apply_token constructors work in the same fashion, this
 * time using the TOK_APP macro. Here, of course, there is no SORT check
 * possible on the parameter applied to the token. An EXP token, T,  with two
 * parameters, P1 and P2, is applied using: o_exp_apply_token(T, {P1; P2}) ie
 * the token parameters are simply output sequentially.
 */

#define TOK_APP(num_, sort_, tok_, pars_) \
{ TDF new_; \
	num_; tok_; ASSERT_SORT(s_token); \
	NEW_STREAM(&new_, pars_) \
	out_tdfint32(bits_in_TDF(&new_)); \
	append_TDF(&new_, 1); \
	SET_RSORT(sort_); \
}

/*
 * The other BITSTREAMs are all derived from token_definition which is rather
 * peculiar in that the SORT of the body parameter depends on its result_sort
 * parameter. The o_token_def macro is to be found in here rather than in
 * encodings.h and its SORT is described as s_bitstream rather than
 * s_token_defn as one might expect. Otherwise, it can used in the same way as
 * the other o_ macros. Note that the SORT of the body parameter is not
 * checked to be consistent with its result_sort parameter.
*/

#define o_token_def(p_result_sort, p_tok_params, p_body) \
{ TDF new_; \
	NEW_STREAM(& new_, \
		   { out_basic_int(UL(1), UI(1)); \
		   p_result_sort; ASSERT_SORT(s_sortname); \
		   TDF_LIST(p_tok_params, s_tokformals); \
		   p_body; \
		   } \
		  ) \
	out_tdfint32(bits_in_TDF(&new_)); \
	append_TDF(&new_, 1); \
	SET_RSORT(s_bitstream); \
}


#endif
