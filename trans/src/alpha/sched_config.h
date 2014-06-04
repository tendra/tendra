/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
  sched_config.h
*/

#ifndef H_SCHED_CONFIG
#define H_SCHED_CONFIG

#define NUM_CLASSES		((Unsigned) 20)
#define NUM_FUNC_UNITS		((Unsigned) 7)
#define NUM_RESOURCES		((Unsigned) 69)
#define NUM_INSTRUCTIONS	18
#define INSTRUCTION_SIZE	4
#define MEMORY_LATENCY		((Unsigned) 6)
/* #define USE_MY_INSTRUCTION_DATA 0*/
#define CHANGE_OVER		1
#define REMOVE_TEXT		1
#define FS_TEXT_AVAILABLE	1	/* can we assume existence of the 'text' macro ? */
#define FS_DUAL_ISSUE		1
#define FS_PIPELINE_DIAGRAM	0
#define FS_NOP_REQUIRED		0
#define FS_NOP_SYMBOL		"NOP"
#define FS_FUNIT_FROM_CLASS	1
#define FS_CYCLES_FROM_CLASS	1
#define FS_DEDUCE_MEM_USES	1
#define FS_STACK_REGISTER	R30
#define FS_FIXED_ZERO_REGISTER	R31
#define FS_FLOAT_ZERO_REGISTER	F31


#define MAX_USES		5	/* maximum number of registers used by an instruction */
#define MAX_SETS		2	/* maximum number of registers set  by an instruction */
#define MAX_NODES		((Unsigned) 3000)
#define MAX_DEPTH		100
#define SCALE_FACTOR		4
#define PIPE_LENGTH		((size_t) 25)
#define NODE_BLOCK_SIZE		((size_t) 1000)
#define INST_BLOCK_SIZE		((size_t) 1000)
#define LIST_BLOCK_SIZE		((size_t) 1000)

#define TIDY_UP			1
#define SAVE_SPACE	       0



#define UNALIGNED_ACCESS_OFFSET_ADJUSTMENT -7
#define UNALIGNED_ACCESS_SIZE_ADJUSTMENT   7

#define is_in_ibus1 1		/*	Is in instruction bus 1				*/
#define is_in_ibus2 2		/*	Is in instruction bus 2				*/
#define is_in_abox  4		/*	Is in address box				*/
#define is_in_bbox  8		/*	Is in branch box				*/
#endif
