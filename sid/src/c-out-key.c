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


/*** c-out-key.c --- Output of key ADT objects.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the identifier key output routines used by SID.
 *
 *** Change Log:
 * $Log: c-out-key.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:31  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:19  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-out-key.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "rstack.h"
#include "rule.h"
#include "syntax.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

static void
write_c_key PROTO_N ((ostream, contents, length))
	    PROTO_T (OStreamP ostream X
		     CStringP contents X
		     unsigned length)
{
    while (length --) {
	char c;

	switch (c = *contents ++) {
	  case '-':
	    write_cstring (ostream, "_H");
	    break;
	  case '_':
	    write_cstring (ostream, "__");
	    break;
	  case ':':
	    write_cstring (ostream, "_C");
	    break;
	  default:
	    if ((syntax_is_letter (c)) || (syntax_is_digit (c))) {
		write_char (ostream, c);
	    } else {
		write_cstring (ostream, "_X");
		write_unsigned (ostream, (unsigned) (unsigned char) c);
		write_char (ostream, '_');
	    }
	    break;
	}
    }
}

/*--------------------------------------------------------------------------*/

void
c_output_mapped_key PROTO_N ((info, entry))
		    PROTO_T (COutputInfoP info X
			     EntryP       entry)
{
    OStreamP ostream = c_out_info_ostream (info);
    NStringP mapping = entry_get_mapping (entry);
    BoolT    strict  = c_out_info_get_numeric_ids (info);

    if (mapping) {
	write_nstring (ostream, mapping);
    } else {
	KeyP     key    = entry_key (entry);
	NStringP prefix;

	switch (entry_type (entry)) EXHAUSTIVE {
	  case ET_TYPE:
	    prefix = c_out_info_type_prefix (info);
	    break;
	  case ET_RULE:
	    prefix = c_out_info_fn_prefix (info);
	    break;
	  case ET_BASIC:
	    prefix = c_out_info_terminal_prefix (info);
	    strict = FALSE;
	    break;
	  case ET_NON_LOCAL:
	    prefix = c_out_info_in_prefix (info);
	    break;
	  case ET_ACTION:
	  case ET_NAME:
	  case ET_RENAME:
	  case ET_PREDICATE:
	    UNREACHED;
	}
	write_nstring (ostream, prefix);
	if (key_is_string (key) && (!strict)) {
	    NStringP nstring = key_get_string (key);

	    write_c_key (ostream, nstring_contents (nstring),
			 nstring_length (nstring));
	} else {
	    write_unsigned (ostream, key_get_number (key));
	}
    }
}

void
c_output_key PROTO_N ((info, key, prefix))
	     PROTO_T (COutputInfoP info X
		      KeyP         key X
		      NStringP     prefix)
{
    OStreamP ostream = c_out_info_ostream (info);
    BoolT    strict  = c_out_info_get_numeric_ids (info);

    write_nstring (ostream, prefix);
    if (key_is_string (key) && (!strict)) {
	NStringP nstring = key_get_string (key);

	write_c_key (ostream, nstring_contents (nstring),
		     nstring_length (nstring));
    } else {
	write_unsigned (ostream, key_get_number (key));
    }
}

void
c_output_label_key PROTO_N ((info, key, label))
		   PROTO_T (COutputInfoP info X
			    KeyP         key X
			    unsigned     label)
{
    OStreamP ostream = c_out_info_ostream (info);
    NStringP prefix  = c_out_info_label_prefix (info);
    BoolT    strict  = c_out_info_get_numeric_ids (info);

    write_nstring (ostream, prefix);
    write_unsigned (ostream, label);
    write_char (ostream, '_');
    if (key_is_string (key) && (!strict)) {
	NStringP nstring = key_get_string (key);

	write_c_key (ostream, nstring_contents (nstring),
		     nstring_length (nstring));
    } else {
	write_unsigned (ostream, key_get_number (key));
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
