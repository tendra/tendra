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


/*** key.h --- Key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "key.c" for more information.
 *
 *** Change Log:*/

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

