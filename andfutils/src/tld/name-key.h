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


/*** name-key.h --- External name key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "name-key.c" for more information.
 *
 *** Change Log:
 * $Log: name-key.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:40  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:36  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_NAME_KEY
#define H_NAME_KEY

#include "os-interface.h"
#include "cstring.h"
#include "dstring.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int NameKeyTypeT, *NameKeyTypeT *
#define KT_STRING	(0)
#define KT_UNIQUE	(1)
#else
typedef enum {
    KT_STRING,
    KT_UNIQUE
} NameKeyTypeT;
#endif /* defined (FS_NO_ENUM) */

typedef struct NameUniqueT {
    unsigned			length;
    NStringT *		components;
} NameUniqueT;

typedef struct NameKeyT {
    NameKeyTypeT		type;
    union {
	NStringT		string;
	NameUniqueT		unique;
    } u;
} NameKeyT;

typedef struct NameKeyListEntryT {
    struct NameKeyListEntryT   *next;
    NameKeyT			key;
} NameKeyListEntryT;

typedef struct NameKeyListT {
    NameKeyListEntryT *	head;
} NameKeyListT;

typedef struct NameKeyPairListEntryT {
    struct NameKeyPairListEntryT *next;
    NameKeyT			  from;
    NameKeyT			  to;
} NameKeyPairListEntryT;

typedef struct NameKeyPairListT {
    NameKeyPairListEntryT *	head;
} NameKeyPairListT;

/*--------------------------------------------------------------------------*/

extern void			name_key_init_string
(NameKeyT *, NStringT *);
extern void			name_key_init_unique
(NameKeyT *, unsigned);
extern BoolT			name_key_parse_cstring
(NameKeyT *, char *);
extern void			name_key_set_component
(NameKeyT *, unsigned, NStringT *);
extern NameKeyTypeT		name_key_type
(NameKeyT *);
extern NStringT *		name_key_string
(NameKeyT *);
extern unsigned			name_key_components
(NameKeyT *);
extern NStringT *		name_key_get_component
(NameKeyT *, unsigned);
extern unsigned			name_key_hash_value
(NameKeyT *);
extern BoolT			name_key_equal
(NameKeyT *, NameKeyT *);
extern void			name_key_assign
(NameKeyT *, NameKeyT *);
extern void			name_key_copy
(NameKeyT *, NameKeyT *);
extern void			name_key_destroy
(NameKeyT *);

extern void			write_name_key
(OStreamT *, NameKeyT *);

extern void			name_key_list_init
(NameKeyListT *);
extern void			name_key_list_add
(NameKeyListT *, NameKeyT *);
extern NameKeyListEntryT *name_key_list_head
(NameKeyListT *);
extern NameKeyT *		name_key_list_entry_key
(NameKeyListEntryT *);
extern NameKeyListEntryT *name_key_list_entry_next
(NameKeyListEntryT *);

extern void			name_key_pair_list_init
(NameKeyPairListT *);
extern BoolT			name_key_pair_list_add
(NameKeyPairListT *, NameKeyT *, NameKeyT *);
extern NameKeyPairListEntryT *name_key_pair_list_head
(NameKeyPairListT *);
extern NameKeyT *		name_key_pair_list_entry_from
(NameKeyPairListEntryT *);
extern NameKeyT *		name_key_pair_list_entry_to
(NameKeyPairListEntryT *);
extern NameKeyPairListEntryT *name_key_pair_list_entry_next
(NameKeyPairListEntryT *);

#endif /* !defined (H_NAME_KEY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
