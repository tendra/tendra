/*
    		 Crown Copyright (c) 1997, 1998
    
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


#ifndef COMPILE_INCLUDED
#define COMPILE_INCLUDED


/*
    MAIN COMPILATION ROUTINES

    The routines in this module are concerned with the main compilation
    actions of transforming declarations and definitions into TDF.
*/

extern void compile_variable PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void compile_function PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void compile_token PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void compile_type PROTO_S ( ( IDENTIFIER ) ) ;
extern void compile_virtual PROTO_S ( ( CLASS_TYPE, int ) ) ;
extern void compile_asm PROTO_S ( ( EXP ) ) ;
extern void compile_comment PROTO_S ( ( string, unsigned long ) ) ;
extern void compile_preserve PROTO_S ( ( IDENTIFIER ) ) ;
extern void compile_pending PROTO_S ( ( void ) ) ;
extern void compile_weak PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern void update_tag PROTO_S ( ( IDENTIFIER, int ) ) ;
extern LIST ( IDENTIFIER ) pending_funcs ;

#if TDF_OUTPUT
extern void enc_tagdec PROTO_S ( ( IDENTIFIER, ulong, TYPE, int ) ) ;
extern BITSTREAM *enc_tagdec_start PROTO_S ( ( IDENTIFIER, ulong, TYPE, int ) ) ;
extern void enc_tagdec_end PROTO_S ( ( BITSTREAM * ) ) ;
extern BITSTREAM *enc_tagdef_start PROTO_S ( ( IDENTIFIER, ulong, TYPE, int ) ) ;
extern void enc_tagdef_end PROTO_S ( ( BITSTREAM * ) ) ;
extern ulong make_tagdef PROTO_S ( ( IDENTIFIER, TYPE, EXP, EXP, int ) ) ;
extern BITSTREAM *enc_variable PROTO_S ( ( BITSTREAM *, IDENTIFIER, int, EXP *, EXP ) ) ;
extern BITSTREAM *enc_access PROTO_S ( ( BITSTREAM *, DECL_SPEC ) ) ;
extern BITSTREAM *enc_tokdef_start PROTO_S ( ( ulong, CONST char *, ulong *, int ) ) ;
extern void enc_tokdef_end PROTO_S ( ( ulong, BITSTREAM * ) ) ;
extern void enc_tokdec PROTO_S ( ( ulong, CONST char * ) ) ;
extern int enc_tokdef PROTO_S ( ( IDENTIFIER, int ) ) ;
extern void enc_dynamic_init PROTO_S ( ( void ) ) ;
extern DECL_SPEC crt_func_access ;
#endif


#endif
