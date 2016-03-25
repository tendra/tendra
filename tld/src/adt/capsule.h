/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * capsule.h - TDF capsule ADT.
 *
 * See the file "capsule.c" for more information.
 */

#ifndef H_CAPSULE
#define H_CAPSULE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"
#include "unit-table.h"

struct LibCapsuleT;

typedef enum {
    CT_INPUT,
    CT_OUTPUT
} CapsuleTypeT;

typedef struct CapsuleT {
    CapsuleTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    NStringT			contents;
    unsigned			capsule_index;
    char *			name;
    bool			complete;
} CapsuleT;

extern void			capsule_read_unit_set_file
(char *);
extern CapsuleT *		capsule_create_stream_input
(char *);
extern CapsuleT *		capsule_create_string_input
(char *, NStringT *);
extern CapsuleT *		capsule_create_stream_output
(char *);
extern char *			capsule_name
(CapsuleT *);
extern size_t			capsule_byte
(CapsuleT *);
extern void			capsule_read
(CapsuleT *, UnitTableT *, ShapeTableT *);
extern void			capsule_store_contents
(CapsuleT *);
extern NStringT *		capsule_contents
(CapsuleT *);
extern void			capsule_set_index
(CapsuleT *, unsigned);
extern unsigned			capsule_get_index
(CapsuleT *);
extern void			capsule_write
(CapsuleT *, UnitTableT *, ShapeTableT *);
extern void			capsule_close
(CapsuleT *);
extern unsigned			capsule_get_major_version
(void);
extern void			capsule_set_major_version
(unsigned);
extern unsigned			capsule_get_minor_version
(void);

#endif /* !defined (H_CAPSULE) */
