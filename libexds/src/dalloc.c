/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * dalloc.c - Memory allocation and deallocation.
 *
 * This file implements the dynamic memory management facility specified in
 * the file "dalloc.h".  See that file for more information.
 */

/*
 * TODO Perhaps this can be replaced with our centralised xalloc.h if
 * the exception system is also centralised?
 *
 * TODO I don't see why .base is ByteT and not char *. A few other things
 * ought to be void *, too.
 */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>

ExceptionT *XX_dalloc_no_memory = EXCEPTION("cannot allocate memory");

#ifdef PO_DALLOC_DEBUG_ALIGN

#define DALLOC_MAGIC 0x21436587
#define ALIGN(x) (((int) (((x) + (PO_DALLOC_DEBUG_ALIGN) - 1) / \
	(PO_DALLOC_DEBUG_ALIGN))) * (PO_DALLOC_DEBUG_ALIGN))

typedef struct DallocDataT {
	char *file;
	unsigned line;
	size_t size;
	int magic;
} DallocDataT;

static size_t dalloc_data_size = ALIGN(sizeof(DallocDataT));

#ifdef __NeXT__

#undef true
#undef false
#include <mach/mach.h>

void *
X__dalloc_allocate(size_t size, size_t length, const char *file, unsigned line)
{
	size_t real_size;
	vm_address_t address;
	DallocDataT *data;
	ByteT *base;

	assert(size != 0);
	if (length == 0) {
		return NULL;
	}

	real_size = (size * length) + dalloc_data_size;

	if (vm_allocate(task_self(), &address, (vm_size_t) real_size, true)
		!= KERN_SUCCESS) {

		THROW(XX_dalloc_no_memory);
		UNREACHED;
	}

	data        = (DallocDataT *) address;
	base        = (ByteT *) address;
	data->file  = file;
	data->line  = line;
	data->size  = real_size;
	data->magic = DALLOC_MAGIC;

	return base + dalloc_data_size;
}

void
X__dalloc_deallocate(void *ptr, const char *file, unsigned line)
{
	ByteT *pointer;
	DallocDataT *data;
	vm_address_t address;
	vm_size_t size;
	kern_return_t result;

	if (!ptr) {
		return;
	}

	pointer = (ByteT *) ptr;
	data    = (DallocDataT *) (pointer - dalloc_data_size);
	address = (vm_address_t) data;
	size    = data->size;

	if (data->magic == 0) {
		E_dalloc_multi_deallocate(ptr, file, line, data->file, data->line);
		UNREACHED;
	} else if (data->magic != DALLOC_MAGIC) {
		E_dalloc_corrupt_block (ptr, file, line);
		UNREACHED;
	}

	data->magic = 0;
	result = vm_protect (task_self(), address, size, false, VM_PROT_NONE);
	assert(result == KERN_SUCCESS);
}

#else

void *
X__dalloc_allocate(size_t size, size_t length, const char *file, unsigned line)
{
	size_t real_size;
	ByteT *base;
	DallocDataT *data;
	void *tmp;

	assert(size != 0);
	if (length == 0) {
		tmp = NULL;
	}

	real_size = size * length + dalloc_data_size;

	if ((tmp = malloc(real_size)) == NULL) {
		THROW(XX_dalloc_no_memory);
		UNREACHED;
	}

	IGNORE memset(tmp, 0, real_size);
	data        = tmp;
	base        = tmp;
	data->file  = file;
	data->line  = line;
	data->magic = DALLOC_MAGIC;

	return base + dalloc_data_size;
}

void
X__dalloc_deallocate(void *ptr, const char *file, unsigned line)
{
	ByteT *pointer;
	DallocDataT *data;

	if (!ptr) {
		return;
	}

	pointer = (ByteT *) ptr;
	data    = (DallocDataT *) (pointer - dalloc_data_size);

	if (data->magic == 0) {
		E_dalloc_multi_deallocate(ptr, file, line, data->file, data->line);
		UNREACHED;
	} else if (data->magic != DALLOC_MAGIC) {
		E_dalloc_corrupt_block (ptr, file, line);
		UNREACHED;
	}

	data->magic = 0;
	free(data);
}

#endif /* defined (__NeXT__) */

#else

void *
X__dalloc_allocate(size_t size, size_t length)
{
	void *tmp;

	assert(size != 0);
	if (length == 0) {
		return NULL;
	}

	if ((tmp = calloc(length, size)) == NULL) {
		THROW(XX_dalloc_no_memory);
		UNREACHED;
	}

	return tmp;
}

#endif /* defined (PO_DALLOC_DEBUG_ALIGN) */

