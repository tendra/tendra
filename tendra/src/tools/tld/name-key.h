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


/*** name-key.h --- External name key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "name-key.c" for more information.
 *
 *** Change Log:*/

/****************************************************************************/

#ifndef H_NAME_KEY
#define H_NAME_KEY

#include "config.h"
#include "cstring.h"
#include "dstring.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int NameKeyTypeT, *NameKeyTypeP;
#define KT_STRING	(0)
#define KT_UNIQUE	(1)
#else
typedef enum {
	KT_STRING,
	KT_UNIQUE
} NameKeyTypeT, *NameKeyTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct NameUniqueT {
	unsigned			length;
	NStringP			components;
} NameUniqueT, *NameUniqueP;

typedef struct NameKeyT {
	NameKeyTypeT		type;
	union {
		NStringT		string;
		NameUniqueT		unique;
	} u;
} NameKeyT, *NameKeyP;

typedef struct NameKeyListEntryT {
	struct NameKeyListEntryT   *next;
	NameKeyT			key;
} NameKeyListEntryT, *NameKeyListEntryP;

typedef struct NameKeyListT {
	NameKeyListEntryP		head;
} NameKeyListT, *NameKeyListP;

typedef struct NameKeyPairListEntryT {
	struct NameKeyPairListEntryT *next;
	NameKeyT			  from;
	NameKeyT			  to;
} NameKeyPairListEntryT, *NameKeyPairListEntryP;

typedef struct NameKeyPairListT {
	NameKeyPairListEntryP		head;
} NameKeyPairListT, *NameKeyPairListP;

/*--------------------------------------------------------------------------*/

extern void			name_key_init_string(NameKeyP, NStringP);
extern void			name_key_init_unique(NameKeyP, unsigned);
extern BoolT			name_key_parse_cstring(NameKeyP, char *);
extern void			name_key_set_component(NameKeyP, unsigned, NStringP);
extern NameKeyTypeT		name_key_type(NameKeyP);
extern NStringP			name_key_string(NameKeyP);
extern unsigned			name_key_components(NameKeyP);
extern NStringP			name_key_get_component(NameKeyP, unsigned);
extern unsigned			name_key_hash_value(NameKeyP);
extern BoolT			name_key_equal(NameKeyP, NameKeyP);
extern void			name_key_assign(NameKeyP, NameKeyP);
extern void			name_key_copy(NameKeyP, NameKeyP);
extern void			name_key_destroy(NameKeyP);

extern void			write_name_key(OStreamP, NameKeyP);

extern void			name_key_list_init(NameKeyListP);
extern void			name_key_list_add(NameKeyListP, NameKeyP);
extern NameKeyListEntryP	name_key_list_head(NameKeyListP);
extern NameKeyP			name_key_list_entry_key(NameKeyListEntryP);
extern NameKeyListEntryP	name_key_list_entry_next(NameKeyListEntryP);

extern void			name_key_pair_list_init(NameKeyPairListP);
extern BoolT			name_key_pair_list_add(NameKeyPairListP, NameKeyP, NameKeyP);
extern NameKeyPairListEntryP	name_key_pair_list_head(NameKeyPairListP);
extern NameKeyP			name_key_pair_list_entry_from(NameKeyPairListEntryP);
extern NameKeyP			name_key_pair_list_entry_to(NameKeyPairListEntryP);
extern NameKeyPairListEntryP	name_key_pair_list_entry_next(NameKeyPairListEntryP);

#endif /* !defined (H_NAME_KEY) */
