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


/* 	inst_fmtdecs.h,v 1.4 1995/09/04 16:23:56 john Exp	 */


/*
   instfmtdecs.h
   declarations of functions used to output assembler instructions.
*/
#ifndef INSTFMTDECS_H
#define INSTFMTDECS_H
#include "addresstypes.h"
#include "cross.h"
#include "instypes.h"
#include "ins_data.h"
#include "exptypes.h"
#include "procrectypes.h"
#if DO_SCHEDULE
#include "scheduler.h"
#endif
#define IMMEDIATE_MAX	255
#define IMMEDIATE_MIN	-128

extern char *outass PROTO_S ((char *));
extern void load_store PROTO_S ((instruction,int,baseoff));
extern void load_store_immediate PROTO_S ((instruction,int,INT64));
extern void load_store_label PROTO_S ((instruction,int,int));
extern void integer_branch PROTO_S ((instruction,int,int));
extern void integer_jump PROTO_S ((instruction,int,int,int));
extern void integer_jump_external PROTO_S ((instruction,int,baseoff));
extern void integer_jump_fn PROTO_S ((instruction,int,exp,space));
extern void operate_fmt PROTO_S ((instruction,int,int,int));
extern void operate_fmt_immediate PROTO_S ((instruction,int,int,int));
extern void operate_fmt_big_immediate PROTO_S ((instruction,int,INT64,int));
extern void float_load_store PROTO_S ((instruction,int,baseoff));
extern void float_branch PROTO_S ((instruction,int,int));
extern void float_op PROTO_S ((instruction,int,int,int));
extern void float_convert PROTO_S ((instruction,int,int));
extern void float_load_store_immediate PROTO_S ((instruction,int,char*));
extern void call_pal PROTO_S ((instruction, instruction));
extern void fetch PROTO_S ((instruction,baseoff));
extern void no_parameter_instructions PROTO_S ((instruction));
extern void single_parameter_instructions PROTO_S ((instruction,int));
extern void memory_fmt PROTO_S ((instruction,int,int));
extern void operate_fmt PROTO_S ((instruction,int,int,int));
#if DO_SCHEDULE
extern void out_code PROTO_S ((Instruction_data));
extern void add_instruction PROTO_S ((Instruction));
extern Instruction_data get_new_ins_data PROTO_S ((void));
extern void output_instruction PROTO_S ((Class,char*,char*));
extern void output_data PROTO_S ((char*,char*));

typedef struct String_dat
{
    char data;
    struct String_dat *next;
} StringData;

typedef struct
{
    StringData *head,*tail;
} String;

#else
#define output_instruction(class,string,op) op
#define output_data(string,op) op
#endif

#endif /*INSTFMTDECS_H*/


  
 
  



