/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ARCHIVE_H
#define ARCHIVE_H


/*
 * ARCHIVE OPTION MARKER
 *
 * This is used to indicate the end of the archive files, and the beginning of
 * the archive options in build_archive.
 */

#define ARCHIVE_OPTION_START	"+"


/*
 * ARCHIVE OPTIONS
 *
 * These flags control the inclusion of certain information in the archives.
 */

extern enum filetype archive_type;
extern void	process_archive_opt(void);


/*
 * PROCEDURE DECLARATIONS
 *
 * These routines include the general utilities for file manipulation plus the
 * procedures for building and splitting TDF archives.
 */

int remove_recursive(const char *);
int is_archive(const char *);
extern int	split_archive(const char *, filename **);
extern int	build_archive(const char *, const char **);
extern long	file_size(const char *);


#endif /* ARCHIVE_H */
