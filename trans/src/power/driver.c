/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/getopt.h>

#include <local/ash.h>
#include <local/cpu.h>

#include <reader/readglob.h>

#include <construct/installglob.h>
#include <construct/machine.h>

#include <main/flags.h>
#include <main/driver.h>

#include "procrec.h"
#include "macro.h"
#include "addr.h"
#include "make_code.h"
#include "dynamic_init.h"

#define VERSION_STR "4.26"

enum cpu cpu;

static void
init(void)
{
	cpu       = CPU_COMMON;
	endian    = ENDIAN_BIG;
	assembler = ASM_IBM;
	format    = FORMAT_XCOFF;
	diag      = DIAG_NONE;
	cconv     = CCONV_XLC;
	abi       = ABI_POWER;

	/*
	 * This makes the output easier to read, rather than the traditional
	 * integers for register names.
	 */
	do_macros = 0;

	/*
	 * procs delivering structs recast to extra param
	 * for call struct/union return convention
	 */
	redo_structfns = true;

	do_profile            = false; /* Produce profiling info */
	separate_units        = false; /* Translate units separately */
	all_variables_visible = false; /* Set vis flag for all declarations */
	strict_fl_div         = true;  /* Don't mult by 1/constant */
	round_after_flop      = true; /* Round every time */
	trap_on_nil_contents  = false;
	target_dbl_maxexp     = 308;

	/* set assembler id prefixes */
	local_prefix = "S."; /* S for static */
	name_prefix  = "";

	/* init nowhere */
	setregalt(nowhere.answhere, 0);
	nowhere.ashwhere.ashsize = 0;
	nowhere.ashwhere.ashsize = 0;
}

static int
option(char c, const char *optarg)
{
	UNUSED(optarg);

	switch (c) {
	case 'e': no_error_jump   = 1; break;
	case 'm': do_macros       = 1; break;
	case 'n': do_dynamic_init = 1; break;

	default:
		return -1;
	}

	return 0;
}

static int
switch_cpu(const char *optarg)
{
	switch (*optarg) {
	case 'C': cpu = CPU_COMMON;  break;
	case 'R': cpu = CPU_RS6000;  break;
	case 'P': cpu = CPU_POWERPC; break;

	default:
		return -1;
	}

	return 0;
}

static void
unhas(void)
{
	/* Things trans.power does not "has" */
	has &= ~HAS_BYTEOPS;
	has &= ~HAS_BYTEREGS;
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_ROTATE;
	has &= ~HAS_MAXMIN;
	has &= ~HAS_SETCC;
	has &= ~HAS_COMPLEX;
	has &= ~HAS_64_BIT;
	has &= ~HAS_LONG_DOUBLE;

	if (writable_strings) {
		/* TODO: either always on, or always off. error out accordingly */
	}
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

	"emn",
	option,
	switch_cpu,

	local_translate_capsule,

	ABI_POWER,
	CCONV_XLC,
	ENDIAN_BIG | ENDIAN_LITTLE,
	FORMAT_XCOFF,
	DIAG_NONE | DIAG_STABX | DIAG_XDB_OLD | DIAG_XDB_NEW,
	ASM_IBM
};

