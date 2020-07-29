/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rename-file.h - Routines for parsing rename file.
 *
 * See the file "rename-file.c" for more information.
 */

#ifndef H_RENAME_FILE
#define H_RENAME_FILE

#include "adt/arg-data.h"
#include <exds/common.h>
#include <exds/cstring.h>

extern void			rename_file_parse
(char *, ArgDataT *);

#endif /* !defined (H_RENAME_FILE) */
