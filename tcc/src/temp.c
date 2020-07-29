/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include "temp.h"
#include "flags.h"
#include "utility.h"
#include "filename.h"
#include "execute.h"
#include "environ.h"
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
		error(ERR_FATAL, "%s: Random temporary retry limit reached", dir);
		return 0;
	}

	if (*limit == 10) {
		error(ERR_WARN, "%s: Random temporary space overcrowded", dir);
	}

	{
		char rnd[10];

		temp_generateid(rnd, sizeof rnd);

		if (strlen(dir) + 1 + strlen(prefix) + 1 + sizeof rnd + 1 > FILENAME_MAX) {
			error(ERR_FATAL, "%s: Random temporary directory too long", dir);
			return 0;
		}

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
		cmd_env("MKDIR");
		cmd_string(buf);

		IGNORE execute(no_filename, no_filename);
		if (!last_return) {
			return xstrdup(buf);
		}
	}

	error(ERR_FATAL, "Can't create temporary directory: %s", buf);

	return NULL;
}


/*
 * CREATE A TEMPORARY FILE
 */

FILE *
temp_fopen(char *buf, size_t bufsz, const char *name, const char *mode)
{
	FILE *f;

	assert(name != NULL);
	assert(*name != '\0');

	if (tempdir == NULL) {
		tempdir = temp_mkdir(envvar_get(envvars, "PREFIX_TMP"), progname);
	}

	if (strlen(tempdir) + 1 + strlen(name) + 1 > bufsz) {
		error(ERR_FATAL, "Temporary filename too long");
	}

	if (dry_run) {
		return (void *) &"unused";
	}

	IGNORE sprintf(buf, "%s/%s", tempdir, name);

	f = fopen(buf, mode);
	if (f == NULL) {
		error(ERR_FATAL, "%s: %s", buf, strerror(errno));
	}

	return f;
}

