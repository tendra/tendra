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


/**** file-name.h --- File name manipulation routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file defines some file name manipulation routines.  It should be
 * replaced on operating systems with a different file name syntax to that
 * used here ('/' seperated path names).
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	CStringP		file_name_basename
 *			PROTO_S ((CStringP path))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the file name
 * component of the specifed path.
 *
 ** Function:	CStringP		file_name_dirname
 *			PROTO_S ((CStringP path))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the directory name
 * component of the specifed path.
 *
 ** Function:	CStringP		file_name_expand
 *			PROTO_S ((CStringP dir, CStringP name,
 *				  CStringP suffix))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the path name
 * obtained by expanding the specified name in the specified dir.  If the
 * suffix is non nil, it is also appended to the path name, following the
 * suffix seperator character.
 *
 ** Function:	CStringP		file_name_is_basename
 *			PROTO_S ((CStringP path))
 ** Exceptions:
 *
 * This function returns true if the specified path has no directory
 * component.
 *
 ** Function:	CStringP		file_name_is_absolute
 *			PROTO_S ((CStringP path))
 ** Exceptions:
 *
 * This function returns true if the specified path is an absolute path name.
 *
 ** Function:	void			file_name_populate
 *			PROTO_S ((CStringP path))
 ** Exceptions:
 *
 * This function tries to create all of the directories on the specified path.
 * The final component of the path is considered to be a file, and is not
 * created as a directory.  There is no confirmation of whether the function
 * succeeds or not - this must be determined in another manner.
 *
 **** Change Log:
 * $Log: file-name.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:39  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:14  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#ifndef H_FILE_NAME
#define H_FILE_NAME

#include "os-interface.h"
#include "dalloc.h"

/*--------------------------------------------------------------------------*/

extern CStringP			file_name_basename
	PROTO_S ((CStringP));
extern CStringP			file_name_dirname
	PROTO_S ((CStringP));
extern CStringP			file_name_expand
	PROTO_S ((CStringP, CStringP, CStringP));
extern BoolT			file_name_is_basename
	PROTO_S ((CStringP));
extern BoolT			file_name_is_absolute
	PROTO_S ((CStringP));
extern void			file_name_populate
	PROTO_S ((CStringP));

#endif /* !defined (H_FILE_NAME) */
