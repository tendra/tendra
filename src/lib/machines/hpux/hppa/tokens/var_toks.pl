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
        /* ********************************************* */
        /*                                               */
        /*    Var Param Token Definitions for hp_pa.     */
        /*    Needs to be linked with the ANSI library   */
        /*    specific to platform.                      */
        /*                                               */
        /* ********************************************* */



Tokdec ~va_list : [] SHAPE;
Tokdec ~__va_start : [EXP] EXP;
Tokdec ~va_arg : [EXP, SHAPE] EXP ; 
Tokdec ~va_end : [EXP] EXP;

Tokdec ~next_caller_offset : [EXP, SHAPE, SHAPE] EXP;
Tokdec ~next_callee_offset : [EXP, SHAPE, SHAPE] EXP;

Tokdec ansi.stdarg.va_list : [] SHAPE;
Tokdec ansi.stdarg.__va_start : [EXP] EXP;
Tokdec ansi.stdarg.va_arg : [EXP, SHAPE] EXP;
Tokdec ansi.stdarg.va_end : [EXP] EXP;



	/* TOKENS FOR TRADITIONAL PROCEDURES */

Tokdef ~va_list = [] SHAPE  ansi.stdarg.va_list;

Tokdef ~__va_start = [i:EXP] EXP
    ansi.stdarg.__va_start [i];

Tokdef ~va_arg = [l:EXP, s:SHAPE] EXP  
    ansi.stdarg.va_arg [l, s];

Tokdef ~va_end = [l:EXP] EXP
    ansi.stdarg.va_end [l];



	/* TOKENS FOR GENERAL PROCEDURES */

/*  These tokens are given no definitions here since  */
/*  they are inlined directly by the translator.      */


Keep (
	~next_caller_offset, ~next_callee_offset,
	~va_list, ~__va_start, ~va_arg, ~va_end
)
