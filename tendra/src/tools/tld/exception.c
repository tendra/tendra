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


/**** exception.c --- Exception handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the exception handling facility specified in the file
 * "exception.h".  See that file for more details.
 *
 **** Change Log:*/

/****************************************************************************/

#include "exception.h"
#include "msgcat.h"

//extern void			MSG_exception_unhandled(ExceptionP, CStringP, unsigned);
//extern void			MSG_exception_corrupt_handler(CStringP, unsigned);

/*--------------------------------------------------------------------------*/

HandlerP			X__exception_handler_stack = NIL (HandlerP);
ThrowDataT			X__exception_throw_data;

/*--------------------------------------------------------------------------*/

NoReturnT
X__exception_throw()
{
    static BoolT failing = FALSE;
    HandlerP     stack   = X__exception_handler_stack;

    if (failing) {
		abort ();
		UNREACHED;
    } else if (stack == NIL (HandlerP)) {
		failing = TRUE;
		MSG_exception_unhandled (X__exception_throw_data.exception,
							   X__exception_throw_data.file,
							   X__exception_throw_data.line);
		abort ();
		UNREACHED;
    }
#ifdef PO_EXCEPTION_STACK_DIRECTION
    if ((stack->magic_start != X__EXCEPTION_MAGIC) ||
		(stack->magic_end != X__EXCEPTION_MAGIC) ||
#if PO_EXCEPTION_STACK_DIRECTION > 0
		(((GenericP) stack) > ((GenericP) &stack)) ||
#endif /* PO_EXCEPTION_STACK_DIRECTION > 0 */
#if PO_EXCEPTION_STACK_DIRECTION < 0
		(((GenericP) stack) < ((GenericP) &stack)) ||
#endif /* PO_EXCEPTION_STACK_DIRECTION < 0 */
		(stack->next == stack)) {
		failing = TRUE;
		MSG_exception_corrupt_handler (stack->file, stack->line);
		abort ();
		UNREACHED;
    }
#endif /* defined (PO_EXCEPTION_STACK_DIRECTION) */
    longjmp (X__exception_handler_stack->buffer, 1);
    UNREACHED;
}

CStringP
exception_name(ExceptionP exc)
{
    return (exc);
}
