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

#ifdef SUN
#define SUN_INTERFACE
#else
#define NEXT_INTERFACE
#endif
#else /* NEXT or SUN */

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
    HP OPERATING SYSTEM INTERFACE
*/

#ifdef HP_INTERFACE

#define float_to_unsigned		"___fixu"
#define unsigned_to_float		"___floatu"
#define profiling_routine		"mcount"
#define profiling_reg			REG_A0
#define profiling_uses_lea		0

#endif /* HP_INTERFACE */


/*
    NEXT OPERATING SYSTEM INTERFACE, or SunOS.
*/

#ifdef NEXT_INTERFACE

#define float_to_unsigned		"__fixunsdfsi"
#undef  unsigned_to_float		/* use built-in version */
#define profiling_routine		"mcount"
#define profiling_reg			REG_A0
#define profiling_uses_lea		1

#endif /* NEXT_INTERFACE */

#ifdef SUN_INTERFACE

#undef float_to_unsigned
#undef unsigned_to_float
#define profiling_routine "mcount"  /* all the defines for profiling */
#define profiling_reg REG_A0        /* are probably wrong. */
#define profiling_uses_lea 1
#endif