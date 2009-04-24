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


#ifndef INSTRUCTION_INCLUDED
#define INSTRUCTION_INCLUDED

#include <stdbool.h>

struct zone_tag;

#include "../adt.h"
#include "../localnames.h"


typedef enum arg_type_tag { 
  arg_charP, arg_char_nb,  arg_nb_of_chars, 
  arg_identifier, arg_terminal,
  arg_ignore, arg_return_terminal, arg_none /*Just for error recovery*/ 
} arg_type ;

typedef struct arg_tag {
  arg_type type;
  struct arg_tag* next;
  union {
    unsigned int digit;
    char* literal;
  } u ;
  bool is_reference;
} arg;

/* ordered */
typedef struct args_list_tag {
  arg*  head ;
  arg** tail ;
  int nb_return_terminal;
} args_list ;

typedef enum instruction_type_tag { return_terminal, push_zone, pop_zone, do_nothing , action_call } instruction_type ;

typedef struct instruction_tag {
  instruction_type type;
  struct instruction_tag* next;
  union {
    char* name;  /* token   */
    struct {
      struct zone_tag* z;
      int is_beginendmarker_in_zone ;
    } s;
    struct {
      EntryT* called_act;
      args_list* lhs; 
      args_list* rhs; 
    } act;
  } u;
} instruction ;

/* ordered */
typedef struct instructions_list_tag {
  instruction* head;
  instruction** tail;
  int size;
  LocalNamesT local_names;
  int nb_return_terminal;
} instructions_list;


extern arg* add_arg (arg_type, unsigned int) ;
extern arg* add_identifier_arg ( char* ) ;
extern arg* add_reference_arg ( char* ) ;
extern arg* add_terminal_arg ( char* ) ;
extern arg* add_none_arg ( void ) ;
extern void arg_output(arg*, bool, int, FILE*);
extern args_list* add_args_list (void) ;

extern instruction * add_instruction_return_terminal (char* name);
extern instruction* add_instruction_donothing (void) ;
extern instruction * add_instruction_action (EntryT*, args_list*, args_list*) ;
extern instruction* add_instruction_mapping (char* map) ;

extern instruction* add_instruction_pushzone (struct zone_tag *z) ;
extern instruction* add_instruction_popzone (struct zone_tag *z, int is_endmarker_in_zone) ;
extern instructions_list* add_instructions_list (void) ;

extern LocalNamesT* instructionslist_localnames(instructions_list*);

#endif
