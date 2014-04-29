/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#define _POSIX_SOURCE

#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "config.h"
#include "name.h"
#include "utility.h"

#ifdef FS_NO_MODE_T
typedef unsigned short mode_t;
#endif

#ifndef errno
extern int errno;
#endif

/*
 * INPUT BUFFER
 *
 * This buffer is used to store strings in various contexts.
 */
char *buffer = NULL;

/*
 * ERROR VARIABLES
 */
int warnings = 1;
time_t progdate = 0;
char *filename = NULL;

/*
 * CONSTRUCT A STRING
 *
 * This routine takes a printf string and a list of arguments, and
 * does a sprintf into a permanent area of memory.
 */
char *
string_printf(char *s, ...) /* VARARGS */
{
	va_list args;

	va_start(args, s);
	IGNORE vsprintf(buffer, s, args);
	va_end(args);

	return xstrdup(buffer);
}

/*
 * MODE OF DIRECTORIES CREATED
 *
 * The mode of any created directories is determined.  On a truly POSIX
 * compliant machine, the first branch is taken.
 */
#if defined(S_IRWXU) && defined(S_IRWXG) && defined(S_IRWXO)
#define DIRMODE (S_IRWXU | S_IRWXG | S_IRWXO)
#else
#if defined(S_IREAD) && defined(S_IWRITE) && defined(S_IEXEC)
#define DIRMODE (S_IREAD | S_IWRITE | S_IEXEC)
#else
#define DIRMODE 0777
#endif
#endif

/*
 * CREATE A DIRECTORY TO PUT A FILE IN
 *
 * This routine recursively creates a directory to contain a file
 * named nm.
 */
void
create_dir(char *nm)
{
	struct stat st;
	char *dir;

	dir = dirname(nm);
	if (dir == NULL) {
		return;
	}

	if (0 == stat(dir, &st)) {
		return;
	}

#ifdef ENOENT
	if (errno != ENOENT) {
		error(ERROR_SERIOUS, "Illegal directory, %s", dir);
		return;
	}
#endif

	create_dir(dir);

	if (verbose) {
		IGNORE printf("Creating directory, %s ...\n", dir);
	}

	if (mkdir(dir, (mode_t) DIRMODE)) {
		error(ERROR_SERIOUS, "Can't create directory, %s", dir);
		return;
	}
}

/*
 * CHECK A FILENAME
 *
 * This routine checks the file name nm for excessively long components,
 * which may cause problems on some machines.
 */
void
check_name(char *nm)
{
	char *p;
	int i = 0, n = 0;

	for (p = nm; *p; p++) {
		if (*p == '/') {
			if (i > n) {
				n = i;
			}

			i = 0;
			continue;
		}

		i++;
	}

	if (i > n) {
		n = i;
	}

	if (n > 14) {
		char *err = "The filename %s contains a component of length %d";
		error(ERROR_WARNING, err, nm, n);
	}
}

/*
 * FIND THE DATE STAMP ON A FILE
 *
 * This routine finds the modification time of the file nm.  Zero is
 * returned for inaccessible files.
 */
time_t
date_stamp(char *nm)
{
	struct stat st;

	if (nm && stat(nm, &st) == 0) {
		return st.st_mtime;
	}

	return (time_t) 0;
}

/*
 * SET THE CURRENT FILENAME
 *
 * This routine is a hack to avoid keeping the 'filename' variable
 * const-qualified, which would require sprinkling consts across the
 * program.
 */
void
set_filename(char *nm)
{
	crt_file_name = nm;
	filename = nm;
}

