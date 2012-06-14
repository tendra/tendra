/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

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


void asm_nprefix(void);
void asm_fprefix(void);
void asm_ind_before(void);
void asm_ind_middle(void);
void asm_ind_after(void);
void asm_predec_before(void);
void asm_predec_after(void);
void asm_postinc_before(void);
void asm_postinc_after(void);
void asm_scale_before(void);
void asm_scale(void);
void asm_scale_1(void);
void asm_mem_before(void);
void asm_mem_second(void);
void asm_mem_third(void);
void asm_mem_after(void);
void asm_bf_before(void);
void asm_bf_middle(void);
void asm_bf_after(void);
void asm_rpair_sep(void);
void asm_comment(void);


/*
    HP ASSEMBLER DETAILS
*/

#ifdef HP_ASSEMBLER

#define  asm_percent_regs		/* registers are %d0 etc */

#define  asm_data_first			/* true */

#define  asm_cmp_reversed		/* cmp instructions are reversed */
#define  asm_version			outs("\tversion 2")
#define  asm_version_aux		outs("\tversion 3")

#endif /* HP_ASSEMBLER */


/*
    HP DEBUGGER DETAILS
*/

#ifdef XDB_DEBUGGER
#define default_diag			DIAG_UNKNOWN
#endif /* XDB_DEBUGGER */


/*
    HP OPERATING SYSTEM INTERFACE
*/

#ifdef HP_INTERFACE

#define hp_cc_conventions		/* use HP conventions */
#define float_to_unsigned		"___fixu"
#define unsigned_to_float		"___floatu"
#define profiling_routine		"mcount"
#define profiling_reg			REG_A0
#define profiling_uses_lea		0

#endif /* HP_INTERFACE */


/*
    GAS (NEXT) ASSEMBLER DETAILS
*/

#ifdef GAS_ASSEMBLER

#define asm_simple_regs			/* registers are d0 etc */

#undef 	asm_data_first			/* false */

#define asm_does_jump_lens		/* calculates jump lengths */
#define asm_uses_equals			/* uses = rather than set */
#define asm_uses_lcomm			/* uses lcomm rather than bss */
#define asm_no_btst_suffix		/* doesn't understand btst.[bl] */

#endif /* GAS_ASSEMBLER */


/*
    GNU DEBUGGER DETAILS
*/

#ifdef GDB_DEBUGGER
#define default_diag			DIAG_STAB
#endif /* GDB_DEBUGGER */


/*
    NEXT OPERATING SYSTEM INTERFACE, or SunOS.
*/

#ifdef NEXT_INTERFACE

#define gcc_conventions			/* use gcc conventions */
#define float_to_unsigned		"__fixunsdfsi"
#undef  unsigned_to_float		/* use built-in version */
#define profiling_routine		"mcount"
#define profiling_reg			REG_A0
#define profiling_uses_lea		1

#endif /* NEXT_INTERFACE */

#ifdef SUN_INTERFACE

#define gcc_conventions
#undef float_to_unsigned
#undef unsigned_to_float
#define profiling_routine "mcount"  /* all the defines for profiling */
#define profiling_reg REG_A0        /* are probably wrong. */
#define profiling_uses_lea 1
#endif
