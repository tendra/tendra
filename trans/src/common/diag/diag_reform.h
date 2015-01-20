/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAG_REFORM_H
#define DIAG_REFORM_H

/*
 * This header is an attempt to reform the interfaces for diag/ and newdiag/
 * for the callbacks out to each architecture. The goal here is to be able to
 * (eventually) link both diag/ and newdiag/ simultaneously.
 */


#include <diag/diagtypes1.h>

#if DWARF
#include <dwarf/dwarf_types.h>
#endif


/*
 * This is used by common/reader to create common/diag types by the f_* API.
 */
#if DWARF
typedef dwarf_global    diag_global;
#else
/* XXX: dwarf_diag_config.h has this as int! */
typedef diag_descriptor diag_global;
#endif


/*
 * This is used as a pointer for some architecures, and a numerical index
 * for others. Where it is a numerical index, it indexes into an array;
 * I think a pointer would suffice for those cases with a little work, too.
 * XXX: meanwhile architecture-specific knowledge here breaks abstraction
 */
#if DWARF
typedef dwarf_type_label *OUTPUT_REC;
#elif defined(TRANS_X86) || defined(TRANS_HPPA) || defined(TRANS_SPARC)
typedef long   OUTPUT_REC;
#else
typedef void * OUTPUT_REC;
#endif


/*
 * This is only called in one place and the interface could be normalised
 * somehow. dwarf_global just associates a dwarf_label field with a
 * diag_descriptor.
 */
#if DWARF
dwarf_global *   NEW_DIAG_GLOBAL(diag_descriptor *);
#else
diag_descriptor *NEW_DIAG_GLOBAL(diag_descriptor *);
#endif


void OUTPUT_GLOBALS_TAB(void);
void OUTPUT_DIAG_TAGS(void);
void INSPECT_FILENAME(filename);


#endif

