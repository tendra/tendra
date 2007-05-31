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


/**** dalloc.c --- Memory allocation and deallocation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the dynamic memory management facility specified in
 * the file "dalloc.h".  See that file for more information.
 *
 **** Change Log:
 * $Log: dalloc.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:28  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:09  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "dalloc.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_dalloc_no_memory = EXCEPTION("cannot allocate memory");

/*--------------------------------------------------------------------------*/

#ifdef PO_DALLOC_DEBUG_ALIGN

#define DALLOC_MAGIC 0x21436587
#define ALIGN(x) (((int) (((x) + (PO_DALLOC_DEBUG_ALIGN) - 1) / \
			  (PO_DALLOC_DEBUG_ALIGN))) * (PO_DALLOC_DEBUG_ALIGN))

/*--------------------------------------------------------------------------*/

typedef struct DallocDataT {
    char *			file;
    unsigned			line;
    size_t			size;
    int				magic;
} DallocDataT, *DallocDataP;

/*--------------------------------------------------------------------------*/

static size_t dalloc_data_size = ALIGN(sizeof(DallocDataT));

/*--------------------------------------------------------------------------*/

#ifdef __NeXT__

#undef TRUE
#undef FALSE
#include <mach/mach.h>

/*--------------------------------------------------------------------------*/

void *
X__dalloc_allocate(size_t size, size_t length, char * file, unsigned line)
{
    void * tmp;

    assert(size != 0);
    if (length == 0) {
	tmp = NULL;
    } else {
	size_t        real_size = (((size) * length) + dalloc_data_size);
	vm_address_t address;
	DallocDataP  data;
	ByteP        base;

	if (vm_allocate(task_self (), &address, (vm_size_t) real_size,
			TRUE) != KERN_SUCCESS) {
	    THROW(XX_dalloc_no_memory);
	    UNREACHED;
	}
	data        = (DallocDataP)address;
	base        = (ByteP)address;
	tmp         = (base + dalloc_data_size);
	data->file  = file;
	data->line  = line;
	data->size  = real_size;
	data->magic = DALLOC_MAGIC;
    }
    return (tmp);
}

void
X__dalloc_deallocate(void * ptr, char * file, unsigned line)
{
    if (ptr) {
	ByteP         pointer = (ByteP) ptr;
	DallocDataP   data    = (DallocDataP)(pointer - dalloc_data_size);
	vm_address_t  address = (vm_address_t) data;
	vm_size_t     size    = data->size;
	kern_return_t result;

	if (data->magic == 0) {
	    E_dalloc_multi_deallocate(ptr, file, line, data->file, data->line);
	    UNREACHED;
	} else if (data->magic != DALLOC_MAGIC) {
	    E_dalloc_corrupt_block (ptr, file, line);
	    UNREACHED;
	}
	data->magic = 0;
	result = vm_protect (task_self (), address, size, FALSE, VM_PROT_NONE);
	assert(result == KERN_SUCCESS);
    }
}

#else

void *
X__dalloc_allocate(size_t size, size_t length, char * file, unsigned line)
{
    void * tmp;

    assert(size != 0);
    if (length == 0) {
	tmp = NULL;
    } else {
	size_t       real_size = ((size * length) + dalloc_data_size);
	ByteP       base;
	DallocDataP data;

	if ((tmp = malloc(real_size)) == NULL) {
	    THROW(XX_dalloc_no_memory);
	    UNREACHED;
	}
	(void) memset (tmp, 0, real_size);
	data        = tmp;
	base        = tmp;
	tmp         = (base + dalloc_data_size);
	data->file  = file;
	data->line  = line;
	data->magic = DALLOC_MAGIC;
    }
    return (tmp);
}

void
X__dalloc_deallocate(void * ptr, char * file, unsigned line)
{
    if (ptr) {
	ByteP       pointer = (ByteP) ptr;
	DallocDataP data    = (DallocDataP)(pointer - dalloc_data_size);

	if (data->magic == 0) {
	    E_dalloc_multi_deallocate(ptr, file, line, data->file, data->line);
	    UNREACHED;
	} else if (data->magic != DALLOC_MAGIC) {
	    E_dalloc_corrupt_block (ptr, file, line);
	    UNREACHED;
	}
	data->magic = 0;
	free ((void *) data);
    }
}

#endif /* defined (__NeXT__) */

#else

void *
X__dalloc_allocate(size_t size, size_t length)
{
    void * tmp;

    assert(size != 0);
    if (length == 0) {
	tmp = NULL;
    } else if ((tmp = calloc(length, size)) == NULL) {
	THROW(XX_dalloc_no_memory);
	UNREACHED;
    }
    return (tmp);
}

#endif /* defined (PO_DALLOC_DEBUG_ALIGN) */
