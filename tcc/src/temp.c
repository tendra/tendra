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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <shared/error.h>
#include <shared/string.h>

#include "temp.h"
#include "flags.h"
#include "utility.h"
#include "filename.h"
#include "execute.h"
#include "archive.h"

#define RETRY_LIMIT 100

static void
temp_generateid(char *s, size_t z)
{
	size_t i;
	static const char set[] = "0123456789"
	                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (i = 0; i < z; i++) {
		s[i] = set[rand() % (sizeof set - 1)];
	}
}


static int
temp_retry(int *limit, char *buf, size_t sz, const char *dir, const char *prefix)
{
	assert(limit != NULL);
	assert(buf != NULL);
	assert(sz != 0);
	assert(dir != NULL);
	assert(prefix != NULL);

	/* TODO: stat() on dir */

	if (*limit == RETRY_LIMIT) {
		error(ERROR_FATAL, "%s: Random temporary retry limit reached", dir);
		return 0;
	}

	if (*limit == 10) {
		error(ERROR_WARNING, "%s: Random temporary space overcrowded", dir);
	}

	{
		char rnd[10];

		temp_generateid(rnd, sizeof rnd);

		/* TODO: bounds-check and error() */
		IGNORE sprintf(buf, "%s/%s-%.*s", dir, prefix, (int) sizeof rnd, rnd);
	}

	return 1;
}

/*
 * CREATE A TEMPORARY DIRECTORY
 */

const char *
temp_mkdir(const char *dir, const char *prefix)
{
	char buf[FILENAME_MAX];
	int l;

	for (l = 0; temp_retry(&l, buf, sizeof buf, dir, prefix); l++) {
		cmd_list(exec_mkdir);
		cmd_string(buf);

		IGNORE execute(no_filename, no_filename);
		if (!last_return) {
			return xstrdup(buf);
		}
	}

	error(ERROR_FATAL, "Can't create temporary directory: %s", buf);

	return NULL;
}


/*
 * CREATE A TEMPORARY FILE
 */

FILE *
temp_fopen(char **out, const char *dir, const char *prefix)
{
	char buf[FILENAME_MAX];
	int l;

	for (l = 0; temp_retry(&l, buf, sizeof buf, dir, prefix); l++) {
		FILE *p;

		if (dry_run) {
			p = (void *) &"unused";
		} else {
			p = fopen(buf, "a");
		}

		if (p != NULL) {
			*out = xstrdup(buf);
			return p;
		}
	}

	error(ERROR_FATAL, "Can't create temporary file: %s, buf");

	return NULL;
}

