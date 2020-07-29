/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OPTIONS_H
#define OPTIONS_H


#include "filename.h"
#include "list.h"
#include "hash.h"

/*
 * TYPE REPRESENTING AN OPTION
 *
 * An option consists of an input pattern, in, an output command, out, and some
 * explanatory text, explain. For options which do not form part of the command
 * line interface (i.e. those used for environment files), the "explain" field
 * carries a default value, instead.
 */
/* TODO: this can probably become private */
struct optmap {
	char *in;
	char *out;
	char *explain;
};


/*
 * TABLES OF OPTIONS
 *
 * These tables give the option mappings for the command-line options and the
 * environment options.
 */

extern struct optmap main_optmap[];


/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with processing command-line options and input
 * files.
 */

extern void process_options(list *, struct optmap *, enum hash_precedence);


/*
 * THE LIST OF ALL INPUT FILES
 *
 * All the input files are formed into this list.
 */

extern filename *input_files;


#endif /* OPTIONS_H */
