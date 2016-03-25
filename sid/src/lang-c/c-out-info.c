/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-out-info.c - Output control ADT.
 *
 * This file implements the SID output information routines.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "c-out-info.h"
#include "c-code.h"

void
c_out_info_init(COutputInfoT *info, OutputInfoT *out_info)
{
	info->info              = out_info;
	info->header1           = NULL;
	info->header2           = NULL;
	info->trailer1          = NULL;
	info->trailer2          = NULL;
	persistent_list_init(&info->persistents);
	nstring_copy_cstring(c_out_info_type_prefix(info), "ZT");
	nstring_copy_cstring(c_out_info_fn_prefix(info), "ZR");
	nstring_copy_cstring(c_out_info_in_prefix(info), "ZI");
	nstring_copy_cstring(c_out_info_out_prefix(info), "ZO");
	nstring_copy_cstring(c_out_info_label_prefix(info), "ZL");
	nstring_copy_cstring(c_out_info_terminal_prefix(info), "ZB");
	nstring_copy_cstring(c_out_info_persistents_prefix(info), "ZP");
	info->prototypes        = false;
	info->numeric_ids       = false;
	info->numeric_terminals = true;
	info->casts             = false;
	info->unreachable       = false;
	info->lines             = true;
	info->terminals         = true;
	info->split             = 0;
}

OutputInfoT *
c_out_info_info(COutputInfoT *info)
{
	return info->info;
}

OStreamT *
c_out_info_ostream(COutputInfoT *info)
{
	return out_info_get_current_ostream(info->info);
}

char *
c_out_info_program_name(COutputInfoT *info)
{
	return out_info_get_prog_name(info->info);
}

char *
c_out_info_source_name(COutputInfoT *info)
{
	return out_info_get_infile_name(info->info, 0);
}

char *
c_out_info_c_source_name(COutputInfoT *info)
{
	return out_info_get_infile_name(info->info, 1);
}

CCodeT *
c_out_info_get_header1(COutputInfoT *info)
{
	return info->header1;
}

void
c_out_info_set_header1(COutputInfoT *info, CCodeT *code)
{
	info->header1 = code;
}

CCodeT *
c_out_info_get_header2(COutputInfoT *info)
{
	return info->header2;
}

void
c_out_info_set_header2(COutputInfoT *info, CCodeT *code)
{
	info->header2 = code;
}

CCodeT *
c_out_info_get_trailer1(COutputInfoT *info)
{
	return info->trailer1;
}

void
c_out_info_set_trailer1(COutputInfoT *info, CCodeT *code)
{
	info->trailer1 = code;
}

CCodeT *
c_out_info_get_trailer2(COutputInfoT *info)
{
	return info->trailer2;
}

void
c_out_info_set_trailer2(COutputInfoT *info, CCodeT *code)
{
	info->trailer2 = code;
}

NStringT *
c_out_info_type_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_TYPE];
}

NStringT *
c_out_info_fn_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_FN];
}

NStringT *
c_out_info_in_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_IN];
}

NStringT *
c_out_info_out_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_OUT];
}

NStringT *
c_out_info_label_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_LABEL];
}

NStringT *
c_out_info_terminal_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_TERMINAL];
}

NStringT *
c_out_info_persistents_prefix(COutputInfoT *info)
{
	return &info->prefixes[CPFX_PERSISTENTS];
}

NStringT *
c_out_info_prefix(COutputInfoT *info, CPrefixT prefix)
{
	return &info->prefixes[prefix];
}

PersistentListT *
c_out_info_persistents(COutputInfoT *info)
{
	return &info->persistents;
}

bool
c_out_info_get_prototypes(COutputInfoT *info)
{
	return info->prototypes;
}

void
c_out_info_set_prototypes(COutputInfoT *info, bool prototypes)
{
	info->prototypes = prototypes;
}

bool
c_out_info_get_numeric_ids(COutputInfoT *info)
{
	return info->numeric_ids;
}

void
c_out_info_set_numeric_ids(COutputInfoT *info, bool numeric_ids)
{
	info->numeric_ids = numeric_ids;
}

bool
c_out_info_get_numeric_terminals(COutputInfoT *info)
{
	return info->numeric_terminals;
}

void
c_out_info_set_numeric_terminals(COutputInfoT *info, bool numeric_terminals)
{
	info->numeric_terminals = numeric_terminals;
}

bool
c_out_info_get_casts(COutputInfoT *info)
{
	return info->casts;
}

void
c_out_info_set_casts(COutputInfoT *info, bool casts)
{
	info->casts = casts;
}

bool
c_out_info_get_unreachable(COutputInfoT *info)
{
	return info->unreachable;
}

void
c_out_info_set_unreachable(COutputInfoT *info, bool unreachable)
{
	info->unreachable = unreachable;
}

bool
c_out_info_get_lines(COutputInfoT *info)
{
	return info->lines;
}

void
c_out_info_set_lines(COutputInfoT *info, bool lines)
{
	info->lines = lines;
}

bool
c_out_info_get_terminals(COutputInfoT *info)
{
	return info->terminals;
}

void
c_out_info_set_terminals(COutputInfoT *info, bool lines)
{
	info->terminals = lines;
}

unsigned
c_out_info_get_split(COutputInfoT *info)
{
	return info->split;
}

void
c_out_info_set_split(COutputInfoT *info, unsigned split)
{
	info->split = split;
}
