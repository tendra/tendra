/*
 * Copyright (c) 2002-2008 The TenDRA Project <http://www.tendra.org/>.
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
 * $Id: main.c 2129 2008-06-30 12:14:08Z kate $
 */

/*
 * lang.h - Language entry point interface.
 */

#ifndef H_LANG
#define H_LANG

#include "output.h"
#include "grammar.h"
#include "adt/cstring-list.h"

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
	 * File input. This is called after the grammar is parsed.
	 */
	void  (*input_proc)(void *, GrammarT *);

	/*
	 * File output.
	 */
	void  (*output_proc)(void *, GrammarT *);
} LangListT;

#endif /* H_LANG */

