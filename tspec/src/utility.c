/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#define _POSIX_SOURCE

#include <sys/types.h>
#include <sys/stat.h>

#include <stdarg.h>
#include <errno.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "name.h"
#include "utility.h"

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
		error(ERR_SERIOUS, "Illegal directory, %s", dir);
		return;
	}
#endif

	create_dir(dir);

	if (verbose) {
		IGNORE printf("Creating directory, %s ...\n", dir);
	}

	if (mkdir(dir, (mode_t) DIRMODE)) {
		error(ERR_SERIOUS, "Can't create directory, %s", dir);
		return;
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

