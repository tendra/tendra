/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/dstring.h>

#include "adt/name-key.h"
#include "adt/library.h"


static void fmt_nstring(FILE *fp, void *p) {
	NStringT *nstring = p;

	UNUSED(fp);

	write_nstring(ostream_error, nstring);
}

static void fmt_namekey(FILE *fp, void *p) {
	NameKeyT *namekeyt = p;

	UNUSED(fp);

	write_name_key(ostream_error, namekeyt);
}

static void fmt_libcap(FILE *fp, void *p) {
	LibCapsuleT *libcap = p;

	UNUSED(fp);

	write_lib_capsule_full_name(ostream_error, libcap);
}

void fmt_init(void) {
	fmt_register('S', fmt_nstring);
	fmt_register('K', fmt_namekey);
	fmt_register('N', fmt_libcap);
}

