/*	$OpenPackages: ohash_int.h,v 1.6 2001/04/02 14:15:57 espie Exp $ */
/*	$OpenBSD: ohash_int.h,v 1.1 2001/03/02 13:27:07 espie Exp $	*/
/* $TenDRA$ */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ohash.h"

struct _ohash_record {
	hv_type		hv;
	const char 	*p;
};

#define DELETED		((const char *)h)
#define NONE		(h->size)

/* Don't bother changing the hash table if the change is small enough.  */
#define MINSIZE		(1UL << 4)
#define MINDELETED	4

