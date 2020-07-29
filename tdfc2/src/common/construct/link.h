/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LINK_INCLUDED
#define LINK_INCLUDED


/*
 * DISTINGUISHED LINKAGE VALUES
 *
 * These values are used as distinguished linkage numbers for use in the
 * output routines. Unassigned linkage numbers are given the value LINK_NONE.
 * External linkage numbers are or-ed with the value LINK_EXTERN to
 * distinguish them from internal linkage numbers.
 */

#define LINK_NONE		((ulong)0xffffffffUL)
#define LINK_EXTERN		((ulong)0x80000000UL)
#define LINK_ZERO		((ulong)0xfffffffeUL)
#define LINK_TOKDEF		((ulong)0xfffffffdUL)


#endif
