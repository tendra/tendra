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


#ifndef DIAG_INCLUDED
#define DIAG_INCLUDED


/*
    TDF DIAGNOSTICS ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    diagnostic information.
*/

#if TDF_OUTPUT
extern void enc_diag_id PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void enc_diag_init PROTO_S ( ( CONST char *, ulong, TYPE ) ) ;
extern void enc_diag_token PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern BITSTREAM *enc_diag_name PROTO_S ( ( BITSTREAM *, IDENTIFIER, int ) ) ;
extern BITSTREAM *enc_diag_local PROTO_S ( ( BITSTREAM *, IDENTIFIER, BITSTREAM * ) ) ;
extern BITSTREAM *enc_diag_params PROTO_S ( ( BITSTREAM *, LIST ( IDENTIFIER ), BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_diag_start PROTO_S ( ( BITSTREAM * ) ) ;
extern BITSTREAM *enc_diag_begin PROTO_S ( ( BITSTREAM ** ) ) ;
extern BITSTREAM *enc_diag_stmt PROTO_S ( ( BITSTREAM *, EXP, int ) ) ;
extern BITSTREAM *enc_diag_end PROTO_S ( ( BITSTREAM *, BITSTREAM *, EXP, int ) ) ;
extern BITSTREAM *enc_diag_block PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_diag_ctype PROTO_S ( ( BITSTREAM *, CLASS_TYPE ) ) ;
extern BITSTREAM *enc_diag_type PROTO_S ( ( BITSTREAM *, TYPE, int ) ) ;
extern int enc_diag_pending PROTO_S ( ( void ) ) ;
extern int is_diag_stmt PROTO_S ( ( EXP ) ) ;
#endif


#endif
