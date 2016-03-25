/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * file-name.h - File name manipulation routines.
 *
 * This file defines some file name manipulation routines.  It should be
 * replaced on operating systems with a different file name syntax to that
 * used here ('/' seperated path names).
 */

#ifndef H_FILE_NAME
#define H_FILE_NAME

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the file name
 * component of the specifed path.
 */
extern char *			file_name_basename
(char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the directory name
 * component of the specifed path.
 */
extern char *			file_name_dirname
(char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the path name
 * obtained by expanding the specified name in the specified dir.  If the
 * suffix is non nil, it is also appended to the path name, following the
 * suffix seperator character.
 */
extern char *			file_name_expand
(const char *, const char *, const char *);

/*
 * This function returns true if the specified path has no directory
 * component.
 */
extern bool			file_name_is_basename
(const char *);

/*
 * This function returns true if the specified path is an absolute path name.
 */
extern bool			file_name_is_absolute
(char *);

/*
 * This function tries to create all of the directories on the specified path.
 * The final component of the path is considered to be a file, and is not
 * created as a directory.  There is no confirmation of whether the function
 * succeeds or not - this must be determined in another manner.
 */
extern void			file_name_populate
(char *);

#endif /* !defined (H_FILE_NAME) */
