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


/**** dalloc.h --- Memory allocation and deallocation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a dynamic memory allocation facility.
 * All dynamically allocated objects are initialised with zeroes, but
 * non-integer typed fields will still need to be initialised explicitly.
 *
 * If the macro ``PO_DALLOC_DEBUG_ALIGN'' is defined, then extra debugging
 * information is added into the space allocated to help detect errors in
 * memory management.  If this macro is defined, it requires two functions to
 * be provided:
 *
 *	void				E_dalloc_multi_deallocate
 *			PROTO_S ((GenericP, CStringP, unsigned, CStringP,
 *				  unsigned));
 *	void				E_dalloc_corrupt_block
 *			PROTO_S ((GenericP, CStringP, unsigned));
 *
 * The first function will be called if a block is deallocated more than once.
 * It takes the block's address, and the file and line number of the
 * deallocation and allocation of the block as arguments.  The second function
 * is called if a block is corrupt when deallocated.  It takes the address of
 * the block and the file and line number of the deallocation of the block as
 * arguments.  Neither of these functions should return.
 *
 * This debugging mode should not be used on software that is shipped.  It has
 * machine specific implementations, and may be quite inefficient.
 *
 ***=== MACROS ===============================================================
 *
 ** Macro:	ALLOCATE (type)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This macro allocates an object of the specified type.  A pointer to the
 * object is returned.
 *
 ** Macro:	ALLOCATE_VECTOR (type, length)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This macro allocates a vector of the specified length containing objects of
 * the specified type.  A pointer to the first element in the vector is
 * returned.
 *
 ** Macro:	DEALLOCATE (pointer)
 ** Exceptions:
 *
 * This macro deallocates the specified pointer.  If the pointer is a null
 * pointer (``NIL (SomeTypeP)''), this does nothing.
 *
 ***=== EXCEPTIONS ===========================================================
 *
 ** Exception:	XX_dalloc_no_memory
 *
 * This exception is raised if there is not enough memory to allocate an
 * object (or a vector of objects).
 *
 **** Change Log:*/

/****************************************************************************/

#ifndef H_DALLOC
#define H_DALLOC

#include "config.h"
#include "exception.h"

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_dalloc_no_memory;

/*--------------------------------------------------------------------------*/

#ifdef PO_DALLOC_DEBUG_ALIGN

extern void			E_dalloc_multi_deallocate(GenericP, CStringP, unsigned, CStringP, unsigned);
extern void			E_dalloc_corrupt_block(GenericP, CStringP, unsigned);
extern GenericP			X__dalloc_allocate(size_t, size_t, CStringP, unsigned);
extern void			X__dalloc_deallocate(GenericP, CStringP, unsigned);

#else

extern GenericP			X__dalloc_allocate(size_t, size_t);

#endif /* defined (PO_DALLOC_DEBUG_ALIGN) */

/*--------------------------------------------------------------------------*/

#ifdef PO_DALLOC_DEBUG_ALIGN

#define ALLOCATE(type) \
((type *) X__dalloc_allocate (sizeof (type), (size_t) 1, __FILE__, \
			      (unsigned) __LINE__))

#define ALLOCATE_VECTOR(type,length) \
((type *) X__dalloc_allocate (sizeof (type), (size_t) (length), __FILE__, \
			      (unsigned) __LINE__))

#define DEALLOCATE(pointer) \
X__dalloc_deallocate ((GenericP) (pointer), __FILE__, (unsigned) __LINE__)

#else

#define ALLOCATE(type) \
((type *) X__dalloc_allocate (sizeof (type), (size_t) 1))

#define ALLOCATE_VECTOR(type,length) \
((type *) X__dalloc_allocate (sizeof (type), (size_t) (length)))

#define DEALLOCATE(pointer) \
if (pointer) {free ((GenericP) (pointer));}

#endif /* defined (PO_DALLOC_DEBUG_ALIGN) */

#endif /* !defined (H_DALLOC) */
