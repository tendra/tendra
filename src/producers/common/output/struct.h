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


#ifndef STRUCT_INCLUDED
#define STRUCT_INCLUDED


/*
    TDF CLASS ENCODING ROUTINES

    The routines in this module are concerned with the mappings of classes
    to TDF SHAPEs.
*/

#if TDF_OUTPUT
extern ulong compile_class PROTO_S ( ( CLASS_TYPE ) ) ;
extern BITSTREAM *enc_null_class PROTO_S ( ( BITSTREAM *, CLASS_TYPE ) ) ;
extern BITSTREAM *enc_ctor_init PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_member PROTO_S ( ( BITSTREAM *, IDENTIFIER ) ) ;
extern BITSTREAM *enc_al_ctype PROTO_S ( ( BITSTREAM *, CLASS_TYPE ) ) ;
extern BITSTREAM *enc_ctype PROTO_S ( ( BITSTREAM *, CLASS_TYPE ) ) ;
extern BITSTREAM *enc_base PROTO_S ( ( BITSTREAM *, GRAPH, int ) ) ;
extern BITSTREAM *enc_add_base PROTO_S ( ( BITSTREAM *, OFFSET, OFFSET ) ) ;
extern BITSTREAM *enc_end_base PROTO_S ( ( BITSTREAM *, OFFSET, OFFSET ) ) ;
extern BITSTREAM *enc_rtti_type PROTO_S ( ( BITSTREAM *, TYPE, int ) ) ;
extern BITSTREAM *enc_rtti_exp PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_dyn_cast PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_vtable_shape PROTO_S ( ( BITSTREAM *, ulong ) ) ;
extern ulong virtual_no PROTO_S ( ( IDENTIFIER, VIRTUAL ) ) ;
extern void define_vtable PROTO_S ( ( CLASS_TYPE, int, int ) ) ;
extern void compile_incompl PROTO_S ( ( void ) ) ;
extern IDENTIFIER dummy_type_name ;
extern OFFSET off_size_t ;
extern ulong size_dummy_vtab ;
extern TYPE ptr_dummy_class ;
extern TYPE ptr_dummy_vtab ;
extern TYPE dummy_class ;
extern TYPE dummy_count ;
extern TYPE dummy_vtab ;
extern TYPE dummy_func ;
#endif


#endif
