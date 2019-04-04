/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * lang.h - Language entry point interface.
 */

#ifndef H_LANG
#define H_LANG

#include <exds/cstring-list.h>

#include "output.h"
#include "grammar.h"

/*
 * This structure provides the interface for language-specific implementations;
 * this acts as the entry point from main.c. Each language provides one
 * (or several) instances of this, each acting as a language as per the -l flag.
 *
 * The callbacks provided may be given as NULL if they are not required.
 */
typedef struct LangListT {
	/*
	 * The name of the language, as used by the -l flag. This should not
	 * contain spaces.
	 */
	const char *language;

	/*
	 * The number of input files and output files required for this language.
	 */
	unsigned num_input_files;
	unsigned num_output_files;

	/*
	 * Initialisation. This is called before the grammar is parsed.
	 *
	 * The value returned is an opaque pointer passed to the input_proc()
	 * and output_proc() callbacks.
	 */
	void *(*init_proc)(OutputInfoT *, CStringListT *);

	/*
	 * Routine for reading the .act file. This is called after the grammar is parsed.
	 */
	void  (*input_proc)(void *, GrammarT *);

	/*
	 * Routine for outputting the parser in the language represented by this struct.
	 */
	void  (*output_proc)(void *, GrammarT *);
} LangListT;

#endif /* H_LANG */

