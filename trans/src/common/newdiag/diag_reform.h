/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef reform_DIAG_REFORM_H
#define reform_DIAG_REFORM_H

/*
 * This header is an attempt to reform the interfaces for diag/ and newdiag/
 * for the callbacks out to each architecture. The goal here is to be able to
 * (eventually) link both diag/ and newdiag/ simultaneously.
 */


#if DWARF
#include <dwarf/dwarf_types.h>
#endif


/*
 * This is used as a pointer for some architecures, and a numerical index
 * for others. Where it is a numerical index, it indexes into an array;
 * I think a pointer would suffice for those cases with a little work, too.
 * XXX: meanwhile architecture-specific knowledge here breaks abstraction
 */
#if DWARF
typedef dwarf_type_label *reform_OUTPUT_REC;
#elif defined(TRANS_80x86) || defined(TRANS_HPPA) || defined(TRANS_SPARC)
typedef long   reform_OUTPUT_REC;
#else
typedef void * reform_OUTPUT_REC;
#endif


/*
 * This is only called in one place and the interface could be normalised
 * somehow. dwarf_global just associates a dwarf_label field with a
 * diag_descriptor.
 */
#if DWARF
dwarf_global *   reform_NEW_DIAG_GLOBAL(reform_diag_descriptor *);
#else
reform_diag_descriptor *reform_NEW_DIAG_GLOBAL(reform_diag_descriptor *);
#endif


void reform_OUTPUT_GLOBALS_TAB(void);
void reform_OUTPUT_DIAG_TAGS(void);
void reform_INSPECT_FILENAME(reform_filename);


#endif

