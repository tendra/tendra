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
#define FS_ASSERT		DEBUG	/*  ASSERT has no effect unless DEBUG is 1  */
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

#undef FS_ENUMERATION
#define FS_ENUMERATION 1


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
