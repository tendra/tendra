/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-out-key.h - Output key ADT objects.
 *
 * See the file "c-out-key.c" for more information.
 */

#ifndef H_C_OUT_KEY
#define H_C_OUT_KEY

#include <exds/common.h>
#include <exds/exception.h>
#include "c-output.h"
#include <exds/dstring.h>
#include "../adt/entry.h"
#include "../adt/key.h"

void		c_output_mapped_key(COutputInfoT *, EntryT *);
void		c_output_key(COutputInfoT *, KeyT *, NStringT *);
void		c_output_label_key(COutputInfoT *, KeyT *, unsigned);
void		c_output_string_key(COutputInfoT *, KeyT *, NStringT *);

#endif /* !defined (H_C_OUT_KEY) */
