/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

        /* ********************************************* */
        /*                                               */
        /*    Generic Var Param Token Definitions.       */
        /*    Needs to be linked with the ANSI library   */
        /*    specific to each platform.                 */
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

Tokdef ~next_caller_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
  offset_pad (
    	parameter_alignment (next_sh),
	offset_add (
	    this_offset,
	    shape_offset (this_sh)
	)
    );

Tokdef ~next_callee_offset = [this_offset:EXP, this_sh:SHAPE, next_sh:SHAPE] EXP
    offset_pad (
	parameter_alignment (next_sh),
	    offset_add (
	    this_offset,
	    shape_offset (this_sh)
	)
    );


Keep (
	~next_caller_offset, ~next_callee_offset,
	~va_list, ~__va_start, ~va_arg, ~va_end
)
