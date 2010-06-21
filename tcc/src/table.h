/*
 * Copyright (c) 2008 The TenDRA Project <http://www.tendra.org/>.
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
 * An attempt to centralise the various tables pertaining to file types
 * and their extensions.
 * $Id$
 */

#ifndef TABLE_H
#define TABLE_H

#include "config.h"
#include "filename.h"

#define TYPE_ARRAY_SIZE     (UNKNOWN_TYPE + 8)

enum filetype_keep {
	/*
	 * False but changeable.
	 *
	 * This is kept as 0 to facilitate using this enum in conditionals.
	 * TODO perhaps rename to something using the word "FALSE".
	 */
	FTK_FC = 0,

	/* True but changeable */
	FTK_TC = 1,

	/* True and not changeable */
	FTK_TN = 2
};

/* TODO eventually this can become private, and accessed through a suitable API */
struct filetype_table {
	/*
	 * SINGLE CHARACTER KEYS FOR FILE TYPES
	 *
	 * Each file type has an associated identifying letter. In most cases this
	 * corresponds to the file suffix. This is expected to be unique per type.
	 *
	 * Unused keys are set to '\0'.
	 *
	 * TODO why does this exist?
	 * TODO: We can probably eliminate this in favour of strings.
	 */
	char key;

	/*
	 * The ID of each entry; this is the primary key for a filetype, by which
	 * its associated information (such as its keep information) may be found.
	 */
	const enum filetype filetype;

	/*
	 * FILE PRESERVATION AND CONSTRUCTION OPTIONS
	 *
	 * These tables control whether output files of the various file types should
	 * be kept and whether the compilation stops after they are produced.
	 *
	 * In the keeps array, a nonzero value indicates that any file of this type which
	 * is created should be preserved. In the stops array, it indicates that the
	 * compilation halts at this stage. The keeps_aux array keeps track of the
	 * explicit file preservation options.
	 */
	enum filetype_keep keep;
	enum filetype_keep keep_aux;
	enum filetype_keep stop;

	/*
	 * SUFFIX OVERRIDES
	 *
	 * This table contains the strings which are used when the suffix overrides are
	 * set from the command line. Initially, it is empty.
	 */
	/* TODO who uses this? can we remove the feature? */
	const char *suffix;

	/*
	 * True if this filetype is applicable to the checker. In this case, when
	 * run as the checker, tcc will consider this filetype unrecognised if this
	 * is false.
	 */
	boolean checker;

	/*
	 * True if this filetype's key is a stage identifier as well as being a
	 * suffix; false indicates a suffix. Stage identifiers are a superset.
	 */
	boolean stage;

	/* TODO more fields to come here. move in content from various lookup functions */
};

extern struct filetype_table filetype_table[TYPE_ARRAY_SIZE];

/*
 * Returns true if the given file is to be kept.
 */
enum filetype_keep
table_keep(enum filetype type);

/*
 * Returns true if the given file is to be stopped.
 */
enum filetype_keep
table_stop(enum filetype type);

/*
 * Find the suffix for the given filetype.
 */
const char *
table_suffix(enum filetype type);

/*
 * Find the single-character key for the given filetype.
 */
char table_key(enum filetype type);

/*
 * Find the filetype associated with a single-character key, which may either
 * be a suffix or a stage identifier.
 */
enum filetype
table_findbykey(char key);

boolean
table_checker(enum filetype type);

boolean
table_stage(enum filetype type);

#endif

