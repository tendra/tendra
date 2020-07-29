/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * dalloc.h - Memory allocation and deallocation.
 *
 * This file specifies the interface to a dynamic memory allocation facility.
 * All dynamically allocated objects are initialised with zeroes, but
 * non-integer typed fields will still need to be initialised explicitly.
 *
 *
 * If the macro ``PO_DALLOC_DEBUG_ALIGN'' is defined, then extra debugging
 * information is added into the space allocated to help detect errors in
 * memory management.  If this macro is defined, it requires two functions to
 * be provided:
 *
 *	void				E_dalloc_multi_deallocate
 *			(void *, char *, unsigned, char *,
 *				  unsigned);
 *	void				E_dalloc_corrupt_block
 *			(void *, char *, unsigned);
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
 * Exception:	XX_dalloc_no_memory
 *
 * This exception is raised if there is not enough memory to allocate an
 * object (or a vector of objects).
 */

#ifndef H_DALLOC
#define H_DALLOC

#include <stddef.h>
#include <stdlib.h>

#include <exds/common.h>
#include <exds/exception.h>


extern ExceptionT *XX_dalloc_no_memory;

#ifdef PO_DALLOC_DEBUG_ALIGN

void
E_dalloc_multi_deallocate(void *, char *, unsigned, char *, unsigned);

void
E_dalloc_corrupt_block(void *, char *, unsigned);

void *
X__dalloc_allocate(size_t, size_t, char *, unsigned);

void
X__dalloc_deallocate(void *, char *, unsigned);

#else

void *
X__dalloc_allocate(size_t, size_t);

#endif /* defined (PO_DALLOC_DEBUG_ALIGN) */


#ifdef PO_DALLOC_DEBUG_ALIGN

# define ALLOCATE(type) \
	((type *) X__dalloc_allocate(sizeof(type), (size_t) 1, __FILE__, \
		(unsigned)__LINE__))

# define ALLOCATE_VECTOR(type, length) \
	((type *) X__dalloc_allocate(sizeof(type), (size_t) (length), __FILE__, \
		(unsigned) __LINE__))

# define DEALLOCATE(pointer) \
	X__dalloc_deallocate((pointer), __FILE__, (unsigned) __LINE__)

#else

/*
 * This macro allocates an object of the specified type.  A pointer to the
 * object is returned.
 */
# define ALLOCATE(type) \
	((type *) X__dalloc_allocate(sizeof(type), (size_t) 1))

/*
 * This macro allocates a vector of the specified length containing objects of
 * the specified type.  A pointer to the first element in the vector is
 * returned.
 */
# define ALLOCATE_VECTOR(type, length) \
	((type *) X__dalloc_allocate(sizeof(type), (size_t) (length)))

/*
 * This macro deallocates the specified pointer.  If the pointer is a null
 * pointer (NULL), this does nothing.
 */
# define DEALLOCATE(pointer) free(pointer);

#endif /* defined (PO_DALLOC_DEBUG_ALIGN) */

#endif /* !defined (H_DALLOC) */
