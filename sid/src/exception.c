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


/**** exception.c --- Exception handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the exception handling facility specified in the file
 * "exception.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: exception.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:32  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:10  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include "exception.h"

extern void			E_exception_unhandled
	PROTO_S ((ExceptionP, CStringP, unsigned));
extern void			E_exception_corrupt_handler
	PROTO_S ((CStringP, unsigned));

/*--------------------------------------------------------------------------*/

HandlerP			X__exception_handler_stack = NIL (HandlerP);
ThrowDataT			X__exception_throw_data;

/*--------------------------------------------------------------------------*/

NoReturnT
X__exception_throw PROTO_Z ()
{
    static BoolT failing = FALSE;
    HandlerP     stack   = X__exception_handler_stack;

    if (failing) {
	abort ();
	UNREACHED;
    } else if (stack == NIL (HandlerP)) {
	failing = TRUE;
	E_exception_unhandled (X__exception_throw_data.exception,
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
	E_exception_corrupt_handler (stack->file, stack->line);
	abort ();
	UNREACHED;
    }
#endif /* defined (PO_EXCEPTION_STACK_DIRECTION) */
    longjmp (X__exception_handler_stack->buffer, 1);
    UNREACHED;
}

CStringP
exception_name PROTO_N ((exc))
	       PROTO_T (ExceptionP exc)
{
    return (exc);
}
