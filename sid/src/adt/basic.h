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


/*
 * basic.h --- Basic ADT.
 *
 * See the file "basic.c" for more information.
 */

#ifndef H_BASIC
#define H_BASIC

#include "../os-interface.h"
#include "../eds/bitvec.h"
#include "../eds/dalloc.h"
#include "../eds/dstring.h"
#include "entry.h"
#include "../grammar.h"
#include "../eds/ostream.h"
#include "types.h"

/*
 * A terminal is represented by a BasicT. The term basic used to refer to
 * terminals in previous versions of SID.
 */
typedef struct BasicT {
	/*
	 * This is used to generate the token definition when outputting the
	 * parser.
	 */
    unsigned			terminal;

	/*
	 * The tuple of types e.g. for a terminal declared by:
	 *
	 * 	identifier : () -> (:StringT);
	 *
	 * .result contains a tuple of one element that indicates the only
	 * result is a StringT.
	 */
    TypeTupleT			result;

	/*
	 * The code given in the %terminals% extraction section of the action
	 * information file (the .act file). This is stored as a void * because
	 * the true type will depend on the output language used.
	 */
    void *			result_code;

	/*
	 * Indicates if the terminal is ignored or not, i.e. declared with a
	 * preceding ! in the .sid file.
	 */
    BoolT			ignored;
} BasicT;

typedef struct BasicClosureT {
    BitVecT *			bitvec;
    GrammarT *			grammar;
} BasicClosureT;

extern BasicT *		basic_create(GrammarT *, BoolT);
extern unsigned		basic_terminal(BasicT *);
extern TypeTupleT *	basic_result(BasicT *);
extern void *		basic_get_result_code(BasicT *);
extern void		basic_set_result_code(BasicT *, void *);
extern BoolT		basic_get_ignored(BasicT *);
extern void		basic_iter_for_table(BasicT *, BoolT,
					     void(*)(EntryT *, void *),
					     void *);

extern void		write_basics(OStreamT *, BasicClosureT *);

#endif /* !defined (H_BASIC) */
