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

#include <stddef.h>

#include "xalloc/xalloc.h"
#include "error/error.h"

#include "instruction.h"
#include "zone.h"



/* 
    ALLOCATE A NEW ARG 

    This routine allocates a arg for a user provided function
*/
static arg*
new_arg(void) 
{
    arg *p;
    p = xmalloc(sizeof *p);
    p->next = NULL;
    p->is_reference = false;
    return p;
}

/*
    ADDS AN ARG

    This routines adds a new arg
 */
arg *
add_arg (arg_type t, unsigned int d)
{
    arg* p = new_arg();
    p->type = t;
    p->u.digit = d;
    return p;
}

/*
    ADDS AN ARG

    This routines adds an identifier arg
 */
arg *
add_identifier_arg ( char* s)
{
    arg* p = new_arg();
    p->type = arg_identifier;
    p->u.literal = s;
    return p;
}

/*
    ADDS AN ARG

    This routines adds a reference arg
 */
arg *
add_reference_arg ( char* s)
{
    arg* p = new_arg();
    p->type = arg_identifier;
    p->u.literal = s;
    p->is_reference = true;
    return p;
}

arg* 
add_terminal_arg ( char* s) 
{
    arg* p = new_arg();
    p->type = arg_terminal;
    p->u.literal = s;
    return p;
}

arg* 
add_none_arg ( void ) 
{
    arg* p = new_arg();
    p->type = arg_none;
    p->u.literal = NULL;
    return p;
}

void 
arg_output(arg* p, bool is_ref, int d, FILE* file)
{
	switch(p->type) {
	case arg_charP:
		error(ERROR_SERIOUS, "#* is not implemented yet at output level"); 
		break;
	case arg_char_nb:
		/*TODO assert(p->u.digit<nb_of_chars);*/
		fprintf(file, "c%d", p->u.digit);
		break;
	case arg_nb_of_chars:
		fprintf(file, "%d", d);
		break;

	case arg_identifier:
		if(p->is_reference) {
			/*TODO assert(is_ref);*/
			fprintf(file, "%s", p->u.literal);
		}
		else {
			if(is_ref)
				fprintf(file, "(*%s)", p->u.literal);
			else
				fprintf(file, "%s", p->u.literal);
		}
		break;
	case arg_terminal:
		fprintf(file, "%s", p->u.literal);
		break;
	case arg_ignore:
		error(ERROR_SERIOUS, "Ignore symbol ! is not implemented yet at output level"); 
		/*TODO implement*/
		break;
	case arg_return_terminal:
		fprintf(file, "ZT1"); /*TODO make prefixes option controllable or lct file controllable*/
		break;

	case arg_none :
	default:
		break;
		/*TODO ASSERT UNREACHABLE*/
	}
}

/*
    ALLOCATES A NEW ARGS LIST

    This routines allocates a new args list
*/
static args_list*
new_args_list (void) 
{
    args_list *p;
    p = xmalloc(sizeof *p);
    p->head =NULL;
    p->tail=&(p->head);
    p->nb_return_terminal = 0;
    return p;
}


/*
    ADDS A NEW ARGS LIST

    This routines adds a new args list
*/
args_list*
add_args_list (void) 
{
    args_list *p=new_args_list();
    return p;
}


/*
    ALLOCATE A NEW INSTRUCTION

    This routine allocates a new instrucion
*/

static instruction * 
new_instruction (instruction_type type) 
{
    instruction *p;
	p = xmalloc(sizeof *p);
    p->type=type;
    p->next=NULL;
    return p;
}

/*
    ADD  A NEW RETURN TOKEN INSTRUCTION

    This routine adds a new return token instruction
*/

instruction * 
add_instruction_return_terminal (char* name)
{
    instruction *p=new_instruction(return_terminal);
    p->u.name=name;
    return p;
}

/*
    ADD  A NEW DO NOTHING INSTRUCTION

    This routine adds a new do nothing instruction
*/

instruction * 
add_instruction_donothing () 
{
    instruction* p=new_instruction(do_nothing);
    return p;
}

/*
    ADD  A NEW DO NOTHING INSTRUCTION

    This routine adds a new do nothing instruction
*/

instruction * 
add_instruction_action (EntryT* act, args_list* lhs, args_list* rhs) 
{
    instruction* p=new_instruction(action_call);
    p->u.act.called_act=act;
    p->u.act.rhs=rhs;
    p->u.act.lhs=lhs;
    return p;
}

/*
    ADD  A NEW PUSH ZONE INSTRUCTION

    This routine adds a new push zone instruction
*/

instruction * 
add_instruction_pushzone (zone* z) 
{
    instruction* p=new_instruction(push_zone);
    p->u.s.z=z;
    p->u.s.is_beginendmarker_in_zone=1;
    return p;
}

/*
    ADD  A NEW POP ZONE INSTRUCTION

    This routine adds a new pop zone instruction
*/

instruction*
add_instruction_popzone (zone* z, int is_endmarker_in_zone) 
{
    instruction* p=new_instruction(pop_zone);
    p->u.s.z=z;
    p->u.s.is_beginendmarker_in_zone=is_endmarker_in_zone;
    return p;
}

/*
    ALLOCATE A NEW INSTRUCTION

    This routine allocates a new instrucion
*/

static 
instructions_list*
new_instructions_list (void)
{
    instructions_list *p;
	p = xmalloc(sizeof *p);
    p->head=NULL;
    p->tail=&(p->head);
    localnames_init(&(p->local_names));
    p->size = 0;
    p->nb_return_terminal=0;
    return p;   
}

/*
    ADDS A NEW INSTRUCTIONS LIST

    This routine adds a new instructions list.
*/

instructions_list*
add_instructions_list (void)
{
    instructions_list *p=new_instructions_list();
    return p;   
}


/*
	GET local names from InstructionsList
*/
LocalNamesT* 
instructionslist_localnames(instructions_list* l)
{
	return &l->local_names;
}

