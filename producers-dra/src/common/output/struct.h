/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STRUCT_INCLUDED
#define STRUCT_INCLUDED


/*
    TDF CLASS ENCODING ROUTINES

    The routines in this module are concerned with the mappings of classes
    to TDF SHAPEs.
*/

#if TDF_OUTPUT
extern ulong compile_class(CLASS_TYPE);
extern BITSTREAM *enc_null_class(BITSTREAM *, CLASS_TYPE);
extern BITSTREAM *enc_ctor_init(BITSTREAM *, EXP);
extern BITSTREAM *enc_member(BITSTREAM *, IDENTIFIER);
extern BITSTREAM *enc_al_ctype(BITSTREAM *, CLASS_TYPE);
extern BITSTREAM *enc_ctype(BITSTREAM *, CLASS_TYPE);
extern BITSTREAM *enc_base(BITSTREAM *, GRAPH, int);
extern BITSTREAM *enc_add_base(BITSTREAM *, OFFSET, OFFSET);
extern BITSTREAM *enc_end_base(BITSTREAM *, OFFSET, OFFSET);
extern BITSTREAM *enc_rtti_type(BITSTREAM *, TYPE, int);
extern BITSTREAM *enc_rtti_exp(BITSTREAM *, EXP);
extern BITSTREAM *enc_dyn_cast(BITSTREAM *, EXP);
extern BITSTREAM *enc_vtable_shape(BITSTREAM *, ulong);
extern ulong virtual_no(IDENTIFIER, VIRTUAL);
extern void define_vtable(CLASS_TYPE, int, int);
extern void compile_incompl(void);
extern IDENTIFIER dummy_type_name;
extern OFFSET off_size_t;
extern ulong size_dummy_vtab;
extern TYPE ptr_dummy_class;
extern TYPE ptr_dummy_vtab;
extern TYPE dummy_class;
extern TYPE dummy_count;
extern TYPE dummy_vtab;
extern TYPE dummy_func;
#endif


#endif
