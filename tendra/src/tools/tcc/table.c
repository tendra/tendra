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

#include <stddef.h>

#include "table.h"

struct filetype_table filetype_table[TYPE_ARRAY_SIZE] = {
	{	C_SOURCE,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	PREPROC_C,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	CPP_SOURCE,			FTK_FC, FTK_FC, FTK_FC, "cpp" },
	{	PREPROC_CPP,		FTK_FC, FTK_FC, FTK_FC, NULL },
	{	INDEP_TDF,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	DEP_TDF,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	AS_SOURCE,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	BINARY_OBJ,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	EXECUTABLE,			FTK_TN, FTK_FC, FTK_TN, NULL },
	{	PRETTY_TDF,			FTK_TC, FTK_FC, FTK_TN, NULL },
	{	PL_TDF,				FTK_FC, FTK_FC, FTK_FC, NULL },
	{	TDF_ARCHIVE,		FTK_TN, FTK_FC, FTK_TN, NULL },
	{	MIPS_G_FILE,		FTK_FC, FTK_FC, FTK_FC, NULL },
	{	MIPS_T_FILE,		FTK_FC, FTK_FC, FTK_FC, NULL },
	{	C_SPEC,				FTK_FC, FTK_FC, FTK_FC, NULL },
	{	CPP_SPEC,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	STARTUP_FILE,		FTK_FC, FTK_FC, FTK_FC, NULL },
	{	UNKNOWN_TYPE,		FTK_FC, FTK_FC, FTK_FC, NULL },

		/* Dummy types */
		/* TODO only keep, keep_aux and stop are used? */
	{	INDEP_TDF_COMPLEX,	FTK_FC, FTK_FC, FTK_FC, NULL },
	{	C_SPEC_1,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	C_SPEC_2,			FTK_TC, FTK_FC, FTK_FC, NULL },
	{	CPP_SPEC_1,			FTK_FC, FTK_FC, FTK_FC, NULL },
	{	CPP_SPEC_2,			FTK_TC, FTK_FC, FTK_FC, NULL },
	{	INDEP_TDF_AUX,		FTK_FC, FTK_FC, FTK_FC, NULL },
	{	BINARY_OBJ_AUX,		FTK_FC, FTK_FC, FTK_FC, NULL }
};

int
table_keep(enum filetype type) {
	return filetype_table[type].keep;
}

int
table_stop(enum filetype type) {
	return filetype_table[type].stop;
}

const char *
table_suffix(enum filetype type) {
	/* TODO I think not for Dummy types */
	return filetype_table[type].suffix;
}

