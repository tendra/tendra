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

#include <assert.h>
#include <stddef.h>

#include "config.h"
#include "table.h"

struct filetype_table filetype_table[TYPE_ARRAY_SIZE] = {
	{	C_SOURCE,			FTK_FC, FTK_FC, FTK_FC, NULL,  'c',  1, 0 },
	{	PREPROC_C,			FTK_FC, FTK_FC, FTK_FC, NULL,  'i',  1, 0 },
	{	CPP_SOURCE,			FTK_FC, FTK_FC, FTK_FC, "cpp", 'C',  1, 0 },
	{	PREPROC_CPP,		FTK_FC, FTK_FC, FTK_FC, NULL,  'I',  1, 0 },
	{	INDEP_TDF,			FTK_FC, FTK_FC, FTK_FC, NULL,  'j',  0, 0 },
	{	DEP_TDF,			FTK_FC, FTK_FC, FTK_FC, NULL,  't',  0, 0 },
	{	AS_SOURCE,			FTK_FC, FTK_FC, FTK_FC, NULL,  's',  1, 0 },
	{	BINARY_OBJ,			FTK_FC, FTK_FC, FTK_FC, NULL,  'o',  1, 0 },
	{	EXECUTABLE,			FTK_TN, FTK_FC, FTK_TN, NULL,  '\0', 0, 0 },
	{	PRETTY_TDF,			FTK_TC, FTK_FC, FTK_TN, NULL,  'p',  0, 0 },
	{	PL_TDF,				FTK_FC, FTK_FC, FTK_FC, NULL,  'P',  0, 0 },
	{	TDF_ARCHIVE,		FTK_TN, FTK_FC, FTK_TN, NULL,  'A',  0, 0 },
	{	MIPS_G_FILE,		FTK_FC, FTK_FC, FTK_FC, NULL,  'G',  1, 1 },
	{	MIPS_T_FILE,		FTK_FC, FTK_FC, FTK_FC, NULL,  'T',  1, 1 },
	{	C_SPEC,				FTK_FC, FTK_FC, FTK_FC, NULL,  'k',  1, 0 },
	{	CPP_SPEC,			FTK_FC, FTK_FC, FTK_FC, NULL,  'K',  1, 0 },
	{	STARTUP_FILE,		FTK_FC, FTK_FC, FTK_FC, NULL,  'h',  1, 1 },
	{	UNKNOWN_TYPE,		FTK_FC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },

		/* Dummy types */
		/* TODO only keep, keep_aux and stop are used? */
	{	INDEP_TDF_COMPLEX,	FTK_FC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },
	{	C_SPEC_1,			FTK_FC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },
	{	C_SPEC_2,			FTK_TC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },
	{	CPP_SPEC_1,			FTK_FC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },
	{	CPP_SPEC_2,			FTK_TC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },
	{	INDEP_TDF_AUX,		FTK_FC, FTK_FC, FTK_FC, NULL,  '\0', 0, 0 },
	{	BINARY_OBJ_AUX,		FTK_FC, FTK_FC, FTK_FC, NULL,  'b',  0, 0 }
};

boolean
table_isdummy(type) {
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

boolean
table_checker(enum filetype type) {
	assert(type != UNKNOWN_TYPE);
	assert(type != EXECUTABLE);
	assert(!table_isdummy(type));

	return filetype_table[type].checker;
}

boolean
table_stage(enum filetype type) {
	assert(type != UNKNOWN_TYPE);
	assert(type != EXECUTABLE);
	assert(!table_isdummy(type));

	return filetype_table[type].stage;
}

