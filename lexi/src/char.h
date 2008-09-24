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
#include <stdio.h>
#include "adt.h"
#include "localnames.h"

typedef unsigned int letter;

struct zone_tag;
struct lexer_parse_tree_tag;

typedef enum arg_type_tag { 
  arg_charP, arg_char_nb, arg_chars_list, arg_litteral, arg_nb_of_chars, 
  arg_identifier, arg_terminal,
  arg_ignore, arg_return_terminal, arg_none /*Just for error recovery*/ 
} arg_type ;

typedef struct arg_tag {
  arg_type type;
  struct arg_tag* next;
  union {
    unsigned int digit;
    char* litteral;
  } u ;
  bool is_reference;
} arg;

/* ordered */
typedef struct args_list_tag {
  arg*  head ;
  arg** tail ;
  int nb_return_terminal;
} args_list ;

typedef struct user_function_tag {
  char* name;
  args_list* args;
} user_function;

typedef enum instruction_type_tag { return_terminal, push_zone, pop_zone, pure_apply_function, terminal_apply_function, do_nothing , action_call } instruction_type ;

typedef struct instruction_tag {
  instruction_type type;
  struct instruction_tag* next;
  union {
    char* name;  /* token   */
    struct {
      struct zone_tag* z;
      int is_beginendmarker_in_zone ;
    } s;
    user_function* fun; 
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


/*
    TYPE REPRESENTING A CHARACTER

    A character consists of a single letter (which may have associated
    data) plus pointers to the next character and to a list of alternative
    characters.
*/
typedef struct character_tag {
    letter ch;
    struct character_tag *opt;
    struct character_tag *next;
    union {
        instructions_list* definition; 
        char* map;   
    } u;
} character;

/*
    TYPE REPRESENTING A CHARACTER GROUP

    A character group is a named array of letters.
*/

typedef struct char_group_tag {
    char *name;
    letter *defn;
    letter letter_code;
    letter notin_letter_code;
    unsigned int group_code; /* for outputting the bitfield */
    struct zone_tag* z; /* Points back to the zone we are in */
    struct char_group_tag* next; /* Next in hash table */  
    struct char_group_tag* next_in_groups_list; 
} char_group;

typedef struct char_group_list_tag {
    char_group*  head;
    char_group** tail;
} char_group_list;


/*
    TYPE REPRESENTING A KEYWORD

    A keyword consists of a name plus some associated data.  All keywords
    are formed into a list using the next field.  done is a flag used in
    the output routines.
*/

typedef struct keyword_tag {
    char *name;
    instruction* instr;
    int done;
    struct keyword_tag *next;
} keyword;


/*
    PARAMETERS
*/

#define MAX_GROUPS		32
#define GROUP_HASH_TABLE_SIZE     128
#define LETTER_TRANSLATOR_SIZE  512

/* 
   Type of Zones indicate if a zone return terminals or not.

   If a zone never return terminal then it is possible to output 
   a more efficient code.
   
*/

typedef enum zone_type_tag {
    typezone_general_zone, /* A zone that can return more than one terminal */
    typezone_pseudo_token, /* A zone that returns only one terminal on zone exit*/
    typezone_pure_function /* A zone that never returns a terminal */ 
} zone_type;

/*
    TYPE REPRESENTING A ZONE
*/
typedef struct zone_tag {
    char* zone_name;
    zone_type type;  

    character* zone_pre_pass;
    character* zone_main_pass;

    keyword* keywords;
    char_group_list groups_hash_table [GROUP_HASH_TABLE_SIZE];  
    char_group* white_space;

    instructions_list *default_instructions;

    instructions_list* entering_instructions;
    instructions_list* leaving_instructions;

    struct zone_tag *opt; /*opt=brother*/
    struct zone_tag *next;/* next=first son*/ 
    struct zone_tag *up; 
    struct lexer_parse_tree_tag *top_level;
} zone;

/*
  THE LETTER TRANSLATOR TYPES
*/

typedef enum letter_translation_type_tag {
  eof_letter, last_letter, group_letter, notin_group_letter, char_letter
} letter_translation_type;

typedef struct letter_translation_tag {
  letter_translation_type type;
  letter letter_code ; 
  union {
    int ch; 
    char_group* grp;
  } u;
  struct letter_translation_tag* next; 
} letter_translation;


typedef struct letter_translation_list_tag {
  letter_translation* head;
  letter_translation** tail;
} letter_translation_list;

/* 
   THE LEXER PARSE TREE OF THE LXI FILE
*/

typedef struct lexer_parse_tree_tag {
  zone* global_zone;

  FILE* copyright_file;

  int no_total_groups;
  char_group_list groups_list;

  TableT table; /* Actions and types */

  EntryT* lexi_char_type;    /*  for #0 arguments */
  EntryT* lexi_string_type;  /*  for #* arguments */
  EntryT* lexi_int_type;     /*  for #n arguments */
  EntryT* lexi_terminal_type;     /*  for $ = returns */

  letter_translation_list (letters_table[LETTER_TRANSLATOR_SIZE]) ;
  letter last_letter_code;
  letter eof_letter_code;
  letter next_generated_key;

} lexer_parse_tree;

/*
    DECLARATIONS FOR CHARACTER ROUTINES
*/

extern void init_lexer_parse_tree(lexer_parse_tree*);

extern void set_predefined_char_lexi_type(lexer_parse_tree*, char*, char*);
extern void set_predefined_string_lexi_type(lexer_parse_tree*, char*, char*);
extern void set_predefined_int_lexi_type(lexer_parse_tree*, char*, char*);
extern void set_predefined_terminal_lexi_type(lexer_parse_tree*, char*);

extern EntryT* lexer_char_type(lexer_parse_tree*);
extern EntryT* lexer_string_type(lexer_parse_tree*);
extern EntryT* lexer_int_type(lexer_parse_tree*);
extern EntryT* lexer_terminal_type(lexer_parse_tree*);

extern void add_char(zone*, character*, letter*, instructions_list*, char* );
extern zone* add_zone(zone*, char*,letter*, int);
extern char_group* make_group(zone*, char *, letter *);
extern int in_group(char_group *, letter);
extern int is_group_empty(char_group *);
extern int all_groups_empty(char_group *list);
extern letter *make_string(char *, zone*);
extern letter find_escape(int,letter);
extern void add_keyword(zone*, char*, instruction*);
extern size_t char_maxlength(character *, letter);
extern size_t zone_maxlength(zone *, int);
extern zone * find_zone (zone*, char*); 

extern user_function* add_user_function (char *name) ;
extern instruction * add_instruction_return_terminal (char* name);
extern instruction* add_instruction_purefunction (char* name, args_list* args) ;
extern instruction* add_instruction_terminalfunction (char* name, args_list* args) ;
extern instruction* add_instruction_donothing (void) ;
extern instruction * add_instruction_action (EntryT*, args_list*, args_list*) ;
extern instruction* add_instruction_mapping (char* map) ;
extern args_list* add_args_list (void) ;
extern arg* add_arg (arg_type, unsigned int) ;
extern arg* add_litteral_arg ( char* ) ;
extern arg* add_identifier_arg ( char* ) ;
extern arg* add_reference_arg ( char* ) ;
extern arg* add_terminal_arg ( char* ) ;
extern arg* add_none_arg ( void ) ;
extern void arg_output(arg*, bool, int, FILE*);

extern instruction* add_instruction_pushzone (zone* z) ;
extern instruction* add_instruction_popzone (zone* z, int is_endmarker_in_zone) ;
extern instructions_list* add_instructions_list (void) ;
extern letter_translation* add_group_letter_translation(char_group*, int);
extern void letters_table_add_translation(letter_translation*, letter_translation_list []);
extern letter_translation* letters_table_get_translation(letter, letter_translation_list []);
extern unsigned int hash_cstring (char*);
extern unsigned int hash_cstring_n(char*,size_t);

extern LocalNamesT* instructionslist_localnames(instructions_list*);
extern bool args_rhs_fill_type(args_list*, LocalNamesT*, lexer_parse_tree*);
#endif
