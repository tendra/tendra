/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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
#include "installtypes.h"
#if DO_SCHEDULE
#include "scheduler.h"
#endif
#define IMMEDIATE_MAX	255
#define IMMEDIATE_MIN	-128

extern char *outass(char *);
extern void load_store(instruction,int,baseoff);
extern void load_store_immediate(instruction,int,INT64);
extern void load_store_label(instruction,int,int);
extern void integer_branch(instruction,int,int);
extern void integer_jump(instruction,int,int,int);
extern void integer_jump_external(instruction,int,baseoff);
extern void integer_jump_fn(instruction,int,exp,space);
extern void operate_fmt(instruction,int,int,int);
extern void operate_fmt_immediate(instruction,int,int,int);
extern void operate_fmt_big_immediate(instruction,int,INT64,int);
extern void float_load_store(instruction,int,baseoff);
extern void float_branch(instruction,int,int);
extern void float_op(instruction,int,int,int);
extern void float_convert(instruction,int,int);
extern void float_load_store_immediate(instruction,int,char*);
extern void call_pal(instruction, instruction);
extern void fetch(instruction,baseoff);
extern void no_parameter_instructions(instruction);
extern void single_parameter_instructions(instruction,int);
extern void memory_fmt(instruction,int,int);
extern void operate_fmt(instruction,int,int,int);
#if DO_SCHEDULE
extern void out_code(Instruction_data);
extern void add_instruction(Instruction);
extern Instruction_data get_new_ins_data(void);
extern void output_instruction(Class,char*,char*);
extern void output_data(char*,char*);

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
#define output_instruction(class,string,op)op
#define output_data(string,op)op
#endif

#endif /*INSTFMTDECS_H*/








