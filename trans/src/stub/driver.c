/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

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
	UNUSED(optarg);

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

	local_translate_capsule,

	0,
	0,
	0,
	0,
	0,
	0
};

