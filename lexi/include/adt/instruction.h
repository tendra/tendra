/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_INSTRUCTION_H
#define LEXI_INSTRUCTION_H

#include <stdbool.h>

struct zone;

#include "localnames.h"

enum arg_type {
	arg_charP,
	arg_char_nb,
	arg_nb_of_chars,
	arg_identifier,
	arg_terminal,
	arg_ignore,
	arg_return_terminal,
	arg_none
};

struct arg {
	enum arg_type type;
	struct arg *next;

	union {
		unsigned int digit;
		char *literal;
	} u;

	bool is_reference;
};

/* ordered */
struct args_list {
	struct arg  *head;
	struct arg **tail;
	int nb_return_terminal;
};

enum instruction_type {
	return_terminal,
	push_zone,
	pop_zone,
	do_nothing,
	action_call
};

struct instruction {
	enum instruction_type type;
	struct instruction *next;

	union {
		char *name; /* token */
		struct {
			struct zone *z;
			int is_beginendmarker_in_zone;
		} s;
		struct {
			struct EntryT *called_act;
			struct args_list *lhs;
			struct args_list *rhs;
		} act;
	} u;
};

/* ordered */
struct instructions_list {
	struct instruction* head;
	struct instruction** tail;
	int size;
	struct LocalNamesT local_names;
	int nb_return_terminal;
};

struct arg *add_arg(enum arg_type, unsigned int);
struct arg *add_identifier_arg(char *);
struct arg *add_reference_arg(char *);
struct arg *add_terminal_arg(char *);
struct arg *add_none_arg(void);
void arg_output(struct arg *, bool, int, FILE *);
struct args_list *add_args_list(void);

struct instruction *add_instruction_return_terminal(char *name);
struct instruction *add_instruction_donothing(void);
struct instruction *add_instruction_action(struct EntryT *, struct args_list *, struct args_list *);
struct instruction *add_instruction_mapping(char *map);

struct instruction *add_instruction_pushzone(struct zone *z);
struct instruction *add_instruction_popzone(struct zone *z, int is_endmarker_in_zone);
struct instructions_list *add_instructions_list(void);

struct LocalNamesT *instructionslist_localnames(struct instructions_list *);

#endif

