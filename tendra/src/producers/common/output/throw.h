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


#ifndef THROW_INCLUDED
#define THROW_INCLUDED


/*
    TDF EXCEPTION HANDLING ENCODING ROUTINES

    The routines in this module are concerned with the encoding of
    exception handling as TDF expressions.
*/

#if TDF_OUTPUT
extern BITSTREAM *enc_try PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_throw PROTO_S ( ( BITSTREAM *, EXP, EXP, EXP ) ) ;
extern BITSTREAM *enc_rethrow PROTO_S ( ( BITSTREAM * ) ) ;
extern BITSTREAM *enc_thrown PROTO_S ( ( BITSTREAM *, TYPE ) ) ;
extern BITSTREAM *enc_try_func PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_catch_func PROTO_S ( ( BITSTREAM *, LIST ( TYPE ), EXP ) ) ;
extern BITSTREAM *enc_destr_func PROTO_S ( ( BITSTREAM *, EXP ) ) ;
extern BITSTREAM *enc_try_start PROTO_S ( ( BITSTREAM *, ulong *, unsigned ) ) ;
extern BITSTREAM *enc_try_end PROTO_S ( ( BITSTREAM *, ulong ) ) ;
extern int in_exception_spec ;
#endif


#endif
