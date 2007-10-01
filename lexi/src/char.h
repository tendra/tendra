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


#ifndef CHAR_INCLUDED
#define CHAR_INCLUDED

#include <stddef.h>


/*
    TYPE REPRESENTING A CHARACTER

    A character consists of a single letter (which may have associated
    data) plus pointers to the next character and to a list of alternative
    characters.
*/

typedef unsigned int letter;

struct zone_tag;

typedef enum arg_type_tag { 
  arg_charP, arg_char_nb, arg_chars_list
} arg_type ;

typedef struct arg_tag {
  arg_type type;
  struct arg_tag* next;
  unsigned int digit;
} arg;

typedef struct args_list_tag {
  arg*  head ;
  arg** tail ;
} args_list ;

typedef struct user_function_tag {
  char* name;
  args_list* args;
} user_function;

typedef enum instruction_type_tag { return_token, push_zone, pop_zone, apply_function, do_nothing } instruction_type ;

typedef struct instruction_tag {
  instruction_type type;
  struct instruction_tag* next;
  union {
    char* name;  /* token   */
    struct zone_tag* z;
    user_function* fun; 
  } ;
} instruction ;

typedef struct instructions_list_tag {
  instruction* head;
  instruction** tail;
} instructions_list;


typedef struct character_tag {
    letter ch;
    char* cond;
    struct character_tag *opt;
    struct character_tag *next;
    union {
        instructions_list* definition; 
        char* map;   
    };
} character;

/*
    TYPE REPRESENTING A CHARACTER GROUP

    A character group is a named array of letters.
*/

typedef struct {
    char *name;
    letter *defn;
} char_group;


/*
    TYPE REPRESENTING A KEYWORD

    A keyword consists of a name plus some associated data.  All keywords
    are formed into a list using the next field.  done is a flag used in
    the output routines.
*/

typedef struct keyword_tag {
    char *name;
    instruction* instr;
    char* cond;
    int done;
    struct keyword_tag *next;
} keyword;


/*
    PARAMETERS
*/

#define MAX_GROUPS		31

/*
    TYPE REPRESENTING A ZONE

*/
typedef struct zone_tag {
    char* zone_name;
    character* zone_pre_pass;
    character* zone_main_pass;

    keyword* keywords;

    instructions_list *default_actions;
    char *default_cond;

    instructions_list* entering_instructions;
    instructions_list* leaving_instructions;

    struct zone_tag *opt; /*opt=brother*/
    struct zone_tag *next;/* next=first son*/ 
    struct zone_tag *up; 
} zone;



/*
    SPECIAL LETTERS
*/

#define SIMPLE_LETTER		((letter)0x0100)
#define EOF_LETTER		((letter)0x0100)
#define LAST_LETTER		((letter)0x0101)
#define WHITE_LETTER		((letter)0x0102)
#define GROUP_LETTER		((letter)0x0103)


/*
    DECLARATIONS FOR CHARACTER ROUTINES
*/

extern letter *white_space;
/*extern character *pre_pass;*/
extern zone* global_zone;
extern char_group groups [];
extern int no_groups;
/*extern keyword *keywords;*/
extern void add_char(character*, letter*, char *, instructions_list*, char* );
extern zone* add_zone(zone*, char*,letter*);
extern void make_group(char *, letter *);
extern int in_group(letter *, letter);
extern letter *make_string(char *);
extern letter find_escape(int);
extern void add_keyword(zone*, char *, char*, instruction*);
extern size_t char_maxlength(character *);
extern zone * find_zone (zone*, char*); 

extern user_function* add_user_function (char *name) ;
extern instruction * add_instruction_return_token (char* name);
extern instruction* add_instruction_function (char* name, args_list* args) ;
extern instruction* add_instruction_donothing () ;
extern instruction* add_instruction_mapping (char* map) ;
extern args_list* add_args_list (void);
extern arg* add_arg (arg_type, unsigned int);
extern instruction* add_instruction_pushzone (zone* z) ;
extern instructions_list* add_instructions_list (void) ;


#endif
