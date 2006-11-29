/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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


/**** c-check.c --- Routines to check grammar.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file contains routines to check that all actions and basic result
 * extraction functions are defined.
 *
 **** Change Log:
 * $Log: c-check.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:55:53  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:12  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-check.h"
#include "action.h"
#include "basic.h"
#include "entry.h"
#include "gen-errors.h"
#include "table.h"

/*--------------------------------------------------------------------------*/

static void
c_check_grammar_1(EntryP entry, GenericP gclosure)
{
    TypeP type;

    UNUSED(gclosure);
    switch (entry_type(entry))EXHAUSTIVE {
      case ET_RULE:
	break;
      case ET_BASIC: {
	  BasicP basic = entry_get_basic(entry);

	  if ((!types_equal_zero_tuple(basic_result(basic))) &&
	      (basic_get_result_code(basic) == NIL(GenericP))) {
	      E_basic_result_code_not_defined(entry_key(entry));
	  }
      }
	break;
      case ET_ACTION:
	if (action_get_code(entry_get_action(entry)) == NIL(GenericP)) {
	    E_action_code_not_defined(entry_key(entry));
	}
	break;
      case ET_TYPE:
	type = entry_get_type(entry);
	if (((type_get_assign_code(type) != NIL(GenericP)) ||
	     (type_get_param_assign_code(type) != NIL(GenericP)) ||
	     (type_get_result_assign_code(type) != NIL(GenericP))) &&
	    ((type_get_assign_code(type) == NIL(GenericP)) ||
	     (type_get_param_assign_code(type) == NIL(GenericP)) ||
	     (type_get_result_assign_code(type) == NIL(GenericP)))) {
	    E_type_code_not_defined(entry_key(entry));
	}
	break;
      case ET_NON_LOCAL:
      case ET_NAME:
      case ET_RENAME:
	break;
      case ET_PREDICATE:
	UNREACHED;
    }
}

/*--------------------------------------------------------------------------*/

void
c_check_grammar(GrammarP grammar)
{
    table_iter(grammar_table(grammar), c_check_grammar_1, NIL(GenericP));
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output")
 * eval: (include::add-path-entry "../c-output" "../generated")
 * end:
**/
