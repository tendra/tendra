/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "cstring.h"
#include "msgcat.h"
#include "tenapp.h"

#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include "name.h"
#include "utility.h"


/*
 *    INPUT BUFFER
 *
 *    This buffer is used to store strings in various contexts.
 */

char *buffer = null;


/*
 *    ERROR VARIABLES
 *
 *    The value exit_status gives the overall status of the program.  It
 *    can be EXIT_SUCCESS or EXIT_FAILURE.  The variable progname gives
 *    the name of the program, which is used in error reports.  filename
 *    and line_no give the current file position.
 */

int no_errors = 0;
time_t progdate = 0;
char *filename = null;
int line_no = 1;


/*
 *    PRINT AN ERROR MESSAGE
 *
 *    This routine prints an error message s (a printf-style string,
 *    which may be followed by any number of arguments) of severity e
 *    (see utility.h).
 */

void
tspec_on_message(MSG_DATA *mp)
{
	switch (mp->usage) {
	case MSG_SEV_FATAL : {
	    exit_status = EXIT_FAILURE;
	    no_errors++;
	    break;
	}
	case MSG_SEV_INTERNAL : {
	    exit_status = EXIT_FAILURE;
	    no_errors++;
	    break;
	}
	case MSG_SEV_ERROR : {
	    exit_status = EXIT_FAILURE;
	    no_errors++;
	    break;
	}
	}
}


/*
 *    CONSTRUCT A STRING
 *
 *    This routine takes a printf string and a list of arguments, and
 *    does a sprintf into a permanent area of memory.
 */

char *
string_printf(char *s, ...) /* VARARGS */
{
	va_list args;
	va_start (args, s);
	IGNORE vsprintf (buffer, s, args);
	va_end (args);
	return (string_copy (buffer));
}


/*
 *    MODE OF DIRECTORIES CREATED
 *
 *    The mode of any created directories is determined.  On a truly POSIX
 *    compliant machine, the first branch is taken.
 */

#if defined (S_IRWXU) && defined (S_IRWXG) && defined (S_IRWXO)
#define  DIRMODE	(S_IRWXU | S_IRWXG | S_IRWXO)
#else
#if defined (S_IREAD) && defined (S_IWRITE) && defined (S_IEXEC)
#define  DIRMODE	(S_IREAD | S_IWRITE | S_IEXEC)
#else
#define  DIRMODE	0777
#endif
#endif


/*
 *    CREATE A DIRECTORY TO PUT A FILE IN
 *
 *    This routine recursively creates a directory to contain a file
 *    named nm.
 */

void
create_dir(char *nm)
{
	struct stat st;
	char *dir = dirname (nm);
	if (dir == null) return;
	if (stat (dir, &st) == 0) return;
#ifdef ENOENT
	if (errno != ENOENT) {
		MSG_illegal_directory (dir);
		return;
	}
#endif
	create_dir (dir);
	if (verbose) IGNORE printf ("Creating directory, %s ...\n", dir);
	if (mkdir (dir, DIRMODE)) {
		MSG_cant_create_directory (dir);
		return;
	}
	return;
}


/*
 *    CHECK A FILENAME
 *
 *    This routine checks the file name nm for excessively long components,
 *    which may cause problems on some machines.
 */

void
check_name(char *nm)
{
	char *p;
	int i = 0, n = 0;
	for (p = nm; *p; p++) {
		if (*p == '/') {
			if (i > n) n = i;
			i = 0;
		} else {
			i++;
		}
	}
	if (i > n) n = i;
	if (n > 14) {
		MSG_path_component_too_long (nm, n);
	}
	return;
}


/*
 *    FIND THE DATE STAMP ON A FILE
 *
 *    This routine finds the modification time of the file nm.  Zero is
 *    returned for inaccessible files.
 */

time_t
date_stamp(char *nm)
{
	struct stat st;
	if (nm && stat (nm, &st) == 0) return (st.st_mtime);
	return ((time_t) 0);
}
