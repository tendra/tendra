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


#ifndef DIAG2_INCLUDED
#define DIAG2_INCLUDED


/*
    TDF DIAGNOSTICS (NEW FORMAT) ENCODING ROUTINES

    The routines in this module are concerned with the encoding of TDF
    new format diagnostic information.
*/

#if ( TDF_OUTPUT && TDF_NEW_DIAG )
extern void enc_dg_id PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void enc_dg_token PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern BITSTREAM *enc_dg_local PROTO_S ( ( BITSTREAM *, IDENTIFIER, BITSTREAM * ) ) ;
extern BITSTREAM *enc_dg_params PROTO_S ( ( BITSTREAM *, LIST ( IDENTIFIER ), BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_dg_name PROTO_S ( ( BITSTREAM *, IDENTIFIER, TYPE ) ) ;
extern BITSTREAM *enc_dg_type PROTO_S ( ( BITSTREAM *, TYPE, int ) ) ;
extern BITSTREAM *enc_dg_compilation PROTO_S ( ( BITSTREAM * ) ) ;
extern BITSTREAM *enc_dg_stmt PROTO_S ( ( BITSTREAM *, EXP, int ) ) ;
extern ulong enc_dg_basetype PROTO_S ( ( TYPE, int ) ) ;
extern int enc_dg_pending PROTO_S ( ( void ) ) ;
#endif


#endif
