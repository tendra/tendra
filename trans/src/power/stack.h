/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef STACK_H
#define STACK_H  1

#include <construct/installtypes.h>

#include "addr.h"

#define ALIGNNEXT(bitposn, bitalign)	(((bitposn) + (bitalign) -1) & ~((bitalign) -1))
#define ALLOCA_ALIGNMENT(n)((n+7) & ~7)

/* Stack frame layout, from Assembler Reference manual page 4-19, in bytes */
#define STACK_LINK_AREA_SIZE		24
#define	STACK_BACK_CHAIN		0
#define	STACK_SAVED_CR			4
#define	STACK_SAVED_LR			8
#define	STACK_RESERVED1			12
#define	STACK_RESERVED2			16
#define	STACK_SAVED_TOC			20
#define	STACK_ARG_AREA			STACK_LINK_AREA_SIZE

#define	STACK_FIXED_REG_DUMP_AREA_SIZE	(19*4)		/* 19 fixed point */
#define	STACK_FLOAT_REG_DUMP_AREA_SIZE	((18*2)*4)	/* 18 doubles */
#define	STACK_REG_DUMP_AREA_SIZE	(ALIGNNEXT(STACK_FIXED_REG_DUMP_AREA_SIZE,8)\
						   +STACK_FLOAT_REG_DUMP_AREA_SIZE)
#define	STACK_MIN_MAXARGS		(8*4)		/* 8 words of params */

/* info on the stack frame of current proc being coded */
extern long p_no_of_returns;
extern long p_sreg_first_save;
extern long p_sfreg_first_save;
extern long p_frame_size;
extern long p_locals_offset;

extern long p_args_and_link_size;/* maximum size of parameter list + LINK_AREA size in bytes */
extern bool p_has_fp;
extern bool p_has_saved_sp;
extern bool p_leaf;
extern bool p_has_back_chain;
extern bool p_has_alloca;
extern bool p_save_all_sregs;
extern bool p_has_vcallees;
extern bool p_has_no_vcallers;
extern long p_fixed_params;
extern long p_float_params;
extern long p_callee_size;
extern bool p_has_tp;
extern int p_return_label;
extern ans p_result;/* what the result of the proc is */
extern exp p_current;
extern void generate_procedure_prologue(void);
extern void generate_procedure_epilogue(void);
extern void generate_untidy_procedure_epilogue(void);
extern void save_sp_on_stack(void);
extern void get_sp_from_stack(void);
extern void save_back_chain_using_frame_pointer(void);
extern void initialise_procedure(procrec *);
extern void restore_sregs(int,int);
extern void restore_link_register(void);
#define EXTRA_CALLEE_BYTES 8 /* the number of bytes added on to the callees i.e 4 to hold saved chain*/

#endif
