/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
*/
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/


/*
    TARGET CONFIGURATION FILE

    If NEXT is defined, the system will use the GNU assembler (gas)
    format, the GNU debugger (gdb) and the NeXT operating system
    interface.  Otherwise the system will use the HP assembler, the
    HP debugger (xdb) and the HP-UX operating system interface.  To
    use gas and gdb on the HP, it is necessary to define the GNU macro.
*/


#if defined(NEXT) || defined(SUN) /* NeXT 68K or sun 68k */

#define GAS_ASSEMBLER
#define GDB_DEBUGGER
#ifdef SUN
#define SUN_INTERFACE
#else
#define NEXT_INTERFACE
#endif
#else /* NEXT or SUN */

#ifdef GNU
#define GAS_ASSEMBLER
#define GDB_DEBUGGER
#else /* GNU */
#define HP_ASSEMBLER
#define XDB_DEBUGGER
#endif /* GNU */

#define HP_INTERFACE

#endif /* NEXT */


/*
    HP ASSEMBLER DETAILS
*/

#ifdef HP_ASSEMBLER

#define  asm_dotty_instrs		/* instructions are mov.l etc */
#define  asm_percent_regs		/* registers are %d0 etc */

#define  asm_data_first			/* true */
#define  asm_nprefix			outc ( '&' )
#define  asm_fprefix			outs ( "0f" )
#define  asm_ind_before			outc ( '(' )
#define  asm_ind_middle			/* empty */
#define  asm_ind_after			outc ( ')' )
#define  asm_predec_before		outs ( "-(" )
#define  asm_predec_after		outc ( ')' )
#define  asm_postinc_before		outc ( '(' )
#define  asm_postinc_after		outs ( ")+" )
#define  asm_scale_before		outc ( ',' )
#define  asm_scale			outs ( ".l*" )
#define  asm_scale_1			outs ( ".l" )
#define  asm_mem_before			outs ( "([" )
#define  asm_mem_second			/* empty */
#define  asm_mem_third			outc ( ']' )
#define  asm_mem_after			outc ( ')' )
#define  asm_bf_before			outc ( '{' )
#define  asm_bf_middle			outc ( ':' )
#define  asm_bf_after			outc ( '}' )
#define  asm_rpair_sep			outc ( ':' )
#define  asm_comment			outc ( '#' )

#define  asm_cmp_reversed		/* cmp instructions are reversed */
#define  asm_version			outs ( "\tversion 2" )
#define  asm_version_aux		outs ( "\tversion 3" )

#endif /* HP_ASSEMBLER */


/*
    HP DEBUGGER DETAILS
*/

#ifdef XDB_DEBUGGER
#define  default_diag			DIAG_UNKNOWN
#endif /* XDB_DEBUGGER */


/*
    HP OPERATING SYSTEM INTERFACE
*/

#ifdef HP_INTERFACE

#define  hp_cc_conventions		/* use HP conventions */
#define  float_to_unsigned		"___fixu"
#define  unsigned_to_float		"___floatu"
#define  profiling_routine		"mcount"
#define  profiling_reg			REG_A0
#define  profiling_uses_lea		0

#endif /* HP_INTERFACE */


/*
    GAS (NEXT) ASSEMBLER DETAILS
*/

#ifdef GAS_ASSEMBLER

#define  asm_simple_instrs		/* instructions are movl etc */
#define  asm_simple_regs		/* registers are d0 etc */

#undef 	 asm_data_first			/* false */
#define  asm_nprefix			outc ( '#' )
#define  asm_fprefix			outs ( "0r" )
#define  asm_ind_before			/* empty */
#define  asm_ind_middle			outc ( '@' )
#define  asm_ind_after			/* empty */
#define  asm_predec_before		/* empty */
#define  asm_predec_after		outs ( "@-" )
#define  asm_postinc_before		/* empty */
#define  asm_postinc_after		outs ( "@+" )
#define  asm_scale_before		/* empty */
#define  asm_scale			outs ( ":l:" )
#define  asm_scale_1			outs ( ":l" )
#define  asm_mem_before			/* empty */
#define  asm_mem_second			outc ( '@' )
#define  asm_mem_third			outc ( '@' )
#define  asm_mem_after			/* empty */
#define  asm_bf_before			outc ( '{' )
#define  asm_bf_middle			outc ( ':' )
#define  asm_bf_after			outc ( '}' )
#define  asm_rpair_sep			outc ( ':' )
#define  asm_comment			outc ( '#' )

#define  asm_does_jump_lens		/* calculates jump lengths */
#define  asm_uses_equals		/* uses = rather than set */
#define  asm_uses_lcomm			/* uses lcomm rather than bss */
#define  asm_no_btst_suffix		/* doesn't understand btst.[bl] */

#endif /* GAS_ASSEMBLER */


/*
    GNU DEBUGGER DETAILS
*/

#ifdef GDB_DEBUGGER
#define  default_diag			DIAG_STAB
#endif /* GDB_DEBUGGER */


/*
    NEXT OPERATING SYSTEM INTERFACE, or SunOS.
*/

#ifdef NEXT_INTERFACE

#define  gcc_conventions		/* use gcc conventions */
#define  float_to_unsigned		"__fixunsdfsi"
#undef   unsigned_to_float		/* use built-in version */
#define  profiling_routine		"mcount"
#define  profiling_reg			REG_A0
#define  profiling_uses_lea		1

#endif /* NEXT_INTERFACE */

#ifdef SUN_INTERFACE

#define gcc_conventions
#undef float_to_unsigned
#undef unsigned_to_float
#define profiling_routine "mcount"  /* all the defines for profiling */
#define profiling_reg REG_A0        /* are probably wrong. */
#define profiling_uses_lea 1
#endif

