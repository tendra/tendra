/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/*
 * file-name.c - File name manipulation routines.
 *
 * This file implements the file name manipulation facility specified in the
 * file "file-name.h".  See that file for more details.
 */

#include <sys/stat.h>
#include <stddef.h>
#include <string.h>

#include "file-name.h"
#include <exds/common.h>
#include <exds/cstring.h>

char *
file_name_basename(char * path)
{
    char * last = strrchr(path, '/');

    if (last) {
	return(cstring_duplicate(last + 1));
    } else {
	return(cstring_duplicate(path));
    }
}

char *
file_name_dirname(char * path)
{
    char * last = strrchr(path, '/');

    if (last) {
	return(cstring_duplicate_prefix(path,(unsigned)(last - path)));
    } else {
	return(cstring_duplicate(path));
    }
}

char *
file_name_expand(char * dir,			  char * name, 
			  char * suffix)
{
    unsigned dir_length  = strlen(dir);
    unsigned name_length = strlen(name);
    unsigned suf_length  = (suffix ?(strlen(suffix)): 0);
    unsigned suf_extra   = (unsigned)(suffix ? 1 : 0);
    unsigned extra;
    unsigned length;
    char * path;
    char * tmp;

    if ((dir_length > 0) && (dir[dir_length - 1]!= '/')) {
	extra = 1;
    } else {
	extra = 0;
    }
    length = (dir_length + extra + name_length + suf_extra + suf_length + 1);
    path   = ALLOCATE_VECTOR(char, length);
    tmp    = path;
    if (dir_length > 0) {
	(void)memcpy((void *)tmp,(void *)dir,(size_t)dir_length);
	tmp += dir_length;
	if (dir[dir_length - 1]!= '/') {
	    tmp[0] = '/';
	    tmp++;
	}
    }
   (void)memcpy((void *)tmp,(void *)name,(size_t)name_length);
    tmp += name_length;
    if (suffix) {
	tmp[0] = '.';
	tmp++;
	(void)memcpy((void *)tmp,(void *)suffix,(size_t)suf_length);
	tmp += suf_length;
    }
    tmp[0] = '\0';
    return(path);
}

BoolT
file_name_is_basename(char * path)
{
    return(!!strchr(path, '/'));
}

BoolT
file_name_is_absolute(char * path)
{
    return(path[0] == '/');
}

void
file_name_populate(char * path)
{
    char * new_path = cstring_duplicate(path);
    char * tmp      = strchr(new_path, '/');

    if (tmp) {
	do {
	    *tmp = '\0';
	   (void)mkdir(new_path, 0755);
	    *tmp = '/';
	} while ((tmp = strchr(tmp + 1, '/')) != NULL);
    }
    DEALLOCATE(new_path);
}
