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


/**** file-name.c --- File name manipulation routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the file name manipulation facility specified in the
 * file "file-name.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: file-name.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/07/05  11:58:40  smf
 * Marked possible unused function as such.  Reduced strength of checks.
 *
 * Revision 1.2  1994/12/12  11:45:37  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:14  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include "file-name.h"
#include "cstring.h"

/*--------------------------------------------------------------------------*/

CStringP
file_name_basename PROTO_N ((path))
		   PROTO_T (CStringP path)
{
    CStringP last = cstring_find_reverse (path, '/');

    if (last) {
	return (cstring_duplicate (last + 1));
    } else {
	return (cstring_duplicate (path));
    }
}

CStringP
file_name_dirname PROTO_N ((path))
		  PROTO_T (CStringP path)
{
    CStringP last = cstring_find_reverse (path, '/');

    if (last) {
	return (cstring_duplicate_prefix (path, (unsigned) (last - path)));
    } else {
	return (cstring_duplicate (path));
    }
}

CStringP
file_name_expand PROTO_N ((dir, name, suffix))
		 PROTO_T (CStringP dir X
			  CStringP name X
			  CStringP suffix)
{
    unsigned dir_length  = cstring_length (dir);
    unsigned name_length = cstring_length (name);
    unsigned suf_length  = (suffix ? (cstring_length (suffix)) : 0);
    unsigned suf_extra   = (unsigned) (suffix ? 1 : 0);
    unsigned extra;
    unsigned length;
    CStringP path;
    CStringP tmp;

    if ((dir_length > 0) && (dir [dir_length - 1] != '/')) {
	extra = 1;
    } else {
	extra = 0;
    }
    length = (dir_length + extra + name_length + suf_extra + suf_length + 1);
    path   = ALLOCATE_VECTOR (char, length);
    tmp    = path;
    if (dir_length > 0) {
	(void) memcpy ((GenericP) tmp, (GenericP) dir, (SizeT) dir_length);
	tmp += dir_length;
	if (dir [dir_length - 1] != '/') {
	    tmp [0] = '/';
	    tmp ++;
	}
    }
    (void) memcpy ((GenericP) tmp, (GenericP) name, (SizeT) name_length);
    tmp += name_length;
    if (suffix) {
	tmp [0] = '.';
	tmp ++;
	(void) memcpy ((GenericP) tmp, (GenericP) suffix, (SizeT) suf_length);
	tmp += suf_length;
    }
    tmp [0] = '\0';
    return (path);
}

BoolT
file_name_is_basename PROTO_N ((path))
		      PROTO_T (CStringP path)
{
    return (!cstring_contains (path, '/'));
}

BoolT
file_name_is_absolute PROTO_N ((path))
		      PROTO_T (CStringP path)
{
    return (path [0] == '/');
}

void
file_name_populate PROTO_N ((path))
		   PROTO_T (CStringP path)
{
#ifdef FS_MKDIR
    CStringP new_path = cstring_duplicate (path);
    CStringP tmp      = cstring_find (new_path, '/');

    if (tmp) {
	do {
	    *tmp = '\0';
	    (void) mkdir (new_path, 0755);
	    *tmp = '/';
	} while ((tmp = cstring_find (tmp + 1, '/')) != NIL (CStringP));
    }
    DEALLOCATE (new_path);
#else
    UNUSED (path);
#endif /* defined (FS_MKDIR) */
}
