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


#ifndef INIT_INCLUDED
#define INIT_INCLUDED


/*
    TDF INITIALISATION ENCODING ROUTINES

    The routines in this module are concerned with the encoding of
    initialisation expressions.
*/

#if TDF_OUTPUT
extern BITSTREAM *enc_init_tag PROTO_S ( ( BITSTREAM *, ulong, OFFSET, int, TYPE, EXP, EXP, int ) ) ;
extern BITSTREAM *enc_init_global PROTO_S ( ( BITSTREAM *, EXP, EXP, ulong, TYPE ) ) ;
extern BITSTREAM *enc_init_local PROTO_S ( ( BITSTREAM *, EXP, EXP, ulong, TYPE, EXP ) ) ;
extern BITSTREAM *enc_assign_local PROTO_S ( ( BITSTREAM *, EXP, EXP, ulong, TYPE, EXP ) ) ;
extern BITSTREAM *enc_init_array PROTO_S ( ( BITSTREAM *, EXP, NAT, TYPE ) ) ;
extern BITSTREAM *enc_init_class PROTO_S ( ( BITSTREAM *, EXP, CLASS_TYPE ) ) ;
extern BITSTREAM *enc_term_local PROTO_S ( ( BITSTREAM *, ulong, OFFSET, int, TYPE, EXP, int ) ) ;
extern BITSTREAM *enc_term_global PROTO_S ( ( BITSTREAM *, ulong, TYPE, EXP, ulong ) ) ;
extern BITSTREAM *enc_flag_test PROTO_S ( ( BITSTREAM *, ulong, unsigned, int, NTEST ) ) ;
extern BITSTREAM *enc_destr_count PROTO_S ( ( BITSTREAM *, TYPE, int ) ) ;
extern BITSTREAM *enc_term_type PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_dealloc PROTO_S ( ( BITSTREAM *, EXP, ulong ) ) ;
extern BITSTREAM *enc_alloc PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *make_term_local PROTO_S ( ( BITSTREAM *, TYPE, EXP *, int ) ) ;
extern void make_term_global PROTO_S ( ( TYPE, EXP * ) ) ;
extern EXP make_dummy_init PROTO_S ( ( TYPE ) ) ;
extern int is_init_complex PROTO_S ( ( EXP ) ) ;
extern int in_dynamic_init ;
extern int in_static_init ;
#endif


#endif
