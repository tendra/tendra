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


#ifndef EXP_INCLUDED
#define EXP_INCLUDED


/*
    TDF EXP ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    EXPs and related sorts.
*/

#if TDF_OUTPUT
extern BITSTREAM *enc_exp PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_addr_exp PROTO_S ( ( BITSTREAM *, TYPE, EXP ) ) ;
extern BITSTREAM *enc_cont_exp PROTO_S ( ( BITSTREAM *, TYPE, EXP ) ) ;
extern BITSTREAM *enc_null_exp PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_make_int PROTO_S ( ( BITSTREAM *, TYPE, int ) ) ;
extern BITSTREAM *enc_make_snat PROTO_S ( ( BITSTREAM *, int ) ) ;
extern BITSTREAM *enc_condition PROTO_S ( ( BITSTREAM *, EXP, ulong, ulong ) ) ;
extern BITSTREAM *enc_assign_op PROTO_S ( ( BITSTREAM *, TYPE, int * ) ) ;
extern BITSTREAM *enc_cont_op PROTO_S ( ( BITSTREAM *, TYPE, int * ) ) ;
extern BITSTREAM *enc_ntest PROTO_S ( ( BITSTREAM *, NTEST ) ) ;
extern BITSTREAM *enc_exp_list PROTO_S ( ( BITSTREAM *, LIST ( EXP ) ) ) ;
extern BITSTREAM *enc_dummy_exp PROTO_S ( ( BITSTREAM *, TYPE, ulong, OFFSET, int, int ) ) ;
extern BITSTREAM *enc_compare PROTO_S ( ( BITSTREAM *, EXP, EXP, NTEST, ulong, ulong ) ) ;
extern BITSTREAM *enc_error_treatment PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern EXP simplify_cond PROTO_S ( ( EXP, int * ) ) ;
#endif


#endif
