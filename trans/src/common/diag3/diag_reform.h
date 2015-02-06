/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef DIAG_REFORM_H
#define DIAG_REFORM_H

/*
 * This header is an attempt to reform the interfaces for diag3/ and diag4/
 * for the callbacks out to each architecture. The goal here is to be able to
 * (eventually) link both diag3/ and diag4/ simultaneously.
 */


#include <diag3/diagtypes1.h>

#if DWARF1
#include <dwarf1/dw1_types.h>
#endif


/*
 * This is used by common/reader to create common/diag types by the f_* API.
 */
#if DWARF1
typedef diag_descriptor diag_global;
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
#if DWARF1
typedef dwarf_type_label *OUTPUT_REC;
#elif defined(TRANS_X86) || defined(TRANS_HPPA) || defined(TRANS_SPARC)
typedef long   OUTPUT_REC;
#else
typedef void * OUTPUT_REC;
#endif


#if DWARF1
diag_descriptor *NEW_DIAG_GLOBAL(diag_descriptor *);
#else
diag_descriptor *NEW_DIAG_GLOBAL(diag_descriptor *);
#endif


void OUTPUT_GLOBALS_TAB(void);
void OUTPUT_DIAG_TAGS(void);
void INSPECT_FILENAME(filename);


#endif

