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


/*** key.c --- Key ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the identifier key routines used by SID.
 *
 *** Change Log:
 * $Log: key.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:19  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:35  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "key.h"

/*--------------------------------------------------------------------------*/

void
key_init_from_string PROTO_N ((key, string, number))
		     PROTO_T (KeyP     key X
			      NStringP string X
			      unsigned number)
{
    key->type   = KT_STRING;
    nstring_assign (&(key->string), string);
    key->number = number;
}

void
key_init_from_number PROTO_N ((key, number))
		     PROTO_T (KeyP     key X
			      unsigned number)
{
    key->type   = KT_NUMERIC;
    key->number = number;
}

CmpT
key_compare PROTO_N ((key1, key2))
	    PROTO_T (KeyP key1 X
		     KeyP key2)
{
    if ((key1->type) < (key2->type)) {
	return (CMP_LT);
    } else if ((key1->type) > (key2->type)) {
	return (CMP_GT);
    }
    switch (key1->type) EXHAUSTIVE {
      case KT_STRING:
	return (nstring_compare (&(key1->string), &(key2->string)));
      case KT_NUMERIC:
	if (key1->number < key2->number) {
	    return (CMP_LT);
	} else if (key1->number > key2->number) {
	    return (CMP_GT);
	} else {
	    return (CMP_EQ);
	}
    }
    UNREACHED;
}

#ifdef FS_FAST
#undef key_is_string
#endif /* defined (FS_FAST) */
BoolT
key_is_string PROTO_N ((key))
	      PROTO_T (KeyP key)
{
    return (key->type == KT_STRING);
}
#ifdef FS_FAST
#define key_is_string(k) ((k)->type == KT_STRING)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef key_get_string
#endif /* defined (FS_FAST) */
NStringP
key_get_string PROTO_N ((key))
	       PROTO_T (KeyP key)
{
    ASSERT (key->type == KT_STRING);
    return (&(key->string));
}
#ifdef FS_FAST
#define key_get_string(k) (&((k)->string))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef key_get_number
#endif /* defined (FS_FAST) */
unsigned
key_get_number PROTO_N ((key))
	       PROTO_T (KeyP key)
{
    return (key->number);
}
#ifdef FS_FAST
#define key_get_number(k) ((k)->number)
#endif /* defined (FS_FAST) */

unsigned
key_hash_value PROTO_N ((key))
	       PROTO_T (KeyP key)
{
    switch (key->type) EXHAUSTIVE {
      case KT_NUMERIC:
	return (key->number);
      case KT_STRING:
	return (nstring_hash_value (&(key->string)));
    }
    UNREACHED;
}

void
write_key PROTO_N ((ostream, key))
	  PROTO_T (OStreamP ostream X
		   KeyP     key)
{
    switch (key->type) EXHAUSTIVE {
      case KT_STRING:
	write_nstring (ostream, &(key->string));
	break;
      case KT_NUMERIC:
	write_unsigned (ostream, key->number);
	break;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
