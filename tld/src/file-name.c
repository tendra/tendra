/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * file-name.c - File name manipulation routines.
 *
 * This file implements the file name manipulation facility specified in the
 * file "file-name.h".  See that file for more details.
 */

#include <stddef.h>
#include <string.h>

#include <exds/common.h>
#include <exds/cstring.h>

#include "file-name.h"

char *
file_name_basename(char * path)
{
    char * last = strrchr(path, '/');

    if (last) {
	return cstring_duplicate(last + 1);
    } else {
	return cstring_duplicate(path);
    }
}

char *
file_name_dirname(char * path)
{
    char * last = strrchr(path, '/');

    if (last) {
	return cstring_duplicate_prefix(path,(unsigned)(last - path));
    } else {
	return cstring_duplicate(path);
    }
}

char *
file_name_expand(const char * dir,			  const char * name, 
			  const char * suffix)
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
    return path;
}

BoolT
file_name_is_basename(const char * path)
{
    return !strchr(path, '/');
}

BoolT
file_name_is_absolute(char * path)
{
    return path[0] == '/';
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
