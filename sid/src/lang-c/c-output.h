/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * c-output.h - Output routines.
 *
 * See the file "c-output.c" for more information.
 */

#ifndef H_C_OUTPUT
#define H_C_OUTPUT

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include "../adt/entry-list.h"
#include "../grammar.h"
#include "../adt/key.h"
#include <exds/ostream.h>
#include "c-out-info.h"

#define C_INDENT_STEP		((unsigned)1)
#define C_INDENT_FOR_ERROR	C_INDENT_STEP
#define C_INDENT_FOR_PARAM	((unsigned)1)
#define C_INDENT_FOR_CASE	((unsigned)1)
#define C_INDENT_FOR_LABEL	((unsigned)1)

void		c_output_parser(COutputInfoT *, GrammarT *);
void		c_output_header(COutputInfoT *, GrammarT *);
void		c_output_location(COutputInfoT *, const char *, unsigned);
void		c_output_key_message(COutputInfoT *, char *, KeyT *,
					     char *, unsigned);
unsigned		c_out_next_label(void);
void		c_output_open(COutputInfoT *, unsigned);
void		c_output_close(COutputInfoT *, unsigned);
void		c_output_terminal_entry(COutputInfoT *, EntryT *);

#endif /* !defined (H_C_OUTPUT) */
