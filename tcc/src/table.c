/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file is an attempt to centralise the various tables pertaining to file
 * types and their extensions. It is likely to evolve a little during the
 * course of refactoring the internal structure of tcc with the aim of neatly
 * segregating various things.
 *
 * TODO: rename this file to something more appropiate when the contents have settled.
 * TODO: consider sorting filetype_table for bsearch()
 * TODO: figure out what keep_aux is all about; can we fold it in somehow?
 * TODO: add a query for .keep_aux
 * TODO: document terms: suffix, stage identifier
 * TODO: add stage identifiers here
 * TODO: consider what ought to be private from table.h. comment accordingly
 *
 * TODO: possibly when coming up with an interface to set stops, we need only set to FTK_TC
 * For the moment this is omitted, and to set keep/stop values the table is accessed directly.
 * Perhaps table_setkeep(enum filetype type, enum filetype_keep keep) - the code seems
 * to set .keep to all possible values.
 *
 * TODO: provide a method of iteration; this is used in a few places. its purposes are
 * specific enough to provide sensible encapsulation here.
 *
 */

#include <shared/bool.h>

#include <assert.h>
#include <stddef.h>

#include "table.h"

struct filetype_table filetype_table[TYPE_ARRAY_SIZE] = {
	{ 'c', C_SOURCE,          FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{ 'i', PREPROC_C,         FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{ 'C', CPP_SOURCE,        FTK_FC, FTK_FC, FTK_FC, "cpp", 1, 0 },
	{ 'I', PREPROC_CPP,       FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{ 'j', INDEP_TDF,         FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{ 't', DEP_TDF,           FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{ 's', AS_SOURCE,         FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{ 'o', BINARY_OBJ,        FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{  0,  EXECUTABLE,        FTK_TN, FTK_FC, FTK_TN, NULL,  0, 0 },
	{ 'p', PRETTY_TDF,        FTK_TC, FTK_FC, FTK_TN, NULL,  0, 0 },
	{ 'P', PL_TDF,            FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{ 'A', TDF_ARCHIVE,       FTK_TN, FTK_FC, FTK_TN, NULL,  0, 0 },
	{ 'G', BINASM_G_FILE,     FTK_FC, FTK_FC, FTK_FC, NULL,  1, 1 },
	{ 'T', BINASM_T_FILE,     FTK_FC, FTK_FC, FTK_FC, NULL,  1, 1 },
	{ 'k', C_SPEC,            FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{ 'K', CPP_SPEC,          FTK_FC, FTK_FC, FTK_FC, NULL,  1, 0 },
	{ 'h', STARTUP_FILE,      FTK_FC, FTK_FC, FTK_FC, NULL,  1, 1 },
	{  0,  UNKNOWN_TYPE,      FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },

	    /* Dummy types */
	    /* TODO only keep, keep_aux and stop are used? */
	{  0,  INDEP_TDF_COMPLEX, FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{  0,  C_SPEC_1,          FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{  0,  C_SPEC_2,          FTK_TC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{  0,  CPP_SPEC_1,        FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{  0,  CPP_SPEC_2,        FTK_TC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{  0,  INDEP_TDF_AUX,     FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 },
	{ 'b', BINARY_OBJ_AUX,    FTK_FC, FTK_FC, FTK_FC, NULL,  0, 0 }
};

bool
table_isdummy(enum filetype type) {
	return type > UNKNOWN_TYPE;
}

enum filetype_keep
table_keep(enum filetype type) {
	return filetype_table[type].keep;
}

enum filetype_keep
table_stop(enum filetype type) {
	return filetype_table[type].stop;
}

const char *
table_suffix(enum filetype type) {
	/* TODO I think not for Dummy types */
	return filetype_table[type].suffix;
}

char
table_key(enum filetype type) {
	assert(filetype_table[type].key != '\0');

	return filetype_table[type].key;
}

enum filetype
table_findbykey(char key) {
	unsigned int i;

	assert(key != '\0');

	for (i = 0; i < TYPE_ARRAY_SIZE; i++) {
		if (filetype_table[i].key == key) {
			return filetype_table[i].filetype;
		}
	}

	return UNKNOWN_TYPE;
}

bool
table_checker(enum filetype type) {
	assert(type != UNKNOWN_TYPE);
	assert(type != EXECUTABLE);
	assert(!table_isdummy(type));

	return filetype_table[type].checker;
}

bool
table_stage(enum filetype type) {
	assert(type != UNKNOWN_TYPE);
	assert(type != EXECUTABLE);
	assert(!table_isdummy(type));

	return filetype_table[type].stage;
}

