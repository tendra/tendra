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


#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED


/*
    TDF SHAPE ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    SHAPEs and related sorts.
*/

#if TDF_OUTPUT
extern BITSTREAM *enc_add_ptr PROTO_S ( ( BITSTREAM *, EXP, ulong, OFFSET, int ) ) ;
extern BITSTREAM *enc_alignment PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_arith PROTO_S ( ( BITSTREAM *, TYPE, int ) ) ;
extern BITSTREAM *enc_bfvar PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_bool PROTO_S ( ( BITSTREAM *, int ) ) ;
extern BITSTREAM *enc_char PROTO_S ( ( BITSTREAM *, STRING, TYPE, TYPE ) ) ;
extern BITSTREAM *enc_extra_offset PROTO_S ( ( BITSTREAM *, TYPE, OFFSET, int ) ) ;
extern BITSTREAM *enc_float PROTO_S ( ( BITSTREAM *, FLOAT, TYPE ) ) ;
extern BITSTREAM *enc_float_int PROTO_S ( ( BITSTREAM *, int, TYPE ) ) ;
extern BITSTREAM *enc_flvar PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_int_lit PROTO_S ( ( BITSTREAM *, NAT, TYPE, unsigned ) ) ;
extern BITSTREAM *enc_nat PROTO_S ( ( BITSTREAM *, NAT, int ) ) ;
extern BITSTREAM *enc_offset PROTO_S ( ( BITSTREAM *, OFFSET ) ) ;
extern BITSTREAM *enc_shape PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_shape_offset PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_snat PROTO_S ( ( BITSTREAM *, NAT, int, int ) ) ;
extern BITSTREAM *enc_string PROTO_S ( ( BITSTREAM *, STRING, TYPE ) ) ;
extern BITSTREAM *enc_strlit PROTO_S ( ( BITSTREAM *, STRING ) ) ;
extern BITSTREAM *enc_variety PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern int eq_type_rep PROTO_S ( ( TYPE, TYPE, int ) ) ;
extern int is_tokenised_class PROTO_S ( ( TYPE ) ) ;
#endif


#endif
