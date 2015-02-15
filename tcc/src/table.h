/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * An attempt to centralise the various tables pertaining to file types
 * and their extensions.
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
	bool checker;

	/*
	 * True if this filetype's key is a stage identifier as well as being a
	 * suffix; false indicates a suffix. Stage identifiers are a superset.
	 */
	bool stage;

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

bool
table_checker(enum filetype type);

bool
table_stage(enum filetype type);

#endif

