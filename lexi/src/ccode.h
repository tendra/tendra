/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_CCODE_H
#define LEXI_CCODE_H

#include "exds/common.h"
#include "exds/dstring.h"

struct NameTransT;

enum CcodeItemTypeT {
	Ccode_string,
	Ccode_identifier,
	Ccode_reference,
	Ccode_at
};

struct CcodeItemT {
	enum CcodeItemTypeT item_type;
	NStringT name;
	struct CcodeItemT *next;
};

struct CcodeT {
	struct CcodeItemT *head;
	struct CcodeItemT **tail;
};

void ccode_init(struct CcodeT *);
void ccode_assign(struct CcodeT *, struct CcodeT *);
void ccode_append_at(struct CcodeT *);
void ccode_append_ident(struct CcodeT *, NStringT *);
void ccode_append_ref(struct CcodeT *ccode, NStringT *i);
void ccode_append_string(struct CcodeT *, NStringT *);
void ccode_destroy(struct CcodeT *c);
void ccode_out(FILE *, struct CcodeT *, struct NameTransT *, int);

#endif

