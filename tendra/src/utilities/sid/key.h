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


/*** key.h --- Key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "key.c" for more information.
 *
 *** Change Log:
 * $Log: key.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:21  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:35  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_KEY
#define H_KEY

#include "os-interface.h"
#include "dstring.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int KeyTypeT, *KeyTypeP;
#define KT_STRING	(0)
#define KT_NUMERIC	(1)
#else
typedef enum {
    KT_STRING,
    KT_NUMERIC
} KeyTypeT, *KeyTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct KeyT {
    KeyTypeT			type;
    NStringT			string;
    unsigned			number;
} KeyT, *KeyP;

/*--------------------------------------------------------------------------*/

extern void			key_init_from_string
	PROTO_S ((KeyP, NStringP, unsigned));
extern void			key_init_from_number
	PROTO_S ((KeyP, unsigned));
extern CmpT			key_compare
	PROTO_S ((KeyP, KeyP));
extern BoolT			key_is_string
	PROTO_S ((KeyP));
extern NStringP			key_get_string
	PROTO_S ((KeyP));
extern unsigned			key_get_number
	PROTO_S ((KeyP));
extern unsigned			key_hash_value
	PROTO_S ((KeyP));

extern void			write_key
	PROTO_S ((OStreamP, KeyP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define key_is_string(k) ((k)->type == KT_STRING)
#define key_is_number(k) ((k)->type == KT_NUMBER)
#define key_get_string(k) (&((k)->string))
#define key_get_number(k) ((k)->number)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_KEY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/

