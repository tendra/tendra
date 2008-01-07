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


/**** file-name.c --- File name manipulation routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the file name manipulation facility specified in the
 * file "file-name.h".  See that file for more details.
 *
 **** Change Log:*/

/****************************************************************************/

#include "file-name.h"
#include "cstring.h"

/*--------------------------------------------------------------------------*/

char *
file_name_basename(char *path)
{
	char *last = strrchr (path, '/');

	if (last) {
		return (string_copy (last + 1));
	} else {
		return (string_copy (path));
	}
}

char *
file_name_dirname(char *path)
{
	char *last = strrchr (path, '/');

	if (last) {
		return (string_ncopy (path, (unsigned) (last - path)));
	} else {
		return (string_copy (path));
	}
}

char *
file_name_expand(char *dir, char *name, char *suffix)
{
	unsigned dir_length  = strlen (dir);
	unsigned name_length = strlen (name);
	unsigned suf_length  = (suffix ? (strlen (suffix)) : 0);
	unsigned suf_extra   = (unsigned) (suffix ? 1 : 0);
	unsigned extra;
	unsigned length;
	char *path;
	char *tmp;

	if ((dir_length > 0) && (dir [dir_length - 1] != '/')) {
		extra = 1;
	} else {
		extra = 0;
	}
	length = (dir_length + extra + name_length + suf_extra + suf_length + 1);
	path   = ALLOCATE_VECTOR (char, length);
	tmp    = path;
	if (dir_length > 0) {
		(void) memcpy (tmp, dir, (size_t) dir_length);
		tmp += dir_length;
		if (dir [dir_length - 1] != '/') {
			tmp [0] = '/';
			tmp ++;
		}
	}
	(void) memcpy (tmp, name, (size_t) name_length);
	tmp += name_length;
	if (suffix) {
		tmp [0] = '.';
		tmp ++;
		(void) memcpy (tmp, suffix, (size_t) suf_length);
		tmp += suf_length;
	}
	tmp [0] = '\0';
	return (path);
}

BoolT
file_name_is_basename(char *path)
{
	return (strchr (path, '/') == NULL);
}

BoolT
file_name_is_absolute(char *path)
{
	return (path [0] == '/');
}

void
file_name_populate(char *path)
{
#ifdef FS_MKDIR
	char *new_path = cstring_duplicate (path);
	char *tmp      = cstring_find (new_path, '/');

	if (tmp) {
		do {
			*tmp = '\0';
			(void) mkdir (new_path, 0755);
			*tmp = '/';
		} while ((tmp = cstring_find (tmp + 1, '/')) != NULL);
	}
	DEALLOCATE (new_path);
#else
	UNUSED (path);
#endif /* defined (FS_MKDIR) */
}
