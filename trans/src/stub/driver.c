/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
/* XXX:
#include <stdlib.h>
#include <string.h>

#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>

#include <local/out.h>
#include <local/cpu.h>

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/main_reads.h>
#include <reader/readglob.h>

#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/exp.h>
*/

#include <main/driver.h>
#include <main/flags.h>

#define VERSION_STR "0.0"

static void
init(void)
{
}

static int
option(char c, const char *optarg)
{
	switch (c) {
	default:
		return -1;
	}

	return 0;
}

static int
switch_cpu(const char *optarg)
{
	switch (*optarg) {
	default:
		return -1;
	}

	return 0;
}

static void
unhas(void)
{
}

static void
cleanup(void)
{
}

struct driver driver = {
	VERSION_STR,

	init,
	unhas,
	NULL,
	NULL,
	cleanup,

	"",
	option,
	switch_cpu,

	0,
	0,
	0,
	0,
	0,
	0
};

