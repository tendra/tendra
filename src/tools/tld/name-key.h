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

extern void			name_key_init_string
	PROTO_S ((NameKeyP, NStringP));
extern void			name_key_init_unique
	PROTO_S ((NameKeyP, unsigned));
extern BoolT			name_key_parse_cstring
	PROTO_S ((NameKeyP, CStringP));
extern void			name_key_set_component
	PROTO_S ((NameKeyP, unsigned, NStringP));
extern NameKeyTypeT		name_key_type
	PROTO_S ((NameKeyP));
extern NStringP			name_key_string
	PROTO_S ((NameKeyP));
extern unsigned			name_key_components
	PROTO_S ((NameKeyP));
extern NStringP			name_key_get_component
	PROTO_S ((NameKeyP, unsigned));
extern unsigned			name_key_hash_value
	PROTO_S ((NameKeyP));
extern BoolT			name_key_equal
	PROTO_S ((NameKeyP, NameKeyP));
extern void			name_key_assign
	PROTO_S ((NameKeyP, NameKeyP));
extern void			name_key_copy
	PROTO_S ((NameKeyP, NameKeyP));
extern void			name_key_destroy
	PROTO_S ((NameKeyP));

extern void			write_name_key
	PROTO_S ((OStreamP, NameKeyP));

extern void			name_key_list_init
	PROTO_S ((NameKeyListP));
extern void			name_key_list_add
	PROTO_S ((NameKeyListP, NameKeyP));
extern NameKeyListEntryP	name_key_list_head
	PROTO_S ((NameKeyListP));
extern NameKeyP			name_key_list_entry_key
	PROTO_S ((NameKeyListEntryP));
extern NameKeyListEntryP	name_key_list_entry_next
	PROTO_S ((NameKeyListEntryP));

extern void			name_key_pair_list_init
	PROTO_S ((NameKeyPairListP));
extern BoolT			name_key_pair_list_add
	PROTO_S ((NameKeyPairListP, NameKeyP, NameKeyP));
extern NameKeyPairListEntryP	name_key_pair_list_head
	PROTO_S ((NameKeyPairListP));
extern NameKeyP			name_key_pair_list_entry_from
	PROTO_S ((NameKeyPairListEntryP));
extern NameKeyP			name_key_pair_list_entry_to
	PROTO_S ((NameKeyPairListEntryP));
extern NameKeyPairListEntryP	name_key_pair_list_entry_next
	PROTO_S ((NameKeyPairListEntryP));

#endif /* !defined (H_NAME_KEY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
